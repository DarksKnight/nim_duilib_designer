#include "../stdafx.h"
#include "AreaBox.h"

AreaBox::AreaBox():AreaBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
	GetDelegateData()->SetWidth(160);
	GetDelegateData()->SetHeight(80);
}

AreaBox::AreaBox(const AreaBox& box):AreaBoxDelegate(this),ui::Box(box)
{
	SetDelegateData(new DelegateData(*(DelegateData*)box.GetUserDataBase()));
}