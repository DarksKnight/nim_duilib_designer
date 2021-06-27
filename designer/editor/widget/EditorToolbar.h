#pragma once

class EditorToolbar : public ui::Box
{
public:
	typedef std::function<void(const std::wstring& path)> OpenFileCallback;
public:
	EditorToolbar();
	~EditorToolbar();
public:
	void SetSaveCallback(StdClosure callback) {
		_save_callback = callback;
	}
	void SetNewFileCallback(StdClosure callback) {
		_new_file_callback = callback;
	}
	void SetOpenFileCallback(OpenFileCallback callback) {
		_open_file_callback = callback;
	}
private:
	bool OnClickFile(ui::EventArgs* args);
	bool OnMenuSaveFile(ui::EventArgs* args);
	bool OnMenuNewFile(ui::EventArgs* args);
	bool OnMenuOpenFile(ui::EventArgs* args);
	void OnSelectPathCallback(BOOL ret, std::wstring path);
private:
	ui::Button* _btn_tool_file;
	nim_comp::CMenuWnd* _tool_file_menu;
	StdClosure _save_callback;
	StdClosure _new_file_callback;
	OpenFileCallback _open_file_callback;
};

