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


// ���巹��Ʈ ���� ���� ����
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

// CRsPort Ŭ���� ����
class CRsPort
{
public:
	BOOL   m_Connect;     // ��Ʈ ���� ����
	HANDLE m_idComDev;    // ��Ʈ �ڵ�

public:
	// ��Ʈ���� ������ �б� �Լ�
	int ReadCommPort(unsigned char *message, DWORD length);

	// ��Ʈ�� ������ ���� �Լ�
	int WriteCommPort(unsigned char* message, DWORD dwLength);

	// ��Ʈ�� ���� �ִ��� Ȯ���ϴ� �Լ�
	bool IsCommPortOpen();

	// �⺻ ������
	CRsPort(CString m_portName);

	// �Ű������� �ִ� ������
	CRsPort(CString m_portName, DWORD BaudRate);
	CRsPort(CString m_portName, DWORD BaudRate, BYTE ByteSize, BYTE Parity, BYTE StopBits);

	// �Ҹ���
	virtual ~CRsPort();

protected:
	// ��Ʈ �ݱ� �Լ�
	void CloseCommPort(void);

	// ��� ���� �Լ�
	BOOL SetupConnection(void);

	// ��Ʈ �ʱ�ȭ �Լ�
	void initComport(CString m_portName);

	OVERLAPPED osWrite;  // �񵿱� ���� ���꿡 ���Ǵ� ����ü
	OVERLAPPED osRead;   // �񵿱� �б� ���꿡 ���Ǵ� ����ü
	DCB        dcb_setup;  // ��� ������ ���� ����ü
};