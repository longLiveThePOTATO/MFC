// RsPort.h : ��� ����

#pragma once
// ���� ���� ����
#define NUL  0x00  // �� ����
#define SOH  0x01  // ��� ����
#define STX  0x02  // �ؽ�Ʈ ����
#define ETX  0x03  // �ؽ�Ʈ ����
#define EOT  0x04  // ���� ����
#define ENQ  0x05  // ��û
#define ACK  0x06  // ���� ����
#define NAK  0x15  // ���� ����
#define XON  0x11  // ���� ����
#define XOFF 0x13  // ���� ����
#define ESC  0x1b  // �̽�������
#define CR   0x0d  // ĳ���� ����
#define LF   0x0a  // ���� �ǵ�

// ��� ����
const int DEF_MAX_SERIAL_PORT = 6;  ///< Serial Port ����
const int ERR_SERIAL_PORT_SUCCESS = 0;  // ����
const int ERR_PORT_OPEN_FAIL = 1;  // ��Ʈ ���� ����
const int ERR_TIME_OUT = 2;        // �ð� �ʰ� ����



// CRsPort Ŭ���� ����
class CRsPort
{
public:
	BOOL   m_Connect;     // ��Ʈ ���� ����
	HANDLE m_idComDev;    // ��Ʈ �ڵ�

public:
	// ��Ʈ���� ������ �б� �Լ�
	//CString ReadCommPort();
	int ReadCommPort(char *message, DWORD length);

	// ��Ʈ�� ������ ���� �Լ�
	int WriteCommPort(unsigned char* message, DWORD dwLength);

	// ��Ʈ�� ���� �ִ��� Ȯ���ϴ� �Լ�
	bool IsCommPortOpen();

	// �⺻ ������
	CRsPort();
	//CRsPort(CString m_portName, DWORD BaudRate);

	// �Ҹ���
	virtual ~CRsPort();

	
	// ��Ʈ �ݱ� �Լ�
	void CloseCommPort(void);

	// ��� ���� �Լ�
	BOOL SetupConnection(void);

	// ��Ʈ �ʱ�ȭ �Լ�
	void initComport(CString m_portName, DWORD baudRate);

protected:

	OVERLAPPED osWrite;  // �񵿱� ���� ���꿡 ���Ǵ� ����ü
	OVERLAPPED osRead;   // �񵿱� �б� ���꿡 ���Ǵ� ����ü
	DCB        dcb_setup;  // ��� ������ ���� ����ü
};
