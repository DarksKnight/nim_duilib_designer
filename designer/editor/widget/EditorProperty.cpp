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
	DelegateData* data = (DelegateData*)control->GetUserDataBase();
	SetProperty(L"class", data->GetClass());
	SetProperty(L"name", data->GetName());
	int width = data->GetWidth();
	std::wstring widthValue = L"";
	if (width == DUI_LENGTH_AUTO) {
		widthValue = L"auto";
	}
	else if (width == DUI_LENGTH_STRETCH) {
		widthValue = L"stretch";
	}
	else {
		widthValue = nbase::IntToString16(width);
	}
	SetProperty(L"width", widthValue);
	int height = data->GetHeight();
	std::wstring heightValue = L"";
	if (height == DUI_LENGTH_AUTO) {
		heightValue = L"auto";
	}
	else if (height == DUI_LENGTH_STRETCH) {
		heightValue = L"stretch";
	}
	else {
		heightValue = nbase::IntToString16(height);
	}
	SetProperty(L"height", heightValue);
	ui::UiRect margin = data->GetMargin();
	SetProperty(L"margin", nbase::StringPrintf(L"%d,%d,%d,%d", margin.left, margin.top, margin.right, margin.bottom));
	SetProperty(L"bkcolor", data->GetBkcolor());
	SetProperty(L"bkimage", data->GetBkImage());
	SetProperty(L"valign", data->GetValign());
	SetProperty(L"halign", data->GetHalign());
	SetProperty(L"text", data->GetText());
}

void EditorProperty::SetProperty(const std::wstring& name, const std::wstring& value)
{
	for (int i = 0; i < _list_propery->GetCount(); i++) {
		PropertyItem* item = (PropertyItem*)_list_propery->GetItemAt(i);
		if (item->GetDataName() == name) {
			item->SetValue(value);
			GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::UI_CHANGED);
			break;
		}
	}
}