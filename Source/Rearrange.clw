; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=SequenceWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Rearrange.h"

ClassCount=10
Class1=CRearrangeApp
Class2=CMainDlg
Class3=CAboutDlg

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_REARRANGE_DIALOG
Resource4=IDD_SEQGEN
Resource5=IDD_DIALOGSTOP
Class4=CButStop
Class5=OffsetWnd
Class6=SequenceWnd
Resource6=IDD_PROGRESS
Class7=CButStop2
Resource7=IDD_ABOUTBOX (English (U.S.))
Class8=CSequenceGenerator
Resource8=IDD_REARRANGE_DIALOG (English (U.S.))
Class9=CProgress
Resource9=IDD_DIALOGSTOP2
Class10=CStartup
Resource10=IDD_DIALOGSTARTUP

[CLS:CRearrangeApp]
Type=0
HeaderFile=Rearrange.h
ImplementationFile=Rearrange.cpp
Filter=N
LastObject=CRearrangeApp

[CLS:CMainDlg]
Type=0
HeaderFile=MainDlg.h
ImplementationFile=MainDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDITOFFFREQ

[CLS:CAboutDlg]
Type=0
HeaderFile=MainDlg.h
ImplementationFile=MainDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_REARRANGE_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CMainDlg

[DLG:IDD_REARRANGE_DIALOG (English (U.S.))]
Type=1
Class=CMainDlg
ControlCount=29
Control1=IDC_BUTLOADWAV,button,1342242816
Control2=IDC_BUTPLAYOFF,button,1342242816
Control3=IDC_BUTDISPLAY,button,1342242816
Control4=IDC_STATSEQFREQ,static,1342308866
Control5=IDC_EDITOFFFREQ,edit,1350639744
Control6=IDC_SPINOFFFREQ,msctls_updown32,1342177447
Control7=IDC_STATCURROFF,static,1342308866
Control8=IDC_EDITCURROFF,edit,1350639744
Control9=IDC_BUTCURROFF,button,1342242816
Control10=IDC_STATWNDSIZE,static,1342308866
Control11=IDC_EDITWNDSIZE,edit,1350639744
Control12=IDC_BUTWNDSIZE,button,1342242816
Control13=IDC_BUTGENSEQ,button,1342242816
Control14=IDC_STATBACKG2,static,1342177285
Control15=IDC_BUTNEWSEQ,button,1342242816
Control16=IDC_BUTPLAYSEQ,button,1342242816
Control17=IDC_STATOFFFREQ,static,1342308866
Control18=IDC_EDITSEQFREQ,edit,1350639744
Control19=IDC_SPINSEQFREQ,msctls_updown32,1342177447
Control20=IDC_STATRESDUR,static,1342308866
Control21=IDC_EDITRES,edit,1350639744
Control22=IDC_EDITDUR,edit,1350639744
Control23=IDC_BUTRESDUR,button,1342242816
Control24=IDC_CHEKSMOO,button,1342244387
Control25=IDC_STATBACKG,static,1342177285
Control26=IDC_BUTNEWPROJ,button,1342242816
Control27=IDC_BUTLOADPROJ,button,1342242816
Control28=IDC_BUTSAVEPROJ,button,1342242816
Control29=IDC_BUTSAVEASWAV,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308482
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354

[DLG:IDD_DIALOGSTOP]
Type=1
Class=CButStop
ControlCount=1
Control1=IDOK,button,1342242817

[CLS:CButStop]
Type=0
HeaderFile=ButStop.h
ImplementationFile=ButStop.cpp
BaseClass=CDialog
Filter=D
LastObject=CButStop
VirtualFilter=dWC

[CLS:OffsetWnd]
Type=0
HeaderFile=OffsetWnd.h
ImplementationFile=OffsetWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=OffsetWnd

[CLS:SequenceWnd]
Type=0
HeaderFile=SequenceWnd.h
ImplementationFile=SequenceWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=SequenceWnd

[DLG:IDD_DIALOGSTOP2]
Type=1
Class=CButStop2
ControlCount=1
Control1=IDOK,button,1342242817

[CLS:CButStop2]
Type=0
HeaderFile=ButStop2.h
ImplementationFile=ButStop2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CButStop2

[DLG:IDD_SEQGEN]
Type=1
Class=CSequenceGenerator
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDITRES2,edit,1350639744
Control4=IDC_EDITDUR2,edit,1350639744
Control5=IDC_EDITOFF2,edit,1350639744
Control6=IDC_SCROLDISARR,scrollbar,1342242816
Control7=IDC_SCROLIRREG,scrollbar,1342242816
Control8=IDC_SCROLDENS,scrollbar,1342242816
Control9=IDC_STATRES,static,1342308866
Control10=IDC_STATDUR,static,1342308866
Control11=IDC_STATOFF,static,1342308866
Control12=IDC_STATDISARR,static,1342308352
Control13=IDC_STATIRREG,static,1342308352
Control14=IDC_STATDENS,static,1342308352

[CLS:CSequenceGenerator]
Type=0
HeaderFile=SequenceGenerator.h
ImplementationFile=SequenceGenerator.cpp
BaseClass=CDialog
Filter=D
LastObject=CSequenceGenerator
VirtualFilter=dWC

[DLG:IDD_PROGRESS]
Type=1
Class=CProgress
ControlCount=1
Control1=IDC_STATPROG,static,1342308865

[CLS:CProgress]
Type=0
HeaderFile=Progress.h
ImplementationFile=Progress.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATPROG

[DLG:IDD_DIALOGSTARTUP]
Type=1
Class=CStartup
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342179342
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308353
Control7=IDC_STATIC,static,1342308353
Control8=IDC_STATIC,static,1342308353
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342177285
Control12=IDC_STATIC,static,1342177285

[CLS:CStartup]
Type=0
HeaderFile=Startup.h
ImplementationFile=Startup.cpp
BaseClass=CDialog
Filter=D
LastObject=CStartup

