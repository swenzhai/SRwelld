
// SRtestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SRtest.h"
#include "SRtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSRtestDlg 对话框



CSRtestDlg::CSRtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SRTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSRtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSRtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSRtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSRtestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSRtestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSRtestDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSRtestDlg 消息处理程序

BOOL CSRtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSRtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSRtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSRtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#pragma comment(lib,"../Release/SRwelld.lib")
#include "../SRwelld/SRwelld.h"
void CSRtestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	srAbout();

}

BYTE pBuf[720 * 512] = {0xff,0,1,2,0xff};
BITMAPINFO bmpInfo;
BYTE* pDst;
double scale = 2.1;
char c[1078];
BITMAPINFO *pBmpInfoDst;
void CSRtestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	bmpInfo.bmiHeader.biWidth = 720;
	bmpInfo.bmiHeader.biHeight = 440;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 8;
	FILE *fp;
	fp = fopen("D:\\20.bmp", "rb");
	fread(c, 1, 1078, fp);
	fread(pBuf, 1, 720 * 440,fp);
	fclose(fp);
	BITMAPINFO *pBInfo = (BITMAPINFO*)(&c[14]);
	srCreateResizeCoef(pBuf, pBInfo/*(BITMAPINFO*)(char*)(&c[14])*/, &pDst, &pBmpInfoDst, scale);
}

#include "TimerCounter.h"
TimerCounter tCount;
void CSRtestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	tCount.Start();
	srResize(1);
	tCount.Stop();

	static int i=10001;
	char s[256];
	sprintf(s,"%d.bmp",i++);
	FILE * fp;
	fp = fopen(s, "wb");
	/*BITMAPINFO *pBInfo = (BITMAPINFO *)&c[14];
	pBInfo->bmiHeader.biHeight = 440 * scale;
	pBInfo->bmiHeader.biWidth = 720 * scale;*/
	volatile int *sizeImgDst = (int *)&c[2];
	*sizeImgDst = 720 * scale * 440 * scale;
	int * offsetDst = (int *)&c[10];
	*offsetDst = 54;
	fwrite(c, 1, 14, fp);
	fwrite(pBmpInfoDst, 1, /*1078*/54-14, fp);
	fwrite(pDst, 1,720*scale*440*scale*3,fp);
	fclose(fp);
}


void CSRtestDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	srReleaseResizeCoef();
}

