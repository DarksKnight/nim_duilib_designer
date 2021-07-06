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
		_combo_value = (ui::Label*)FindSubControl(L"combo_value");
		_combo_value->AttachButtonDown(nbase::Bind(&PropertyItem::OnComboClick, this, std::placeholders::_1));
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
		_combo_value->SetText(value);
		break;
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

bool PropertyItem::OnComboClick(ui::EventArgs* args)
{
	if (_combo_menu) {
		_combo_menu->Close();
		_combo_menu = NULL;
		return true;
	}
	ui::UiRect rect = args->pSender->GetPos();
	ui::CPoint point(rect.left, rect.bottom);
	::ClientToScreen(GetWindow()->GetHWND(), &point);
	_combo_menu = new nim_comp::CMenuWnd(GetWindow()->GetHWND());
	ui::STRINGorID xml(L"../layout/menu_property_combo.xml");
	_combo_menu->Init(xml, _T("xml"), point);
	ui::ListBox* listMenu = (ui::ListBox*)_combo_menu->FindControl(L"listMenu");
	listMenu->AttachSelect(nbase::Bind(&PropertyItem::OnComboItemClick, this, std::placeholders::_1));
	for (auto it = _data.inputDatas.begin(); it != _data.inputDatas.end(); ++it) {
		ui::MenuElement* element = new ui::MenuElement;
		element->SetMouseChildEnabled(false);
		element->SetClass(L"menu_element");
		element->SetFixedWidth(args->pSender->GetWidth());
		element->SetFixedHeight(25);
		ui::Label* label = new ui::Label;
		label->SetFixedHeight(DUI_LENGTH_AUTO);
		label->SetVerAlignType(ui::kVerAlignCenter);
		label->SetText(*it);
		element->Add(label);
		listMenu->Add(element);
	}
	return true;
}

bool PropertyItem::OnComboItemClick(ui::EventArgs* args)
{
	_combo_value->SetText(_data.inputDatas[args->wParam]);
	_combo_menu->Close();
	_combo_menu = NULL;
	return true;
}

void PropertyItem::ChangeProperty()
{
	GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::CONTROL_SET_PROPERTY);
}