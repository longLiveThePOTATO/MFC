// RsPort.cpp: CRsPort 클래스의 구현 파일입니다.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"  // 표준 시스템 포함 파일
#include "RsPort.h"  // RsPort 클래스 헤더 파일

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 생성자/소멸자
//////////////////////////////////////////////////////////////////////

// 기본 생성자 - 포트 이름을 받아 초기화
CRsPort::CRsPort(CString m_portName)
{
   dcb_setup.BaudRate = CBR_19200;  // 통신 속도 설정 (19200 baud)
   dcb_setup.ByteSize = 8;          // 데이터 비트 수 설정 (8 비트)
   dcb_setup.Parity   = NOPARITY;   // 패리티 비트 없음
   dcb_setup.StopBits = ONESTOPBIT; // 스톱 비트 설정 (1 비트)
   initComport(m_portName);         // 포트 초기화 함수 호출
}

// 매개변수가 있는 생성자 - 포트 이름, 속도를 받아 초기화
CRsPort::CRsPort(CString m_portName, DWORD BaudRate)
{
	dcb_setup.BaudRate = BaudRate;
	dcb_setup.ByteSize = 8;          // 데이터 비트 수 설정 (8 비트)
	dcb_setup.Parity = NOPARITY;   // 패리티 비트 없음
	dcb_setup.StopBits = ONESTOPBIT; // 스톱 비트 설정 (1 비트)
	initComport(m_portName);
}
// 매개변수가 있는 생성자 - 포트 이름, 속도, 데이터 비트, 패리티, 스톱 비트를 받아 초기화
CRsPort::CRsPort(CString m_portName, DWORD BaudRate, BYTE ByteSize, BYTE Parity, BYTE StopBits)
{
	dcb_setup.BaudRate = BaudRate;
	dcb_setup.ByteSize = ByteSize;
	dcb_setup.Parity = Parity;
	dcb_setup.StopBits = StopBits;
	initComport(m_portName);
}

// 소멸자 - 포트를 닫는 함수 호출
CRsPort::~CRsPort()
{
   CloseCommPort();
}

// 포트 초기화 함수
void CRsPort::initComport(CString m_portName)
{
   COMMTIMEOUTS  commTimeOuts;  // 통신 시간 초과 설정 구조체

   // 포트를 연다
   m_idComDev = CreateFile((LPCTSTR)m_portName, GENERIC_READ | GENERIC_WRITE, 
	   0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

   // 포트 열기 실패 시
   if (m_idComDev == (HANDLE)-1)
   {
		CloseHandle(m_idComDev);  // 핸들 닫기
		m_Connect = FALSE;        // 연결 상태를 FALSE로 설정
		// AfxMessageBox(_T("WARNING : 포트를 여는데 실패하였습니다."));
   }
   else
   {
		SetCommMask(m_idComDev, EV_RXCHAR);          // 수신 이벤트 설정
		SetupComm(m_idComDev, 4096, 4096);           // 입출력 버퍼 크기 설정
		PurgeComm(m_idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);  // 통신 포트 초기화

		// 통신 시간 초과 값 설정
		commTimeOuts.ReadIntervalTimeout = -1;
		commTimeOuts.ReadTotalTimeoutMultiplier = 0;
		commTimeOuts.ReadTotalTimeoutConstant = 1000;
		commTimeOuts.WriteTotalTimeoutMultiplier = 0;
		commTimeOuts.WriteTotalTimeoutConstant = 1000;
		SetCommTimeouts(m_idComDev, &commTimeOuts);

		m_Connect = SetupConnection();  // 통신 설정

		// 비동기 I/O를 위한 이벤트 설정
		osWrite.Offset = 0;
		osWrite.OffsetHigh = 0;
		osRead.Offset = 0;
		osRead.OffsetHigh = 0;
		osRead.hEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
		osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   }
}

// 통신 설정 함수
BOOL CRsPort::SetupConnection()
{
   BOOL fRetVal;  // 함수 반환 값
   DCB  dcb;      // 디바이스 제어 블록 구조체
   
   dcb.DCBlength = sizeof(DCB);  // 구조체 크기 설정
   GetCommState(m_idComDev, &dcb);  // 현재 통신 상태 가져오기
   dcb.BaudRate = dcb_setup.BaudRate;  // 설정된 BaudRate로 설정
   dcb.ByteSize = dcb_setup.ByteSize;  // 설정된 ByteSize로 설정
   dcb.Parity   = dcb_setup.Parity;    // 설정된 Parity로 설정
   dcb.StopBits = dcb_setup.StopBits;  // 설정된 StopBits로 설정

   // 기타 통신 설정
   dcb.fOutxDsrFlow = 0;
   dcb.fDtrControl = DTR_CONTROL_ENABLE;
   dcb.fOutxCtsFlow = 0;
   dcb.fRtsControl = RTS_CONTROL_ENABLE;
   dcb.fInX = dcb.fOutX = 0;  // XON/XOFF 사용 안 함
   dcb.XonChar  = 0x11;       // ASCII_XON
   dcb.XoffChar = 0x13;       // ASCII_XOFF
   dcb.XonLim   = 100;
   dcb.XoffLim  = 100;
   dcb.fBinary  = TRUE;
   dcb.fParity  = TRUE;

   // 통신 상태 설정
   fRetVal = SetCommState(m_idComDev, &dcb);
   return fRetVal;  // 설정 결과 반환
}

// 포트 닫기 함수
void CRsPort::CloseCommPort()
{
  if (m_Connect == FALSE) return;  // 연결되어 있지 않으면 반환
  CloseHandle(m_idComDev);         // 포트 핸들 닫기
  CloseHandle(osRead.hEvent);      // 읽기 이벤트 핸들 닫기
  CloseHandle(osWrite.hEvent);     // 쓰기 이벤트 핸들 닫기
}

// 포트에 데이터 쓰기 함수
int CRsPort::WriteCommPort(unsigned char *message, DWORD dwLength)
{
   int ret_code;
   ret_code = WriteFile(m_idComDev, message, dwLength, &dwLength, &osWrite);  // 데이터 쓰기
   return ret_code;  // 결과 반환
}

// 포트에서 데이터 읽기 함수
int CRsPort::ReadCommPort(unsigned char *message, DWORD length)
{
   COMSTAT  ComStat;           // 통신 상태 구조체
   DWORD    dwErrorFlags;      // 오류 플래그
   DWORD    dwLength;          // 데이터 길이
   DWORD    dwReadLength = 0;  // 읽은 데이터 길이

   CStringA strTemp;
   strTemp.Format("%s", message);

   if (m_Connect == FALSE)  return 0;  // 연결되어 있지 않으면 0 반환
   else 
   {
	   ClearCommError(m_idComDev, &dwErrorFlags, &ComStat);  // 통신 오류 플래그 초기화
	   dwLength = min((DWORD)length, ComStat.cbInQue);       // 읽을 데이터 길이 설정
	   ReadFile(m_idComDev, message, dwLength, &dwReadLength, &osRead);  // 데이터 읽기
   }

   // 읽은 데이터가 없을 때
   if (dwReadLength == 0)
   {
	   CStringA str;
	   str.Format("%s", message);

	   if (strTemp != str)
	   {	   
		   return str.GetLength();  // 읽은 데이터 길이 반환
	   }	   
   }
  
   return dwReadLength;  // 실제 읽은 데이터 길이 반환
}

// 포트가 열려 있는지 확인하는 함수
bool CRsPort::IsCommPortOpen()
{
	if (m_Connect)
		return true;  // 연결되어 있으면 true 반환
	return false;     // 연결되어 있지 않으면 false 반환
}
