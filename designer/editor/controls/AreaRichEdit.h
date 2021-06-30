#pragma once
#include "../delegate/AreaRichEditDelegate.h"

class AreaRichEdit : public ui::RichEdit, public AreaRichEditDelegate
{
public:
	AreaRichEdit();
	AreaRichEdit(const AreaRichEdit& richedit);
	~AreaRichEdit();
};