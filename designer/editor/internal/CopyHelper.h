#pragma once
#include "base/memory/singleton.h"
#include "../delegate/AreaControlDelegate.h"

class CopyHelper
{
public:
	CopyHelper();
	~CopyHelper();
	SINGLETON_DEFINE(CopyHelper);
public:
	void Copy(ui::Control* ctrl);
	void Paste();
private:
	AreaControlDelegate* _copy_ctrl = NULL;
	ui::Box* _copy_ctrl_parent = NULL;
};