#pragma once
#include "../delegate/AreaLabelDelegate.h"

class AreaLabel : public ui::Label, public AreaLabelDelegate
{
public:
	AreaLabel();
	AreaLabel(const AreaLabel& label);
};