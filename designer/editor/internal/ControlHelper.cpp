#include "../stdafx.h"
#include "ControlHelper.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaWindow.h"
#include "../controls/AreaHBox.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaVBox.h"

ControlHelper::ControlHelper()
{
}


ControlHelper::~ControlHelper()
{
}

std::vector<ControlData> ControlHelper::GetControlList()
{
	if (!_datas.empty()) {
		return _datas;
	}
	_datas.push_back(ControlData(L"Box", L"无约束容器"));
	_datas.push_back(ControlData(L"HBox", L"横向容器"));
	_datas.push_back(ControlData(L"VBox", L"纵向容器"));
	_datas.push_back(ControlData(L"Control", L"基础控件"));
	return _datas;
}

ui::CSize ControlHelper::GetPreSize(const std::wstring& name)
{
	ui::CSize size(50, 50);
	if (name == L"Box" || name == L"HBox" || name == L"VBox") {
		size.cx = 100;
		size.cy = 60;
	}
	else if (name == L"Control") {
		size.cx = 50;
		size.cy = 50;
	}
	else if (name == L"Label") {
		size.cx = 50;
		size.cy = 20;
	}
	return size;
}

AreaControlDelegate* ControlHelper::CreateControl(const std::wstring& name)
{
	AreaControlDelegate* control = NULL;
	if (name == L"Box") {
		control = new AreaBox;
	}
	else if (name == L"HBox") {
		control = new AreaHBox;
	}
	else if (name == L"VBox") {
		control = new AreaVBox;
	}
	else if (name == L"Control") {
		control = new AreaControl;
	}
	return control;
}

AreaControlDelegate* ControlHelper::AddControl(ui::Box* box, const std::wstring& name, const std::wstring& controlName)
{
	AreaControlDelegate* control = CreateControl(name);
	if (!control) {
		return NULL;
	}
	if (name == L"Box") {
		box->Add((AreaBox*)control);
	}
	else if (name == L"HBox") {
		box->Add((AreaHBox*)control);
	}
	else if (name == L"VBox") {
		box->Add((AreaVBox*)control);
	}
	else if (name == L"Control") {
		box->Add((AreaControl*)control);
	}
	control->SetControlName(controlName);
	return control;
}

ui::Control* ControlHelper::Clone(AreaControlDelegate* delegate)
{
	ui::Control* control = NULL;
	return control;
}

void ControlHelper::Remove(ui::Control* control)
{
	if (!control) {
		return;
	}
	AreaHBoxDelegate* tempHBox = dynamic_cast<AreaHBoxDelegate*>(control);
	if (tempHBox) {
		tempHBox->Remove();
		return;
	}
	AreaVBoxDelegate* tempVBox = dynamic_cast<AreaVBoxDelegate*>(control);
	if (tempVBox) {
		tempVBox->Remove();
		return;
	}
	AreaBoxDelegate* tempBox = dynamic_cast<AreaBoxDelegate*>(control);
	if (tempBox) {
		tempBox->Remove();
		return;
	}
	AreaControlDelegate* tempControl = dynamic_cast<AreaControlDelegate*>(control);
	if (tempControl) {
		tempControl->Remove();
		return;
	}
}

bool ControlHelper::CheckDupliName(const std::wstring& name, ui::Box* box)
{
	if (!box) {
		return false;
	}
	for (int i = 0; i < box->GetCount(); i++) {
		ui::Control* control = box->GetItemAt(i);
		if (control->GetName() == name) {
			return true;
		}
		ui::Box* container = dynamic_cast<ui::Box*>(control);
		if (container) {
			bool result = CheckDupliName(name, container);
			if (result) {
				return true;
			}
		}
	}
	return false;
}

std::wstring ControlHelper::GetControlName(const std::wstring& name, ui::Box* box)
{
	std::wstring controlName = L"";
	if (name == L"Box") {
		controlName = name + nbase::IntToString16(_box_index);
		_box_index++;
	}
	else if (name == L"HBox") {
		controlName = name + nbase::IntToString16(_hbox_index);
		_hbox_index++;
	}
	else if (name == L"VBox") {
		controlName = name + nbase::IntToString16(_vbox_index);
		_vbox_index++;
	}
	else if (name == L"Control") {
		controlName = name + nbase::IntToString16(_control_index);
		_control_index++;
	}
	if (CheckDupliName(name, box)) {
		return GetControlName(name, box);
	}
	return controlName;
}