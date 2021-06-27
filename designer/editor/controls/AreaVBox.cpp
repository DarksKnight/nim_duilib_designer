#include "../stdafx.h"
#include "AreaVBox.h"

AreaVBox::AreaVBox():AreaVBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}