// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rearrange.h"
#include "MainDlg.h"
#include "Progress.h"
#include "ButStop.h"
#include "ButStop2.h"
#include "Startup.h"
#include "SequenceGenerator.h"
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
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
	m_editwndsizeval = 1;
	m_editcurroffval = 0;
	m_editofffreqval = 120;
	m_editdurval = DEF_SEQ_DURATION;
	m_editresval = DEF_SEQ_RESOLUTION;
	m_editseqfreqval = 120;
	m_cheksmooval = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_CHEKSMOO, m_cheksmoo);
	DDX_Control(pDX, IDC_SPINSEQFREQ, m_spinseqfreq);
	DDX_Control(pDX, IDC_SPINOFFFREQ, m_spinofffreq);
	DDX_Control(pDX, IDC_BUTNEWSEQ, m_butnewseq);
	DDX_Control(pDX, IDC_STATBACKG2, m_statbackg2);
	DDX_Control(pDX, IDC_BUTSAVEPROJ, m_butsaveproj);
	DDX_Control(pDX, IDC_STATWNDSIZE, m_statwndsize);
	DDX_Control(pDX, IDC_STATSEQFREQ, m_statseqfreq);
	DDX_Control(pDX, IDC_STATRESDUR, m_statresdur);
	DDX_Control(pDX, IDC_STATOFFFREQ, m_statofffreq);
	DDX_Control(pDX, IDC_STATCURROFF, m_statcurroff);
	DDX_Control(pDX, IDC_STATBACKG, m_statbackg);
	DDX_Control(pDX, IDC_EDITWNDSIZE, m_editwndsize);
	DDX_Control(pDX, IDC_EDITSEQFREQ, m_editseqfreq);
	DDX_Control(pDX, IDC_EDITRES, m_editres);
	DDX_Control(pDX, IDC_EDITOFFFREQ, m_editofffreq);
	DDX_Control(pDX, IDC_EDITDUR, m_editdur);
	DDX_Control(pDX, IDC_EDITCURROFF, m_editcurroff);
	DDX_Control(pDX, IDC_BUTWNDSIZE, m_butwndsize);
	DDX_Control(pDX, IDC_BUTSAVEASWAV, m_butsaveaswav);
	DDX_Control(pDX, IDC_BUTRESDUR, m_butresdur);
	DDX_Control(pDX, IDC_BUTLOADWAV, m_butloadwav);
	DDX_Control(pDX, IDC_BUTPLAYSEQ, m_butplayseq);
	DDX_Control(pDX, IDC_BUTPLAYOFF, m_butplayoff);
	DDX_Control(pDX, IDC_BUTNEWPROJ, m_butnewproj);
	DDX_Control(pDX, IDC_BUTLOADPROJ, m_butloadproj);
	DDX_Control(pDX, IDC_BUTGENSEQ, m_butgenseq);
	DDX_Control(pDX, IDC_BUTDISPLAY, m_butdisplay);
	DDX_Control(pDX, IDC_BUTCURROFF, m_butcurroff);
	DDX_Text(pDX, IDC_EDITWNDSIZE, m_editwndsizeval);
	DDV_MinMaxUInt(pDX, m_editwndsizeval, 1, 9999999);
	DDX_Text(pDX, IDC_EDITCURROFF, m_editcurroffval);
	DDV_MinMaxUInt(pDX, m_editcurroffval, 0, 9999999);
	DDX_Text(pDX, IDC_EDITOFFFREQ, m_editofffreqval);
	DDV_MinMaxUInt(pDX, m_editofffreqval, 0, 9999999);
	DDX_Text(pDX, IDC_EDITDUR, m_editdurval);
	DDV_MinMaxUInt(pDX, m_editdurval, 1, 96);
	DDX_Text(pDX, IDC_EDITRES, m_editresval);
	DDV_MinMaxUInt(pDX, m_editresval, 1, 128);
	DDX_Text(pDX, IDC_EDITSEQFREQ, m_editseqfreqval);
	DDV_MinMaxUInt(pDX, m_editseqfreqval, 0, 9999999);
	DDX_Check(pDX, IDC_CHEKSMOO, m_cheksmooval);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
