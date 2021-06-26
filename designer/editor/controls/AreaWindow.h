#pragma once
#include "AreaBox.h"

class AreaWindow : public AreaBox
{
public:
	AreaWindow();
	~AreaWindow();
protected:
	void OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element) {
		element->DeleteAttribute("width");
		element->DeleteAttribute("height");
	}
};