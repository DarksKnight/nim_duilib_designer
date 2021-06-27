#pragma once

class PropertyItem : public ui::ListContainerElement
{
public:
	PropertyItem(PropertyData data);
	~PropertyItem();
public:
	void InitCtrls();
public:
	std::wstring GetDataName() {
		return _name;
	}
	void SetValue(const std::wstring& value) {
		_re_value->SetText(value);
	}
	std::wstring GetValue() {
		return _re_value->GetText();
	}
private:
	bool OnKillFocus(ui::EventArgs* args);
	bool OnTapReturn(ui::EventArgs* args);
private:
	void ChangeProperty();
private:
	ui::Label* _lb_desc;
	ui::RichEdit* _re_value;
private:
	std::wstring _name = L"";
};