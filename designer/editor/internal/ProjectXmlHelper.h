#pragma once

class ProjectXmlHelper
{
public:
	ProjectXmlHelper();
	~ProjectXmlHelper();
	SINGLETON_DEFINE(ProjectXmlHelper);
public:
	void CreateProjectXml(const std::wstring & folder);
};