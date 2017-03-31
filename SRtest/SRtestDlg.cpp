
// SRtestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SRtest.h"
#include "SRtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSRtestDlg �Ի���



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


// CSRtestDlg ��Ϣ�������

BOOL CSRtestDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSRtestDlg::OnPaint()
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
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSRtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#pragma comment(lib,"../Release/SRwelld.lib")
#include "../SRwelld/SRwelld.h"
void CSRtestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	srReleaseResizeCoef();
}

