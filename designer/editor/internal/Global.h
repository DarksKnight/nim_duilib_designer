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

enum CustomEventType
{
	UI_CHANGED = 0,
	CONTROL_BUTTON_DOWN,
	CONTROL_REMOVE,
	CONTROL_COPY,
	CONTROL_PASTE
};

struct ControlData
{
	std::wstring name = L"";
	std::wstring desc = L"";

	ControlData(std::wstring name, std::wstring desc) {
		this->name = name;
		this->desc = desc;
	}
};