#ifndef UI_CORE_TABBOX_H_
#define UI_CORE_TABBOX_H_

#pragma once

namespace ui
{

class UILIB_API TabBox : public Box
{
public:
	TabBox(Layout* pLayout = new Layout());

	// ���ڳ�ʼ��xml����
	virtual void DoInit() override;

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual bool Add(Control* pControl) override;
	virtual bool AddAt(Control* pControl, std::size_t iIndex) override;
	virtual bool Remove(Control* pControl) override;
	virtual bool RemoveAt(std::size_t iIndex) override;
	virtual void RemoveAll() override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

	/**
	 * @brief ��ȡ��ǰѡ����
	 * @return ���ص�ǰѡ��������
	 */
	int GetCurSel() const;

	/**
	 * @brief ���ݿؼ�����ѡ��һ������
	 * @param[in] iIndex Ҫѡ�����������
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool SelectItem(int iIndex);

	/**
	 * @brief ���ݿؼ�ָ��ѡ��һ������
	 * @param[in] pControl Ҫѡ�������ָ��
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool SelectItem(Control* pControl);

	/**
	 * @brief ���ݿؼ�����ѡ��һ������
	 * @param[in] pControlName Ҫѡ��Ŀؼ�����
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool SelectItem(const std::wstring& pControlName);

	/**
	 * @brief �����Ƿ���ʾ����Ч��
	 * @param[in] bFadeSwitch ����Ϊ true ����ʾ��false Ϊ����ʾ����
	 * @return ��
	 */
	void SetFadeSwitch(bool bFadeSwitch);

	/**
	 * @brief �ж��Ƿ���Ҫ��ʾ����Ч��
	 * @return ���� true ��ʾ������false Ϊ����ʾ����Ч��
	 */
	bool IsFadeSwitch() { return m_bFadeSwith; }
	
	/** @brief ����ѡ��ʱ��
	  * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	  * @return ��
	  */
	void AttachSelect(const EventCallback& callback) { OnEvent[kEventSelect] += callback; }
protected:
	/**
	 * @brief ��ʾһ�� TAB ��
	 * @param[in] it TAB ������
	 * @return ��
	 */
	void ShowTabItem(std::size_t it);

	/**
	 * @brief ����һ�� TAB ��
	 * @param[in] it TAB ������
	 * @return ��
	 */
	void HideTabItem(std::size_t it);

protected:
	int m_iCurSel;
	int m_iInitSel;
	bool m_bIsInit;
	bool m_bFadeSwith;
};

}
#endif // UI_CORE_TABBOX_H_
