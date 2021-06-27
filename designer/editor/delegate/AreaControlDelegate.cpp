#include "../stdafx.h"
#include "AreaControlDelegate.h"

AreaControlDelegate::AreaControlDelegate(ui::Control* control):_control(control)
{
	control->AttachButtonDown(nbase::Bind(&AreaControlDelegate::OnButtonDown, this, std::placeholders::_1));
	control->AttachButtonUp(nbase::Bind(&AreaControlDelegate::OnButtonUp, this, std::placeholders::_1));
	control->AttachAllEvents(nbase::Bind(&AreaControlDelegate::Notify, this, std::placeholders::_1));
	control->SetBorderColor(L"blue");
	control->SetBorderSize(1);
}

AreaControlDelegate::~AreaControlDelegate()
{
}

void AreaControlDelegate::ParseElement(tinyxml2::XMLElement* element)
{
	std::wstring value = nbase::UTF8ToUTF16(element->Value());
	std::string widthAttr = "stretch";
	std::string heightAttr = "stretch";
	std::string marginAttr = "";
	if (element->BoolAttribute("width")) {
		widthAttr = element->Attribute("width");
	}
	if (element->BoolAttribute("height")) {
		heightAttr = element->Attribute("height");
	}
	if (element->BoolAttribute("margin")) {
		marginAttr = element->Attribute("margin");
	}
	int width = 0;
	int height = 0;
	if (widthAttr == "auto") {
		width = DUI_LENGTH_AUTO;
	}
	else if (widthAttr == "stretch") {
		width = DUI_LENGTH_STRETCH;
	}
	else {
		nbase::StringToInt(widthAttr, &width);
	}
	_control->SetFixedWidth(width);
	if (heightAttr == "auto") {
		height = DUI_LENGTH_AUTO;
	}
	else if (heightAttr == "stretch") {
		height = DUI_LENGTH_STRETCH;
	}
	else {
		nbase::StringToInt(heightAttr, &height);
	}
	_control->SetFixedHeight(height);
	if (!marginAttr.empty()) {
		std::vector<std::string> marginVector = ConvertVector(nim_comp::StringHelper::Split(marginAttr, ","));
		int left, top, right, bottom = 0;
		nbase::StringToInt(marginVector[0], &left);
		nbase::StringToInt(marginVector[1], &top);
		nbase::StringToInt(marginVector[2], &right);
		nbase::StringToInt(marginVector[3], &bottom);
		ui::UiRect margin(left, top, right, bottom);
		_control->SetMargin(margin);
	}
	OnParseElement(element);
}

tinyxml2::XMLElement* AreaControlDelegate::GetElement(tinyxml2::XMLDocument* doc)
{
	tinyxml2::XMLElement* element = doc->NewElement(nbase::UTF16ToUTF8(GetControlName()).c_str());
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
	_selected = false;
	_control->SetBorderColor(L"blue");
}

void AreaControlDelegate::Remove()
{
	_control->GetParent()->Remove(_control);
}

bool AreaControlDelegate::OnButtonDown(ui::EventArgs* args)
{
	_is_button_down = true;
	_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_BUTTON_DOWN, 0);
	args->pSender->SetBorderColor(L"red");
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
	OnItemMenu();
	return true;
}

bool AreaControlDelegate::OnItemMenuCopy(ui::EventArgs* args)
{
	_control->GetWindow()->SendNotify(_control, ui::kEventNotify, CustomEventType::CONTROL_COPY, 0);
	return true;
}

bool AreaControlDelegate::OnItemMenuDelete(ui::EventArgs* args)
{
	Remove();
	return true;
}