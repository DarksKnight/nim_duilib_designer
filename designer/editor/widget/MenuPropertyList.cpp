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

void MenuPropertyList::Show(const std::wstring& type)
{
	_type = type;
	SetVisible(true);
}

void MenuPropertyList::Hide()
{
	_list_property->RemoveAll();
	SetVisible(false);
}

void MenuPropertyList::LoadClassData(std::vector<std::wstring> classes, const std::wstring& keyword)
{
	_list_property->RemoveAll();
	for (auto it = classes.begin(); it != classes.end(); ++it) {
		std::wstring classStr = *it;
		if (!keyword.empty() && classStr.find(keyword) == std::wstring::npos) {
			continue;
		}
		ui::ListContainerElement* element = new ui::ListContainerElement;
		element->SetMouseChildEnabled(false);
		element->SetDataID(classStr);
		element->SetClass(L"listitem");
		element->SetFixedHeight(30);
		ui::Label* label = new ui::Label;
		element->Add(label);
		label->SetText(classStr);
		label->SetVerAlignType(ui::kVerAlignCenter);
		label->SetMargin(ui::UiRect(2, 0, 0, 0));
		_list_property->Add(element);
	}
}

void MenuPropertyList::LoadFontData(std::vector<std::wstring> fonts, const std::wstring& keyword)
{
	for (auto it = fonts.begin(); it != fonts.end(); ++it) {
		std::wstring fontStr = *it;
		if (!keyword.empty() && fontStr.find(keyword) == std::wstring::npos) {
			continue;
		}
		ui::ListContainerElement* element = new ui::ListContainerElement;
		element->SetMouseChildEnabled(false);
		element->SetDataID(fontStr);
		element->SetClass(L"listitem");
		element->SetFixedHeight(30);
		ui::Label* label = new ui::Label;
		element->Add(label);
		label->SetText(fontStr);
		label->SetVerAlignType(ui::kVerAlignCenter);
		label->SetMargin(ui::UiRect(2, 0, 0, 0));
		_list_property->Add(element);
	}
}

bool MenuPropertyList::OnSelect(ui::EventArgs* args)
{
	if (_select_callback) {
		ui::ListContainerElement* item = (ui::ListContainerElement*)((ui::ListBox*)args->pSender)->GetItemAt(args->wParam);
		_select_callback(_type, item->GetDataID());
	}
	return true;
}