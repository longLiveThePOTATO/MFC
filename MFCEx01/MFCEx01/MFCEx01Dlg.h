
// MFCEx01Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "color.h"
#include <vector>

// CMFCEx01Dlg ��ȭ ����
class CMFCEx01Dlg : public CDialogEx
{
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
	int count_T;
	int selectedIndex; // ���õ� �ε��� ���� �߰�
	CPoint start_pos;
	CString obj_Str;
	CListCtrl m_List;
	CBrush m_Brush;
	CStatic m_Pic;
	CRect view;
	CEdit center_X;
	CEdit center_Y;
	CEdit size_X;
	CEdit size_Y;

	enum ShapeType {RECTANGLE, CIRCLE};
	struct ObjData
	{
		ShapeType type;
		CPoint sP;
		CPoint eP;
		std::string name;

		ObjData(ShapeType t, CPoint start, CPoint end)
			: type(t), sP(start), eP(end){}
	};
	std::vector<ObjData> objData;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBtnClickedAddR();
	afx_msg void OnBtnClickedAddC();
	afx_msg void OnBnClickedDel();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

	void DrawShape(CDC* pDC, const ObjData& objData, COLORREF color); // ������ �׸��� �Լ� ����
	CPoint CalculateCenter(const CPoint& start, const CPoint& end);
//	CPoint CalculateSize();
	CPoint CalculateSize(const CPoint start, const CPoint end);
};
