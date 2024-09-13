
// PleaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Please.h"
#include "PleaseDlg.h"
#include "afxdialogex.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartPointsSerie.h"
#include "ChartCtrl\ChartSurfaceSerie.h"
#include "ChartCtrl\ChartGrid.h"
#include "ChartCtrl\ChartBarSerie.h"
#include "ChartCtrl\ChartLabel.h"

#include "ChartCtrl\ChartAxisLabel.h"
#include "ChartCtrl\ChartStandardAxis.h"
#include "ChartCtrl\ChartDateTimeAxis.h"

#include "ChartCtrl\ChartCrossHairCursor.h"
#include "ChartCtrl\ChartDragLineCursor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CPleaseDlg dialog




CPleaseDlg::CPleaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPleaseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPleaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
}

BEGIN_MESSAGE_MAP(CPleaseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CPleaseDlg message handlers

BOOL CPleaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CChartCtrl ref;
	ref.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(true);
	pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis); 
	pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pBottomAxis->SetMinMax(-2, 4);
	pLeftAxis->SetMinMax(-2, 4);
	pBottomAxis->SetTickIncrement(false, 20.0);
	pBottomAxis->SetDiscrete(false);
	pBottomAxis->EnableScrollBar(true);

	pSeries = m_ChartCtrl.CreatePointsSerie();
	pSeries->ClearSerie();
	pSeries->SetColor(RGB(0, 0, 255)); //Blue
	double X1ValA[20] = { 2.517698, 2.437809, 2.350005, 2.439785, 2.431612, 2.559086, 2.646461, 2.571107, 2.489640, 2.537891};
	double X2ValA[20] = { 0.935017, -0.104350, -0.033527, 0.046756, 0.019428, 0.960286, 0.749433, 0.585592, 0.902089, 1.186642};
	pSeries->SetPoints(X1ValA, X2ValA, 20);
	
	pSeries = m_ChartCtrl.CreatePointsSerie();
	pSeries->ClearSerie();
	pSeries->SetColor(RGB(0, 255, 0)); //Green
	double X1ValE[20] = { 2.580691, 2.491221, 2.406124, 2.429034, 2.323496, 0.906010, 1.200899, 1.249910, 1.268834, 1.447836};
	double X2ValE[20] = { -1.315633, 0.664569, 0.812542, 0.812283, 0.785103, 1.889869, 1.292844, 1.219653, 1.099945, 1.279805};
	pSeries->SetPoints(X1ValE, X2ValE, 20);
	
	pSeries = m_ChartCtrl.CreatePointsSerie();
	pSeries->ClearSerie();
	pSeries->SetColor(RGB(255, 255, 0)); //Yellow
	double X1ValI[20] = { 1.359790, 1.250591, 1.029996, 1.055910, 1.046444, 1.192805, 1.201017, 1.182028, 1.372785, 1.358149};
	double X2ValI[20] = { -0.414586, -0.627901, -0.879671, -0.496843, -0.491424, 0.030973, 0.459908, 0.540104, -0.160144, -0.475751};
	pSeries->SetPoints(X1ValI, X2ValI, 20);

	pSeries = m_ChartCtrl.CreatePointsSerie();
	pSeries->ClearSerie();
	pSeries->SetColor(RGB(255, 0, 0)); //Red
	double X1ValO[20] = { 1.221799, 1.396369, 1.187837, 1.217572, 1.206330, 1.400851, 1.669933, 1.739863, 1.508711, 1.671336};
	double X2ValO[20] = { 2.579040, 2.192817, 2.590984, 2.899500, 2.935252, 2.787321, 2.592942, 3.273837, 2.943879, 2.848514};
	pSeries->SetPoints(X1ValO, X2ValO, 20);


	pSeries = m_ChartCtrl.CreatePointsSerie();
	pSeries->ClearSerie();
	pSeries->SetColor(RGB(0, 0, 0)); //Black
	double X1ValU[20] = { 1.062204, 1.103320, 0.996336, 1.138870, 1.169659, 1.421484, 1.215674, 1.183220, 1.170496, 1.393087};
	double X2ValU[20] = { 2.155811, 2.321889, 2.455996, 2.555053, 2.503188, 2.430105, 2.529144, 2.230777, 2.632343, 2.911725};
	pSeries->SetPoints(X1ValU, X2ValU, 20);


	//Line for A 
	pSerie = m_ChartCtrl.CreateLineSerie();
	pSerie->ClearSerie();
	pSerie->SetWidth(2); //line width
	pSerie->SetColor(RGB(0, 0, 255)); //Blue
	double XValA[2] = {-2, 4};
	double YValA[2] = {-205.208, 113.503};
	pSerie->SetPoints(XValA, YValA, 2);
	
	//Line for E
	//pSerie = m_ChartCtrl.CreateLineSerie();
	//pSerie->ClearSerie();
	//pSerie->SetWidth(2); //line width
	//pSerie->SetColor(RGB(0, 255, 0)); //Green
	//double XValE[4] = {-2, 4};
	//double YValE[4] = {-9.88986, 3.7211};
	//pSerie->SetPoints(XValE, YValE, 2);

	//Line for I 
	pSerie = m_ChartCtrl.CreateLineSerie();
	pSerie->ClearSerie();
	pSerie->SetWidth(2); //line width
	pSerie->SetColor(RGB(255, 255, 0)); //Yellow
	double XValI[2] = {-2, 4};
	double YValI[2] = {6.65567, -3.54457};
	pSerie->SetPoints(XValI, YValI, 2);

	//Line for O 
	//pSerie = m_ChartCtrl.CreateLineSerie();
	//pSerie->ClearSerie();
	//pSerie->SetWidth(2); //line width
	//pSerie->SetColor(RGB(255, 0, 0)); //Red
	//double XValO[2] = {-2, 4};
	//double YValO[2] = {2565.5, 2562.54};
	//pSerie->SetPoints(XValO, YValO, 2);

	//Line for U 
	pSerie = m_ChartCtrl.CreateLineSerie();
	pSerie->ClearSerie();
	pSerie->SetWidth(2); //line width
	pSerie->SetColor(RGB(0, 0, 0)); //Black
	double XValU[2] = {-2, 4};
	double YValU[2] = {-0.467929, 3.02181};
	pSerie->SetPoints(XValU, YValU, 2);

	m_ChartCtrl.EnableRefresh(true);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPleaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPleaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPleaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

