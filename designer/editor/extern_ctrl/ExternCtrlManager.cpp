#pragma once
#include "../stdafx.h"
#include "ExternCtrlManager.h"
#include "../widget/EditorArea.h"
#include "../widget/EditorControlsList.h"
#include "../widget/EditorProperty.h"
#include "../widget/EditorToolbar.h"

ui::Control* ExternCtrlManager::CreateExternCtrl(const std::wstring& name)
{
	ui::Control* ret = nullptr;
	if (name.compare(L"EditorArea") == 0)
		ret = new EditorArea;
	else if (name.compare(L"EditorControlsList") == 0)
		ret = new EditorControlsList;
	else if (name.compare(L"EditorProperty") == 0)
		ret = new EditorProperty;
	else if (name.compare(L"EditorToolbar") == 0)
		ret = new EditorToolbar;
	return ret;
}