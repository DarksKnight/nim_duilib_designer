#include "../stdafx.h"
#include "PropertyItem.h"

PropertyItem::PropertyItem(PropertyData data):_data(data)
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/item_property.xml");
	_lb_desc = (ui::Label*)FindSubControl(L"lb_desc");
	_lb_desc->SetText(data.desc + L"(" + data.name + L")");
	_tb_input = (ui::TabBox*)FindSubControl(L"tb_input");
	switch (data.inputType)
	{
	case RICHEDIT:
	{
		_tb_input->SelectItem(0);
		_re_value = (ui::RichEdit*)FindSubControl(L"re_value");
		_re_value->AttachKillFocus(nbase::Bind(&PropertyItem::OnKillFocus, this, std::placeholders::_1));
		_re_value->AttachReturn(nbase::Bind(&PropertyItem::OnTapReturn, this, std::placeholders::_1));
		_re_value->SetText(data.defaultValue);
		break;
	}
	case COMBO:
	{
		_tb_input->SelectItem(1);
		_combo_value = (ui::Combo*)FindSubControl(L"combo_value");
		for (auto it = data.inputDatas.begin(); it != data.inputDatas.end(); ++it) {
			ui::ListContainerElement* label = new ui::ListContainerElement;
			label->SetText(*it);
			label->SetTextPadding(ui::UiRect(5, 0, 0, 0));
			_combo_value->Add(label);
		}
		_combo_value->SelectItem(0);
		break;
	}
	default:
		break;
	}
}


PropertyItem::~PropertyItem()
{
}

void PropertyItem::InitCtrls()
{
	int index = GetIndex();
	if (index % 2 == 0) {
		SetBkColor(L"bk_property_item_dark");
	}
	else {
		SetBkColor(L"bk_property_item_light");
	}
}

void PropertyItem::SetValue(const std::wstring& value)
{
	switch (_tb_input->GetCurSel())
	{
	case 0:
		_re_value->SetText(value);
		break;
	case 1:
	{
		for (int i = 0; i < _data.inputDatas.size(); i++) {
			if (_data.inputDatas[i] == value) {
				_combo_value->SelectItem(i);
			}
		}
		break;
	}
	default:
		break;
	}
}

std::wstring PropertyItem::GetValue()
{
	switch (_tb_input->GetCurSel())
	{
	case 0:
		return _re_value->GetText();
	case 1:
		return _combo_value->GetText();
	default:
		break;
	}
	return L"";
}

bool PropertyItem::OnKillFocus(ui::EventArgs* args)
{
	ChangeProperty();
	return true;
}

bool PropertyItem::OnTapReturn(ui::EventArgs* args)
{
	ChangeProperty();
	return true;
}

void PropertyItem::ChangeProperty()
{
	GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::CONTROL_SET_PROPERTY);
}