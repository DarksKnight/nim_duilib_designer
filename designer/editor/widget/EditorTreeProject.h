#pragma once

class EditorTreeProject : public ui::Box
{
public:
	EditorTreeProject();
	~EditorTreeProject();
public:
	void LoadData(const std::wstring & path);
private:
	ui::Box* _box_tree_project;
};