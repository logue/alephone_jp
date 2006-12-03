// ShowAnimationDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "ShowAnimationDialog.h"


// CShowAnimationDialog ダイアログ

IMPLEMENT_DYNAMIC(CShowAnimationDialog, CDialog)

CShowAnimationDialog::CShowAnimationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CShowAnimationDialog::IDD, pParent)
{

}

CShowAnimationDialog::~CShowAnimationDialog()
{
}

void CShowAnimationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowAnimationDialog, CDialog)
END_MESSAGE_MAP()


// CShowAnimationDialog メッセージ ハンドラ
