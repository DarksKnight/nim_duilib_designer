#include "../stdafx.h"
#include "EditorTreeControls.h"

EditorTreeControls::EditorTreeControls()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_tree_controls.xml");
}


EditorTreeControls::~EditorTreeControls()
{
}