// RsPort.cpp: CRsPort Ŭ������ ���� �����Դϴ�.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"  // ǥ�� �ý��� ���� ����
#include "RsPort.h"  // RsPort Ŭ���� ��� ����

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// ������/�Ҹ���
//////////////////////////////////////////////////////////////////////

// �Ű������� �ִ� ������ - ��Ʈ �̸�, �ӵ��� �޾� �ʱ�ȭ
//CRsPort::CRsPort(CString m_portName, DWORD BaudRate)
CRsPort::CRsPort()
{
	//dcb_setup.BaudRate = BaudRate;
	dcb_setup.ByteSize = 8;          // ������ ��Ʈ �� ���� (8 ��Ʈ)
	dcb_setup.Parity = NOPARITY;   // �и�Ƽ ��Ʈ ����
	dcb_setup.StopBits = ONESTOPBIT; // ���� ��Ʈ ���� (1 ��Ʈ)
	//initComport(m_portName);
}

// �Ҹ��� - ��Ʈ�� �ݴ� �Լ� ȣ��
CRsPort::~CRsPort()
{
   CloseCommPort();
}

// ��Ʈ �ʱ�ȭ �Լ�
void CRsPort::initComport(CString m_portName, DWORD BaudRate)
{
   COMMTIMEOUTS  commTimeOuts;  // ��� �ð� �ʰ� ���� ����ü

   // ��Ʈ�� ����
   m_idComDev = CreateFile((LPCTSTR)m_portName, GENERIC_READ | GENERIC_WRITE, 
	   0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

   // ��Ʈ ���� ���� ��
   if (m_idComDev == (HANDLE)-1)
   {
		CloseHandle(m_idComDev);  // �ڵ� �ݱ�
		m_Connect = FALSE;        // ���� ���¸� FALSE�� ����
		AfxMessageBox(_T("WARNING : ��Ʈ�� ���µ� �����Ͽ����ϴ�."));
   }
   else
   {
		SetCommMask(m_idComDev, EV_RXCHAR);          // ���� �̺�Ʈ ����
		SetupComm(m_idComDev, 4096, 4096);           // ����� ���� ũ�� ����
		PurgeComm(m_idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);  // ��� ��Ʈ �ʱ�ȭ

		// ��� �ð� �ʰ� �� ����
		commTimeOuts.ReadIntervalTimeout = -1;
		commTimeOuts.ReadTotalTimeoutMultiplier = 0;
		commTimeOuts.ReadTotalTimeoutConstant = 1000;
		commTimeOuts.WriteTotalTimeoutMultiplier = 0;
		commTimeOuts.WriteTotalTimeoutConstant = 1000;
		SetCommTimeouts(m_idComDev, &commTimeOuts);

		m_Connect = SetupConnection();  // ��� ����

		// �񵿱� I/O�� ���� �̺�Ʈ ����
		osWrite.Offset = 0;
		osWrite.OffsetHigh = 0;
		osRead.Offset = 0;
		osRead.OffsetHigh = 0;
		osRead.hEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
		osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   }
}

// ��� ���� �Լ�
BOOL CRsPort::SetupConnection()
{
   BOOL fRetVal;  // �Լ� ��ȯ ��
   DCB  dcb;      // ����̽� ���� ��� ����ü
   
   dcb.DCBlength = sizeof(DCB);  // ����ü ũ�� ����
   GetCommState(m_idComDev, &dcb);  // ���� ��� ���� ��������
   dcb.BaudRate = dcb_setup.BaudRate;  // ������ BaudRate�� ����
   dcb.ByteSize = dcb_setup.ByteSize;  // ������ ByteSize�� ����
   dcb.Parity   = dcb_setup.Parity;    // ������ Parity�� ����
   dcb.StopBits = dcb_setup.StopBits;  // ������ StopBits�� ����

   // ��Ÿ ��� ����
   dcb.fOutxDsrFlow = 0;
   dcb.fDtrControl = DTR_CONTROL_ENABLE;
   dcb.fOutxCtsFlow = 0;
   dcb.fRtsControl = RTS_CONTROL_ENABLE;
   dcb.fInX = dcb.fOutX = 0;  // XON/XOFF ��� �� ��
   dcb.XonChar  = 0x11;       // ASCII_XON
   dcb.XoffChar = 0x13;       // ASCII_XOFF
   dcb.XonLim   = 100;
   dcb.XoffLim  = 100;
   dcb.fBinary  = TRUE;
   dcb.fParity  = TRUE;

   // ��� ���� ����
   fRetVal = SetCommState(m_idComDev, &dcb);
   return fRetVal;  // ���� ��� ��ȯ
}

// ��Ʈ �ݱ� �Լ�
void CRsPort::CloseCommPort()
{
  if (m_Connect == FALSE) return;  // ����Ǿ� ���� ������ ��ȯ
  CloseHandle(m_idComDev);         // ��Ʈ �ڵ� �ݱ�
  CloseHandle(osRead.hEvent);      // �б� �̺�Ʈ �ڵ� �ݱ�
  CloseHandle(osWrite.hEvent);     // ���� �̺�Ʈ �ڵ� �ݱ�
}

// ��Ʈ�� ������ ���� �Լ�
int CRsPort::WriteCommPort(unsigned char *message, DWORD dwLength)
{
   int ret_code;
   ret_code = WriteFile(m_idComDev, message, dwLength, &dwLength, &osWrite);  // ������ ����
   return ret_code;  // ��� ��ȯ
}

// ��Ʈ���� ������ �б� �Լ�
#include <afxstr.h>   // CString�� ����ϱ� ���� ���

// ��Ʈ���� ������ �б� �Լ�
CString CRsPort::ReadCommPort()
{
	COMSTAT  ComStat;           // ��� ���� ����ü
	DWORD    dwErrorFlags;      // ���� �÷���
	DWORD    dwLength;          // ������ ����
	DWORD    dwReadLength = 0;  // ���� ������ ����

	// ���� ���� üũ
	if (m_Connect == FALSE)
		return _T("");  // ����Ǿ� ���� ������ �� ���ڿ� ��ȯ

	ClearCommError(m_idComDev, &dwErrorFlags, &ComStat);  // ��� ���� �÷��� �ʱ�ȭ
	dwLength = min((DWORD)50, ComStat.cbInQue);           // ���� ������ ���� ���� (�ִ� 50����Ʈ)

	char buffer[51];  // �����͸� ������ ����, ���̴� 50 + null ���� ����('\0')�� ����Ͽ� 51�� ����

	if (ReadFile(m_idComDev, buffer, dwLength, &dwReadLength, &osRead))
	{
		buffer[dwReadLength] = '\0';  // null ���� ���� �߰�
		return CString(buffer);   // char �迭�� CString���� ��ȯ�Ͽ� ��ȯ
	}
	else
	{
		return _T("");  // ���� �� �� ���ڿ� ��ȯ
	}
}

/*
int CRsPort::ReadCommPort(unsigned char *message, DWORD length)
{
COMSTAT  ComStat;           // ��� ���� ����ü
DWORD    dwErrorFlags;      // ���� �÷���
DWORD    dwLength;          // ������ ����
DWORD    dwReadLength = 0;  // ���� ������ ����

CStringA strTemp;
strTemp.Format("%s", message);

if (m_Connect == FALSE)  return 0;  // ����Ǿ� ���� ������ 0 ��ȯ
else
{
ClearCommError(m_idComDev, &dwErrorFlags, &ComStat);  // ��� ���� �÷��� �ʱ�ȭ
dwLength = min((DWORD)length, ComStat.cbInQue);       // ���� ������ ���� ����
ReadFile(m_idComDev, message, dwLength, &dwReadLength, &osRead);  // ������ �б�
}

// ���� �����Ͱ� ���� ��
if (dwReadLength == 0)
{
CStringA str;
str.Format("%s", message);

if (strTemp != str)
{
return str.GetLength();  // ���� ������ ���� ��ȯ
}
}

return dwReadLength;  // ���� ���� ������ ���� ��ȯ
}

*/

// ��Ʈ�� ���� �ִ��� Ȯ���ϴ� �Լ�
bool CRsPort::IsCommPortOpen()
{
	if (m_Connect)
		return true;  // ����Ǿ� ������ true ��ȯ
	return false;     // ����Ǿ� ���� ������ false ��ȯ
}
