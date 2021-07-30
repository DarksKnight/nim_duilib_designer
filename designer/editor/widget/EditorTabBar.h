#pragma once
#include "EditorTreeProject.h"

class EditorTabBar : public ui::Box
{
public:
	EditorTabBar();
	~EditorTabBar();
public:
	void LoadProject();
private:
	EditorTreeProject* _editor_tree_project;
};