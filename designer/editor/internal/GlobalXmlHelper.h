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
	Font GetFont(const std::wstring& id);
public:
	std::wstring GetGlobalXmlPath() {
		return _global_xml_path;
	}
	std::map<std::wstring, Class> GetClasses() {
		return _classes;
	}
	std::map<std::wstring, Font> GetFonts() {
		return _fonts;
	}
private:
	std::wstring _global_xml_path;
	std::wstring _backup_global_xml_path;
	std::map<std::wstring, Font> _fonts;
	std::map<std::wstring, std::wstring> _colors;
	std::map<std::wstring, Class> _classes;
};