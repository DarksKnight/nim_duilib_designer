#include "../stdafx.h"
#include "EditorTabBar.h"
#include "../internal/ProjectXmlHelper.h"

EditorTabBar::EditorTabBar()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_tabbar.xml");
	_editor_tree_project = (EditorTreeProject*)FindSubControl(L"etp");
}

EditorTabBar::~EditorTabBar()
{
}

void EditorTabBar::LoadProject()
{
	_editor_tree_project->LoadData(ProjectXmlHelper::GetInstance()->GetRootPath());
}