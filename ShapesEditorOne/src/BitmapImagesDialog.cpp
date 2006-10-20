// BitmapImagesDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapImagesDialog.h"


// CBitmapImagesDialog ダイアログ

IMPLEMENT_DYNAMIC(CBitmapImagesDialog, CDialog)
CBitmapImagesDialog::CBitmapImagesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapImagesDialog::IDD, pParent)
    , clutNum(0)
{
}

CBitmapImagesDialog::~CBitmapImagesDialog()
{
}

void CBitmapImagesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, clutNum);
    DDX_Control(pDX, IDC_COMBO1, clutCmb);
}


BEGIN_MESSAGE_MAP(CBitmapImagesDialog, CDialog)
END_MESSAGE_MAP()


// CBitmapImagesDialog メッセージ ハンドラ

BOOL CBitmapImagesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CBitmapImagesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CBitmapImagesDialog::setupDialog()
{
    Invalidate(FALSE);
}