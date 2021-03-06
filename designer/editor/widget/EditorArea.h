#pragma once
#include "../controls/AreaBox.h"
#include "../controls/AreaWindow.h"

#define PADDING 10

class EditorArea : public ui::Box
{
public:
	typedef std::function<void(ui::Control* control)> SelectItemCallback;
public:
	EditorArea();
	~EditorArea();
public:
	AreaControlDelegate* DropControl(const std::wstring& name);
	void DropControl(ui::Control* control);
	void RemoveSelectItem();
	ui::Control* FindSelectedItem(ui::Box* box);
	ui::Control* FindControlById(ui::Box* box, int id);
public:
	void SetSelectItemCallback(SelectItemCallback callback) {
		_select_item_callback = callback;
	}
	AreaWindow* GetAreaWindow() {
		return (AreaWindow*)GetItemAt(0);
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