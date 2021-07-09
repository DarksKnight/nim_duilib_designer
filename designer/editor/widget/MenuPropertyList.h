#pragma once

class MenuPropertyList : public ui::Box
{
public:
	typedef std::function<void(const std::wstring & key, const std::wstring& value)> SelectCallback;
public:
	MenuPropertyList();
	~MenuPropertyList();
public:
	void LoadClassData(const std::wstring & key, std::map<std::wstring, Class> classes);
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
	std::wstring _key = L"";
};