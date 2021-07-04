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
	SetDelegateData(new DelegateData(*(DelegateData*)richEdit.GetUserDataBase()));
	DelegateData* data = (DelegateData*)richEdit.GetUserDataBase();
	SetEnabled(false);
	SetFixedWidth(data->GetWidth());
	SetFixedHeight(data->GetHeight());
	SetMargin(data->GetMargin());
	SetText(data->GetText());
	_ext_property.push_back(PropertyData(L"text", L"请输入文字", data->GetText()));
}