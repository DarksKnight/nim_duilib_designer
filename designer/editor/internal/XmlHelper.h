#pragma once
#include "../widget/EditorArea.h"
#include "base/memory/singleton.h"

#define XML_HEADER "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

class XmlHelper
{
public:
	typedef std::function<void(AreaControlDelegate* delegate)> ParseControlCallback;
public:
	XmlHelper();
	~XmlHelper();
	SINGLETON_DEFINE(XmlHelper);
public:
	bool ConvertXml(EditorArea* area, const std::wstring & path);
	bool ParseXml(ui::Box* box, const std::wstring & path, ParseControlCallback callback = NULL);
	bool ParseXmlPreview(ui::Box* box, const std::wstring& path);
private:
	tinyxml2::XMLElement* GetElement(tinyxml2::XMLDocument* doc, ui::Control* control);
	void ParseElement(tinyxml2::XMLElement* element, ui::Box* rootBox, ParseControlCallback callback = NULL);
private:
	std::vector<std::string> ConvertVector(std::list<std::string> list) {
		std::vector<std::string> vector;
		for (auto it = list.begin(); it != list.end(); ++it) {
			vector.push_back(*it);
		}
		return vector;
	}
private:
	ParseControlCallback _callback;
};

