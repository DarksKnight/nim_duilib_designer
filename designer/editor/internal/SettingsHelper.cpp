#include "../stdafx.h"
#include "SettingsHelper.h"
#include <ShlObj_core.h>


SettingsHelper::SettingsHelper()
{
	TCHAR path[MAX_PATH] = {0};
	BOOL result = SHGetSpecialFolderPath(NULL, path, CSIDL_APPDATA, false);
	if (!result) {
		return;
	}
	_path = path;
	_path += L"\\NimDesigner\\";
	nbase::CreateDirectory(_path);
	_path += L"config.ini";
}


SettingsHelper::~SettingsHelper()
{
}

void SettingsHelper::Set(const std::wstring & tag, const std::wstring& key, const std::wstring& value)
{
	WritePrivateProfileString(tag.c_str(), key.c_str(), value.c_str(), _path.c_str());
}

std::wstring SettingsHelper::Get(const std::wstring& tag, const std::wstring& key, LPCWSTR default)
{
	TCHAR result[MAX_PATH] = { 0 };
	GetPrivateProfileString(tag.c_str(), key.c_str(), default, result, MAX_PATH, _path.c_str());
	return result;
}