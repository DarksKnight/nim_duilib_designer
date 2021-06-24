#pragma once
#include "../widget/EditorControlsList.h"
#include "../widget/EditorArea.h"

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
private:
	void OnSelect(DrawControl control);
	void OnButtonUp();
private:
	EditorControlsList* _controls_list;
	EditorArea* _editor_area;
	ui::Box* _box_property;
private:
	std::map<int, DrawControl> _draw_controls;
	DrawControl _select_control;
};