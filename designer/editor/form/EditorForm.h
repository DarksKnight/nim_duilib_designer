#pragma once
#include "../widget/EditorControlsList.h"
#include "../widget/EditorArea.h"
#include "../widget/EditorToolbar.h"

class EditorForm : public ui::WindowImplBase
{
public:
	EditorForm();
	~EditorForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static const std::wstring kClassName;
protected:
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
	void OnSelect(DrawControl control);
	void OnButtonUp();
	void OnSave();
	void OnNewFile();
	void OnSelectPathCallback(BOOL ret, std::wstring path);
	void OnMsgBoxCallback(nim_comp::MsgBoxRet ret);
private:
	EditorToolbar* _toolbar;
	EditorControlsList* _controls_list;
	EditorArea* _editor_area;
	ui::Box* _box_container;
	ui::Box* _box_property;
	ui::Box* _box_drag_pre;
	ui::Box* _box_editor_area;
private:
	std::map<int, DrawControl> _draw_controls;
	DrawControl _select_control;
	bool _saved = false;
	bool _exec_new = false;
	std::wstring _last_save_path;
};