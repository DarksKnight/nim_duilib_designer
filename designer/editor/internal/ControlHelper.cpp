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
	SIZE_T cchLen = name.length();
	switch (cchLen) {
	case 3:
		if (name == DUI_CTR_BOX) {
			size.cx = 100;
			size.cy = 60;
		}
		break;
	case 4:
		if (name == DUI_CTR_HBOX || name == DUI_CTR_VBOX) {
			size.cx = 100;
			size.cy = 60;
		}
		break;
	case 5:
		if (name == DUI_CTR_LABEL) {
			size.cx = 50;
			size.cy = 20;
		}
		break;
	case 7:
		if (name == DUI_CTR_CONTROL) {
			size.cx = 50;
			size.cy = 50;
		}
		break;
	default:
		break;
	}
	return size;
}

void ControlHelper::DropControl(ui::Box* box, POINT pt, const std::wstring& name)
{
	AreaControlDelegate* delegate = NULL;
	SIZE_T cchLen = name.length();
	switch (cchLen) {
	case 3:
		if (name == DUI_CTR_BOX) {
			delegate = new AreaBox;
			box->Add((AreaBox*)delegate);
		}
		break;
	case 4:
		if (name == DUI_CTR_HBOX) {
			delegate = new AreaHBox;
			box->Add((AreaHBox*)delegate);
		}
		else if (name == DUI_CTR_VBOX) {
			delegate = new AreaVBox;
			box->Add((AreaVBox*)delegate);
		}
		break;
	case 7:
		if (name == DUI_CTR_CONTROL) {
			delegate = new AreaControl;
			box->Add((AreaControl*)delegate);
		}
		break;
	default:
		delegate = new AreaBox;
		box->Add((AreaBox*)delegate);
		break;
	}
	std::wstring controlName = GetName(name);
	delegate->SetControlName(controlName);
	AreaBox* tempBox = dynamic_cast<AreaBox*>(box);
	if (tempBox) {
		tempBox->SetDropUIMargin(pt, delegate);
		return;
	}
	AreaHBox* tempHBox = dynamic_cast<AreaHBox*>(box);
	if (tempHBox) {
		tempHBox->SetDropUIMargin(pt, delegate);
		return;
	}
	AreaVBox* tempVBox = dynamic_cast<AreaVBox*>(box);
	if (tempVBox) {
		tempVBox->SetDropUIMargin(pt, delegate);
		return;
	}
}

AreaControlDelegate* ControlHelper::DropControl(ui::Box* box, const std::wstring& name)
{
	AreaControlDelegate* delegate = NULL;
	SIZE_T cchLen = name.length();
	switch (cchLen) {
	case 3:
		if (name == DUI_CTR_BOX) {
			delegate = new AreaBox;
			box->Add((AreaBox*)delegate);
		}
		break;
	case 4:
		if (name == DUI_CTR_HBOX) {
			delegate = new AreaHBox;
			box->Add((AreaHBox*)delegate);
		}
		else if (name == DUI_CTR_VBOX) {
			delegate = new AreaVBox;
			box->Add((AreaVBox*)delegate);
		}
		break;
	case 7:
		if (name == DUI_CTR_CONTROL) {
			delegate = new AreaControl;
			box->Add((AreaControl*)delegate);
		}
		break;
	default:
		delegate = new AreaBox;
		box->Add((AreaBox*)delegate);
		break;
	}
	return delegate;
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

std::wstring ControlHelper::GetName(const std::wstring& name)
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
	if (CheckDupliName(name, _container_box)) {
		return GetName(name);
	}
	return controlName;
}