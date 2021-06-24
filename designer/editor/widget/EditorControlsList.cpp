#include "../stdafx.h"
#include "EditorControlsList.h"

EditorControlsList::EditorControlsList()
{
}


EditorControlsList::~EditorControlsList()
{
}

void EditorControlsList::LoadData(std::vector<DrawControl> controls)
{
	for (auto it = controls.begin(); it != controls.end(); ++it) {
		ui::HBox* hBox = new ui::HBox;
		hBox->AttachButtonDown(nbase::Bind(&EditorControlsList::OnButtonDown, this, std::placeholders::_1));
		hBox->AttachButtonUp(nbase::Bind(&EditorControlsList::OnButtonUp, this, std::placeholders::_1));
		hBox->SetDataID(nbase::IntToString16(it->id));
		hBox->SetFixedHeight(30);
		this->Add(hBox);
		ui::Label* lbTitle = new ui::Label;
		lbTitle->SetMouseEnabled(false);
		hBox->Add(lbTitle);
		lbTitle->SetText(it->name);
	}
}

bool EditorControlsList::OnButtonDown(ui::EventArgs* args)
{
	if (_select_callback) {
		int id = -1;
		nbase::StringToInt(args->pSender->GetDataID(), &id);
		_select_callback(id);
	}
	return true;
}

bool EditorControlsList::OnButtonUp(ui::EventArgs* args)
{
	if (_select_callback) {
		_select_callback(-1);
	}
	return true;
}