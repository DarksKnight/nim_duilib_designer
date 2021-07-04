#include "../stdafx.h"
#include "AreaControl.h"

AreaControl::AreaControl():AreaControlDelegate(this)
{
	SetFixedWidth(50);
	SetFixedHeight(50);
	GetDelegateData()->SetWidth(50);
	GetDelegateData()->SetHeight(50);
}


AreaControl::AreaControl(const AreaControl& control):AreaControlDelegate(this),ui::Control(control)
{
}