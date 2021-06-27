#include "../stdafx.h"
#include "AreaHBox.h"

AreaHBox::AreaHBox():AreaHBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}