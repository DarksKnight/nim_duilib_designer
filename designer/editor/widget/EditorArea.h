#pragma once

#define PADDING 10

class EditorArea : public ui::Box
{
public:
	struct WindowInfo
	{
		int width = 500;
		int height = 500;
	};
public:
	EditorArea();
	~EditorArea();
public:
	ui::Box* DropControl(ControlData* data);
public:
	WindowInfo GetWindowInfo() {
		return _window_info;
	}
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
	bool OnMouseEvent(ui::EventArgs* args);
private:
	ui::Box* FindParentBox(POINT pt);
	void SetUniversalData(ui::Control* control, ControlData* data);
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
	WindowInfo _window_info;
};

