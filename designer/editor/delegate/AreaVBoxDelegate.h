#pragma once
#include "AreaBoxDelegate.h"

class AreaVBoxDelegate : public AreaBoxDelegate
{
public:
	AreaVBoxDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return L"VBox";
	}
};