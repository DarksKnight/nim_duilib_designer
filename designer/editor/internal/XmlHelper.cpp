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
	ParseElement(rootElement, ((ui::Box*)area->GetItemAt(0)));
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

void XmlHelper::ParseElement(tinyxml2::XMLElement* element, ui::Box* rootBox)
{
	if (!rootBox) {
		return;
	}
	for (tinyxml2::XMLElement* currenteleElement = element->FirstChildElement(); currenteleElement; currenteleElement = currenteleElement->NextSiblingElement()) {
		std::wstring value = nbase::UTF8ToUTF16(currenteleElement->Value());
		std::string widthAttr = "stretch";
		std::string heightAttr = "stretch";
		std::string marginAttr = "";
		if (currenteleElement->BoolAttribute("width")) {
			widthAttr = currenteleElement->Attribute("width");
		}
		if (currenteleElement->BoolAttribute("height")) {
			heightAttr = currenteleElement->Attribute("height");
		}
		if (currenteleElement->BoolAttribute("margin")) {
			marginAttr = currenteleElement->Attribute("margin");
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

		ui::Box* box = NULL;
		if (value == L"Box") {
			box = new ui::Box;
			box->SetBorderSize(1);
			box->SetBorderColor(L"blue");
			box->SetFixedWidth(width);
			box->SetFixedHeight(height);
			if (!marginAttr.empty()) {
				std::vector<std::string> marginVector = ConvertVector(nim_comp::StringHelper::Split(marginAttr, ","));
				int left, top, right, bottom = 0;
				nbase::StringToInt(marginVector[0], &left);
				nbase::StringToInt(marginVector[1], &top);
				nbase::StringToInt(marginVector[2], &right);
				nbase::StringToInt(marginVector[3], &bottom);
				ui::UiRect marginRect(left, top, right, bottom);
				box->SetMargin(marginRect);
			}
			rootBox->Add(box);
		}
		if (!currenteleElement->NoChildren()) {
			ParseElement(currenteleElement, box);
		}
	}
}