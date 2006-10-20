// WeaponPage2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "WeaponPage2.h"


// CWeaponPage2 ダイアログ

IMPLEMENT_DYNAMIC(CWeaponPage2, CDialog)

CWeaponPage2::CWeaponPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CWeaponPage2::IDD, pParent)
{

}

CWeaponPage2::~CWeaponPage2()
{
}

void CWeaponPage2::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, weaponTypeCmb);
    DDX_Control(pDX, IDC_EDIT1, weaponTypeNum);

    DDX_Control(pDX, IDC_EDIT2, triggers[0].weaponRoundPerMagazine);
    DDX_Control(pDX, IDC_COMBO15, triggers[0].weaponAmmurationTypeCmb);
    DDX_Control(pDX, IDC_EDIT37, triggers[0].weaponAmmurationTypeNum);
    DDX_Control(pDX, IDC_EDIT39, triggers[0].weaponRoundTicks);
    DDX_Control(pDX, IDC_EDIT40, triggers[0].weaponRecoveryTicks);
    DDX_Control(pDX, IDC_EDIT62, triggers[0].weaponChargingTicks);
    DDX_Control(pDX, IDC_EDIT63, triggers[0].weaponRecoil);
    DDX_Control(pDX, IDC_COMBO31, triggers[0].weaponFiringSoundCmb);
    DDX_Control(pDX, IDC_EDIT64, triggers[0].weaponFiringSoundNum);
    DDX_Control(pDX, IDC_COMBO32, triggers[0].weaponClickSoundCmb);
    DDX_Control(pDX, IDC_EDIT85, triggers[0].weaponClickSoundNum);
    DDX_Control(pDX, IDC_COMBO33, triggers[0].weaponChargingSoundCmb);
    DDX_Control(pDX, IDC_EDIT72, triggers[0].weaponChargingSoundNum);
    DDX_Control(pDX, IDC_COMBO34, triggers[0].weaponShellCasingSoundCmb);
    DDX_Control(pDX, IDC_EDIT66, triggers[0].weaponShellCasingSoundNum);
    DDX_Control(pDX, IDC_COMBO35, triggers[0].weaponReloadingSoundCmb);
    DDX_Control(pDX, IDC_EDIT67, triggers[0].weaponReloadingSoundNum);
    DDX_Control(pDX, IDC_COMBO36, triggers[0].weaponChargedSoundCmb);
    DDX_Control(pDX, IDC_EDIT69, triggers[0].weaponChargedSoundNum);
    DDX_Control(pDX, IDC_COMBO37, triggers[0].weaponProjectileTypeCmb);
    DDX_Control(pDX, IDC_EDIT86, triggers[0].weaponProjectileTypeNum);
    DDX_Control(pDX, IDC_EDIT83, triggers[0].weaponError);
    DDX_Control(pDX, IDC_EDIT87, triggers[0].weaponDeltaX);
    DDX_Control(pDX, IDC_EDIT88, triggers[0].weaponDeltaZ);
    DDX_Control(pDX, IDC_COMBO38, triggers[0].weaponShellCasingTypeCmb);
    DDX_Control(pDX, IDC_EDIT90, triggers[0].weaponShellCasingTypeNum);
    DDX_Control(pDX, IDC_EDIT89, triggers[0].weaponBurstCount);

    DDX_Control(pDX, IDC_EDIT16, triggers[1].weaponRoundPerMagazine);
    DDX_Control(pDX, IDC_COMBO25, triggers[1].weaponAmmurationTypeCmb);
    DDX_Control(pDX, IDC_EDIT52, triggers[1].weaponAmmurationTypeNum);
    DDX_Control(pDX, IDC_EDIT53, triggers[1].weaponRoundTicks);
    DDX_Control(pDX, IDC_EDIT54, triggers[1].weaponRecoveryTicks);
    DDX_Control(pDX, IDC_EDIT91, triggers[1].weaponChargingTicks);
    DDX_Control(pDX, IDC_EDIT92, triggers[1].weaponRecoil);
    DDX_Control(pDX, IDC_COMBO39, triggers[1].weaponFiringSoundCmb);
    DDX_Control(pDX, IDC_EDIT93, triggers[1].weaponFiringSoundNum);
    DDX_Control(pDX, IDC_COMBO40, triggers[1].weaponClickSoundCmb);
    DDX_Control(pDX, IDC_EDIT94, triggers[1].weaponClickSoundNum);
    DDX_Control(pDX, IDC_COMBO41, triggers[1].weaponChargingSoundCmb);
    DDX_Control(pDX, IDC_EDIT95, triggers[1].weaponChargingSoundNum);
    DDX_Control(pDX, IDC_COMBO42, triggers[1].weaponShellCasingSoundCmb);
    DDX_Control(pDX, IDC_EDIT96, triggers[1].weaponShellCasingSoundNum);
    DDX_Control(pDX, IDC_COMBO43, triggers[1].weaponReloadingSoundCmb);
    DDX_Control(pDX, IDC_EDIT97, triggers[1].weaponReloadingSoundNum);
    DDX_Control(pDX, IDC_COMBO44, triggers[1].weaponChargedSoundCmb);
    DDX_Control(pDX, IDC_EDIT76, triggers[1].weaponChargedSoundNum);
    DDX_Control(pDX, IDC_COMBO45, triggers[1].weaponProjectileTypeCmb);
    DDX_Control(pDX, IDC_EDIT98, triggers[1].weaponProjectileTypeNum);
    DDX_Control(pDX, IDC_EDIT99, triggers[1].weaponError);
    DDX_Control(pDX, IDC_EDIT100, triggers[1].weaponDeltaX);
    DDX_Control(pDX, IDC_EDIT101, triggers[1].weaponDeltaZ);
    DDX_Control(pDX, IDC_COMBO46, triggers[1].weaponShellCasingTypeCmb);
    DDX_Control(pDX, IDC_EDIT103, triggers[1].weaponShellCasingTypeNum);
    DDX_Control(pDX, IDC_EDIT102, triggers[1].weaponBurstCount);
    DDX_Control(pDX, IDC_EDIT1, weaponTypeNum);
}


