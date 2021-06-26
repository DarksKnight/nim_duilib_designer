#include "../stdafx.h"
#include "EditorForm.h"
#include "../internal/XmlHelper.h"

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
	_control_datas.push_back(new ControlData(L"Box", 160, 80));
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
	_controls_list->LoadData(_control_datas);

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
	if (uMsg == WM_KEYDOWN && wParam == 'S' && ::GetKeyState(VK_CONTROL) < 0) {
		OnSaveFile();
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void EditorForm::OnSelect(ControlData* data)
{
	_select_data = data;
	ui::Box* preBox = new ui::Box;
	preBox->SetFixedWidth(_pre_box_width);
	preBox->SetFixedHeight(_pre_box_height);
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
	_editor_area->DropControl(_select_data);
}

void EditorForm::OnSaveFile()
{
	if (_saved) {
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
	EditorCreateForm* form = (EditorCreateForm*)(nim_comp::WindowsManager::GetInstance()->GetWindow(EditorCreateForm::kClassName, EditorCreateForm::kClassName));
	if (!form)
	{
		form = new EditorCreateForm();
		form->Create(GetHWND(), EditorCreateForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
		form->CenterWindow();
		form->SetNewFileCallback(nbase::Bind(&EditorForm::DoNewFile, this, std::placeholders::_1));
		form->SetOpenFileCallback(nbase::Bind(&EditorForm::OnOpenFile, this, std::placeholders::_1));
		form->ShowWindow();
	}
	else
	{
		form->ActiveWindow();
	}
}

void EditorForm::DoNewFile(EditorCreateForm::CreateType type)
{
	if (!_saved && _box_editor_area->GetCount() > 0) {
		nim_comp::MsgboxCallback cb = nbase::Bind(&EditorForm::OnMsgBoxCallback, this, std::placeholders::_1, type);
		nim_comp::ShowMsgBox(GetHWND(), cb, L"STRID_UNSAVE_TIP", true, L"STRID_HINT", true, L"STRING_OK", true, L"STRING_CANCEL", true);
		return;
	}
	_saved = false;
	_box_editor_area->RemoveAll();
	_editor_area = new EditorArea;
	_box_editor_area->Add(_editor_area);
}

void EditorForm::OnOpenFile(const std::wstring& path)
{
	_saved = true;
	_last_save_path = path;
	_editor_area = new EditorArea;
	_box_editor_area->Add(_editor_area);
	XmlHelper::GetInstance()->ParseXml(_editor_area, path);
}

void EditorForm::OnSelectPathCallback(BOOL ret, std::wstring path)
{
	if (!ret) {
		return;
	}
	_saved = true;
	_last_save_path = path;
	if (!XmlHelper::GetInstance()->ConvertXml(_editor_area, path)) {
		nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), L"STRID_SAVE_FAIL", true, L"STRID_HINT");
	}
}

void EditorForm::OnMsgBoxCallback(nim_comp::MsgBoxRet ret, EditorCreateForm::CreateType type)
{
	if (ret == nim_comp::MB_NO) {
		_saved = true;
		DoNewFile(type);
		return;
	}
	OnSaveFile();
}

void EditorForm::OpenCreateForm()
{
	EditorCreateForm* form = new EditorCreateForm();
	form->Create(GetHWND(), EditorCreateForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	form->CenterWindow();
	form->SetNewFileCallback(nbase::Bind(&EditorForm::DoNewFile, this, std::placeholders::_1));
	form->SetOpenFileCallback(nbase::Bind(&EditorForm::OnOpenFile, this, std::placeholders::_1));
	form->ShowWindow();
}