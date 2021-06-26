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
	CONTROL_BUTTON_DOWN
};