#pragma once

class ImportItem : public ui::ListContainerElement
{
public:
	ImportItem(const std::wstring & name, const std::wstring & path);
	~ImportItem();
public:
	std::wstring GetPath() {
		return _path;
	}
private:
	ui::Label* _lb_name;
	ui::Label* _lb_path;
private:
	std::wstring _name;
	std::wstring _path;
};