// MFCEx02Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCEx02.h"
#include "MFCEx02Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define M_PI 3.14159265358979323846
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

// RsPort 객체 정적 전역 변수 선언
//CRsPort g_RsPort;

// CMFCEx02Dlg 대화 상자

CMFCEx02Dlg::CMFCEx02Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCEx02Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCEx02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	// DDX_Control(pDX, IDC_View, m_PictureControl);
	DDX_Control(pDX, IDC_View, m_Pic);
	DDX_Control(pDX, IDC_EDIT1, center_X);
	DDX_Control(pDX, IDC_EDIT2, center_Y);
	DDX_Control(pDX, IDC_EDIT3, size_X);
	DDX_Control(pDX, IDC_EDIT4, size_Y);
	DDX_Control(pDX, IDC_COMPORT, m_Comport);
	DDX_Control(pDX, IDC_BAUDRATE, m_BaudRate);
	DDX_Control(pDX, IDC_EDIT6, m_Receive);
	DDX_Control(pDX, IDC_EDIT5, m_Send);
}

BEGIN_MESSAGE_MAP(CMFCEx02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_AddR, &CMFCEx02Dlg::OnBtnClickedAddR)
	ON_BN_CLICKED(IDC_AddC, &CMFCEx02Dlg::OnBtnClickedAddC)
	ON_BN_CLICKED(IDC_DEL, &CMFCEx02Dlg::OnBnClickedDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CMFCEx02Dlg::OnLvnItemchangedList)
	//ON_STN_CLICKED(IDC_View, &CMFCEx02Dlg::OnStnClickedView)
	ON_CBN_DROPDOWN(IDC_COMPORT, &CMFCEx02Dlg::OnCbnDropdownComport)
	ON_CBN_DROPDOWN(IDC_BAUDRATE, &CMFCEx02Dlg::OnCbnDropdownBaudRate)
	ON_BN_CLICKED(IDC_CONNECT, &CMFCEx02Dlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_UNCONNECT, &CMFCEx02Dlg::OnBnClickedUnconnect)
	ON_BN_CLICKED(IDC_SEND, &CMFCEx02Dlg::OnBnClickedSend)
END_MESSAGE_MAP()

// CMFCEx02Dlg 메시지 처리기

BOOL CMFCEx02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.

	CMenu* pSysMenu = GetSystemMenu(FALSE);


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);            // 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);        // 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// m_PictureControl.SubclassDlgItem(IDC_View, this);
	obj_Type = 0;
	count_R = 0;
	count_C = 0;
	count_T = 0;

	objData;

	m_Pic.GetClientRect(&view);
	/*
	#define CBR_110             110
	#define CBR_300             300
	#define CBR_600             600
	#define CBR_1200            1200
	#define CBR_2400            2400
	#define CBR_4800            4800
	#define CBR_9600            9600
	#define CBR_14400           14400
	#define CBR_19200           19200
	#define CBR_38400           38400
	#define CBR_56000           56000
	#define CBR_57600           57600
	#define CBR_115200          115200
	#define CBR_128000          128000
	#define CBR_256000          256000
	*/
	// 보드레이트 콤보박스 초기화
	m_BaudRate.AddString(_T("9600"));
	m_BaudRate.AddString(_T("14400"));
	m_BaudRate.AddString(_T("19200"));
	m_BaudRate.AddString(_T("38400"));
	m_BaudRate.AddString(_T("56000"));
	m_BaudRate.AddString(_T("57600"));
	m_BaudRate.AddString(_T("115200"));
	m_BaudRate.AddString(_T("256000"));
<<<<<<< HEAD
	m_BaudRate.SetCurSel(0);

	m_Comport.SetCurSel(0);
=======
	m_BaudRate.SetCurSel(0); // 기본값 설정
