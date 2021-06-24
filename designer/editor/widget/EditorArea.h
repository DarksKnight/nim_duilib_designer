#pragma once

class EditorArea : public ui::Box
{
public:
	EditorArea();
	~EditorArea();
private:
	bool OnButtonUp(ui::EventArgs* args);
};