BEGIN_MESSAGE_MAP(CWeaponPage2, CDialog)
    ON_WM_SHOWWINDOW()
    ON_CBN_SELCHANGE(IDC_COMBO1, &CWeaponPage2::OnCbnSelchangeCombo1)
    ON_EN_CHANGE(IDC_EDIT2, &CWeaponPage2::OnEnChangeEdit2)
    ON_CBN_SELCHANGE(IDC_COMBO15, &CWeaponPage2::OnCbnSelchangeCombo15)
    ON_EN_CHANGE(IDC_EDIT39, &CWeaponPage2::OnEnChangeEdit39)
    ON_EN_CHANGE(IDC_EDIT40, &CWeaponPage2::OnEnChangeEdit40)
    ON_EN_CHANGE(IDC_EDIT62, &CWeaponPage2::OnEnChangeEdit62)
    ON_EN_CHANGE(IDC_EDIT63, &CWeaponPage2::OnEnChangeEdit63)
    ON_CBN_SELCHANGE(IDC_COMBO31, &CWeaponPage2::OnCbnSelchangeCombo31)
    ON_CBN_SELCHANGE(IDC_COMBO32, &CWeaponPage2::OnCbnSelchangeCombo32)
    ON_CBN_SELCHANGE(IDC_COMBO33, &CWeaponPage2::OnCbnSelchangeCombo33)
    ON_CBN_SELCHANGE(IDC_COMBO34, &CWeaponPage2::OnCbnSelchangeCombo34)
    ON_CBN_SELCHANGE(IDC_COMBO35, &CWeaponPage2::OnCbnSelchangeCombo35)
    ON_CBN_SELCHANGE(IDC_COMBO36, &CWeaponPage2::OnCbnSelchangeCombo36)
    ON_CBN_SELCHANGE(IDC_COMBO37, &CWeaponPage2::OnCbnSelchangeCombo37)
    ON_EN_CHANGE(IDC_EDIT83, &CWeaponPage2::OnEnChangeEdit83)
    ON_EN_CHANGE(IDC_EDIT87, &CWeaponPage2::OnEnChangeEdit87)
    ON_EN_CHANGE(IDC_EDIT88, &CWeaponPage2::OnEnChangeEdit88)
    ON_CBN_SELCHANGE(IDC_COMBO38, &CWeaponPage2::OnCbnSelchangeCombo38)
    ON_EN_CHANGE(IDC_EDIT89, &CWeaponPage2::OnEnChangeEdit89)
    ON_EN_CHANGE(IDC_EDIT16, &CWeaponPage2::OnEnChangeEdit16)
    ON_CBN_SELCHANGE(IDC_COMBO25, &CWeaponPage2::OnCbnSelchangeCombo25)
    ON_EN_CHANGE(IDC_EDIT53, &CWeaponPage2::OnEnChangeEdit53)
    ON_EN_CHANGE(IDC_EDIT54, &CWeaponPage2::OnEnChangeEdit54)
    ON_EN_CHANGE(IDC_EDIT91, &CWeaponPage2::OnEnChangeEdit91)
    ON_EN_CHANGE(IDC_EDIT92, &CWeaponPage2::OnEnChangeEdit92)
    ON_CBN_SELCHANGE(IDC_COMBO39, &CWeaponPage2::OnCbnSelchangeCombo39)
    ON_CBN_SELCHANGE(IDC_COMBO40, &CWeaponPage2::OnCbnSelchangeCombo40)
    ON_CBN_SELCHANGE(IDC_COMBO41, &CWeaponPage2::OnCbnSelchangeCombo41)
    ON_CBN_SELCHANGE(IDC_COMBO42, &CWeaponPage2::OnCbnSelchangeCombo42)
    ON_CBN_SELCHANGE(IDC_COMBO43, &CWeaponPage2::OnCbnSelchangeCombo43)
    ON_CBN_SELCHANGE(IDC_COMBO44, &CWeaponPage2::OnCbnSelchangeCombo44)
    ON_CBN_SELCHANGE(IDC_COMBO45, &CWeaponPage2::OnCbnSelchangeCombo45)
    ON_EN_CHANGE(IDC_EDIT99, &CWeaponPage2::OnEnChangeEdit99)
    ON_EN_CHANGE(IDC_EDIT100, &CWeaponPage2::OnEnChangeEdit100)
    ON_EN_CHANGE(IDC_EDIT101, &CWeaponPage2::OnEnChangeEdit101)
    ON_CBN_SELCHANGE(IDC_COMBO46, &CWeaponPage2::OnCbnSelchangeCombo46)
    ON_EN_CHANGE(IDC_EDIT102, &CWeaponPage2::OnEnChangeEdit102)
