#pragma once

class CreateDataItem : public ui::ListContainerElement
{
public:
	CreateDataItem(CreateDataInfo data);
	~CreateDataItem();
public:
	std::wstring GetDataName() {
		return _name;
	}
private:
	ui::Label* _lb_desc;
private:
	std::wstring _name = L"";
};