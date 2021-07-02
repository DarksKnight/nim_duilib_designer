﻿#include "../stdafx.h"
#include "EditorCreateForm.h"
#include "../internal/SettingsHelper.h"

const LPCTSTR EditorCreateForm::kClassName = L"EditorCreateForm";

EditorCreateForm::EditorCreateForm()
{
}


EditorCreateForm::~EditorCreateForm()
{
}

std::wstring EditorCreateForm::GetSkinFolder()
{
	return L"layout";
}

std::wstring EditorCreateForm::GetSkinFile()
{
	return L"layout_editor_create.xml";
}

std::wstring EditorCreateForm::GetWindowClassName() const
{
	return kClassName;
}

std::wstring EditorCreateForm::GetWindowId() const
{
	return kClassName;
}

void EditorCreateForm::InitWindow()
{
	_cb_settings_show = (ui::CheckBox*)FindControl(L"cb_settings_show");
	_cb_settings_show->AttachSelect(nbase::Bind(&EditorCreateForm::OnSelectSettings, this, std::placeholders::_1));
	_cb_settings_show->AttachUnSelect(nbase::Bind(&EditorCreateForm::OnSelectSettings, this, std::placeholders::_1));
	_list_create_type = (ui::ListBox*)FindControl(L"list_create_type");
	_list_create_type->AttachSelect(nbase::Bind(&EditorCreateForm::OnCreateTypeSelect, this, std::placeholders::_1));
	_list_create_type->SelectItem(0);
	_btn_new_file = (ui::Button*)FindControl(L"btn_new_file");
	_btn_new_file->AttachClick(nbase::Bind(&EditorCreateForm::OnNewFileClick, this, std::placeholders::_1));
	_btn_open_file = (ui::Button*)FindControl(L"btn_open_file");
	_btn_open_file->AttachClick(nbase::Bind(&EditorCreateForm::OnOpenFileClick, this, std::placeholders::_1));
	_btn_cancel = (ui::Button*)FindControl(L"btn_cancel");
	_btn_cancel->AttachClick(nbase::Bind(&EditorCreateForm::OnCancelClick, this, std::placeholders::_1));
	std::wstring value = SettingsHelper::GetInstance()->Get(CONFIG_TAG_CREATE, CONFIG_KEY_CREATE_SHOW, L"1");
	_cb_settings_show->Selected(value == L"1");
}

LRESULT EditorCreateForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (_operation_type == OperationType::NEW_FILE && _new_file_callback) {
		_new_file_callback(_create_type);
	}
	else if (_operation_type == OperationType::OPEN_FILE && _open_file_callback) {
		_open_file_callback(_path);
	}
	if (_close_callback) {
		_close_callback(_operation_type);
	}
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT EditorCreateForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN && wParam == VK_RETURN) {
		OnNewFileClick(NULL);
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

bool EditorCreateForm::OnCreateTypeSelect(ui::EventArgs* args)
{
	switch (args->wParam)
	{
	case 0:
		_create_type = CreateType::WINDOW;
		break;
	case 1:
		_create_type = CreateType::WIDGET;
		break;
	default:
		break;
	}
	return true;
}

bool EditorCreateForm::OnNewFileClick(ui::EventArgs* args)
{
	_operation_type = OperationType::NEW_FILE;
	Close();
	return true;
}

bool EditorCreateForm::OnOpenFileClick(ui::EventArgs* args)
{
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.xml)"] = L"*.xml";
	fileDlg->SetFilter(filters);
	fileDlg->SetFileName(L"newFile");
	fileDlg->SetDefExt(L".xml");
	fileDlg->SetParentWnd(GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorCreateForm::OnSelectPathCallback, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AyncShowOpenFileDlg(callback2);
	return true;
}

bool EditorCreateForm::OnCancelClick(ui::EventArgs* args)
{
	Close();
	return true;
}

bool EditorCreateForm::OnSelectSettings(ui::EventArgs * args)
{
	if (_cb_settings_show->IsSelected()) {
		SettingsHelper::GetInstance()->Set(CONFIG_TAG_CREATE, CONFIG_KEY_CREATE_SHOW, L"1");
	}
	else {
		SettingsHelper::GetInstance()->Set(CONFIG_TAG_CREATE, CONFIG_KEY_CREATE_SHOW, L"0");
	}
	return true;
}

void EditorCreateForm::OnSelectPathCallback(BOOL ret, std::wstring path)
{
	_operation_type = OperationType::OPEN_FILE;
	_path = path;
	Close();
}