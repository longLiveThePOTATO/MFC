// MFCEx02Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCEx02.h"
#include "MFCEx02Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define M_PI 3.14159265358979323846
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.


// CMFCEx02Dlg ��ȭ ����

CMFCEx02Dlg::CMFCEx02Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCEx02Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCEx02Dlg::DoDataExchange(CDataExchange* pDX)
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
	//ON_STN_CLICKED(IDC_View, &CMFCEx02Dlg::OnStnClickedView)
END_MESSAGE_MAP()

// CMFCEx02Dlg �޽��� ó����

BOOL CMFCEx02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.

	CMenu* pSysMenu = GetSystemMenu(FALSE);


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


// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCEx02Dlg::OnPaint()
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
		//����
		CPaintDC dc(&m_Pic);
		// ��� �簢�� �׸���
		CBrush whiteBrush(WHITE); // ��� �귯�� ����
		dc.SelectObject(&whiteBrush); // ��� �귯�� ����

		CRect whiteRect(view.left, view.top, view.right, view.bottom); // �߽��� �������� �簢�� ũ�� ����
		dc.Rectangle(whiteRect); // �簢�� �׸���

		vCenterX = view.left + view.Width() / 2;
		vCenterY = view.top + view.Height() / 2;

		// ������ �׸���
		dc.MoveTo(vCenterX, view.top);
		dc.LineTo(vCenterX, view.bottom);

		// ���� �׸���
		dc.MoveTo(view.left, vCenterY);
		dc.LineTo(view.right, vCenterY);

		/*
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_View);
		CDC* pDC = pStatic->GetDC();
		pStatic->GetClientRect(&view);
		CRgn rgn;
		rgn.CreateRectRgn(view.left, view.top, view.right, view.bottom);

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		UpdateData();

		// �⺻ �� ����
		CPen default_pen(PS_SOLID, 2, LIGHTBLUE);
		CPen* pOldPen = pDC->SelectObject(&default_pen);

		// �귯�� ����
		CBrush* pOldBrush = (CBrush*)pDC->SelectObject(GetStockObject(NULL_BRUSH));
		pDC->SelectClipRgn(&rgn);
		// ���� ���õ� ��ü �ε���
		int sIndex = -1;

		// ������ ����� ���� �׸���
		for (int i = 0; i < (int)objData.size(); i++)
		{
		if (!objData[i].bSelect)
		{
		// �⺻ ������ �׸���
		DrawShape(objData[i].type, pDC, objData[i].sP, objData[i].eP);
		}
		else
		{
		sIndex = i;
		}
		}
		if (sIndex != -1){
		// ���� ������ �׸��� (�ӽ÷� �� ����)
		CPen red_pen(PS_SOLID, 2, LIGHTRED);
		CPen* pOldPenTemp = pDC->SelectObject(&red_pen);

		DrawShape(objData[sIndex].type, pDC, objData[sIndex].sP, objData[sIndex].eP);

		// ���� ������ ����
		pDC->SelectObject(pOldPenTemp);
		}


		//for (const auto& obj : objData)
		//{
		//	if (!obj.bSelect){
		//		DrawShape(obj_Type, pDC, start_Pos, end_Pos);
		//	}
		//}
		pDC->SelectClipRgn(NULL); // ���� ���� ����
		pStatic->ReleaseDC(pDC);
		*/

	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCEx02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCEx02Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString str;
	start_Pos = CPoint(point.x - 12, point.y - 12);
	/*
		str.Format(_T("%d"), start_Pos.x);
		center_X.SetWindowText(str);
		str.Format(_T("%d"), start_Pos.y);
		center_Y.SetWindowText(str);*/

}

