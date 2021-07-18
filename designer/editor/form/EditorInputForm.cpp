#include "../stdafx.h"
#include "EditorInputForm.h"

const LPCTSTR EditorInputForm::kClassName = L"EditorInputForm";

EditorInputForm::EditorInputForm()
{
}


EditorInputForm::~EditorInputForm()
{
}

std::wstring EditorInputForm::GetSkinFolder()
{
	return L"layout";
}

std::wstring EditorInputForm::GetSkinFile()
{
	return L"layout_editor_input.xml";
}

std::wstring EditorInputForm::GetWindowClassName() const
{
	return kClassName;
}

std::wstring EditorInputForm::GetWindowId() const
{
	return kClassName;
}

void EditorInputForm::InitWindow()
{
	_re_input = (ui::RichEdit*)FindControl(L"re_input");
	_btn_ok = (ui::Button*)FindControl(L"btn_ok");
	_btn_cancel = (ui::Button*)FindControl(L"btn_cancel");
}

LRESULT EditorInputForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (_callback) {
		_callback(_is_ok ? _re_input->GetText() : L"");
	}
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool EditorInputForm::OnClickOK(ui::EventArgs* args)
{
	_is_ok = true;
	Close();
	return true;
}

bool EditorInputForm::OnClickCancel(ui::EventArgs* args)
{
	Close();
	return true;
}