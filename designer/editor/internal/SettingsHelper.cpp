#include "../stdafx.h"
#include "SettingsHelper.h"
#include <ShlObj_core.h>


SettingsHelper::SettingsHelper()
{
	wchar_t path[2048];
	BOOL result = SHGetSpecialFolderPath(NULL
		, path
		, CSIDL_LOCAL_APPDATA
		, false);
	if (!result) {
		return;
	}
	_path = path;
	_path += L"\\NimDesigner\\config.ini";
}


SettingsHelper::~SettingsHelper()
{
}

void SettingsHelper::Set(const std::wstring & tag, const std::wstring& key, const std::wstring& value)
{
	WritePrivateProfileString(tag.c_str(), key.c_str(), value.c_str(), _path.c_str());
}

std::wstring Get(const std::wstring& tag, const std::wstring& key)
{
	std::wstring result = L"";
	return result;
}