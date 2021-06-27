#pragma once

class EditorProperty : public ui::Box
{
public:
	EditorProperty();
	~EditorProperty();
public:
	void LoadControlProperty(ui::Control* control);
private:
	void LoadBasicProperty();
	void SetProperty(const std::wstring & name, const std::wstring & value);
private:
	ui::ListBox* _list_propery;
};

