#include "stdafx.h"
#include "Comm.h"


// ���� ����
HWND g_hWnd; // ������ �ڵ�
VOID CALLBACK TermIrq(int port); // IRQ �ݹ� �Լ� ����

//////////////////////////////////////////////////////////////////////
// ������/�Ҹ���
//////////////////////////////////////////////////////////////////////

Comm::Comm()
{
	m_nPort = 0;     // ��Ʈ ��ȣ �ʱ�ȭ
	m_nError = 0;    // ���� �ڵ� �ʱ�ȭ
	m_nResult = 0;   // ��� �ڵ� �ʱ�ȭ

	m_bOpen = FALSE; // ��Ʈ ���� ���� �÷��� �ʱ�ȭ
	g_hWnd = NULL;   // ������ �ڵ� �ʱ�ȭ
}

Comm::~Comm()
{
	// �Ҹ��ڿ��� ���ҽ� ������ �ʿ� ����
}

BOOL Comm::COpen(HWND hWnd, int port, int baudrate, int mode, const char irq, BOOL bEvent)
{
	if (m_bOpen)
		CClose(); // �̹� ���� ������ ��Ʈ�� ����

	// �ϵ���� �� ����Ʈ���� �帧 ���� ����
	int hw = FALSE ? 3 : 0;
	int sw = FALSE ? 12 : 0;

	if (m_bOpen) return TRUE; // �̹� ���� ������ TRUE ��ȯ

	// ��Ʈ ���� �� ����
	if (sio_open(port) != SIO_OK) return FALSE;
	if (sio_ioctl(port, baudrate, mode) != SIO_OK) return FALSE;
	if (sio_flowctrl(port, hw | sw) != SIO_OK) return FALSE;
	if (sio_DTR(port, (FALSE ? 1 : 0)) != SIO_OK) return FALSE;
	if (sio_RTS(port, (TRUE ? 1 : 0)) != SIO_OK) return FALSE;

	// �б�/���� Ÿ�Ӿƿ� ����
	sio_SetReadTimeouts(2, MAXDWORD, 0);
	sio_SetWriteTimeouts(port, MAXDWORD);

	// ���� �÷��� �� ���
	sio_flush(port, 2);
	Waitmsec(100);

	m_nPort = port; // ��Ʈ ��ȣ ����
	m_bOpen = TRUE; // ��Ʈ ���� ���� �÷��� ����

	if (bEvent)
	{
		g_hWnd = hWnd; // ������ �ڵ� ����

		// IRQ �ڵ鷯 ���
		m_nResult = sio_term_irq(m_nPort, TermIrq, irq);
		if (m_nResult != SIO_OK)
		{
			TRACE(_T("COM%d : Event fault!\n"), port); // �̺�Ʈ ���� �޽��� ���
			CClose();
			return FALSE;
		}
	}

	return TRUE; // ���������� �������� ��ȯ
}

bool Comm::COpen(short port, long baudrate)
{
	if (m_bOpen)
		CClose();

	// Comm��Ʈ �ʱ� ����
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

	// Input/Output ���� �ʱ�ȭ
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
		// IRQ �ڵ鷯 ����
		sio_term_irq(m_nPort, NULL, 0x00);
		m_nResult = 0;
	}

	if (m_bOpen)
	{
		// ��Ʈ �ݱ�
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
	if (!m_bOpen) return FALSE; // ��Ʈ�� ���� ���� ������ FALSE ��ȯ

	char ch[CHAR_MAX];
	memset(ch, 0, sizeof(ch)); // ���� �ʱ�ȭ
	sio_flush(m_nPort, 1); // ��Ʈ �÷���

	int len = sio_iqueue(m_nPort); // ���� ��⿭�� ���� Ȯ��
	if (CHAR_MAX <= (len - 1))
		return FALSE;

	if (len < 1) return FALSE;
	m_nError = sio_read(m_nPort, ch, len); // ������ �б�
	ch[len + 1] = '\0'; // ���ڿ� ���� �� ���� �߰�

#ifdef _UNICODE
	str = __PCharToCStringInUnicode(ch); // �����ڵ� ���ڿ� ��ȯ
#else
	str.Format(_T("%s"), ch); // ASCII ���ڿ� ����
#endif

	return TRUE; // ���� ���� ��ȯ		// <- ���� ���� �ذ��Ѵٰ� ������... �̰� ����
}