>>>>>>> a403ade4f722a643b830640b5e263c83868067ff


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCEx02Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (view.Width() - cxIcon + 1) / 2;
		int y = (view.Height() - cyIcon + 1) / 2;
		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{

		CDialogEx::OnPaint();
		// IDC_VIEW (m_Pic) 컨트롤의 중앙에 수직선과 수평선 그리기
		//주의
		CPaintDC dc(&m_Pic);
		// 흰색 사각형 그리기
		CBrush whiteBrush(WHITE); // 흰색 브러시 생성
		dc.SelectObject(&whiteBrush); // 흰색 브러시 선택

		CRect whiteRect(view.left, view.top, view.right, view.bottom); // 중심을 기준으로 사각형 크기 설정
		dc.Rectangle(whiteRect); // 사각형 그리기

		vCenterX = view.left + view.Width() / 2;
		vCenterY = view.top + view.Height() / 2;

		// 수직선 그리기
		dc.MoveTo(vCenterX, view.top);
		dc.LineTo(vCenterX, view.bottom);

		// 수평선 그리기
		dc.MoveTo(view.left, vCenterY);
		dc.LineTo(view.right, vCenterY);



	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCEx02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCEx02Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	start_Pos = CPoint(point.x - 12, point.y - 12);
	/*
		str.Format(_T("%d"), start_Pos.x);
		center_X.SetWindowText(str);
		str.Format(_T("%d"), start_Pos.y);
		center_Y.SetWindowText(str);*/

}

void CMFCEx02Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);
	point = CPoint(point.x - 12, point.y - 12);
	end_Pos = point;

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_View);
	CRgn rgn;
	rgn.CreateRectRgn(view.left, view.top, view.right, view.bottom);

	UpdateData();
	if (view.PtInRect(point) && view.PtInRect(start_Pos)) {
		switch (obj_Type)
		{
		case 1:
			count_R++;  // 사각형 개수 증가
			obj_Str.Format(_T("Rect %d"), count_R);				// 사각형 이름 설정
			objData.emplace_back(1, start_Pos, point, false);	// 객체 데이터 저장
			m_List.InsertItem(m_List.GetItemCount(), obj_Str);				// 리스트에 객체 추가
			break;
		case 2:
		{
			count_C++;  // 원 개수 증가
			obj_Str.Format(_T("Circle %d"), count_C);			// 원 이름 설정
			objData.emplace_back(2, start_Pos, point, false);	// 객체 데이터 저장
			m_List.InsertItem(m_List.GetItemCount(), obj_Str);				// 리스트에 객체 추가
			break;

		}
		default:
			break;
		}
		//Invalidate();
		onDrawImage();

	}
}

void CMFCEx02Dlg::OnBtnClickedAddR()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	obj_Type = 1;
}

void CMFCEx02Dlg::OnBtnClickedAddC()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	obj_Type = 2;
}

void CMFCEx02Dlg::OnBnClickedDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가
	obj_Type = 0;
	// 선택된 리스트 아이템의 인덱스를 가져옵니다.
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}

	// 선택된 항목의 인덱스를 호출
	int selectedIndex = m_List.GetNextSelectedItem(pos);
	if (selectedIndex >= 0 && selectedIndex < objData.size())
	{
		// objData에서 선택된 항목을 삭제
		objData.erase(objData.begin() + selectedIndex);

		// m_List에서 선택된 항목을 삭제
		m_List.DeleteItem(selectedIndex);
	}

	// 편집 컨트롤에 있는 텍스트 삭제
	center_X.SetWindowText(_T(""));
	center_Y.SetWindowText(_T(""));
	size_X.SetWindowText(_T(""));
	size_Y.SetWindowText(_T(""));
	//Invalidate();
	onDrawImage();
}

