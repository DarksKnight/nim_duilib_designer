#pragma once
#include "AreaBoxDelegate.h"

class AreaHBoxDelegate : public AreaBoxDelegate
{
public:
	AreaHBoxDelegate(ui::Control* control);
public:
	void SetDropUIMargin(POINT pt, AreaControlDelegate* target) override;
};