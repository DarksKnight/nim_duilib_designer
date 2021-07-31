#include "../stdafx.h"
#include "EditorCreateForm.h"
#include "../internal/SettingsHelper.h"
#include "../item/CreateDataItem.h"
#include "../internal/XmlHelper.h"
#include "../internal/ControlHelper.h"

const LPCTSTR EditorCreateForm::kClassName = L"EditorCreateForm";

EditorCreateForm::EditorCreateForm()
{
	_create_data_infos.push_back(CreateDataInfo(L"window", L"窗口"));
	_create_data_infos.push_back(CreateDataInfo(L"window_with_title", L"窗口(带默认标题栏)"));
	_create_data_infos.push_back(CreateDataInfo(L"box", L"自定义控件"));
	_create_data_infos.push_back(CreateDataInfo(L"dialog", L"弹窗"));
}


EditorCreateForm::~EditorCreateForm()
{
}

std::wstring EditorCreateForm::GetSkinFolder()
{
	return L"layout";
}

std::wstring EditorCreateForm::GetSkinFile()
{
	return L"layout_editor_create.xml";
}

std::wstring EditorCreateForm::GetWindowClassName() const
{
	return kClassName;
}

std::wstring EditorCreateForm::GetWindowId() const
{
	return kClassName;
}

void EditorCreateForm::InitWindow()
{
	_box_preview = (ui::Box*)FindControl(L"box_preview");
	_cb_settings_show = (ui::CheckBox*)FindControl(L"cb_settings_show");
	_cb_settings_show->AttachSelect(nbase::Bind(&EditorCreateForm::OnSelectSettings, this, std::placeholders::_1));
	_cb_settings_show->AttachUnSelect(nbase::Bind(&EditorCreateForm::OnSelectSettings, this, std::placeholders::_1));
	_list_create_type = (ui::ListBox*)FindControl(L"list_create_type");
	for (auto it = _create_data_infos.begin(); it != _create_data_infos.end(); ++it) {
		CreateDataItem* item = new CreateDataItem(*it);
		_list_create_type->Add(item);
	}
	_list_create_type->AttachSelect(nbase::Bind(&EditorCreateForm::OnCreateTypeSelect, this, std::placeholders::_1));
	_list_create_type->SelectItem(0);
	_btn_new_file = (ui::Button*)FindControl(L"btn_new_file"); 
	_btn_new_file->AttachClick(nbase::Bind(&EditorCreateForm::OnNewFileClick, this, std::placeholders::_1));
	_btn_open_file = (ui::Button*)FindControl(L"btn_open_file");
	_btn_open_file->AttachClick(nbase::Bind(&EditorCreateForm::OnOpenFileClick, this, std::placeholders::_1));
	_btn_cancel = (ui::Button*)FindControl(L"btn_cancel");
	_btn_cancel->AttachClick(nbase::Bind(&EditorCreateForm::OnCancelClick, this, std::placeholders::_1));
	std::wstring value = SettingsHelper::GetInstance()->Get(CONFIG_TAG_CREATE, CONFIG_KEY_CREATE_SHOW, L"1");
	_cb_settings_show->Selected(value == L"1");
}

LRESULT EditorCreateForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (_operation_type == OperationType::NEW_FILE && _new_file_callback) {
		_new_file_callback(_create_flag);
	}
	else if (_operation_type == OperationType::OPEN_FILE && _open_file_callback && !_path.empty()) {
		_open_file_callback(_path);
	}
	if (_close_callback) {
		_close_callback(_operation_type);
	}
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT EditorCreateForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN && wParam == VK_RETURN) {
		OnNewFileClick(NULL);
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

bool EditorCreateForm::OnCreateTypeSelect(ui::EventArgs* args)
{
	CreateDataItem* item = (CreateDataItem*)(_list_create_type->GetItemAt(args->wParam));
	_create_flag = item->GetDataName();
	std::wstring templeteXml = ui::GlobalManager::GetResourcePath() + L"templete\\templete_" + _create_flag + L".xml";
	ParseXmlPreview(_box_preview, templeteXml);
	return true;
}

bool EditorCreateForm::OnNewFileClick(ui::EventArgs* args)
{
	_operation_type = OperationType::NEW_FILE;
	Close();
	return true;
}

bool EditorCreateForm::OnOpenFileClick(ui::EventArgs* args)
{
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.xml)"] = L"*.xml";
	fileDlg->SetFilter(filters);
	fileDlg->SetDefExt(L".xml");
	fileDlg->SetParentWnd(GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorCreateForm::OnSelectPathCallback, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AyncShowOpenFileDlg(callback2);
	return true;
}

bool EditorCreateForm::OnCancelClick(ui::EventArgs* args)
{
	Close();
	return true;
}

bool EditorCreateForm::OnSelectSettings(ui::EventArgs * args)
{
	if (_cb_settings_show->IsSelected()) {
		SettingsHelper::GetInstance()->Set(CONFIG_TAG_CREATE, CONFIG_KEY_CREATE_SHOW, L"1");
	}
	else {
		SettingsHelper::GetInstance()->Set(CONFIG_TAG_CREATE, CONFIG_KEY_CREATE_SHOW, L"0");
	}
	return true;
}

void EditorCreateForm::OnSelectPathCallback(BOOL ret, std::wstring path)
{
	_operation_type = OperationType::OPEN_FILE;
	_path = path;
	Close();
}

bool EditorCreateForm::ParseXmlPreview(ui::Box* box, const std::wstring& path)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError result = doc.LoadFile(nbase::UTF16ToUTF8(path).c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return false;
	}
	box->RemoveAll();
	ParseElement(doc.RootElement(), box);
	return true;
}

void EditorCreateForm::ParseElement(tinyxml2::XMLElement* element, ui::Box* rootBox)
{
	if (!rootBox) {
		return;
	}
	for (tinyxml2::XMLElement* currentElement = element->FirstChildElement(); currentElement; currentElement = currentElement->NextSiblingElement()) {
		std::wstring value = nbase::UTF8ToUTF16(currentElement->Value());
		AreaControlDelegate* areaControl = ControlHelper::GetInstance()->DropControl(rootBox, value);
		areaControl->ParseElement(currentElement);
		ui::Box* containerBox = dynamic_cast<ui::Box*>(areaControl);
		if (!currentElement->NoChildren() && containerBox) {
			ParseElement(currentElement, containerBox);
		}
	}
}