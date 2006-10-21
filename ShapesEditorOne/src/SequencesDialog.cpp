// SequencesDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "SequencesDialog.h"


// CSequencesDialog ダイアログ

IMPLEMENT_DYNAMIC(CSequencesDialog, CDialog)
CSequencesDialog::CSequencesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSequencesDialog::IDD, pParent)
{
}

CSequencesDialog::~CSequencesDialog()
{
}

void CSequencesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSequencesDialog, CDialog)
END_MESSAGE_MAP()


// CSequencesDialog メッセージ ハンドラ

BOOL CSequencesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CSequencesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    setupDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSequencesDialog::setupDialog()
{
    UpdateData();

}
