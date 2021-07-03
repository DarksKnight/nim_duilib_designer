#pragma once
#include "../widget/EditorArea.h"
#include "base/memory/singleton.h"

class XmlHelper
{
public:
	XmlHelper();
	~XmlHelper();
	SINGLETON_DEFINE(XmlHelper);
public:
	bool ConvertXml(EditorArea* area, const std::wstring & path, bool window = true);
	bool ParseXml(ui::Box* box, const std::wstring & path);
	bool ParseXmlPreview(ui::Box* box, const std::wstring& path);
private:
	tinyxml2::XMLElement* GetElement(tinyxml2::XMLDocument* doc, ui::Control* control);
	void ParseElement(tinyxml2::XMLElement* element, ui::Box* rootBox);
private:
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

