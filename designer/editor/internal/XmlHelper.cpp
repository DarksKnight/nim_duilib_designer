#include "../stdafx.h"
#include "XmlHelper.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaWindow.h"

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
		rootWindow->SetAttribute("size", nbase::StringPrintf("%d,%d", area->GetItemAt(0)->GetFixedWidth(), area->GetItemAt(0)->GetFixedHeight()).c_str());
	}
	if (((AreaBox*)area->GetItemAt(0))->GetCount() > 0) {
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
	ParseElement(rootElement, ((ui::Box*)area->GetItemAt(0)));
}

tinyxml2::XMLElement* XmlHelper::GetElement(tinyxml2::XMLDocument* doc, ui::Control* control)
{
	tinyxml2::XMLElement* element = NULL;
	if (!control) {
		return element;
	}
	AreaBox* areaBox = dynamic_cast<AreaBox*>(control);
	if (areaBox) {
		AreaWindow* areaWindow = dynamic_cast<AreaWindow*>(control);
		if (areaWindow) {
			element = areaWindow->GetElement(doc);
		}
		else {
			element = areaBox->GetElement(doc);
		}
		for (int i = 0; i < areaBox->GetCount(); i++) {
			tinyxml2::XMLElement* subEl = GetElement(doc, areaBox->GetItemAt(i));
			element->InsertEndChild(subEl);
		}
	}
	return element;
}

void XmlHelper::ParseElement(tinyxml2::XMLElement* element, ui::Box* rootBox)
{
	if (!rootBox) {
		return;
	}
	for (tinyxml2::XMLElement* currentElement = element->FirstChildElement(); currentElement; currentElement = currentElement->NextSiblingElement()) {
		AreaControl* areaControl = NULL;
		std::wstring value = nbase::UTF8ToUTF16(currentElement->Value());
		if (value == L"Box") {
			areaControl = new AreaBox;
			rootBox->Add((AreaBox*)areaControl);
		}
		areaControl->ParseElement(currentElement);
		ui::Box* containerBox = dynamic_cast<ui::Box*>(areaControl);
		if (!currentElement->NoChildren() && containerBox) {
			ParseElement(currentElement, containerBox);
		}
	}
}