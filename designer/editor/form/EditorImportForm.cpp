#include "../stdafx.h"
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
	_btn_import->AttachClick(nbase::Bind(&EditorImportForm::OnClick, this, std::placeholders::_1));
}

bool EditorImportForm::OnClick(ui::EventArgs* args)
{
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	fileDlg->SetParentWnd(GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&EditorImportForm::OnChooseFolderCallback, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AsyncShowSelectFolderDlg(callback2);
	return true;
}

void EditorImportForm::OnChooseFolderCallback(BOOL ret, std::wstring path)
{
	if (!ret) {
		return;
	}
	std::wstring langFolder = path + L"\\lang";
	std::wstring themesFolder = path + L"\\themes";
	if (!nbase::FilePathIsExist(langFolder, true) || !nbase::FilePathIsExist(themesFolder, true)) {
		return;
	}
	ProjectXmlHelper::GetInstance()->CreateProjectXml(path);
}