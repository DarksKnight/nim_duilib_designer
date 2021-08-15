#include "../stdafx.h"
#include "ProjectXmlHelper.h"
#include "GlobalXmlHelper.h"

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
	tinyxml2::XMLElement* projectElement = _doc.NewElement("Project");
	_doc.InsertEndChild(projectElement);
	std::wstring folder = L"";
	nbase::FilePathApartDirectory(path, folder);
	tinyxml2::XMLElement* rootPathElement = _doc.NewElement("RootPath");
	rootPathElement->SetAttribute("path", nbase::UTF16ToUTF8(folder).c_str());
	projectElement->InsertEndChild(rootPathElement);
	_global_xml_element = _doc.NewElement("GlobalXml");
	projectElement->InsertEndChild(_global_xml_element);
	_lang_element = _doc.NewElement("Language");
	projectElement->InsertEndChild(_lang_element);
	_resource_element = _doc.NewElement("Resource");
	projectElement->InsertEndChild(_resource_element);
	_layout_element = _doc.NewElement("Layout");
	projectElement->InsertEndChild(_layout_element);
	_dir_element = _doc.NewElement("Dir");
	projectElement->InsertEndChild(_dir_element);
	InternalScanFolder(folder);
	tinyxml2::XMLError result = _doc.SaveFile(nbase::UTF16ToUTF8(path).c_str());
	if (result == tinyxml2::XML_SUCCESS) {
		std::wstring name = L"";
		nbase::FilePathApartFileName(path, name);
		_projects.push_front(ProjectInfo(name, path));
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
		std::string value = currentElement->Value();
		if (value == "RootPath") {
			_root_path = nbase::UTF8ToUTF16(currentElement->Attribute("path"));
		}
		else if (value == "GlobalXml") {
			std::wstring path = nbase::UTF8ToUTF16(currentElement->Attribute("path"));
			GlobalXmlHelper::GetInstance()->SetGlobalXmlPath(path);
		}
		else if (value == "Language") {
			_lang_element = currentElement;
		}
		else if (value == "Resource") {
			_resource_element = currentElement;
		}
		else if (value == "Layout") {
			_layout_element = currentElement;
		}
		else if (value == "Dir") {
			_dir_element = currentElement;
		}
	}
	RemoveProject(path);
	std::wstring name = L"";
	nbase::FilePathApartFileName(path, name);
	_projects.push_front(ProjectInfo(name, path));
	SaveCache();
	return true;
}

void ProjectXmlHelper::AddDir(const std::wstring& dir)
{
	if (CheckDupPath(_dir_element, dir)) {
		return;
	}
	tinyxml2::XMLElement* element = _doc.NewElement("Item");
	element->SetAttribute("path", nbase::UTF16ToUTF8(dir).c_str());
	_dir_element->InsertEndChild(element);
	_doc.SaveFile(nbase::UTF16ToUTF8((*_projects.begin()).path).c_str());
}

void ProjectXmlHelper::RemoveProject(const std::wstring& path)
{
	for (auto it = _projects.begin(); it != _projects.end(); ++it) {
		if (it->path == path) {
			_projects.erase(it);
			break;
		}
	}
	SaveCache();
}

void ProjectXmlHelper::RemoveItem(const std::wstring& path)
{
	bool result = RemovePathElement(_layout_element, path);
	if (!result) {
		result = RemovePathElement(_lang_element, path);
	}
	if (!result) {
		result = RemovePathElement(_resource_element, path);
	}
	if (!result) {
		result = RemovePathElement(_dir_element, path);
	}
	if (!result) {
		return;
	}
	_doc.SaveFile(nbase::UTF16ToUTF8((*_projects.begin()).path).c_str());
}

