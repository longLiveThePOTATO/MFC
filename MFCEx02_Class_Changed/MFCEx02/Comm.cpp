#include "stdafx.h"
#include "Comm.h"


// 전역 변수
HWND g_hWnd; // 윈도우 핸들
VOID CALLBACK TermIrq(int port); // IRQ 콜백 함수 선언

//////////////////////////////////////////////////////////////////////
// 생성자/소멸자
//////////////////////////////////////////////////////////////////////

Comm::Comm()
{
	m_nPort = 0;     // 포트 번호 초기화
	m_nError = 0;    // 오류 코드 초기화
	m_nResult = 0;   // 결과 코드 초기화

	m_bOpen = FALSE; // 포트 열림 상태 플래그 초기화
	g_hWnd = NULL;   // 윈도우 핸들 초기화
}

Comm::~Comm()
{
	// 소멸자에서 리소스 정리는 필요 없음
}

BOOL Comm::COpen(HWND hWnd, int port, int baudrate, int mode, const char irq, BOOL bEvent)
{
	if (m_bOpen)
		CClose(); // 이미 열려 있으면 포트를 닫음

	// 하드웨어 및 소프트웨어 흐름 제어 설정
	int hw = FALSE ? 3 : 0;
	int sw = FALSE ? 12 : 0;

	if (m_bOpen) return TRUE; // 이미 열려 있으면 TRUE 반환

	// 포트 열기 및 설정
	if (sio_open(port) != SIO_OK) return FALSE;
	if (sio_ioctl(port, baudrate, mode) != SIO_OK) return FALSE;
	if (sio_flowctrl(port, hw | sw) != SIO_OK) return FALSE;
	if (sio_DTR(port, (FALSE ? 1 : 0)) != SIO_OK) return FALSE;
	if (sio_RTS(port, (TRUE ? 1 : 0)) != SIO_OK) return FALSE;

	// 읽기/쓰기 타임아웃 설정
	sio_SetReadTimeouts(2, MAXDWORD, 0);
	sio_SetWriteTimeouts(port, MAXDWORD);

	// 버퍼 플러시 및 대기
	sio_flush(port, 2);
	Waitmsec(100);

	m_nPort = port; // 포트 번호 저장
	m_bOpen = TRUE; // 포트 열림 상태 플래그 설정

	if (bEvent)
	{
		g_hWnd = hWnd; // 윈도우 핸들 저장

		// IRQ 핸들러 등록
		m_nResult = sio_term_irq(m_nPort, TermIrq, irq);
		if (m_nResult != SIO_OK)
		{
			TRACE(_T("COM%d : Event fault!\n"), port); // 이벤트 오류 메시지 출력
			CClose();
			return FALSE;
		}
	}

	return TRUE; // 성공적으로 열었음을 반환
}

bool Comm::COpen(short port, long baudrate)
{
	if (m_bOpen)
		CClose();

	// Comm포트 초기 셋팅
	int hw = FALSE ? 3 : 0;
	int sw = FALSE ? 12 : 0;
	if (m_bOpen)															return TRUE;
	if (sio_open(port) != SIO_OK)									return FALSE;
	if (sio_ioctl(port, baudrate, P_NONE | BIT_8 | STOP_1) != SIO_OK) 		return FALSE;
	if (sio_flowctrl(port, hw | sw) != SIO_OK)					return FALSE;
	if (sio_DTR(port, (FALSE ? 1 : 0)) != SIO_OK)				return FALSE;
	if (sio_RTS(port, (TRUE ? 1 : 0)) != SIO_OK)					return FALSE;

	int nReternValue;
	nReternValue = sio_SetReadTimeouts(2, MAXDWORD, 0);
	nReternValue = sio_SetWriteTimeouts(port, MAXDWORD);

	DWORD timeout, intervaltime;
	sio_GetReadTimeouts(port, &timeout, &intervaltime);
	TRACE(_T("[Read] TotalTimeout = %d, IntervalTime = %d\r\n"), timeout, intervaltime);
	sio_GetWriteTimeouts(port, &timeout);
	TRACE(_T("[Write] TotalTimeout = %d\r\n"), timeout);

	// Input/Output 버퍼 초기화
	nReternValue = sio_flush(port, 2);
	Sleep(100);

	m_nPort = port;
	m_bOpen = TRUE;

	return TRUE;
}

void Comm::CClose()
{
	if (m_nResult == SIO_OK)
	{
		// IRQ 핸들러 해제
		sio_term_irq(m_nPort, NULL, 0x00);
		m_nResult = 0;
	}

	if (m_bOpen)
	{
		// 포트 닫기
		sio_close(m_nPort);
		m_bOpen = FALSE;
	}
}

void Comm::Waitmsec(long tw)
{
	time_t s, e;
	e = clock();
	s = e + tw;

	while (e < s) e = clock();
}

