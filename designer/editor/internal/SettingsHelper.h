#pragma once

class SettingsHelper
{
public:
	SettingsHelper();
	~SettingsHelper();
	SINGLETON_DEFINE(SettingsHelper);
public:
	void Set(const std::wstring& tag, const std::wstring& key, const std::wstring& value);
	std::wstring Get(const std::wstring& tag, const std::wstring& key, LPCWSTR default = L"");
private:
	std::wstring _path;
};