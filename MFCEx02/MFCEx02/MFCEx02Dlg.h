
// MFCEx02Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "color.h"
#include <vector>
#define CENTER 310
#define HALFLENGTH 298
// CMFCEx02Dlg ��ȭ ����
class CMFCEx02Dlg : public CDialogEx
{
	// �����Դϴ�.
public:
	CMFCEx02Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFCEX02_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


	// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	DECLARE_MESSAGE_MAP()
public:
	int obj_Type;
	int count_R;
	int count_C;
	int count_T;
	int selectedIndex = NULL; // ���õ� �ε��� ���� �߰�
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
	CPoint CalculateCenter(const CPoint& start, const CPoint& end);
	CPoint CalculateSize(const CPoint start, const CPoint end);
	CPoint ReScale(CPoint point);
	CComboBox m_Comport;

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
	afx_msg void OnStnClickedView();
	afx_msg void OnCbnDropdownComport();

	void drawShape(int type, CDC* pdc, CPoint sP, CPoint eP);
	void drawRectangle(CDC* pDC, const CPoint& start, const CPoint& end);
	void drawEllipse(CDC* pDC, const CPoint& center, const CPoint& radius);
	void onDrawImage();
	void getSerialPort();
	afx_msg void OnCbnDropdownBaudRate();
	CComboBox m_BaudRate;
	afx_msg void OnBnClickedConnect();
};
