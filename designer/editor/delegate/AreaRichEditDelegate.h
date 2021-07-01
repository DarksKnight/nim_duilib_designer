#pragma once
#include "AreaBoxDelegate.h"

class AreaRichEditDelegate : public AreaBoxDelegate
{
public:
	AreaRichEditDelegate(ui::Control* control);
	~AreaRichEditDelegate();
protected:
	void OnParseElement(tinyxml2::XMLElement* element);
	void OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element);
protected:
	std::wstring GetControlName() {
		return DUI_CTR_RICHEDIT;
	}
};