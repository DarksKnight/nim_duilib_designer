#include "../stdafx.h"
#include "PropertyHelper.h"

PropertyHelper::PropertyHelper()
{
}


PropertyHelper::~PropertyHelper()
{
}

std::vector<PropertyData> PropertyHelper::GetBasicProperty()
{
	if (!_basic_property.empty()) {
		return _basic_property;
	}
	_basic_property.push_back(PropertyData(L"name", L"名称"));
	_basic_property.push_back(PropertyData(L"width", L"宽度"));
	_basic_property.push_back(PropertyData(L"height", L"高度"));
	_basic_property.push_back(PropertyData(L"margin", L"外边距"));
	return _basic_property;
}