//{{AFX_MSG_MAP(CMainDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTLOADWAV, OnButloadwav)
ON_BN_CLICKED(IDC_BUTPLAYOFF, OnButplayoff)
ON_BN_CLICKED(IDC_BUTWNDSIZE, OnButwndsize)
ON_BN_CLICKED(IDC_BUTDISPLAY, OnButdisplay)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_BUTCURROFF, OnButcurroff)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTRESDUR, OnButresdur)
ON_BN_CLICKED(IDC_BUTPLAYSEQ, OnButplayseq)
ON_BN_CLICKED(IDC_BUTNEWSEQ, OnButnewseq)
ON_BN_CLICKED(IDC_BUTGENSEQ, OnButgenseq)
	ON_BN_CLICKED(IDC_BUTSAVEASWAV, OnButsaveaswav)
	ON_BN_CLICKED(IDC_BUTSAVEPROJ, OnButsaveproj)
	ON_BN_CLICKED(IDC_BUTLOADPROJ, OnButloadproj)
	ON_BN_CLICKED(IDC_BUTNEWPROJ, OnButnewproj)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// ZEDS Initialisation
	InitOffset();
	InitWavData();
	InitSeqData();
	InitSeqGen();
	
	CRect r;
	GetClientRect(&r);
	
		m_statbackg.MoveWindow(4,4,r.right - 8, 23 + 4);
		m_butnewproj.MoveWindow(6,6,79,23);
		m_butloadproj.MoveWindow(80 + 6,6,79,23);
		m_butsaveproj.MoveWindow(160 + 6,6,79,23);
		m_butsaveaswav.MoveWindow(240 + 6,6,79,23);
		m_butgenseq.MoveWindow(432,6,107,23);
		
		m_butloadwav.MoveWindow(4,r.bottom - 79 - 23,79,23);
		m_butplayoff.MoveWindow(4 + 80,r.bottom - 79 - 23,71,23);
		m_butdisplay.MoveWindow(4 + 152,r.bottom - 79 - 23,55,23);
		m_statofffreq.MoveWindow(4 + 208,r.bottom - 79 - 23 - 4,71,23);
		m_editofffreq.MoveWindow(4 + 280,r.bottom - 79 - 23,51,19);
		m_statcurroff.MoveWindow(4 + 332,r.bottom - 79 - 23 - 4,71,23);
		m_editcurroff.MoveWindow(4 + 410 - 8,r.bottom - 79 - 23,63,19);
		m_butcurroff.MoveWindow(4 + 410 + 64 - 8,r.bottom - 79 - 23,15,15);
		m_statwndsize.MoveWindow(4 + 384 + 96 + 8 - 8,r.bottom - 79 - 23 - 4,71,23);
		m_editwndsize.MoveWindow(4 + 464 + 96 - 8,r.bottom - 79 - 23,63,19);
		m_butwndsize.MoveWindow(4 + 464 + 96 + 64 - 8,r.bottom - 79 - 23,15,15);
		
		m_statbackg2.MoveWindow(4,r.bottom - 23 - 6 - 32 - 12,r.right - 8,2);
		
		m_butnewseq.MoveWindow(6,r.bottom - 23 - 6,39,23);
		m_butplayseq.MoveWindow(6 + 44,r.bottom - 23 - 6,79,23);
		m_statseqfreq.MoveWindow(6 + 160,r.bottom - 23 - 6 - 4,79,23);
		m_editseqfreq.MoveWindow(6 + 240,r.bottom - 23 - 6,51,19);
		m_statresdur.MoveWindow(6 + 320 - 20,r.bottom - 23 - 6 - 4,99,23);
		m_editres.MoveWindow(6 + 400,r.bottom - 23 - 6,27,19);
		m_editdur.MoveWindow(6 + 428,r.bottom - 23 - 6,27,19);
		m_butresdur.MoveWindow(6 + 456,r.bottom - 23 - 6,15,15);
		m_cheksmoo.MoveWindow(6 + 456 + 15,r.bottom - 23 - 6,79,23);

		HRESULT hr;
		
		hr = DirectSoundCreate(NULL, &lpdirsnd, NULL);
		if (hr != DS_OK)	{
			MessageBox("Cannot create DSound object","ERROR",MB_ICONEXCLAMATION | MB_OK);
			exit(-1);
		}
		
		hr = lpdirsnd->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
		if (hr != DS_OK){
			MessageBox("Cannot init DSound object","ERROR",MB_ICONEXCLAMATION | MB_OK);
			exit(-1);
		}
		
		UINT i;
		LPVOID			write1, write2;
		DWORD				length1, length2;
		
		wavefmtex.wFormatTag = WAVE_FORMAT_PCM;
		wavefmtex.nChannels = 1;
		wavefmtex.nSamplesPerSec = 44100;
		wavefmtex.nAvgBytesPerSec = 88200;
		wavefmtex.nBlockAlign = 2;
		wavefmtex.wBitsPerSample = 16;
		wavefmtex.cbSize = 24932;
		
		dsbuffdesc.dwSize = 20;
		dsbuffdesc.dwFlags =DSBCAPS_CTRLFREQUENCY
			| DSBCAPS_GETCURRENTPOSITION2
			| DSBCAPS_STATIC
			| DSBCAPS_CTRLPAN;
		dsbuffdesc.dwBufferBytes = 32;
		dsbuffdesc.dwReserved = 0;
		dsbuffdesc.lpwfxFormat = &wavefmtex;
		
		Wave.SamplesPerSec = wavefmtex.nSamplesPerSec;
		Wave.TotalNumSamples = UIRoundD((double)dsbuffdesc.dwBufferBytes / 2.0);
		Wave.WindowSize = 1;
		
		BYTE* psampletmp;
		
		psampletmp = new BYTE[32];
		if (psampletmp == NULL)
		{
			exit(-1);
		}
		
		for(i = 0; i < 32; i++)
			psampletmp[i] = 0;
		
		hr = lpdirsnd->CreateSoundBuffer(&dsbuffdesc, &lpdsbuff, NULL);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		//fill buffer
		hr = lpdsbuff->Lock(0, 32, &write1, &length1,	&write2, &length2, 0);
		if (hr == DSERR_BUFFERLOST)
		{
			lpdsbuff->Restore();
			hr = lpdsbuff->Lock(0, 32, &write1, &length1, &write2, &length2, 0);
		}
		if (hr != DS_OK)
		{
			exit(-1);
		}
		
		CopyMemory(write1, psampletmp, length1);
		
		if (write2 != NULL)
		{
			CopyMemory(write2, psampletmp + length1, length2);
		}
		
		hr = lpdsbuff->Unlock(write1, length1, write2, length2);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		
		delete psampletmp;
		
		free(Wave.PSample);
		Wave.PSample = (double*)malloc(16 * sizeof(double));
		if (Wave.PSample == NULL)
		{
			exit(-1);
		}
		
		for(i = 0; i < 16; i++)
			Wave.PSample[i] = 0;
		
		hr = lpdsbuff->SetPan(0);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		
		TimerFlag = 0;
		offwnd = new OffsetWnd(&TimerFlag);
		offwnd->Create(NULL,
			"Offset Window",
			WS_VISIBLE | WS_BORDER,
			CRect(r.left,r.top + 34,r.right,r.bottom - 79 - 28),
			this,
			101);	
		
		seqwnd = new SequenceWnd();
		seqwnd->Create(NULL,
			"Sequence Window",
			WS_VISIBLE | WS_BORDER,
			CRect(r.left,r.bottom - 23 - 6 - 36 ,r.right ,r.bottom - 23 - 6 - 6),
			this,
			101);	
		
		SetDefID(IDC_STATBACKG);
		
		m_spinofffreq.SetBuddy(&m_editofffreq);
		m_spinofffreq.SetPos(1);
		m_spinofffreq.SetRange(1,1);
		
		m_spinseqfreq.SetBuddy(&m_editseqfreq);
		m_spinseqfreq.SetPos(1);
		m_spinseqfreq.SetRange(1,1);

		CString cstr("NO-FILE-LOADED");
		WAVFilename = new CHAR[cstr.GetLength()+1];
		WAVFileLength = cstr.GetLength()+1;
		strcpy(WAVFilename, cstr);

		CStartup dlg(this);
		dlg.DoModal();
		return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMainDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_statbackg.m_hWnd != NULL){
		offwnd->MoveWindow(0,34,cx,cy - 79 - 62);
		seqwnd->MoveWindow(0,cy - 23 - 6 - 37 ,cx,32);
		
		m_statbackg.MoveWindow(4,4,cx - 8, 23 + 4);
		m_butnewproj.MoveWindow(6,6,79,23);
		m_butloadproj.MoveWindow(80 + 6,6,79,23);
		m_butsaveproj.MoveWindow(160 + 6,6,79,23);
		m_butsaveaswav.MoveWindow(240 + 6,6,79,23);
		m_butgenseq.MoveWindow(432,6,107,23);
		
		m_butloadwav.MoveWindow(4,cy - 79 - 23,79,23);
		m_butplayoff.MoveWindow(4 + 80,cy - 79 - 23,71,23);
		m_butdisplay.MoveWindow(4 + 152,cy - 79 - 23,55,23);
		m_statofffreq.MoveWindow(4 + 208,cy - 79 - 23 - 4,71,23);
		m_editofffreq.MoveWindow(4 + 280,cy - 79 - 23,51,19);
		m_statcurroff.MoveWindow(4 + 332,cy - 79 - 23 - 4,71,23);
		m_editcurroff.MoveWindow(4 + 410 - 8,cy - 79 - 23,63,19);
		m_butcurroff.MoveWindow(4 + 410 + 64 - 8,cy - 79 - 23,15,15);
		m_statwndsize.MoveWindow(4 + 384 + 96 + 8 - 8,cy - 79 - 23 - 4,71,23);
		m_editwndsize.MoveWindow(4 + 464 + 96 - 8,cy - 79 - 23,63,19);
		m_butwndsize.MoveWindow(4 + 464 + 96 + 64 - 8,cy - 79 - 23,15,15);
		
		m_statbackg2.MoveWindow(4,cy - 23 - 6 - 32 - 12,cx - 8,2);
		
		m_butnewseq.MoveWindow(6,cy - 23 - 6,39,23);
		m_butplayseq.MoveWindow(6 + 44,cy - 23 - 6,79,23);
		m_statseqfreq.MoveWindow(6 + 160,cy - 23 - 6 - 4,79,23);
		m_editseqfreq.MoveWindow(6 + 240,cy - 23 - 6,51,19);
		m_statresdur.MoveWindow(6 + 320 - 20,cy - 23 - 6 - 4,99,23);
		m_editres.MoveWindow(6 + 400,cy - 23 - 6,27,19);
		m_editdur.MoveWindow(6 + 428,cy - 23 - 6,27,19);
		m_butresdur.MoveWindow(6 + 456,cy - 23 - 6,15,15);
		m_cheksmoo.MoveWindow(6 + 456 + 15,cy - 23 - 6,79,23);

		m_spinofffreq.SetBuddy(&m_editofffreq);		
		m_spinseqfreq.SetBuddy(&m_editseqfreq);
		
		UpdateData(TRUE);
		m_spinofffreq.SetPos(m_editofffreqval);
		m_spinofffreq.SetRange(UIRoundD(((double)(100 * 4) / (double)Wave.TotalNumSamples) * 60.0)
			,UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0));
			
		m_spinseqfreq.SetPos(m_editseqfreqval);
		m_spinseqfreq.SetRange(UIRoundD(((double)(100 * 4) / (double)Wave.TotalNumSamples) * 60.0)
			,UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0));
	}
}

