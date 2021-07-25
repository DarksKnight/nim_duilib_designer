#include "../stdafx.h"
#include "ImportItem.h"

ImportItem::ImportItem(const std::wstring& name, const std::wstring& path)
	:_name(name),
	_path(path)
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/item_import.xml");
	_lb_name = (ui::Label*)FindSubControl(L"lb_name");
	_lb_name->SetText(_name);
	_lb_path = (ui::Label*)FindSubControl(L"lb_path");
	_lb_path->SetText(_path);
}


ImportItem::~ImportItem()
{
}