END_MESSAGE_MAP()


// CWeaponPage2 メッセージ ハンドラ

void CWeaponPage2::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if(bShow == TRUE){
        //更新
        weaponTypeCmb.SetCurSel(theApp.editWeaponTypeId);
        setupDialog();
    }
}

BOOL CWeaponPage2::OnInitDialog(){
    BOOL ret = CDialog::OnInitDialog();

    //武器の種類
    for(int i = 0; i < MAXIMUM_NUMBER_OF_WEAPONS; i ++){
        weaponTypeCmb.InsertString(i, theApp.weaponInformations[i].jname);
    }
    //弾薬の種類
    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
        triggers[0].weaponAmmurationTypeCmb.InsertString(i, theApp.definedItemInformations[i].jname);
        triggers[1].weaponAmmurationTypeCmb.InsertString(i, theApp.definedItemInformations[i].jname);
    }
    triggers[0].weaponAmmurationTypeCmb.InsertString(NUMBER_OF_DEFINED_ITEMS,
        L"*none*");
    triggers[1].weaponAmmurationTypeCmb.InsertString(NUMBER_OF_DEFINED_ITEMS,
        L"*none*");
    //サウンド
    for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
        for(int j = 0; j < NUMBER_OF_TRIGGERS; j ++){
            triggers[j].weaponFiringSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
            triggers[j].weaponClickSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
            triggers[j].weaponChargingSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
            triggers[j].weaponShellCasingSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
            triggers[j].weaponReloadingSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
            triggers[j].weaponChargedSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        }
    }
    for(int j = 0; j < NUMBER_OF_TRIGGERS; j ++){
        triggers[j].weaponFiringSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
            L"*none*");
        triggers[j].weaponClickSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
            L"*none*");
        triggers[j].weaponChargingSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
            L"*none*");
        triggers[j].weaponShellCasingSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
            L"*none*");
        triggers[j].weaponReloadingSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
            L"*none*");
        triggers[j].weaponChargedSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
            L"*none*");
    }
    //弾の種類
    for(int i = 0; i < NUMBER_OF_PROJECTILE_TYPES; i ++){
        triggers[0].weaponProjectileTypeCmb.InsertString(i, theApp.projectileInformations[i].jname);
        triggers[1].weaponProjectileTypeCmb.InsertString(i, theApp.projectileInformations[i].jname);
    }
    triggers[0].weaponProjectileTypeCmb.InsertString(NUMBER_OF_PROJECTILE_TYPES,
        L"*none*");
    triggers[1].weaponProjectileTypeCmb.InsertString(NUMBER_OF_PROJECTILE_TYPES,
        L"*none*");
    //薬莢の種類
    for(int i = 0; i < NUMBER_OF_SHELL_CASING_TYPES; i ++){
        triggers[0].weaponShellCasingTypeCmb.InsertString(i, theApp.weaponShellCasingInformations[i].jname);
        triggers[1].weaponShellCasingTypeCmb.InsertString(i, theApp.weaponShellCasingInformations[i].jname);
    }
    triggers[0].weaponShellCasingTypeCmb.InsertString(NUMBER_OF_SHELL_CASING_TYPES,
        L"*none*");
    triggers[1].weaponShellCasingTypeCmb.InsertString(NUMBER_OF_SHELL_CASING_TYPES,
        L"*none*");

    
    weaponTypeCmb.SetCurSel(theApp.editWeaponTypeId);
    setupDialog();
    return ret;
}

