#include "../stdafx.h"
#include "AreaWindow.h"

AreaWindow::AreaWindow()
{
	SetFixedWidth(500);
	SetFixedHeight(500);
	SetBkColor(L"bk_wnd_darkcolor");
	SetMove(false);
	SetShowMenu(false);
	for (auto it = _basic_property.begin(); it != _basic_property.end();) {
		if (it->name == L"name") {
			it = _basic_property.erase(it);
		}
		else if (it->name == L"margin") {
			it = _basic_property.erase(it);
		}
		else {
			it++;
		}
	}
}


AreaWindow::~AreaWindow()
{
}
