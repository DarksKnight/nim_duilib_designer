#pragma once
#include "../delegate/AreaVBoxDelegate.h"

class AreaVBox : public ui::VBox, public AreaVBoxDelegate
{
public:
	AreaVBox();
	AreaVBox(const AreaVBox& box);
};