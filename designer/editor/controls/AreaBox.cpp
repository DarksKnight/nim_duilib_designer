﻿#include "../stdafx.h"
#include "AreaBox.h"

AreaBox::AreaBox():AreaBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}