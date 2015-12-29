// OffsetWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Rearrange.h"
#include "MainDlg.h"
#include "OffsetWnd.h"

extern "C"{
	#include "RearrangeMain.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OffsetWnd

OffsetWnd::OffsetWnd(UINT* TF)
{
	TimerFlag = TF;
	displaystate = TRUE;
	mousestate = 0;
	pointer1 = AfxGetApp()->LoadCursor(IDC_POINTER1);
	pointer2 = AfxGetApp()->LoadCursor(IDC_POINTER2);
}

OffsetWnd::~OffsetWnd()
{
}


BEGIN_MESSAGE_MAP(OffsetWnd, CWnd)
	//{{AFX_MSG_MAP(OffsetWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// OffsetWnd message handlers

void OffsetWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	UpdateDisplay();
	if(*TimerFlag == 0){
		DrawOffsets();

		if(displaystate == TRUE){
			DrawEnvelope();
		}else{
			DrawZero();
		}
	}
	DrawCurrOffset();
	// Do not call CWnd::OnPaint() for painting messages
}

void OffsetWnd::UpdateDisplay()
{
	UINT i,j;
	int y,max;
	double stride;
	CPen pen1;

	CClientDC dc(this);

	CRect cr;
	GetClientRect(&cr);

	dc.SetBkColor(RGB(0,0,0));

	dc.FillSolidRect(cr ,RGB(0,0,0));

	stride = (double)Wave.TotalNumSamples / (double)cr.right;
//	if(stride >= 1.0){
		dc.SetROP2(R2_COPYPEN);
		
		if(pen1.CreatePen(PS_SOLID,1,RGB(128,128,128)))
		{
			CPen* oldpen = dc.SelectObject(&pen1);
		//	dc->MoveTo(CPoint(0,cr.bottom / 2));
			int cb; //For SPEED
			cb = (int)UIRoundD((double)cr.bottom / 2.0);
			for(i = 0; i < (UINT)cr.right; i++){
				max = cb;
				for(j = 0; j < stride; j++){
					y = ((int)(Wave.PSample[(int)(i * stride) + j] * (cb - 4))  + cb);
					if(y > cb){
						if(y > max)
							max = y;
					}else{
						if(y < max)
							max = y;
					}
				}
				dc.MoveTo(CPoint(i,cb));
				dc.LineTo(CPoint(i,max));

			}
			dc.SelectObject(oldpen);
		}
/*	}else{
		dc->SetROP2(R2_COPYPEN);
		
		if(pen1.CreatePen(PS_SOLID,1,RGB(128,128,128)))
		{
			CPen* oldpen = dc->SelectObject(&pen1);
		//	dc->MoveTo(CPoint(0,cr.bottom / 2));
			for(i = 0; i < Wave.TotalNumSamples; i++){
				y = (int)(Wave.PSample[i] * ((int)(cr.bottom / 2.0) - 4) + (cr.bottom / 2));
				dc->MoveTo(CPoint(i,cr.bottom / 2));
				dc->LineTo(CPoint(i,y));
			}
//			dc->MoveTo(CPoint(i,cr.bottom / 2));
//			dc->LineTo(CPoint(cr.right,cr.bottom / 2));
			dc->SelectObject(oldpen);
		}
	}*/

/*	if(displaystate == TRUE){
		DisplayThresh();
		}else{
		DisplayZero();
		}*/
}

void OffsetWnd::DrawEnvelope()
{
	int y,max,i,j;
	double stride;
	CPen pen;
	
	CClientDC dc(this);
	
	CRect cr;
	GetClientRect(&cr);

//	stride = Wave.TotalNumSamples / cr.right;
	
//	if(stride >= 1.0){	
		stride = ((double)Wave.TotalNumSamples / (double)Wave.WindowSize) / (double)cr.right;

		dc.SetROP2(R2_COPYPEN);
		if(pen.CreatePen(PS_SOLID,1,RGB(255,255,255)))
		{
			CPen* oldpen = dc.SelectObject(&pen);
			dc.MoveTo(CPoint(0,cr.bottom));
			for(i = 0; i < cr.right; i++){
				max = (cr.bottom - 1);
				for(j = 0; j < stride; j++){
					y = (int)(Wave.PEnvelop[(int)(i * stride) + j] * (-(cr.bottom - 4)) + cr.bottom );
					if(y < max)
						max = y;					
				}
				dc.LineTo(CPoint(i,max));
				dc.MoveTo(CPoint(i,max));
			}
			dc.SelectObject(oldpen);
		}
/*	}else{
		dc->SetROP2(R2_COPYPEN);

		stride = Wave.TotalNumSamples / Wave.WindowSize;
		
		if(pen.CreatePen(PS_SOLID,1,RGB(255,255,255)))
		{
			CPen* oldpen = dc->SelectObject(&pen);
			dc->MoveTo(CPoint(0,cr.bottom));
			for(i = 0; i < stride; i++){
				y = (int)(Wave.PEnvelop[i] * (-(cr.bottom - 4)) + cr.bottom );
				dc->LineTo(CPoint(i * Wave.WindowSize,y));
				dc->MoveTo(CPoint(i * Wave.WindowSize,y));
			}
			dc->SelectObject(oldpen);
		}
	}*/
}

