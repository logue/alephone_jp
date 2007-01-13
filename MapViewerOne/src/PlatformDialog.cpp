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
    
    
    //initially
    initActivate.SetCheck(PLATFORM_IS_INITIALLY_ACTIVE(platform)?1:0);
    initExtended.SetCheck(PLATFORM_IS_INITIALLY_EXTENDED(platform)?1:0);
    //contracted?

    //control
    ctrlPlayer.SetCheck(PLATFORM_IS_PLAYER_CONTROLLABLE(platform)?1:0);
    ctrlAliens.SetCheck(PLATFORM_IS_MONSTER_CONTROLLABLE(platform)?1:0);
    UpdateData();

    //bites
    biteDamage.SetCheck(PLATFORM_CAUSES_DAMAGE(platform)?1:0);
    biteReverse.SetCheck(PLATFORM_REVERSES_DIRECTION_WHEN_OBSTRUCTED(platform)?1:0);

    //door?
    door.SetCheck(PLATFORM_IS_DOOR(platform)?1:0);

    //open
    ((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(PLATFORM_COMES_FROM_FLOOR(platform)?1:0);
    ((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(PLATFORM_COMES_FROM_CEILING(platform)?1:0);
    ((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(PLATFORM_GOES_BOTH_WAYS(platform)?1:0);
    floorToCeiling.SetCheck(PLATFORM_EXTENDS_FLOOR_TO_CEILING(platform)?1:0);

    //activate
    actOnce.SetCheck(PLATFORM_ACTIVATES_ONLY_ONCE(platform)?1:0);
    actActivateLight.SetCheck(PLATFORM_ACTIVATES_ONLY_ONCE(platform)?1:0);
    actActivateAdj.SetCheck(PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_WHEN_ACTIVATING(platform)?1:0);
    actDeactivateAdj.SetCheck(PLATFORM_DEACTIVATES_ADJACENT_PLATFORMS_WHEN_ACTIVATING(platform)?1:0);
    actAdj.SetCheck(PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_AT_EACH_LEVEL(platform)?1:0);

    //deactivate
    ((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(
        (!PLATFORM_DEACTIVATES_AT_EACH_LEVEL(platform) && !PLATFORM_DEACTIVATES_AT_INITIAL_LEVEL(platform))?1:0);
    ((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(PLATFORM_DEACTIVATES_AT_EACH_LEVEL(platform)?1:0);
    ((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(PLATFORM_DEACTIVATES_AT_INITIAL_LEVEL(platform)?1:0);
    deDeactivateLight.SetCheck(PLATFORM_DEACTIVATES_LIGHT(platform)?1:0);
    deDeactivateAdj.SetCheck(PLATFORM_DEACTIVATES_ADJACENT_PLATFORMS_WHEN_DEACTIVATING(platform)?1:0);
    deActivateAdj.SetCheck(PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_WHEN_DEACTIVATING(platform)?1:0);

    //misc
    miscCannotExternal.SetCheck(PLATFORM_CANNOT_BE_EXTERNALLY_DEACTIVATED(platform)?1:0);
    miscUseNative.SetCheck(PLATFORM_USES_NATIVE_POLYGON_HEIGHTS(platform)?1:0);
    miscDelayBeforeAct.SetCheck(PLATFORM_DELAYS_BEFORE_ACTIVATION(platform)?1:0);
    miscNotActParent.SetCheck(PLATFORM_DOES_NOT_ACTIVATE_PARENT(platform)?1:0);
    miscContractSlower.SetCheck(PLATFORM_CONTRACTS_SLOWER(platform)?1:0);
    miscLocked.SetCheck(PLATFORM_IS_LOCKED(platform)?1:0);
    miscSecret.SetCheck(PLATFORM_IS_SECRET(platform)?1:0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

