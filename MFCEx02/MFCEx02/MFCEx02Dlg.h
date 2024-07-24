// MFCEx02Dlg.h : 헤더 파일

#pragma once
#include "afxwin.h"
#include "color.h"
#include <vector>
#include "Comm.h"
#include <map>
#include "FPoint.h"

#define TIMER_ID 1
#define TIMER_INTERVAL 100 // 100ms마다 타이머 이벤트 발생
enum Command {
	ADD, DEL, GETCOUNT, GETOBJ, INVALID
};

// CMFCEx02Dlg 대화 상자
class CMFCEx02Dlg : public CDialogEx
{
	// 생성입니다.
public:
	CMFCEx02Dlg(CWnd* pParent = NULL);    // 표준 생성자입니다.

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCEX02_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//afx_msg LRESULT OnReadComport(WPARAM wParam, LPARAM lParam);

public:
	// 초기화 및 설정
	CComboBox m_Comport;
	CComboBox m_BaudRate;
	CEdit center_X;
	CEdit center_Y;
	CEdit size_X;
	CEdit size_Y;
	CEdit m_Send;
	CEdit m_Receive;
	CStatic m_Pic;
	CListCtrl m_List;
	CBrush m_Brush;

	int obj_Type;
	int count_R;
	int count_C;
	int count_T;
	int selectedIndex = NULL;
	int vCenterX;
	int vCenterY;

	CPoint start_Pos;
	CString obj_Str;
	CRect view;

	// 도형 관리
	struct ObjData
	{
		int type;
		CFPoint cP;
		CFPoint size;
		std::string name;
		BOOL bSelect;

		ObjData(int t, CFPoint center, CFPoint s, bool flag)
			: type(t), cP(center), size(s), bSelect(flag){}
	};
	std::vector<ObjData> objData;

	// 이벤트 핸들러
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBtnClickedAddR();
	afx_msg void OnBtnClickedAddC();
	afx_msg void OnBnClickedDel();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedView();
	afx_msg void OnCbnDropdownComport();
	afx_msg void OnCbnDropdownBaudRate();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedUnconnect();
	afx_msg void OnBnClickedSend();
	void OnReadComPort();


	// Serial 통신
	Comm g_Comm;
	void getSerialPort();
	long GetBaudRate(int index);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	// 유틸리티
	void drawShape(int type, CDC* pdc, const CFPoint& center, const CFPoint& size);
	void drawRectangle(CDC* pDC, const CFPoint& center, const CFPoint& size);
	void drawEllipse(CDC* pDC, const CFPoint& center, const CFPoint& sizes);
	void onDrawImage();
	CFPoint Scale(const CFPoint& point);
	CFPoint ReScale(const CFPoint& point);
	std::vector<CString> split(const CString& s);
	CString delimiter = _T(";");
	Command StringToCommand(const CString& commandStr);
	int CommandProcs(const CString& s);

	
	std::map<CString, Command> commandMap;

	// Initializes the command map
	void InitializeCommandMap() {
		commandMap[_T("ADD")] = ADD;
		commandMap[_T("DEL")] = DEL;
		commandMap[_T("GETCOUNT")] = GETCOUNT;
		commandMap[_T("GETOBJ")] = GETOBJ;
		commandMap[_T("INVALID")] = INVALID;
	}

	int Response(int s_f);
};
