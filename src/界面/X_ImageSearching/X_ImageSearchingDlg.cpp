
// X_ImageSearchingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "X_ImageSearching.h"
#include "X_ImageSearchingDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include "Rtree_image_search.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char *selected;
int key = 0;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
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


// CX_ImageSearchingDlg �Ի���



CX_ImageSearchingDlg::CX_ImageSearchingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CX_ImageSearchingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CX_ImageSearchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, x_listControl);
	DDX_Control(pDX, IDC_PICTURE, x_picture);
}

BEGIN_MESSAGE_MAP(CX_ImageSearchingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CX_ImageSearchingDlg::OnNMDblclkList)
ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CX_ImageSearchingDlg::OnNMDblclkList)
ON_BN_CLICKED(IDC_CM, &CX_ImageSearchingDlg::OnBnClickedCm)
END_MESSAGE_MAP()


// CX_ImageSearchingDlg ��Ϣ�������

BOOL CX_ImageSearchingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	x_listControl.ModifyStyle(0L, LVS_REPORT);
	x_listControl.SetExtendedStyle(LVS_EX_FULLROWSELECT);// ѡ������

	x_listControl.InsertColumn(0, _T("ͼƬ��"));

	CRect rect;
    x_listControl.GetClientRect(&rect);
    x_listControl.SetColumnWidth(0, rect.Width( ));  

	

	ListFill(x_listControl);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CX_ImageSearchingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CX_ImageSearchingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	if(!key)
	{
		CImage image;
		image.Load(_T("start.jpg"));
		CRect rect;
		int cx = image.GetWidth();
		int cy = image.GetHeight();

		GetDlgItem(IDC_PICTURE)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		GetDlgItem(IDC_PICTURE)->MoveWindow(rect.left,rect.top,cx,cy,TRUE);

		CWnd *pWnd = GetDlgItem(IDC_PICTURE);
		pWnd->GetClientRect(&rect);

		CDC *pDC = pWnd->GetDC();

		image.Draw(pDC->m_hDC,rect);
		ReleaseDC(pDC);
		key = 1;
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CX_ImageSearchingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ListFill(CListCtrl& c)
{
	int i;
	CString cs;

	CFile cf;
    cf.Open(_T("imagelist.txt"), CFile::modeRead);
    CArchive ar(&cf, CArchive::load);

	for(i = 0; i < 5613; i++)
	{
		ar.ReadString(cs);
		LPCTSTR p = cs;
		c.InsertItem(i,p);

	    c.EnsureVisible(i, TRUE);
        c.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, 
                          LVIS_SELECTED | LVIS_FOCUSED);
        c.SetFocus( );
	}
}

void outputTheResult()
{
	DeleteFileA("result.html");//���Ѿ�����result.html�ļ�����ɾȥ��Ȼ����������
	CFile cf;
    cf.Open(_T("result.txt"), CFile::modeRead);
    CArchive ar(&cf, CArchive::load);
	CString cs;

	char y = 34;
	ofstream outFile("result.html",ios::app);          //����һ��result.html����ҳ�ļ�
	outFile<<"<html>"<<endl;     //��ʼ����html���
	outFile<<"<head><style type="<<y<<"text/css"<<y<<
		">body {background-color: aliceblue}";
	outFile<<"div#header {margin-left:150;height:150px;float:top;}"<<endl
		<<"div#content {margin-left:150;margin-top:60;width:100px;float:left;}"<<endl<<"div#center {margin-left:250;margin-top:60;float:left;}"<<endl<<"</style></head>"<<endl;
	outFile<<"<body background="<<y<<"content.jpg"<<y<<">"<<endl;
	outFile<<"<div id="<<y<<"header"<<y<<"><p><img src="<<y<<"head.jpg"<<y<<" /></p></div>"<<endl
		<<"<div id="<<y<<"content"<<y<<"><p><img src="<<y<<"team.gif"<<y<<" /></p></div>"<<endl;
	outFile<<"<div id="<<y<<"center"<<y<<"><p><img src="<<y<<"tail.gif"<<y<<"/></p>"<<endl;
	while(ar.ReadString(cs))                            //��������������ӵķ�ʽ���ֳ������뿴�ĸ���ҳ��������Ӽ���
	{
		LPCTSTR p = cs;
		//outFile<<"<a href="<<y<<p<<y<<"style="<<y<<"text-decoration:none"<<y<<">"<<p<<"</a>"<<endl<<"<br />";
		outFile<<"<p><img src="<<y<<p<<y<<"width = 400 align = right"<<" /></p>";
	}
	outFile<<"<p><img src="<<y<<"tail.gif"<<y<<"/></p></div></body>"<<endl<<"</html>"<<endl;         //��������html���   

	                                                   // ��chrome�������result.html��ҳ�ļ� 
    ShellExecute(0,_T("open"),_T("chrome.exe"),_T("result.html"),0,0);
}


void CX_ImageSearchingDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
    int m = pNMListView->iItem;
    int n = pNMListView->iSubItem;

    if(m >=0)
    {
      CString txt = x_listControl.GetItemText(m,n);
	  LPCTSTR pictureName = txt;
	  char n[30];
	  int i;
	  for(i = 0; ;i++)
	  {
		  if(pictureName[i] == '.')
			  break;
		  else
			  n[i] = pictureName[i];
	  }
	  n[i] = '.';
	  n[i+1] = 'J';
	  n[i+2] = 'P';
	  n[i+3] = 'E';
	  n[i+4] = 'G';
	  n[i+5] = '\0';

	  selected = n;
	  CImage image;
	  image.Load(n);
	  CRect rect;
	  int cx = image.GetWidth();
	  int cy = image.GetHeight();
	  similar_image_search(n);
	  GetDlgItem(IDC_PICTURE)->GetWindowRect(&rect);
	  ScreenToClient(&rect);
	  GetDlgItem(IDC_PICTURE)->MoveWindow(rect.left,rect.top,cx,cy,TRUE);

	  CWnd *pWnd = GetDlgItem(IDC_PICTURE);
	  pWnd->GetClientRect(&rect);

	  CDC *pDC = pWnd->GetDC();

	  image.Draw(pDC->m_hDC,rect);
	  ReleaseDC(pDC);
    }

	*pResult = 0;
}


void CX_ImageSearchingDlg::OnBnClickedCm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//DeleteFileA("result.txt");//���Ѿ�����result.txt�ļ�����ɾȥ��Ȼ����������
	outputTheResult();
}
