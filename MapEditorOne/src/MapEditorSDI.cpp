// MapEditorSDI.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "MainFrm.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static char* POLYGON_COLOR_FILE_NAME = "data/PolygonColor.txt";

// CMapEditorSDIApp

BEGIN_MESSAGE_MAP(CMapEditorSDIApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMapEditorSDIApp::OnAppAbout)
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 標準の印刷セットアップ コマンド
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
    ON_COMMAND(ID_FILE_OPEN, &CMapEditorSDIApp::OnFileOpen)
END_MESSAGE_MAP()


// CMapEditorSDIApp コンストラクション

static void loadInformations(const char* filename, int max, 
                             Information *informations)
{
    const int LENGTH = 1024 * 10;
    char cstr[LENGTH];

    CFile f;
    if(!f.Open(CString(filename), CFile::modeRead)){
        CString errMsg = CString("Couldn't open:");
        errMsg += L"[" + CString(filename) + L"]";
        MessageBox(NULL, errMsg, L"Error", MB_OK);
        exit(-1);
    }
    f.Read(cstr, LENGTH);
    CString str = CString(cstr);
    CStringArray array;
    splitString(str, "\r\n", array);
    for(int i = 0; i < max; i ++){
        informations[i].jname = array.GetAt(i);
    }
    f.Close();
}

CMapEditorSDIApp::CMapEditorSDIApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。

    //ファイルからコンボ用文字列読み込み
    //大別
    loadInformations("data/ObjectTypes.txt", NUMBER_OF_OBJECT_TYPES,
        objectTypeInformations);
    //モンスター
    loadInformations("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES,
        monsterTypeInformations);
    //オブジェ
    loadInformations("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS,
        sceneryTypeInformations);
    //アイテム
    loadInformations("data/DefinedItems.txt", NUMBER_OF_DEFINED_ITEMS,
        itemTypeInformations);
    //音
    loadInformations("data/SoundSourceTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS,
        soundSourceInformations);
    //起動
    loadInformations("data/ActivateTypes.txt", NUMBER_OF_ACTIVATE_TYPES,
        activateTypeInformations);
    //フラグ
    objectFlagInformations[0].bind = _map_object_is_invisible;
    objectFlagInformations[1].bind = _map_object_hanging_from_ceiling;
    objectFlagInformations[2].bind = _map_object_is_blind;
    objectFlagInformations[3].bind = _map_object_is_deaf;
    objectFlagInformations[4].bind = _map_object_floats;
    objectFlagInformations[5].bind = _map_object_is_network_only;

    //termnal groups
    loadInformations("data/TerminalGroupTypes.txt", NUMBER_OF_GROUP_TYPES,
        terminalGroupTypeInformations);

    //polygon type
    loadInformations("data/PolygonType.txt", NUMBER_OF_POLYGON_TYPE,
        polygonTypeInformations);

    //色設定
    //ファイルから読み込み
    const int LENGTH = 1024*10;
    char cstr[LENGTH];
    
    char *filename = POLYGON_COLOR_FILE_NAME;
    CFile f;
    if(!f.Open(CString(filename), CFile::modeRead)){
        CString errMsg = CString("Couldn't open:");
        errMsg += L"[" + CString(filename) + L"]";
        MessageBox(NULL, errMsg, L"Error", MB_OK);
        exit(-1);
    }
    f.Read(cstr, LENGTH);
    CString str = CString(cstr);
    CStringArray array;
    splitString(str, "\r\n", array);
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        //コンマで分解
        CStringArray splits;
        splitString((CString&)array.GetAt(i), ",", splits);
        int col[3];
        for(int j = 0; j < 3; j ++){
            CString num = splits.GetAt(j);
            char dataCStr[256];
            strToChar(num.Trim(), dataCStr);
            col[j] = atoi(dataCStr);
        }
        this->polygonTypeColor[i] = RGB(col[0], col[1], col[2]);
    }
    f.Close();

    //Zoom
    zoomDivision = ZOOM_DIVISION_DEFAULT;

    isPressLButtonWithShift = false;

    offset.x = 0;
    offset.y = 0;

    objectPropertyDialog = NULL;

    //1WU 1/2WU 1/4WU 1/8 WU
    int intervals[]={
        WORLD_ONE * 2, WORLD_ONE, WORLD_ONE / 2, WORLD_ONE / 4, WORLD_ONE / 8
    };
    for(int i = 0; i < NUMBER_OF_GLID; i ++){
        gridIntervals[i] = intervals[i];
    }
    nowGridInterval = 0;

    this->isObjectPropertyDialogShow = TRUE;
    this->isPolygonTypeDialogShow = TRUE;
    this->isHeightDialogShow = TRUE;

    AfxInitRichEdit();

    selectGroupInformation.clear();
    isSelectingGroup = false;
}


// 唯一の CMapEditorSDIApp オブジェクトです。

CMapEditorSDIApp theApp;


// CMapEditorSDIApp 初期化

BOOL CMapEditorSDIApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// OLE ライブラリを初期化します。
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("MapEditorOne"));
	LoadStdProfileSettings(4);  // 標準の INI ファイルのオプションをロードします (MRU を含む)
	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMapEditorSDIDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CMapEditorSDIView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE Execute open を使用可能にします。
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出してください。
	//  SDI アプリケーションでは、ProcessShellCommand の直後にこの呼び出しが発生しなければなりません。
	// ドラッグ/ドロップ オープンを許可します。
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



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

// ダイアログを実行するためのアプリケーション コマンド
void CMapEditorSDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CMapEditorSDIApp メッセージ ハンドラ

static void loadMap(const char* filename)
{
}

void CMapEditorSDIApp::OnFileOpen()
{
    
    // TODO: ここにコマンド ハンドラ コードを追加します。
    //開くダイアログ
}