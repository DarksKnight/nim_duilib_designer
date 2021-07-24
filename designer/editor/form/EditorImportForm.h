#pragma once

class EditorImportForm : public nim_comp::WindowEx
{
public:
	EditorImportForm();
	~EditorImportForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual void InitWindow() override;
	static const LPCTSTR kClassName;
private:
	bool OnClick(ui::EventArgs* args);
private:
	void OnChooseFolderCallback(BOOL ret, std::wstring path);
private:
	ui::ListBox* _list_project;
	ui::Button* _btn_import;
};