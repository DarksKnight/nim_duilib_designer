#include "../stdafx.h"
#include "EditorToolbar.h"

EditorToolbar::EditorToolbar()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_toolbar.xml");
	_btn_tool_file = (ui::Button*)FindSubControl(L"btn_tool_file");
	_btn_tool_file->AttachClick(nbase::Bind(&EditorToolbar::OnClickFile, this, std::placeholders::_1));
}


EditorToolbar::~EditorToolbar()
{
}

bool EditorToolbar::OnClickFile(ui::EventArgs* args)
{
	ui::UiRect rect = args->pSender->GetPos();
	ui::CPoint point(rect.left, rect.bottom);
	::ClientToScreen(GetWindow()->GetHWND(), &point);
	nim_comp::CMenuWnd* toolFileMenu = new nim_comp::CMenuWnd(GetWindow()->GetHWND());
	ui::STRINGorID xml(L"../layout/menu_tool_bar_file.xml");
	toolFileMenu->Init(xml, _T("xml"), point);
	nim_comp::CMenuElementUI* menuFileSave = (nim_comp::CMenuElementUI*)toolFileMenu->FindControl(L"menu_save_file");
	menuFileSave->AttachSelect(nbase::Bind(&EditorToolbar::OnMenuSaveFile, this, std::placeholders::_1));
	nim_comp::CMenuElementUI* menuSettings = (nim_comp::CMenuElementUI*)toolFileMenu->FindControl(L"menu_settings");
	menuSettings->AttachSelect(nbase::Bind(&EditorToolbar::OnMenuSettings, this, std::placeholders::_1));
	return true;
}

bool EditorToolbar::OnMenuSaveFile(ui::EventArgs* args)
{
	if (_save_callback) {
		_save_callback();
	}
	return true;
}

bool EditorToolbar::OnMenuSettings(ui::EventArgs* args)
{
	return true;
}