void OffsetWnd::DrawZero()
{
	CPen pen;
	CClientDC dc(this);

	CRect cr;
	GetClientRect(&cr);
	dc.SetROP2(R2_COPYPEN);

	if(pen.CreatePen(PS_SOLID,1,RGB(255,255,255)))
	{
		CPen* oldpen = dc.SelectObject(&pen);
		dc.MoveTo(CPoint(0,cr.bottom / 2));
		dc.LineTo(CPoint(cr.right,cr.bottom / 2));
		dc.SelectObject(oldpen);
	}
}

void OffsetWnd::DrawOffsets()
{
	SetOffset(0,Offset[0],RGB(255,0,0));
	SetOffset(1,Offset[1],RGB(255,128,0));
	SetOffset(2,Offset[2],RGB(255,255,0));
	SetOffset(3,Offset[3],RGB(0,255,0));
	SetOffset(4,Offset[4],RGB(0,255,255));
	SetOffset(5,Offset[5],RGB(0,128,255));
	SetOffset(6,Offset[6],RGB(0,0,255));
	SetOffset(7,Offset[7],RGB(255,0,255));
}

void OffsetWnd::SetOffset(UINT offnum, UINT newloc, COLORREF color)
{
	CClientDC dc(this);

	CPen /*newpen1,*/newpen2;
	CRect cr;
	GetClientRect(&cr);

	dc.SetROP2(R2_COPYPEN);
	/*		
	dc->SetROP2(R2_XORPEN);
	if(newpen1.CreatePen(PS_SOLID,1,dc->GetPixel((UINT)(((double)Offset[offnum] / (double)Wave.TotalNumSamples) * (double)cr.right),0)))
	{
		CPen* oldpen = dc->SelectObject(&newpen1);
		dc->MoveTo(CPoint((UINT)(((double)Offset[offnum] / (double)Wave.TotalNumSamples) * (double)cr.right),cr.top));
		dc->LineTo(CPoint((UINT)(((double)Offset[offnum] / (double)Wave.TotalNumSamples) * (double)cr.right),cr.bottom));
		dc->SelectObject(oldpen);
	}
*/
	Offset[offnum] = newloc;

	if(newpen2.CreatePen(PS_SOLID,1,color))
	{
		CPen* oldpen = dc.SelectObject(&newpen2);
		dc.MoveTo(CPoint((UINT)(((double)Offset[offnum] / (double)Wave.TotalNumSamples) * (double)cr.right),cr.top));
		dc.LineTo(CPoint((UINT)(((double)Offset[offnum] / (double)Wave.TotalNumSamples) * (double)cr.right),cr.bottom));
		dc.SelectObject(oldpen);
	}
}

void OffsetWnd::DrawCurrOffset()
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

void OffsetWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect cr;
	CWnd *pParent;
	UINT i;
	
	if(mousestate < 1){	
		pParent = GetParent();
		GetClientRect(&cr);
		
		for(i = 0; i < 8; i++){
			if((((int)point.x - 1) <= (int)UIRoundD(((double)Offset[i] / (double)Wave.TotalNumSamples) * (double)cr.right))
				&& ((UINT)(point.x + 2) >= UIRoundD(((double)Offset[i] / (double)Wave.TotalNumSamples) * (double)cr.right))){
			SetCursor(pointer1);
				CurrOffset = i;
				DrawCurrOffset();
				
				char buffer[100];
				sprintf(buffer,"%u",Offset[CurrOffset]);
				
				pParent->SetDlgItemText(IDC_EDITCURROFF,buffer);
				pParent->UpdateData(TRUE);
				
				
				mousestate = 1;
			}
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void OffsetWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	static UINT oldx = 0;
	static COLORREF col = RGB(255,255,255);
	
	if(nFlags != NULL){
		CRect cr;
		GetClientRect(&cr);
		if(mousestate == 1){
			UpdateDisplay();
			if(displaystate == TRUE){
				DrawEnvelope();
			}else{
				DrawZero();
			}
			mousestate = 2;
			oldx = UIRoundD(((double)Offset[CurrOffset] / (double)Wave.TotalNumSamples) * (double)cr.right);
			switch (CurrOffset){
			case 0:
				col = RGB(255,0,0);
				break;
			case 1:
				col = RGB(255,128,0);
				break;
			case 2:
				col = RGB(255,255,0);
				break;
			case 3:
				col = RGB(0,255,0);
				break;
			case 4:
				col = RGB(0,255,255);
				break;
			case 5:
				col = RGB(0,128,255);
				break;
			case 6:
				col = RGB(0,0,255);
				break;
			case 7:
				col = RGB(255,0,255);
				break;
			}
		}
		if(mousestate == 2){
			
			
			CWnd *pParent;
			pParent = GetParent();
			
			CClientDC dc(this);
	
			CPen newpen1;
			
			dc.SetROP2(R2_XORPEN);	
			
			if(newpen1.CreatePen(PS_SOLID,1,col))
			{
				CPen* oldpen = dc.SelectObject(&newpen1);
				dc.MoveTo(oldx,0);
				dc.LineTo(oldx,cr.bottom);
				dc.MoveTo(point.x,0);
				dc.LineTo(point.x,cr.bottom);
				oldx = point.x;
				dc.SelectObject(oldpen);
			}
			
			char buffer[100];
			Offset[CurrOffset] = UIRoundD(((double)point.x / (double)cr.right) * (double)Wave.TotalNumSamples);
			if(Offset[CurrOffset] >= Wave.TotalNumSamples)
				Offset[CurrOffset] = Wave.TotalNumSamples - 1;
			sprintf(buffer,"%u",Offset[CurrOffset]);
			pParent->SetDlgItemText(IDC_EDITCURROFF,buffer);
			
			pParent->UpdateData(TRUE);
		}
		
	}
	CWnd::OnMouseMove(nFlags, point);
}

void OffsetWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(mousestate >= 2){
		
		UpdateDisplay();
		
		if(displaystate == TRUE){
			DrawEnvelope();
		}else{
			DrawZero();
		}
		
		DrawOffsets();	
	}
	
	mousestate = 0;
	CWnd::OnLButtonUp(nFlags, point);
}

void OffsetWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect cr;
	CWnd *pParent;
	UINT i;
	
	if(mousestate < 1){	
		pParent = GetParent();
		GetClientRect(&cr);
		
		for(i = 0; i < 8; i++){
			if((((int)point.x - 1) <= (int)UIRoundD(((double)Offset[i] / (double)Wave.TotalNumSamples) * (double)cr.right))
				&& ((UINT)(point.x + 2) >= UIRoundD(((double)Offset[i] / (double)Wave.TotalNumSamples) * (double)cr.right))){
				SetCursor(pointer2);
				CurrOffset = i;
				DrawCurrOffset();
				
				char buffer[100];
				sprintf(buffer,"%u",Offset[CurrOffset]);
				
				pParent->SetDlgItemText(IDC_EDITCURROFF,buffer);
				pParent->UpdateData(TRUE);
								
				mousestate = 1;
			}
		}
	}
	
	CWnd::OnRButtonDown(nFlags, point);
}

void OffsetWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if(mousestate >= 1)
	{
		FindOnset();
		
		UpdateDisplay();	
		if(displaystate == TRUE){
			DrawEnvelope();
		}else{
			DrawZero();
		}
		DrawOffsets();	

		char buffer[100];
		sprintf(buffer,"%u",Offset[CurrOffset]);

		CWnd* pParent;
		pParent = GetParent();
		pParent->SetDlgItemText(IDC_EDITCURROFF,buffer);

		mousestate = 0;
		CWnd::OnRButtonUp(nFlags, point);
	}
}
