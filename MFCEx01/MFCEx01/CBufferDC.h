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
	CWnd*		m_pParent;			// 대상 윈도우에 대한 포인터
	CDC*		m_pTarget;			// 대상 윈도우 DC에 대한 포인터
	PAINTSTRUCT	m_PaintStruct;
	CRect		m_RcClient, m_RcWindow;	// 대상 윈도우의 크기 정보
	CDC			m_MemoryDC;			// 버퍼 DC
	CBitmap		m_MemoryBmp, *m_pOldMemoryBmp;

};