#include "../stdafx.h"
#include "EditorTreeProject.h"
#include "../internal/ProjectXmlHelper.h"

std::string DirChunk::OnGetIUIStyleName() const
{
	return "DirChunkUI";
}

int DirChunkUI::GetHeight()
{
	return 20;
}

void DirChunkUI::OnFill()
{
	AttachDoubleClick(nbase::Bind(&DirChunkUI::OnDoubleClick, this, std::placeholders::_1));
	auto&& data = std::dynamic_pointer_cast<DirData>(doc_item_);
	if (!data) {
		return;
	}
	ui::Label* lbDesc = (ui::Label*)FindSubControl(L"lb_desc");
	lbDesc->SetText(data->name);
}

bool DirChunkUI::OnDoubleClick(ui::EventArgs* args)
{
	if (_selected_callback) {
		auto&& data = std::dynamic_pointer_cast<DirData>(doc_item_);
		_selected_callback(data->path);
	}
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
		_tree->SetWindow(GetWindow(), this, false);
		_tree->RegisterStyleUI("DirChunkUI", [this]() {
			DirChunkUI* item = new DirChunkUI;
			item->SetVirtualParent(_tree);
			ui::GlobalManager::FillBoxWithCache(item, L"layout/item_tree_dir.xml");
			item->SetWindow(_tree->GetWindow(), NULL);
			item->SetOwner(_tree);
			item->SetSelectedCallback(ToWeakCallback([=](const std::wstring& path) {
				_selected_path = path;
				GetWindow()->SendNotify(this, ui::kEventNotify, TREE_PROJECT_SELECTED);
				}));
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