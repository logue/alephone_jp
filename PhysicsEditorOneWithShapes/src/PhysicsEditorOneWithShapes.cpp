// PhysicsEditorOneWithShapes.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "PhysicsEditorOneWithShapes.h"
#include "PhysicsEditorOneWithShapesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhysicsEditorOneWithShapesApp

BEGIN_MESSAGE_MAP(CPhysicsEditorOneWithShapesApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPhysicsEditorOneWithShapesApp コンストラクション

CPhysicsEditorOneWithShapesApp::CPhysicsEditorOneWithShapesApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CPhysicsEditorOneWithShapesApp オブジェクトです。

CPhysicsEditorOneWithShapesApp theApp;


// CPhysicsEditorOneWithShapesApp 初期化

BOOL CPhysicsEditorOneWithShapesApp::InitInstance()
{
	// アプリケーション　マニフェストが　visual スタイルを有効にするために、
	// ComCtl32.dll バージョン 6　以降の使用を指定する場合は、
	// Windows XP に　InitCommonControls() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 標準初期化
	// これらの機能を使わずに、最終的な実行可能ファイルのサイズを縮小したい場合は、
	// 以下から、不要な初期化ルーチンを
	// 削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: この文字列を、会社名または組織名などの、
	// 適切な文字列に変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	CPhysicsEditorOneWithShapesDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//       記述してください。
	}

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
