// SequenceGenerator.cpp : implementation file
//

#include "stdafx.h"
#include "Rearrange.h"
#include "SequenceGenerator.h"
extern "C"{
	#include "RearrangeMain.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSequenceGenerator dialog


CSequenceGenerator::CSequenceGenerator(CWnd* pParent /*=NULL*/)
	: CDialog(CSequenceGenerator::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSequenceGenerator)
	m_editdur2val = Sequence.Duration;
	m_editoff2val = NumOffsets;
	m_editres2val = Sequence.Resolution;
	//}}AFX_DATA_INIT
}


void CSequenceGenerator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSequenceGenerator)
	DDX_Control(pDX, IDC_SCROLIRREG, m_scrolirreg);
	DDX_Control(pDX, IDC_SCROLDISARR, m_scroldisarr);
	DDX_Control(pDX, IDC_SCROLDENS, m_scroldens);
	DDX_Text(pDX, IDC_EDITDUR2, m_editdur2val);
	DDV_MinMaxUInt(pDX, m_editdur2val, 1, 96);
	DDX_Text(pDX, IDC_EDITOFF2, m_editoff2val);
	DDV_MinMaxUInt(pDX, m_editoff2val, 1, 8);
	DDX_Text(pDX, IDC_EDITRES2, m_editres2val);
	DDV_MinMaxUInt(pDX, m_editres2val, 1, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSequenceGenerator, CDialog)
	//{{AFX_MSG_MAP(CSequenceGenerator)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSequenceGenerator message handlers

BOOL CSequenceGenerator::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char s[100];
	UpdateData(FALSE);
/*	sprintf(s,"%u",m_editres2val);
	SetDlgItemText(IDC_EDITRES2,s);
	sprintf(s,"%u",m_editdur2val);
	SetDlgItemText(IDC_EDITODUR2,s);
	sprintf(s,"%u",m_editoff2val);
	SetDlgItemText(IDC_EDITOFF2,s);*/

	sprintf(s,"Disarrangement: %d%%",Disarrangement);
	SetDlgItemText(IDC_STATDISARR,s);

	if(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) <= 0.25)
		sprintf(s,"Irregularity: %d%% 8x",UIRoundD(400.0 * ((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX)));
	if(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) > 0.25)
		sprintf(s,"Irregularity: %d%% 16x",UIRoundD(400.0 * (((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) - 0.25)));
	if(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) > 0.50)
		sprintf(s,"Irregularity: %d%% 32x",UIRoundD(200.0 * (((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) - 0.50)));

	SetDlgItemText(IDC_STATIRREG,s);
	sprintf(s,"Density: %d%%",Density);
	SetDlgItemText(IDC_STATDENS,s);

	m_scroldisarr.SetScrollRange(
		DEF_SEQGEN_DISARR_MIN , DEF_SEQGEN_DISARR_MAX );
	m_scroldisarr.SetScrollPos( Disarrangement );

	m_scrolirreg.SetScrollRange(
		DEF_SEQGEN_IRREG_MIN , DEF_SEQGEN_IRREG_MAX );	
	m_scrolirreg.SetScrollPos( Irregularity );

	m_scroldens.SetScrollRange(
		 DEF_SEQGEN_DENS_MIN , DEF_SEQGEN_DENS_MAX );
	m_scroldens.SetScrollPos( Density );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSequenceGenerator::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int pos;

	pos = pScrollBar->GetScrollPos();
	switch(nSBCode){
		case SB_PAGEUP:
			pos -= 5;
			break;
		case SB_LINEUP:
			pos -= 1;
			break;
		case SB_PAGEDOWN:
			pos += 5;
			break;
		case SB_LINEDOWN:
			pos += 1;
			break;
		case SB_THUMBTRACK:
			pos = nPos;
			break;
		default:
			return;
	}
	pScrollBar->SetScrollPos(pos);

	if(pScrollBar == &m_scroldisarr){
		if(pos < DEF_SEQGEN_DISARR_MIN)
			pos = DEF_SEQGEN_DISARR_MIN;
		if(pos > DEF_SEQGEN_DISARR_MAX)
			pos = DEF_SEQGEN_DISARR_MAX;
		char s[100];
		sprintf(s,"Disarrangement: %d%%",pos);
		SetDlgItemText(IDC_STATDISARR,s);
		Disarrangement = pos;
	}

	if(pScrollBar == &m_scrolirreg){
		if(pos < DEF_SEQGEN_IRREG_MIN)
			pos = DEF_SEQGEN_IRREG_MIN;
		if(pos > DEF_SEQGEN_IRREG_MAX)
			pos = DEF_SEQGEN_IRREG_MAX;
		char s[100];
	
		if(((double)pos / (double)DEF_SEQGEN_IRREG_MAX) <= 0.25)
			sprintf(s,"Irregularity: %d%% 8x",UIRoundD(400.0 * ((double)pos / (double)DEF_SEQGEN_IRREG_MAX)));
		if(((double)pos / (double)DEF_SEQGEN_IRREG_MAX) > 0.25)
			sprintf(s,"Irregularity: %d%% 16x",UIRoundD(400.0 * (((double)pos / (double)DEF_SEQGEN_IRREG_MAX)- 0.25)));
		if(((double)pos / (double)DEF_SEQGEN_IRREG_MAX) > 0.50)
			sprintf(s,"Irregularity: %d%% 32x",UIRoundD(200.0 * (((double)pos / (double)DEF_SEQGEN_IRREG_MAX)- 0.50)));
		
		SetDlgItemText(IDC_STATIRREG,s);
		Irregularity = pos;
	}

	if(pScrollBar == &m_scroldens){
		if(pos < DEF_SEQGEN_DENS_MIN)
			pos = DEF_SEQGEN_DENS_MIN;
		if(pos > DEF_SEQGEN_DENS_MAX)
			pos = DEF_SEQGEN_DENS_MAX;
		char s[100];
		sprintf(s,"Density: %d%%",pos);
		SetDlgItemText(IDC_STATDENS,s);
		Density = pos;
	}
	UpdateData(TRUE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSequenceGenerator::OnOK() 
{
	BOOL test = FALSE;
	UpdateData(TRUE);
	if(m_editres2val > 128){
		m_editres2val = 128;
		test = TRUE;
	}
	if(m_editres2val < 1){
		m_editres2val = 1;
		test = TRUE;
	}
	if(m_editdur2val > 96){
		m_editdur2val = 96;
		test = TRUE;
	}
	if(m_editdur2val < 1){
		m_editdur2val = 1;	
		test = TRUE;
	}
		if(m_editoff2val > NUM_OFFSETS){
		m_editoff2val = NUM_OFFSETS;
		test = TRUE;
	}
	if(m_editoff2val < 1){
		m_editoff2val = 1;	
		test = TRUE;
	}
	UpdateData(FALSE);

	NumOffsets = m_editoff2val;
	Sequence.Resolution = m_editres2val;
	Sequence.Duration = m_editdur2val;
	if(test == FALSE)
		CDialog::OnOK();
}
