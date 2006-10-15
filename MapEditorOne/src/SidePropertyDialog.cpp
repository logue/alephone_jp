// SidePropertyDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "SidePropertyDialog.h"


// CSidePropertyDialog ダイアログ

IMPLEMENT_DYNAMIC(CSidePropertyDialog, CDialog)

CSidePropertyDialog::CSidePropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSidePropertyDialog::IDD, pParent)
{

}

CSidePropertyDialog::~CSidePropertyDialog()
{
}

void CSidePropertyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSidePropertyDialog, CDialog)
END_MESSAGE_MAP()


// CSidePropertyDialog メッセージ ハンドラ
