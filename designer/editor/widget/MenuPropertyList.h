﻿#pragma once

class MenuPropertyList : public ui::Box
{
public:
	typedef std::function<void(const std::wstring & key, const std::wstring& value)> SelectCallback;
public:
	MenuPropertyList();
	~MenuPropertyList();
public:
	void Show(const std::wstring& type);
	void Hide();
	void LoadClassData(std::map<std::wstring, Class> classes);
	void LoadFontData(std::map<std::wstring, Font> fonts);
public:
	void SetSelectCallback(SelectCallback callback) {
		_select_callback = callback;
	}
private:
	bool OnSelect(ui::EventArgs* args);
private:
	ui::ListBox* _list_property;
private:
	SelectCallback _select_callback;
	std::wstring _type = L"";
};