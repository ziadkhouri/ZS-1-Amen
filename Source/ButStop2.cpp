// ButStop2.cpp : implementation file
//

#include "stdafx.h"
#include "Rearrange.h"
#include "ButStop2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButStop2 dialog


CButStop2::CButStop2(CWnd* pParent /*=NULL*/)
	: CDialog(CButStop2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CButStop2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CButStop2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButStop2)
	DDX_Control(pDX, IDOK, m_butstop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CButStop2, CDialog)
	//{{AFX_MSG_MAP(CButStop2)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButStop2 message handlers

void CButStop2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CWnd *pParent;
	CRect wr;

	pParent = GetOwner();
	pParent->GetWindowRect(&wr);
  MoveWindow(4 + wr.left + 50,wr.bottom - 4 - 29 ,79,23);
	m_butstop.MoveWindow(0,0,79,23);
	
	// Do not call CDialog::OnPaint() for painting messages
}
