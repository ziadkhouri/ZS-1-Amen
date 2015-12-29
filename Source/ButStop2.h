#if !defined(AFX_BUTSTOP2_H__A7B74985_CBD3_11D1_AEC0_8D0D5CDAA34F__INCLUDED_)
#define AFX_BUTSTOP2_H__A7B74985_CBD3_11D1_AEC0_8D0D5CDAA34F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ButStop2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButStop2 dialog

class CButStop2 : public CDialog
{
// Construction
public:
	CButStop2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CButStop2)
	enum { IDD = IDD_DIALOGSTOP2 };
	CButton	m_butstop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButStop2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CButStop2)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTSTOP2_H__A7B74985_CBD3_11D1_AEC0_8D0D5CDAA34F__INCLUDED_)
