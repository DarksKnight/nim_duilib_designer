#include "../stdafx.h"
#include "AreaHBoxDelegate.h"

AreaHBoxDelegate::AreaHBoxDelegate(ui::Control* control):AreaBoxDelegate(control)
{
}

void AreaHBoxDelegate::SetDropIMargin(POINT pt, AreaControlDelegate* target)
{
	ui::UiRect margin;
	ui::Control* preCtrl = FindPreControl(target->GetCtonrol());
	if (preCtrl) {
		margin.left = pt.x - preCtrl->GetPos().right;
		margin.top = pt.y - preCtrl->GetPos().top;
	}
	else {
		margin.left = pt.x - _control->GetPos().left;
		margin.top = pt.y - _control->GetPos().top;
	}
	target->SetUIMargin(margin);
}