// PhysicsEditorDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "PhysicsEditorDlg.h"
#include "extensions.h"
#include "FileHandler.h"
#include "effect_definitions.h"
#include "item_definitions.h"
#include "monster_definitions.h"
//#include "monsters.h"

#include "projectile_definitions.h"
#include "weapon_definitions.h"

#include "SaveCheckDialog.h"

/** prototype ****/
static void importPhysicsFile(char *filename);

/** local global ****/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CPhysicsEditorDlg ダイアログ

/**
    メモリ上の設定データを標準のものに直します
*/
static void setDefinitionsToDefault(){
    //モンスター情報
    memcpy(monster_definitions, theApp.monster_default_definitions, sizeof(struct monster_definition) * NUMBER_OF_MONSTER_TYPES);
    memcpy(effect_definitions, theApp.effect_default_definitions, sizeof(struct effect_definition) * NUMBER_OF_EFFECT_TYPES);
    memcpy(projectile_definitions, theApp.projectile_default_definitions, sizeof(struct projectile_definition) * NUMBER_OF_PROJECTILE_TYPES);
    memcpy(physics_models, theApp.physics_default_models, sizeof(struct physics_constants) * NUMBER_OF_PHYSICS_MODELS);
    memcpy(weapon_definitions, theApp.weapon_default_definitions, sizeof(struct weapon_definition) * MAXIMUM_NUMBER_OF_WEAPONS);
}


CPhysicsEditorDlg::CPhysicsEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhysicsEditorDlg::IDD, pParent)
	, physicsFileNameField(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhysicsEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, physicsFileNameField);
	DDX_Control(pDX, IDC_EDIT1, physicsFileName);
	DDX_Control(pDX, IDC_TAB1, phyTabPane);
}

BEGIN_MESSAGE_MAP(CPhysicsEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_OPEN32772, &CPhysicsEditorDlg::OnFileOpenPhysics)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPhysicsEditorDlg::OnTcnSelchangeTab1)
	ON_COMMAND(ID_FILE_EXIT32774, &CPhysicsEditorDlg::OnFileExit32774)
	ON_COMMAND(ID_FILE_NEW32771, &CPhysicsEditorDlg::OnFileNew32771)
	ON_COMMAND(ID_FILE_SAVE, &CPhysicsEditorDlg::OnFileSave)
    ON_WM_DESTROY()
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPhysicsEditorDlg メッセージ ハンドラ

