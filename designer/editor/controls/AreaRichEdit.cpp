#include "../stdafx.h"
#include "AreaRichEdit.h"

AreaRichEdit::AreaRichEdit():AreaRichEditDelegate(this)
{
	SetFixedWidth(100);
	SetFixedHeight(30);
	GetDelegateData()->SetWidth(100);
	GetDelegateData()->SetHeight(30);
	SetEnabled(false);
	std::wstring text = L"请输入文字";
	SetText(text);
	GetDelegateData()->SetText(text);
	_ext_property.push_back(PropertyData(L"text", L"请输入文字", text));
}

AreaRichEdit::AreaRichEdit(const AreaRichEdit& richEdit): AreaRichEditDelegate(this)
{
	SetEnabled(false);
	SetName(richEdit.GetName());
	SetFixedWidth(richEdit.GetFixedWidth());
	SetFixedHeight(richEdit.GetFixedHeight());;
	SetMargin(richEdit.GetMargin());
	std::wstring text = L"请输入文字";
	SetText(text);
	_ext_property.push_back(PropertyData(L"text", L"请输入文字", L"请输入文字"));
}