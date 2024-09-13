
// PleaseDlg.h : header file
//
#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartLabel.h"
#pragma once


// CPleaseDlg dialog
class CPleaseDlg : public CDialogEx
{
// Construction
public:
	CPleaseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PLEASE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CChartCtrl m_ChartCtrl;
	CChartStandardAxis* pBottomAxis;
	CChartStandardAxis* pLeftAxis;
	CChartPointsSerie* pSeries;
	CChartLineSerie* pSerie;
};
