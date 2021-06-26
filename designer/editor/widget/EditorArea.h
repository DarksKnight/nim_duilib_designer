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
	typedef std::function<void(ui::Control* control)> SelectItemCallback;
public:
	EditorArea();
	~EditorArea();
public:
	ui::Control* DropControl(ControlData* data);
public:
	WindowInfo GetWindowInfo() {
		return _window_info;
	}
	void SetSelectItemCallback(SelectItemCallback callback) {
		_select_item_callback = callback;
	}
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
	bool OnMouseEvent(ui::EventArgs* args);
private:
	ui::Box* FindParentBox(POINT pt);
	void SetUniversalData(ui::Control* control, ControlData* data);
	void Reset(ui::Control* control);
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
	SelectItemCallback _select_item_callback;
};

