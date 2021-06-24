#include "../stdafx.h"
#include "EditorForm.h"

const std::wstring EditorForm::kClassName = L"EditorForm";

EditorForm::EditorForm()
{
}


EditorForm::~EditorForm()
{
}

std::wstring EditorForm::GetSkinFolder()
{
	return L"layout";
}

std::wstring EditorForm::GetSkinFile()
{
	return L"layout_editor.xml";
}

std::wstring EditorForm::GetWindowClassName() const
{
	return kClassName;
}

void EditorForm::InitWindow()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	_draw_controls.push_back(DrawControl(0, L"Box"));
	_controls_list = (EditorControlsList*)FindControl(L"eclList");
	_controls_list->SetSelectCallback(nbase::Bind(&EditorForm::OnSelect, this ,std::placeholders::_1));
	_controls_list->LoadData(_draw_controls);
}

LRESULT EditorForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void EditorForm::OnSelect(int id)
{
	
}