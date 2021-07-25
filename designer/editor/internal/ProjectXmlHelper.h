#pragma once

class ProjectXmlHelper
{
public:
	ProjectXmlHelper();
	~ProjectXmlHelper();
	SINGLETON_DEFINE(ProjectXmlHelper);
public:
	bool CreateNd(const std::wstring& path);
	bool ReadNd(const std::wstring& path);
private:
	void ScanFolder(const std::wstring& folder);
private:
	const std::wstring _suffix = L".nd";
	tinyxml2::XMLDocument _doc;
	tinyxml2::XMLElement* _lang_element;
	tinyxml2::XMLElement* _resource_element;
	tinyxml2::XMLElement* _layout_element;
	std::wstring _path = L"";
};