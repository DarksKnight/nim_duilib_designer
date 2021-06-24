#include "../stdafx.h"
#include "EditorDrawBox.h"

EditorDrawBox::EditorDrawBox()
{
	AttachButtonUp(nbase::Bind(&EditorDrawBox::OnButtonUp, this, std::placeholders::_1));
}


EditorDrawBox::~EditorDrawBox()
{
}

bool EditorDrawBox::OnButtonUp(ui::EventArgs* args)
{
	ui::HBox* box = new ui::HBox;
	box->SetName(L"hbox2");
	box->SetFixedWidth(400);
	box->SetFixedHeight(400);
	box->SetBorderSize(1);
	box->SetBorderColor(L"black");
	this->Add(box);
	return true;
}