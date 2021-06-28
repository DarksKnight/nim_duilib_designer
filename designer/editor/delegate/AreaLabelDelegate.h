#pragma once
#include "AreaControlDelegate.h"

class AreaLabelDelegate : public AreaControlDelegate
{
public:
	AreaLabelDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_LABEL;
	}
};