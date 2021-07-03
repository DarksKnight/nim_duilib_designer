#include "../stdafx.h"
#include "PropertyHelper.h"

PropertyHelper::PropertyHelper()
{
}


PropertyHelper::~PropertyHelper()
{
}

void PropertyHelper::SetProperty(ui::Control* control, const std::wstring& name, const std::wstring& value)
{
	if (name == L"name") {
		control->SetName(value);
	}
	else if (name == L"width") {
		int width = 0;
		if (value == L"auto") {
			width = DUI_LENGTH_AUTO;
		}
		else if (value == L"stretch") {
			width = DUI_LENGTH_STRETCH;
		}
		else {
			nbase::StringToInt(value, &width);
		}
		control->SetFixedWidth(width);
	}
	else if (name == L"height") {
		int height = 0;
		if (value == L"auto") {
			height = DUI_LENGTH_AUTO;
		}
		else if (value == L"stretch") {
			height = DUI_LENGTH_STRETCH;
		}
		else {
			nbase::StringToInt(value, &height);
		}
		control->SetFixedHeight(height);
	}
	else if (name == L"margin") {
		ui::UiRect rcMargin;
		LPTSTR pstr = NULL;
		rcMargin.left = _tcstol(value.c_str(), &pstr, 10);
		rcMargin.top = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.right = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.bottom = _tcstol(pstr + 1, &pstr, 10);
		control->SetMargin(rcMargin);
	}
	else if (name == L"text") {
		ui::Label* label = dynamic_cast<ui::Label*>(control);
		if (label) {
			label->SetText(value);
			return;
		}
		ui::RichEdit* richEdit = dynamic_cast<ui::RichEdit*>(control);
		if (richEdit) {
			richEdit->SetText(value);
			return;
		}
		ui::Button* btn = dynamic_cast<ui::Button*>(control);
		if (btn) {
			btn->SetText(value);
			return;
		}
	}
}