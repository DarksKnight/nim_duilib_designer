#include "../stdafx.h"
#include "XmlHelper.h"
#include <iterator>
#include <algorithm>

XmlHelper::XmlHelper()
{
}


XmlHelper::~XmlHelper()
{
}

bool XmlHelper::ConvertXml(EditorArea* area, const std::wstring& path, bool window)
{
	tinyxml2::XMLDocument doc;
	doc.Parse(_xml_header.c_str());
	tinyxml2::XMLElement* rootWindow = doc.NewElement("Window");
	doc.InsertEndChild(rootWindow);
	if (window) {
		rootWindow->SetAttribute("size", nbase::StringPrintf("%d,%d", area->GetWindowInfo().width, area->GetWindowInfo().height).c_str());
	}
	if (((ui::Box*)area->GetItemAt(0))->GetCount() > 0) {
		tinyxml2::XMLElement* element = GetElement(&doc, area->GetItemAt(0));
		rootWindow->InsertEndChild(element);
	}
	tinyxml2::XMLError result = doc.SaveFile(nbase::UTF16ToUTF8(path).c_str());
	if (result == tinyxml2::XML_SUCCESS) {
		return true;
	}
	else {
		return false;
	}
}

bool XmlHelper::ParseXml(EditorArea* area, const std::wstring& path, bool window)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError result = doc.LoadFile(nbase::UTF16ToUTF8(path).c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return false;
	}
	tinyxml2::XMLElement* rootElement = doc.RootElement();
	if (window) {
		std::string sizeAttr = rootElement->Attribute("size");
		std::vector<std::string> sizeVector = ConvertVector(nim_comp::StringHelper::Split(sizeAttr, ","));
		int width = 0;
		nbase::StringToInt(sizeVector[0], &width);
		area->GetItemAt(0)->SetFixedWidth(width);
		int height = 0;
		nbase::StringToInt(sizeVector[1], &height);
		area->GetItemAt(0)->SetFixedHeight(height);
	}
	ParseElement(area, rootElement, ((ui::Box*)area->GetItemAt(0)));
}

tinyxml2::XMLElement* XmlHelper::GetElement(tinyxml2::XMLDocument* doc, ui::Control* control)
{
	tinyxml2::XMLElement* element = NULL;
	if (!control) {
		return element;
	}
	ui::Box* box = dynamic_cast<ui::Box*>(control);
	if (box) {
		element = doc->NewElement("Box");
		if (box->GetName() != L"sampleWindow") {
			SetUniversalAttr(element, control);
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

void XmlHelper::ParseElement(EditorArea* area, tinyxml2::XMLElement* element, ui::Box* rootBox)
{
	if (!rootBox) {
		return;
	}
	for (tinyxml2::XMLElement* currenteleElement = element->FirstChildElement(); currenteleElement; currenteleElement = currenteleElement->NextSiblingElement()) {
		ControlData* data = SetUniversalProperty(currenteleElement);
		data->parentBox = rootBox;
		ui::Box* containerBox = area->DropControl(data);
		if (!currenteleElement->NoChildren()) {
			ParseElement(area, currenteleElement, containerBox);
		}
	}
}

void XmlHelper::SetUniversalAttr(tinyxml2::XMLElement* element, ui::Control* control)
{
	if (!CheckWidthAndHeight(control->GetFixedWidth())) {
		element->SetAttribute("width", control->GetFixedWidth());
	}
	if (!CheckWidthAndHeight(control->GetFixedHeight())) {
		element->SetAttribute("height", control->GetFixedHeight());
	}
	if (!CheckRectEmpty(control->GetMargin())) {
		element->SetAttribute("margin", nbase::StringPrintf("%d,%d,%d,%d", control->GetMargin().left, control->GetMargin().top, control->GetMargin().right, control->GetMargin().bottom).c_str());
	}
}

ControlData* XmlHelper::SetUniversalProperty(tinyxml2::XMLElement* element)
{
	std::wstring value = nbase::UTF8ToUTF16(element->Value());
	std::string widthAttr = "stretch";
	std::string heightAttr = "stretch";
	std::string marginAttr = "";
	if (element->BoolAttribute("width")) {
		widthAttr = element->Attribute("width");
	}
	if (element->BoolAttribute("height")) {
		heightAttr = element->Attribute("height");
	}
	if (element->BoolAttribute("margin")) {
		marginAttr = element->Attribute("margin");
	}
	int width = 0;
	int height = 0;
	if (widthAttr == "auto") {
		width = DUI_LENGTH_AUTO;
	}
	else if (widthAttr == "stretch") {
		width = DUI_LENGTH_STRETCH;
	}
	else {
		nbase::StringToInt(widthAttr, &width);
	}
	if (heightAttr == "auto") {
		height = DUI_LENGTH_AUTO;
	}
	else if (heightAttr == "stretch") {
		height = DUI_LENGTH_STRETCH;
	}
	else {
		nbase::StringToInt(heightAttr, &height);
	}
	ControlData* data = new ControlData(value, width, height, true);
	if (!marginAttr.empty()) {
		std::vector<std::string> marginVector = ConvertVector(nim_comp::StringHelper::Split(marginAttr, ","));
		int left, top, right, bottom = 0;
		nbase::StringToInt(marginVector[0], &left);
		nbase::StringToInt(marginVector[1], &top);
		nbase::StringToInt(marginVector[2], &right);
		nbase::StringToInt(marginVector[3], &bottom);
		ui::UiRect marginRect(left, top, right, bottom);
		data->margin = marginRect;
	}
	return data;
}