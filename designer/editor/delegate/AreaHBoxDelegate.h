#pragma once
#include "AreaBoxDelegate.h"

class AreaHBoxDelegate : public AreaBoxDelegate
{
public:
	AreaHBoxDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return L"HBox";
	}
};