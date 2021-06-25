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
	bool ParseXml(EditorArea* area, const std::wstring & path, bool window = true);
private:
	tinyxml2::XMLElement* GetElement(tinyxml2::XMLDocument* doc, ui::Control* control);
	void ParseElement(EditorArea* area, tinyxml2::XMLElement* element, ui::Box* rootBox);
private:
	bool CheckRectEmpty(ui::UiRect rect) {
		return rect.left == 0 && rect.top == 0 && rect.right == 0 && rect.bottom == 0;
	}
	bool CheckWidthAndHeight(int value) {
		return value < 0;
	}
	std::vector<std::string> ConvertVector(std::list<std::string> list) {
		std::vector<std::string> vector;
		for (auto it = list.begin(); it != list.end(); ++it) {
			vector.push_back(*it);
		}
		return vector;
	}
private:
	const std::string _xml_header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
};

