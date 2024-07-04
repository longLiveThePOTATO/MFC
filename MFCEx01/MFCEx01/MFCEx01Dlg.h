
// MFCEx01Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "color.h"

// CMFCEx01Dlg ��ȭ ����
class CMFCEx01Dlg : public CDialogEx
{
private:
	CPoint start_pos;

// �����Դϴ�.
public:
	CMFCEx01Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFCEX01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	DECLARE_MESSAGE_MAP()
public:
	int obj_Type;
	int count_R;
	int count_C;
	CString obj_Str;
	CListBox m_List;
	CBrush m_Brush;
	CStatic m_Pic;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBtnClickedAddR();
	afx_msg void OnBtnClickedAddC();
	afx_msg void OnCanvasView();
	afx_msg void OnBnClickedDel();
};
