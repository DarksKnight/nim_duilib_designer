#include "../stdafx.h"
#include "AreaButtonDelegate.h"

AreaButtonDelegate::AreaButtonDelegate(ui::Control* control):AreaControlDelegate(control)
{
}

void AreaButtonDelegate::OnParseElement(tinyxml2::XMLElement* element)
{
	ui::Button* button = (ui::Button*)_control;
	const tinyxml2::XMLAttribute* attr = NULL;
	if (attr = element->FindAttribute("text")) {
		button->SetText(nbase::UTF8ToUTF16(attr->Value()));
	}
	else {
		button->SetText(L"");
	}
}