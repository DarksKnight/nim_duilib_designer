#pragma once
#include "../delegate/AreaVBoxDelegate.h"

class AreaVBox : public ui::VBox, public AreaVBoxDelegate
{
public:
	AreaVBox();
public:
	void SetDropIMargin(POINT pt, AreaControlDelegate* target) override;
};