#pragma once
#include "AreaLabelDelegate.h"

class AreaCheckBoxDelegate : public AreaLabelDelegate
{
public:
	AreaCheckBoxDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_CHECKBOX;
	}
};