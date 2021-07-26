#pragma once
#include "../widget/EditorControlsList.h"
#include "../widget/EditorArea.h"
#include "../widget/EditorToolbar.h"
#include "../widget/EditorProperty.h"
#include "../widget/EditorTreeControls.h"
#include "../widget/MenuPropertyList.h"
#include "EditorCreateForm.h"
#include "../widget/EditorTreeProject.h"

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
	bool OnClickWarn(ui::EventArgs* args);
private:
	void OnInitForm();
	void OnSelect(const ControlData& data);
	void OnButtonUp();
	void SaveFile();
	void DoNewFile(const std::wstring & flag);
	void OnOpenFile();
	void DoOpenFile(const std::wstring& path);
	void OnCreateFormClose(EditorCreateForm::OperationType type);
	void OnSaveSelectPathCallback(BOOL ret, std::wstring path);
	void OnOpenSelectPathCallback(BOOL ret, std::wstring path);
	void OnChooseGlobalXmlPath(BOOL ret, std::wstring path);
	void OnParseControl(AreaControlDelegate* delegate);
	void OpenImportForm();
	void OpenCreateForm();
	void UiChanged();
	void ShowControlPropery();
	void OnMenuPropertyListSelect(const std::wstring & key, const std::wstring & value);
private:
	EditorToolbar* _toolbar;
	EditorControlsList* _controls_list;
	EditorArea* _editor_area;
	EditorProperty* _editor_property;
	EditorTreeControls* _editor_tree_controls;
	EditorTreeProject* _editor_tree_project;
	MenuPropertyList* _menu_property_list;
	ui::Label* _lb_title;
	ui::Box* _box_container;
	ui::Box* _box_drag_pre;
	ui::Box* _box_editor_area;
	ui::Box* _box_property;
	ui::Box* _box_warn;
private:
	ControlData _select_data;
	bool _saved = false;
	std::wstring _last_save_path = L"";
	std::wstring _title = L"";
	std::wstring _templete_path = L"";
};