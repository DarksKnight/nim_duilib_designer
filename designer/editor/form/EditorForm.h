#pragma once
#include "../internal/Global.h"
#include "../widget/EditorControlsList.h"

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
	void OnSelect(int id);
private:
	EditorControlsList* _controls_list;
private:
	std::vector<DrawControl> _draw_controls;
};

