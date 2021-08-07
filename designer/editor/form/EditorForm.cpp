#include "../stdafx.h"
#include "EditorForm.h"
#include "../internal/XmlHelper.h"
#include "../internal/ControlHelper.h"
#include "../item/PropertyItem.h"
#include "../internal/PropertyHelper.h"
#include "../internal/CopyHelper.h"
#include "../internal/SettingsHelper.h"
#include "../internal/GlobalXmlHelper.h"
#include "EditorImportForm.h"
#include "../internal/ProjectXmlHelper.h"

const LPCTSTR EditorForm::kClassName = L"EditorForm";

EditorForm::EditorForm()
{
}


EditorForm::~EditorForm()
{
}

std::wstring EditorForm::GetSkinFolder()
{
	return L"layout";
}

std::wstring EditorForm::GetSkinFile()
{
	return L"layout_editor.xml";
}

std::wstring EditorForm::GetWindowClassName() const
{
	return kClassName;
}

std::wstring EditorForm::GetWindowId() const
{
	return kClassName;
}

void EditorForm::InitWindow()
{
	m_pRoot->AttachBubbledEvent(ui::kEventAll, nbase::Bind(&EditorForm::Notify, this, std::placeholders::_1));
	_menu_property_list = (MenuPropertyList*)FindControl(L"menu_property_list");
	_menu_property_list->SetSelectCallback(nbase::Bind(&EditorForm::OnMenuPropertyListSelect, this, std::placeholders::_1, std::placeholders::_2));
	_lb_title = (ui::Label*)FindControl(L"lb_title");
	_btn_close = (ui::Button*)FindControl(L"btn_close");
	_btn_close->AttachClick(nbase::Bind(&EditorForm::OnClickExit, this, std::placeholders::_1));
	_toolbar = (EditorToolbar*)FindControl(L"et");
	_toolbar->SetSaveCallback(nbase::Bind(&EditorForm::SaveFile, this));
	_toolbar->SetNewFileCallback(nbase::Bind(&EditorForm::OpenCreateForm, this));
	_toolbar->SetOpenFileCallback(nbase::Bind(&EditorForm::OnOpenFile, this));
	_box_container = (ui::Box*)FindControl(L"box_container");
	_box_property = (ui::Box*)FindControl(L"box_property");
	_controls_list = (EditorControlsList*)FindControl(L"ecl");
	_editor_property = (EditorProperty*)FindControl(L"ep");
	_editor_tree_controls = (EditorTreeControls*)FindControl(L"etc");
	_editor_tree_project = (EditorTreeProject*)FindControl(L"etp");
	_box_drag_pre = (ui::Box*)FindControl(L"box_drag_pre");
	_box_editor_area = (ui::Box*)FindControl(L"box_editor_area");
	_tb_tree = (ui::TabBox*)FindControl(L"tb_tree");
	_btn_tree_project = (ui::Button*)FindControl(L"btn_tree_project");
	_btn_tree_project->AttachClick(nbase::Bind(&EditorForm::OnClickTab, this, std::placeholders::_1));
	_btn_tree_controls = (ui::Button*)FindControl(L"btn_tree_controls");
	_btn_tree_controls->AttachClick(nbase::Bind(&EditorForm::OnClickTab, this, std::placeholders::_1));
	_controls_list->SetSelectCallback(nbase::Bind(&EditorForm::OnSelect, this ,std::placeholders::_1));
	_controls_list->SetButtonUpCallback(nbase::Bind(&EditorForm::OnButtonUp, this));
	nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&EditorForm::OnInitForm, this));
}

LRESULT EditorForm::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	_box_drag_pre->SetMargin(ui::UiRect(pt.x, pt.y, 0, 0));
	return __super::OnMouseMove(uMsg, wParam, lParam, bHandled);
}

