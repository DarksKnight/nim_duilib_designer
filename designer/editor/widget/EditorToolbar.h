#pragma once

class EditorToolbar : public ui::Box
{
public:
	typedef std::function<void()> SaveCallback;
public:
	EditorToolbar();
	~EditorToolbar();
public:
	void InitCtrls();
public:
	void SetSaveCallback(SaveCallback callback) {
		_save_callback = callback;
	}
private:
	bool OnClickFile(ui::EventArgs* args);
	bool OnMenuFileSave(ui::EventArgs* args);
private:
	ui::Button* _btn_tool_file;
	nim_comp::CMenuWnd* _tool_file_menu;
	SaveCallback _save_callback;
};

