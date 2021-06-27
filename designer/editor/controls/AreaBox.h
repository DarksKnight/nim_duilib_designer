#pragma once
#include "../delegate/AreaBoxDelegate.h"

class AreaBox : public ui::Box, public AreaBoxDelegate
{
public:
	AreaBox();
public:
	void SetDropIMargin(POINT pt, AreaControlDelegate* target) {
		ui::UiRect margin(pt.x - GetPos().left, pt.y - GetPos().top, 0, 0);
		target->SetUIMargin(margin);
	}
};