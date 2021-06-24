#pragma once
#include "../stdafx.h"
#include "base/memory/singleton.h"

enum ControlType
{
	Box = 0,
	HBox
};

struct DrawControl 
{
	int id;
	std::wstring name;

	DrawControl() {
		this->id = -1;
		this->name = L"";
	}

	DrawControl(int id, std::wstring name) {
		this->id = id;
		this->name = name;
	}
};