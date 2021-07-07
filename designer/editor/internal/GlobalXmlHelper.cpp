#include "../stdafx.h"
#include "GlobalXmlHelper.h"
#include "SettingsHelper.h"

GlobalXmlHelper::GlobalXmlHelper()
{
	_global_xml_path = SettingsHelper::GetInstance()->Get(CONFIG_TAG_CREATE, CONFIG_KEY_GLOBAL_XML);
	if (!nbase::FilePathIsExist(_global_xml_path, false)) {
		_global_xml_path = L"";
		return;
	}
	if (!_global_xml_path.empty()) {
		if (!SetGlobalXmlPath(_global_xml_path)) {
			_global_xml_path = L"";
		}
	}
}


GlobalXmlHelper::~GlobalXmlHelper()
{
}

bool GlobalXmlHelper::SetGlobalXmlPath(const std::wstring& path)
{
	_global_xml_path = path;
	SettingsHelper::GetInstance()->Set(CONFIG_TAG_CREATE, CONFIG_KEY_GLOBAL_XML, _global_xml_path);
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError result = doc.LoadFile(nbase::UTF16ToUTF8(path).c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return false;
	}
	for (tinyxml2::XMLElement* element = doc.RootElement()->FirstChildElement(); element; element = element->NextSiblingElement()) {
		const tinyxml2::XMLAttribute* attr = NULL;
		std::wstring name = nbase::UTF8ToUTF16(element->Value());
		if (name == L"Font") {
			Font font;
			if (attr = element->FindAttribute("id")) {
				font.id = nbase::UTF8ToUTF16(attr->Value());
			}
			if (attr = element->FindAttribute("name")) {
				font.name = nbase::UTF8ToUTF16(attr->Value());
			}
			if (attr = element->FindAttribute("size")) {
				int size = 0;
				nbase::StringToInt(attr->Value(), &size);
				font.size = size;
			}
			if (attr = element->FindAttribute("bold")) {
				font.bold = attr->Value() == "true";
			}
			if (attr = element->FindAttribute("underline")) {
				font.underline = attr->Value() == "true";
			}
			_fonts[font.id] = font;
		}
		else if (name == L"TextColor") {
			attr = element->FindAttribute("name");
			std::wstring name = nbase::UTF8ToUTF16(attr->Value());
			attr = element->FindAttribute("value");
			std::wstring value = nbase::UTF8ToUTF16(attr->Value());
			_colors[name] = value;
		}
		else if (name == L"Class") {
			Class clz;
			if (attr = element->FindAttribute("name")) {
				clz.name = nbase::UTF8ToUTF16(attr->Value());
			}
			_classes[clz.name] = clz;
		}
	}
	return true;
}