BOOL CMainDlg::LoadWAV(LPSTR filename)
{
	HRESULT			hr;
	char* psampletmp;
	LPVOID			write1, write2;
	DWORD				length1, length2;
	HMMIO 			hmmio;
	UINT				i;
	MMCKINFO		parent, child;
	
	parent.ckid 				= (FOURCC)0;
	parent.cksize 			= 0;
	parent.fccType			= (FOURCC)0;
	parent.dwDataOffset = 0;
	parent.dwFlags			= 0;
		
	child = parent;
		
	hmmio = mmioOpen(filename, NULL, MMIO_READ | MMIO_ALLOCBUF);
	if (hmmio == NULL)
	{
		MessageBox("Cannot open file","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);//can't open file
	}
	
	/* descend into the RIFF */
	parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(hmmio, &parent, NULL, MMIO_FINDRIFF))
	{
		mmioClose(hmmio, 0);
		MessageBox("Not a WAV file","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	
	/* descend to the WAVEfmt */
	child.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmio, &child, &parent, 0))
	{
		mmioClose(hmmio, 0);
		MessageBox("Not a WAV file","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	
	/* read the WAVEFMT from the wave file */
	if (mmioRead(hmmio, (char*)&wavefmtex, sizeof(wavefmtex)) != sizeof(wavefmtex))
	{
		mmioClose(hmmio, 0);
		MessageBox("Cannot read file","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	
	/* We only handle PCM format WAVEs */
	if ((wavefmtex.wFormatTag != WAVE_FORMAT_PCM)
		| (wavefmtex.nChannels != 1)
		| (wavefmtex.wBitsPerSample != 16)
		)
	{
		MessageBox("Not 16 bit mono\nWAV format","ERROR",MB_ICONEXCLAMATION | MB_OK);
		mmioClose(hmmio, 0);
		return(FALSE); 	//WAVE file is not PCM format
	}
	if (mmioAscend(hmmio, &child, 0))
	{
		mmioClose(hmmio, 0);
		MessageBox("Corrupt File","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);	//unable to ascend
	}
		
		/* descend to the data chunk */
	child.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmio, &child, &parent, MMIO_FINDCHUNK))
	{
		mmioClose(hmmio, 0);
		MessageBox("Corrupt File","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	
	psampletmp = new char[child.cksize];
	if (psampletmp == NULL)
	{
		mmioClose(hmmio, 0);
		MessageBox("Cannot allocate Memory","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
		
	/* read the wave data */
	if ((DWORD)mmioRead(hmmio, psampletmp, child.cksize) != child.cksize)
	{
		mmioClose(hmmio, 0);
		MessageBox("Cannot read data","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
		
	mmioClose(hmmio, 0);
	
	//create buffer
	dsbuffdesc.dwSize				= sizeof(DSBUFFERDESC);
	dsbuffdesc.dwFlags 			= DSBCAPS_CTRLFREQUENCY
		| DSBCAPS_GETCURRENTPOSITION2
		| DSBCAPS_STATIC
		| DSBCAPS_CTRLPAN;
	dsbuffdesc.dwBufferBytes = child.cksize;
	dsbuffdesc.lpwfxFormat 	= &wavefmtex;
	
	Wave.SamplesPerSec = wavefmtex.nSamplesPerSec;
	Wave.TotalNumSamples = (unsigned int)(dsbuffdesc.dwBufferBytes / 2.0);
	Wave.WindowSize = 1;
	
	hr = lpdirsnd->CreateSoundBuffer(&dsbuffdesc, &lpdsbuff, NULL);
	if (hr != DS_OK)
	{
		MessageBox("Cannot create sound buffer","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	//fill buffer
	hr = lpdsbuff->Lock(0, child.cksize, &write1, &length1,	&write2, &length2, 0);
	if (hr == DSERR_BUFFERLOST)
	{
		lpdsbuff->Restore();
		hr = lpdsbuff->Lock(0, child.cksize, &write1, &length1, &write2, &length2, 0);
	}
	if (hr != DS_OK)
	{
		MessageBox("Cannot Lock sound buffer","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	
	CopyMemory(write1, psampletmp, length1);
	
	if (write2 != NULL)
	{
		CopyMemory(write2, psampletmp + length1, length2);
	}
	
	hr = lpdsbuff->Unlock(write1, length1, write2, length2);
	if (hr != DS_OK)
	{
		MessageBox("Cannot unlock sound buffer","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	
	//	for(i = 0; i < child.cksize / 2; i++){
	//		psample[i] =
	//			0.5 - ((double)((((psampletmp[(2 * i) + 1] << 8) | psampletmp[2 * i]) + 32768) % 65536) / 65536.0);
	//	}
	free(Wave.PSample);
	Wave.PSample = (double*)malloc(Wave.TotalNumSamples * sizeof(double));
	
	for(i = 0; i < Wave.TotalNumSamples; i++){
		Wave.PSample[i] =
			(_int16)(
			(0xff00 & ((unsigned _int16)psampletmp[(2 * i) + 1] << 8))
			|
			(0x00ff & ((unsigned _int16)psampletmp[2 * i]))
			) / 32786.0;
	}
	//	curroffset = 0;
	//	delete psampletmp;
	
	hr = lpdsbuff->SetPan(0);
	if (hr != DS_OK)
	{
		MessageBox("sound buffer error","ERROR",MB_ICONEXCLAMATION | MB_OK);
		return(FALSE);
	}
	
	delete [] psampletmp;
	return(TRUE);
}

void CMainDlg::OnButloadwav() 
{
	const char fileDialogFilter[] =
				"WAV files (*.wav)|*.wav||";
	const char fileDialogExt[] = "wav";
	
	CFileDialog fileDialog( TRUE, 
		fileDialogExt, NULL,
		OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON |OFN_HIDEREADONLY 
		, fileDialogFilter );
	if( fileDialog.DoModal() == IDOK )
	{ 
		CString cstr(fileDialog.GetPathName());
	//	LPSTR lpstr = new CHAR[cstr.GetLength()+1];
	//	strcpy(lpstr, cstr);
		delete [] WAVFilename;
		WAVFilename = new CHAR[cstr.GetLength()+1];
		strcpy(WAVFilename, cstr);
		WAVFileLength = cstr.GetLength()+1;		
		//	snd = new SoundFile(m_hWnd);
		
		if(LoadWAV(WAVFilename) == TRUE){
			SetupOffsets();
			
			Wave.WindowSize = UIRoundD((double)Wave.TotalNumSamples / 512.0);
			if(Wave.WindowSize <= 0)
				Wave.WindowSize = 1;
			
			m_editwndsizeval = Wave.WindowSize;
			
			m_editofffreqval = UIRoundD(((double)(44100 * 4) / (double)Wave.TotalNumSamples) * 60.0);
			m_spinofffreq.SetPos(m_editofffreqval);
			m_spinofffreq.SetRange(UIRoundD(((double)(100 * 4) / (double)Wave.TotalNumSamples) * 60.0)
				,UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0));
			
			m_editseqfreqval = UIRoundD(((double)(44100 * 4) / (double)Wave.TotalNumSamples) * 60.0);
			m_spinseqfreq.SetPos(m_editseqfreqval);
			m_spinseqfreq.SetRange(UIRoundD(((double)(100 * 4) / (double)Wave.TotalNumSamples) * 60.0)
				,UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0));
			
			UpdateData(FALSE);
			
			MakeEnvelope();
			
			
			offwnd->UpdateDisplay();
			offwnd->DrawOffsets();
			
			offwnd->displaystate = TRUE;
			offwnd->DrawEnvelope();
			
			offwnd->DrawCurrOffset();
			SetWindowText(CString("Zs-1b Amen 1998  ") + CString(WAVFilename));
		}
	//	delete [] lpstr;
		
	}
}

void CMainDlg::OnButplayoff() 
{
	HRESULT hr;
	UpdateData(TRUE);
	
	UINT freq;
	
	freq = UIRoundD((((double)m_editofffreqval / 60.0)
		* (double)Wave.TotalNumSamples) / 4.0);
	
	if(freq < 100){
		m_editofffreqval = UIRoundD(((double)(101 * 4) / (double)Wave.TotalNumSamples) * 60.0);
		freq = 100;	
		UpdateData(FALSE);
		}
	if(freq > 100000){
		m_editofffreqval = UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0);
		freq = 100000;
		UpdateData(FALSE);
	}
	
	offwnd->UpdateDisplay();
		
		hr = lpdsbuff->SetCurrentPosition((ULONG)(Offset[CurrOffset] * 2.0));
		if (hr != DS_OK)
		{
			exit(-1);
		}
		hr = lpdsbuff->SetFrequency((DWORD)freq);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		hr = lpdsbuff->Play(0, 0,DSBPLAY_LOOPING);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		
		TimerFlag = 0;
		SetTimer(TID_OFFWND,1,NULL);
		//	CRect r;
		//	GetClientRect(&r);
		
		CButStop dlg(this);
		//	dlg.MoveWindow(4 + 80,r.bottom - 79 - 23,71,23);
		
		dlg.DoModal();
		
		KillTimer(TID_OFFWND);
		lpdsbuff->Stop();
		TimerFlag = 0;
		
		offwnd->UpdateDisplay();
		if(offwnd->displaystate == TRUE){
			offwnd->DrawEnvelope();
		}else{
			offwnd->DrawZero();
		}
		offwnd->DrawOffsets();
		
}
void CMainDlg::OnButwndsize() 
{
	UpdateData(TRUE);
	if(m_editwndsizeval >= Wave.TotalNumSamples){
		m_editwndsizeval = Wave.TotalNumSamples - 1;
		UpdateData(FALSE);		
	}
	Wave.WindowSize = m_editwndsizeval;
	MakeEnvelope();
	
	offwnd->UpdateDisplay();
	offwnd->DrawOffsets();
	
	offwnd->displaystate = TRUE;
	offwnd->DrawEnvelope();
}

void CMainDlg::OnButdisplay() 
{
	offwnd->UpdateDisplay();
	offwnd->DrawOffsets();
	
	if(offwnd->displaystate == TRUE){
		offwnd->displaystate = FALSE;
		offwnd->DrawZero();
	}else{
		offwnd->displaystate = TRUE;
		offwnd->DrawEnvelope();
	}
}

void CMainDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	delete [] WAVFilename;
	delete offwnd;
	delete seqwnd;
	
	CleanUp();
}

void CMainDlg::OnButcurroff() 
{
	UpdateData(TRUE);
	
	if(m_editcurroffval >= Wave.TotalNumSamples)
		m_editcurroffval = Wave.TotalNumSamples - 1;
	
	Offset[CurrOffset] = m_editcurroffval;	
	UpdateData(FALSE);
	
	offwnd->UpdateDisplay();
	offwnd->DrawOffsets();
	
	if(offwnd->displaystate == TRUE){
		offwnd->DrawEnvelope();
	}else{
		offwnd->DrawZero();
	}
}

void CMainDlg::OnTimer(UINT nIDEvent) 
{
	static UINT oldx = 0;
	static COLORREF col = RGB(255,255,255);
	
	if(nIDEvent == TID_SEQWND){
		static UINT pointoff = 0;
		static UINT oldcurroff = EMPTY_CELL_VAL;
		
		if(TimerFlag == 0){
			oldx = 0;
			TimerFlag = 3;
			oldcurroff = EMPTY_CELL_VAL;
			pointoff = 0;
		}
		if(TimerFlag >= 2){
			CRect cr;
			offwnd->GetClientRect(&cr);
			CDC* dc;
			dc = offwnd->GetDC();
			if(dc == NULL){
				exit(-1);
			}		
			dc->SetROP2(R2_XORPEN);
			
			CPen newpen1,newpen2;	
			UINT curroff;
			UINT actualpoint;
			DWORD playpos,writepos;
			
			lpdsbuffSeq->GetCurrentPosition(&playpos,&writepos);
			
			curroff = (UINT)floor(((double)Sequence.Resolution * (double)Sequence.Duration)
				* (((double)playpos / 2.0) / (double)Sequence.TotalNumSamples));
			curroff = (Sequence.PCell + curroff)->OffsetIndex;
			
			actualpoint = UIRoundD((double)playpos / 2.0) % Wave.TotalNumSamples;
			
			if(curroff != oldcurroff){
				if(TimerFlag != 3){
					if(newpen2.CreatePen(PS_SOLID,1,col))
					{				
						CPen* oldpen = dc->SelectObject(&newpen2);
						dc->MoveTo(oldx,0);
						dc->LineTo(oldx,cr.bottom);
						oldx = actualpoint;
						dc->SelectObject(oldpen);
					}
				}
				TimerFlag = 3;
				switch(curroff){
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
				case EMPTY_CELL_VAL:
					col = RGB(0,0,0);
					break;
				}				
				pointoff = actualpoint;
				oldcurroff = curroff;
			}
			
			if(((double)playpos / 2.0) < ((double)Wave.TotalNumSamples
				/ (double)Sequence.Resolution)){
				pointoff = 0;
			}
			
			if(curroff == EMPTY_CELL_VAL){
				actualpoint = 0;
			}else{
				actualpoint =  (UIRoundD((double)cr.right * 
					((double)(actualpoint - pointoff + Offset[curroff])
					/ (double)Wave.TotalNumSamples))) % cr.right;
			}
			
			if(newpen1.CreatePen(PS_SOLID,1,col))
			{				
				CPen* oldpen = dc->SelectObject(&newpen1);
				dc->MoveTo(actualpoint,0);
				dc->LineTo(actualpoint,cr.bottom);
				if(TimerFlag != 3){
					dc->MoveTo(oldx,0);
					dc->LineTo(oldx,cr.bottom);}
				TimerFlag = 2;
				oldx = actualpoint;
				dc->SelectObject(oldpen);
			}
			offwnd->ReleaseDC(dc);
		}
	}
	if(nIDEvent == TID_OFFWND){
		CRect cr;
		offwnd->GetClientRect(&cr);
		if(TimerFlag == 0){
			
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
			TimerFlag = 1;
		}
		CDC* dc;
		dc = offwnd->GetDC();
		if(dc == NULL){
			exit(-1);
		}
		
		CPen newpen1;
		
		dc->SetROP2(R2_XORPEN);	
		
		if(newpen1.CreatePen(PS_SOLID,1,col))
		{
			UINT point;
			DWORD playpos,writepos;
			
			lpdsbuff->GetCurrentPosition(&playpos,&writepos);
			point = UIRoundD(cr.right * (((double)playpos / 2.0) / (double)Wave.TotalNumSamples));
			
			CPen* oldpen = dc->SelectObject(&newpen1);
			dc->MoveTo(point,0);
			dc->LineTo(point,cr.bottom);
			dc->MoveTo(oldx,0);
			dc->LineTo(oldx,cr.bottom);
			oldx = point;
			dc->SelectObject(oldpen);
		}
		offwnd->ReleaseDC(dc);
	}
	CDialog::OnTimer(nIDEvent);
}

void CMainDlg::OnButresdur() 
{
	UpdateData(TRUE);
	if(m_editresval > 128)
		m_editresval = 128;
	if(m_editresval < 1)
		m_editresval = 1;
	if(m_editdurval > 96)
		m_editdurval = 96;
	if(m_editdurval < 1)
		m_editdurval = 1;
	UpdateData(FALSE);
	ResDurChange(m_editresval,m_editdurval);
	seqwnd->UpdateDisplay();
}

void CMainDlg::OnButplayseq() 
{
	UINT i;
	UpdateData(TRUE);
	
	CProgress Prg(this);
	Prg.Create(IDD_PROGRESS,this);
	
	Prg.SetDlgItemText(IDC_STATPROG,"Calculating Frequencies...");
	UINT freq;
	freq = UIRoundD((((double)m_editseqfreqval / 60.0)
		* (double)Wave.TotalNumSamples) / 4.0);
	
	if(freq < 100){
		m_editofffreqval = UIRoundD(((double)(101 * 4) / (double)Wave.TotalNumSamples) * 60.0);
		freq = 100;	
		UpdateData(FALSE);
	}	
	if(freq > 100000){
		m_editofffreqval = UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0);
		freq = 100000;
		UpdateData(FALSE);
	}
	
	Prg.SetDlgItemText(IDC_STATPROG,"Rendering Sequence...");
	RenderSequence();

	UpdateData(TRUE);
	if(m_cheksmooval){
		Prg.SetDlgItemText(IDC_STATPROG,"Smoothing Sequence...");
		SmoothSequence();
	}
	BYTE *pSampleSeq;
		
	Prg.SetDlgItemText(IDC_STATPROG,"Converting Data...");
	pSampleSeq = new BYTE[Sequence.TotalNumSamples * 2];		
	UINT idx; //For SPEED
	_int16 sval; //For SPEED
		
	for(i = 0; i < Sequence.TotalNumSamples; i++){
		idx = i * 2;
		sval = (_int16)(Sequence.PSample[i] * 32786.0);

		pSampleSeq[idx] =( unsigned _int8)(0x00ff & sval);
		pSampleSeq[++idx] = (unsigned _int8)(0x00ff & (sval >> 8));
	}
	
	Prg.SetDlgItemText(IDC_STATPROG,"Creating Buffer");
	HRESULT hr;		
	
	dsbuffdescSeq.dwSize = 20;
	dsbuffdescSeq.dwFlags =DSBCAPS_CTRLFREQUENCY
		| DSBCAPS_GETCURRENTPOSITION2
		| DSBCAPS_CTRLPAN;
	dsbuffdescSeq.dwBufferBytes = Sequence.TotalNumSamples * 2;
	dsbuffdescSeq.dwReserved = 0;
	dsbuffdescSeq.lpwfxFormat = &wavefmtex;
	
	hr = lpdirsnd->CreateSoundBuffer(&dsbuffdescSeq, &lpdsbuffSeq, NULL);
	if (hr != DS_OK)
	{
		exit(-1);
	}
	
	hr = lpdsbuffSeq->SetPan(0);
	if (hr != DS_OK)
	{
		exit(-1);
	}
		
	Prg.SetDlgItemText(IDC_STATPROG,"Filling Buffer...");
	LPVOID			write1, write2;
	DWORD				length1, length2;
		
	hr = lpdsbuffSeq->Lock(0, dsbuffdescSeq.dwBufferBytes , &write1, &length1,	&write2, &length2, 0);
	if (hr == DSERR_BUFFERLOST)
	{
		lpdsbuffSeq->Restore();
		hr = lpdsbuffSeq->Lock(0, dsbuffdescSeq.dwBufferBytes , &write1, &length1, &write2, &length2, 0);
	}
	if (hr != DS_OK)
	{
		exit(-1);
	}
		
	CopyMemory(write1, pSampleSeq, length1);
	
	if (write2 != NULL)
	{
		CopyMemory(write2, pSampleSeq + length1, length2);
	}
		
	hr = lpdsbuffSeq->Unlock(write1, length1, write2, length2);
	if (hr != DS_OK)
	{
		exit(-1);
	}

	hr = lpdsbuffSeq->SetCurrentPosition(0);
	if (hr != DS_OK)
	{
		exit(-1);
	}
	hr = lpdsbuffSeq->SetFrequency((DWORD)freq);
	if (hr != DS_OK)
	{
		exit(-1);
	}

	Prg.SetDlgItemText(IDC_STATPROG,"Finished!");
	Prg.DestroyWindow();
		
		
		offwnd->UpdateDisplay();
		TimerFlag = 0;		
		
		hr = lpdsbuffSeq->Play(0, 0,DSBPLAY_LOOPING);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		SetTimer(TID_SEQWND,1,NULL);
		
		CButStop2 dlg(this);
		dlg.DoModal();
		
		KillTimer(TID_SEQWND);
		TimerFlag = 0;
		lpdsbuffSeq->Stop();
		
		offwnd->UpdateDisplay();
		if(offwnd->displaystate == TRUE){
			offwnd->DrawEnvelope();
		}else{
			offwnd->DrawZero();
		}
		offwnd->DrawOffsets();
		
	delete [] pSampleSeq;		
}


void CMainDlg::OnButnewseq() 
{
	if(MessageBox("WARNING:\nThis will delete the existing sequence data.","New Sequence",MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK){
		m_editdurval = DEF_SEQ_DURATION;
		m_editresval = DEF_SEQ_RESOLUTION;
		free(Sequence.PSample);
		free(Sequence.PCell);
		InitSeqData();
		UpdateData(FALSE);
		seqwnd->UpdateDisplay();
	}
}

void CMainDlg::OnButgenseq() 
{
	if(MessageBox("WARNING:\nThis will reset offset positions!","WARNING",MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK){
		CSequenceGenerator seqgen(this);

		SetupOffsets();
		offwnd->UpdateDisplay();
		offwnd->DrawOffsets();
		if(offwnd->displaystate == TRUE){
			offwnd->DrawEnvelope();
		}else{
			offwnd->DrawZero();
		}
		offwnd->DrawCurrOffset();

		while(seqgen.DoModal() == IDOK){
			m_editdurval = Sequence.Duration;
			m_editresval = Sequence.Resolution;
			UpdateData(FALSE);

			ResDurChange(m_editresval,m_editdurval);
			
			GenerateSequence();
	
			seqwnd->UpdateDisplay();
			OnButplayseq();
				
//			}while(MessageBox("Retry Generation?"
//				,"Sequence Generator",MB_ICONQUESTION | MB_YESNO) == IDYES);
		}
	}
}

void CMainDlg::OnButsaveaswav() 
{
	HMMIO 			hmmio;
	UINT				i;
	MMCKINFO		parent, child;
	
	parent.ckid 				= (FOURCC)0;
	parent.cksize 			= 0;
	parent.fccType			= (FOURCC)0;
	parent.dwDataOffset = 0;
	parent.dwFlags			= 0;
		
	child = parent;
	
	const char fileDialogFilter[] =
				"WAV files (*.wav)|*.wav||";
	const char fileDialogExt[] = "wav";
	
	CFileDialog fileDialog( FALSE, 
		fileDialogExt, NULL,
		OFN_OVERWRITEPROMPT  | OFN_NONETWORKBUTTON | OFN_HIDEREADONLY 
		, fileDialogFilter );
	if( fileDialog.DoModal() == IDOK )
	{ 
		CProgress Prg(this);
		Prg.Create(IDD_PROGRESS,this);
		
		Prg.SetDlgItemText(IDC_STATPROG,"Rendering Sequence...");
		RenderSequence();

		UpdateData(TRUE);
		if(m_cheksmooval){
			Prg.SetDlgItemText(IDC_STATPROG,"Smoothing Sequence...");
			SmoothSequence();
		}
		
		Prg.SetDlgItemText(IDC_STATPROG,"Opening File...");
		CString cstr(fileDialog.GetPathName());
		LPSTR lpstr = new CHAR[cstr.GetLength()+1];
		strcpy(lpstr, cstr);
		
		hmmio = mmioOpen(lpstr, NULL, MMIO_WRITE | MMIO_CREATE | MMIO_ALLOCBUF);
		if (hmmio == NULL)
		{
			exit(-1); //can't open file
		}
		delete lpstr;
		parent.fccType = mmioFOURCC('W', 'A', 'V', 'E'); 
		mmioCreateChunk(hmmio, &parent, MMIO_CREATERIFF);  
		

		
		/* descend to the WAVEfmt */
		child.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioCreateChunk(hmmio, &child, NULL);  
		
		if (mmioWrite(hmmio, (char*)&wavefmtex, sizeof(wavefmtex)) != sizeof(wavefmtex))
		{
			mmioClose(hmmio, 0);
			exit(-1); 	//unable to write chunk
		}
		
		if (mmioAscend(hmmio, &child, 0))
		{
			mmioClose(hmmio, 0);
			exit(-1); 	//unable to ascend
		}
		
		/* descend to the data chunk */
		child.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioCreateChunk(hmmio, &child, NULL);  

		Prg.SetDlgItemText(IDC_STATPROG,"Converting Data...");
		BYTE* samples;
		samples = new BYTE[Sequence.TotalNumSamples * 2];		
		UINT idx; //For SPEED
		_int16 sval; //For SPEED
		
		for(i = 0; i < Sequence.TotalNumSamples; i++){
			idx = i * 2;
			sval = (_int16)(Sequence.PSample[i] * 32786.0);

			samples[idx] =( unsigned _int8)(0x00ff & sval);
			samples[++idx] = (unsigned _int8)(0x00ff & (sval >> 8));
	}
							
		Prg.SetDlgItemText(IDC_STATPROG,"Writing Data...");		
		if ((DWORD)mmioWrite(hmmio, (char *)samples, Sequence.TotalNumSamples * 2) != (Sequence.TotalNumSamples * 2))
		{
			mmioClose(hmmio, 0);
			exit(-1); 	
		}
		delete [] samples;
		if (mmioAscend(hmmio, &child, 0))
		{
			mmioClose(hmmio, 0);
			exit(-1); 
		}
		if (mmioAscend(hmmio, &parent, 0))
		{
			mmioClose(hmmio, 0);
			exit(-1); 	//unable to ascend
		}
		mmioClose(hmmio, 0);
		
		Prg.SetDlgItemText(IDC_STATPROG,"Finished!");
		Prg.DestroyWindow();
	}	
}


void CMainDlg::OnButsaveproj() 
{
	const char fileDialogFilter[] =
				"Amen files (*.amn)|*.amn||";
	const char fileDialogExt[] = "amn";
	
	CFileDialog fileDialog( FALSE, 
		fileDialogExt, NULL,
		OFN_OVERWRITEPROMPT  | OFN_NONETWORKBUTTON | OFN_HIDEREADONLY 
		, fileDialogFilter );

	if( fileDialog.DoModal() == IDOK )
	{
		CFile f;
		CFileException exception;
		CProgress Prg(this);
		Prg.Create(IDD_PROGRESS,this);
		
		Prg.SetDlgItemText(IDC_STATPROG,"Saving Data...");
		if(!(f.Open(fileDialog.GetPathName(),
			CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive,
			&exception))){
			char s[100];
			sprintf(s,"Error opening file %d",exception.m_cause);
			MessageBox(s,"Error",MB_OK);
			return;
		}else{
			UpdateData(TRUE);
			try
			{
				f.Write(Offset,NUM_OFFSETS * sizeof(unsigned int));
				f.Write(&CurrOffset, sizeof(unsigned int));
				f.Write(&Wave.TotalNumSamples, sizeof(unsigned int));
				f.Write(&m_editwndsize, sizeof(UINT));
				f.Write(&m_editseqfreqval, sizeof(UINT));
				f.Write(&Sequence, sizeof(SequenceBuffer));
				f.Write(Sequence.PCell,Sequence.Resolution
					* Sequence.Duration
					* sizeof(SequenceCell));
				f.Write(&WAVFileLength, sizeof(UINT));
				f.Write(WAVFilename, WAVFileLength * sizeof(CHAR));
			}
			catch(CFileException exception)
			{
				MessageBox("Error writing file","Error",MB_OK);
			}
			f.Close();
		}
		Prg.SetDlgItemText(IDC_STATPROG,"Finished!");
		Prg.DestroyWindow();
	}
}

void CMainDlg::OnButloadproj() 
{
		const char fileDialogFilter[] =
				"Amen files (*.amn)|*.amn||";
	const char fileDialogExt[] = "amn";
	
	CFileDialog fileDialog( TRUE, 
		fileDialogExt, NULL,
		OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON |OFN_HIDEREADONLY 
		, fileDialogFilter );	
	
	if( fileDialog.DoModal() == IDOK )
	{
		CFile f;
		CFileException exception;
		unsigned int OffsetTmp[NUM_OFFSETS];
		unsigned int Length;
		unsigned int SeqFreq;

		if(!(f.Open(fileDialog.GetPathName(),
			CFile::modeRead,	&exception))){
			char s[100];
			sprintf(s,"Error opening file %d",exception.m_cause);
			MessageBox(s,"Error",MB_OK);
			return;
		}else{
			try
			{
				f.Read(OffsetTmp,NUM_OFFSETS * sizeof(unsigned int));
				f.Read(&CurrOffset, sizeof(unsigned int));
				f.Read(&Length, sizeof(unsigned int));
				f.Read(&m_editwndsize, sizeof(UINT));
				f.Read(&SeqFreq, sizeof(UINT));
				free(Sequence.PCell);
				free(Sequence.PSample);
				f.Read(&Sequence, sizeof(SequenceBuffer));				
				Sequence.PCell = (SequenceCell*)malloc(
					Sequence.Resolution
					* Sequence.Duration
					* sizeof(SequenceCell));
				Sequence.PSample = (double*)malloc(
					Sequence.TotalNumSamples
					* sizeof(double));
				f.Read(Sequence.PCell,
					Sequence.Resolution
					* Sequence.Duration
					* sizeof(SequenceCell));
				f.Read(&WAVFileLength, sizeof(UINT));
				delete [] WAVFilename;
				WAVFilename = new CHAR[WAVFileLength];
				f.Read(WAVFilename, WAVFileLength * sizeof(CHAR));
			}
			catch(CFileException exception)
			{
				MessageBox("Error reading file","Error",MB_OK);
			}
			f.Close();
		}
		UINT i;
		if(LoadWAV(WAVFilename) == FALSE){
			char s[100];
			sprintf(s,"Please select a new WAV\n or Locate\n %s",WAVFilename);
			MessageBox(s,"Error",MB_ICONEXCLAMATION | MB_OK);
			OnButloadwav();
			
			for(i = 0; i < NUM_OFFSETS;i++){
				Offset[i] =  UIRoundD((double)Wave.TotalNumSamples * 
					((double)OffsetTmp[i] / (double)Length));
			}
		}else{
			
			for(i = 0; i < NUM_OFFSETS;i++){
				Offset[i] = OffsetTmp[i];
			}
		}
		SetWindowText(CString("Zs-1b Amen 1998  ") + CString(WAVFilename));
		m_editcurroffval = CurrOffset;
		m_editdurval = Sequence.Duration;
		m_editresval = Sequence.Resolution;
		m_editwndsizeval;
		m_editseqfreqval = SeqFreq;

		m_editofffreqval = UIRoundD(((double)(44100 * 4) / (double)Wave.TotalNumSamples) * 60.0);
		m_spinofffreq.SetPos(m_editofffreqval);
		m_spinofffreq.SetRange(UIRoundD(((double)(100 * 4) / (double)Wave.TotalNumSamples) * 60.0)
			,UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0));
			
		m_spinseqfreq.SetPos(m_editseqfreqval);
		m_spinseqfreq.SetRange(UIRoundD(((double)(100 * 4) / (double)Wave.TotalNumSamples) * 60.0)
			,UIRoundD(((double)(100000 * 4) / (double)Wave.TotalNumSamples) * 60.0));
		
		UpdateData(FALSE);
		MakeEnvelope();

		offwnd->UpdateDisplay();
		offwnd->DrawOffsets();
			
		offwnd->displaystate = TRUE;
		offwnd->DrawEnvelope();
			
		offwnd->DrawCurrOffset();

		seqwnd->UpdateDisplay();
	}
}

void CMainDlg::OnButnewproj() 
{
	if(MessageBox("WARNING:\nThis will delete all project information!"
		,"WARNING",MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK){
		CleanUp();
		InitOffset();
		InitWavData();
		InitSeqData();
		InitSeqGen();
		
		HRESULT hr;
		
		UINT i;
		LPVOID			write1, write2;
		DWORD				length1, length2;
		
		dsbuffdesc.dwSize = 20;
		dsbuffdesc.dwFlags =DSBCAPS_CTRLFREQUENCY
			| DSBCAPS_GETCURRENTPOSITION2
			| DSBCAPS_STATIC
			| DSBCAPS_CTRLPAN;
		dsbuffdesc.dwBufferBytes = 32;
		dsbuffdesc.dwReserved = 0;
		dsbuffdesc.lpwfxFormat = &wavefmtex;
		
		Wave.SamplesPerSec = wavefmtex.nSamplesPerSec;
		Wave.TotalNumSamples = UIRoundD((double)dsbuffdesc.dwBufferBytes / 2.0);
		Wave.WindowSize = 1;
		
		BYTE* psampletmp;
		
		psampletmp = new BYTE[32];
		if (psampletmp == NULL)
		{
			exit(-1);
		}
		
		for(i = 0; i < 32; i++)
			psampletmp[i] = 0;
		
		hr = lpdirsnd->CreateSoundBuffer(&dsbuffdesc, &lpdsbuff, NULL);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		//fill buffer
		hr = lpdsbuff->Lock(0, 32, &write1, &length1,	&write2, &length2, 0);
		if (hr == DSERR_BUFFERLOST)
		{
			lpdsbuff->Restore();
			hr = lpdsbuff->Lock(0, 32, &write1, &length1, &write2, &length2, 0);
		}
		if (hr != DS_OK)
		{
			exit(-1);
		}
		
		CopyMemory(write1, psampletmp, length1);
		
		if (write2 != NULL)
		{
			CopyMemory(write2, psampletmp + length1, length2);
		}
		
		hr = lpdsbuff->Unlock(write1, length1, write2, length2);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		
		delete psampletmp;
		
		free(Wave.PSample);
		Wave.PSample = (double*)malloc(16 * sizeof(double));
		if (Wave.PSample == NULL)
		{
			exit(-1);
		}
		
		for(i = 0; i < 16; i++)
			Wave.PSample[i] = 0;
		
		hr = lpdsbuff->SetPan(0);
		if (hr != DS_OK)
		{
			exit(-1);
		}
		
		TimerFlag = 0;
		
		m_spinofffreq.SetBuddy(&m_editofffreq);
		m_spinofffreq.SetPos(1);
		m_spinofffreq.SetRange(1,1);
				
		m_spinseqfreq.SetBuddy(&m_editseqfreq);
		m_spinseqfreq.SetPos(1);
		m_spinseqfreq.SetRange(1,1);
		
		MakeEnvelope();
		
		offwnd->UpdateDisplay();
		offwnd->DrawOffsets();
		
		offwnd->displaystate = TRUE;
		offwnd->DrawEnvelope();
		
		
		seqwnd->UpdateDisplay();
		m_editcurroffval = CurrOffset;
		m_editdurval = Sequence.Duration;
		m_editresval = Sequence.Resolution;
		UpdateData(FALSE);
		SetWindowText(CString("Zs-1b Amen 1998  "));
	}
}