BOOL Comm::CWrite(CString str)
{
	if (!m_bOpen) return FALSE; // ��Ʈ�� ���� ���� ������ FALSE ��ȯ

	m_nError = sio_flush(m_nPort, 0); // ��Ʈ �÷���
	Sleep(50); // ��� ���

	int len = str.GetLength(); // ���ڿ� ���� ��������
#ifdef _UNICODE
	CHAR* pTemp = __CStringToPCharInUnicode(str); // �����ڵ� ���ڿ��� ASCII ���ڿ��� ��ȯ
#else
	CHAR *pTemp = new CHAR[len + 1];
	memset(pTemp, 0x00, len + 1);
	memcpy(pTemp, str.GetBuffer(0), len + 1);
	str.ReleaseBuffer();
#endif

	m_nError = sio_write(m_nPort, pTemp, len); // ������ ����
	delete[] pTemp; // �������� �Ҵ��� �޸� ����
	return (m_nError == SIO_OK); // ���� ���� ��ȯ
}

BOOL Comm::CWrite2(CString str)
{
	if (!m_bOpen) return FALSE; // ��Ʈ�� ���� ���� ������ FALSE ��ȯ

	char ch[512] = {};

	sio_flush(m_nPort, 0); // ��Ʈ �÷���
	Sleep(50); // ��� ���

	int l = str.GetLength();
	if (l < 510)
	{
		for (int i = 0; i < l; i++)
		{
			ch[i] = (char)str.GetAt(i); // ���ڿ��� char �迭�� ��ȯ
		}
		m_nError = sio_write(m_nPort, ch, l); // ������ ����
	}

	return (m_nError == SIO_OK); // ���� ���� ��ȯ
}

BOOL Comm::CWrite(CHAR* c, int length)
{
	sio_flush(m_nPort, 0); // ��Ʈ �÷���
	Sleep(50); // ��� ���

	m_nError = sio_write(m_nPort, c, length); // ������ ����

	return (m_nError == SIO_OK); // ���� ���� ��ȯ
}

void Comm::CPutch(int c)
{
	if (!m_bOpen) return; // ��Ʈ�� ���� ���� ������ ��ȯ

	m_nError = sio_flush(m_nPort, 0); // ��Ʈ �÷���
	Sleep(25); // ��� ���

	m_nError = sio_putch(m_nPort, c); // ���� ���� ����
	Sleep(50); // ��� ���
}

int Comm::CGetch()
{
	if (!m_bOpen) return '\0'; // ��Ʈ�� ���� ���� ������ �� ���� ��ȯ

	int c;
	c = sio_getch(m_nPort); // ���� ���� �б�

	if (c < 0) m_nError = c; // ���� �ڵ� ����
	return c; // ���� ���� ��ȯ
}
//************  Read & Write Functions End  ************//

short Comm::ErrorCheck() const
{
	return m_nError; // ������ ���� �ڵ� ��ȯ
}

BOOL Comm::CommCheck() const
{
	return m_bOpen; // ��Ʈ ���� ���� ��ȯ
}

//************  Event Functions End  ************//

VOID CALLBACK TermIrq(int port)
{
	::PostMessage(g_hWnd, WM_RECEIVED_COMM, (WPARAM)port, 0); // �̺�Ʈ �߻� �� �޽��� ����
}


// ���ڿ� ��ȯ �Լ�
char* Comm::__CStringToPCharInUnicode(CString str)
{
	wchar_t* wchar_str = NULL;
	char*    char_str = NULL;
	int      char_str_len = 0;

	wchar_str = str.GetBuffer(str.GetLength()); // CString�� wchar_t �迭�� ��ȯ
	str.ReleaseBuffer();

	char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
	char_str = new char[char_str_len + 1];  // �޸� �Ҵ�
	WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0, 0);

	char_str[char_str_len] = '\0'; // ���ڿ� ���� �� ���� �߰�
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

	wchar_str[char_str_len] = _T('\0'); // ���ڿ� ���� �� ���� �߰�
	cstring_str.Format(_T("%s"), wchar_str); // CString���� ��ȯ
	delete[] wchar_str; // �������� �Ҵ��� �޸� ����
	return cstring_str;
}

