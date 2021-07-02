#pragma once
#include "../stdafx.h"
#include "base/memory/singleton.h"

#define CONFIG_TAG_CREATE L"CreateForm"
#define CONFIG_KEY_CREATE_SHOW L"Show"

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
	CONTROL_PASTE,
	CONTROL_SELECTED,
	CONTROL_SET_PROPERTY
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

struct PropertyData
{
	std::wstring name = L"";
	std::wstring desc = L"";
	std::wstring defaultValue = L"";

	PropertyData(std::wstring name, std::wstring desc, std::wstring defaultValue = L"") {
		this->name = name;
		this->desc = desc;
		this->defaultValue = defaultValue;
	}
};