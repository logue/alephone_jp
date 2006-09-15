// SelectLevelDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "SelectLevelDialog.h"
#include ".\selectleveldialog.h"


// CSelectLevelDialog ダイアログ

IMPLEMENT_DYNAMIC(CSelectLevelDialog, CDialog)
CSelectLevelDialog::CSelectLevelDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectLevelDialog::IDD, pParent)
{
}

CSelectLevelDialog::~CSelectLevelDialog()
{
}

void CSelectLevelDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, selectLevelListBox);
}


BEGIN_MESSAGE_MAP(CSelectLevelDialog, CDialog)
    ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
    ON_WM_CREATE()
    ON_LBN_DBLCLK(IDC_LIST1, OnLbnDblclkList1)
END_MESSAGE_MAP()


// CSelectLevelDialog メッセージ ハンドラ

//クリック
void CSelectLevelDialog::OnLbnSelchangeList1()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    theApp.editLevelIndex = selectLevelListBox.GetCurSel();
}

//生成時
int CSelectLevelDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO :  ここに特定な作成コードを追加してください。
    //リストボックスに流し込み
    return 0;
}

BOOL CSelectLevelDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    char cstr[256];

    // TODO :  ここに初期化を追加してください
    for(int i = 0; i < theApp.LevelNameList.GetSize(); i ++){
        sprintf(cstr, "%d.", i+1);
        selectLevelListBox.AddString(CString(cstr) + CString(theApp.LevelNameList.GetAt(i)));
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

//ダブルクリック
void CSelectLevelDialog::OnLbnDblclkList1()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    //選択
    theApp.editLevelIndex = selectLevelListBox.GetCurSel();

    //閉じる
    EndDialog(IDOK);
}
