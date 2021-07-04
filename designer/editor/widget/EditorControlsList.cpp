#include "../stdafx.h"
#include "EditorControlsList.h"

EditorControlsList::EditorControlsList()
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/box_control_list.xml");
	_datas = ControlHelper::GetInstance()->GetControlList();
	_list_control = (ui::VirtualListBox*)FindSubControl(L"list_control");
	_list_control->SetElementHeight(30);
	_list_control->SetDataProvider(this);
	_list_control->InitElement(_datas.size());
	_re_search = (ui::RichEdit*)FindSubControl(L"re_search");
	_re_search->AttachTextChange(nbase::Bind(&EditorControlsList::OnSearchTextChanged, this, std::placeholders::_1));
}

EditorControlsList::~EditorControlsList()
{
}

ui::Control* EditorControlsList::CreateElement()
{
	ui::ListContainerElement* item = (ui::ListContainerElement*)ui::GlobalManager::CreateBoxWithCache(L"layout/item_control_list.xml");
	return item;
}

void EditorControlsList::FillElement(ui::Control* control, int index)
{
	ui::ListContainerElement* item = (ui::ListContainerElement*)control;
	item->AttachButtonDown(nbase::Bind(&EditorControlsList::OnButtonDown, this, std::placeholders::_1));
	item->AttachButtonUp(nbase::Bind(&EditorControlsList::OnButtonUp, this, std::placeholders::_1));
	ui::Label* lbDesc = (ui::Label*)item->FindSubControl(L"lb_desc");
	lbDesc->SetText(_datas[index].desc + L"(" + _datas[index].name + L")");
}

bool EditorControlsList::OnButtonDown(ui::EventArgs* args)
{
	ui::ListContainerElement* element = (ui::ListContainerElement*)args->pSender;
	if (_select_callback) {
		_select_callback(_datas[element->GetIndex()].name);
	}
	return true;
}

bool EditorControlsList::OnButtonUp(ui::EventArgs* args)
{
	if (_button_up_callback) {
		_button_up_callback();
	}
	return true;
}

bool EditorControlsList::OnSearchTextChanged(ui::EventArgs* args)
{
	std::wstring key = _re_search->GetText();
	nbase::LowerString(key);
	_datas.clear();
	std::vector<ControlData> orgDatas = ControlHelper::GetInstance()->GetControlList();
	for (auto it = orgDatas.begin(); it != orgDatas.end(); ++it) {
		std::wstring name = it->name;
		nbase::LowerString(name);
		std::wstring desc = it->desc;
		nbase::LowerString(desc);
		if (name.find(key) != std::wstring::npos || desc.find(key) != std::wstring::npos) {
			_datas.push_back(*it);
		}
	}
	_list_control->Refresh();
	return true;
}