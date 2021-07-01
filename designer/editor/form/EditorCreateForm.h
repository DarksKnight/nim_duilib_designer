#pragma once

class EditorCreateForm : public nim_comp::WindowEx
{
public:
	enum class OperationType
	{
		NONE, NEW_FILE, OPEN_FILE
	};
	enum class CreateType
	{
		NONE, WINDOW, WIDGET
	};
	typedef std::function<void(const std::wstring& path)> OpenFileCallback;
	typedef std::function<void(CreateType type)> NewFileCallback;
	typedef std::function<void(OperationType type)> CloseCallback;
public:
	EditorCreateForm();
	~EditorCreateForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static const LPCTSTR kClassName;
public:
	void SetNewFileCallback(NewFileCallback callback) {
		_new_file_callback = callback;
	}
	void SetOpenFileCallback(OpenFileCallback callback) {
		_open_file_callback = callback;
	}
	void SetCloseCallback(CloseCallback callback) {
		_close_callback = callback;
	}
protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
	bool OnCreateTypeSelect(ui::EventArgs* args);
	bool OnNewFileClick(ui::EventArgs* args);
	bool OnOpenFileClick(ui::EventArgs* args);
	bool OnCancelClick(ui::EventArgs* args);
private:
	void OnSelectPathCallback(BOOL ret, std::wstring path);
private:
	ui::ListBox* _list_create_type;
	ui::Button* _btn_new_file;
	ui::Button* _btn_open_file;
	ui::Button* _btn_cancel;
private:
	NewFileCallback _new_file_callback;
	OpenFileCallback _open_file_callback;
	CloseCallback _close_callback;
	OperationType _operation_type = OperationType::NONE;
	CreateType _create_type = CreateType::NONE;
	std::wstring _path = L"";
};

