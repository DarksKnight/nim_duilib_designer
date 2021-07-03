#pragma once
#include "AreaControlDelegate.h"

class AreaLabelDelegate : public AreaControlDelegate
{
public:
	AreaLabelDelegate(ui::Control* control);
protected:
	void OnParseElement(tinyxml2::XMLElement* element) override;
	void OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element) override;
protected:
	std::wstring GetControlName() {
		return DUI_CTR_LABEL;
	}
};