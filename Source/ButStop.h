#if !defined(AFX_BUTSTOP_H__B1AEAFC5_C276_11D1_AEC0_8E5EC3D3E83F__INCLUDED_)
#define AFX_BUTSTOP_H__B1AEAFC5_C276_11D1_AEC0_8E5EC3D3E83F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ButStop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButStop dialog

class CButStop : public CDialog
{
// Construction
public:
	CButStop(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CButStop)
	enum { IDD = IDD_DIALOGSTOP };
	CButton	m_butstop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButStop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CButStop)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTSTOP_H__B1AEAFC5_C276_11D1_AEC0_8E5EC3D3E83F__INCLUDED_)
