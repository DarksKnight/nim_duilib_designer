#include "../stdafx.h"
#include "AreaRichEdit.h"

AreaRichEdit::AreaRichEdit():AreaRichEditDelegate(this)
{
	SetFixedWidth(100);
	SetFixedHeight(30);
	SetText(L"请输入文字");
	SetEnabled(false);
}

AreaRichEdit::AreaRichEdit(const AreaRichEdit& richEdit): AreaRichEditDelegate(this)
{
	SetName(richEdit.GetName());
	SetFixedWidth(richEdit.GetFixedWidth());
	SetFixedHeight(richEdit.GetFixedHeight());;
	SetMargin(richEdit.GetMargin());
	SetEnabled(false);
	SetText(L"请输入文字");
}

AreaRichEdit::~AreaRichEdit()
{
}