void CWeaponPage2::setupDialog(){
    int type = theApp.editWeaponTypeId;

    //武器種類
    setIntegerNum(type, &weaponTypeNum);

    for(int j = 0; j < NUMBER_OF_TRIGGERS; j ++){
        //弾薬数
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].rounds_per_magazine,
            &(triggers[j].weaponRoundPerMagazine));
        //弾薬アイテムの種類
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].ammunition_type,
            NUMBER_OF_DEFINED_ITEMS, 
            &triggers[j].weaponAmmurationTypeNum,
            &triggers[j].weaponAmmurationTypeCmb);
        //発砲時間
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].ticks_per_round,
            &(triggers[j].weaponRoundTicks));
        //回復時間
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].recovery_ticks,
            &(triggers[j].weaponRecoveryTicks));
        //チャージ時間
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].charging_ticks,
            &(triggers[j].weaponChargingTicks));
        //反動
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].recoil_magnitude,
            &(triggers[j].weaponRecoil));
        //発砲音
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].firing_sound,
            NUMBER_OF_SOUND_DEFINITIONS, 
            &triggers[j].weaponFiringSoundNum,
            &triggers[j].weaponFiringSoundCmb);
        //空
        setComboNum(
            weapon_definitions[type].weapons_by_trigger[j].click_sound,
            NUMBER_OF_SOUND_DEFINITIONS, 
            &triggers[j].weaponClickSoundNum,
            &triggers[j].weaponClickSoundCmb);
        //チャージ音
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].charging_sound,
            NUMBER_OF_SOUND_DEFINITIONS, 
            &triggers[j].weaponChargingSoundNum,
            &triggers[j].weaponChargingSoundCmb);
        //薬莢の音
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].shell_casing_sound,
            NUMBER_OF_SOUND_DEFINITIONS, 
            &triggers[j].weaponShellCasingSoundNum,
            &triggers[j].weaponShellCasingSoundCmb);
        //再装填
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].reloading_sound,
            NUMBER_OF_SOUND_DEFINITIONS, 
            &triggers[j].weaponReloadingSoundNum,
            &triggers[j].weaponReloadingSoundCmb);
        //チャージ完了
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].charged_sound,
            NUMBER_OF_SOUND_DEFINITIONS, 
            &triggers[j].weaponChargedSoundNum,
            &triggers[j].weaponChargedSoundCmb);
        //弾の種類
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].projectile_type,
            NUMBER_OF_PROJECTILE_TYPES, 
            &triggers[j].weaponProjectileTypeNum,
            &triggers[j].weaponProjectileTypeCmb);

        //誤差
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].theta_error,
            &(triggers[j].weaponError));
        //dx
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].dx,
            &(triggers[j].weaponDeltaX));
        //dz
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].dz,
            &(triggers[j].weaponDeltaZ));
        //薬莢の種類
        setComboNum(weapon_definitions[type].weapons_by_trigger[j].shell_casing_type,
            NUMBER_OF_SHELL_CASING_TYPES, 
            &triggers[j].weaponShellCasingTypeNum,
            &triggers[j].weaponShellCasingTypeCmb);
        //BurstCount
        setIntegerNum(weapon_definitions[type].weapons_by_trigger[j].burst_count,
            &(triggers[j].weaponBurstCount));
    }
    
}
/**
    種類コンボ
*/
void CWeaponPage2::OnCbnSelchangeCombo1()
{
    theApp.editWeaponTypeId = weaponTypeCmb.GetCurSel();
    setupDialog();
}
/**
    弾薬数
*/
void CWeaponPage2::OnEnChangeEdit2()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].rounds_per_magazine =
        getIntegerNum(&triggers[0].weaponRoundPerMagazine);
}
//item
void CWeaponPage2::OnCbnSelchangeCombo15()
{
    int sel = triggers[0].weaponAmmurationTypeCmb.GetCurSel();
    if( sel == NUMBER_OF_DEFINED_ITEMS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].ammunition_type =
        sel;
    setIntegerNum(sel, &triggers[0].weaponAmmurationTypeNum);
}
//firing time
void CWeaponPage2::OnEnChangeEdit39()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].ticks_per_round =
        getIntegerNum(&triggers[0].weaponRoundTicks);
}
//recovery
void CWeaponPage2::OnEnChangeEdit40()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].recovery_ticks =
        getIntegerNum(&triggers[0].weaponRecoveryTicks);
}
//charge
void CWeaponPage2::OnEnChangeEdit62()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].charging_ticks =
        getIntegerNum(&triggers[0].weaponChargingTicks);
}
//nock back
void CWeaponPage2::OnEnChangeEdit63()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].recoil_magnitude =
        getIntegerNum(&triggers[0].weaponRecoil);
}
//firing sound
void CWeaponPage2::OnCbnSelchangeCombo31()
{
    int sel = triggers[0].weaponFiringSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].firing_sound = sel;
    setIntegerNum(sel, &triggers[0].weaponFiringSoundNum);
    UpdateData();
}
//click sound
void CWeaponPage2::OnCbnSelchangeCombo32()
{
    int sel = triggers[0].weaponClickSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].click_sound = sel;
    setIntegerNum(sel, &triggers[0].weaponClickSoundNum);
    UpdateData();
}
//charging
void CWeaponPage2::OnCbnSelchangeCombo33()
{
    int sel = triggers[0].weaponChargingSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].charging_sound = sel;
    setIntegerNum(sel, &triggers[0].weaponChargingSoundNum);
    UpdateData();
}
//shell casing
void CWeaponPage2::OnCbnSelchangeCombo34()
{
    int sel = triggers[0].weaponShellCasingSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].shell_casing_sound = sel;
    setIntegerNum(sel, &triggers[0].weaponShellCasingSoundNum);
    UpdateData();
}
//reloading sound
void CWeaponPage2::OnCbnSelchangeCombo35()
{
    int sel = triggers[0].weaponReloadingSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].reloading_sound = sel;
    setIntegerNum(sel, &triggers[0].weaponReloadingSoundNum);
    UpdateData();
}
//charged sound
void CWeaponPage2::OnCbnSelchangeCombo36()
{
    int sel = triggers[0].weaponChargedSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].charged_sound = sel;
    setIntegerNum(sel, &triggers[0].weaponChargedSoundNum);
    UpdateData();
}
//projectile type
void CWeaponPage2::OnCbnSelchangeCombo37()
{
    int sel = triggers[0].weaponProjectileTypeCmb.GetCurSel();
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].projectile_type = sel;
    setIntegerNum(sel, &triggers[0].weaponProjectileTypeNum);
    UpdateData();
}
//error
void CWeaponPage2::OnEnChangeEdit83()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].theta_error =
        getIntegerNum(&triggers[0].weaponError);
}
//dx
void CWeaponPage2::OnEnChangeEdit87()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].dx =
        getIntegerNum(&triggers[0].weaponDeltaX);
}
//dz
void CWeaponPage2::OnEnChangeEdit88()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].dz =
        getIntegerNum(&triggers[0].weaponDeltaZ);
}
//shell casing type
void CWeaponPage2::OnCbnSelchangeCombo38()
{
    int sel = triggers[0].weaponShellCasingTypeCmb.GetCurSel();
    if(sel == NUMBER_OF_SHELL_CASING_TYPES){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].shell_casing_type = sel;
    setIntegerNum(sel, &triggers[0].weaponShellCasingTypeNum);
    UpdateData();
}
//burst count
void CWeaponPage2::OnEnChangeEdit89()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[0].burst_count =
        getIntegerNum(&triggers[0].weaponBurstCount);
}

