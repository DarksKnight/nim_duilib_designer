#pragma once
#include "AreaControlDelegate.h"

class AreaCheckBoxDelegate : public AreaControlDelegate
{
public:
	AreaCheckBoxDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_CHECKBOX;
	}
};