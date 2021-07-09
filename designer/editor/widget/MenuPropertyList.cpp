#include "../stdafx.h"
#include "MenuPropertyList.h"

MenuPropertyList::MenuPropertyList()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/menu_property_list.xml");
	_list_property = (ui::ListBox*)FindSubControl(L"list_property");
	_list_property->AttachSelect(nbase::Bind(&MenuPropertyList::OnSelect, this, std::placeholders::_1));
}


MenuPropertyList::~MenuPropertyList()
{
}

void MenuPropertyList::LoadClassData(const std::wstring& key, std::map<std::wstring, Class> classes)
{
	_key = key;
	for (auto it = classes.begin(); it != classes.end(); ++it) {
		ui::ListContainerElement* element = new ui::ListContainerElement;
		element->SetMouseChildEnabled(false);
		element->SetDataID(it->second.name);
		element->SetClass(L"listitem");
		element->SetFixedHeight(30);
		ui::Label* label = new ui::Label;
		element->Add(label);
		label->SetText(it->second.name);
		label->SetVerAlignType(ui::kVerAlignCenter);
		label->SetMargin(ui::UiRect(2, 0, 0, 0));
		_list_property->Add(element);
	}
}

bool MenuPropertyList::OnSelect(ui::EventArgs* args)
{
	if (_select_callback) {
		ui::ListContainerElement* item = (ui::ListContainerElement*)((ui::ListBox*)args->pSender)->GetItemAt(args->wParam);
		_select_callback(_key, item->GetDataID());
	}
	return true;
}