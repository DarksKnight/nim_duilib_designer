#include "../stdafx.h"
#include "EditorArea.h"

EditorArea::EditorArea()
{
}


EditorArea::~EditorArea()
{
}

void EditorArea::DropControl(DrawControl control)
{
	POINT pt = { 0 };
	::GetCursorPos(&pt);
	::ScreenToClient(GetWindow()->GetHWND(), &pt);
	ui::Box* container = FindParentBox(pt);
	ui::UiRect rect = container->GetPos();
	int left = pt.x - rect.left;
	int top = pt.y - rect.top;
	switch (control.id)
	{
	case ControlType::Box:
	{
		ui::Box* boxContainer = new ui::Box;
		boxContainer->AttachButtonDown(nbase::Bind(&EditorArea::OnButtonDown, this, std::placeholders::_1));
		boxContainer->AttachButtonUp(nbase::Bind(&EditorArea::OnButtonUp, this, std::placeholders::_1));
		boxContainer->AttachAllEvents(nbase::Bind(&EditorArea::OnMouseEvent, this, std::placeholders::_1));
		boxContainer->SetName(L"box2");
		boxContainer->SetFixedWidth(160);
		boxContainer->SetFixedHeight(80);
		boxContainer->SetBorderSize(1);
		boxContainer->SetBorderColor(L"blue");
		container->Add(boxContainer);
		boxContainer->SetMargin(ui::UiRect(left, top, 0, 0));
		break;
	}
	default:
		break;
	}
}

bool EditorArea::OnButtonDown(ui::EventArgs* args)
{
	args->pSender->SetDataID(L"down");
	ui::UiRect controlRect = args->pSender->GetPos();
	if (args->ptMouse.x - controlRect.left < PADDING) {
		_current_direction = Direction::LEFT;
	}
	else if (controlRect.right - args->ptMouse.x < PADDING) {
		_current_direction = Direction::RIGHT;
	}
	else if (args->ptMouse.y - controlRect.top < PADDING) {
		_current_direction = Direction::TOP;
	}
	else if (controlRect.bottom - args->ptMouse.y < PADDING) {
		_current_direction = Direction::BOTTOM;
	}
	_last_point = args->ptMouse;
	return true;
}

bool EditorArea::OnButtonUp(ui::EventArgs* args)
{
	args->pSender->SetDataID(L"");
	_current_direction = Direction::NONE;
	return true;
}

bool EditorArea::OnMouseEvent(ui::EventArgs* args)
{
	if (args->Type != ui::kEventMouseMove) {
		return true;
	}
	ui::UiRect controlRect = args->pSender->GetPos();
	if (args->ptMouse.x - controlRect.left < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
	}
	else if (controlRect.right - args->ptMouse.x < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
	}
	else if (args->ptMouse.y - controlRect.top < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
	}
	else if (controlRect.bottom - args->ptMouse.y < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
	}
	std::wstring dataId = args->pSender->GetDataID();
	if (dataId != L"down") {
		return true;
	}
	ui::UiRect rect = args->pSender->GetMargin();
	int left = args->ptMouse.x - _last_point.x;
	int top = args->ptMouse.y - _last_point.y;
	switch (_current_direction)
	{
	case Direction::LEFT:
	{
		rect.left += left;
		int width = args->pSender->GetFixedWidth() - left;
		if (width < 1) {
			width = 1;
		}
		args->pSender->SetFixedWidth(width);
		break;
	}
	case Direction::RIGHT:
	{
		rect.right += left;
		args->pSender->SetFixedWidth(args->pSender->GetFixedWidth() + left);
		break;
	}
	case Direction::TOP:
	{
		rect.top += top;
		int height = args->pSender->GetFixedHeight() - top;
		if (height < 1) {
			height = 1;
		}
		args->pSender->SetFixedHeight(height);
		break;
	}
	case Direction::BOTTOM:
	{
		rect.bottom += top;
		args->pSender->SetFixedHeight(args->pSender->GetFixedHeight() + top);
		break;
	}
	default:
		rect.left += left;
		rect.top += top;
		break;
	}
	args->pSender->SetMargin(rect);
	_last_point = args->ptMouse;
	return true;
}

ui::Box* EditorArea::FindParentBox(POINT pt)
{
	ui::Control* control = dynamic_cast<ui::Control*>(GetWindow()->FindControl(pt));
	if (!control) {
		return this;
	}
	control = dynamic_cast<ui::Box*>(control);
	if (control) {
		return (ui::Box*)control;
	}
	control = control->GetParent();
	if (!control) {
		return this;
	}
	return (ui::Box*)control;
}