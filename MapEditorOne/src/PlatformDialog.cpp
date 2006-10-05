// PlatformDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PlatformDialog.h"


// CPlatformDialog ダイアログ

IMPLEMENT_DYNAMIC(CPlatformDialog, CDialog)

CPlatformDialog::CPlatformDialog(CWnd* pParent , int index)
	: CDialog(CPlatformDialog::IDD, pParent)
{
    platformIndex = index;
}

CPlatformDialog::~CPlatformDialog()
{
}

void CPlatformDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, typeCmb);
    DDX_Control(pDX, IDC_EDIT1, speedNum);
    DDX_Control(pDX, IDC_EDIT2, delayNum);
    DDX_Control(pDX, IDC_COMBO2, speedCmb);
    DDX_Control(pDX, IDC_COMBO3, delayCmb);
    DDX_Control(pDX, IDC_CHECK1, autoMin);
    DDX_Control(pDX, IDC_CHECK2, autoMax);
    DDX_Control(pDX, IDC_EDIT3, minHeight);
    DDX_Control(pDX, IDC_EDIT4, maxHeight);
    DDX_Control(pDX, IDC_CHECK3, door);
    DDX_Control(pDX, IDC_COMBO7, presetCmb);
    DDX_Control(pDX, IDC_CHECK15, floorToCeiling);
    DDX_Control(pDX, IDC_CHECK5, initActivate);
    DDX_Control(pDX, IDC_CHECK6, initExtended);
    DDX_Control(pDX, IDC_CHECK7, ctrlPlayer);
    DDX_Control(pDX, IDC_CHECK8, ctrlAliens);
    DDX_Control(pDX, IDC_CHECK9, biteDamage);
    DDX_Control(pDX, IDC_CHECK10, biteReverse);
    DDX_Control(pDX, IDC_CHECK16, actOnce);
    DDX_Control(pDX, IDC_CHECK17, actActivateLight);
    DDX_Control(pDX, IDC_CHECK18, actActivateAdj);
    DDX_Control(pDX, IDC_CHECK19, actDeactivateAdj);
    DDX_Control(pDX, IDC_CHECK20, actAdj);
    DDX_Control(pDX, IDC_CHECK21, deDeactivateLight);
    DDX_Control(pDX, IDC_CHECK22, deDeactivateAdj);
    DDX_Control(pDX, IDC_CHECK23, deActivateAdj);
    DDX_Control(pDX, IDC_CHECK24, miscCannotExternal);
    DDX_Control(pDX, IDC_CHECK25, miscUseNative);
    DDX_Control(pDX, IDC_CHECK26, miscDelayBeforeAct);
    DDX_Control(pDX, IDC_CHECK27, miscNotActParent);
    DDX_Control(pDX, IDC_CHECK28, miscContractSlower);
    DDX_Control(pDX, IDC_CHECK29, miscLocked);
    DDX_Control(pDX, IDC_CHECK30, miscSecret);
    DDX_Control(pDX, IDC_COMBO10, tagCmb);
}


BEGIN_MESSAGE_MAP(CPlatformDialog, CDialog)
END_MESSAGE_MAP()


// CPlatformDialog メッセージ ハンドラ

BOOL CPlatformDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //store speed
    //store delay
    //store tag
    //store other platform
    //store presets
    
    platform_data *platform = &PlatformList[platformIndex];
    // *** set nums ***
    //types
    //speed
    setIntegerNum(platform->speed, &speedNum);
    
    //delay
    setIntegerNum(platform->delay, &delayNum);

    //height

    UpdateData();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

