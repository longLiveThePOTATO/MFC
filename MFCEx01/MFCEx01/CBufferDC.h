#include "afxwin.h"

class CBufferDC :public CDC
{
private:
	CBufferDC(){}
	CBufferDC(const CBufferDC &src){}
	CBufferDC& operator=(const CBufferDC &src){}
protected:
	BOOL Attach(HDC hDC);
	HDC Detech();
private:
	CWnd*		m_pParent;			// ��� �����쿡 ���� ������
	CDC*		m_pTarget;			// ��� ������ DC�� ���� ������
	PAINTSTRUCT	m_PaintStruct;
	CRect		m_RcClient, m_RcWindow;	// ��� �������� ũ�� ����
	CDC			m_MemoryDC;			// ���� DC
	CBitmap		m_MemoryBmp, *m_pOldMemoryBmp;

};