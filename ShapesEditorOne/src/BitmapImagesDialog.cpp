// BitmapImagesDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapImagesDialog.h"


// CBitmapImagesDialog ダイアログ

IMPLEMENT_DYNAMIC(CBitmapImagesDialog, CDialog)
CBitmapImagesDialog::CBitmapImagesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapImagesDialog::IDD, pParent)
{
}

CBitmapImagesDialog::~CBitmapImagesDialog()
{
}

void CBitmapImagesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBitmapImagesDialog, CDialog)
END_MESSAGE_MAP()


// CBitmapImagesDialog メッセージ ハンドラ
