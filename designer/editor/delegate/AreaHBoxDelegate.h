#pragma once
#include "AreaBoxDelegate.h"

class AreaHBoxDelegate : public AreaBoxDelegate
{
public:
	AreaHBoxDelegate(ui::Control* control);
public:
	void SetDropIMargin(POINT pt, AreaControlDelegate* target) override;
protected:
	std::wstring GetControlName() {
		return L"HBox";
	}
};