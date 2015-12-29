// Startup.cpp : implementation file
//

#include "stdafx.h"
#include "Rearrange.h"
#include "Startup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartup dialog


CStartup::CStartup(CWnd* pParent /*=NULL*/)
	: CDialog(CStartup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStartup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartup, CDialog)
	//{{AFX_MSG_MAP(CStartup)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartup message handlers
