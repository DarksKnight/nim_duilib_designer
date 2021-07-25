#include "../stdafx.h"
#include "ProjectXmlHelper.h"

ProjectXmlHelper::ProjectXmlHelper()
{
	_cache_path = GlobalData::APPDATA_ROMAING + L"project.json";
	if (!nbase::FilePathIsExist(_cache_path, false)) {
		return;
	}
	std::string content = "";
	nbase::ReadFileToString(_cache_path, content);
	Json::Reader reader;
	Json::Value value;
	bool result = reader.parse(content, value);
	if (!result) {
		return;
	}
	Json::Value projectArray = value["projects"];
	for (int i = 0; i < projectArray.size(); i++) {
		Json::Value obj = projectArray[i];
		_projects.push_back(ProjectInfo(nbase::UTF8ToUTF16(obj["name"].asString()), nbase::UTF8ToUTF16(obj["path"].asString())));
	}
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
	if (result == tinyxml2::XML_SUCCESS) {
		_nd_path = path;
		SaveCache();
	}
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
	_nd_path = path;
	SaveCache();
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

void ProjectXmlHelper::SaveCache()
{
	Json::Value cacheValue;
	Json::Value projectArray;
	if (nbase::FilePathIsExist(_cache_path, false)) {
		std::string content = "";
		nbase::ReadFileToString(_cache_path, content);
		Json::Reader reader;
		bool result = reader.parse(content, cacheValue);
		if (result) {
			projectArray = cacheValue["projects"];
		}
	}
	Json::Value projectValue;
	std::wstring name = L"";
	nbase::FilePathApartFileName(_nd_path, name);
	projectValue["name"] = nbase::UTF16ToUTF8(name);
	projectValue["path"] = nbase::UTF16ToUTF8(_nd_path);
	projectArray.append(projectValue);
	cacheValue["projects"] = projectArray;
	Json::FastWriter writer;
	nbase::WriteFile(_cache_path, writer.write(cacheValue));
}