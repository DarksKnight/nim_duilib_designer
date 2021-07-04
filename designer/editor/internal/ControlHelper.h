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
	AreaControlDelegate* DropControl(ui::Box* box, POINT pt, const std::wstring& name);
	AreaControlDelegate* DropControl(ui::Box* box, const std::wstring& name);
	void Remove(ui::Control* control);
	bool CheckDupliName(const std::wstring& name, ui::Box* box);
	std::wstring GetName(const std::wstring& name);
public:
	void SetContainerBox(ui::Box* box) {
		_container_box = box;
	}
	int CreateId() {
		return _id++;
	}
private:
	ui::Box* _container_box = NULL;
private:
	std::vector<ControlData> _datas;
	int _box_index = 0;
	int _hbox_index = 0;
	int _vbox_index = 0;
	int _control_index = 0;
	int _label_index = 0;
	int _richedit_index = 0;
	int _button_index = 0;
	int _checkbox_index = 0;
	int _id = 0;
};