#pragma once
#include "AreaLabelDelegate.h"

class AreaRichEditDelegate : public AreaLabelDelegate
{
public:
	AreaRichEditDelegate(ui::Control* control);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_RICHEDIT;
	}
};