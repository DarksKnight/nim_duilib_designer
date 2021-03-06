#include "../stdafx.h"
#include "ControlHelper.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaWindow.h"
#include "../controls/AreaHBox.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaVBox.h"
#include "../controls/AreaLabel.h"
#include "../controls/AreaRichEdit.h"
#include "../controls/AreaButton.h"
#include "../controls/AreaCheckBox.h"

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
	_datas.push_back(ControlData(DUI_CTR_BOX, L"无约束容器"));
	_datas.push_back(ControlData(DUI_CTR_HBOX, L"横向容器"));
	_datas.push_back(ControlData(DUI_CTR_VBOX, L"纵向容器"));
	_datas.push_back(ControlData(DUI_CTR_CONTROL, L"基础控件"));
	_datas.push_back(ControlData(DUI_CTR_LABEL, L"文本控件"));
	_datas.push_back(ControlData(DUI_CTR_RICHEDIT, L"输入控件"));
	_datas.push_back(ControlData(DUI_CTR_BUTTON, L"按钮"));
	_datas.push_back(ControlData(DUI_CTR_CHECKBOX, L"复选框"));
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
	case 6:
		if (name == DUI_CTR_BUTTON) {
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
	case 8:
		if (name == DUI_CTR_RICHEDIT) {
			size.cx = 80;
			size.cy = 30;
		}
		else if (name == DUI_CTR_CHECKBOX) {
			size.cx = 80;
			size.cy = 30;
		}
		break;
	default:
		break;
	}
	return size;
}

AreaControlDelegate* ControlHelper::DropControl(ui::Box* box, POINT pt, const std::wstring& name)
{
	AreaControlDelegate* delegate = NULL;
	SIZE_T cchLen = name.length();
	switch (cchLen) {
	case 3:
		if (name == DUI_CTR_BOX) {
			delegate = new AreaBox;
			delegate->SetControlData(_datas[0]);
			box->Add((AreaBox*)delegate);
		}
		break;
	case 4:
		if (name == DUI_CTR_HBOX) {
			delegate = new AreaHBox;
			delegate->SetControlData(_datas[1]);
			box->Add((AreaHBox*)delegate);
		}
		else if (name == DUI_CTR_VBOX) {
			delegate = new AreaVBox;
			delegate->SetControlData(_datas[2]);
			box->Add((AreaVBox*)delegate);
		}
		break;
	case 5:
		if (name == DUI_CTR_LABEL) {
			delegate = new AreaLabel;
			delegate->SetControlData(_datas[4]);
			box->Add((AreaLabel*)delegate);
		}
		break;
	case 6:
		if (name == DUI_CTR_BUTTON) {
			delegate = new AreaButton;
			delegate->SetControlData(_datas[6]);
			box->Add((AreaButton*)delegate);
		}
		break;
	case 7:
		if (name == DUI_CTR_CONTROL) {
			delegate = new AreaControl;
			delegate->SetControlData(_datas[3]);
			box->Add((AreaControl*)delegate);
		}
		break;
	case 8:
		if (name == DUI_CTR_RICHEDIT) {
			delegate = new AreaRichEdit;
			delegate->SetControlData(_datas[5]);
			box->Add((AreaRichEdit*)delegate);
		}
		else if (name == DUI_CTR_CHECKBOX) {
			delegate = new AreaCheckBox;
			delegate->SetControlData(_datas[7]);
			box->Add((AreaCheckBox*)delegate);
		}
		break;
	default:
		break;
	}
	std::wstring controlName = GetName(name);
	delegate->SetControlName(controlName);
	AreaBox* tempBox = dynamic_cast<AreaBox*>(box);
	AreaHBox* tempHBox = dynamic_cast<AreaHBox*>(box);
	AreaVBox* tempVBox = dynamic_cast<AreaVBox*>(box);
	if (tempBox) tempBox->SetDropUIMargin(pt, delegate);
	else if (tempHBox) tempHBox->SetDropUIMargin(pt, delegate);
	else tempVBox->SetDropUIMargin(pt, delegate);
	return delegate;
}