////////////////////////
/// secondary

//round per magazine
void CWeaponPage2::OnEnChangeEdit16()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].rounds_per_magazine =
        getIntegerNum(&triggers[1].weaponRoundPerMagazine);
}
//item
void CWeaponPage2::OnCbnSelchangeCombo25()
{
    int sel = triggers[1].weaponAmmurationTypeCmb.GetCurSel();
    if( sel == NUMBER_OF_DEFINED_ITEMS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].ammunition_type =
        sel;
    setIntegerNum(sel, &triggers[1].weaponAmmurationTypeNum);
}
//round per ticks
void CWeaponPage2::OnEnChangeEdit53()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].ticks_per_round =
        getIntegerNum(&triggers[1].weaponRoundTicks);
}
//recovery
void CWeaponPage2::OnEnChangeEdit54()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].recovery_ticks =
        getIntegerNum(&triggers[1].weaponRecoveryTicks);
}
//charge
void CWeaponPage2::OnEnChangeEdit91()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].charging_ticks =
        getIntegerNum(&triggers[1].weaponChargingTicks);
}
//recoil
void CWeaponPage2::OnEnChangeEdit92()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].recoil_magnitude =
        getIntegerNum(&triggers[1].weaponRecoil);
}
//firing sound
void CWeaponPage2::OnCbnSelchangeCombo39()
{
    int sel = triggers[1].weaponFiringSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].firing_sound = sel;
    setIntegerNum(sel, &triggers[1].weaponFiringSoundNum);
    UpdateData();
}
//click sound
void CWeaponPage2::OnCbnSelchangeCombo40()
{
    int sel = triggers[1].weaponClickSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].click_sound = sel;
    setIntegerNum(sel, &triggers[1].weaponClickSoundNum);
    UpdateData();
}
//charging
void CWeaponPage2::OnCbnSelchangeCombo41()
{
    int sel = triggers[1].weaponChargingSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].charging_sound = sel;
    setIntegerNum(sel, &triggers[1].weaponChargingSoundNum);
    UpdateData();
}
//shell casing
void CWeaponPage2::OnCbnSelchangeCombo42()
{
    int sel = triggers[1].weaponShellCasingTypeCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].shell_casing_sound = sel;
    setIntegerNum(sel, &triggers[1].weaponShellCasingTypeNum);
    UpdateData();
}
//reloading
void CWeaponPage2::OnCbnSelchangeCombo43()
{
    int sel = triggers[1].weaponReloadingSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].reloading_sound = sel;
    setIntegerNum(sel, &triggers[1].weaponReloadingSoundNum);
    UpdateData();
}
//charged
void CWeaponPage2::OnCbnSelchangeCombo44()
{
    int sel = triggers[1].weaponChargedSoundCmb.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].charged_sound = sel;
    setIntegerNum(sel, &triggers[1].weaponChargedSoundNum);
    UpdateData();
}
//projectile type
void CWeaponPage2::OnCbnSelchangeCombo45()
{
    int sel = triggers[1].weaponProjectileTypeCmb.GetCurSel();
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].projectile_type = sel;
    setIntegerNum(sel, &triggers[1].weaponProjectileTypeNum);
    UpdateData();
}
//error
void CWeaponPage2::OnEnChangeEdit99()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].theta_error =
        getIntegerNum(&triggers[1].weaponError);
}
//dx
void CWeaponPage2::OnEnChangeEdit100()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].dx =
        getIntegerNum(&triggers[1].weaponDeltaX);
}
//dz
void CWeaponPage2::OnEnChangeEdit101()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].dz =
        getIntegerNum(&triggers[1].weaponDeltaZ);
}
//shell casing
void CWeaponPage2::OnCbnSelchangeCombo46()
{
    int sel = triggers[1].weaponShellCasingTypeCmb.GetCurSel();
    if(sel == NUMBER_OF_SHELL_CASING_TYPES){
        sel = -1;
    }
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].shell_casing_type = sel;
    setIntegerNum(sel, &triggers[1].weaponShellCasingTypeNum);
    UpdateData();
}
//burst count
void CWeaponPage2::OnEnChangeEdit102()
{
    weapon_definitions[theApp.editWeaponTypeId].weapons_by_trigger[1].burst_count =
        getIntegerNum(&triggers[1].weaponBurstCount);
}
