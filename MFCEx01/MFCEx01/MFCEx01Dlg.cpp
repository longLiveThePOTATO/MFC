// MFCEx01Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCEx01.h"
#include "MFCEx01Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCEx01Dlg ��ȭ ����

CMFCEx01Dlg::CMFCEx01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCEx01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCEx01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	// DDX_Control(pDX, IDC_View, m_PictureControl);
	DDX_Control(pDX, IDC_View, m_Pic);
	DDX_Control(pDX, IDC_EDIT1, center_X);
	DDX_Control(pDX, IDC_EDIT2, center_Y);
	DDX_Control(pDX, IDC_EDIT3, size_X);
	DDX_Control(pDX, IDC_EDIT4, size_Y);
}

BEGIN_MESSAGE_MAP(CMFCEx01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_AddR, &CMFCEx01Dlg::OnBtnClickedAddR)
	ON_BN_CLICKED(IDC_AddC, &CMFCEx01Dlg::OnBtnClickedAddC)
	ON_BN_CLICKED(IDC_DEL, &CMFCEx01Dlg::OnBnClickedDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CMFCEx01Dlg::OnLvnItemchangedList)
END_MESSAGE_MAP()

// CMFCEx01Dlg �޽��� ó����

BOOL CMFCEx01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);            // ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);        // ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// m_PictureControl.SubclassDlgItem(IDC_View, this);
	obj_Type = 0;
	count_R = 0;
	count_C = 0;
	count_T = 0;

	objData;

	m_Pic.GetClientRect(&view);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFCEx01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCEx01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (view.Width() - cxIcon + 1) / 2;
		int y = (view.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		// IDC_VIEW (m_Pic) ��Ʈ���� �߾ӿ� �������� ���� �׸���

		int centerX = view.left + view.Width() / 2;
		int centerY = view.top + view.Height() / 2;

		CPaintDC dc(&m_Pic);
		// ��� �簢�� �׸���
		CBrush whiteBrush(WHITE); // ��� �귯�� ����
		dc.SelectObject(&whiteBrush); // ��� �귯�� ����

		CRect whiteRect(view.left, view.top, view.right, view.bottom); // �߽��� �������� �簢�� ũ�� ����
		dc.Rectangle(whiteRect); // �簢�� �׸���

		// ������ �׸���
		dc.MoveTo(centerX, view.top);
		dc.LineTo(centerX, view.bottom);

		// ���� �׸���
		dc.MoveTo(view.left, centerY);
		dc.LineTo(view.right, centerY);

		
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCEx01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCEx01Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	start_pos = point;
}

void CMFCEx01Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_View);
	CDC* pDC = pStatic->GetDC();
	pStatic->GetClientRect(&view);
	CRgn rgn;
	rgn.CreateRectRgn(view.left, view.top, view.right, view.bottom);


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData();
	// �� ����
	CPen my_pen(PS_SOLID, 2, LIGHTBLUE);
	CPen* pOldPen = pDC->SelectObject(&my_pen);

	// �귯�� ����
	CBrush* pOldBrush = (CBrush*)pDC->SelectObject(GetStockObject(NULL_BRUSH));
	CString obj_Str;
	count_T++;
	pDC->SelectClipRgn(&rgn);
	if (view.PtInRect(point) && view.PtInRect(start_pos)) {
		switch (obj_Type)
		{
		case 1:
			pDC->Rectangle(start_pos.x, start_pos.y, point.x, point.y);
			count_R++;  // �簢�� ���� ����
			obj_Str.Format(_T("Rect %d"), count_R);  // �簢�� �̸� ����
			objData.emplace_back(RECTANGLE, start_pos, point);
			m_List.InsertItem(count_T, obj_Str);	// ����Ʈ�� ��ü �߰�
			break;
		case 2:
			pDC->Ellipse(start_pos.x, start_pos.y, point.x, point.y);
			count_C++;  // �� ���� ����
			obj_Str.Format(_T("Circle %d"), count_C);  // �� �̸� ����
			objData.emplace_back(CIRCLE, start_pos, point);
			m_List.InsertItem(count_T, obj_Str);	// ����Ʈ�� ��ü �߰�
			break;
		default:
			break;
		}
		pDC->SelectClipRgn(NULL); // ���� ���� ���� 
		pStatic->ReleaseDC(pDC);

	}

}

void CMFCEx01Dlg::OnBtnClickedAddR()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	obj_Type = 1;
}

void CMFCEx01Dlg::OnBtnClickedAddC()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	obj_Type = 2;
}


void CMFCEx01Dlg::OnBnClickedDel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	obj_Type = 0;
}




void CMFCEx01Dlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
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
			str.Format(_T("%d"), CalculateCenter(objData[selectedIndex].sP, objData[selectedIndex].eP).x);
			center_X.SetWindowText(str);
			str.Format(_T("%d"), CalculateCenter(objData[selectedIndex].sP, objData[selectedIndex].eP).y);
			center_Y.SetWindowText(str);
			str.Format(_T("%d"), CalculateSize(objData[selectedIndex].sP, objData[selectedIndex].eP).x);
			size_X.SetWindowText(str);
			str.Format(_T("%d"), CalculateSize(objData[selectedIndex].sP, objData[selectedIndex].eP).y);
			size_Y.SetWindowText(str);
			// you could do your own processing on nItem here
		}
	}

	*pResult = 0;
}


CPoint CMFCEx01Dlg::CalculateCenter(const CPoint& start, const CPoint& end)
{
	int centerX = (start.x + end.x) / 2;
	int centerY = (start.y + end.y) / 2;
	return CPoint(centerX, centerY);
}


//CPoint CMFCEx01Dlg::CalculateSize()
//{
//	return CPoint();
//}


CPoint CMFCEx01Dlg::CalculateSize(const CPoint start, const CPoint end)
{
	int sizeX = std::abs(start.x - end.x);
	int sizeY = std::abs(start.y - end.y);
	return CPoint(sizeX, sizeY);
}
