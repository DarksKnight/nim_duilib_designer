#pragma once

class EditorCreateForm : public nim_comp::WindowEx
{
public:
	typedef std::function<void(const std::wstring & flag)> NewFileCallback;
public:
	EditorCreateForm();
	~EditorCreateForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual void InitWindow() override;
	static const LPCTSTR kClassName;
public:
	void SetNewFileCallback(NewFileCallback callback) {
		_new_file_callback = callback;
	}
protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
	bool OnCreateTypeSelect(ui::EventArgs* args);
	bool OnNewFileClick(ui::EventArgs* args);
	bool OnCancelClick(ui::EventArgs* args);
private:
	bool ParseXmlPreview(ui::Box* box, const std::wstring& path);
	void ParseElement(tinyxml2::XMLElement* element, ui::Box* rootBox);
private:
	ui::ListBox* _list_create_type;
	ui::Button* _btn_new_file;
	ui::Button* _btn_cancel;
	ui::Box* _box_preview;
private:
	NewFileCallback _new_file_callback;
	std::wstring _create_flag = L"";
	std::wstring _path = L"";
	std::vector<CreateDataInfo> _create_data_infos;
};

