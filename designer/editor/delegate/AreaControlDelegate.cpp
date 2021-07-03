﻿#include "../stdafx.h"
#include "AreaControlDelegate.h"

AreaControlDelegate::AreaControlDelegate(ui::Control* control):_control(control)
{
	_control->AttachButtonDown(nbase::Bind(&AreaControlDelegate::OnButtonDown, this, std::placeholders::_1));
	_control->AttachButtonUp(nbase::Bind(&AreaControlDelegate::OnButtonUp, this, std::placeholders::_1));
	_control->AttachAllEvents(nbase::Bind(&AreaControlDelegate::Notify, this, std::placeholders::_1));
	_basic_property.push_back(PropertyData(L"name", L"名称"));
	_basic_property.push_back(PropertyData(L"width", L"宽度"));
	_basic_property.push_back(PropertyData(L"height", L"高度"));
	_basic_property.push_back(PropertyData(L"margin", L"外边距"));
}

AreaControlDelegate::~AreaControlDelegate()
{
}

void AreaControlDelegate::ParseElement(tinyxml2::XMLElement* element)
{
	const tinyxml2::XMLAttribute* attr = NULL;
	if (attr = element->FindAttribute("name")) {
		_control->SetName(nbase::UTF8ToUTF16(attr->Value()));
	}
	if (attr = element->FindAttribute("width")) {
		std::wstring widthAttr = nbase::UTF8ToUTF16(attr->Value());
		int width = 0;
		if (widthAttr == L"auto") {
			width = DUI_LENGTH_AUTO;
		}
		else if (widthAttr == L"stretch") {
			width = DUI_LENGTH_STRETCH;
		}
		else {
			nbase::StringToInt(widthAttr, &width);
		}
		_control->SetFixedWidth(width);
	}
	else {
		_control->SetFixedWidth(DUI_LENGTH_STRETCH);
	}
	if (attr = element->FindAttribute("height")) {
		std::wstring heightAttr = nbase::UTF8ToUTF16(attr->Value());
		int height = 0;
		if (heightAttr == L"auto") {
			height = DUI_LENGTH_AUTO;
		}
		else if (heightAttr == L"stretch") {
			height = DUI_LENGTH_STRETCH;
		}
		else {
			nbase::StringToInt(heightAttr, &height);
		}
		_control->SetFixedHeight(height);
	}
	else {
		_control->SetFixedHeight(DUI_LENGTH_STRETCH);
	}
	if (attr = element->FindAttribute("margin")) {
		std::wstring marginAttr = nbase::UTF8ToUTF16(attr->Value());
		ui::UiRect rcMargin;
		LPTSTR pstr = NULL;
		rcMargin.left = _tcstol(marginAttr.c_str(), &pstr, 10);
		rcMargin.top = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.right = _tcstol(pstr + 1, &pstr, 10);
		rcMargin.bottom = _tcstol(pstr + 1, &pstr, 10);
		_control->SetMargin(rcMargin);
	}
	if (attr = element->FindAttribute("bkcolor")) {
		_control->SetBkColor(nbase::UTF8ToUTF16(attr->Value()));
	}
	if (attr = element->FindAttribute("valign")) {
		std::wstring valignAttr = nbase::UTF8ToUTF16(attr->Value());
		ui::VerAlignType type;
		if (valignAttr == L"top") {
			type = ui::kVerAlignTop;
		}
		else if (valignAttr == L"center") {
			type = ui::kVerAlignCenter;
		}
		else {
			type = ui::kVerAlignBottom;
		}
		_control->SetVerAlignType(type);
	}
	if (attr = element->FindAttribute("halign")) {
		std::wstring halignAttr = nbase::UTF8ToUTF16(attr->Value());
		ui::HorAlignType type;
		if (halignAttr == L"left") {
			type = ui::kHorAlignLeft;
		}
		else if (halignAttr == L"center") {
			type = ui::kHorAlignCenter;
		}
		else {
			type = ui::kHorAlignRight;
		}
		_control->SetHorAlignType(type);
	}
	if (attr = element->FindAttribute("bkimage")) {
		_control->SetBkImage(nbase::UTF8ToUTF16(attr->Value()));
	}
	if (attr = element->FindAttribute("class")) {
		_control->SetClass(nbase::UTF8ToUTF16(attr->Value()));
	}
	OnParseElement(element);
}

tinyxml2::XMLElement* AreaControlDelegate::GetElement(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement(nbase::UTF16ToUTF8(GetControlName()).c_str());
	std::wstring controlName = _control->GetName();
	if (!controlName.empty()) {
		element->SetAttribute("name", nbase::UTF16ToUTF8(controlName).c_str());
	}
	if (!CheckWidthAndHeight(_control->GetFixedWidth())) {
		element->SetAttribute("width", _control->GetFixedWidth());
	}
	if (!CheckWidthAndHeight(_control->GetFixedHeight())) {
		element->SetAttribute("height", _control->GetFixedHeight());
	}
	if (!CheckRectEmpty(_control->GetMargin())) {
		element->SetAttribute("margin", nbase::StringPrintf("%d,%d,%d,%d", _control->GetMargin().left, _control->GetMargin().top, _control->GetMargin().right, _control->GetMargin().bottom).c_str());
	}
	OnGetElement(doc, element);
	return element;
}

