// MainDlg.h : header file
//

#if !defined(AFX_MAINDLG_H__C280E547_BEAA_11D1_AEC0_E383BD573F37__INCLUDED_)
#define AFX_MAINDLG_H__C280E547_BEAA_11D1_AEC0_E383BD573F37__INCLUDED_

#include "OffsetWnd.h"	// Added by ClassView
#include "SequenceWnd.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

#define TID_OFFWND (132)
#define TID_SEQWND (133)

class CMainDlg : public CDialog
{
// Construction
public:
	UINT WAVFileLength;
	LPSTR WAVFilename;
	DSBUFFERDESC dsbuffdescSeq;
	LPDIRECTSOUNDBUFFER lpdsbuffSeq;
	WAVEFORMATEX wavefmtexSeq;
	SequenceWnd* seqwnd;
	UINT TimerFlag;
	OffsetWnd* offwnd;
	BOOL LoadWAV(LPSTR filename);
	CMainDlg(CWnd* pParent = NULL);	// standard constructor
	WAVEFORMATEX wavefmtex;
	LPDIRECTSOUNDBUFFER lpdsbuff;
	DSBUFFERDESC dsbuffdesc;
	LPDIRECTSOUND lpdirsnd;
// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_REARRANGE_DIALOG };
	CButton	m_cheksmoo;
	CSpinButtonCtrl	m_spinseqfreq;
	CSpinButtonCtrl	m_spinofffreq;
	CButton	m_butnewseq;
	CStatic	m_statbackg2;
	CButton	m_butsaveproj;
	CStatic	m_statwndsize;
	CStatic	m_statseqfreq;
	CStatic	m_statresdur;
	CStatic	m_statofffreq;
	CStatic	m_statcurroff;
	CStatic	m_statbackg;
	CEdit	m_editwndsize;
	CEdit	m_editseqfreq;
	CEdit	m_editres;
	CEdit	m_editofffreq;
	CEdit	m_editdur;
	CEdit	m_editcurroff;
	CButton	m_butwndsize;
	CButton	m_butsaveaswav;
	CButton	m_butresdur;
	CButton	m_butloadwav;
	CButton	m_butplayseq;
	CButton	m_butplayoff;
	CButton	m_butnewproj;
	CButton	m_butloadproj;
	CButton	m_butgenseq;
	CButton	m_butdisplay;
	CButton	m_butcurroff;
	UINT	m_editwndsizeval;
	UINT	m_editcurroffval;
	UINT	m_editofffreqval;
	UINT	m_editdurval;
	UINT	m_editresval;
	UINT	m_editseqfreqval;
	BOOL	m_cheksmooval;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButloadwav();
	afx_msg void OnButplayoff();
	afx_msg void OnButwndsize();
	afx_msg void OnButdisplay();
	afx_msg void OnDestroy();
	afx_msg void OnButcurroff();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButresdur();
	afx_msg void OnButplayseq();
	afx_msg void OnButnewseq();
	afx_msg void OnButgenseq();
	afx_msg void OnButsaveaswav();
	afx_msg void OnButsaveproj();
	afx_msg void OnButloadproj();
	afx_msg void OnButnewproj();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__C280E547_BEAA_11D1_AEC0_E383BD573F37__INCLUDED_)
