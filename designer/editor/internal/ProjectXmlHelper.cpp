#include "../stdafx.h"
#include "ProjectXmlHelper.h"

ProjectXmlHelper::ProjectXmlHelper()
{

}


ProjectXmlHelper::~ProjectXmlHelper()
{
}

void ProjectXmlHelper::CreateProjectXml(const std::wstring& path)
{
	tinyxml2::XMLDocument doc;
	doc.Parse(XML_HEADER);
	tinyxml2::XMLElement* projectElement = doc.NewElement("Window");
	doc.InsertEndChild(projectElement);
	tinyxml2::XMLElement* rootElement = doc.NewElement("RootPath");
	std::wstring folder = L"";
	nbase::FilePathApartDirectory(path, folder);
	rootElement->SetAttribute("path", nbase::UTF16ToUTF8(folder).c_str());
	projectElement->InsertEndChild(rootElement);
	tinyxml2::XMLError result = doc.SaveFile(nbase::UTF16ToUTF8(path).c_str());
	int a = 0;
}