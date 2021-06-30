#pragma once
#include "AreaBoxDelegate.h"

class AreaRichEditDelegate : public AreaBoxDelegate
{
public:
	AreaRichEditDelegate(ui::Control* control);
	~AreaRichEditDelegate();
protected:
	std::wstring GetControlName() {
		return DUI_CTR_RICHEDIT;
	}
};