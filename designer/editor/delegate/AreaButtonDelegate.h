#pragma once
#include "AreaControlDelegate.h"

class AreaButtonDelegate : public AreaControlDelegate
{
public:
	AreaButtonDelegate(ui::Control* control);
protected:
	void OnParseElement(tinyxml2::XMLElement* element) override;
protected:
	std::wstring GetControlName() {
		return DUI_CTR_BUTTON;
	}
};