LRESULT EditorForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN) {
		if (wParam == 'S' && ::GetKeyState(VK_CONTROL) < 0) {
			SaveFile();
		}
		else if (wParam == 'C' && ::GetKeyState(VK_CONTROL) < 0) {
			ui::Control* ctrl = _editor_area->FindSelectedItem(_editor_area->GetAreaWindow());
			CopyHelper::GetInstance()->Copy(ctrl);
		}
		else if (wParam == 'V' && ::GetKeyState(VK_CONTROL) < 0) {
			CopyHelper::GetInstance()->Paste();
		}
		else if (::GetKeyState(VK_DELETE) < 0) {
			_editor_area->RemoveSelectItem();
		}
	}
	else if (uMsg == WM_NCLBUTTONDBLCLK) {
		if (IsZoomed(GetHWND())) {
			ui::Control* pMaxButton = (ui::Control*)FindControl(L"maxbtn");
			ui::Control* pRestoreButton = (ui::Control*)FindControl(L"restorebtn");
			if (pMaxButton && pRestoreButton) {
				pMaxButton->SetVisible(true);
				pRestoreButton->SetVisible(false);
			}
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		else {
			ui::Control* pMaxButton = (ui::Control*)FindControl(L"maxbtn");
			ui::Control* pRestoreButton = (ui::Control*)FindControl(L"restorebtn");
			if (pMaxButton && pRestoreButton) {
				pMaxButton->SetVisible(false);
				pRestoreButton->SetVisible(true);
			}
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		return 1;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void EditorForm::OnInitForm()
{
	/*ui::Control* pMaxButton = (ui::Control*)FindControl(L"maxbtn");
	ui::Control* pRestoreButton = (ui::Control*)FindControl(L"restorebtn");
	if (pMaxButton && pRestoreButton) {
		pMaxButton->SetVisible(false);
		pRestoreButton->SetVisible(true);
	}
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);*/
	int width = GetPos().GetWidth();
	_controls_list->SetFixedWidth(width / 7);
	_box_property->SetFixedWidth(width / 6);
	std::wstring value = SettingsHelper::GetInstance()->Get(CONFIG_TAG_CREATE, CONFIG_KEY_CREATE_SHOW, L"1");
	if (value == L"1") {
		OpenImportForm();
	}
}

bool EditorForm::Notify(ui::EventArgs* args)
{
	if (args->Type != ui::kEventNotify) {
		return true;
	}
	switch (args->wParam)
	{
	case CustomEventType::UI_CHANGED:
		UiChanged();
		break;
	case CustomEventType::CONTROL_SELECTED:
		ShowControlPropery();
		break;
	case CustomEventType::CONTROL_SET_PROPERTY:
	{
		ui::Control* item = _editor_area->FindSelectedItem(_editor_area->GetAreaWindow());
		if (item) {
			PropertyItem* pItem = (PropertyItem*)args->pSender;
			PropertyHelper::GetInstance()->SetProperty(item, pItem->GetDataName(), pItem->GetValue());
		}
		break;
	}
	case CustomEventType::SHOW_CLASS_PROPERTY_LIST:
	{
		PropertyItem* item = (PropertyItem*)args->pSender;
		_menu_property_list->Show(L"class");
		_menu_property_list->SetFixedWidth(item->GetWidth() - 110);
		_menu_property_list->SetMargin(ui::UiRect(item->GetPos(false).left + 110, item->GetPos(false).top + item->GetHeight(), 0, 0));
		_menu_property_list->LoadClassData(GlobalXmlHelper::GetInstance()->GetClasses());
		break;
	}
	case CustomEventType::SHOW_FONT_PROPERTY_LIST:
	{
		PropertyItem* item = (PropertyItem*)args->pSender;
		_menu_property_list->Show(L"font");
		_menu_property_list->SetFixedWidth(item->GetWidth() - 110);
		_menu_property_list->SetMargin(ui::UiRect(item->GetPos(false).left + 110, item->GetPos(false).top + item->GetHeight(), 0, 0));
		_menu_property_list->LoadFontData(GlobalXmlHelper::GetInstance()->GetClasses());
		break;
	}
	case CustomEventType::PROPERTY_ITEM_CLASS_TEXT_CHANGE:
	{
		ui::RichEdit* richEdit = (ui::RichEdit*)args->pSender;
		std::wstring keyword = richEdit->GetText();
		_menu_property_list->LoadClassData(GlobalXmlHelper::GetInstance()->GetClasses(), keyword);
		break;
	}
	case CustomEventType::PROPERTY_ITEM_FONT_TEXT_CHANGE:
	{
		ui::RichEdit* richEdit = (ui::RichEdit*)args->pSender;
		std::wstring keyword = richEdit->GetText();
		_menu_property_list->LoadFontData(GlobalXmlHelper::GetInstance()->GetClasses(), keyword);
		break;
	}
	case CustomEventType::HIDE_PROPERTY_LIST:
	{
		if (!_menu_property_list->GetPos().IsPointIn(args->ptMouse)) {
			_menu_property_list->Hide();
		}
		break;
	}
	case CustomEventType::TREE_PROJECT_SELECTED:
	{
		DirChunkUI* item = (DirChunkUI*)args->pSender;
		DoOpenFile(item->GetPath());
		break;
	}
	default:
		break;
	}
	return true;
}

bool EditorForm::OnClickTab(ui::EventArgs* args)
{
	std::wstring name = args->pSender->GetName();
	if (name == L"btn_tree_project") {
		_tb_tree->SelectItem(L"etp");
	}
	else {
		_tb_tree->SelectItem(L"etc");
	}
	return true;
}

bool EditorForm::OnClickExit(ui::EventArgs* args)
{
	PostQuitMessage(0);
	return true;
}

void EditorForm::OnSelect(const ControlData& data)
{
	_select_data = data;
	ui::Box* preBox = new ui::Box;
	ui::CSize preSize = ControlHelper::GetInstance()->GetPreSize(_select_data.name);
	preBox->SetFixedWidth(preSize.cx);
	preBox->SetFixedHeight(preSize.cy);
	preBox->SetBkColor(L"bk_wnd_darkcolor");
	_box_drag_pre->Add(preBox);
	_box_drag_pre->SetVisible(true);
}

void EditorForm::OnButtonUp()
{
	_box_drag_pre->RemoveAll();
	_box_drag_pre->SetVisible(false);
	POINT pt = { 0 };
	::GetCursorPos(&pt);
	::ScreenToClient(m_hWnd, &pt);
	ui::UiRect rect = _editor_area->GetPos();
	if (!rect.IsPointIn(pt)) {
		return;
	}
	AreaControlDelegate* delegate = _editor_area->DropControl(_select_data.name);
	ui::Box* parent = delegate->GetCtonrol()->GetParent();
	if (parent) {
		_editor_tree_controls->AddNode(_select_data, delegate->GetDelegateData(), (DelegateData*)parent->GetUserDataBase());
	}
	else {
		_editor_tree_controls->AddNode(_select_data, delegate->GetDelegateData());
	}
	UiChanged();
}

void EditorForm::SaveFile()
{
	if (_saved) {
		return;
	}
	if (_last_save_path.empty()) {
		nim_comp::ShowMsgBox(GetHWND(), NULL, L"STRID_UNSAVE_ERROR_NOT_FOUND_FILE", true, L"STRID_HINT", true, L"STRING_OK", true);
		return;
	}
	if (!XmlHelper::GetInstance()->ConvertXml(_editor_area, _last_save_path)) {
		nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), L"STRID_UNSAVE_ERROR_NOT_FOUND_FILE", true, L"STRID_HINT");
		return;
	}
	std::wstring fileName;
	nbase::FilePathApartFileName(_last_save_path, fileName);
	_title = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_EDITORFORM_TITLE") + L" - " + fileName;
	_lb_title->SetText(_title);
	_saved = true;
}

void EditorForm::DoNewFile(const std::wstring& flag)
{
	_templete_path = ui::GlobalManager::GetResourcePath() + L"templete\\templete_" + flag + L".xml";
	if (!nbase::FilePathIsExist(_templete_path, false)) {
		nim_comp::ShowMsgBox(GetHWND(), NULL, L"STRID_CREATE_ERROR", true, L"STRID_HINT", true, L"STRING_OK", true);
		return;
	}
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.xml)"] = L"*.xml";
	fileDlg->SetFilter(filters);
	fileDlg->SetFileName(L"new");
	fileDlg->SetDefExt(L".xml");
	fileDlg->SetParentWnd(GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorForm::OnSaveSelectPathCallback, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AyncShowSaveFileDlg(callback2);
}

void EditorForm::OnOpenFile()
{
	if (!_saved && _box_editor_area->GetCount() > 0) {
		nim_comp::ShowMsgBox(GetHWND(), NULL, L"STRID_UNSAVE_TIP", true, L"STRID_HINT", true, L"STRING_OK", true);
		return;
	}
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.xml)"] = L"*.xml";
	fileDlg->SetFilter(filters);
	fileDlg->SetDefExt(L".xml");
	fileDlg->SetParentWnd(GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorForm::OnOpenSelectPathCallback, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AyncShowOpenFileDlg(callback2);
}

void EditorForm::DoOpenFile(const std::wstring& path)
{
	_box_editor_area->RemoveAll();
	_saved = true;
	_last_save_path = path;
	XmlHelper::GetInstance()->SetSavedXmlPath(_last_save_path);
	_toolbar->SetEnabled(true);
	_controls_list->SetVisible(true);
	_box_property->SetVisible(true);
	_editor_area = new EditorArea;
	_box_editor_area->Add(_editor_area);
	ControlHelper::GetInstance()->SetContainerBox(_editor_area);
	XmlHelper::GetInstance()-> ParseXml(_editor_area, path, nbase::Bind(&EditorForm::OnParseControl, this, std::placeholders::_1), nbase::Bind(&EditorForm::OnParseFinish, this));
	std::wstring fileName = L"";
	nbase::FilePathApartFileName(path, fileName);
	_title = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_EDITORFORM_TITLE") + L" - " + fileName;
	_lb_title->SetText(_title);
}

void EditorForm::OnCreateFormClose(EditorCreateForm::OperationType type)
{
	_toolbar->SetEnabled(true);
}

void EditorForm::OnSaveSelectPathCallback(BOOL ret, std::wstring path)
{
	if (!ret) {
		return;
	}
	_last_save_path = path;
	XmlHelper::GetInstance()->SetSavedXmlPath(_last_save_path);
	_toolbar->SetEnabled(true);
	_controls_list->SetVisible(true);
	_box_property->SetVisible(true);
	std::wstring fileName;
	nbase::FilePathApartFileName(_last_save_path, fileName);
	_title = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_EDITORFORM_TITLE") + L" - " + fileName;
	_lb_title->SetText(_title);
	nbase::WriteFile(_last_save_path, "");
	_box_editor_area->RemoveAll();
	_editor_area = new EditorArea;
	_box_editor_area->Add(_editor_area);
	if (!XmlHelper::GetInstance()->ParseXml(_editor_area, _templete_path, nbase::Bind(&EditorForm::OnParseControl, this, std::placeholders::_1), nbase::Bind(&EditorForm::OnParseFinish, this))) {
		nim_comp::ShowMsgBox(GetHWND(), NULL, L"STRID_CREATE_ERROR", true, L"STRID_HINT", true, L"STRING_OK", true);
	}
	SaveFile();
}

void EditorForm::OnOpenSelectPathCallback(BOOL ret, std::wstring path)
{
	if (!ret || path.empty()) {
		return;
	}
	DoOpenFile(path);
}

void EditorForm::OnParseControl(AreaControlDelegate* delegate)
{
	ui::Box* box = delegate->GetCtonrol()->GetParent();
	if (box) {
		_editor_tree_controls->AddNode(delegate->GetControlData(), delegate->GetDelegateData(), (DelegateData*)box->GetUserDataBase());
	}
	else {
		_editor_tree_controls->AddNode(delegate->GetControlData(), delegate->GetDelegateData());
	}
}

void EditorForm::OnParseFinish()
{
	_editor_tree_controls->Update();
}

void EditorForm::OpenImportForm()
{
	EditorImportForm* form = (EditorImportForm*)(nim_comp::WindowsManager::GetInstance()->GetWindow(EditorImportForm::kClassName, EditorImportForm::kClassName));
	if (form) {
		form->ActiveWindow();
	}
	else {
		form = new EditorImportForm();
		form->Create(GetHWND(), EditorCreateForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
		form->SetSelectCallback(nbase::Bind(&EditorForm::ReadNd, this, std::placeholders::_1));
		form->CenterWindow();
		form->ShowWindow();
	}
}

void EditorForm::OpenCreateForm()
{
	if (!_saved && _box_editor_area->GetCount() > 0) {
		nim_comp::ShowMsgBox(GetHWND(), NULL, L"STRID_UNSAVE_TIP", true, L"STRID_HINT", true, L"STRING_OK", true);
		return;
	}
	EditorCreateForm* form = (EditorCreateForm*)(nim_comp::WindowsManager::GetInstance()->GetWindow(EditorCreateForm::kClassName, EditorCreateForm::kClassName));
	if (form) {
		form->ActiveWindow();
	}
	else {
		form = new EditorCreateForm();
		form->Create(GetHWND(), EditorCreateForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
		form->CenterWindow();
		form->SetNewFileCallback(nbase::Bind(&EditorForm::DoNewFile, this, std::placeholders::_1));
		form->SetOpenFileCallback(nbase::Bind(&EditorForm::DoOpenFile, this, std::placeholders::_1));
		form->SetCloseCallback(nbase::Bind(&EditorForm::OnCreateFormClose, this, std::placeholders::_1));
		form->ShowWindow();
	}
}

void EditorForm::UiChanged()
{
	_saved = false;
	_lb_title->SetText(_title + L" *");
}

void EditorForm::ShowControlPropery()
{
	ui::Control* item = _editor_area->FindSelectedItem((ui::Box*)_editor_area->GetItemAt(0));
	AreaControlDelegate* delegate = dynamic_cast<AreaControlDelegate*>(item);
	if (item && delegate) {
		_editor_property->LoadProperty(delegate->GetControlData().name, delegate);
		_editor_property->LoadControlProperty(item);
	}
}

void EditorForm::OnMenuPropertyListSelect(const std::wstring& key, const std::wstring& value)
{
	_menu_property_list->SetVisible(false);
	ui::Control* item = _editor_area->FindSelectedItem(_editor_area->GetAreaWindow());
	if (!item) {
		return;
	}
	PropertyHelper::GetInstance()->SetProperty(item, key, value);
	_editor_property->SetProperty(key, value);
}

void EditorForm::ReadNd(const std::wstring& rdPath)
{
	bool result = ProjectXmlHelper::GetInstance()->ReadNd(rdPath);
	if (!result) {
		return;
	}
	_toolbar->SetEnabled(true);
	_controls_list->SetVisible(true);
	_box_property->SetVisible(true);
	_editor_tree_project->LoadData();
}