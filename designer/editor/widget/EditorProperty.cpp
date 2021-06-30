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

void EditorProperty::LoadProperty(const std::wstring& name, AreaControlDelegate* delegate)
{
	if (_current_name == name 
		&& _basic_property.size() == delegate->GetBasicProperty().size() 
		&& _ext_property.size() == delegate->GetExtProperty().size()) {
		return;
	}
	_current_name = name;
	_basic_property = delegate->GetBasicProperty();
	_ext_property = delegate->GetExtProperty();
	_list_propery->RemoveAll();
	std::vector<PropertyData> tempProperty;
	tempProperty.insert(tempProperty.end(), _basic_property.begin(), _basic_property.end());
	tempProperty.insert(tempProperty.end(), _ext_property.begin(), _ext_property.end());
	for (auto it = tempProperty.begin(); it != tempProperty.end(); ++it) {
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
	ui::Label* label = dynamic_cast<ui::Label*>(control);
	if (label) SetProperty(L"text", label->GetText());
	ui::RichEdit* richEdit = dynamic_cast<ui::RichEdit*>(control);
	if (richEdit) SetProperty(L"text", richEdit->GetText());
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