#pragma once
#include "../stdafx.h"
#include "base/memory/singleton.h"

#define XML_HEADER "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

#define CONFIG_TAG_CREATE L"CreateForm"
#define CONFIG_KEY_CREATE_SHOW L"Show"
#define CONFIG_KEY_GLOBAL_XML L"GlobalXmlPath"

#define ATTRIBUTE_MEMBER_FUNC(argType, name, arg)\
	public:\
	void Set##name(const argType& v) {\
	arg = v;\
	}\
	argType Get##name() {\
	return arg;\
	}

enum ThreadId
{
	kThreadUI,
	kThreadGlobalMisc,
	kThreadGlobalXmlDiff
};

enum ControlType
{
	Box = 0,
	HBox
}; 

enum PropertyInputType
{
	RICHEDIT, COMBO, FILEBUTTON, COLOR_BUTTON
};

enum CustomEventType
{
	UI_CHANGED = 0,
	CONTROL_BUTTON_DOWN,
	CONTROL_REMOVE,
	CONTROL_COPY,
	CONTROL_PASTE,
	CONTROL_SELECTED,
	CONTROL_SET_PROPERTY,
	SHOW_CLASS_PROPERTY_LIST,
	SHOW_FONT_PROPERTY_LIST,
	PROPERTY_ITEM_CLASS_TEXT_CHANGE,
	PROPERTY_ITEM_FONT_TEXT_CHANGE,
	HIDE_PROPERTY_LIST
};

struct CreateDataInfo
{
	std::wstring name = L"";
	std::wstring desc = L"";

	CreateDataInfo(std::wstring name, std::wstring desc) {
		this->name = name;
		this->desc = desc;
	}
};

struct ControlData
{
	std::wstring name = L"";
	std::wstring desc = L"";

	ControlData(){}

	ControlData(const std::wstring & name, const std::wstring & desc) {
		this->name = name;
		this->desc = desc;
	}
};

struct DirData
{
	std::wstring name = L"";
	std::wstring path = L"";

	DirData() {}

	DirData(const std::wstring& name, const std::wstring& path) {
		this->name = name;
		this->path = path;
	}
};

struct PropertyData
{
	std::wstring name = L"";
	std::wstring desc = L"";
	std::wstring defaultValue = L"";
	PropertyInputType inputType = RICHEDIT;
	std::vector<std::wstring> inputDatas;

	PropertyData(std::wstring name, std::wstring desc, std::wstring defaultValue = L"") {
		this->name = name;
		this->desc = desc;
		this->defaultValue = defaultValue;
	}

	PropertyData(std::wstring name, std::wstring desc, PropertyInputType type) {
		this->name = name;
		this->desc = desc;
		this->defaultValue = defaultValue;
		this->inputType = type;
	}

	PropertyData(std::wstring name, std::wstring desc, PropertyInputType type, std::vector<std::wstring> inputDatas, std::wstring defaultValue = L"") {
		this->name = name;
		this->desc = desc;
		this->defaultValue = defaultValue;
		this->inputType = type;
		this->inputDatas = inputDatas;
	}
};

class GlobalData
{
public:
	std::wstring static APPDATA_ROMAING;
	std::wstring static APPDATA_LOCAL;
};

class DelegateData : public ui::UserDataBase
{
	ATTRIBUTE_MEMBER_FUNC(int, Id, id);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Name, name);
	ATTRIBUTE_MEMBER_FUNC(int, Width, width);
	ATTRIBUTE_MEMBER_FUNC(int, Height, height);
	ATTRIBUTE_MEMBER_FUNC(ui::UiRect, Margin, margin);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Bkcolor, bkcolor);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Valign, valign);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Halign, halign);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, BkImage, bkimage);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Class, className);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Text, text);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Font, font);
	ATTRIBUTE_MEMBER_FUNC(std::wstring, Visible, visible);
	DelegateData() {}
	DelegateData(const DelegateData& data) {
		this->id = data.id;
		this->name = data.name;
		this->width = data.width;
		this->height = data.height;
		this->margin = data.margin;
		this->bkcolor = data.bkcolor;
		this->valign = data.valign;
		this->halign = data.halign;
		this->bkimage = data.bkimage;
		this->className = data.className;
		this->text = data.text;
		this->font = data.font;
		this->visible = data.visible;
	}
private:
	int id = 0;
	std::wstring name = L"";
	int width = -3;
	int height = -3;
	ui::UiRect margin;
	std::wstring bkcolor = L"";
	std::wstring valign = L"";
	std::wstring halign = L"";
	std::wstring bkimage = L"";
	std::wstring className = L"";
	std::wstring text = L"";
	std::wstring font = L"";
	std::wstring visible = L"";
};