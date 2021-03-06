#include "../stdafx.h"
#include "PropertyItem.h"
#include "../internal/XmlHelper.h"
#include "../internal/GlobalXmlHelper.h"
#include "commdlg.h"
#include "../form/EditorInputForm.h"

PropertyItem::PropertyItem(PropertyData data):_data(data)
{
	ui::GlobalManager::FillBoxWithCache(this, L"layout/item_property.xml");
	_lb_desc = (ui::Label*)FindSubControl(L"lb_desc");
	_lb_desc->SetText(data.desc + L"(" + data.name + L")");
	_tb_input = (ui::TabBox*)FindSubControl(L"tb_input");
	switch (data.inputType)
	{
	case RICHEDIT:
		_tb_input->SelectItem(0);
		_re_value = (ui::RichEdit*)FindSubControl(L"re_value");
		_re_value->AttachSetFocus(nbase::Bind(&PropertyItem::OnFocus, this, std::placeholders::_1));
		_re_value->AttachTextChange(nbase::Bind(&PropertyItem::OnTextChanged, this, std::placeholders::_1));
		_re_value->AttachKillFocus(nbase::Bind(&PropertyItem::OnKillFocus, this, std::placeholders::_1));
		_re_value->AttachReturn(nbase::Bind(&PropertyItem::OnTapReturn, this, std::placeholders::_1));
		_re_value->SetText(data.defaultValue);
		break;
	case COMBO:
		_tb_input->SelectItem(1);
		_combo_value = (ui::Label*)FindSubControl(L"combo_value");
		_combo_value->AttachButtonDown(nbase::Bind(&PropertyItem::OnComboClick, this, std::placeholders::_1));
		break;
	case FILEBUTTON:
		_tb_input->SelectItem(2);
		_lb_path = (ui::Label*)FindSubControl(L"lb_path");
		_btn_file = (ui::Button*)FindSubControl(L"btn_file");
		_btn_file->AttachClick(nbase::Bind(&PropertyItem::OnFileButtonClick, this, std::placeholders::_1));
		break;
	case COLOR_BUTTON:
		_tb_input->SelectItem(3);
		_ctrl_preview = FindSubControl(L"ctrl_preview");
		_btn_choose = (ui::Button*)FindSubControl(L"btn_choose");
		_btn_choose->AttachClick(nbase::Bind(&PropertyItem::OnColorButtonClick, this, std::placeholders::_1));
		break;
	default:
		break;
	}
}


PropertyItem::~PropertyItem()
{
}

void PropertyItem::InitCtrls()
{
	int index = GetIndex();
	if (index % 2 == 0) {
		SetBkColor(L"bk_property_item_dark");
	}
	else {
		SetBkColor(L"bk_property_item_light");
	}
}

void PropertyItem::SetValue(const std::wstring& value)
{
	switch (_tb_input->GetCurSel())
	{
	case 0:
		_re_value->SetText(value);
		break;
	case 1:
		_combo_value->SetText(value);
		break;
	case 2:
		_lb_path->SetText(value);
		break;
	default:
		break;
	}
}

std::wstring PropertyItem::GetValue()
{
	switch (_tb_input->GetCurSel())
	{
	case 0:
		return _re_value->GetText();
	case 1:
		return _combo_value->GetText();
	case 2:
		return _lb_path->GetText();
	default:
		break;
	}
	return L"";
}

bool PropertyItem::OnFocus(ui::EventArgs* args)
{
	if (_data.name == L"class") {
		GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::SHOW_CLASS_PROPERTY_LIST);
	}
	else if (_data.name == L"font") {
		GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::SHOW_FONT_PROPERTY_LIST);
	}
	return true;
}

bool PropertyItem::OnTextChanged(ui::EventArgs* args)
{
	if (_data.name == L"class") {
		GetWindow()->SendNotify(args->pSender, ui::kEventNotify, CustomEventType::PROPERTY_ITEM_CLASS_TEXT_CHANGE);
	}
	else if (_data.name == L"font") {
		GetWindow()->SendNotify(args->pSender, ui::kEventNotify, CustomEventType::PROPERTY_ITEM_FONT_TEXT_CHANGE);
	}
	return true;
}

bool PropertyItem::OnKillFocus(ui::EventArgs* args)
{
	GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::HIDE_PROPERTY_LIST);
	ChangeProperty();
	return true;
}

bool PropertyItem::OnTapReturn(ui::EventArgs* args)
{
	GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::HIDE_PROPERTY_LIST);
	ChangeProperty();
	return true;
}

