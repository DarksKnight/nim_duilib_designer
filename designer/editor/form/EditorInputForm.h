#pragma once

class EditorInputForm : public nim_comp::WindowEx
{
public:
	typedef std::function<void(const std::wstring& text)> InputCallback;
public:
	EditorInputForm();
	~EditorInputForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static const LPCTSTR kClassName;
public:
	void SetCallback(InputCallback callback) {
		_callback = callback;
	}
private:
	bool OnClickOK(ui::EventArgs* args);
	bool OnClickCancel(ui::EventArgs* args);
private:
	ui::RichEdit* _re_input;
	ui::Button* _btn_ok;
	ui::Button* _btn_cancel;
private:
	bool _is_ok = false;
	InputCallback _callback;
};