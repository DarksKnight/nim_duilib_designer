#include "../stdafx.h"
#include "AreaLabel.h"

AreaLabel::AreaLabel():AreaLabelDelegate(this)
{
	SetFixedWidth(80);
	SetFixedHeight(30);
	InitProperty();
}


AreaLabel::AreaLabel(const AreaLabel& label) :AreaLabelDelegate(this),ui::Label(label)
{
	InitProperty();
}

void AreaLabel::InitProperty()
{
	std::wstring text = L"文本";
	SetText(text);
	_ext_property.clear();
	_ext_property.push_back(PropertyData(L"text", L"文本内容", text));
}