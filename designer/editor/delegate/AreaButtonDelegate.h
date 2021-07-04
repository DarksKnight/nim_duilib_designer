#pragma once
#include "AreaLabelDelegate.h"

class AreaButtonDelegate : public AreaLabelDelegate
{
public:
	AreaButtonDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_BUTTON;
	}
};