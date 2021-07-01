#pragma once
#include "../delegate/AreaButtonDelegate.h"

class AreaButton : public ui::Button, public AreaButtonDelegate
{
public:
	AreaButton();
	AreaButton(const AreaButton & button);
private:
	void InitProperty();
};