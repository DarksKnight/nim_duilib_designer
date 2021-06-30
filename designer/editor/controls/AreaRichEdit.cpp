#include "../stdafx.h"
#include "AreaRichEdit.h"

AreaRichEdit::AreaRichEdit():AreaRichEditDelegate(this)
{
	SetFixedWidth(100);
	SetFixedHeight(30);
	InitProperty();
}

AreaRichEdit::AreaRichEdit(const AreaRichEdit& richEdit): AreaRichEditDelegate(this)
{
	SetName(richEdit.GetName());
	SetFixedWidth(richEdit.GetFixedWidth());
	SetFixedHeight(richEdit.GetFixedHeight());;
	SetMargin(richEdit.GetMargin());
	InitProperty();
}

AreaRichEdit::~AreaRichEdit()
{
}

void AreaRichEdit::InitProperty()
{
	SetEnabled(false);
	std::wstring text = L"请输入文字";
	SetText(text);
	_ext_property.clear();
	_ext_property.push_back(PropertyData(L"text", L"请输入文字", text));
}