#include "../stdafx.h"
#include "EditorTreeProject.h"

EditorTreeProject::EditorTreeProject()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_tree_project.xml");
	_box_tree_project = (ui::Box*)FindSubControl(L"box_tree_project");
}


EditorTreeProject::~EditorTreeProject()
{
}