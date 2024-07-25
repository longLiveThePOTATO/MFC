// MFCEx02Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCEx02.h"
#include "MFCEx02Dlg.h"


#ifdef _DEBUG
#define M_PI 3.14159265358979323846
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

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
	DDX_Control(pDX, IDC_View, m_Pic);
	DDX_Control(pDX, IDC_EDIT1, center_X);
	DDX_Control(pDX, IDC_EDIT2, center_Y);
	DDX_Control(pDX, IDC_EDIT3, size_X);
	DDX_Control(pDX, IDC_EDIT4, size_Y);
	DDX_Control(pDX, IDC_COMPORT, m_Comport);
	DDX_Control(pDX, IDC_BAUDRATE, m_BaudRate);
	DDX_Control(pDX, IDC_EDIT5, m_Send);
	DDX_Control(pDX, IDC_EDIT6, m_Receive);
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
	ON_CBN_DROPDOWN(IDC_COMPORT, &CMFCEx02Dlg::OnCbnDropdownComport)
	ON_CBN_DROPDOWN(IDC_BAUDRATE, &CMFCEx02Dlg::OnCbnDropdownBaudRate)
	ON_BN_CLICKED(IDC_CONNECT, &CMFCEx02Dlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_UNCONNECT, &CMFCEx02Dlg::OnBnClickedUnconnect)
	ON_BN_CLICKED(IDC_SEND, &CMFCEx02Dlg::OnBnClickedSend)
	//ON_MESSAGE(WM_RECEIVED_COMM, &CMFCEx02Dlg::OnReadComport)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCEx02Dlg 메시지 처리기

BOOL CMFCEx02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.


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
	// 보드레이트 콤보박스 초기화
	m_BaudRate.AddString(_T("B50"));
	m_BaudRate.AddString(_T("B75"));
	m_BaudRate.AddString(_T("B110"));
	m_BaudRate.AddString(_T("B134"));
	m_BaudRate.AddString(_T("B150"));
	m_BaudRate.AddString(_T("B300"));
	m_BaudRate.AddString(_T("B600"));
	m_BaudRate.AddString(_T("B1200"));
	m_BaudRate.AddString(_T("B1800"));
	m_BaudRate.AddString(_T("B2400"));
	m_BaudRate.AddString(_T("B4800"));
	m_BaudRate.AddString(_T("B7200"));
	m_BaudRate.AddString(_T("B9600"));
	m_BaudRate.AddString(_T("B19200"));
	m_BaudRate.AddString(_T("B38400"));
	m_BaudRate.AddString(_T("B57600"));
	m_BaudRate.AddString(_T("B115200"));
	m_BaudRate.AddString(_T("B230400"));
	m_BaudRate.AddString(_T("B230400"));
	m_BaudRate.AddString(_T("B460800"));
	m_BaudRate.AddString(_T("B921600"));
	m_BaudRate.SetCurSel(0);

	m_Comport.AddString(_T("COM1"));
	m_Comport.AddString(_T("COM2"));
	m_Comport.AddString(_T("COM3"));
	m_Comport.AddString(_T("COM4"));
	m_Comport.AddString(_T("COM5"));
	m_Comport.AddString(_T("COM6"));
	m_Comport.AddString(_T("COM7"));
	m_Comport.AddString(_T("COM8"));
	m_Comport.AddString(_T("COM9"));
	m_Comport.SetCurSel(0);

	g_hWnd = GetSafeHwnd();

	// 타이머 설정
	SetTimer(TIMER_ID, TIMER_INTERVAL, NULL);
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

// 이벤트 핸들러
void CMFCEx02Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	start_Pos = CPoint(point.x - 12, point.y - 12);
}