BOOL CPhysicsEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
/*
    this->accel = LoadAccelerators(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDR_ACCELERATOR1));
*/

    //現在選択中のモンスター
    theApp.editMonsterTypeId = 0;
    theApp.editEffectTypeId = 0;
    theApp.editPhysicsTypeId = 0;
    theApp.editProjectileTypeId = 0;
    theApp.editWeaponTypeId = 0;

	CRect r, org;
	this->phyTabPane.GetClientRect(r);
	org = r;
	r.OffsetRect(18,70);
	r.right = r.left + org.Width() - 20;
	r.bottom = r.top + org.Height() - 40;
	this->monsterPage.Create(CMonsterPage::IDD, this);
	this->monsterPage.MoveWindow(&r, TRUE);
	this->monsterPage.ShowWindow(SW_SHOW);
	this->monsterPage2.Create(CMonsterPage2::IDD, this);
	this->monsterPage2.MoveWindow(&r, TRUE);
	this->monsterPage2.ShowWindow(SW_HIDE);
	this->monsterPage3.Create(CMonsterPage3::IDD, this);
	this->monsterPage3.MoveWindow(&r, TRUE);
	this->monsterPage3.ShowWindow(SW_HIDE);
	this->monsterPage4.Create(CMonsterPage4::IDD, this);
	this->monsterPage4.MoveWindow(&r, TRUE);
	this->monsterPage4.ShowWindow(SW_HIDE);
	this->effectPage.Create(CEffectPage::IDD, this);
	this->effectPage.MoveWindow(&r, TRUE);
	this->effectPage.ShowWindow(SW_HIDE);
    this->projectilePage.Create(CProjectilePage::IDD, this);
	this->projectilePage.MoveWindow(&r, TRUE);
	this->projectilePage.ShowWindow(SW_HIDE);
    this->physicsPage.Create(CPhysicsPage::IDD, this);
	this->physicsPage.MoveWindow(&r, TRUE);
	this->physicsPage.ShowWindow(SW_HIDE);
    this->weaponPage.Create(CWeaponPage::IDD, this);
	this->weaponPage.MoveWindow(&r, TRUE);
	this->weaponPage.ShowWindow(SW_HIDE);
    this->weaponPage2.Create(CWeaponPage2::IDD, this);
	this->weaponPage2.MoveWindow(&r, TRUE);
	this->weaponPage2.ShowWindow(SW_HIDE);
	
	TC_ITEMW monsterPane;
	monsterPane.mask = TCIF_TEXT;
	monsterPane.pszText = L"Monsters1(Physics)";
	phyTabPane.InsertItem( 0, &monsterPane);
	TC_ITEMW monsterPane2;
	monsterPane2.mask = TCIF_TEXT;
	monsterPane2.pszText = L"Monsters2(Flags)";
	phyTabPane.InsertItem( 1, &monsterPane2);
	TC_ITEMW monsterPane3;
	monsterPane3.mask = TCIF_TEXT;
	monsterPane3.pszText = L"Monsters3(Sequences)";
	phyTabPane.InsertItem( 2, &monsterPane3);
	TC_ITEMW monsterPane4;
	monsterPane4.mask = TCIF_TEXT;
	monsterPane4.pszText = L"Monsters4(Attack)";
	phyTabPane.InsertItem( 3, &monsterPane4);
	TC_ITEMW effectPane;
	effectPane.mask = TCIF_TEXT;
	effectPane.pszText = L"Effects";
	phyTabPane.InsertItem( 4, &effectPane);
	TC_ITEMW projectilePane;
	projectilePane.mask = TCIF_TEXT;
	projectilePane.pszText = L"Projectiles";
	phyTabPane.InsertItem( 5, &projectilePane);
	TC_ITEMW physicsPane;
	physicsPane.mask = TCIF_TEXT;
	physicsPane.pszText = L"Physics";
	phyTabPane.InsertItem( 6, &physicsPane);
	TC_ITEMW weaponPane;
	weaponPane.mask = TCIF_TEXT;
	weaponPane.pszText = L"Weapons1(Appearance)";
	phyTabPane.InsertItem( 7, &weaponPane);
	TC_ITEMW weaponPane2;
	weaponPane2.mask = TCIF_TEXT;
	weaponPane2.pszText = L"Weapons2(Triggers)";
	phyTabPane.InsertItem( 8, &weaponPane2);

	//基本ファイルを読み込み
	importPhysicsFile(DEFAULT_PHYSICS_FILE_NAME);
    setDefinitionsToDefault();
    
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CPhysicsEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CPhysicsEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CPhysicsEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**
    CStringをchar*に変換します
*/
void strToChar(CString src, char* dest){
    LPWSTR buf = new WCHAR[src.GetLength()];
    LPBOOL ok = new BOOL[1];
	lstrcpy(buf, src);
    wcharToChar(buf, dest);
}

/**
    WCHAR*をchar*に変換します。
*/
void wcharToChar(WCHAR* src, char* dest){
    DWORD len = WideCharToMultiByte(CP_ACP, 0,
        src, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0,
        src, -1, dest, len, NULL, NULL);
}

/**
    char*をWCHAR*に変換します
*/
void charToWChar(char* src, WCHAR* dest){
    DWORD len = MultiByteToWideChar(CP_ACP, 0,
        src, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP,0,
        src, -1, dest, len);
}

