// WeaponPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "WeaponPage.h"


// CWeaponPage ダイアログ

IMPLEMENT_DYNAMIC(CWeaponPage, CDialog)

CWeaponPage::CWeaponPage(CWnd* pParent /*=NULL*/)
	: CDialog(CWeaponPage::IDD, pParent)
{

}

CWeaponPage::~CWeaponPage()
{
}

void CWeaponPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, weaponTypeCmb);
    DDX_Control(pDX, IDC_EDIT1, weaponTypeNum);
    DDX_Control(pDX, IDC_COMBO29, weaponCollectionCmb);
    DDX_Control(pDX, IDC_EDIT40, weaponCollectionNum);
    DDX_Control(pDX, IDC_EDIT11, weaponIdleSequence);
    DDX_Control(pDX, IDC_EDIT44, weaponFiringSequence);
    DDX_Control(pDX, IDC_EDIT12, weaponReloadSequence);
    DDX_Control(pDX, IDC_EDIT13, weaponChargingSequence);
    DDX_Control(pDX, IDC_EDIT83, weaponChargedSequence);
    DDX_Control(pDX, IDC_COMBO15, weaponItemCmb);
    DDX_Control(pDX, IDC_EDIT2, weaponItemNum);
    DDX_Control(pDX, IDC_COMBO16, weaponClassCmb);
    DDX_Control(pDX, IDC_EDIT37, weaponClassNum);
    DDX_Control(pDX, IDC_COMBO20, weaponPowerUpCmb);
    DDX_Control(pDX, IDC_EDIT39, weaponPowerUpNum);
    DDX_Control(pDX, IDC_CHECK2, weaponFlags[0]);
    DDX_Control(pDX, IDC_CHECK3, weaponFlags[1]);
    DDX_Control(pDX, IDC_CHECK4, weaponFlags[2]);
    DDX_Control(pDX, IDC_CHECK122, weaponFlags[3]);
    DDX_Control(pDX, IDC_CHECK6, weaponFlags[4]);
    DDX_Control(pDX, IDC_CHECK123, weaponFlags[5]);
    DDX_Control(pDX, IDC_CHECK8, weaponFlags[6]);
    DDX_Control(pDX, IDC_CHECK124, weaponFlags[7]);
    DDX_Control(pDX, IDC_CHECK10, weaponFlags[8]);
    DDX_Control(pDX, IDC_CHECK125, weaponFlags[9]);
    DDX_Control(pDX, IDC_CHECK12, weaponFlags[10]);
    DDX_Control(pDX, IDC_EDIT6, weaponInstantLight);
    DDX_Control(pDX, IDC_EDIT34, weaponInstantLightContinue);
    DDX_Control(pDX, IDC_EDIT35, weaponIdleWidth);
    DDX_Control(pDX, IDC_EDIT38, weaponIdleHeight);
    DDX_Control(pDX, IDC_EDIT66, weaponKickHeight);
    DDX_Control(pDX, IDC_EDIT41, weaponReloadHeight);
    DDX_Control(pDX, IDC_EDIT42, weaponHorizontalAmplitude);
    DDX_Control(pDX, IDC_EDIT43, weaponBobAmplitude);
    DDX_Control(pDX, IDC_EDIT47, weaponReady);
    DDX_Control(pDX, IDC_EDIT48, weaponAwaitReload);
    DDX_Control(pDX, IDC_EDIT49, weaponReloading);
    DDX_Control(pDX, IDC_EDIT84, weaponReloaded);
    DDX_Control(pDX, IDC_EDIT50, weaponPowerUp);
}


