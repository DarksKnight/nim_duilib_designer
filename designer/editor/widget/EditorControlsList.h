﻿#pragma once
#include "../internal/Global.h"

class EditorControlsList : public ui::VBox
{
public:
	typedef std::function<void(ControlData* data)> SelectCallback;
	typedef std::function<void()> ButtonUpCallback;
public:
	EditorControlsList();
	~EditorControlsList();
public:
	void LoadData(std::vector<ControlData*> datas);
public:
	void SetSelectCallback(SelectCallback callback) {
		_select_callback = callback;
	}
	void SetButtonUpCallback(ButtonUpCallback callback) {
		_button_up_callback = callback;
	}
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
private:
	SelectCallback _select_callback;
	ButtonUpCallback _button_up_callback;
	std::vector<ControlData*> _datas;
};