void CPhysicsEditorDlg::OnFileOpenPhysics()
{
	//ファイルオープンダイアログ表示
	CFileDialog dlg(TRUE, L"*.*", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PhysicsFile (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

        //読み込み
        char str[256];
        strToChar(filename, str);
        importPhysicsFile(str);

        //ダイアログ更新
        setupDialogs();
	}
}

/**
    物理ファイルを読み込みます
*/
void CPhysicsEditorDlg::importPhysicsFile(const char *filename){
	//物理ファイル名設定
	FileSpecifier phy = FileSpecifier(filename);
	set_physics_file(phy);
    //読み込み
	import_definition_structures();


    WCHAR wstr[256];
    charToWChar((char*)filename, wstr);
    //ファイル名設定
	this->physicsFileName.SetWindowTextW(wstr);
    
    //更新を反映
    this->UpdateData();

    //自身にタブ変化メッセージを送りデータを更新する
    PostMessage(TCN_SELCHANGE);
}

void CPhysicsEditorDlg::setupDialogs(){
    this->monsterPage.setupDialog(theApp.editMonsterTypeId);
    this->monsterPage2.setupDialog();
    this->monsterPage3.setupDialog();
    this->monsterPage4.setupDialog();

    this->effectPage.setupDialog();
    this->projectilePage.setupDialog();
    this->physicsPage.setupDialog();

    weaponPage.setupDialog();
    weaponPage2.setupDialog();
}

void CPhysicsEditorDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int sel = this->phyTabPane.GetCurSel();
	//MessageBox(L"CHANGED TAB");

	this->monsterPage.ShowWindow(sel == 0 ? SW_SHOW: SW_HIDE);
	this->monsterPage2.ShowWindow(sel == 1 ? SW_SHOW: SW_HIDE);
	this->monsterPage3.ShowWindow(sel == 2 ? SW_SHOW: SW_HIDE);
	this->monsterPage4.ShowWindow(sel == 3 ? SW_SHOW: SW_HIDE);
	this->effectPage.ShowWindow(sel == 4 ? SW_SHOW: SW_HIDE);
	this->projectilePage.ShowWindow(sel == 5 ? SW_SHOW: SW_HIDE);
	this->physicsPage.ShowWindow(sel == 6 ? SW_SHOW: SW_HIDE);
	this->weaponPage.ShowWindow(sel == 7 ? SW_SHOW: SW_HIDE);
	this->weaponPage2.ShowWindow(sel == 8 ? SW_SHOW: SW_HIDE);

	*pResult = 0;
}
void CPhysicsEditorDlg::OnFileExit32774()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	CSaveCheckDialog dlg;
	if( dlg.DoModal() == IDOK){
		//終了します
        this->DestroyWindow();
		
	}else{
		//何もしません
	}
}

void CPhysicsEditorDlg::OnFileNew32771()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
    //現在の編集は削除されます…
    if(MessageBox(L"If you do, all Editing parameters will disappear!", L"Caution！",
        MB_OKCANCEL | MB_ICONEXCLAMATION) == IDCANCEL){
        //何もしない
        return;
    }
    //デフォルト物理ファイルを読み込み
	//importPhysicsFile(DEFAULT_PHYSICS_FILE_NAME);
    setDefinitionsToDefault();

    setupDialogs();
}

void CPhysicsEditorDlg::OnFileSave()
{
	// TODO: ここにコマンド ハンドラ コードを追加します。
	//保存ダイアログ
    CString fnameStr;
    this->physicsFileName.GetWindowTextW(fnameStr);
    /*if(fnameStr == CString(DEFAULT_PHYSICS_FILE_NAME)){
        fnameStr = CString("hoge.phy");
    }*/
	CFileDialog dlg(FALSE, L"*.*", fnameStr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PhysicsFile (*.phy)|*.phy||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

		char str[256];
        strToChar(filename, str);

		export_definition_structures(str);

		this->physicsFileName.SetWindowTextW(filename);
		this->UpdateData();
	}
}



void CPhysicsEditorDlg::OnDestroy()
{
    
    CDialog::OnDestroy();
    // TODO: ここにメッセージ ハンドラ コードを追加します。
}

void CPhysicsEditorDlg::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    //閉じる確認
    //終了確認ダイアログ表示
	CSaveCheckDialog dlg;
	if( dlg.DoModal() == IDOK){
		//終了します
        CDialog::OnClose();
		
	}else{
		//何もしません
	}
}

/*BOOL CPhysicsEditorDlg::PreTranslateMessage(MSG* pMsg) 
{
    CDialog::PreTranslateMessage(pMsg);
    int x;  
    x = ::TranslateAccelerator(pMsg->hwnd, accel, pMsg);
    TRACE("%d\n", x);
    if(IsDialogMessage(pMsg)) {
        TRACE("上\n");
        return TRUE;
    } else {
        TRACE("下\n");
        TranslateMessage(pMsg);
        return CDialog::PreTranslateMessage(pMsg);
    }

}

*/