void ProjectXmlHelper::ScanFolder(const std::wstring& folder, std::vector<std::wstring>& paths)
{
	HANDLE hdnode;
	WIN32_FIND_DATA wdfnode;
	std::wstring path = folder + L"*.*";
	hdnode = FindFirstFile(path.c_str(), &wdfnode);
	if (INVALID_HANDLE_VALUE == hdnode) {
		return;
	}
	bool isDirEmpty = true;
	do {
		std::wstring fileName = wdfnode.cFileName;
		if (wdfnode.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (!strcmp(".", nbase::UTF16ToUTF8(fileName).c_str()) || !strcmp("..", nbase::UTF16ToUTF8(fileName).c_str())) {
				continue;
			}
			isDirEmpty = false;
			ScanFolder(folder + fileName + L"\\", paths);
		}
		else {
			isDirEmpty = false;
			std::wstring path = folder + fileName;
			if (!CheckDupPath(_layout_element, path) && !CheckDupPath(_resource_element, path)) {
				tinyxml2::XMLElement* element = _doc.NewElement("Item");
				element->SetAttribute("path", nbase::UTF16ToUTF8(path).c_str());
				std::wstring suffix = L"";
				nbase::FilePathExtension(fileName, suffix);
				if (suffix == L".xml") {
					_layout_element->InsertEndChild(element);
				}
				else {
					_resource_element->InsertEndChild(element);
				}
				paths.push_back(path);
			}
		}
	} while (FindNextFile(hdnode, &wdfnode));
	FindClose(hdnode);
	if (isDirEmpty && !CheckDupPath(_dir_element, folder)) {
		tinyxml2::XMLElement* element = _doc.NewElement("Item");
		element->SetAttribute("path", nbase::UTF16ToUTF8(folder).c_str());
		_dir_element->InsertEndChild(element);
		paths.push_back(folder);
	}
}

void ProjectXmlHelper::InternalScanFolder(const std::wstring & folder)
{
	HANDLE hdnode;
	WIN32_FIND_DATA wdfnode;
	std::wstring path = folder + L"*.*";
	hdnode = FindFirstFile(path.c_str(), &wdfnode);
	if (INVALID_HANDLE_VALUE == hdnode) {
		return;
	}
	bool isDirEmpty = true;
	do {
		std::wstring fileName = wdfnode.cFileName;
		if (wdfnode.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (!strcmp(".", nbase::UTF16ToUTF8(fileName).c_str()) || !strcmp("..", nbase::UTF16ToUTF8(fileName).c_str())) {
				continue;
			}
			isDirEmpty = false;
			InternalScanFolder(folder + fileName + L"\\");
		}
		else {
			isDirEmpty = false;
			tinyxml2::XMLElement* element = _doc.NewElement("Item");
			element->SetAttribute("path", nbase::UTF16ToUTF8(folder + fileName).c_str());
			std::wstring suffix = L"";
			nbase::FilePathExtension(fileName, suffix);
			if (suffix == L".ini") {
				_lang_element->InsertEndChild(element);
			}
			else if (suffix == L".xml") {
				if (fileName == L"global.xml") {
					std::wstring path = folder + fileName;
					_global_xml_element->SetAttribute("path", nbase::UTF16ToUTF8(path).c_str());
					GlobalXmlHelper::GetInstance()->SetGlobalXmlPath(path);
				}
				_layout_element->InsertEndChild(element);
			}
			else {
				_resource_element->InsertEndChild(element);
			}
		}
	} while (FindNextFile(hdnode, &wdfnode));
	FindClose(hdnode);
	if (isDirEmpty) {
		tinyxml2::XMLElement* element = _doc.NewElement("Item");
		element->SetAttribute("path", nbase::UTF16ToUTF8(folder).c_str());
		_dir_element->InsertEndChild(element);
	}
}

void ProjectXmlHelper::SaveCache()
{
	Json::Value cacheValue;
	Json::Value projectArray;
	for (auto it = _projects.begin(); it != _projects.end(); ++it) {
		Json::Value projectValue;
		projectValue["name"] = nbase::UTF16ToUTF8(it->name);
		projectValue["path"] = nbase::UTF16ToUTF8(it->path);
		projectArray.append(projectValue);
	}
	cacheValue["projects"] = projectArray;
	Json::FastWriter writer;
	nbase::WriteFile(_cache_path, writer.write(cacheValue));
}

bool ProjectXmlHelper::RemovePathElement(tinyxml2::XMLElement* element, const std::wstring& path)
{
	for (tinyxml2::XMLElement* currentElement = element->FirstChildElement(); currentElement; currentElement = currentElement->NextSiblingElement()) {
		std::wstring temp = nbase::UTF8ToUTF16(currentElement->Attribute("path"));
		if (temp != path) {
			continue;
		}
		element->DeleteChild(currentElement);
		return true;
	}
	return false;
}

bool ProjectXmlHelper::CheckDupPath(tinyxml2::XMLElement* element, const std::wstring& path)
{
	for (tinyxml2::XMLElement* currentElement = element->FirstChildElement(); currentElement; currentElement = currentElement->NextSiblingElement()) {
		std::wstring temp = nbase::UTF8ToUTF16(currentElement->Attribute("path"));
		if (temp == path) {
			return true;
		}
	}
	return false;
}