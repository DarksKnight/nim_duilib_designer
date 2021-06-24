#ifndef UI_UTILS_FONTMANAGER_H_
#define UI_UTILS_FONTMANAGER_H_

#pragma once
namespace Gdiplus{
	class PrivateFontCollection;
}
namespace ui 
{

/** @class FontManager
  * @brief �Զ������������
  * @copyright (c) 2021, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2021/2/26
  */
class UILIB_API FontManager
{
public:
	static FontManager* GetInstance();

	/** @brief ���һ�������ļ�
	  * @param[in] strFontFile �����ļ���
	  * @param[in] strFontName ������
	  * @return �޷���ֵ
	  */
	void AddFontResource(const std::wstring& strFontFile, const std::wstring& strFontName);

	/** @brief ��ȡ������ӵ����������
	  * @return �������ֵļ���
	  */
	const std::vector<std::wstring>& GetFontNames();

	/** @brief ����������ӵ�����
	  * @return �޷���ֵ
	  */
	void Clear();

private:
	FontManager() {};
	~FontManager();
	FontManager(const FontManager&) = delete;
	FontManager& operator = (const FontManager&) = delete;

private:
	std::vector<std::wstring>  m_fontPath;
	std::vector<std::wstring>  m_fontNames;
	std::vector<HANDLE>  m_fontHandles;
};

}
#endif //UI_UTILS_FONTMANAGER_H_
