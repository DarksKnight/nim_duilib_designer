#include "../stdafx.h"
#include "AreaControl.h"

AreaControl::AreaControl():AreaControlDelegate(this)
{
	SetFixedWidth(50);
	SetFixedHeight(50);
}


AreaControl::~AreaControl()
{
}