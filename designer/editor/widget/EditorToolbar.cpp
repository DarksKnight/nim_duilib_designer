#include "../stdafx.h"
#include "EditorToolbar.h"

EditorToolbar::EditorToolbar()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_toolbar.xml");
}


EditorToolbar::~EditorToolbar()
{
}

void EditorToolbar::InitCtrls()
{
	_btn_tool_file = (ui::Button*)FindSubControl(L"btn_tool_file");
	_btn_tool_file->AttachClick(nbase::Bind(&EditorToolbar::OnClickFile, this, std::placeholders::_1));
}

bool EditorToolbar::OnClickFile(ui::EventArgs* args)
{
	ui::UiRect rect = args->pSender->GetPos();
	ui::CPoint point(rect.left, rect.bottom);
	::ClientToScreen(GetWindow()->GetHWND(), &point);
	nim_comp::CMenuWnd* toolFileMenu = new nim_comp::CMenuWnd(GetWindow()->GetHWND());
	ui::STRINGorID xml(L"../layout/menu_file.xml");
	toolFileMenu->Init(xml, _T("xml"), point);
	nim_comp::CMenuElementUI* menuFileSave = (nim_comp::CMenuElementUI*)toolFileMenu->FindControl(L"menu_save_file");
	menuFileSave->AttachSelect(nbase::Bind(&EditorToolbar::OnMenuSaveFile, this, std::placeholders::_1));
	nim_comp::CMenuElementUI* menuNewFile = (nim_comp::CMenuElementUI*)toolFileMenu->FindControl(L"menu_new_file");
	menuNewFile->AttachSelect(nbase::Bind(&EditorToolbar::OnMenuNewFile, this, std::placeholders::_1));
	nim_comp::CMenuElementUI* menuOpenFile = (nim_comp::CMenuElementUI*)toolFileMenu->FindControl(L"menu_open_file");
	menuOpenFile->AttachSelect(nbase::Bind(&EditorToolbar::OnMenuOpenFile, this, std::placeholders::_1));
	return true;
}

bool EditorToolbar::OnMenuSaveFile(ui::EventArgs* args)
{
	if (_save_callback) {
		_save_callback();
	}
	return true;
}

bool EditorToolbar::OnMenuNewFile(ui::EventArgs* args)
{
	if (_new_file_callback) {
		_new_file_callback();
	}
	return true;
}

bool EditorToolbar::OnMenuOpenFile(ui::EventArgs* args)
{
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.xml)"] = L"*.xml";
	fileDlg->SetFilter(filters);
	fileDlg->SetFileName(L"newFile");
	fileDlg->SetDefExt(L".xml");
	fileDlg->SetParentWnd(GetWindow()->GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorToolbar::OnSelectPathCallback, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AyncShowOpenFileDlg(callback2);
	return true;
}

void EditorToolbar::OnSelectPathCallback(BOOL ret, std::wstring path)
{
	if (!ret) {
		return;
	}
	if (!_open_file_callback) {
		return;
	}
	_open_file_callback(path);
}