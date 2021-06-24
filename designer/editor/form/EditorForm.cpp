#include "../stdafx.h"
#include "EditorForm.h"

const std::wstring EditorForm::kClassName = L"EditorForm";

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

void EditorForm::InitWindow()
{
	_draw_controls[0] = DrawControl(ControlType::Box, L"Box");
	_box_container = (ui::Box*)FindControl(L"box_container");
	_controls_list = (EditorControlsList*)FindControl(L"ecl");
	_editor_area = (EditorArea*)FindControl(L"ea");
	_box_property = (ui::Box*)FindControl(L"box_property");
	_box_drag_pre = (ui::Box*)FindControl(L"box_drag_pre");
	int width = GetPos().GetWidth();
	_controls_list->SetFixedWidth(width / 6);
	_box_property->SetFixedWidth(width / 5);
	_controls_list->SetSelectCallback(nbase::Bind(&EditorForm::OnSelect, this ,std::placeholders::_1));
	_controls_list->SetButtonUpCallback(nbase::Bind(&EditorForm::OnButtonUp, this));
	_controls_list->LoadData(_draw_controls);
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

void EditorForm::OnSelect(DrawControl control)
{
	_select_control = control;
	ui::Box* preBox = new ui::Box;
	preBox->SetFixedWidth(100);
	preBox->SetFixedHeight(60);
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
	_editor_area->DropControl(_select_control);
}