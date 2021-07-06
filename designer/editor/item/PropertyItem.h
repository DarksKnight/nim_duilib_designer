#pragma once

class PropertyItem : public ui::ListContainerElement
{
public:
	PropertyItem(PropertyData data);
	~PropertyItem();
public:
	void InitCtrls();
	void SetValue(const std::wstring& value);
	std::wstring GetValue();
public:
	std::wstring GetDataName() {
		return _data.name;
	}
private:
	bool OnKillFocus(ui::EventArgs* args);
	bool OnTapReturn(ui::EventArgs* args);
	bool OnComboClick(ui::EventArgs* args);
	bool OnComboItemClick(ui::EventArgs* args);
private:
	void ChangeProperty();
private:
	ui::TabBox* _tb_input;
	ui::Label* _combo_value;
	ui::Label* _lb_desc;
	ui::RichEdit* _re_value;
	nim_comp::CMenuWnd* _combo_menu;
private:
	PropertyData _data;
};