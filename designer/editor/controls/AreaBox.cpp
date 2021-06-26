#include "../stdafx.h"
#include "AreaBox.h"

AreaBox::AreaBox():AreaControl(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}

AreaBox::~AreaBox()
{
}