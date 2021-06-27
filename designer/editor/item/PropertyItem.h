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
private:
	ui::Label* _lb_desc;
	ui::RichEdit* _re_value;
private:
	std::wstring _name = L"";
};