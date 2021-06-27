#include "../stdafx.h"
#include "EditorForm.h"
#include "../internal/XmlHelper.h"
#include "../internal/ControlHelper.h"

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
	_lb_title = (ui::Label*)FindControl(L"lb_title");
	_toolbar = (EditorToolbar*)FindControl(L"et");
	_toolbar->InitCtrls();
	_toolbar->SetSaveCallback(nbase::Bind(&EditorForm::OnSaveFile, this));
	_toolbar->SetNewFileCallback(nbase::Bind(&EditorForm::OnNewFile, this));
	_toolbar->SetOpenFileCallback(nbase::Bind(&EditorForm::OnOpenFile, this, std::placeholders::_1));
	_box_container = (ui::Box*)FindControl(L"box_container");
	_controls_list = (EditorControlsList*)FindControl(L"ecl");
	_box_property = (ui::Box*)FindControl(L"box_property");
	_box_drag_pre = (ui::Box*)FindControl(L"box_drag_pre");
	_box_editor_area = (ui::Box*)FindControl(L"box_editor_area");
	int width = GetPos().GetWidth();
	_controls_list->SetFixedWidth(width / 6);
	_box_property->SetFixedWidth(width / 5);
	_controls_list->SetSelectCallback(nbase::Bind(&EditorForm::OnSelect, this ,std::placeholders::_1));
	_controls_list->SetButtonUpCallback(nbase::Bind(&EditorForm::OnButtonUp, this));
	nbase::ThreadManager::PostTask(kThreadUI, nbase::Bind(&EditorForm::OpenCreateForm, this));
}

LRESULT EditorForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
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
			OnSaveFile();
		}
		else if (::GetKeyState(VK_DELETE) < 0) {
			_editor_area->RemoveSelectItem();
		}
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

bool EditorForm::Notify(ui::EventArgs* args)
{
	if (args->Type == ui::kEventNotify && args->wParam == CustomEventType::UI_CHANGED) {
		UiChanged();
	}
	return true;
}

void EditorForm::OnSelect(const std::wstring& name)
{
	_select_name = name;
	ui::Box* preBox = new ui::Box;
	ui::CSize preSize = ControlHelper::GetInstance()->GetPreSize(_select_name);
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
	_editor_area->DropControl(_select_name);
	UiChanged();
}

void EditorForm::OnSaveFile()
{
	if (!_last_save_path.empty()) {
		OnSelectPathCallback(TRUE, _last_save_path);
		return;
	}
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.xml)"] = L"*.xml";
	fileDlg->SetFilter(filters);
	fileDlg->SetFileName(L"newFile");
	fileDlg->SetDefExt(L".xml");
	fileDlg->SetParentWnd(GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorForm::OnSelectPathCallback, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AyncShowSaveFileDlg(callback2);
}

void EditorForm::OnNewFile()
{
	_toolbar->SetEnabled(false);
	_controls_list->SetVisible(false);
	EditorCreateForm* form = (EditorCreateForm*)(nim_comp::WindowsManager::GetInstance()->GetWindow(EditorCreateForm::kClassName, EditorCreateForm::kClassName));
	if (!form) {
		form = new EditorCreateForm();
		form->Create(GetHWND(), EditorCreateForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
		form->CenterWindow();
		form->SetNewFileCallback(nbase::Bind(&EditorForm::DoNewFile, this, std::placeholders::_1));
		form->SetOpenFileCallback(nbase::Bind(&EditorForm::OnOpenFile, this, std::placeholders::_1));
		form->SetCloseCallback(nbase::Bind(&EditorForm::OnCreateFormClose, this));
		form->ShowWindow();
	}
	else {
		form->ActiveWindow();
	}
}

void EditorForm::DoNewFile(EditorCreateForm::CreateType type)
{
	if (!_saved && _box_editor_area->GetCount() > 0) {
		nim_comp::MsgboxCallback cb = nbase::Bind(&EditorForm::OnNewFileMsgBoxCallback, this, std::placeholders::_1, type);
		nim_comp::ShowMsgBox(GetHWND(), cb, L"STRID_UNSAVE_TIP", true, L"STRID_HINT", true, L"STRING_OK", true, L"STRING_CANCEL", true);
		return;
	}
	_saved = false;
	_last_save_path = L"";
	_box_editor_area->RemoveAll();
	_editor_area = new EditorArea;
	_box_editor_area->Add(_editor_area);
	_title = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_EDITORFORM_TITLE") + L" - " + ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_EDITORFORM_NEW_FILE");
	_lb_title->SetText(_title);
}

