#include "../stdafx.h"
#include "GlobalXmlHelper.h"
#include "SettingsHelper.h"
#include "../util/MD5.h"
#include "XmlHelper.h"

GlobalXmlHelper::GlobalXmlHelper()
{
}


GlobalXmlHelper::~GlobalXmlHelper()
{
}

bool GlobalXmlHelper::SetGlobalXmlPath(const std::wstring& path)
{
	std::wstring fn;
	nbase::FilePathApartFileName(path, fn);
	if (fn != L"global.xml") {
		return false;
	}
	_global_xml_path = path;
	_backup_global_xml_path = GlobalData::APPDATA_LOCAL + L"backup_global.xml";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError result = doc.LoadFile(nbase::UTF16ToUTF8(nbase::win32::GetCurrentModuleDirectory() + L"resources\\themes\\default\\global.xml").c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return false;
	}
	for (tinyxml2::XMLElement* element = doc.RootElement()->FirstChildElement(); element; element = element->NextSiblingElement()) {
		const tinyxml2::XMLAttribute* attr = NULL;
		std::wstring name = nbase::UTF8ToUTF16(element->Value());
		if (name == L"Font") {
			if (attr = element->FindAttribute("id")) {
				_fonts.push_back(nbase::UTF8ToUTF16(attr->Value()));
			}
		}
		else if (name == L"TextColor") {
			if (attr = element->FindAttribute("name")) {
				_colors.push_back(nbase::UTF8ToUTF16(attr->Value()));
			}
		}
		else if (name == L"Class") {
			if (attr = element->FindAttribute("name")) {
				_classes.push_back(nbase::UTF8ToUTF16(attr->Value()));
			}
		}
	}
	nbase::ThreadManager::PostRepeatedTask(kThreadGlobalXmlDiff, nbase::Bind(&GlobalXmlHelper::Diff, this), nbase::TimeDelta::FromMilliseconds(50));
	return true;
}

void GlobalXmlHelper::Diff()
{
	if (!nbase::FilePathIsExist(_global_xml_path, false)) {
		return;
	}
	int64_t fileSize = nbase::GetFileSize(_global_xml_path);
	if (_original_xml_size == fileSize) {
		return;
	}
	_original_xml_size = fileSize;
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError result = doc.LoadFile(nbase::UTF16ToUTF8(_global_xml_path).c_str());
	if (result != tinyxml2::XML_SUCCESS) {
		return;
	}
	std::vector<tinyxml2::XMLNode*> elements;
	for (tinyxml2::XMLNode* node = doc.RootElement()->FirstChild(); node; node = node->NextSibling()) {
		const tinyxml2::XMLElement* element = node->ToElement();
		const tinyxml2::XMLAttribute* attr = NULL;
		std::wstring name = nbase::UTF8ToUTF16(node->Value());
		if (name == L"Font") {
			if (attr = element->FindAttribute("id")) {
				if (std::find(_fonts.begin(), _fonts.end(), nbase::UTF8ToUTF16(attr->Value())) == _fonts.end()) {
					elements.push_back(node);
					_fonts.push_back(nbase::UTF8ToUTF16(attr->Value()));
				}
			}
		}
		else if (name == L"TextColor") {
			if (attr = element->FindAttribute("name")) {
				if (std::find(_colors.begin(), _colors.end(), nbase::UTF8ToUTF16(attr->Value())) == _colors.end()) {
					elements.push_back(node);
					_colors.push_back(nbase::UTF8ToUTF16(attr->Value()));
				}
			}
		}
		else if (name == L"Class") {
			if (attr = element->FindAttribute("name")) {
				if (std::find(_classes.begin(), _classes.end(), nbase::UTF8ToUTF16(attr->Value())) == _classes.end()) {
					elements.push_back(node);
					_classes.push_back(nbase::UTF8ToUTF16(attr->Value()));
				}
			}
		}
	}
	tinyxml2::XMLDocument saveDoc;
	saveDoc.Parse(XML_HEADER);
	tinyxml2::XMLElement* globalElement = saveDoc.NewElement("Global");
	saveDoc.InsertEndChild(globalElement);
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		tinyxml2::XMLNode* copy = (*it)->DeepClone(&saveDoc);
		globalElement->InsertEndChild(copy);
	}
	saveDoc.SaveFile(nbase::UTF16ToUTF8(_backup_global_xml_path).c_str());
	ui::WindowBuilder dialog_builder;
	ui::Window paint_manager;
	dialog_builder.Create(_backup_global_xml_path.c_str(), ui::CreateControlCallback(), &paint_manager);
}