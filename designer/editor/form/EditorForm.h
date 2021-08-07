#pragma once
#include "../widget/EditorControlsList.h"
#include "../widget/EditorArea.h"
#include "../widget/EditorToolbar.h"
#include "../widget/EditorProperty.h"
#include "../widget/EditorTreeControls.h"
#include "../widget/MenuPropertyList.h"
#include "EditorCreateForm.h"
#include "../widget/EditorTreeProject.h"
#include "../widget/EditorTabBar.h"

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
	static const LPCTSTR kClassName;
protected:
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
	bool Notify(ui::EventArgs* args);
	bool OnClickTab(ui::EventArgs* args);
	bool OnClickExit(ui::EventArgs* args);
private:
	void OnCreateFormClose(EditorCreateForm::OperationType type);
	void OnSaveSelectPathCallback(BOOL ret, std::wstring path);
	void OnOpenSelectPathCallback(BOOL ret, std::wstring path);
	void OnParseControl(AreaControlDelegate* delegate);
	void OnParseFinish();
private:
	void OnInitForm();
	void OnSelect(const ControlData& data);
	void OnButtonUp();
	void SaveFile();
	void DoNewFile(const std::wstring & flag);
	void OnOpenFile();
	void DoOpenFile(const std::wstring& path);
	void OpenImportForm();
	void OpenCreateForm();
	void UiChanged();
	void ShowControlPropery();
	void OnMenuPropertyListSelect(const std::wstring & key, const std::wstring & value);
	void ReadNd(const std::wstring & rdPath);
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
	ui::TabBox* _tb_tree;
	ui::Button* _btn_tree_project;
	ui::Button* _btn_tree_controls;
	ui::Button* _btn_close;
private:
	ControlData _select_data;
	bool _saved = false;
	std::wstring _last_save_path = L"";
	std::wstring _title = L"";
	std::wstring _templete_path = L"";
};