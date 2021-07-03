#include "../stdafx.h"
#include "CreateDataItem.h"

CreateDataItem::CreateDataItem(CreateDataInfo data)
{
	_name = data.name;
	ui::GlobalManager::FillBoxWithCache(this, L"layout/item_create_data.xml");
	_lb_desc = (ui::Label*)FindSubControl(L"lb_desc");
	_lb_desc->SetText(data.desc);
}


CreateDataItem::~CreateDataItem()
{
}