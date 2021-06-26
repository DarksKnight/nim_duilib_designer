#pragma once
#include "../delegate/AreaBoxDelegate.h"

class AreaBox : public ui::Box, public AreaBoxDelegate
{
public:
	AreaBox();
};