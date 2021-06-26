#include "../stdafx.h"
#include "EditorArea.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaWindow.h"
#include "../controls/AreaHBox.h"
#include "../controls/AreaBox.h"

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
	ui::Box* container = NULL;
	POINT pt = { 0 };
	::GetCursorPos(&pt);
	::ScreenToClient(GetWindow()->GetHWND(), &pt);
	container = (AreaBox*)FindParentBox(pt);
	if (!container) {
		return;
	}
	AreaControlDelegate* areaControl = NULL;
	if (name == L"Box") {
		areaControl = new AreaBox;
		container->Add((AreaBox*)areaControl);
	}
	else if (name == L"HBox") {
		areaControl = new AreaHBox;
		container->Add((AreaHBox*)areaControl);
	}
	areaControl->SetUIMargin(pt, container);
}

bool EditorArea::Notify(ui::EventArgs* args)
{
	if (args->Type == ui::kEventNotify && args->wParam == CustomEventType::CONTROL_BUTTON_DOWN) {
		Reset(GetItemAt(0));
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
	return NULL;
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