BEGIN_MESSAGE_MAP(CWeaponPage, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CWeaponPage::OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO29, &CWeaponPage::OnCbnSelchangeCombo29)
    ON_EN_CHANGE(IDC_EDIT11, &CWeaponPage::OnEnChangeEdit11)
    ON_EN_CHANGE(IDC_EDIT44, &CWeaponPage::OnEnChangeEdit44)
    ON_EN_CHANGE(IDC_EDIT12, &CWeaponPage::OnEnChangeEdit12)
    ON_EN_CHANGE(IDC_EDIT13, &CWeaponPage::OnEnChangeEdit13)
    ON_EN_CHANGE(IDC_EDIT83, &CWeaponPage::OnEnChangeEdit83)
    ON_CBN_SELCHANGE(IDC_COMBO15, &CWeaponPage::OnCbnSelchangeCombo15)
    ON_CBN_SELCHANGE(IDC_COMBO16, &CWeaponPage::OnCbnSelchangeCombo16)
    ON_CBN_SELCHANGE(IDC_COMBO20, &CWeaponPage::OnCbnSelchangeCombo20)
    ON_BN_CLICKED(IDC_CHECK2, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK3, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK4, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK122, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK6, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK123, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK8, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK124, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK10, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK125, &CWeaponPage::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK12, &CWeaponPage::OnBnClickedCheck2)
    ON_EN_CHANGE(IDC_EDIT6, &CWeaponPage::OnEnChangeEdit6)
    ON_EN_CHANGE(IDC_EDIT34, &CWeaponPage::OnEnChangeEdit34)
    ON_EN_CHANGE(IDC_EDIT35, &CWeaponPage::OnEnChangeEdit35)
    ON_EN_CHANGE(IDC_EDIT38, &CWeaponPage::OnEnChangeEdit38)
    ON_EN_CHANGE(IDC_EDIT66, &CWeaponPage::OnEnChangeEdit66)
    ON_EN_CHANGE(IDC_EDIT41, &CWeaponPage::OnEnChangeEdit41)
    ON_EN_CHANGE(IDC_EDIT42, &CWeaponPage::OnEnChangeEdit42)
    ON_EN_CHANGE(IDC_EDIT43, &CWeaponPage::OnEnChangeEdit43)
    ON_EN_CHANGE(IDC_EDIT47, &CWeaponPage::OnEnChangeEdit47)
    ON_EN_CHANGE(IDC_EDIT48, &CWeaponPage::OnEnChangeEdit48)
    ON_EN_CHANGE(IDC_EDIT49, &CWeaponPage::OnEnChangeEdit49)
    ON_EN_CHANGE(IDC_EDIT84, &CWeaponPage::OnEnChangeEdit84)
    ON_EN_CHANGE(IDC_EDIT50, &CWeaponPage::OnEnChangeEdit50)
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CWeaponPage::OnInitDialog()
{
    BOOL ret = CDialog::OnInitDialog();
    
    //流し込み
    for(int i = 0; i < NUMBER_OF_WEAPONS; i ++){
        weaponTypeCmb.InsertString(i, theApp.weaponInformations[i].jname);
    }

    //コレクション
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        weaponCollectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }

    //アイテム
    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
        weaponItemCmb.InsertString(i, theApp.definedItemInformations[i].jname);
    }
    weaponItemCmb.InsertString(NUMBER_OF_DEFINED_ITEMS,
        L"*none*");
    //分類
    for(int i = 0; i < NUMBER_OF_WEAPON_CLASS_INFORMATIONS; i ++){
        weaponClassCmb.InsertString(i, theApp.weaponClassInformations[i].jname);
    }
    weaponClassCmb.InsertString(NUMBER_OF_WEAPON_CLASS_INFORMATIONS,
        L"*none*");

    /*//パワーアップ
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        weaponCollectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }*/

    weaponTypeCmb.SetCurSel(theApp.editWeaponTypeId);
    setupDialog();
    return ret;
}
void CWeaponPage::setupDialog()
{
    int type = theApp.editWeaponTypeId;
    //種類
    setIntegerNum(type, &weaponTypeNum);

    //コレクション
    setComboNum(weapon_definitions[type].collection, 0,
        &weaponCollectionNum, &weaponCollectionCmb);

    //通常Seq
    setIntegerNum(weapon_definitions[type].idle_shape,
        &weaponIdleSequence);
    //Seq
    setIntegerNum(weapon_definitions[type].firing_shape,
        &weaponFiringSequence);
    //Seq
    setIntegerNum(weapon_definitions[type].reloading_shape,
        &weaponReloadSequence);
    //Seq
    setIntegerNum(weapon_definitions[type].charging_shape,
        &weaponChargingSequence);
    //Seq
    setIntegerNum(weapon_definitions[type].charged_shape,
        &weaponChargedSequence);

    //アイテム
    setComboNum(weapon_definitions[type].item_type, 
        NUMBER_OF_DEFINED_ITEMS,
        &weaponItemNum, &weaponItemCmb);
    //分類
    setComboNum(weapon_definitions[type].weapon_class,
        NUMBER_OF_WEAPON_CLASS_INFORMATIONS,
        &weaponClassNum, &weaponClassCmb);

    //数値→フラグ
    for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
        if((weapon_definitions[type].flags & theApp.weaponFlagInformations[i].bindId)){
            weaponFlags[i].SetCheck(1);
        }else{
            weaponFlags[i].SetCheck(0);
        }
    }

    //発光
    setIntegerNum(weapon_definitions[type].firing_light_intensity,
        &weaponInstantLight);
    //持続
    setIntegerNum(weapon_definitions[type].firing_intensity_decay_ticks,
        &weaponInstantLightContinue);
    setIntegerNum(weapon_definitions[type].idle_width,
        &weaponIdleWidth);
    setIntegerNum(weapon_definitions[type].idle_height,
        &weaponIdleHeight);
    setIntegerNum(weapon_definitions[type].kick_height,
        &weaponKickHeight);
    setIntegerNum(weapon_definitions[type].reload_height,
        &weaponReloadHeight);
    setIntegerNum(weapon_definitions[type].horizontal_amplitude,
        &weaponHorizontalAmplitude);
    setIntegerNum(weapon_definitions[type].bob_amplitude,
        &weaponBobAmplitude);
    setIntegerNum(weapon_definitions[type].ready_ticks,
        &weaponReady);
    setIntegerNum(weapon_definitions[type].await_reload_ticks,
        &weaponAwaitReload);
    setIntegerNum(weapon_definitions[type].loading_ticks,
        &weaponReloading);
    setIntegerNum(weapon_definitions[type].finish_loading_ticks,
        &weaponReloaded);
    /*setIntegerNum(weapon_definitions[type].powerup_ticks,
        &weaponPowerUp);*/
}

