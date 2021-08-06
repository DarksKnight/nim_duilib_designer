#pragma once

class ProjectXmlHelper
{
public:
	struct ProjectInfo
	{
		std::wstring name;
		std::wstring path;

		ProjectInfo(const std::wstring& name, const std::wstring& path) {
			this->name = name;
			this->path = path;
		}
	};
public:
	ProjectXmlHelper();
	~ProjectXmlHelper();
	SINGLETON_DEFINE(ProjectXmlHelper);
public:
	bool CreateNd(const std::wstring& path);
	bool ReadNd(const std::wstring& path);
	void RemoveProject(const std::wstring & path);
public:
	std::list<ProjectInfo> GetProjects() {
		return _projects;
	}
	std::wstring GetNdPath() {
		return (*_projects.begin()).path;
	}
	std::wstring GetRootPath() {
		return _root_path;
	}
	tinyxml2::XMLElement* GetLangElement() {
		return _lang_element;
	}
	tinyxml2::XMLElement* GetResourcesElement() {
		return _resource_element;
	}
	tinyxml2::XMLElement* GetLayoutElement() {
		return _layout_element;
	}
private:
	void ScanFolder(const std::wstring& folder);
	void SaveCache();
private:
	const std::wstring _suffix = L".nd";
	tinyxml2::XMLDocument _doc;
	tinyxml2::XMLElement* _lang_element;
	tinyxml2::XMLElement* _resource_element;
	tinyxml2::XMLElement* _layout_element;
	tinyxml2::XMLElement* _global_xml_element;
	std::wstring _cache_path = L"";
	std::wstring _root_path = L"";
	std::list<ProjectInfo> _projects;
};