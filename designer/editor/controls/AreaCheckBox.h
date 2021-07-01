#pragma once
#include "../delegate/AreaCheckBoxDelegate.h"

class AreaCheckBox : public ui::CheckBox, public AreaCheckBoxDelegate
{
public:
	AreaCheckBox();
	AreaCheckBox(const AreaCheckBox & box);
};