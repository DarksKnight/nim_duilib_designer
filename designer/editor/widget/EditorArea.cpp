#include "../stdafx.h"
#include "EditorArea.h"

EditorArea::EditorArea()
{
	ui::Box* windowBox = new ui::Box;
	windowBox->AttachButtonDown(nbase::Bind(&EditorArea::OnButtonDown, this, std::placeholders::_1));
	windowBox->AttachButtonUp(nbase::Bind(&EditorArea::OnButtonUp, this, std::placeholders::_1));
	windowBox->AttachAllEvents(nbase::Bind(&EditorArea::OnMouseEvent, this, std::placeholders::_1));
	windowBox->SetName(L"sampleWindow");
	windowBox->SetFixedWidth(_window_info.width);
	windowBox->SetFixedHeight(_window_info.height);
	windowBox->SetBorderSize(1);
	windowBox->SetBorderColor(L"blue");
	windowBox->SetBkColor(L"bk_wnd_darkcolor");
	this->Add(windowBox);
}


EditorArea::~EditorArea()
{
}

ui::Control* EditorArea::DropControl(ControlData* data)
{
	ui::Box* container = NULL;
	if (!data->isLoad) {
		POINT pt = { 0 };
		::GetCursorPos(&pt);
		::ScreenToClient(GetWindow()->GetHWND(), &pt);
		container = FindParentBox(pt);
		ui::UiRect rect = container->GetPos();
		data->margin.left = pt.x - rect.left;
		data->margin.top = pt.y - rect.top;
	}
	else {
		container = data->parentBox;
	}
	if (data->name == L"Box") {
		ui::Box* boxContainer = new ui::Box;
		SetUniversalData(boxContainer, data);
		container->Add(boxContainer);
		return boxContainer;
	}
	else if (data->name == L"HBox") {
		ui::HBox* boxContainer = new ui::HBox;
		SetUniversalData(boxContainer, data);
		container->Add(boxContainer);
		return boxContainer;
	}
	else if (data->name == L"VBox") {
		ui::VBox* boxContainer = new ui::VBox;
		SetUniversalData(boxContainer, data);
		container->Add(boxContainer);
		return boxContainer;
	}
	else if (data->name == L"Label") {
		ui::Label* label = new ui::Label;
		SetUniversalData(label, data);
		label->SetText(L"label");
		container->Add(label);
		return label;
	}
	return NULL;
}

bool EditorArea::OnButtonDown(ui::EventArgs* args)
{
	if (_select_item_callback) {
		_select_item_callback(args->pSender);
	}
	Reset(GetItemAt(0));
	args->pSender->SetDataID(L"down");
	args->pSender->SetBorderColor(L"red");
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
	if (args->pSender->GetName() != L"sampleWindow") {
		args->pSender->SetMargin(rect);
	}
	else {
		_window_info.width = args->pSender->GetFixedWidth();
		_window_info.height = args->pSender->GetFixedHeight();
	}
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

void EditorArea::SetUniversalData(ui::Control* control, ControlData* data)
{
	control->AttachButtonDown(nbase::Bind(&EditorArea::OnButtonDown, this, std::placeholders::_1));
	control->AttachButtonUp(nbase::Bind(&EditorArea::OnButtonUp, this, std::placeholders::_1));
	control->AttachAllEvents(nbase::Bind(&EditorArea::OnMouseEvent, this, std::placeholders::_1));
	control->SetFixedWidth(data->width);
	control->SetFixedHeight(data->height);
	control->SetUserDataBase(data);
	control->SetBorderSize(1);
	control->SetBorderColor(L"blue");
	control->SetMargin(data->margin);
}

void EditorArea::Reset(ui::Control* control)
{
	control->SetBorderColor(L"blue");
	ui::Box* box = dynamic_cast<ui::Box*>(control);
	if (!box) {
		return;
	}
	for (int i = 0; i < box->GetCount(); i++) {
		ui::Control* subCtrl = box->GetItemAt(i);
		ui::Box* subBox = dynamic_cast<ui::Box*>(subCtrl);
		if (!subBox) {
			subCtrl->SetBorderColor(L"blue");
			continue;
		}
		Reset(subCtrl);
	}
}