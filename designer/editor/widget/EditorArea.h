#pragma once

#define PADDING 10

class EditorArea : public ui::Box
{
public:
	typedef std::function<void(ui::Control* control)> SelectItemCallback;
public:
	EditorArea();
	~EditorArea();
public:
	void DropControl(const std::wstring& name);
public:
	void SetSelectItemCallback(SelectItemCallback callback) {
		_select_item_callback = callback;
	}
private:
	bool Notify(ui::EventArgs* args);
private:
	ui::Box* FindParentBox(POINT pt);
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
	SelectItemCallback _select_item_callback;
};

