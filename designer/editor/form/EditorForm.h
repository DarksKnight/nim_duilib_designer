#pragma once
#include "../widget/EditorControlsList.h"
#include "../widget/EditorArea.h"
#include "../widget/EditorToolbar.h"
#include "../widget/EditorProperty.h"
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
	bool Notify(ui::EventArgs* args);
	void OnSelect(const std::wstring & name);
	void OnButtonUp();
	void OnSaveFile();
	void OnNewFile();
	void DoNewFile(EditorCreateForm::CreateType type);
	void OnOpenFile(const std::wstring& path);
	void DoOpenFile(const std::wstring& path);
	void OnCreateFormClose();
	void OnSelectPathCallback(BOOL ret, std::wstring path);
	void OnNewFileMsgBoxCallback(nim_comp::MsgBoxRet ret, EditorCreateForm::CreateType type);
	void OnOpenFileMsgBoxCallback(nim_comp::MsgBoxRet ret, const std::wstring & path);
	void OpenCreateForm();
	void UiChanged();
private:
	EditorToolbar* _toolbar;
	EditorControlsList* _controls_list;
	EditorArea* _editor_area;
	EditorProperty* _editor_property;
	ui::Label* _lb_title;
	ui::Box* _box_container;
	ui::Box* _box_drag_pre;
	ui::Box* _box_editor_area;
private:
	std::wstring _select_name = L"";
	bool _saved = false;
	std::wstring _last_save_path = L"";
	std::wstring _title = L"";
};