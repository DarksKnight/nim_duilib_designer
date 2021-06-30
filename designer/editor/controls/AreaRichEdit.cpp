#include "../stdafx.h"
#include "AreaRichEdit.h"

AreaRichEdit::AreaRichEdit():AreaRichEditDelegate(this)
{
}

AreaRichEdit::AreaRichEdit(const AreaRichEdit& richedit): AreaRichEditDelegate(this)
{

}

AreaRichEdit::~AreaRichEdit()
{
}