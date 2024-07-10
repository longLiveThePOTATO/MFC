
// MFCEx01Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "color.h"
#include <vector>
#define CENTER 310
#define HALFLENGTH 298
// CMFCEx01Dlg 대화 상자
class CMFCEx01Dlg : public CDialogEx
{
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
	int count_T;
	int selectedIndex; // 선택된 인덱스 변수 추가
	int vCenterX;
	int vCenterY;
	CPoint start_Pos, end_Pos;
	CString obj_Str;
	CListCtrl m_List;
	CBrush m_Brush;
	CStatic m_Pic;
	CRect view;
	CEdit center_X;
	CEdit center_Y;
	CEdit size_X;
	CEdit size_Y;

	struct ObjData
	{
		int type;
		CPoint sP;
		CPoint eP;
		std::string name;
		BOOL bSelect;

		ObjData(int t, CPoint start, CPoint end, bool flag)
			: type(t), sP(start), eP(end), bSelect(flag){}
	};
	std::vector<ObjData> objData;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBtnClickedAddR();
	afx_msg void OnBtnClickedAddC();
	afx_msg void OnBnClickedDel();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

	void DrawEllipse(CDC* pDC, const CPoint& center, const CPoint& radius);
	CPoint CalculateCenter(const CPoint& start, const CPoint& end);
	CPoint CalculateSize(const CPoint start, const CPoint end);
	CPoint ReScale(CPoint point);
	void DrawShape(int type, CDC* pdc, CPoint sP, CPoint eP);
};
