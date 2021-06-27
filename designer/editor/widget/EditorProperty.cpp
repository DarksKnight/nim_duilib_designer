#include "../stdafx.h"
#include "EditorProperty.h"
#include "../item/PropertyItem.h"
#include "../internal/PropertyHelper.h"

EditorProperty::EditorProperty()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_property.xml");
	_list_propery = (ui::ListBox*)FindSubControl(L"list_propery");
}


EditorProperty::~EditorProperty()
{
}

void EditorProperty::LoadProperty(const std::wstring& name, const std::vector<PropertyData> & datas)
{
	if (_current_name == name && _current_datas.size() == datas.size()) {
		return;
	}
	_current_name = name;
	_current_datas = datas;
	_list_propery->RemoveAll();
	for (auto it = datas.begin(); it != datas.end(); ++it) {
		PropertyItem* item = new PropertyItem(*it);
		_list_propery->Add(item);
		item->InitCtrls();
	}
}

void EditorProperty::LoadControlProperty(ui::Control* control)
{
	SetProperty(L"name", control->GetName());
	SetProperty(L"width", nbase::IntToString16(control->GetFixedWidth()));
	SetProperty(L"height", nbase::IntToString16(control->GetFixedHeight()));
	ui::UiRect margin = control->GetMargin();
	SetProperty(L"margin", nbase::StringPrintf(L"%d,%d,%d,%d", margin.left, margin.top, margin.right, margin.bottom));
}

void EditorProperty::SetProperty(const std::wstring& name, const std::wstring& value)
{
	for (int i = 0; i < _list_propery->GetCount(); i++) {
		PropertyItem* item = (PropertyItem*)_list_propery->GetItemAt(i);
		if (item->GetDataName() == name) {
			item->SetValue(value);
			break;
		}
	}
}