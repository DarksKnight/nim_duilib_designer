#pragma once

#define PADDING 8

class EditorArea : public ui::Box
{
public:
	EditorArea();
	~EditorArea();
public:
	void DropControl(DrawControl control);
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
	bool OnMouseEvent(ui::EventArgs* args);
private:
	ui::Box* FindParentBox(POINT pt);
private:
	enum class Direction
	{
		NONE,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};
private:
	POINT _last_point;
	Direction _current_direction = Direction::NONE;
};

