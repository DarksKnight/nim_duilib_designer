#pragma once
#include "../widget/EditorControlsList.h"
#include "../widget/EditorArea.h"
#include "../widget/EditorToolbar.h"
#include "EditorCreateForm.h"

class EditorForm : public nim_comp::WindowEx
{
public:
	EditorForm();
	~EditorForm();
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static const LPCTSTR kClassName;
protected:
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
	void OnSelect(ControlData* data);
	void OnButtonUp();
	void OnSaveFile();
	void OnNewFile();
	void DoNewFile(EditorCreateForm::CreateType type);
	void OnOpenFile(const std::wstring& path);
	void OnSelectPathCallback(BOOL ret, std::wstring path);
	void OnMsgBoxCallback(nim_comp::MsgBoxRet ret, EditorCreateForm::CreateType type);
	void OpenCreateForm();
private:
	EditorToolbar* _toolbar;
	EditorControlsList* _controls_list;
	EditorArea* _editor_area;
	ui::Box* _box_container;
	ui::Box* _box_property;
	ui::Box* _box_drag_pre;
	ui::Box* _box_editor_area;
private:
	std::vector<ControlData*> _control_datas;
	ControlData* _select_data;
	bool _saved = false;
	std::wstring _last_save_path;
	int _pre_box_width = 100;
	int _pre_box_height = 60;
};