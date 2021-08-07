#include "../stdafx.h"
#include "EditorTreeProject.h"
#include "../internal/ProjectXmlHelper.h"
#include <shellapi.h>

void DirChunkUI::OnFill()
{
	AttachDoubleClick(nbase::Bind(&DirChunkUI::OnDoubleClick, this, std::placeholders::_1));
	auto&& data = std::dynamic_pointer_cast<DirData>(doc_item_);
	if (!data) {
		return;
	}
	_path = data->path;
	std::wstring suffix = L"";
	nbase::FilePathExtension(data->path, suffix);
	_is_dir = suffix.empty();
	ui::Label* lbDesc = (ui::Label*)FindSubControl(L"lb_desc");
	lbDesc->SetText(data->name);
}

bool DirChunkUI::OnDoubleClick(ui::EventArgs* args)
{
	auto&& data = std::dynamic_pointer_cast<DirData>(doc_item_);
	GetWindow()->SendNotify(this, ui::kEventNotify, TREE_PROJECT_SELECTED);
	return true;
}

EditorTreeProject::EditorTreeProject()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_tree_project.xml");
	_box_tree_project = (ui::Box*)FindSubControl(L"box_tree_project");
	nbase::ThreadManager::PostTask(ThreadId::kThreadGlobalMisc, ToWeakCallback([this]() {
		_tree = new TreeComponent;
		_box_tree_project->Add(_tree);
		_tree->SetVerScrollUnitPixels(120);
		_tree->SetHorScrollUnitPixels(120);
		_tree->AttachBubbledEvent(ui::kEventMouseRightButtonDown, nbase::Bind(&EditorTreeProject::OnItemMenu, this, std::placeholders::_1));
		_tree->SetWindow(GetWindow(), this, false);
		_tree->RegisterStyleUI("DirChunkUI", [this]() {
			DirChunkUI* item = new DirChunkUI;
			item->SetVirtualParent(_tree);
			item->SetWindow(_tree->GetWindow(), NULL);
			item->SetOwner(_tree);
			return std::shared_ptr<DirChunkUI>(item);
			});
		}));
}

EditorTreeProject::~EditorTreeProject()
{
}

void EditorTreeProject::LoadData()
{
	nbase::ThreadManager::PostTask(ThreadId::kThreadGlobalMisc, ToWeakCallback([this]() {
		InitFolder(ProjectXmlHelper::GetInstance()->GetLangElement());
		InitFolder(ProjectXmlHelper::GetInstance()->GetResourcesElement());
		InitFolder(ProjectXmlHelper::GetInstance()->GetLayoutElement());
		nbase::ThreadManager::PostTask(ThreadId::kThreadUI, ToWeakCallback([=]() {
			_tree->Update(true);
			}));
		}));
}

void EditorTreeProject::InitFolder(tinyxml2::XMLElement* element)
{
	if (!element) {
		return;
	}
	nbase::ThreadManager::PostTask(ThreadId::kThreadUI, ToWeakCallback([=]() {
		auto doc = _tree->GetDoc();
		std::wstring rootPath = ProjectXmlHelper::GetInstance()->GetRootPath();
		for (tinyxml2::XMLElement* currentElement = element->FirstChildElement(); currentElement; currentElement = currentElement->NextSiblingElement()) {
			std::wstring path = nbase::UTF8ToUTF16(currentElement->Attribute("path"));
			std::wstring folderPath = L"";
			nbase::FilePathApartDirectory(path, folderPath);
			std::list<std::wstring> folderList = ui::StringHelper::Split(folderPath.substr(rootPath.length()), L"\\");
			std::wstring prePath = rootPath;
			for (auto it = folderList.begin(); it != folderList.end(); ++it) {
				auto item = std::make_shared<DirChunk>();
				item->SetTreeComponent(_tree);
				item->name = *it;
				item->path = prePath + *it + L"\\";
				item->SetItemID(nbase::UTF16ToUTF8(prePath + *it + L"\\"));
				item->GetUI()->Collapse();
				auto findItem = doc->GetItem(nbase::UTF16ToUTF8(prePath + *it + L"\\"));
				if (findItem) {
					prePath += *it + L"\\";
					continue;
				}
				auto parentItem = doc->GetItem(nbase::UTF16ToUTF8(prePath));
				if (parentItem) {
					doc->AddItem(item, parentItem);
				}
				else {
					doc->AddItem(item);
				}
				prePath += *it + L"\\";
			}
			if (folderPath == rootPath) {
				continue;
			}
			auto item = std::make_shared<DirChunk>();
			item->SetTreeComponent(_tree);
			std::wstring fn = L"";
			nbase::FilePathApartFileName(path, fn);
			item->name = fn;
			item->path = path;
			item->SetItemID(nbase::UTF16ToUTF8(path));
			auto parentItem = doc->GetItem(nbase::UTF16ToUTF8(folderPath));
			doc->AddItem(item, parentItem);
		}
	}));
}

bool EditorTreeProject::OnItemMenu(ui::EventArgs* args)
{
	nim_comp::CMenuWnd* menu = new nim_comp::CMenuWnd(GetWindow()->GetHWND());
	ui::STRINGorID xml(L"");
	DirChunkUI* item = (DirChunkUI*)args->pSender;
	ui::UiRect rect = args->pSender->GetPos();
	ui::CPoint point(rect.left, rect.bottom);
	::ClientToScreen(GetWindow()->GetHWND(), &point);
	bool isDir = item->IsDir();
	if (isDir) {
		xml.m_lpstr = L"../layout/menu_tree_project_dir.xml";
	}
	else {
		xml.m_lpstr = L"../layout/menu_tree_project_file.xml";
	}
	menu->Init(xml, _T("xml"), point);
	nim_comp::CMenuElementUI* menuOpenDir = (nim_comp::CMenuElementUI*)menu->FindControl(L"menu_open_dir");
	menuOpenDir->AttachClick(nbase::Bind(&EditorTreeProject::OnMenuOpenDir, this, std::placeholders::_1, isDir, item->GetPath()));
	nim_comp::CMenuElementUI* menuDel = (nim_comp::CMenuElementUI*)menu->FindControl(L"menu_del");
	menuDel->AttachClick(nbase::Bind(&EditorTreeProject::OnMenuDel, this, std::placeholders::_1, isDir, item->GetPath()));
	return true;
}

bool EditorTreeProject::OnMenuOpenDir(ui::EventArgs* args, bool isDir, const std::wstring& path)
{
	if (isDir) {
		ShellExecute(NULL, L"open", L"explorer.exe", path.c_str(), NULL, SW_SHOWNORMAL);
	}
	else {
		ShellExecute(NULL, L"open", L"explorer.exe", (L"/select," + path).c_str(), NULL, SW_SHOWNORMAL);
	}
	return true;
}

bool EditorTreeProject::OnMenuDel(ui::EventArgs* args, bool isDir, const std::wstring& path)
{
	bool result = true;
	if (isDir) {

	}
	else {
		result = nbase::DeleteFileW(path) == TRUE;
	}
	if (!result) {
		return true;
	}
	_tree->GetDoc()->RemoveItem(nbase::UTF16ToUTF8(path));
	ProjectXmlHelper::GetInstance()->RemoveItem(path);
	_tree->Update(true);
	return true;
}