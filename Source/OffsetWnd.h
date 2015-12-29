#if !defined(AFX_OFFSETWND_H__54DA5E61_C367_11D1_AEC0_A4F577576DC0__INCLUDED_)
#define AFX_OFFSETWND_H__54DA5E61_C367_11D1_AEC0_A4F577576DC0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OffsetWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OffsetWnd window

class OffsetWnd : public CWnd
{
// Construction
public:
	OffsetWnd(UINT *TF);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OffsetWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT* TimerFlag;
	HCURSOR pointer1;
	HCURSOR pointer2;
	UINT mousestate;
	void DrawCurrOffset();
	void SetOffset(UINT offnum, UINT newloc, COLORREF color);
	void DrawOffsets();
	void DrawZero();
	BOOL displaystate;
	void DrawEnvelope();
	void UpdateDisplay();
	virtual ~OffsetWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(OffsetWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OFFSETWND_H__54DA5E61_C367_11D1_AEC0_A4F577576DC0__INCLUDED_)
