#pragma once
#include "../stdafx.h"
#include "base/memory/singleton.h"

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