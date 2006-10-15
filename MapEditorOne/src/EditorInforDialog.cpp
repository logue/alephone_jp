// EditorInforDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "EditorInforDialog.h"


// CEditorInforDialog ダイアログ

IMPLEMENT_DYNAMIC(CEditorInforDialog, CDialog)

CEditorInforDialog::CEditorInforDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditorInforDialog::IDD, pParent)
{

}

CEditorInforDialog::~CEditorInforDialog()
{
}

void CEditorInforDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, gridSizeCmb);
    DDX_Control(pDX, IDC_CHECK1, editorFlags[0]);
    DDX_Control(pDX, IDC_CHECK2, editorFlags[1]);
    DDX_Control(pDX, IDC_CHECK3, editorFlags[2]);
    DDX_Control(pDX, IDC_CHECK4, editorFlags[3]);
    DDX_Control(pDX, IDC_CHECK5, editorFlags[4]);
    DDX_Control(pDX, IDC_CHECK6, editorFlags[5]);
    DDX_Control(pDX, IDC_CHECK7, editorFlags[6]);
    DDX_Control(pDX, IDC_CHECK8, editorFlags[7]);
    DDX_Control(pDX, IDC_CHECK9, editorFlags[8]);
    DDX_Control(pDX, IDC_CHECK10, editorFlags[9]);
    DDX_Control(pDX, IDC_COMBO2, colorSetCmb);
    DDX_Control(pDX, IDC_CHECK12, editorFlags[10]);
    DDX_Control(pDX, IDC_CHECK13, editorFlags[11]);
}


BEGIN_MESSAGE_MAP(CEditorInforDialog, CDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &CEditorInforDialog::OnBnClickedButton1)
    ON_CBN_SELCHANGE(IDC_COMBO2, &CEditorInforDialog::OnCbnSelchangeCombo2)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CEditorInforDialog::OnCbnSelchangeCombo1)
    ON_BN_CLICKED(IDC_CHECK1, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK3, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK4, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK5, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK6, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK7, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK8, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK9, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK10, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK12, &CEditorInforDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK13, &CEditorInforDialog::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CEditorInforDialog メッセージ ハンドラ

BOOL CEditorInforDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //store to combo
    char gridSizes[][100] = {"2 WU", "1/1 WU", "1/2 WU", 
        "1/4 WU", "1/8 WU"};
    for(int i = 0; i < NUMBER_OF_GLID; i ++){
        gridSizeCmb.InsertString(i, CString(gridSizes[i]));
    }
    
    char colorSets[][100] = {"Forge", "Marathon", "Customize..."};
    for(int i = 0; i < NUMBER_OF_COLOR_PRESETS; i ++){
        colorSetCmb.InsertString(i, CString(colorSets[i]));
    }

    //get from theApp.setting
    for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
        flags[i] = theApp.setting.flags[i];
        editorFlags[i].SetCheck(theApp.setting.flags[i]?1:0);
    }
    gridIndex = theApp.setting.getGridSizeIndex();
    gridSizeCmb.SetCurSel(gridIndex);
    isInitialSelect = false;
    //color setting
    colorSetCmb.SetCurSel(theApp.setting.getColorSetting()->type);
    MapEditorOneSetting::copyColorSetting(&colorSetting, theApp.setting.getColorSetting());

    UpdateData();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

//default
void CEditorInforDialog::OnBnClickedButton1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    gridSizeCmb.SetCurSel(0);
    colorSetCmb.SetCurSel(COL_FORGE);
    for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
        editorFlags[i].SetCheck(TRUE);
    }
    MapEditorOneSetting::setColorSetting(COL_FORGE, &colorSetting);
}

//select color combo
void CEditorInforDialog::OnCbnSelchangeCombo2()
{
    int sel = colorSetCmb.GetCurSel();
    colorSetting.type = sel;
    if(sel == COL_CUSTOM){
        //launch customizer and select colors
        CColorCustomizeDialog dlg(AfxGetMainWnd());
        if(dlg.DoModal() == IDOK){
        }
    }else{
        MapEditorOneSetting::setColorSetting(sel, &colorSetting);
    }
}
//grid combo
void CEditorInforDialog::OnCbnSelchangeCombo1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    gridIndex = gridSizeCmb.GetCurSel();
}

void CEditorInforDialog::OnBnClickedCheck1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    //check->flags
    for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
        flags[i] = editorFlags[i].GetCheck()!=0?true:false;
    }
}