void CMFCEx02Dlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Get the selected item index
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		center_X.SetWindowText(_T(""));
		center_Y.SetWindowText(_T(""));
		size_X.SetWindowText(_T(""));
		size_Y.SetWindowText(_T(""));
	}
	else
	{
		while (pos)
		{
			selectedIndex = m_List.GetNextSelectedItem(pos);
			CString str;
			objData[selectedIndex].bSelect = true;
			CPoint sP = objData[selectedIndex].sP;
			CPoint eP = objData[selectedIndex].eP;
			str.Format(_T("%d"), ReScale(CalculateCenter(sP, eP).x));
			center_X.SetWindowText(str);
			str.Format(_T("%d"), ReScale(CalculateCenter(sP, eP).y*(-1)));
			center_Y.SetWindowText(str);
			str.Format(_T("%d"), ReScale(CalculateSize(sP, eP).x));
			size_X.SetWindowText(str);
			str.Format(_T("%d"), ReScale(CalculateSize(sP, eP).y));
			size_Y.SetWindowText(str);
			for (int i = 0; i < (int)objData.size(); i++)
			{
				if (i != selectedIndex)
				{
					objData[i].bSelect = false;
				}
				else
				{
					continue;
				}
			}
			//Invalidate();
			onDrawImage();
		}
	}
	obj_Type = 0;
	*pResult = 0;
}

CPoint CMFCEx02Dlg::CalculateCenter(const CPoint& start, const CPoint& end)
{
	int centerX = (start.x + end.x) / 2 - HALFLENGTH;
	int centerY = (start.y + end.y) / 2 - HALFLENGTH;

	return CPoint(centerX, centerY);
}

CPoint CMFCEx02Dlg::CalculateSize(const CPoint start, const CPoint end)
{
	int sizeX = std::abs(start.x - end.x);
	int sizeY = std::abs(start.y - end.y);
	return CPoint(sizeX, sizeY);
}

CPoint CMFCEx02Dlg::ReScale(CPoint point)
{
	return CPoint(point.x * 100 / view.Width(), point.y * 100 / view.Height());
}

void CMFCEx02Dlg::drawEllipse(CDC* pDC, const CPoint& center, const CPoint& radius)
{
	// 타원을 360도로 나누어 점을 찍음
	for (int angle = 0; angle < 361; angle++)
	{
		// 각도를 라디안으로 변환
		double radians = angle * M_PI / 180.0;

		int x = center.x + (int)(radius.x * cos(radians) / 2);
		int y = center.y - (int)(radius.y * sin(radians) / 2);

		if (angle == 0) {
			pDC->MoveTo(x, y);
		}
		else {
			pDC->LineTo(x, y);
		}
	}
}

void CMFCEx02Dlg::drawRectangle(CDC* pDC, const CPoint& start, const CPoint& end)
{
	pDC->MoveTo(start);
	pDC->LineTo(start.x, end.y);
	pDC->LineTo(end.x, end.y);
	pDC->LineTo(end.x, start.y);
	pDC->LineTo(start);


}

void CMFCEx02Dlg::drawShape(int type, CDC* pDC, CPoint sP, CPoint eP)
{
	switch (type)
	{
	case 1:
		drawRectangle(pDC, sP, eP);
		break;
	case 2:
	{
		CPoint radius = CalculateSize(sP, eP);
		CPoint center = CalculateCenter(sP, eP);
		center.x += HALFLENGTH;
		center.y += HALFLENGTH;
		drawEllipse(pDC, center, radius);
	}
	break;
	default:
		break;
	}
}

