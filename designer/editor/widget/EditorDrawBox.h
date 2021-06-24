#pragma once

class EditorDrawBox : public ui::Box
{
public:
	EditorDrawBox();
	~EditorDrawBox();
private:
	bool OnButtonUp(ui::EventArgs* args);
};

