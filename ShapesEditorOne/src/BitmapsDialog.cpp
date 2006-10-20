// BitmapsDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapsDialog.h"
#include ".\bitmapsdialog.h"


// CBitmapsDialog ダイアログ

IMPLEMENT_DYNAMIC(CBitmapsDialog, CDialog)
CBitmapsDialog::CBitmapsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapsDialog::IDD, pParent)
{
}

CBitmapsDialog::~CBitmapsDialog()
{
}

void CBitmapsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, showTypeCmb);
}


BEGIN_MESSAGE_MAP(CBitmapsDialog, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CBitmapsDialog メッセージ ハンドラ

void CBitmapsDialog::setupDialog()
{
    bitmapImagesDialog.ShowWindow(showMode == eBitmapDialogImages? SW_SHOW : SW_HIDE);
    bitmapCLUTDialog.ShowWindow(showMode == eBitmapDialogCLUT? SW_SHOW : SW_HIDE);

    int sel = showTypeCmb.GetCurSel();

    UpdateData();
}
BOOL CBitmapsDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO :  ここに初期化を追加してください
    bitmapImagesDialog.Create(CBitmapImagesDialog::IDD, this);
    bitmapCLUTDialog.Create(CBitmapCLUTDialog::IDD, this);

    CRect parentRect;
    this->GetWindowRect(&parentRect);
    parentRect.top = 20;
    bitmapImagesDialog.MoveWindow(&parentRect);
    bitmapCLUTDialog.MoveWindow(&parentRect);

    showTypeCmb.SetCurSel(0);

    setupDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CBitmapsDialog::OnCbnSelchangeCombo1()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    int sel = showTypeCmb.GetCurSel();
    showMode = sel;
    setupDialog();
}
