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
	std::vector<ControlData> GetControlList();
	ui::CSize GetPreSize(const std::wstring & name);
	AreaControlDelegate* CreateControl(const std::wstring& name);
	AreaControlDelegate* AddControl(ui::Box* box, const std::wstring& name, const std::wstring & controlName = L"");
	ui::Control* Clone(AreaControlDelegate* delegate);
	void Remove(ui::Control* control);
	bool CheckDupliName(const std::wstring& name, ui::Box* box);
	std::wstring GetControlName(const std::wstring& name, ui::Box* box);
private:
	std::vector<ControlData> _datas;
	int _box_index = 0;
	int _hbox_index = 0;
	int _vbox_index = 0;
	int _control_index = 0;
};