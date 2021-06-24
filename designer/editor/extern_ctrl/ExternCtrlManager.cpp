#pragma once
#include "../stdafx.h"
#include "ExternCtrlManager.h"
#include "../widget/EditorArea.h"
#include "../widget/EditorControlsList.h"

ui::Control* ExternCtrlManager::CreateExternCtrl(const std::wstring& name)
{
	ui::Control* ret = nullptr;
	if (name.compare(L"EditorArea") == 0)
		ret = new EditorArea;
	else if (name.compare(L"EditorControlsList") == 0)
		ret = new EditorControlsList;
	return ret;
}