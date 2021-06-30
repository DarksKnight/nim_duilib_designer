#pragma once

#define PADDING 10

class AreaControlDelegate: public nbase::SupportWeakCallback
{
public:
	AreaControlDelegate(ui::Control* control);
	~AreaControlDelegate();
public:
	void ParseElement(tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* GetElement(tinyxml2::XMLDocument* doc);
	void Reset();
	void Remove();
public:
	virtual std::wstring GetControlName() {
		return DUI_CTR_CONTROL;
	}
	virtual void SetDropUIMargin(POINT pt, AreaControlDelegate* target) {
		ui::UiRect margin(pt.x - _control->GetPos().left, pt.y - _control->GetPos().top, 0, 0);
		target->SetUIMargin(margin);
	}
	std::vector<PropertyData> GetBasicProperty() {
		return _basic_property;
	}
	std::vector<PropertyData> GetExtProperty() {
		return _ext_property;
	}
	void SetMove(bool value) {
		_can_move = value;
	}
	void SetShowMenu(bool value) {
		_show_menu = value;
	}
	void SetUIMargin(ui::UiRect margin) {
		_control->SetMargin(margin);
	}
	void SetControlName(const std::wstring & name) {
		_control->SetName(name);
	}
	ui::Control* GetCtonrol() {
		return _control;
	}
	bool IsSelected() {
		return _selected;
	}
protected:
	virtual void OnParseElement(tinyxml2::XMLElement* element) {}
	virtual void OnGetElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* element) {}
	virtual void OnItemMenu() {}
protected:
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
	ui::Control* FindPreControl(ui::Control* control) {
		ui::Control* preCtrl = NULL;
		ui::Box* box = control->GetParent();
		if (!box) {
			return NULL;
		}
		for (int i = 0; i < box->GetCount(); i++) {
			if (box->GetItemAt(i) == control) {
				return preCtrl;
			}
			preCtrl = box->GetItemAt(i);
		}
		return NULL;
	}
protected:
	nim_comp::CMenuElementUI* _menu_delete;
	nim_comp::CMenuElementUI* _menu_copy;
	nim_comp::CMenuElementUI* _menu_paste;
	ui::Control* _control = NULL;
	std::vector<PropertyData> _basic_property;
	std::vector<PropertyData> _ext_property;
private:
	bool OnButtonDown(ui::EventArgs* args);
	bool OnButtonUp(ui::EventArgs* args);
	bool Notify(ui::EventArgs* args);
	bool OnItemMenu(ui::EventArgs* args);
	bool OnItemMenuCopy(ui::EventArgs* args);
	bool OnItemMenuPaste(ui::EventArgs* args);
	bool OnItemMenuDelete(ui::EventArgs* args);
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
	bool _selected = false;
	bool _is_button_down = false;
	Direction _current_direction = Direction::NONE;
	POINT _last_point;
	bool _can_move = true;
	bool _show_menu = true;
};