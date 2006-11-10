// TextureChildDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "TextureChildDialog.h"


// CTextureChildDialog ダイアログ

IMPLEMENT_DYNAMIC(CTextureChildDialog, CDialog)

CTextureChildDialog::CTextureChildDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureChildDialog::IDD, pParent)
{

}

CTextureChildDialog::~CTextureChildDialog()
{
}

void CTextureChildDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTextureChildDialog, CDialog)
END_MESSAGE_MAP()


// CTextureChildDialog メッセージ ハンドラ
