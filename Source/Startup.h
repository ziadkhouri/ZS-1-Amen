#if !defined(AFX_STARTUP_H__F9E9DEA4_D080_11D1_AEC0_818AD1E2D702__INCLUDED_)
#define AFX_STARTUP_H__F9E9DEA4_D080_11D1_AEC0_818AD1E2D702__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Startup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartup dialog

class CStartup : public CDialog
{
// Construction
public:
	CStartup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartup)
	enum { IDD = IDD_DIALOGSTARTUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartup)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTUP_H__F9E9DEA4_D080_11D1_AEC0_818AD1E2D702__INCLUDED_)
