#if !defined(AFX_SEQUENCEGENERATOR_H__545DF132_CCD8_11D1_AEC0_CDCFE8AE8304__INCLUDED_)
#define AFX_SEQUENCEGENERATOR_H__545DF132_CCD8_11D1_AEC0_CDCFE8AE8304__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SequenceGenerator.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSequenceGenerator dialog

class CSequenceGenerator : public CDialog
{
// Construction
public:
	CSequenceGenerator(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSequenceGenerator)
	enum { IDD = IDD_SEQGEN };
	CScrollBar	m_scrolirreg;
	CScrollBar	m_scroldisarr;
	CScrollBar	m_scroldens;
	UINT	m_editdur2val;
	UINT	m_editoff2val;
	UINT	m_editres2val;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSequenceGenerator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSequenceGenerator)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEQUENCEGENERATOR_H__545DF132_CCD8_11D1_AEC0_CDCFE8AE8304__INCLUDED_)