void CMFCEx02Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);
	point = CPoint(point.x - 12, point.y - 12);
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_View);
	CRgn rgn;
	rgn.CreateRectRgn(view.left, view.top, view.right, view.bottom);

	UpdateData();
	if (view.PtInRect(point) && view.PtInRect(start_Pos)) {	
		CFPoint startPoint(start_Pos);  // CPoint를 CFPoint로 변환
		CFPoint endPoint(point);        // CPoint를 CFPoint로 변환
		CFPoint center;
		center = center.CalculateCenter(startPoint, endPoint).Offset(HALFLENGTH*(-1), HALFLENGTH*(-1));
		center = Scale(center);
		CFPoint size;
		size = Scale(startPoint.DistancePairTo(endPoint));
		switch (obj_Type)
		{
		case 1:
			count_R++;  // 사각형 개수 증가
			obj_Str.Format(_T("Rect %d"), count_R);  // 사각형 이름 설정
			objData.emplace_back(1, center, size, false);  // 객체 데이터 저장
			m_List.InsertItem(m_List.GetItemCount(), obj_Str);  // 리스트에 객체 추가
			break;
		case 2:
			count_C++;  // 원 개수 증가
			obj_Str.Format(_T("Circle %d"), count_C);  // 원 이름 설정
			objData.emplace_back(2, center, size, false);  // 객체 데이터 저장
			m_List.InsertItem(m_List.GetItemCount(), obj_Str);  // 리스트에 객체 추가
			break;
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
	// 선택된 항목의 인덱스를 호출
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
		do
		{
			selectedIndex = m_List.GetNextSelectedItem(pos);
			CString str;
			objData[selectedIndex].bSelect = true;
			CFPoint center = objData[selectedIndex].cP;
			CFPoint sizeP = objData[selectedIndex].size;
			str.Format(_T("%f"),center.x);
			center_X.SetWindowText(str);
			str.Format(_T("%f"), center.y);
			center_Y.SetWindowText(str);
			str.Format(_T("%f"), sizeP.x);
			size_X.SetWindowText(str);
			str.Format(_T("%f"), sizeP.y);
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
			onDrawImage();
		} while (pos);
	}
	obj_Type = 0;
	*pResult = 0;
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

}

void CMFCEx02Dlg::OnBnClickedConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가
	int selComport = m_Comport.GetCurSel();
	if (selComport == CB_ERR) {
		AfxMessageBox(_T("No COM Port Selected"));
		return;
	}

	// ComboBox에서 선택한 항목이 0부터 시작하므로 1을 더해 실제 포트 번호로 사용합니다.
	short port = selComport + 1;

	int selBaudRate = m_BaudRate.GetCurSel();
	if (selBaudRate == CB_ERR) {
		AfxMessageBox(_T("No Baud Rate Selected"));
		return;
	}

	long baudRate = GetBaudRate(selBaudRate);
	int mode = BIT_8 | STOP_1 | P_NONE;
	char irq = 'E'; // 이벤트 기반 인터럽트
	BOOL bEvent = TRUE; // 이벤트 사용

	if (g_Comm.COpen(this->m_hWnd, port, baudRate, mode, irq, bEvent)) {
		AfxMessageBox(_T("Connected successfully"));
	}
	else {
		AfxMessageBox(_T("Failed to open COM port"));
	}
}

void CMFCEx02Dlg::OnBnClickedUnconnect()
{

	g_Comm.CClose();
}

void CMFCEx02Dlg::OnBnClickedSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str_Send;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(str_Send); // 컨트롤에서 텍스트 가져오기

	g_Comm.CWrite(str_Send);
}

void CMFCEx02Dlg::OnReadComPort(){
	CString str_Receive;
	if (g_Comm.CRead(str_Receive)) {
		m_Receive.SetWindowTextW(str_Receive);
		CommandProcs(str_Receive);
	}

	/*	std::vector<CString> tokens = split(str_Receive, _T(";"));

	if (!tokens.empty() && tokens[0] == _T("S")) {
	if (tokens.size() < 2) { // 커맨드가 존재하는지 확인
	AfxMessageBox(_T("Invalid command format: missing command"));
	return;
	}
	CString cmdStr = tokens[1]; // 두 번째 토큰을 커맨드로 설정

	//		Command cmd = stringToCommand(cmdStr); // 커맨드를 enum으로 변환

	}*/
}


//유틸리티 함수
void CMFCEx02Dlg::drawEllipse(CDC* pDC, const CFPoint& center, const CFPoint& size)
{
	// 타원을 360도로 나누어 점을 찍음
	for (int angle = 0; angle < 361; angle++)
	{
		// 각도를 라디안으로 변환
		double radians = angle * M_PI / 180.0;

		// 타원의 방정식을 사용하여 좌표 계산
		int x = center.x + (int)(size.x * cos(radians) / 2);
		int y = center.y - (int)(size.y * sin(radians) / 2);

		if (angle == 0) {
			pDC->MoveTo(x, y);
		}
		else {
			pDC->LineTo(x, y);
		}
	}
}

void CMFCEx02Dlg::drawRectangle(CDC* pDC, const CFPoint& center, const CFPoint& size)
{
	// 사각형의 각 좌표를 계산
	int left = center.x - (size.x / 2);
	int top = center.y - (size.y / 2);
	int right = center.x + (size.x / 2);
	int bottom = center.y + (size.y / 2);

	// 사각형 그리기
	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);
	pDC->LineTo(right, bottom);
	pDC->LineTo(right, top);
	pDC->LineTo(left, top);
}

