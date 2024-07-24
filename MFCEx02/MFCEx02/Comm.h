#pragma once
extern HWND g_hWnd;

#include "PComm.h"

#pragma comment(lib, "PComm.lib")

class Comm  
{
public:
	BOOL COpen(HWND hWnd, int port, int baudrate, int mode, const char irq = 0x0D, BOOL bEvent = FALSE); // mode = P_NONE|BIT_8|STOP_1
	bool COpen(short port, long baudrate);
	void CClose();

	void CPutch(int c);
	int CGetch();
	BOOL CWrite(CString str);
	BOOL CWrite2(CString str);
	BOOL CRead(CString &str);
	BOOL CWrite(CHAR* c, int length);

	CString __PCharToCStringInUnicode(char* char_str);
	char* __CStringToPCharInUnicode(CString str);

public:
	BOOL CommCheck() const;
	short ErrorCheck() const;

	Comm();
	virtual ~Comm();

private:
	int m_nPort;
	int m_nError;
	int m_nResult;

	BOOL m_bOpen;

	void Waitmsec(long tw);
};
