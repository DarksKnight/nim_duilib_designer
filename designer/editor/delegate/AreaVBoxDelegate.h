#pragma once
#include "AreaBoxDelegate.h"

class AreaVBoxDelegate : public AreaBoxDelegate
{
public:
	AreaVBoxDelegate(ui::Control* control);
public:
	void SetDropUIMargin(POINT pt, AreaControlDelegate* target) override;
};