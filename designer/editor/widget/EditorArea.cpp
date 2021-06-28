#include "../stdafx.h"
#include "EditorArea.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaWindow.h"
#include "../controls/AreaHBox.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaVBox.h"
#include "../internal/ControlHelper.h"

EditorArea::EditorArea()
{
	AttachBubbledEvent(ui::kEventAll, nbase::Bind(&EditorArea::Notify, this, std::placeholders::_1));
	AreaWindow* areaWindow = new AreaWindow;
	Add(areaWindow);
}


EditorArea::~EditorArea()
{
}

void EditorArea::DropControl(const std::wstring& name)
{
	POINT pt = { 0 };
	::GetCursorPos(&pt);
	::ScreenToClient(GetWindow()->GetHWND(), &pt);
	ui::Box* container = FindParentBox(pt);
	std::wstring controlName = ControlHelper::GetInstance()->GetControlName(name, (ui::Box*)GetItemAt(0));
	AreaControlDelegate* areaControl = ControlHelper::GetInstance()->AddControl(container, name, controlName);
	AreaBox* tempBox = dynamic_cast<AreaBox*>(container);
	if (tempBox) {
		tempBox->SetDropIMargin(pt, areaControl);
		return;
	}
	AreaHBox* tempHBox = dynamic_cast<AreaHBox*>(container);
	if (tempHBox) {
		tempHBox->SetDropIMargin(pt, areaControl);
		return;
	}
	AreaVBox* tempVBox = dynamic_cast<AreaVBox*>(container);
	if (tempVBox) {
		tempVBox->SetDropIMargin(pt, areaControl);
		return;
	}
}

void EditorArea::DropControl(ui::Control* control)
{
	ui::Box* container = NULL;
	POINT pt = { 0 };
	::GetCursorPos(&pt);
	::ScreenToClient(GetWindow()->GetHWND(), &pt);
	container = FindParentBox(pt);
	container->Add(control);
}

void EditorArea::RemoveSelectItem()
{
	ui::Control* selectedItem = FindSelectedItem((ui::Box*)GetItemAt(0));
	if (!selectedItem) {
		return;
	}
	ControlHelper::GetInstance()->Remove(selectedItem);
}

ui::Control* EditorArea::FindSelectedItem(ui::Box* box)
{
	AreaControlDelegate* curDelegate = dynamic_cast<AreaControlDelegate*>(box);
	if (curDelegate->IsSelected()) {
		return box;
	}
	for (int i = 0; i < box->GetCount(); i++) {
		ui::Control* control = box->GetItemAt(i);
		AreaControlDelegate* delegate = dynamic_cast<AreaControlDelegate*>(control);
		if (!delegate) {
			continue;
		}
		if (delegate->IsSelected()) {
			return control;
		}
		ui::Box* container = dynamic_cast<ui::Box*>(control);
		if (container) {
			ui::Control* temp = FindSelectedItem(container);
			if (temp) {
				return temp;
			}
		}
	}
	return NULL;
}

bool EditorArea::Notify(ui::EventArgs* args)
{
	if (args->Type == ui::kEventNotify) {
		switch (args->wParam)
		{
		case CustomEventType::CONTROL_BUTTON_DOWN:
			Reset(GetItemAt(0));
			break;
		case CustomEventType::CONTROL_COPY:
		{
			ui::Control* ctrl = args->pSender;
			_copy_ctrl = new ui::Control(*ctrl);
			break;
		}
		case CustomEventType::CONTROL_PASTE:
		{
			ui::Control* selectedItem = FindSelectedItem((ui::Box*)GetItemAt(0));
			break;
		}
		default:
			break;
		}
	}
	return true;
}

ui::Box* EditorArea::FindParentBox(POINT pt)
{
	ui::Control* control = dynamic_cast<ui::Control*>(GetWindow()->FindControl(pt));
	if (!control) {
		return NULL;
	}
	ui::Box* box = dynamic_cast<ui::Box*>(control);
	if (box) {
		return box;
	}
	ui::Box* parentBox = dynamic_cast<ui::Box*>(control->GetParent());
	if (parentBox) {
		return parentBox;
	}
	return (ui::Box*)GetItemAt(0);
}

void EditorArea::Reset(ui::Control* control)
{
	AreaControlDelegate* currentCtrl = dynamic_cast<AreaControlDelegate*>(control);
	if (!currentCtrl) {
		return;
	}
	currentCtrl->Reset();
	ui::Box* box = dynamic_cast<ui::Box*>(control);
	if (!box) {
		return;
	}
	for (int i = 0; i < box->GetCount(); i++) {
		AreaControlDelegate* subCtrl = dynamic_cast<AreaControlDelegate*>(box->GetItemAt(i));
		if (!subCtrl) {
			continue;
		}
		ui::Box* subBox = dynamic_cast<ui::Box*>(subCtrl);
		if (!subBox) {
			subCtrl->Reset();
			continue;
		}
		Reset(box->GetItemAt(i));
	}
}