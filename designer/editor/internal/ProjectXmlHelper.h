#pragma once

class ProjectXmlHelper
{
public:
	ProjectXmlHelper();
	~ProjectXmlHelper();
	SINGLETON_DEFINE(ProjectXmlHelper);
public:
	void CreateProjectXml(const std::wstring & path);
private:
	const std::wstring _suffix = L".nd";
};