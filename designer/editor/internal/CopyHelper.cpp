#include "../stdafx.h"
#include "CopyHelper.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaHBox.h"
#include "ControlHelper.h"

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
}

void CopyHelper::Paste()
{
	if (!_copy_ctrl_parent || !_copy_ctrl) {
		return;
	}
	std::wstring name = ControlHelper::GetInstance()->GetName(_copy_ctrl->GetControlName());
	((AreaBox*)_copy_ctrl)->SetName(name);
	_copy_ctrl->SetUIMargin(ui::UiRect());
	std::wstring ctrlName = _copy_ctrl->GetControlName();
	SIZE_T cchLen = ctrlName.length();
	switch (cchLen) {
	case 3:
		if (ctrlName == DUI_CTR_BOX) {
			_copy_ctrl_parent->Add(new AreaBox(*(AreaBox*)_copy_ctrl));
		}
		break;
	case 4:
		if (ctrlName == DUI_CTR_HBOX) {
		}
		else if (ctrlName == DUI_CTR_VBOX) {
		}
		break;
	case 7:
		if (ctrlName == DUI_CTR_CONTROL) {
		}
		break;
	default:
		break;
	}
}