#pragma once
#include "AreaControlDelegate.h"

class AreaLabelDelegate : public AreaControlDelegate
{
public:
	AreaLabelDelegate(ui::Control* control);
protected:
	void OnParseElement(tinyxml2::XMLElement* element);
	void OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_LABEL;
	}
};