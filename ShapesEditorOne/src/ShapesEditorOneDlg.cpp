// ShapesEditorOneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "ShapesEditorOneDlg.h"
#include ".\shapeseditoronedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CShapesEditorOneDlg dialog




CShapesEditorOneDlg::CShapesEditorOneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShapesEditorOneDlg::IDD, pParent)
    , bitmapSelect(0)
    , sequencesSelect(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShapesEditorOneDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //DDX_Control(pDX, IDC_RADIO1, bitmapSelect);
    //DDX_Control(pDX, IDC_RADIO2, sequencesSelect);
}

BEGIN_MESSAGE_MAP(CShapesEditorOneDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
    ON_COMMAND(ID_FILE_CLOSE32773, &CShapesEditorOneDlg::OnFileClose32773)
    ON_COMMAND(ID_FILE_OPEN32772, &CShapesEditorOneDlg::OnFileOpen32772)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CShapesEditorOneDlg message handlers

BOOL CShapesEditorOneDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
    if(!initialize()){
        AfxMessageBox(L"Fail to initialize");
        return FALSE;
    }

    
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShapesEditorOneDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShapesEditorOneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShapesEditorOneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//init app
bool CShapesEditorOneDlg::initialize()
{
    showMode  = eDialogShowBitmaps;

    CRect panelRect, winRect;
    this->GetWindowRect(&winRect);

    panelRect.left = 80;
    panelRect.top = 0;
    panelRect.right = panelRect.left + winRect.Width() - 100;
    panelRect.bottom = panelRect.top + winRect.Height() - 100;

    //setup dialog
    bitmapsDialog.Create(CBitmapsDialog::IDD, this);
    bitmapsDialog.MoveWindow(&panelRect);

    sequencesDialog.Create(MAKEINTRESOURCE(CSequencesDialog::IDD), this);
    sequencesDialog.MoveWindow(&panelRect);

    setupDialog();

    //setup screen
    CRect cl_rect;
    GetClientRect(&cl_rect);
    SDLToWindows *sdlToWin = new SDLToWindows(this->m_hWnd, cl_rect);
    screenSurface = sdlToWin->getSurface();
    
    struct screen_mode_data scr;
    scr.acceleration = 0;
    scr.bit_depth = screenSurface->format->BitsPerPixel;
    scr.draw_every_other_line = 0;
    scr.fullscreen = 0;
    scr.gamma_level = 0;
    scr.high_resolution = 1;
    scr.size = 2;

    initialize_screen(&scr, false);

    delete sdlToWin;
    
    return true;
}
//setup show/hide dialog
void CShapesEditorOneDlg::setupDialog()
{
    bitmapsDialog.ShowWindow(showMode == eDialogShowBitmaps ? TRUE:FALSE);
    sequencesDialog.ShowWindow(showMode == eDialogShowSequences ? TRUE : FALSE);

    //selection
    bitmapSelect = showMode == eDialogShowBitmaps? TRUE: FALSE;
    sequencesSelect = showMode == eDialogShowSequences? TRUE: FALSE;
    
    CButton* btn = (CButton*)GetDlgItem(IDC_RADIO1);
    btn->SetCheck(bitmapSelect);
    btn = (CButton*)GetDlgItem(IDC_RADIO2);
    btn->SetCheck(sequencesSelect);

    bitmapsDialog.setupDialog();
    sequencesDialog.setupDialog();

    UpdateData();
}

//bitmap
void CShapesEditorOneDlg::OnBnClickedRadio1()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    showMode = eDialogShowBitmaps;

    setupDialog();
}

void CShapesEditorOneDlg::OnBnClickedRadio2()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    showMode = eDialogShowSequences;

    setupDialog();
}
//OnExit
void CShapesEditorOneDlg::OnFileClose32773()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    OnClose();
    DestroyWindow();
}
//OnOpen
void CShapesEditorOneDlg::OnFileOpen32772()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    //ファイル選択ダイアログ
    close_shapes_file();
	CFileDialog dlg(TRUE, L"*.*", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	    L"MarathonMapFile (*.*)|*.*||", this);
    if(dlg.DoModal() == IDOK){
        //ファイル名
        CString filename = dlg.GetPathName();
        char cstr[_MAX_PATH];
        strToChar(filename, cstr);

        CRect cl_rect;
        GetClientRect(&cl_rect);
        SDLToWindows *sdlToWin = new SDLToWindows(this->m_hWnd, cl_rect);
        screenSurface = sdlToWin->getSurface();
        if(!openShapes(cstr)){
            AfxMessageBox(CString("failed to open shapes file:") + 
                dlg.GetFileName());
        }else{
            theApp.isShapesLoaded = true;
        }
        delete sdlToWin;

        setupDialog();
    }
}
//OnClose
void CShapesEditorOneDlg::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    closeShapes();

    CDialog::OnClose();
}
