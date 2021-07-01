#include "../stdafx.h"
#include "AreaRichEditDelegate.h"

AreaRichEditDelegate::AreaRichEditDelegate(ui::Control* control):AreaBoxDelegate(control)
{
}


AreaRichEditDelegate::~AreaRichEditDelegate()
{
}

void AreaRichEditDelegate::OnParseElement(tinyxml2::XMLElement* element)
{
	std::wstring text = L"";
	const tinyxml2::XMLAttribute* attr = NULL;
	if (attr = element->FindAttribute("text")) {
		text = nbase::UTF8ToUTF16(attr->Value());
	}
	((ui::RichEdit*)_control)->SetText(text);
}

void AreaRichEditDelegate::OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element)
{
	element->SetAttribute("text", nbase::UTF16ToUTF8(((ui::RichEdit*)_control)->GetText()).c_str());
}