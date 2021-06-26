#pragma once
#include "AreaControl.h"

class AreaBox : public ui::Box, public AreaControl
{
public:
	AreaBox();
	~AreaBox();
protected:
	std::wstring GetControlName() {
		return L"Box";
	}
};

