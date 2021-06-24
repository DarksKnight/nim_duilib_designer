#include "../stdafx.h"
#include "EditorControlsList.h"

EditorControlsList::EditorControlsList()
{
}


EditorControlsList::~EditorControlsList()
{
}

void EditorControlsList::LoadData(std::map<int, DrawControl> controls)
{
	_controls = controls;
	for (auto it = controls.begin(); it != controls.end(); ++it) {
		ui::Box* boxContainer = new ui::Box;
		boxContainer->AttachButtonDown(nbase::Bind(&EditorControlsList::OnButtonDown, this, std::placeholders::_1));
		boxContainer->AttachButtonUp(nbase::Bind(&EditorControlsList::OnButtonUp, this, std::placeholders::_1));
		boxContainer->SetDataID(nbase::IntToString16(it->second.id));
		boxContainer->SetFixedHeight(30);
		boxContainer->SetBkColor(L"blue");
		this->Add(boxContainer);
		ui::Label* lbTitle = new ui::Label;
		lbTitle->SetMouseEnabled(false);
		lbTitle->SetFixedWidth(DUI_LENGTH_AUTO);
		lbTitle->SetFixedHeight(DUI_LENGTH_AUTO);
		lbTitle->SetHorAlignType(ui::kHorAlignCenter);
		lbTitle->SetVerAlignType(ui::kVerAlignCenter);
		boxContainer->Add(lbTitle);
		lbTitle->SetText(it->second.name);
	}
}

bool EditorControlsList::OnButtonDown(ui::EventArgs* args)
{
	if (_select_callback) {
		int id = -1;
		nbase::StringToInt(args->pSender->GetDataID(), &id);
		auto it = _controls.find(id);
		if (it != _controls.end()) {
			_select_callback(it->second);
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