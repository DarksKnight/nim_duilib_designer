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

std::vector<std::wstring> ControlHelper::GetControlList()
{
	if (!_datas.empty()) {
		return _datas;
	}
	_datas.push_back(L"Box");
	_datas.push_back(L"HBox");
	_datas.push_back(L"VBox");
	_datas.push_back(L"Control");
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

AreaControlDelegate* ControlHelper::AddControl(ui::Box* box, const std::wstring& name)
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