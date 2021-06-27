#include "../stdafx.h"
#include "EditorControlsList.h"
#include "../internal/ControlHelper.h"

EditorControlsList::EditorControlsList()
{
	_datas = ControlHelper::GetInstance()->GetControlList();
	for (auto it = _datas.begin(); it != _datas.end(); ++it) {
		ui::ListContainerElement* containerElement = new ui::ListContainerElement;
		containerElement->SetMargin(ui::UiRect(1, 1, 1, 1));
		containerElement->SetClass(L"listitem");
		containerElement->AttachButtonDown(nbase::Bind(&EditorControlsList::OnButtonDown, this, std::placeholders::_1));
		containerElement->AttachButtonUp(nbase::Bind(&EditorControlsList::OnButtonUp, this, std::placeholders::_1));
		containerElement->SetFixedHeight(30);
		this->Add(containerElement);
		ui::Label* lbTitle = new ui::Label;
		lbTitle->SetMouseEnabled(false);
		lbTitle->SetFixedWidth(DUI_LENGTH_AUTO);
		lbTitle->SetFixedHeight(DUI_LENGTH_AUTO);
		lbTitle->SetVerAlignType(ui::kVerAlignCenter);
		lbTitle->SetMargin(ui::UiRect(12, 0, 0, 0));
		containerElement->Add(lbTitle);
		lbTitle->SetText(it->desc + L"(" + it->name + L")");
	}
}


EditorControlsList::~EditorControlsList()
{
}

void EditorControlsList::LoadData()
{
	
}

bool EditorControlsList::OnButtonDown(ui::EventArgs* args)
{
	if (_select_callback) {
		_select_callback(_datas[args->wParam].name);
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