#include "../stdafx.h"
#include "AreaControl.h"

AreaControl::AreaControl(ui::Control* control):_control(control)
{
	control->AttachButtonDown(nbase::Bind(&AreaControl::OnButtonDown, this, std::placeholders::_1));
	control->AttachButtonUp(nbase::Bind(&AreaControl::OnButtonUp, this, std::placeholders::_1));
	control->AttachAllEvents(nbase::Bind(&AreaControl::OnMouseEvent, this, std::placeholders::_1));
	control->SetBorderColor(L"blue");
	control->SetBorderSize(1);
}

AreaControl::~AreaControl()
{
}

void AreaControl::ParseElement(tinyxml2::XMLElement* element)
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

tinyxml2::XMLElement* AreaControl::GetElement(tinyxml2::XMLDocument* doc)
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

bool AreaControl::OnButtonDown(ui::EventArgs* args)
{
	if (_button_down_callback) {
		_button_down_callback();
	}
	args->pSender->SetBorderColor(L"red");
	_is_button_down = true;
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

bool AreaControl::OnButtonUp(ui::EventArgs* args)
{
	_is_button_down = false;
	_current_direction = Direction::NONE;
	return true;
}

bool AreaControl::OnMouseEvent(ui::EventArgs* args)
{
	if (args->Type != ui::kEventMouseMove) {
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
		rect.right += left;
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
		rect.bottom += top;
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