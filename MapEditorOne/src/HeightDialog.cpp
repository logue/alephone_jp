// HeightDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "HeightDialog.h"
#include ".\heightdialog.h"


// CHeightDialog ダイアログ

IMPLEMENT_DYNAMIC(CHeightDialog, CDialog)

CHeightDialog::CHeightDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHeightDialog::IDD, pParent)
    , isRevealHiddenLines(FALSE)
{

}

CHeightDialog::~CHeightDialog()
{
}

void CHeightDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER2, maxSlider);
    DDX_Control(pDX, IDC_SLIDER1, minSlider);
    DDX_Control(pDX, IDC_EDIT1, maxNum);
    DDX_Control(pDX, IDC_EDIT6, minNum);
    DDX_Check(pDX, IDC_CHECK1, isRevealHiddenLines);
}


BEGIN_MESSAGE_MAP(CHeightDialog, CDialog)
    ON_WM_CLOSE()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CHeightDialog::OnNMCustomdrawSlider2)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CHeightDialog::OnNMCustomdrawSlider1)
    ON_EN_CHANGE(IDC_EDIT1, &CHeightDialog::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT6, &CHeightDialog::OnEnChangeEdit6)
    ON_BN_CLICKED(IDC_CHECK1, &CHeightDialog::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CHeightDialog メッセージ ハンドラ
// CMonsterPropertyDialog メッセージ ハンドラ
BOOL CHeightDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CHeightDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CHeightDialog::PostNcDestroy()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CHeightDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CHeightDialog::DestroyWindow()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    //表示を消すだけ
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}


BOOL CHeightDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    int max = SHRT_MAX;
    maxSlider.SetRange(-max, max);
    maxSlider.SetPos(-max);

    minSlider.SetRange(-max, max);
    minSlider.SetPos(max);


    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
//max
void CHeightDialog::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int pos = -maxSlider.GetPos();
    setIntegerNum(pos, &maxNum);
    theApp.viewHeightMax = pos;
    parent->Invalidate(FALSE);
    *pResult = 0;
}

//min
void CHeightDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int pos = -minSlider.GetPos();
    setIntegerNum(pos, &minNum);
    theApp.viewHeightMin = pos;
    parent->Invalidate(FALSE);
    *pResult = 0;
}
//maxnum
void CHeightDialog::OnEnChangeEdit1()
{
    int num = getIntegerNum(&maxNum);
    maxSlider.SetPos(-num);
    parent->Invalidate(FALSE);
    UpdateData();
}
//minnum
void CHeightDialog::OnEnChangeEdit6()
{
    int num = getIntegerNum(&minNum);
    minSlider.SetPos(-num);
    parent->Invalidate(FALSE);
    UpdateData();
}

//reveal hidden lines
void CHeightDialog::OnBnClickedCheck1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    theApp.isRevealHiddenLines = this->isRevealHiddenLines == TRUE?true:false;
}
