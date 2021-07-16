#pragma once
#include "base/memory/singleton.h"

class GlobalXmlHelper : public nbase::SupportWeakCallback
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
	std::vector<std::wstring> GetClasses() {
		return _classes;
	}
	std::vector<std::wstring> GetFonts() {
		return _fonts;
	}
private:
	void Diff();
private:
	std::wstring _global_xml_path = L"";
	std::wstring _backup_global_xml_path = L"";
	std::vector<std::wstring> _fonts;
	std::vector<std::wstring> _colors;
	std::vector<std::wstring> _classes;
	int64_t _original_xml_size = 0;
};