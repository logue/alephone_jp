// BitmapCLUTDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapCLUTDialog.h"


// CBitmapCLUTDialog ダイアログ

IMPLEMENT_DYNAMIC(CBitmapCLUTDialog, CDialog)
CBitmapCLUTDialog::CBitmapCLUTDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapCLUTDialog::IDD, pParent)
{
}

CBitmapCLUTDialog::~CBitmapCLUTDialog()
{
}

void CBitmapCLUTDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBitmapCLUTDialog, CDialog)
END_MESSAGE_MAP()


// CBitmapCLUTDialog メッセージ ハンドラ
