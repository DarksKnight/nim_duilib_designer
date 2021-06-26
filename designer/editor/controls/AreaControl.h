#pragma once

#define PADDING 10

class AreaControl: nbase::SupportWeakCallback
{
public:
	AreaControl(ui::Control* control);
	~AreaControl();
public:
	void ParseElement(tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* GetElement(tinyxml2::XMLDocument* doc);
public:
	void SetButtonDownCallback(StdClosure callback) {
		_button_down_callback = callback;
	}
	void SetMove(bool value) {
		_can_move = value;
	}
	void SetShowMenu(bool value) {
		_show_menu = value;
	}
protected:
	virtual std::wstring GetControlName() = 0;
protected:
	virtual void OnParseElement(tinyxml2::XMLElement* element) {}
	virtual void OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element) {}
	virtual void OnItemMenu() {}
protected:
	nim_comp::CMenuElementUI* _menu_delete;
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
	bool OnMouseEvent(ui::EventArgs* args);
	bool OnItemMenu(ui::EventArgs* args);
	bool OnItemMenuDelete(ui::EventArgs* args);
private:
	bool CheckRectEmpty(ui::UiRect rect) {
		return rect.left == 0 && rect.top == 0 && rect.right == 0 && rect.bottom == 0;
	}
	bool CheckWidthAndHeight(int value) {
		return value < 0;
	}
	std::vector<std::string> ConvertVector(std::list<std::string> list) {
		std::vector<std::string> vector;
		for (auto it = list.begin(); it != list.end(); ++it) {
			vector.push_back(*it);
		}
		return vector;
	}
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
	bool _is_button_down = false;
	Direction _current_direction = Direction::NONE;
	POINT _last_point;
	StdClosure _button_down_callback;
	bool _can_move = true;
	ui::Control* _control = NULL;
	bool _show_menu = true;
};