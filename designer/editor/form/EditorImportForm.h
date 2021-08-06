#pragma once

class EditorImportForm : public nim_comp::WindowEx
{
public:
	typedef std::function<void(const std::wstring& path)> SelectCallback;
public:
	EditorImportForm();
	~EditorImportForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static const LPCTSTR kClassName;
public:
	void SetSelectCallback(SelectCallback callback) {
		_callback = callback;
	}
private:
	bool OnClick(ui::EventArgs* args);
	bool OnItemSelect(ui::EventArgs* args);
private:
	void OnNewFileCallback(BOOL ret, std::wstring path);
	void OnImportFileCallback(BOOL ret, std::wstring path);
private:
	void LoadDataItems();
private:
	ui::ListBox* _list_project;
	ui::Button* _btn_import;
	ui::Button* _btn_new;
private:
	SelectCallback _callback;
	std::wstring _select_path = L"";
};