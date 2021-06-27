#include "../stdafx.h"
#include "AreaVBoxDelegate.h"

AreaVBoxDelegate::AreaVBoxDelegate(ui::Control* control):AreaBoxDelegate(control)
{
}

void AreaVBoxDelegate::SetDropIMargin(POINT pt, AreaControlDelegate* target)
{
	ui::UiRect margin;
	ui::Control* preCtrl = FindPreControl(target->GetCtonrol());
	if (preCtrl) {
		margin.left = pt.x - preCtrl->GetPos().left;
		margin.top = pt.y - preCtrl->GetPos().bottom;
	}
	else {
		margin.left = pt.x - _control->GetPos().left;
		margin.top = pt.y - _control->GetPos().top;
	}
	target->SetUIMargin(margin);
}