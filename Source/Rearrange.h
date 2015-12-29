// Rearrange.h : main header file for the REARRANGE application
//

#if !defined(AFX_REARRANGE_H__C280E545_BEAA_11D1_AEC0_E383BD573F37__INCLUDED_)
#define AFX_REARRANGE_H__C280E545_BEAA_11D1_AEC0_E383BD573F37__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRearrangeApp:
// See Rearrange.cpp for the implementation of this class
//

class CRearrangeApp : public CWinApp
{
public:
	CRearrangeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRearrangeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRearrangeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REARRANGE_H__C280E545_BEAA_11D1_AEC0_E383BD573F37__INCLUDED_)
