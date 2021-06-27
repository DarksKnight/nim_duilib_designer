#pragma once
#include "../delegate/AreaControlDelegate.h"

class AreaControl : public ui::Control, public AreaControlDelegate
{
public:
	AreaControl();
	~AreaControl();
protected:
	std::wstring GetControlName() {
		return L"Control";
	}
};