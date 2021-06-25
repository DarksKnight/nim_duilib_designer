#include "../stdafx.h"
#include "EditorControlsList.h"

EditorControlsList::EditorControlsList()
{
}


EditorControlsList::~EditorControlsList()
{
}

void EditorControlsList::LoadData(std::vector<ControlData*> datas)
{
	_datas = datas;
	for (auto it = datas.begin(); it != datas.end(); ++it) {
		ui::Box* boxContainer = new ui::Box;
		boxContainer->AttachButtonDown(nbase::Bind(&EditorControlsList::OnButtonDown, this, std::placeholders::_1));
		boxContainer->AttachButtonUp(nbase::Bind(&EditorControlsList::OnButtonUp, this, std::placeholders::_1));
		boxContainer->SetFixedHeight(30);
		boxContainer->SetBkColor(L"blue");
		boxContainer->SetDataID((*it)->name);
		this->Add(boxContainer);
		ui::Label* lbTitle = new ui::Label;
		lbTitle->SetMouseEnabled(false);
		lbTitle->SetFixedWidth(DUI_LENGTH_AUTO);
		lbTitle->SetFixedHeight(DUI_LENGTH_AUTO);
		lbTitle->SetHorAlignType(ui::kHorAlignCenter);
		lbTitle->SetVerAlignType(ui::kVerAlignCenter);
		boxContainer->Add(lbTitle);
		lbTitle->SetText((*it)->name);
	}
}

bool EditorControlsList::OnButtonDown(ui::EventArgs* args)
{
	if (_select_callback) {
		for (auto it = _datas.begin(); it != _datas.end(); ++it) {
			if ((*it)->name == args->pSender->GetDataID()) {
				_select_callback(*it);
				return true;
			}
		}
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