#include "../stdafx.h"
#include "EditorControlsList.h"
#include "../internal/ControlHelper.h"

EditorControlsList::EditorControlsList()
{
	std::vector<std::wstring> datas = ControlHelper::GetInstance()->GetControlList();
	for (auto it = datas.begin(); it != datas.end(); ++it) {
		ui::Box* boxContainer = new ui::Box;
		boxContainer->AttachButtonDown(nbase::Bind(&EditorControlsList::OnButtonDown, this, std::placeholders::_1));
		boxContainer->AttachButtonUp(nbase::Bind(&EditorControlsList::OnButtonUp, this, std::placeholders::_1));
		boxContainer->SetFixedHeight(30);
		boxContainer->SetBkColor(L"blue");
		boxContainer->SetDataID(*it);
		this->Add(boxContainer);
		ui::Label* lbTitle = new ui::Label;
		lbTitle->SetMouseEnabled(false);
		lbTitle->SetFixedWidth(DUI_LENGTH_AUTO);
		lbTitle->SetFixedHeight(DUI_LENGTH_AUTO);
		lbTitle->SetHorAlignType(ui::kHorAlignCenter);
		lbTitle->SetVerAlignType(ui::kVerAlignCenter);
		boxContainer->Add(lbTitle);
		lbTitle->SetText(*it);
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
		_select_callback(args->pSender->GetDataID());
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