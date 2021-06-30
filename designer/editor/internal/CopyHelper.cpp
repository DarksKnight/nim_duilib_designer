#include "../stdafx.h"
#include "CopyHelper.h"
#include "ControlHelper.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaHBox.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaVBox.h"
#include "../controls/AreaLabel.h"
#include "../controls/AreaRichEdit.h"

CopyHelper::CopyHelper()
{
}


CopyHelper::~CopyHelper()
{
}

void CopyHelper::Copy(ui::Control* ctrl)
{
	if (!ctrl) {
		return;
	}
	_copy_ctrl_parent = ctrl->GetParent();
	AreaBox* box = dynamic_cast<AreaBox*>(ctrl);
	if (box) {
		_copy_ctrl = new AreaBox(*box);
		return;
	}
	AreaHBox* hBox = dynamic_cast<AreaHBox*>(ctrl);
	if (hBox) {
		_copy_ctrl = new AreaHBox(*hBox);
		return;
	}
	AreaControl* control = dynamic_cast<AreaControl*>(ctrl);
	if (control) {
		_copy_ctrl = new AreaControl(*control);
		return;
	}
	AreaVBox* vBox = dynamic_cast<AreaVBox*>(ctrl);
	if (vBox) {
		_copy_ctrl = new AreaVBox(*vBox);
		return;
	}
	AreaLabel* label = dynamic_cast<AreaLabel*>(ctrl);
	if (label) {
		_copy_ctrl = new AreaLabel(*label);
		return;
	}
	AreaRichEdit* richEdit = dynamic_cast<AreaRichEdit*>(ctrl);
	if (richEdit) {
		_copy_ctrl = new AreaRichEdit(*richEdit);
		return;
	}
}

void CopyHelper::Paste()
{
	if (!_copy_ctrl_parent || !_copy_ctrl) {
		return;
	}
	std::wstring name = ControlHelper::GetInstance()->GetName(_copy_ctrl->GetControlName());
	_copy_ctrl->SetUIMargin(ui::UiRect());
	std::wstring ctrlName = _copy_ctrl->GetControlName();
	SIZE_T cchLen = ctrlName.length();
	switch (cchLen) {
	case 3:
		if (ctrlName == DUI_CTR_BOX) {
			((AreaBox*)_copy_ctrl)->SetName(name);
			_copy_ctrl_parent->Add(new AreaBox(*(AreaBox*)_copy_ctrl));
		}
		break;
	case 4:
		if (ctrlName == DUI_CTR_HBOX) {
			((AreaHBox*)_copy_ctrl)->SetName(name);
			_copy_ctrl_parent->Add(new AreaHBox(*(AreaHBox*)_copy_ctrl));
		}
		else if (ctrlName == DUI_CTR_VBOX) {
			((AreaVBox*)_copy_ctrl)->SetName(name);
			_copy_ctrl_parent->Add(new AreaVBox(*(AreaVBox*)_copy_ctrl));
		}
		break;
	case 5:
		if (ctrlName == DUI_CTR_LABEL) {
			((AreaLabel*)_copy_ctrl)->SetName(name);
			_copy_ctrl_parent->Add(new AreaLabel(*(AreaLabel*)_copy_ctrl));
		}
		break;
	case 7:
		if (ctrlName == DUI_CTR_CONTROL) {
			((AreaControl*)_copy_ctrl)->SetName(name);
			_copy_ctrl_parent->Add(new AreaControl(*(AreaControl*)_copy_ctrl));
		}
		break;
	case 8:
		if (ctrlName == DUI_CTR_RICHEDIT) {
			((AreaRichEdit*)_copy_ctrl)->SetName(name);
			_copy_ctrl_parent->Add(new AreaRichEdit(*(AreaRichEdit*)_copy_ctrl));
		}
		break;
	default:
		break;
	}
}