//************  Read & Write Functions First  ************//
BOOL Comm::CRead(CString &str)
{
	if (!m_bOpen) return FALSE; // 포트가 열려 있지 않으면 FALSE 반환

	char ch[CHAR_MAX];
	memset(ch, 0, sizeof(ch)); // 버퍼 초기화
	sio_flush(m_nPort, 1); // 포트 플러시

	int len = sio_iqueue(m_nPort); // 수신 대기열의 길이 확인
	if (CHAR_MAX <= (len - 1))
		return FALSE;

	if (len < 1) return FALSE;
	m_nError = sio_read(m_nPort, ch, len); // 데이터 읽기
	ch[len + 1] = '\0'; // 문자열 끝에 널 문자 추가

#ifdef _UNICODE
	str = __PCharToCStringInUnicode(ch); // 유니코드 문자열 변환
#else
	str.Format(_T("%s"), ch); // ASCII 문자열 포맷
#endif

	return TRUE; // 성공 여부 반환		// <- 수신 오류 해결한다고 수정함... 이게 뭐지
}

BOOL Comm::CWrite(CString str)
{
	if (!m_bOpen) return FALSE; // 포트가 열려 있지 않으면 FALSE 반환

	m_nError = sio_flush(m_nPort, 0); // 포트 플러시
	Sleep(50); // 잠시 대기

	int len = str.GetLength(); // 문자열 길이 가져오기
#ifdef _UNICODE
	CHAR* pTemp = __CStringToPCharInUnicode(str); // 유니코드 문자열을 ASCII 문자열로 변환
#else
	CHAR *pTemp = new CHAR[len + 1];
	memset(pTemp, 0x00, len + 1);
	memcpy(pTemp, str.GetBuffer(0), len + 1);
	str.ReleaseBuffer();
#endif

	m_nError = sio_write(m_nPort, pTemp, len); // 데이터 쓰기
	delete[] pTemp; // 동적으로 할당한 메모리 해제
	return (m_nError == SIO_OK); // 성공 여부 반환
}

BOOL Comm::CWrite2(CString str)
{
	if (!m_bOpen) return FALSE; // 포트가 열려 있지 않으면 FALSE 반환

	char ch[512] = {};

	sio_flush(m_nPort, 0); // 포트 플러시
	Sleep(50); // 잠시 대기

	int l = str.GetLength();
	if (l < 510)
	{
		for (int i = 0; i < l; i++)
		{
			ch[i] = (char)str.GetAt(i); // 문자열을 char 배열로 변환
		}
		m_nError = sio_write(m_nPort, ch, l); // 데이터 쓰기
	}

	return (m_nError == SIO_OK); // 성공 여부 반환
}

BOOL Comm::CWrite(CHAR* c, int length)
{
	sio_flush(m_nPort, 0); // 포트 플러시
	Sleep(50); // 잠시 대기

	m_nError = sio_write(m_nPort, c, length); // 데이터 쓰기

	return (m_nError == SIO_OK); // 성공 여부 반환
}

void Comm::CPutch(int c)
{
	if (!m_bOpen) return; // 포트가 열려 있지 않으면 반환

	m_nError = sio_flush(m_nPort, 0); // 포트 플러시
	Sleep(25); // 잠시 대기

	m_nError = sio_putch(m_nPort, c); // 단일 문자 쓰기
	Sleep(50); // 잠시 대기
}

int Comm::CGetch()
{
	if (!m_bOpen) return '\0'; // 포트가 열려 있지 않으면 널 문자 반환

	int c;
	c = sio_getch(m_nPort); // 단일 문자 읽기

	if (c < 0) m_nError = c; // 오류 코드 저장
	return c; // 읽은 문자 반환
}
//************  Read & Write Functions End  ************//

short Comm::ErrorCheck() const
{
	return m_nError; // 마지막 오류 코드 반환
}

BOOL Comm::CommCheck() const
{
	return m_bOpen; // 포트 열림 상태 반환
}

//************  Event Functions End  ************//

VOID CALLBACK TermIrq(int port)
{
	::PostMessage(g_hWnd, WM_RECEIVED_COMM, (WPARAM)port, 0); // 이벤트 발생 시 메시지 전송
}


// 문자열 변환 함수
char* Comm::__CStringToPCharInUnicode(CString str)
{
	wchar_t* wchar_str = NULL;
	char*    char_str = NULL;
	int      char_str_len = 0;

	wchar_str = str.GetBuffer(str.GetLength()); // CString을 wchar_t 배열로 변환
	str.ReleaseBuffer();

	char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
	char_str = new char[char_str_len + 1];  // 메모리 할당
	WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0, 0);

	char_str[char_str_len] = '\0'; // 문자열 끝에 널 문자 추가
	return char_str;
}

CString Comm::__PCharToCStringInUnicode(char* char_str)
{
	wchar_t* wchar_str = NULL;
	CString  cstring_str;
	int      char_str_len = 0;

	char_str_len = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, char_str, -1, NULL, NULL);
	wchar_str = new wchar_t[char_str_len + 1];
	MultiByteToWideChar(CP_ACP, 0, char_str, -1, wchar_str, char_str_len);

	wchar_str[char_str_len] = _T('\0'); // 문자열 끝에 널 문자 추가
	cstring_str.Format(_T("%s"), wchar_str); // CString으로 변환
	delete[] wchar_str; // 동적으로 할당한 메모리 해제
	return cstring_str;
}