void CMFCEx02Dlg::onDrawImage()
{
	// Picture Control 가져오기
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_View);

	// Picture Control DC 가져오기
	CDC* pDC = pStatic->GetDC();

	// Picture Control의 클라이언트 영역 크기 구하기
	CRect view;
	pStatic->GetClientRect(&view);

	// 메모리 DC와 비트맵 생성
	CDC memDC;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, view.Width(), view.Height());

	// 비트맵을 메모리 DC에 선택
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// 임시 버퍼(memDC)에 그리기 작업 수행
	// memDC.FillSolidRect(view, RGB(0, 0, 0)); // 검은색 배경

	// 흰색 사각형 그리기
	CBrush whiteBrush(WHITE); // 흰색 브러시 생성
	memDC.SelectObject(&whiteBrush); // 흰색 브러시 선택
	memDC.Rectangle(view.left, view.top, view.right, view.bottom);

	int vCenterX = view.left + view.Width() / 2;
	int vCenterY = view.top + view.Height() / 2;

	// 수직선 그리기
	memDC.MoveTo(vCenterX, view.top);
	memDC.LineTo(vCenterX, view.bottom);

	// 수평선 그리기
	memDC.MoveTo(view.left, vCenterY);
	memDC.LineTo(view.right, vCenterY);

	// 기본 펜 설정
	CPen default_pen(PS_SOLID, 2, LIGHTBLUE);
	CPen* pOldPen = memDC.SelectObject(&default_pen);

	// 브러시 설정
	memDC.SelectStockObject(NULL_BRUSH);

	// 그리기 영역 설정
	CRgn rgn;
	rgn.CreateRectRgn(view.left, view.top, view.right, view.bottom);
	memDC.SelectClipRgn(&rgn);

	// 기존에 저장된 도형 그리기
	int sIndex = -1;
	for (int i = 0; i < objData.size(); ++i)
	{
		if (!objData[i].bSelect)
		{
			// 기본 펜으로 그리기
			drawShape(objData[i].type, &memDC, objData[i].sP, objData[i].eP);
		}
		else
		{
			sIndex = i;
		}
	}

	// 선택된 도형 빨간 펜으로 그리기
	if (sIndex != -1)
	{
		CPen red_pen(PS_SOLID, 2, LIGHTRED);
		CPen* pOldPenTemp = memDC.SelectObject(&red_pen);

		drawShape(objData[sIndex].type, &memDC, objData[sIndex].sP, objData[sIndex].eP);

		// 원래 펜으로 복원
		memDC.SelectObject(pOldPenTemp);
	}

	// 그리기 영역 해제
	memDC.SelectClipRgn(NULL);

	// 메모리 DC에서 비트맵을 화면 DC로 복사하여 출력
	pDC->BitBlt(view.left, view.top, view.Width(), view.Height(), &memDC, 0, 0, SRCCOPY);

	// 자원 해제
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	// Picture Control DC 해제
	pStatic->ReleaseDC(pDC);
}

void CMFCEx02Dlg::getSerialPort(){
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	m_Comport.ResetContent();
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL)){
		index++;
		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		m_Comport.AddString(CString(szData));

		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}
	RegCloseKey(hKey);
}

void CMFCEx02Dlg::OnCbnDropdownComport()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가
	getSerialPort();

}


void CMFCEx02Dlg::OnCbnDropdownBaudRate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가
	// 보드레이트 선택 이벤트 처리
	int sel = m_BaudRate.GetCurSel();
	CString strBaudRate;
	m_BaudRate.GetLBText(sel, strBaudRate);
	int baudRate = _ttoi(strBaudRate);

	// TODO: 선택된 보드레이트를 사용하여 시리얼 통신 설정
	// 예: SetBaudRate(baudRate);
}


void CMFCEx02Dlg::OnBnClickedConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가
	int selComport = m_Comport.GetCurSel();
	if (selComport == CB_ERR) {
		AfxMessageBox(_T("No COM Port Selected"));
		return;
	}

	CString strComport;
	m_Comport.GetLBText(selComport, strComport);

	int selBaudRate = m_BaudRate.GetCurSel();
	if (selBaudRate == CB_ERR) {
		AfxMessageBox(_T("No Baud Rate Selected"));
		return;
	}

	CString strBaudRate;
	m_BaudRate.GetLBText(selBaudRate, strBaudRate);
	int baudRate = _ttoi(strBaudRate);

	

	// 3. 시리얼 포트 설정 및 연결
	g_RsPort.initComport(strComport, baudRate);
	if (g_RsPort.IsCommPortOpen()){
	AfxMessageBox(_T("포트가 열렸습니다."));
	}
	else
	{
	AfxMessageBox(_T("WARNING : 포트를 여는데 실패하였습니다."));
	}
	

	/*
	// 3. 시리얼 포트 설정 및 연결
	if (m_serialPort.OpenPort(strComport)) {
		if (m_serialPort.ConfigurePort(baudRate, 8, NOPARITY, ONESTOPBIT)) {
			if (m_serialPort.StartCommunication()) {
				AfxMessageBox(_T("Connected Successfully"));
			}
			else {
				AfxMessageBox(_T("Failed to Start Communication"));
				m_serialPort.ClosePort();
			}
		}
		else {
			AfxMessageBox(_T("Failed to Configure Port"));
			m_serialPort.ClosePort();
		}
	}
	else {
		AfxMessageBox(_T("Failed to Open Port"));
	}
	*/
}


