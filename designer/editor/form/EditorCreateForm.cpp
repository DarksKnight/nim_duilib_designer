#include "../stdafx.h"
#include "EditorCreateForm.h"

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

void EditorCreateForm::InitWindow()
{
}

LRESULT EditorCreateForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
