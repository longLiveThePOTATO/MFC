#pragma once
// 제어 문자 정의
#define NUL  0x00  // 널 문자
#define SOH  0x01  // 헤더 시작
#define STX  0x02  // 텍스트 시작
#define ETX  0x03  // 텍스트 종료
#define EOT  0x04  // 전송 종료
#define ENQ  0x05  // 요청
#define ACK  0x06  // 긍정 응답
#define NAK  0x15  // 부정 응답
#define XON  0x11  // 전송 시작
#define XOFF 0x13  // 전송 중지
#define ESC  0x1b  // 이스케이프
#define CR   0x0d  // 캐리지 리턴
#define LF   0x0a  // 라인 피드

// 상수 정의
const int DEF_MAX_SERIAL_PORT = 6;  ///< Serial Port 수량
const int ERR_SERIAL_PORT_SUCCESS = 0;  // 성공
const int ERR_PORT_OPEN_FAIL = 1;  // 포트 열기 실패
const int ERR_TIME_OUT = 2;        // 시간 초과 오류


// 보드레이트 전역 변수 선언
const int baudRates[] = {
	CBR_110,
	CBR_300,
	CBR_600,
	CBR_1200,
	CBR_2400,
	CBR_4800,
	CBR_9600,
	CBR_14400,
	CBR_19200,
	CBR_38400,
	CBR_56000,
	CBR_57600,
	CBR_115200,
	CBR_128000,
	CBR_256000
};

const int numBaudRates = sizeof(baudRates) / sizeof(baudRates[0]);

// CRsPort 클래스 선언
class CRsPort
{
public:
	BOOL   m_Connect;     // 포트 연결 상태
	HANDLE m_idComDev;    // 포트 핸들

public:
	// 포트에서 데이터 읽기 함수
	int ReadCommPort(unsigned char *message, DWORD length);

	// 포트에 데이터 쓰기 함수
	int WriteCommPort(unsigned char* message, DWORD dwLength);

	// 포트가 열려 있는지 확인하는 함수
	bool IsCommPortOpen();

	// 기본 생성자
	CRsPort(CString m_portName);

	// 매개변수가 있는 생성자
	CRsPort(CString m_portName, DWORD BaudRate);
	CRsPort(CString m_portName, DWORD BaudRate, BYTE ByteSize, BYTE Parity, BYTE StopBits);

	// 소멸자
	virtual ~CRsPort();

protected:
	// 포트 닫기 함수
	void CloseCommPort(void);

	// 통신 설정 함수
	BOOL SetupConnection(void);

	// 포트 초기화 함수
	void initComport(CString m_portName);

	OVERLAPPED osWrite;  // 비동기 쓰기 연산에 사용되는 구조체
	OVERLAPPED osRead;   // 비동기 읽기 연산에 사용되는 구조체
	DCB        dcb_setup;  // 통신 설정을 위한 구조체
};