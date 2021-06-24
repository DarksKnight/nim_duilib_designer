#include "../stdafx.h"
#include "EditorArea.h"

EditorArea::EditorArea()
{
	AttachButtonUp(nbase::Bind(&EditorArea::OnButtonUp, this, std::placeholders::_1));
}


EditorArea::~EditorArea()
{
}

bool EditorArea::OnButtonUp(ui::EventArgs* args)
{
	return true;
}