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
	nim_comp::CMenuElementUI* menuFileSave = (nim_comp::CMenuElementUI*)toolFileMenu->FindControl(L"menu_save");
	menuFileSave->AttachSelect(nbase::Bind(&EditorToolbar::OnMenuFileSave, this, std::placeholders::_1));
	nim_comp::CMenuElementUI* menuNewFile = (nim_comp::CMenuElementUI*)toolFileMenu->FindControl(L"menu_new_file");
	menuNewFile->AttachSelect(nbase::Bind(&EditorToolbar::OnMenuNewFile, this, std::placeholders::_1));
	return true;
}

bool EditorToolbar::OnMenuFileSave(ui::EventArgs* args)
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