void CMFCEx02Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);
	point = CPoint(point.x - 12, point.y - 12);
	end_Pos = point;

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_View);
	CRgn rgn;
	rgn.CreateRectRgn(view.left, view.top, view.right, view.bottom);

	UpdateData();
	if (view.PtInRect(point) && view.PtInRect(start_Pos)) {
		switch (obj_Type)
		{
		case 1:
			count_R++;  // �簢�� ���� ����
			obj_Str.Format(_T("Rect %d"), count_R);				// �簢�� �̸� ����
			objData.emplace_back(1, start_Pos, point, false);	// ��ü ������ ����
			m_List.InsertItem(m_List.GetItemCount(), obj_Str);				// ����Ʈ�� ��ü �߰�
			break;
		case 2:
		{
			count_C++;  // �� ���� ����
			obj_Str.Format(_T("Circle %d"), count_C);			// �� �̸� ����
			objData.emplace_back(2, start_Pos, point, false);	// ��ü ������ ����
			m_List.InsertItem(m_List.GetItemCount(), obj_Str);				// ����Ʈ�� ��ü �߰�
			break;

		}
		default:
			break;
		}
		//Invalidate();
		OnDrawImage();

	}
}

void CMFCEx02Dlg::OnBtnClickedAddR()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	obj_Type = 1;
}

void CMFCEx02Dlg::OnBtnClickedAddC()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	obj_Type = 2;
}

void CMFCEx02Dlg::OnBnClickedDel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰�
	obj_Type = 0;
	// ���õ� ����Ʈ �������� �ε����� �����ɴϴ�.
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}

	// ���õ� �׸��� �ε����� ȣ��
	int selectedIndex = m_List.GetNextSelectedItem(pos);
	if (selectedIndex >= 0 && selectedIndex < objData.size())
	{
		// objData���� ���õ� �׸��� ����
		objData.erase(objData.begin() + selectedIndex);

		// m_List���� ���õ� �׸��� ����
		m_List.DeleteItem(selectedIndex);
	}

	// ���� ��Ʈ�ѿ� �ִ� �ؽ�Ʈ ����
	center_X.SetWindowText(_T(""));
	center_Y.SetWindowText(_T(""));
	size_X.SetWindowText(_T(""));
	size_Y.SetWindowText(_T(""));
	//Invalidate();
	OnDrawImage();
}

void CMFCEx02Dlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
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
			objData[selectedIndex].bSelect = true;
			CPoint sP = objData[selectedIndex].sP;
			CPoint eP = objData[selectedIndex].eP;
			str.Format(_T("%d"), ReScale(CalculateCenter(sP, eP).x));
			center_X.SetWindowText(str);
			str.Format(_T("%d"), ReScale(CalculateCenter(sP, eP).y*(-1)));
			center_Y.SetWindowText(str);
			str.Format(_T("%d"), ReScale(CalculateSize(sP, eP).x));
			size_X.SetWindowText(str);
			str.Format(_T("%d"), ReScale(CalculateSize(sP, eP).y));
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
			//Invalidate();
			OnDrawImage();
		}
	}
	obj_Type = 0;
	*pResult = 0;
}

CPoint CMFCEx02Dlg::CalculateCenter(const CPoint& start, const CPoint& end)
{
	int centerX = (start.x + end.x) / 2 - HALFLENGTH;
	int centerY = (start.y + end.y) / 2 - HALFLENGTH;

	return CPoint(centerX, centerY);
}

CPoint CMFCEx02Dlg::CalculateSize(const CPoint start, const CPoint end)
{
	int sizeX = std::abs(start.x - end.x);
	int sizeY = std::abs(start.y - end.y);
	return CPoint(sizeX, sizeY);
}

CPoint CMFCEx02Dlg::ReScale(CPoint point)
{
	return CPoint(point.x * 100 / view.Width(), point.y * 100 / view.Height());
}

void CMFCEx02Dlg::DrawEllipse(CDC* pDC, const CPoint& center, const CPoint& radius)
{
	// Ÿ���� 360���� ������ ���� ����
	for (int angle = 0; angle < 361; angle++)
	{
		// ������ �������� ��ȯ
		double radians = angle * M_PI / 180.0;

		int x = center.x + (int)(radius.x * cos(radians) / 2);
		int y = center.y - (int)(radius.y * sin(radians) / 2);

		if (angle == 0) {
			pDC->MoveTo(x, y);
		}
		else {
			pDC->LineTo(x, y);
		}
	}
}

