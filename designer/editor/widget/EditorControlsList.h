#pragma once
#include "../internal/Global.h"
#include "../internal/ControlHelper.h"

class EditorControlsList : public ui::Box, public ui::VirtualListInterface
{
public:
	typedef std::function<void(const std::wstring & name)> SelectCallback;
	typedef std::function<void()> ButtonUpCallback;
public:
	EditorControlsList();
	~EditorControlsList();
public:
public:
	ui::Control* CreateElement() override;
	void FillElement(ui::Control* control, int index) override;
public:
	int GetElementCount() {
		return _datas.size();
	}
	void SetSelectCallback(SelectCallback callback) {
		_select_callback = callback;
	}
	void SetButtonUpCallback(ButtonUpCallback callback) {
		_button_up_callback = callback;
	}
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
	bool OnSearchTextChanged(ui::EventArgs* args);
private:
	ui::VirtualListBox* _list_control;
	ui::RichEdit* _re_search;
private:
	SelectCallback _select_callback;
	ButtonUpCallback _button_up_callback;
	std::vector<ControlData> _datas;
};