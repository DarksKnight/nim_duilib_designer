#pragma once

class PropertyHelper
{
public:
	PropertyHelper();
	~PropertyHelper();
	SINGLETON_DEFINE(PropertyHelper);
public:
	void SetProperty(ui::Control* control, const std::wstring& name, const std::wstring & value);
private:
	std::vector<PropertyData> _basic_property;
};