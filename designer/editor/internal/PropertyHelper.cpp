#include "../stdafx.h"
#include "PropertyHelper.h"
#include "GlobalXmlHelper.h"

PropertyHelper::PropertyHelper()
{
}


PropertyHelper::~PropertyHelper()
{
}

void PropertyHelper::SetProperty(ui::Control* control, const std::wstring& name, const std::wstring& value)
{
	if (value.empty()) {
		return;
	}
	DelegateData* data = (DelegateData*)control->GetUserDataBase();
	if (name == L"name") {
		data->SetName(value);
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
		data->SetWidth(width);
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
		data->SetHeight(height);
	}
	else if (name == L"margin") {
		ui::UiRect rcMargin;
		LPTSTR pstr = NULL;
		rcMargin.left = _tcstol(value.c_str(), &pstr, 10);
		rcMargin.top = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.right = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.bottom = _tcstol(pstr + 1, &pstr, 10);
		control->SetMargin(rcMargin);
		data->SetMargin(rcMargin);
	}
	else if (name == L"text") {
		data->SetText(value);
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
	else if (name == L"class") {
		std::wstring pDefaultAttributes = ui::GlobalManager::GetClassAttributes(value);
		if (!pDefaultAttributes.empty()) {
			control->SetClass(value);
			data->SetClass(value);
		}
	}
	else if (name == L"bkcolor") {
		control->SetBkColor(value);
		data->SetBkcolor(value);
	}
	else if (name == L"valign") {
		if (value == L"top") {
			control->SetVerAlignType(ui::kVerAlignTop);
		}
		else if (value == L"center") {
			control->SetVerAlignType(ui::kVerAlignCenter);
		}
		else {
			control->SetVerAlignType(ui::kVerAlignBottom);
		}
		data->SetValign(value);
	}
	else if (name == L"halign") {
		if (value == L"left") {
			control->SetHorAlignType(ui::kHorAlignLeft);
		}
		else if (value == L"center") {
			control->SetHorAlignType(ui::kHorAlignCenter);
		}
		else {
			control->SetHorAlignType(ui::kHorAlignRight);
		}
		data->SetHalign(value);
	}
	else if (name == L"bkimage") {
		control->SetBkImage(value);
		data->SetBkImage(value);
	}
	else if (name == L"font") {
		data->SetFont(value);
		ui::Label* label = dynamic_cast<ui::Label*>(control);
		if (label) {
			label->SetFont(value);
			return;
		}
		ui::RichEdit* richEdit = dynamic_cast<ui::RichEdit*>(control);
		if (richEdit) {
			richEdit->SetFont(value);
			return;
		}
		ui::Button* btn = dynamic_cast<ui::Button*>(control);
		if (btn) {
			btn->SetFont(value);
			return;
		}
	}
}