AreaControlDelegate* ControlHelper::DropControl(ui::Box* box, const std::wstring& name)
{
	AreaControlDelegate* delegate = NULL;
	SIZE_T cchLen = name.length();
	switch (cchLen) {
	case 3:
		if (name == DUI_CTR_BOX) {
			delegate = new AreaBox;
			delegate->SetControlData(_datas[0]);
			box->Add((AreaBox*)delegate);
		}
		break;
	case 4:
		if (name == DUI_CTR_HBOX) {
			delegate = new AreaHBox;
			delegate->SetControlData(_datas[1]);
			box->Add((AreaHBox*)delegate);
		}
		else if (name == DUI_CTR_VBOX) {
			delegate = new AreaVBox;
			delegate->SetControlData(_datas[2]);
			box->Add((AreaVBox*)delegate);
		}
		break;
	case 5:
		if (name == DUI_CTR_LABEL) {
			delegate = new AreaLabel;
			delegate->SetControlData(_datas[4]);
			box->Add((AreaLabel*)delegate);
		}
		break;
	case 6:
		if (name == DUI_CTR_BUTTON) {
			delegate = new AreaButton;
			delegate->SetControlData(_datas[6]);
			box->Add((AreaButton*)delegate);
		}
		break;
	case 7:
		if (name == DUI_CTR_CONTROL) {
			delegate = new AreaControl;
			delegate->SetControlData(_datas[3]);
			box->Add((AreaControl*)delegate);
		}
		break;
	case 8:
		if (name == DUI_CTR_RICHEDIT) {
			delegate = new AreaRichEdit;
			delegate->SetControlData(_datas[5]);
			box->Add((AreaRichEdit*)delegate);
		}
		else if (name == DUI_CTR_CHECKBOX) {
			delegate = new AreaCheckBox;
			delegate->SetControlData(_datas[7]);
			box->Add((AreaCheckBox*)delegate);
		}
		break;
	default:
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
	AreaRichEditDelegate* tempRichEdit = dynamic_cast<AreaRichEditDelegate*>(control);
	if (tempRichEdit) {
		tempRichEdit->Remove();
		return;
	}
	AreaButtonDelegate* tempButton = dynamic_cast<AreaButtonDelegate*>(control);
	if (tempButton) {
		tempButton->Remove();
		return;
	}
	AreaCheckBoxDelegate* tempCheckBox = dynamic_cast<AreaCheckBoxDelegate*>(control);
	if (tempCheckBox) {
		tempCheckBox->Remove();
		return;
	}
	AreaLabelDelegate* tempLabel = dynamic_cast<AreaLabelDelegate*>(control);
	if (tempLabel) {
		tempLabel->Remove();
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
		if (((DelegateData*)control->GetUserDataBase())->GetName() == name) {
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
	SIZE_T cchLen = name.length();
	switch (cchLen) {
	case 3:
		if (name == DUI_CTR_BOX) controlName = name + nbase::IntToString16(_box_index++);
		break;
	case 4:
		if (name == DUI_CTR_HBOX) controlName = name + nbase::IntToString16(_hbox_index++);
		else if (name == DUI_CTR_VBOX) controlName = name + nbase::IntToString16(_vbox_index++);
		break;
	case 5:
		if (name == DUI_CTR_LABEL) controlName = name + nbase::IntToString16(_label_index++);
		break;
	case 6:
		if (name == DUI_CTR_BUTTON) controlName = name + nbase::IntToString16(_button_index++);
		break;
	case 7:
		if (name == DUI_CTR_CONTROL) controlName = name + nbase::IntToString16(_control_index++);
		break;
	case 8:
		if (name == DUI_CTR_RICHEDIT) controlName = name + nbase::IntToString16(_richedit_index++);
		else if (name == DUI_CTR_CHECKBOX) controlName = name + nbase::IntToString16(_checkbox_index++);
		break;
	default:
		break;
	}
	if (CheckDupliName(controlName, _container_box)) {
		return GetName(name);
	}
	return controlName;
}