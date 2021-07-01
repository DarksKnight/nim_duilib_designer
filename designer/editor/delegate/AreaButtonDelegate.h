#pragma once
#include "AreaControlDelegate.h"

class AreaButtonDelegate : public AreaControlDelegate
{
public:
	AreaButtonDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_BUTTON;
	}
};