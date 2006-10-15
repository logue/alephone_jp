// LinePropertyDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "LinePropertyDialog.h"


// CLinePropertyDialog ダイアログ

IMPLEMENT_DYNAMIC(CLinePropertyDialog, CDialog)

CLinePropertyDialog::CLinePropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLinePropertyDialog::IDD, pParent)
{

}

CLinePropertyDialog::~CLinePropertyDialog()
{
}

void CLinePropertyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLinePropertyDialog, CDialog)
END_MESSAGE_MAP()


// CLinePropertyDialog メッセージ ハンドラ
