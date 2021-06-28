﻿#pragma once
#include "AreaControlDelegate.h"

class AreaBoxDelegate : public AreaControlDelegate
{
public:
	AreaBoxDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_BOX;
	}
};