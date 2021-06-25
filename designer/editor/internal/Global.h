#pragma once
#include "../stdafx.h"
#include "base/memory/singleton.h"

enum ThreadId
{
	kThreadUI
};

enum ControlType
{
	Box = 0,
	HBox
}; 

class ControlData : public ui::UserDataBase 
{
public:
	ControlData(const std::wstring& name, int width, int height, bool isLoad = false, ui::Box* parentBox = NULL) {
		this->name = name;
		this->width = width;
		this->height = height;
		this->isLoad = isLoad;
		this->parentBox = parentBox;
	}
public:
	std::wstring name = L"";
	int width = 0;
	int height = 0;
	ui::UiRect margin;
	bool isLoad = false;
	ui::Box* parentBox;
};