// CWeaponPage メッセージ ハンドラ

/**
    武器種類コンボ
*/
void CWeaponPage::OnCbnSelchangeCombo1()
{
    int sel = weaponTypeCmb.GetCurSel();
    theApp.editWeaponTypeId = sel;
    setupDialog();
}
/**
    コレクション
*/
void CWeaponPage::OnCbnSelchangeCombo29()
{
    int sel = weaponCollectionCmb.GetCurSel();
    weapon_definitions[theApp.editWeaponTypeId].collection =
        sel;
    setIntegerNum(sel, &weaponCollectionNum);
    UpdateData();
}

/**
    通常Seq
*/
void CWeaponPage::OnEnChangeEdit11()
{
    weapon_definitions[theApp.editWeaponTypeId].idle_shape =
        getIntegerNum(&weaponIdleSequence);
}

/**
    firing_seq
*/
void CWeaponPage::OnEnChangeEdit44()
{
    weapon_definitions[theApp.editWeaponTypeId].firing_shape =
        getIntegerNum(&weaponFiringSequence);
}

/**
reload
*/
void CWeaponPage::OnEnChangeEdit12()
{
    weapon_definitions[theApp.editWeaponTypeId].reloading_shape =
        getIntegerNum(&weaponReloadSequence);
}

/**
charging
*/
void CWeaponPage::OnEnChangeEdit13()
{
    weapon_definitions[theApp.editWeaponTypeId].charging_shape =
        getIntegerNum(&weaponChargingSequence);
}

/**
charged
*/
void CWeaponPage::OnEnChangeEdit83()
{
    weapon_definitions[theApp.editWeaponTypeId].charged_shape =
        getIntegerNum(&weaponChargedSequence);
}

