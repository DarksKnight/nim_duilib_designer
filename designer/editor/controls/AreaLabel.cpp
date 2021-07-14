#include "../stdafx.h"
#include "AreaLabel.h"

AreaLabel::AreaLabel():AreaLabelDelegate(this)
{
	SetFixedWidth(80);
	SetFixedHeight(30);
	GetDelegateData()->SetWidth(80);
	GetDelegateData()->SetHeight(30);
	std::wstring text = L"文本";
	SetText(text);
	GetDelegateData()->SetText(text);
	_ext_property.push_back(PropertyData(L"text", L"文本内容", text));
	_ext_property.push_back(PropertyData(L"font", L"字体大小"));
}


AreaLabel::AreaLabel(const AreaLabel& label) :AreaLabelDelegate(this),ui::Label(label)
{
	_ext_property.push_back(PropertyData(L"text", L"文本内容", label.GetText()));
	_ext_property.push_back(PropertyData(L"font", L"字体大小"));
	SetDelegateData(new DelegateData(*(DelegateData*)label.GetUserDataBase()));
}