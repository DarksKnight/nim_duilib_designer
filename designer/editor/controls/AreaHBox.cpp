#include "../stdafx.h"
#include "AreaHBox.h"

AreaHBox::AreaHBox():AreaHBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}

AreaHBox::AreaHBox(const AreaHBox& box):AreaHBoxDelegate(this), ui::HBox(box)
{
}