#include "../stdafx.h"
#include "AreaVBox.h"

AreaVBox::AreaVBox():AreaVBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}

void AreaVBox::SetDropIMargin(POINT pt, AreaControlDelegate* target)
{
	ui::UiRect margin;
	target->SetUIMargin(margin);
}