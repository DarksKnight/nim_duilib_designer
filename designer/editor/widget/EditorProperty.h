#pragma once
#include "../delegate/AreaControlDelegate.h"

class EditorProperty : public ui::Box
{
public:
	EditorProperty();
	~EditorProperty();
public:
	void LoadProperty(const std::wstring & name, AreaControlDelegate* delegate);
	void LoadControlProperty(ui::Control* control);
	void SetProperty(const std::wstring & name, const std::wstring & value);
private:
	ui::ListBox* _list_propery;
private:
	std::wstring _current_name = L"";
	std::vector<PropertyData> _basic_property;
	std::vector<PropertyData> _ext_property;
};

