#if !defined(AFX_SEQUENCEWND_H__A7B74981_CBD3_11D1_AEC0_8D0D5CDAA34F__INCLUDED_)
#define AFX_SEQUENCEWND_H__A7B74981_CBD3_11D1_AEC0_8D0D5CDAA34F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SequenceWnd.h : header file
//
#include "OffsetWnd.h"

/////////////////////////////////////////////////////////////////////////////
// SequenceWnd window

class SequenceWnd : public CWnd
{
// Construction
public:
	SequenceWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SequenceWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawCurrOffset();
	void UpdateDisplay();
	virtual ~SequenceWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(SequenceWnd)
	afx_msg void OnPaint();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEQUENCEWND_H__A7B74981_CBD3_11D1_AEC0_8D0D5CDAA34F__INCLUDED_)
