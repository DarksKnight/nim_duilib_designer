#pragma once
#include "../widget/EditorArea.h"
#include <third_party/tinyxml2/include/tinyxml2.h>
#include "base/memory/singleton.h"

class XmlHelper
{
public:
	XmlHelper();
	~XmlHelper();
	SINGLETON_DEFINE(XmlHelper);
public:
	bool ConvertXml(EditorArea* area, const std::wstring & path, bool window = true);
private:
	tinyxml2::XMLElement* GetElement(tinyxml2::XMLDocument* doc, ui::Control* control);
private:
	bool CheckRectEmpty(ui::UiRect rect) {
		return rect.left == 0 && rect.top == 0 && rect.right == 0 && rect.bottom == 0;
	}
	bool CheckWidthAndHeight(int value) {
		return value < 0;
	}
};

