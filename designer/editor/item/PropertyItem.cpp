#include "../stdafx.h"
#include "PropertyItem.h"

PropertyItem::PropertyItem(PropertyData data)
{
	_name = data.name;
	ui::GlobalManager::FillBoxWithCache(this, L"layout/item_property.xml");
	_lb_desc = (ui::Label*)FindSubControl(L"lb_desc");
	_re_value = (ui::RichEdit*)FindSubControl(L"re_value");
	_lb_desc->SetText(data.desc + L"(" + data.name + L")");
	_re_value->SetText(data.defaultValue);
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