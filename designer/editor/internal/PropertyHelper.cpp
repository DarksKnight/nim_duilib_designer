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

void PropertyHelper::SetProperty(ui::Control* control, const std::wstring& name, const std::wstring& value)
{
	if (name == L"name") {
		control->SetName(value);
	}
	else if (name == L"width") {
		int width = 0;
		nbase::StringToInt(value, &width);
		control->SetFixedWidth(width);
	}
	else if (name == L"height") {
		int height = 0;
		nbase::StringToInt(value, &height);
		control->SetFixedHeight(height);
	}
	else if (name == L"margin") {
		ui::UiRect rcMargin;
		LPTSTR pstr = NULL;
		rcMargin.left = _tcstol(value.c_str(), &pstr, 10);
		rcMargin.top = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.right = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.bottom = _tcstol(pstr + 1, &pstr, 10);
		control->SetMargin(rcMargin);
	}
}