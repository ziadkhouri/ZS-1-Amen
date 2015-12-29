// SequenceWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Rearrange.h"
#include "SequenceWnd.h"
#include "MainDlg.h"
#include <math.h>
extern "C"{
	#include "RearrangeMain.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SequenceWnd

SequenceWnd::SequenceWnd()
{
}

SequenceWnd::~SequenceWnd()
{
}


BEGIN_MESSAGE_MAP(SequenceWnd, CWnd)
	//{{AFX_MSG_MAP(SequenceWnd)
	ON_WM_PAINT()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// SequenceWnd message handlers

void SequenceWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	UpdateDisplay();
	// Do not call CWnd::OnPaint() for painting messages
}

void SequenceWnd::UpdateDisplay()
{
	
	CClientDC dc(this);

	CPen pen1,pen2;
	UINT i,j;
	double stride, stride2;

	CRect cr;
	GetClientRect(&cr);

	dc.SetBkColor(RGB(0,0,0));
	dc.FillSolidRect(cr,RGB(0,0,0));

	stride = (double)cr.right / (double)(Sequence.Duration * Sequence.Resolution);

	for(i = 0; i < (Sequence.Duration * Sequence.Resolution); i++){
		switch((Sequence.PCell + i)->OffsetIndex){
		case 0:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(255,0,0));
			break;
		case 1:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(255,128,0));
			break;
		case 2:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(255,255,0));
			break;
		case 3:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(0,255,0));
			break;
		case 4:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(0,255,255));
			break;
		case 5:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(0,128,255));
			break;
		case 6:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(0,0,255));
			break;
		case 7:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(255,0,255));
			break;
		case EMPTY_CELL_VAL:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(0,0,0));
			break;
		default:
			dc.FillSolidRect(CRect(UIRoundD((double)i * stride),0
				,UIRoundD(((double)i + 1.0) * stride),cr.bottom) ,RGB(0,0,0));
		}
	}

	dc.SetROP2(R2_COPYPEN);

	stride = (double)cr.right / (double)Sequence.Resolution / (double)Sequence.Duration;
	stride2 = (double)cr.right / (double)Sequence.Duration;

	if(pen1.CreatePen(PS_SOLID,1,RGB(128,128,128)))
	{
		CPen* oldpen = dc.SelectObject(&pen1);

		for(j = 0; j < Sequence.Duration; j++){
			for(i = 0; i < Sequence.Resolution; i++){
				dc.MoveTo(CPoint(UIRoundD((double)i * stride) + UIRoundD(stride2 * (double)j),cr.bottom));
				dc.LineTo(CPoint(UIRoundD((double)i * stride) + UIRoundD(stride2 * (double)j),0));
			}
		}	
		dc.SelectObject(oldpen);
	}

	dc.SetROP2(R2_COPYPEN);
	
	if(pen2.CreatePen(PS_SOLID,1,RGB(255,255,255)))
	{
		CPen* oldpen = dc.SelectObject(&pen2);

		for(j = 0; j < Sequence.Duration; j++){
			dc.MoveTo(CPoint(UIRoundD(stride2 * (double)j),cr.bottom));
			dc.LineTo(CPoint(UIRoundD(stride2 * (double)j),0));

			dc.MoveTo(CPoint(UIRoundD(stride2 * (double)j + (stride2 / 2.0)),cr.bottom));
			dc.LineTo(CPoint(UIRoundD(stride2 * (double)j + (stride2 / 2.0)),UIRoundD((double)cr.bottom / 2.0)));

			dc.MoveTo(CPoint(UIRoundD(stride2 * (double)j + ((3.0 * stride2) / 4.0)),cr.bottom));
			dc.LineTo(CPoint(UIRoundD(stride2 * (double)j + ((3.0 * stride2) / 4.0)),UIRoundD((3.0 * (double)cr.bottom) / 4.0)));
			
			dc.MoveTo(CPoint(UIRoundD(stride2 * (double)j + (stride2 / 4.0)),cr.bottom));
			dc.LineTo(CPoint(UIRoundD(stride2 * (double)j + (stride2 / 4.0)),UIRoundD((3.0 * (double)cr.bottom) / 4.0)));
		}
		dc.SelectObject(oldpen);
	}
}


void SequenceWnd::DrawCurrOffset()
{
	CWnd *pParent;
	CRect cr;
	CDC* dc;

	pParent = GetParent();
	pParent->GetClientRect(&cr);

	dc = pParent->GetDC();
	if(dc == NULL){
		exit(-1);
	}
	switch (CurrOffset){
		case 0:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(255,0,0));
			break;
		case 1:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(255,128,0));
			break;
		case 2:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(255,255,0));
			break;
		case 3:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(0,255,0));
			break;
		case 4:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(0,255,255));
			break;
		case 5:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(0,128,255));
			break;
		case 6:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(0,0,255));
			break;
		case 7:
			dc->FillSolidRect(CRect(cr.left + 339,cr.bottom - 81 - 7,cr.left + 342 + 63,cr.bottom - 81 - 3),RGB(255,0,255));
			break;
	}
	pParent->ReleaseDC(dc);
}


void SequenceWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	UINT i;
	CRect cr;
	GetClientRect(&cr);

	i = (UINT)floor(((double)point.x / (double)cr.right) * (double)Sequence.Resolution * (double)Sequence.Duration);
	if((Sequence.PCell + i)->OffsetIndex != EMPTY_CELL_VAL){
		CurrOffset = (Sequence.PCell + i)->OffsetIndex;
		CurrOffset =  (++CurrOffset) % NUM_OFFSETS;
		(Sequence.PCell + i)->OffsetIndex  = CurrOffset;
		DrawCurrOffset();
		UpdateDisplay();	
	}
	
	CWnd::OnRButtonUp(nFlags, point);
}

void SequenceWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	UINT i;
	CRect cr;
	GetClientRect(&cr);

	i = (UINT)floor(((double)point.x / (double)cr.right) * (double)Sequence.Resolution * (double)Sequence.Duration);
	if((Sequence.PCell + i)->OffsetIndex == EMPTY_CELL_VAL){
		(Sequence.PCell + i)->OffsetIndex  = CurrOffset;
	}else{
		(Sequence.PCell + i)->OffsetIndex  = EMPTY_CELL_VAL;
	}

	UpdateDisplay();
	
	CWnd::OnLButtonUp(nFlags, point);
}
