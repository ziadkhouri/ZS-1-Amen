// ButStop.cpp : implementation file
//

#include "stdafx.h"
#include "Rearrange.h"
#include "ButStop.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButStop dialog


CButStop::CButStop(CWnd* pParent /*=NULL*/)
	: CDialog(CButStop::IDD, pParent)
{
	//{{AFX_DATA_INIT(CButStop)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CButStop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButStop)
	DDX_Control(pDX, IDOK, m_butstop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CButStop, CDialog)
	//{{AFX_MSG_MAP(CButStop)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButStop message handlers

void CButStop::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CWnd *pParent;
	CRect wr;

	pParent = GetOwner();
	pParent->GetWindowRect(&wr);
  MoveWindow(4 + wr.left + 80 + 4,wr.bottom - 4 - 79 - 23 ,71,23);
	m_butstop.MoveWindow(0,0,71,23);
	// Do not call CDialog::OnPaint() for painting messages
}
