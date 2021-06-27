#pragma once
#include "../delegate/AreaHBoxDelegate.h"

class AreaHBox : public ui::HBox, public AreaHBoxDelegate
{
public:
	AreaHBox();
public:
	void SetDropIMargin(POINT pt, AreaControlDelegate* target) override;
};