void CMFCEx02Dlg::DrawRectangle(CDC* pDC, const CPoint& start, const CPoint& end)
{
	pDC->MoveTo(start);
	pDC->LineTo(start.x, end.y);
	pDC->LineTo(end.x, end.y);
	pDC->LineTo(end.x, start.y);
	pDC->LineTo(start);


}

void CMFCEx02Dlg::DrawShape(int type, CDC* pDC, CPoint sP, CPoint eP)
{
	switch (type)
	{
	case 1:
		DrawRectangle(pDC, sP, eP);
		break;
	case 2:
	{
		CPoint radius = CalculateSize(sP, eP);
		CPoint center = CalculateCenter(sP, eP);
		center.x += HALFLENGTH;
		center.y += HALFLENGTH;
		DrawEllipse(pDC, center, radius);
	}
	break;
	default:
		break;
	}
}
void CMFCEx02Dlg::OnDrawImage()
{
	// Picture Control ��������
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_View);

	// Picture Control DC ��������
	CDC* pDC = pStatic->GetDC();

	// Picture Control�� Ŭ���̾�Ʈ ���� ũ�� ���ϱ�
	CRect view;
	pStatic->GetClientRect(&view);

	// �޸� DC�� ��Ʈ�� ����
	CDC memDC;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, view.Width(), view.Height());

	// ��Ʈ���� �޸� DC�� ����
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// �ӽ� ����(memDC)�� �׸��� �۾� ����
	// memDC.FillSolidRect(view, RGB(0, 0, 0)); // ������ ���

	// ��� �簢�� �׸���
	CBrush whiteBrush(WHITE); // ��� �귯�� ����
	memDC.SelectObject(&whiteBrush); // ��� �귯�� ����
	memDC.Rectangle(view.left, view.top, view.right, view.bottom);

	int vCenterX = view.left + view.Width() / 2;
	int vCenterY = view.top + view.Height() / 2;

	// ������ �׸���
	memDC.MoveTo(vCenterX, view.top);
	memDC.LineTo(vCenterX, view.bottom);

	// ���� �׸���
	memDC.MoveTo(view.left, vCenterY);
	memDC.LineTo(view.right, vCenterY);

	// �⺻ �� ����
	CPen default_pen(PS_SOLID, 2, LIGHTBLUE);
	CPen* pOldPen = memDC.SelectObject(&default_pen);

	// �귯�� ����
	memDC.SelectStockObject(NULL_BRUSH);

	// �׸��� ���� ����
	CRgn rgn;
	rgn.CreateRectRgn(view.left, view.top, view.right, view.bottom);
	memDC.SelectClipRgn(&rgn);

	// ������ ����� ���� �׸���
	int sIndex = -1;
	for (int i = 0; i < objData.size(); ++i)
	{
		if (!objData[i].bSelect)
		{
			// �⺻ ������ �׸���
			DrawShape(objData[i].type, &memDC, objData[i].sP, objData[i].eP);
		}
		else
		{
			sIndex = i;
		}
	}

	// ���õ� ���� ���� ������ �׸���
	if (sIndex != -1)
	{
		CPen red_pen(PS_SOLID, 2, LIGHTRED);
		CPen* pOldPenTemp = memDC.SelectObject(&red_pen);

		DrawShape(objData[sIndex].type, &memDC, objData[sIndex].sP, objData[sIndex].eP);

		// ���� ������ ����
		memDC.SelectObject(pOldPenTemp);
	}

	// �׸��� ���� ����
	memDC.SelectClipRgn(NULL);

	// �޸� DC���� ��Ʈ���� ȭ�� DC�� �����Ͽ� ���
	pDC->BitBlt(view.left, view.top, view.Width(), view.Height(), &memDC, 0, 0, SRCCOPY);

	// �ڿ� ����
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	// Picture Control DC ����
	pStatic->ReleaseDC(pDC);
}

