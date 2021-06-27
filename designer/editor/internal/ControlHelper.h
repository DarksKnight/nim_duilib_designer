#pragma once
#include "base/memory/singleton.h"
#include "../delegate/AreaControlDelegate.h"

class ControlHelper
{
public:
	ControlHelper();
	~ControlHelper();
	SINGLETON_DEFINE(ControlHelper);
public:
	std::vector<std::wstring> GetControlList();
	ui::CSize GetPreSize(const std::wstring & name);
	AreaControlDelegate* CreateControl(const std::wstring& name);
	AreaControlDelegate* AddControl(ui::Box* box, const std::wstring& name);
private:
	std::vector<std::wstring> _datas;
};