void AreaControlDelegate::Reset()
{
	if (_selected) {
		_control->SetBorderSize(0);
	}
	_selected = false;
}

void AreaControlDelegate::Remove()
{
	_control->GetParent()->Remove(_control);
}

bool AreaControlDelegate::OnButtonDown(ui::EventArgs* args)
{
	_is_button_down = true;
	_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_BUTTON_DOWN, 0);
	args->pSender->SetBorderSize(1);
	args->pSender->SetBorderColor(L"blue");
	_selected = true;
	_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_SELECTED, 0);
	ui::UiRect controlRect = args->pSender->GetPos();
	if (args->ptMouse.x - controlRect.left < PADDING) {
		_current_direction = Direction::LEFT;
	}
	else if (controlRect.right - args->ptMouse.x < PADDING) {
		_current_direction = Direction::RIGHT;
	}
	else if (args->ptMouse.y - controlRect.top < PADDING) {
		_current_direction = Direction::TOP;
	}
	else if (controlRect.bottom - args->ptMouse.y < PADDING) {
		_current_direction = Direction::BOTTOM;
	}
	_last_point = args->ptMouse;
	return true;
}

bool AreaControlDelegate::OnButtonUp(ui::EventArgs* args)
{
	_current_direction = Direction::NONE;
	_is_button_down = false;
	return true;
}

bool AreaControlDelegate::Notify(ui::EventArgs* args)
{
	if (args->Type != ui::kEventMouseMove) {
		if (args->Type == ui::kEventMouseRightButtonDown) {
			_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_BUTTON_DOWN, 0);
			args->pSender->SetBorderColor(L"red");
			_selected = true;
			_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_SELECTED, 0);
			OnItemMenu(args);
		}
		return true;
	}
	ui::UiRect controlRect = args->pSender->GetPos();
	if (args->ptMouse.x - controlRect.left < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
	}
	else if (controlRect.right - args->ptMouse.x < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
	}
	else if (args->ptMouse.y - controlRect.top < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
	}
	else if (controlRect.bottom - args->ptMouse.y < PADDING) {
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
	}
	std::wstring dataId = args->pSender->GetDataID();
	if (!_is_button_down) {
		return true;
	}
	_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::UI_CHANGED, 0);
	ui::UiRect rect = args->pSender->GetMargin();
	int left = args->ptMouse.x - _last_point.x;
	int top = args->ptMouse.y - _last_point.y;
	switch (_current_direction)
	{
	case Direction::LEFT:
	{
		rect.left += left;
		int width = args->pSender->GetFixedWidth() - left;
		if (width < 1) {
			width = 1;
		}
		args->pSender->SetFixedWidth(width);
		break;
	}
	case Direction::RIGHT:
	{
		args->pSender->SetFixedWidth(args->pSender->GetFixedWidth() + left);
		break;
	}
	case Direction::TOP:
	{
		rect.top += top;
		int height = args->pSender->GetFixedHeight() - top;
		if (height < 1) {
			height = 1;
		}
		args->pSender->SetFixedHeight(height);
		break;
	}
	case Direction::BOTTOM:
	{
		args->pSender->SetFixedHeight(args->pSender->GetFixedHeight() + top);
		break;
	}
	default:
		rect.left += left;
		rect.top += top;
		break;
	}
	if (_can_move) {
		args->pSender->SetMargin(rect);
	}
	_last_point = args->ptMouse;
	return true;
}

bool AreaControlDelegate::OnItemMenu(ui::EventArgs* args)
{
	if (!_show_menu) {
		return true;
	}
	POINT point;
	::GetCursorPos(&point);
	nim_comp::CMenuWnd* menu = new nim_comp::CMenuWnd(_control->GetWindow()->GetHWND());
	ui::STRINGorID xml(L"../layout/menu_editor_control.xml");
	menu->Init(xml, _T("xml"), point);
	_menu_delete = (nim_comp::CMenuElementUI*)menu->FindControl(L"menu_editor_control_delete");
	_menu_delete->AttachSelect(nbase::Bind(&AreaControlDelegate::OnItemMenuDelete, this, std::placeholders::_1));
	_menu_copy = (nim_comp::CMenuElementUI*)menu->FindControl(L"menu_editor_control_copy");
	_menu_copy->AttachSelect(nbase::Bind(&AreaControlDelegate::OnItemMenuCopy, this, std::placeholders::_1));
	_menu_paste = (nim_comp::CMenuElementUI*)menu->FindControl(L"menu_editor_control_paste");
	_menu_paste->AttachSelect(nbase::Bind(&AreaControlDelegate::OnItemMenuPaste, this, std::placeholders::_1));
	OnItemMenu();
	return true;
}

bool AreaControlDelegate::OnItemMenuCopy(ui::EventArgs* args)
{
	_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_COPY, 0);
	return true;
}

bool AreaControlDelegate::OnItemMenuPaste(ui::EventArgs* args)
{
	_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_PASTE, 0);
	return true;
}

bool AreaControlDelegate::OnItemMenuDelete(ui::EventArgs* args)
{
	Remove();
	return true;
}