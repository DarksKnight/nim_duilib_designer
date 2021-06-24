#pragma once

class EditorToolbar : public ui::Box
{
public:
	EditorToolbar();
	~EditorToolbar();
public:
	void InitCtrls();
private:
	bool OnClick(ui::EventArgs* args);
private:
	ui::Button* _btn_tool_file;
	nim_comp::CMenuWnd* _tool_file_menu;
};

