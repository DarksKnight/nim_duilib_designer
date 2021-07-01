#include "../stdafx.h"
#include "AreaLabelDelegate.h"

AreaLabelDelegate::AreaLabelDelegate(ui::Control* control):AreaControlDelegate(control)
{
}

void AreaLabelDelegate::OnParseElement(tinyxml2::XMLElement* element)
{
	std::wstring text = L"";
	const tinyxml2::XMLAttribute* attr = NULL;
	if (attr = element->FindAttribute("text")) {
		text = nbase::UTF8ToUTF16(attr->Value());
	}
	((ui::Label*)_control)->SetText(text);
}

void AreaLabelDelegate::OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element)
{
	element->SetAttribute("text", nbase::UTF16ToUTF8(((ui::Label*)_control)->GetText()).c_str());
}