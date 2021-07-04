#include "../stdafx.h"
#include "AreaCheckBox.h"

AreaCheckBox::AreaCheckBox():AreaCheckBoxDelegate(this)
{
	SetFixedWidth(80);
	SetFixedHeight(20);
	SetClass(L"checkbox_font14");
	GetDelegateData()->SetWidth(80);
	GetDelegateData()->SetHeight(20);
	GetDelegateData()->SetClass(L"checkbox_font14");
	SetEnabled(false);
	std::wstring text = L"文本";
	SetText(text);
	GetDelegateData()->SetText(text);
	_ext_property.push_back(PropertyData(L"text", L"复选框内容", text));
}

AreaCheckBox::AreaCheckBox(const AreaCheckBox& box):AreaCheckBoxDelegate(this),ui::CheckBox(box)
{
	_ext_property.push_back(PropertyData(L"text", L"复选框内容", box.GetText()));
	SetDelegateData(new DelegateData(*(DelegateData*)box.GetUserDataBase()));
}