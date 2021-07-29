#include "../stdafx.h"
#include "EditorTabBar.h"

EditorTabBar::EditorTabBar()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_tabbar.xml");
}


EditorTabBar::~EditorTabBar()
{
}

void EditorTabBar::LoadProject()
{

}