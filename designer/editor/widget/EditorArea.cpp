#include "../stdafx.h"
#include "EditorArea.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaWindow.h"

EditorArea::EditorArea()
{
	AreaWindow* areaWindow = new AreaWindow;
	areaWindow->SetButtonDownCallback(nbase::Bind(&EditorArea::OnItemButtonDown, this));
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
	container = FindParentBox(pt);
	AreaControl* areaControl = NULL;
	if (name == L"Box") {
		areaControl = new AreaBox;
		container->Add((AreaBox*)areaControl);
	}
	if (areaControl) {
		areaControl->SetButtonDownCallback(nbase::Bind(&EditorArea::OnItemButtonDown, this));
	}
	ui::UiRect rect = container->GetPos();
	ui::UiRect margin(pt.x - rect.left, pt.y - rect.top, 0, 0);
	int lastIndex = container->GetCount() - 1;
	container->GetItemAt(lastIndex)->SetMargin(margin);
}

void EditorArea::OnItemButtonDown()
{
	Reset(GetItemAt(0));
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