void CMFCEx02Dlg::OnBnClickedUnconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	g_RsPort.CloseCommPort();

}


void CMFCEx02Dlg::OnBnClickedSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
<<<<<<< HEAD
	CString str_Send;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(str_Send); // 컨트롤에서 텍스트 가져오기

	// CString에서 문자열 길이 가져오기
	DWORD dwLength = str_Send.GetLength()*2;

	// CString을 unsigned char*로 변환
	unsigned char* p_str = reinterpret_cast<unsigned char*>(str_Send.GetBuffer());

	// 데이터 전송
	g_RsPort.WriteCommPort(p_str, dwLength);

	// 버퍼 해제
	str_Send.ReleaseBuffer();
}


void CMFCEx02Dlg::OnReadComPort()
{
	char buffer[1024] = { 0 }; // 적절한 크기의 버퍼 할당
	int bytesRead = g_RsPort.ReadCommPort(buffer, sizeof(buffer) - 1);

	if (bytesRead > 0)
	{
		buffer[bytesRead] = '\0'; // 널 종료 문자 추가
		CString str_Receive = __PCharToCStringInUnicode(buffer);
		m_Receive.SetWindowTextW(str_Receive);
	}
}


CString CMFCEx02Dlg::__PCharToCStringInUnicode(char* char_str)
{
	wchar_t* wchar_str = NULL;
	CString cstring_str;
	int char_str_len = 0;

	// 멀티바이트 문자열(char*)을 유니코드 문자열(wchar_t*)로 변환하기 위한 길이 계산
	char_str_len = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, char_str, -1, NULL, NULL);
	wchar_str = new wchar_t[char_str_len + 1]; // 변환된 유니코드 문자열을 저장할 메모리 할당
	MultiByteToWideChar(CP_ACP, 0, char_str, -1, wchar_str, char_str_len); // 변환 수행

	wchar_str[char_str_len] = _T('\0'); // 널 종료 문자 추가
	cstring_str.Format(_T("%s"), wchar_str); // CString에 유니코드 문자열 설정
	delete[] wchar_str; // 할당된 메모리 해제
	return cstring_str;
}


static char* __CStringToPCharInUnicode(CString str)
{
	wchar_t* wchar_str = NULL;
	char*    char_str = NULL;
	int      char_str_len = 0;

	wchar_str = str.GetBuffer(str.GetLength()); // CString 내부의 유니코드 버퍼 가져오기
	str.ReleaseBuffer(); // CString 버퍼 해제

	// 유니코드 문자열(wchar_t*)을 멀티바이트 문자열(char*)로 변환하기 위한 길이 계산
	char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
	char_str = new char[char_str_len + 1]; // 변환된 문자열을 저장할 메모리 할당
	WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0, 0); // 변환 수행

	char_str[char_str_len] = '\0'; // 널 종료 문자 추가
	return char_str;
}

static CString __PCharToCStringInUnicode(char* char_str)
{
	wchar_t* wchar_str = NULL;
	CString  cstring_str;
	int      char_str_len = 0;

	char_str_len = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, char_str, -1, NULL, NULL);
	wchar_str = new wchar_t[char_str_len + 1];
	MultiByteToWideChar(CP_ACP, 0, char_str, -1, wchar_str, char_str_len);

	wchar_str[char_str_len] = _T('\0');
	cstring_str.Format(_T("%s"), wchar_str);
	delete[] wchar_str;
	return cstring_str;
}
=======

}




void CMFCEx02Dlg::OnReadComPort()
{
	CString str_Receive = g_RsPort.ReadCommPort();

	m_Receive.SetWindowTextW(str_Receive);
}
>>>>>>> a403ade4f722a643b830640b5e263c83868067ff
