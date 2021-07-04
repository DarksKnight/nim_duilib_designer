#include "../stdafx.h"
#include "AreaButton.h"

AreaButton::AreaButton():AreaButtonDelegate(this)
{
	SetFixedWidth(80);
	SetFixedHeight(30);
	GetDelegateData()->SetWidth(80);
	GetDelegateData()->SetHeight(30);
	std::wstring text = L"按钮";
	SetText(text);
	GetDelegateData()->SetText(text);
	_ext_property.push_back(PropertyData(L"text", L"按钮内容", text));
}

AreaButton::AreaButton(const AreaButton& button):AreaButtonDelegate(this),ui::Button(button)
{
	_ext_property.push_back(PropertyData(L"text", L"按钮内容", button.GetText()));
}