void CMFCEx02Dlg::drawShape(int type, CDC* pDC, const CFPoint& center, const CFPoint& size)
{
	CFPoint scaledSize = ReScale(size);
	CFPoint offsetCenter = ReScale(center).Offset(HALFLENGTH, HALFLENGTH);

	switch (type)
	{
	case 1:
		// 사각형 그리기
		drawRectangle(pDC, offsetCenter, scaledSize);
		break;
	case 2:
		// 타원 그리기
		drawEllipse(pDC, offsetCenter, scaledSize);
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
			drawShape(objData[i].type, &memDC, objData[i].cP, objData[i].size);
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

		drawShape(objData[sIndex].type, &memDC, objData[sIndex].cP, objData[sIndex].size);

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


// Serial 통신
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

long CMFCEx02Dlg::GetBaudRate(int index)
{
	switch (index)
	{
	case 0: return B50;
	case 1: return B75;
	case 2: return B110;
	case 3: return B134;
	case 4: return B150;
	case 5: return B300;
	case 6: return B600;
	case 7: return B1200;
	case 8: return B1800;
	case 9: return B2400;
	case 10: return B4800;
	case 11: return B7200;
	case 12: return B9600;
	case 13: return B19200;
	case 14: return B38400;
	case 15: return B57600;
	case 16: return B115200;
	case 17: return B230400;
	case 18: return B460800;
	case 19: return B921600;
	default: return false; // 기본값으로 설정
	}
}

void CMFCEx02Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID&&g_Comm.CommCheck())
	{
		OnReadComPort(); // 타이머 이벤트 발생 시 시리얼 포트 데이터 읽기
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCEx02Dlg::OnDestroy()
{
	KillTimer(TIMER_ID); // 타이머 해제
	CDialogEx::OnDestroy();
}


// 유틸리티
CFPoint CMFCEx02Dlg::Scale(const CFPoint& point)
{
	// 스케일링 연산
	CFPoint scaledPoint(
		point.x * 100.0f / view.Width(),
		point.y * (-100.0f) / view.Height()
		);

	// 소수점 세 자리로 반올림
	return scaledPoint.RoundToThreeDecimalPlaces(scaledPoint);
}

CFPoint CMFCEx02Dlg::ReScale(const CFPoint& point)
{
	// 리스케일링 연산
	CFPoint rescaledPoint(
		point.x / 100.0f * view.Width(),
		point.y / (-100.0f) * view.Height()
		);

	// 소수점 세 자리로 반올림
	return rescaledPoint.RoundToThreeDecimalPlaces(rescaledPoint);
}

std::vector<CString> CMFCEx02Dlg::split(const CString& s) {
	std::vector<CString> tokens;
	int start = 0;
	int end = s.Find(delimiter);

	// 구분자가 문자열에 존재하는 동안 반복
	while (end != -1) {
		tokens.push_back(s.Mid(start, end - start));
		start = end + delimiter.GetLength();
		end = s.Find(delimiter, start);
	}

	// 마지막 토큰 추가
	tokens.push_back(s.Mid(start));

	return tokens;
}


Command CMFCEx02Dlg::StringToCommand(CString commandStr) {
	if (commandStr.CompareNoCase(_T("Add")) == 0) {
		return ADD;
	}
	else if (commandStr.CompareNoCase(_T("Delete")) == 0) {
		return DEL;
	}
	else if (commandStr.CompareNoCase(_T("GetCount")) == 0) {
		return GETCOUNT;
	}
	else if (commandStr.CompareNoCase(_T("GetObj")) == 0) {
		return GETOBJ;
	}
	else {
		return INVALID;
	}
}

int CMFCEx02Dlg::CommandProcs(const CString& s)
{
	std::vector<CString> tokens = split(s);
	int s_f = 0;
	CString str_Response = _T("");

	// 첫 번째 토큰이 "S"이고 마지막 토큰이 "E"인지 확인
	if (!tokens.empty() && tokens[0] == _T("S") && tokens.back() == _T("E")) {
		// 커맨드가 존재하는지 확인
		if (tokens.size() < 3) {
			return Response(s_f, str_Response); // Invalid format
		}

		// 두 번째 토큰을 커맨드로 설정
		CString cmdStr = tokens[1];
		// 커맨드를 enum으로 변환
		Command cmd = StringToCommand(cmdStr);

		// 커맨드에 따라 처리
		switch (cmd) {
		case ADD:
			if (tokens.size() != 8) {
				return Response(s_f, str_Response); // Incorrect number of tokens
			}
			if (tokens[2] == _T("Rect")) {
				// 형식 검증
				if (!IsValidFloat(tokens[3]) || !IsValidFloat(tokens[4]) ||
					!IsValidFloat(tokens[5]) || !IsValidFloat(tokens[6])) {
					return Response(s_f, str_Response); // Incorrect float values
				}
				count_R++;  // 사각형 개수 증가
				obj_Str.Format(_T("Rect %d"), count_R);  // 사각형 이름 설정
				objData.emplace_back(1, CFPoint(tokens[3], tokens[4]), CFPoint(tokens[5], tokens[6]), false);  // 객체 데이터 저장
				m_List.InsertItem(m_List.GetItemCount(), obj_Str);  // 리스트에 객체 추가
				s_f++;
				break;
			}
			else if (tokens[2] == _T("Arc")) {
				// 형식 검증
				if (!IsValidFloat(tokens[3]) || !IsValidFloat(tokens[4]) ||
					!IsValidFloat(tokens[5]) || !IsValidFloat(tokens[6])) {
					return Response(s_f, str_Response); // Incorrect float values
				}
				count_R++;  // 사각형 개수 증가
				obj_Str.Format(_T("Arc %d"), count_R);  // 호 이름 설정
				objData.emplace_back(2, CFPoint(tokens[3], tokens[4]), CFPoint(tokens[5], tokens[6]), false);  // 객체 데이터 저장
				m_List.InsertItem(m_List.GetItemCount(), obj_Str);  // 리스트에 객체 추가
				s_f++;
				break;
			}
			else {
				return Response(s_f, str_Response); // Unknown shape type
			}

		case DEL:
			if (tokens.size() != 3) {
				return Response(s_f, str_Response); // Incorrect number of tokens
			}
			{
				int index = _ttoi(tokens[2]);
				if (index < 0 || index >= m_List.GetItemCount()) {
					return Response(s_f, str_Response); // Index out of range
				}
				// 리스트의 항목을 선택
				m_List.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
				// 선택된 항목을 삭제
				OnBnClickedDel();
			}
			s_f++;
			break;

		case GETCOUNT:
			if (tokens.size() != 2) {
				return Response(s_f, str_Response); // Incorrect number of tokens
			}
			{
				int count = objData.size();
				str_Response.Format(_T("%d"), count);
				s_f = 3;
			}
			break;

		case GETOBJ:
			if (tokens.size() != 3) {
				return Response(s_f, str_Response); // Incorrect number of tokens
			}
			{
				int index = _ttoi(tokens[2]);
				if (index < 0 || index >= m_List.GetItemCount()) {
					return Response(s_f, str_Response); // Index out of range
				}
				// 리스트 컨트롤의 상태가 변경되었음을 알리기 위해 OnLvnItemchangedList 호출을 유도
				NM_LISTVIEW nmListView;
				memset(&nmListView, 0, sizeof(nmListView));  // 초기화
				nmListView.hdr.hwndFrom = m_List.m_hWnd;
				nmListView.hdr.idFrom = IDC_LIST;
				nmListView.hdr.code = LVN_ITEMCHANGED;
				nmListView.iItem = index;
				nmListView.iSubItem = 0;
				nmListView.uNewState = LVIS_SELECTED;
				nmListView.uOldState = 0;
				nmListView.uChanged = LVIF_STATE;
				nmListView.ptAction.x = 0;
				nmListView.ptAction.y = 0;
				nmListView.lParam = 0;

				// 리스트 컨트롤의 부모 윈도우로 메시지를 보내어 이벤트 핸들러 호출 유도
				m_List.SendMessage(WM_NOTIFY, IDC_LIST, (LPARAM)&nmListView);

				CString centerXStr;
				CString centerYStr;
				CString sizeXStr;
				CString sizeYStr;

				// CEdit 컨트롤에서 문자열 가져오기
				center_X.GetWindowText(centerXStr);
				center_Y.GetWindowText(centerYStr);
				size_X.GetWindowText(sizeXStr);
				size_Y.GetWindowText(sizeYStr);
				str_Response.Format(_T("%s; %s; %s; %s"), centerXStr, centerYStr, sizeXStr, sizeYStr);
				s_f++;
			}
			break;

		default:
			return Response(s_f, str_Response); // Invalid command
		}

		onDrawImage();
		return Response(s_f, str_Response);

	}
	else {
		return Response(s_f, str_Response); // Invalid format
	}
}

int CMFCEx02Dlg::Response(int s_f, CString str_Response)
{
	
	switch (s_f){
	case 0: 
		str_Response = _T("Fail");
		break;
	case 1:
		str_Response = _T("Success");
		break;
	default:
		break;
	}
	if (s_f == 1)	str_Response = _T("Success");
	m_Send.SetWindowTextW(str_Response);
	g_Comm.CWrite(str_Response);
	return s_f;
}

bool CMFCEx02Dlg::IsValidFloat(const CString& str)
{
	// CString을 C 스타일 문자열로 변환
	CT2CA pszConvertedAnsiString(str);
	std::string stdStr(pszConvertedAnsiString);

	// std::string을 float로 변환
	char* end;
	std::strtof(stdStr.c_str(), &end);

	// 변환 결과가 문자열의 끝까지 읽었는지 확인
	return (*end == '\0');
}
