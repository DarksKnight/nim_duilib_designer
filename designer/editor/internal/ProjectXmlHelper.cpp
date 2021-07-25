#include "../stdafx.h"
#include "ProjectXmlHelper.h"

ProjectXmlHelper::ProjectXmlHelper()
{
	_path = GlobalData::APPDATA_ROMAING + L"project.json";
}


ProjectXmlHelper::~ProjectXmlHelper()
{
}

bool ProjectXmlHelper::CreateNd(const std::wstring& path)
{
	_doc.Parse(XML_HEADER);
	tinyxml2::XMLElement* projectElement = _doc.NewElement("Window");
	_doc.InsertEndChild(projectElement);
	std::wstring folder = L"";
	nbase::FilePathApartDirectory(path, folder);
	_lang_element = _doc.NewElement("Language");
	projectElement->InsertEndChild(_lang_element);
	_resource_element = _doc.NewElement("Resource");
	projectElement->InsertEndChild(_resource_element);
	_layout_element = _doc.NewElement("Layout");
	projectElement->InsertEndChild(_layout_element);
	ScanFolder(folder);
	tinyxml2::XMLError result = _doc.SaveFile(nbase::UTF16ToUTF8(path).c_str());
	return result == tinyxml2::XML_SUCCESS;
}

bool ProjectXmlHelper::ReadNd(const std::wstring& path)
{
	tinyxml2::XMLError result = _doc.LoadFile(nbase::UTF16ToUTF8(path).c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return false;
	}
	tinyxml2::XMLElement* element = _doc.RootElement();
	for (tinyxml2::XMLElement* currentElement = element->FirstChildElement(); currentElement; currentElement = currentElement->NextSiblingElement()) {
		std::string value = element->Value();
		if (value == "Language") {
			_lang_element = element;
		}
		else if (value == "Resource") {
			_resource_element = element;
		}
		else if (value == "Layout") {
			_layout_element = element;
		}
	}

	return true;
}

void ProjectXmlHelper::ScanFolder(const std::wstring & folder)
{
	HANDLE hdnode;
	WIN32_FIND_DATA wdfnode;
	std::wstring path = folder + L"*.*";
	hdnode = FindFirstFile(path.c_str(), &wdfnode);
	if (INVALID_HANDLE_VALUE == hdnode) {
		return;
	}
	do {
		if (wdfnode.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (!strcmp(".", nbase::UTF16ToUTF8(wdfnode.cFileName).c_str()) || !strcmp("..", nbase::UTF16ToUTF8(wdfnode.cFileName).c_str())) {
				continue;
			}
			ScanFolder(folder + wdfnode.cFileName + L"\\");
		}
		else {
			tinyxml2::XMLElement* element = _doc.NewElement("Item");
			element->SetAttribute("path", nbase::UTF16ToUTF8(folder + wdfnode.cFileName).c_str());
			std::wstring suffix = L"";
			nbase::FilePathExtension(wdfnode.cFileName, suffix);
			if (suffix == L".ini") {
				_lang_element->InsertEndChild(element);
			}
			else if (suffix == L".xml") {
				_layout_element->InsertEndChild(element);
			}
			else {
				_resource_element->InsertEndChild(element);
			}
		}
	} while (FindNextFile(hdnode, &wdfnode));
	FindClose(hdnode);
}