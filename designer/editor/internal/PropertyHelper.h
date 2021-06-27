#pragma once

class PropertyHelper
{
public:
	PropertyHelper();
	~PropertyHelper();
	SINGLETON_DEFINE(PropertyHelper);
public:
	std::vector<PropertyData> GetBasicProperty();
private:
	std::vector<PropertyData> _basic_property;
};