/**
    アイテム
*/
void CWeaponPage::OnCbnSelchangeCombo15()
{
    int sel = weaponItemCmb.GetCurSel();
    weapon_definitions[theApp.editWeaponTypeId].item_type = sel;
    setIntegerNum(sel, &weaponItemNum);
    UpdateData();
}

/**
    class
*/
void CWeaponPage::OnCbnSelchangeCombo16()
{
    int sel = weaponClassCmb.GetCurSel();
    weapon_definitions[theApp.editWeaponTypeId].weapon_class = sel;
    setIntegerNum(sel, &weaponClassNum);
    UpdateData();
}

/**
power up disable
*/
void CWeaponPage::OnCbnSelchangeCombo20()
{
}
/**
    フラグ
*/
void CWeaponPage::OnBnClickedCheck2()
{
    //値セット
    int flag = 0;
    for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
        if(weaponFlags[i].GetCheck()){
            flag |= theApp.weaponFlagInformations[i].bindId;
        }
    }
    weapon_definitions[theApp.editWeaponTypeId].flags = flag;
}

/**
    発光
*/
void CWeaponPage::OnEnChangeEdit6()
{
    weapon_definitions[theApp.editWeaponTypeId].firing_light_intensity =
        getIntegerNum(&weaponInstantLight);
}
/**
    持続
*/
void CWeaponPage::OnEnChangeEdit34()
{
    weapon_definitions[theApp.editWeaponTypeId].firing_intensity_decay_ticks =
        getIntegerNum(&weaponInstantLightContinue);
}
/**
    idle w
*/
void CWeaponPage::OnEnChangeEdit35()
{
    weapon_definitions[theApp.editWeaponTypeId].idle_width =
        getIntegerNum(&weaponIdleWidth);
}
/**
    idle h
*/
void CWeaponPage::OnEnChangeEdit38()
{
    weapon_definitions[theApp.editWeaponTypeId].idle_height =
        getIntegerNum(&weaponIdleHeight);
}
/**
    fire h
*/
void CWeaponPage::OnEnChangeEdit66()
{
    weapon_definitions[theApp.editWeaponTypeId].kick_height =
        getIntegerNum(&weaponKickHeight);
}
/**
    reload h
*/
void CWeaponPage::OnEnChangeEdit41()
{
    weapon_definitions[theApp.editWeaponTypeId].reload_height =
        getIntegerNum(&weaponReloadHeight);
}
/**
    horizontal w
*/
void CWeaponPage::OnEnChangeEdit42()
{
    weapon_definitions[theApp.editWeaponTypeId].horizontal_amplitude =
        getIntegerNum(&weaponHorizontalAmplitude);
}

/**
    bob amp
*/
void CWeaponPage::OnEnChangeEdit43()
{
    weapon_definitions[theApp.editWeaponTypeId].bob_amplitude =
        getIntegerNum(&weaponBobAmplitude);
}

/**
     ticks
*/
void CWeaponPage::OnEnChangeEdit47()
{
    weapon_definitions[theApp.editWeaponTypeId].ready_ticks =
        getIntegerNum(&weaponReady);
}

/**
    await reload
*/
void CWeaponPage::OnEnChangeEdit48()
{
    weapon_definitions[theApp.editWeaponTypeId].await_reload_ticks =
        getIntegerNum(&weaponAwaitReload);
}

/**
    reloading
*/
void CWeaponPage::OnEnChangeEdit49()
{
    weapon_definitions[theApp.editWeaponTypeId].loading_ticks =
        getIntegerNum(&weaponReloading);
}

/**
    reloaded
*/
void CWeaponPage::OnEnChangeEdit84()
{
    weapon_definitions[theApp.editWeaponTypeId].finish_loading_ticks =
        getIntegerNum(&weaponReloaded);
}

/**
    power up disable
*/
void CWeaponPage::OnEnChangeEdit50()
{
}

/**
*/
void CWeaponPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if(bShow == TRUE){
        weaponTypeCmb.SetCurSel(theApp.editWeaponTypeId);
        setupDialog();
    }
}
