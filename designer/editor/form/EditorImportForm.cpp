﻿#include "../stdafx.h"
#include "EditorImportForm.h"
#include "../internal/ProjectXmlHelper.h"

const LPCTSTR EditorImportForm::kClassName = L"EditorImportForm";

EditorImportForm::EditorImportForm()
{
}


EditorImportForm::~EditorImportForm()
{
}

std::wstring EditorImportForm::GetSkinFolder()
{
	return L"layout";
}

std::wstring EditorImportForm::GetSkinFile()
{
	return L"layout_editor_import.xml";
}

std::wstring EditorImportForm::GetWindowClassName() const
{
	return kClassName;
}

std::wstring EditorImportForm::GetWindowId() const
{
	return kClassName;
}

void EditorImportForm::InitWindow()
{
	_list_project = (ui::ListBox*)FindControl(L"list_project");
	_btn_import = (ui::Button*)FindControl(L"btn_import");
	_btn_new = (ui::Button*)FindControl(L"btn_new");
	_btn_new->AttachClick(nbase::Bind(&EditorImportForm::OnClick, this, std::placeholders::_1));
	_btn_import->AttachClick(nbase::Bind(&EditorImportForm::OnClick, this, std::placeholders::_1));
}

bool EditorImportForm::OnClick(ui::EventArgs* args)
{
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.nd)"] = L"*.nd";
	fileDlg->SetFilter(filters);
	fileDlg->SetFileName(L"newProject");
	fileDlg->SetDefExt(L".nd");
	fileDlg->SetParentWnd(GetHWND());
	std::wstring name = args->pSender->GetName();
	if (name == L"btn_new") {
		nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorImportForm::OnNewFileCallback, this, std::placeholders::_1, std::placeholders::_2);
		fileDlg->AyncShowSaveFileDlg(callback2);
	}
	else {
		nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorImportForm::OnImportFileCallback, this, std::placeholders::_1, std::placeholders::_2);
		fileDlg->AyncShowOpenFileDlg(callback2);
	}
	return true;
}

void EditorImportForm::OnNewFileCallback(BOOL ret, std::wstring path)
{
	if (!ret) {
		return;
	}
	std::wstring folder = L"";
	nbase::FilePathApartDirectory(path, folder);
	std::wstring langFolder = folder + L"\\lang";
	std::wstring themesFolder = folder + L"\\themes";
	if (!nbase::FilePathIsExist(langFolder, true) || !nbase::FilePathIsExist(themesFolder, true)) {
		return;
	}
	ProjectXmlHelper::GetInstance()->CreateNd(path);
}

void EditorImportForm::OnImportFileCallback(BOOL ret, std::wstring path)
{
	if (!ret) {
		return;
	}
	ProjectXmlHelper::GetInstance()->ReadNd(path);
}