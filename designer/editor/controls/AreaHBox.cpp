#include "../stdafx.h"
#include "AreaHBox.h"

AreaHBox::AreaHBox():AreaHBoxDelegate(this)
{
	SetFixedWidth(160);
	SetFixedHeight(80);
}

void AreaHBox::SetDropIMargin(POINT pt, AreaControlDelegate* target)
{
	ui::UiRect margin;
	ui::Control* preCtrl = FindPreControl(target->GetCtonrol());
	if (preCtrl) {
		margin.left = pt.x - preCtrl->GetPos().right;
		margin.top = pt.y - preCtrl->GetPos().top;
	}
	else {
		margin.left = pt.x - GetPos().left;
		margin.top = pt.y - GetPos().top;
	}
	target->SetUIMargin(margin);
}