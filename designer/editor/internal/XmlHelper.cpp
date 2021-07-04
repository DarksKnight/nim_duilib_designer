﻿#include "../stdafx.h"
#include "XmlHelper.h"
#include "../controls/AreaControl.h"
#include "../controls/AreaBox.h"
#include "../controls/AreaHBox.h"
#include "../controls/AreaWindow.h"
#include "../controls/AreaVBox.h"
#include "../controls/AreaLabel.h"
#include "ControlHelper.h"

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

bool XmlHelper::ParseXml(ui::Box* box, const std::wstring& path)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError result = doc.LoadFile(nbase::UTF16ToUTF8(path).c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return false;
	}
	box->RemoveAll();
	AreaWindow* areaWindow = new AreaWindow;
	box->Add((AreaWindow*)areaWindow);
	areaWindow->ParseElement(doc.RootElement());
	std::string sizeAttr = doc.RootElement()->Attribute("size");
	std::vector<std::string> sizeVector = ConvertVector(nim_comp::StringHelper::Split(sizeAttr, ","));
	int width = 0;
	nbase::StringToInt(sizeVector[0], &width);
	areaWindow->SetFixedWidth(width);
	int height = 0;
	nbase::StringToInt(sizeVector[1], &height);
	areaWindow->SetFixedHeight(height);
	ParseElement(doc.RootElement(), areaWindow);
	return true;
}

bool XmlHelper::ParseXmlPreview(ui::Box* box, const std::wstring& path)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError result = doc.LoadFile(nbase::UTF16ToUTF8(path).c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return false;
	}
	box->RemoveAll();
	ParseElement(doc.RootElement(), box);
	return true;
}

tinyxml2::XMLElement* XmlHelper::GetElement(tinyxml2::XMLDocument* doc, ui::Control* control)
{
	tinyxml2::XMLElement* element = NULL;
	if (!control) {
		return element;
	}
	ui::Box* box = dynamic_cast<ui::Box*>(control);
	if (box) {
		AreaBoxDelegate* areaBox = dynamic_cast<AreaBoxDelegate*>(control);
		AreaHBoxDelegate* areaHBox = dynamic_cast<AreaHBoxDelegate*>(control);
		AreaVBoxDelegate* areaVBox = dynamic_cast<AreaVBoxDelegate*>(control);
		if (areaHBox) {
			element = areaHBox->GetElement(doc);
		}
		else if (areaVBox) {
			element = areaVBox->GetElement(doc);
		}
		else {
			element = areaBox->GetElement(doc);
		}
		for (int i = 0; i < box->GetCount(); i++) {
			tinyxml2::XMLElement* subEl = GetElement(doc, box->GetItemAt(i));
			if (!subEl) {
				continue;
			}
			element->InsertEndChild(subEl);
		}
	}
	else {
		AreaControlDelegate* areaControl = dynamic_cast<AreaControlDelegate*>(control);
		if (areaControl) {
			element = areaControl->GetElement(doc);
			return element;
		}
		AreaLabelDelegate* areaLabel = dynamic_cast<AreaLabelDelegate*>(control);
		if (areaLabel) {
			element = areaLabel->GetElement(doc);
			return element;
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
		std::wstring value = nbase::UTF8ToUTF16(currentElement->Value());
		AreaControlDelegate* areaControl = ControlHelper::GetInstance()->DropControl(rootBox, value);
		areaControl->ParseElement(currentElement);
		ui::Box* containerBox = dynamic_cast<ui::Box*>(areaControl);
		if (!currentElement->NoChildren() && containerBox) {
			ParseElement(currentElement, containerBox);
		}
	}
}