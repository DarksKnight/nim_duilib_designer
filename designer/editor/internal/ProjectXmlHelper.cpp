#include "../stdafx.h"
#include "ProjectXmlHelper.h"

ProjectXmlHelper::ProjectXmlHelper()
{

}


ProjectXmlHelper::~ProjectXmlHelper()
{
}

void ProjectXmlHelper::CreateProjectXml(const std::wstring& folder)
{
	tinyxml2::XMLDocument doc;
	doc.Parse(XML_HEADER);
	tinyxml2::XMLElement* projectElement = doc.NewElement("Designer");
	doc.InsertEndChild(projectElement);
	std::wstring projectName = L"";
	nbase::FilePathApartFileName(folder, projectName);
}