#pragma once

class EditorProperty : public ui::Box
{
public:
	EditorProperty();
	~EditorProperty();
public:
	void LoadProperty(const std::wstring & name, const std::vector<PropertyData> & datas);
	void LoadControlProperty(ui::Control* control);
private:
	void SetProperty(const std::wstring & name, const std::wstring & value);
private:
	ui::ListBox* _list_propery;
private:
	std::wstring _current_name = L"";
	std::vector<PropertyData> _current_datas;
};

