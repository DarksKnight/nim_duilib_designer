#pragma once

class EditorToolbar : public ui::Box
{
public:
	EditorToolbar();
	~EditorToolbar();
public:
	void SetSaveCallback(StdClosure callback) {
		_save_callback = callback;
	}
private:
	bool OnClickFile(ui::EventArgs* args);
	bool OnMenuSaveFile(ui::EventArgs* args);
	bool OnMenuSettings(ui::EventArgs* args);
private:
	ui::Button* _btn_tool_file;
	nim_comp::CMenuWnd* _tool_file_menu;
	StdClosure _save_callback;
};

