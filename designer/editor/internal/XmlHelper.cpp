#include "../stdafx.h"
#include "XmlHelper.h"
#include <third_party/tinyxml2/include/tinyxml2.h>

XmlHelper::XmlHelper()
{
}


XmlHelper::~XmlHelper()
{
}

void XmlHelper::ConvertXml(EditorArea* box, const std::wstring& path)
{
	const std::string declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	tinyxml2::XMLDocument doc;
	doc.Parse(declaration.c_str());
	tinyxml2::XMLElement* root = doc.NewElement("Window");
	doc.InsertEndChild(root);
	doc.SaveFile(nbase::UTF16ToUTF8(path).c_str());
}