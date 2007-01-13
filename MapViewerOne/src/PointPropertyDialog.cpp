// PointPropertyDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PointPropertyDialog.h"


// CPointPropertyDialog ダイアログ

IMPLEMENT_DYNAMIC(CPointPropertyDialog, CDialog)

CPointPropertyDialog::CPointPropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPointPropertyDialog::IDD, pParent)
{

}

CPointPropertyDialog::~CPointPropertyDialog()
{
}

void CPointPropertyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPointPropertyDialog, CDialog)
END_MESSAGE_MAP()


// CPointPropertyDialog メッセージ ハンドラ