void EditorForm::OnOpenFile(const std::wstring& path)
{
	if (!_saved && _box_editor_area->GetCount() > 0) {
		nim_comp::MsgboxCallback cb = nbase::Bind(&EditorForm::OnOpenFileMsgBoxCallback, this, std::placeholders::_1, path);
		nim_comp::ShowMsgBox(GetHWND(), cb, L"STRID_UNSAVE_TIP", true, L"STRID_HINT", true, L"STRING_OK", true, L"STRING_CANCEL", true);
		return;
	}
	DoOpenFile(path);
}

void EditorForm::DoOpenFile(const std::wstring& path)
{
	_box_editor_area->RemoveAll();
	_saved = true;
	_last_save_path = path;
	_editor_area = new EditorArea;
	_box_editor_area->Add(_editor_area);
	XmlHelper::GetInstance()->ParseXml(_editor_area, path);
	std::wstring fileName = L"";
	nbase::FilePathApartFileName(path, fileName);
	_title = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_EDITORFORM_TITLE") + L" - " + fileName;
	_lb_title->SetText(_title);
}

void EditorForm::OnCreateFormClose()
{
	_toolbar->SetEnabled(true);
	_controls_list->SetVisible(true);
}

void EditorForm::OnSelectPathCallback(BOOL ret, std::wstring path)
{
	if (!ret) {
		return;
	}
	_saved = true;
	_last_save_path = path;
	std::wstring fileName;
	nbase::FilePathApartFileName(_last_save_path, fileName);
	_title = ui::MutiLanSupport::GetInstance()->GetStringViaID(L"STRID_EDITORFORM_TITLE") + L" - " + fileName;
	_lb_title->SetText(_title);
	if (!XmlHelper::GetInstance()->ConvertXml(_editor_area, path)) {
		nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), L"STRID_SAVE_FAIL", true, L"STRID_HINT");
	}
}

void EditorForm::OnNewFileMsgBoxCallback(nim_comp::MsgBoxRet ret, EditorCreateForm::CreateType type)
{
	if (ret == nim_comp::MB_NO) {
		_saved = true;
		DoNewFile(type);
		return;
	}
	OnSaveFile();
}

void EditorForm::OnOpenFileMsgBoxCallback(nim_comp::MsgBoxRet ret, const std::wstring& path)
{
	if (ret == nim_comp::MB_YES) {
		OnSaveFile();
		return;
	}
	DoOpenFile(path);
}

void EditorForm::OpenCreateForm()
{
	_toolbar->SetEnabled(false);
	_controls_list->SetVisible(false);
	EditorCreateForm* form = new EditorCreateForm();
	form->Create(GetHWND(), EditorCreateForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	form->CenterWindow();
	form->SetNewFileCallback(nbase::Bind(&EditorForm::DoNewFile, this, std::placeholders::_1));
	form->SetOpenFileCallback(nbase::Bind(&EditorForm::OnOpenFile, this, std::placeholders::_1));
	form->SetCloseCallback(nbase::Bind(&EditorForm::OnCreateFormClose, this));
	form->ShowWindow();
}

void EditorForm::UiChanged()
{
	_saved = false;
	_lb_title->SetText(_title + L" *");
}