#pragma once
#include "base/memory/singleton.h"

class GlobalXmlHelper
{
public:
	GlobalXmlHelper();
	~GlobalXmlHelper();
	SINGLETON_DEFINE(GlobalXmlHelper);
public:
	bool SetGlobalXmlPath(const std::wstring& path);
public:
	std::wstring GetGlobalXmlPath() {
		return _global_xml_path;
	}
	std::map<std::wstring, Class> GetClasses() {
		return _classes;
	}
private:
	std::wstring _global_xml_path;
	std::map<std::wstring, Font> _fonts;
	std::map<std::wstring, std::wstring> _colors;
	std::map<std::wstring, Class> _classes;
};