bool PropertyItem::OnComboClick(ui::EventArgs* args)
{
	if (_combo_menu) {
		_combo_menu->Close();
		_combo_menu = NULL;
		return true;
	}
	ui::UiRect rect = args->pSender->GetPos();
	ui::CPoint point(rect.left, rect.bottom);
	::ClientToScreen(GetWindow()->GetHWND(), &point);
	_combo_menu = new nim_comp::CMenuWnd(GetWindow()->GetHWND());
	ui::STRINGorID xml(L"../layout/menu_property_combo.xml");
	_combo_menu->Init(xml, _T("xml"), point);
	ui::ListBox* listMenu = (ui::ListBox*)_combo_menu->FindControl(L"listMenu");
	listMenu->AttachSelect(nbase::Bind(&PropertyItem::OnComboItemClick, this, std::placeholders::_1));
	for (auto it = _data.inputDatas.begin(); it != _data.inputDatas.end(); ++it) {
		ui::MenuElement* element = new ui::MenuElement;
		element->SetMouseChildEnabled(false);
		element->SetClass(L"menu_element");
		element->SetFixedWidth(args->pSender->GetWidth());
		element->SetFixedHeight(25);
		ui::Label* label = new ui::Label;
		label->SetFixedHeight(DUI_LENGTH_AUTO);
		label->SetVerAlignType(ui::kVerAlignCenter);
		label->SetText(*it);
		element->Add(label);
		listMenu->Add(element);
	}
	return true;
}

bool PropertyItem::OnComboItemClick(ui::EventArgs* args)
{
	_combo_value->SetText(_data.inputDatas[args->wParam]);
	_combo_menu->Close();
	_combo_menu = NULL;
	return true;
}

bool PropertyItem::OnFileButtonClick(ui::EventArgs* args)
{
	nim_comp::CFileDialogEx* fileDlg = new nim_comp::CFileDialogEx;
	std::map<LPCTSTR, LPCTSTR> filters;
	filters[L"File Format(*.png)"] = L"*.png";
	fileDlg->SetFilter(filters);
	fileDlg->SetDefExt(L".png");
	fileDlg->SetParentWnd(GetWindow()->GetHWND());
	nim_comp::CFileDialogEx::FileDialogCallback2 callback2 = nbase::Bind(&PropertyItem::OnSelectPath, this, std::placeholders::_1, std::placeholders::_2);
	fileDlg->AyncShowOpenFileDlg(callback2);
	return true;
}

void PropertyItem::OnSelectPath(BOOL ret, std::wstring path)
{
	if (!ret || path.empty()) {
		return;
	}
	std::wstring xmlPath = XmlHelper::GetInstance()->GetSavedXmlPath();
	std::wstring tempPath = L"";
	std::wstring finalPath = L"";
	for (int i = 0; i < xmlPath.length(); i++) {
		if (xmlPath[i] == path[i]) {
			continue;
		}
		tempPath = xmlPath.substr(i);
		finalPath = path.substr(i);
		break;
	}
	std::list<std::wstring> list = ui::StringHelper::Split(tempPath, L"\\");
	for (int i = 0; i < list.size() - 1; i++) {
		finalPath = L"../" + finalPath;
	}
	nbase::StringReplaceAll(L"\\", L"/", finalPath);
	_lb_path->SetText(finalPath);
	_lb_path->SetToolTipText(finalPath);
	ChangeProperty();
}

bool PropertyItem::OnColorButtonClick(ui::EventArgs* args)
{
	static CHOOSECOLOR stChooseColor;
	static COLORREF dwCustColors[16];
	stChooseColor.lStructSize = sizeof(CHOOSECOLOR);
	stChooseColor.hwndOwner = GetWindow()->GetHWND();
	stChooseColor.lpCustColors = (LPDWORD)dwCustColors;
	stChooseColor.Flags = CC_FULLOPEN;
	if (!ChooseColor(&stChooseColor)) {
		return true;
	}
	std::string color = nbase::StringPrintf("#ff%02x%02x%02x", GetRValue(stChooseColor.rgbResult), GetGValue(stChooseColor.rgbResult), GetBValue(stChooseColor.rgbResult));
	EditorInputForm* form = nim_comp::WindowsManager::GetInstance()->SingletonShow<EditorInputForm>(EditorInputForm::kClassName);
	form->SetCallback(nbase::Bind(&PropertyItem::InputCallback, this, std::placeholders::_1));
	return true;
}

void PropertyItem::ChangeProperty()
{
	GetWindow()->SendNotify(this, ui::kEventNotify, CustomEventType::CONTROL_SET_PROPERTY);
}

void PropertyItem::InputCallback(const std::wstring& text)
{
	if (text.empty()) {
		return;
	}

}