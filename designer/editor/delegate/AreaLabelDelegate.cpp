#include "../stdafx.h"
#include "AreaLabelDelegate.h"

AreaLabelDelegate::AreaLabelDelegate(ui::Control* control):AreaControlDelegate(control)
{
}

void AreaLabelDelegate::OnParseElement(tinyxml2::XMLElement* element)
{
	DelegateData* data = GetDelegateData();
	ui::Label* label = (ui::Label*)_control;
	const tinyxml2::XMLAttribute* attr = NULL;
	if (attr = element->FindAttribute("text")) {
		label->SetText(nbase::UTF8ToUTF16(attr->Value()));
		data->SetText(nbase::UTF8ToUTF16(attr->Value()));
	}
	else {
		label->SetText(L"");
	}
	if (attr = element->FindAttribute("font")) {
		label->SetFont(nbase::UTF8ToUTF16(attr->Value()));
		data->SetFont(nbase::UTF8ToUTF16(attr->Value()));
	}
}

void AreaLabelDelegate::OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element)
{
	DelegateData* data = GetDelegateData();
	if (!data->GetText().empty()) {
		element->SetAttribute("text", nbase::UTF16ToUTF8(data->GetText()).c_str());
	}
	if (!data->GetFont().empty()) {
		element->SetAttribute("font", nbase::UTF16ToUTF8(data->GetFont()).c_str());
	}
}