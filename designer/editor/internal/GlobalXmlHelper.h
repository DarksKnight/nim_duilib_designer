#pragma once
#include "base/memory/singleton.h"

class GlobalXmlHelper
{
public:
	struct Font
	{
		std::wstring id;
		std::wstring name;
		int size;
		bool bold;
		bool underline;
	};
	struct Class
	{
		std::wstring name;
	};
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