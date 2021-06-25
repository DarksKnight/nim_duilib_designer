#include "../stdafx.h"
#include "XmlHelper.h"

XmlHelper::XmlHelper()
{
}


XmlHelper::~XmlHelper()
{
}

bool XmlHelper::ConvertXml(EditorArea* area, const std::wstring& path, bool window)
{
	const std::string declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	tinyxml2::XMLDocument doc;
	doc.Parse(declaration.c_str());
	tinyxml2::XMLElement* rootWindow = doc.NewElement("Window");
	doc.InsertEndChild(rootWindow);
	if (window) {
		rootWindow->SetAttribute("size", nbase::StringPrintf("%d,%d", area->GetWindowInfo().width, area->GetWindowInfo().height).c_str());
	}
	tinyxml2::XMLElement* rootBox = doc.NewElement("Box");
	rootWindow->InsertEndChild(rootBox);
	if (((ui::Box*)area->GetItemAt(0))->GetCount() > 0) {
		tinyxml2::XMLElement* element = GetElement(&doc, ((ui::Box*)area->GetItemAt(0))->GetItemAt(0));
		rootBox->InsertEndChild(element);
	}
	tinyxml2::XMLError result = doc.SaveFile(nbase::UTF16ToUTF8(path).c_str());
	if (result == tinyxml2::XML_SUCCESS) {
		return true;
	}
	else {
		return false;
	}
}

tinyxml2::XMLElement* XmlHelper::GetElement(tinyxml2::XMLDocument* doc, ui::Control* control)
{
	tinyxml2::XMLElement* element = NULL;
	ui::Box* box = dynamic_cast<ui::Box*>(control);
	if (box) {
		element = doc->NewElement("Box");
		if (!CheckWidthAndHeight(box->GetFixedWidth())) {
			element->SetAttribute("width", box->GetFixedWidth());
		}
		if (!CheckWidthAndHeight(box->GetFixedHeight())) {
			element->SetAttribute("height", box->GetFixedHeight());
		}
		if (!CheckRectEmpty(box->GetMargin())) {
			element->SetAttribute("margin", nbase::StringPrintf("%d,%d,%d,%d", box->GetMargin().left, box->GetMargin().top, box->GetMargin().right, box->GetMargin().bottom).c_str());
		}
		for (int i = 0; i < box->GetCount(); i++) {
			tinyxml2::XMLElement* subEl = GetElement(doc, box->GetItemAt(i));
			element->InsertEndChild(subEl);
		}
	}
	else {
		element = doc->NewElement("aaaa");
	}
	return element;
}