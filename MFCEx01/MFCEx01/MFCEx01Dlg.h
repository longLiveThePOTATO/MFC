
// MFCEx01Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "color.h"

// CMFCEx01Dlg 대화 상자
class CMFCEx01Dlg : public CDialogEx
{
private:
	CPoint start_pos;

// 생성입니다.
public:
	CMFCEx01Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCEX01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
