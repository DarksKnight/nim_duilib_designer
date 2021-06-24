#pragma once
#include "../widget/EditorArea.h"

class XmlHelper
{
public:
	XmlHelper();
	~XmlHelper();
public:
	static void ConvertXml(EditorArea* box, const std::wstring & path);
};

