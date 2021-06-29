#pragma once
#include "../delegate/AreaControlDelegate.h"

class AreaControl : public ui::Control, public AreaControlDelegate
{
public:
	AreaControl();
	AreaControl(const AreaControl& control);
};