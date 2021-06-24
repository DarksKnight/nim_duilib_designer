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
	_btn_tool_file->AttachClick(nbase::Bind(&EditorToolbar::OnClick, this, std::placeholders::_1));
}

bool EditorToolbar::OnClick(ui::EventArgs* args)
{
	ui::UiRect rect = args->pSender->GetPos();
	ui::CPoint point(rect.left, rect.bottom);
	::ClientToScreen(GetWindow()->GetHWND(), &point);
	nim_comp::CMenuWnd* _tool_file_menu = new nim_comp::CMenuWnd(GetWindow()->GetHWND());
	ui::STRINGorID xml(L"../layout/layout_tool_menu.xml");
	_tool_file_menu->Init(xml, _T("xml"), point);
	return true;
}