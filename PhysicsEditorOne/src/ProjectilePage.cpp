// ProjectilePage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "ProjectilePage.h"


// CProjectilePage ダイアログ

IMPLEMENT_DYNAMIC(CProjectilePage, CDialog)

CProjectilePage::CProjectilePage(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectilePage::IDD, pParent)
{

}

CProjectilePage::~CProjectilePage()
{
}

void CProjectilePage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, prTypeCmb);
    DDX_Control(pDX, IDC_COMBO15, prCollectionCmb);
    DDX_Control(pDX, IDC_EDIT1, prTypeNum);
    DDX_Control(pDX, IDC_EDIT2, prCollectionNum);
    DDX_Control(pDX, IDC_EDIT37, prSequence);
    DDX_Control(pDX, IDC_COMBO16, prDetonationEffect);
    DDX_Control(pDX, IDC_EDIT40, prDetonationEffectNum);
    DDX_Control(pDX, IDC_COMBO29, prMediaDetonationEffectCmb);
    DDX_Control(pDX, IDC_EDIT63, prMediaDetonationEffectNum);
    DDX_Control(pDX, IDC_COMBO30, prContrailEffectCmb);
    DDX_Control(pDX, IDC_EDIT65, prContrailEffectNum);
    DDX_Control(pDX, IDC_EDIT39, prTicksBetweenContrail);
    DDX_Control(pDX, IDC_EDIT71, prMaximumContrail);
    DDX_Control(pDX, IDC_EDIT72, prMediaProjectilePromotion);
    DDX_Control(pDX, IDC_EDIT73, prRadius);
    DDX_Control(pDX, IDC_EDIT74, prAreaOfEffect);
    DDX_Control(pDX, IDC_COMBO6, prDamageTypeCmb);
    DDX_Control(pDX, IDC_EDIT79, prDamageTypeNum);
    DDX_Control(pDX, IDC_EDIT80, prDamageBase);
    DDX_Control(pDX, IDC_EDIT81, prDamageRandom);
    DDX_Control(pDX, IDC_EDIT82, prDamageScale);
    DDX_Control(pDX, IDC_CHECK22, prDamageFlag);
    DDX_Control(pDX, IDC_EDIT5, prSpeed);
    DDX_Control(pDX, IDC_EDIT75, prRange);
    DDX_Control(pDX, IDC_EDIT76, prPitch);
    DDX_Control(pDX, IDC_EDIT77, prFlyBySoundNum);
    DDX_Control(pDX, IDC_COMBO4, prFlyBySoundCmb);
    DDX_Control(pDX, IDC_EDIT78, prBoundSoundNum);
    DDX_Control(pDX, IDC_COMBO5, prBoundSoundCmb);
    DDX_Control(pDX, IDC_CHECK5, prFlags[0]);
    DDX_Control(pDX, IDC_CHECK7, prFlags[1]);
    DDX_Control(pDX, IDC_CHECK9, prFlags[2]);
    DDX_Control(pDX, IDC_CHECK11, prFlags[3]);
    DDX_Control(pDX, IDC_CHECK13, prFlags[4]);
    DDX_Control(pDX, IDC_CHECK15, prFlags[5]);
    DDX_Control(pDX, IDC_CHECK17, prFlags[6]);
    DDX_Control(pDX, IDC_CHECK19, prFlags[7]);
    DDX_Control(pDX, IDC_CHECK21, prFlags[8]);
    DDX_Control(pDX, IDC_CHECK89, prFlags[9]);
    DDX_Control(pDX, IDC_CHECK110, prFlags[10]);
    DDX_Control(pDX, IDC_CHECK111, prFlags[11]);
    DDX_Control(pDX, IDC_CHECK112, prFlags[12]);
    DDX_Control(pDX, IDC_CHECK113, prFlags[13]);
    DDX_Control(pDX, IDC_CHECK114, prFlags[14]);
    DDX_Control(pDX, IDC_CHECK115, prFlags[15]);
    DDX_Control(pDX, IDC_CHECK116, prFlags[16]);
    DDX_Control(pDX, IDC_CHECK117, prFlags[17]);
    DDX_Control(pDX, IDC_CHECK118, prFlags[18]);
    DDX_Control(pDX, IDC_CHECK119, prFlags[19]);
    DDX_Control(pDX, IDC_CHECK120, prFlags[20]);
    DDX_Control(pDX, IDC_CHECK121, prFlags[21]);
}


BEGIN_MESSAGE_MAP(CProjectilePage, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CProjectilePage::OnCbnSelchangeCombo1)
    ON_WM_SHOWWINDOW()
    ON_CBN_SELCHANGE(IDC_COMBO15, &CProjectilePage::OnCbnSelchangeCombo15)
    ON_EN_CHANGE(IDC_EDIT37, &CProjectilePage::OnEnChangeEdit37)
    ON_BN_CLICKED(IDC_CHECK5, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK7, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK9, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK11, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK13, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK15, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK17, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK19, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK21, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK89, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK110, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK111, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK112, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK113, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK114, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK115, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK116, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK117, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK118, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK119, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK120, &CProjectilePage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK121, &CProjectilePage::OnBnClickedCheck5)
    ON_EN_CHANGE(IDC_EDIT5, &CProjectilePage::OnEnChangeEdit5)
    ON_EN_CHANGE(IDC_EDIT75, &CProjectilePage::OnEnChangeEdit75)
    ON_EN_CHANGE(IDC_EDIT76, &CProjectilePage::OnEnChangeEdit76)
    ON_CBN_SELCHANGE(IDC_COMBO4, &CProjectilePage::OnCbnSelchangeCombo4)
    ON_CBN_SELCHANGE(IDC_COMBO5, &CProjectilePage::OnCbnSelchangeCombo5)
    ON_CBN_SELCHANGE(IDC_COMBO16, &CProjectilePage::OnCbnSelchangeCombo16)
    ON_CBN_SELCHANGE(IDC_COMBO29, &CProjectilePage::OnCbnSelchangeCombo29)
    ON_CBN_SELCHANGE(IDC_COMBO30, &CProjectilePage::OnCbnSelchangeCombo30)
    ON_CBN_SELCHANGE(IDC_COMBO6, &CProjectilePage::OnCbnSelchangeCombo6)
    ON_BN_CLICKED(IDC_CHECK22, &CProjectilePage::OnBnClickedCheck22)
    ON_BN_CLICKED(IDC_BUTTON2, &CProjectilePage::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CProjectilePage::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CProjectilePage::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CProjectilePage::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON43, &CProjectilePage::OnBnClickedButton43)
    ON_BN_CLICKED(IDC_BUTTON44, &CProjectilePage::OnBnClickedButton44)
    ON_BN_CLICKED(IDC_BUTTON45, &CProjectilePage::OnBnClickedButton45)
    ON_BN_CLICKED(IDC_BUTTON35, &CProjectilePage::OnBnClickedButton35)
    ON_BN_CLICKED(IDC_BUTTON8, &CProjectilePage::OnBnClickedButton8)
    ON_BN_CLICKED(IDC_BUTTON9, &CProjectilePage::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON38, &CProjectilePage::OnBnClickedButton38)
    ON_BN_CLICKED(IDC_BUTTON39, &CProjectilePage::OnBnClickedButton39)
    ON_BN_CLICKED(IDC_BUTTON40, &CProjectilePage::OnBnClickedButton40)
    ON_BN_CLICKED(IDC_BUTTON46, &CProjectilePage::OnBnClickedButton46)
    ON_BN_CLICKED(IDC_BUTTON47, &CProjectilePage::OnBnClickedButton47)
    ON_BN_CLICKED(IDC_BUTTON48, &CProjectilePage::OnBnClickedButton48)
    ON_BN_CLICKED(IDC_BUTTON49, &CProjectilePage::OnBnClickedButton49)
    ON_BN_CLICKED(IDC_BUTTON1, &CProjectilePage::OnBnClickedButton1)
    ON_EN_CHANGE(IDC_EDIT80, &CProjectilePage::OnEnChangeEdit80)
    ON_EN_CHANGE(IDC_EDIT81, &CProjectilePage::OnEnChangeEdit81)
    ON_EN_CHANGE(IDC_EDIT82, &CProjectilePage::OnEnChangeEdit82)
    ON_EN_CHANGE(IDC_EDIT39, &CProjectilePage::OnEnChangeEdit39)
    ON_EN_CHANGE(IDC_EDIT71, &CProjectilePage::OnEnChangeEdit71)
    ON_EN_CHANGE(IDC_EDIT72, &CProjectilePage::OnEnChangeEdit72)
    ON_EN_CHANGE(IDC_EDIT73, &CProjectilePage::OnEnChangeEdit73)
    ON_EN_CHANGE(IDC_EDIT74, &CProjectilePage::OnEnChangeEdit74)
END_MESSAGE_MAP()

BOOL CProjectilePage::OnInitDialog()
{
    BOOL ret = CDialog::OnInitDialog();

    //種類
    for(int i = 0; i < NUMBER_OF_PROJECTILE_TYPES; i ++){
        prTypeCmb.InsertString(i, theApp.projectileInformations[i].jname);
    }

    //コレクション
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        prCollectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }

    //効果
    for(int i = 0; i < NUMBER_OF_EFFECT_TYPES; i ++){
        prDetonationEffect.InsertString(i, theApp.effectInformations[i].jname);
        prMediaDetonationEffectCmb.InsertString(i, theApp.effectInformations[i].jname);
        prContrailEffectCmb.InsertString(i, theApp.effectInformations[i].jname);
    }
    prDetonationEffect.InsertString(NUMBER_OF_EFFECT_TYPES,
        L"*none*");
    prMediaDetonationEffectCmb.InsertString(NUMBER_OF_EFFECT_TYPES,
        L"*none*");
    prContrailEffectCmb.InsertString(NUMBER_OF_EFFECT_TYPES,
        L"*none*");

    //サウンド
    for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
        prFlyBySoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        prBoundSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
    }
    prFlyBySoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
        L"*none*");
    prBoundSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
        L"*none*");

    //ダメージタイプ
    for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
        prDamageTypeCmb.InsertString(i, theApp.damageInformations[i].jname);
    }
    prDamageTypeCmb.InsertString(NUMBER_OF_DAMAGE_TYPES,
        L"*none*");

    prTypeCmb.SetCurSel(theApp.editProjectileTypeId);
    return ret;

}

void CProjectilePage::setupDialog()
{
    int type = theApp.editProjectileTypeId;
    setIntegerNum(type, &prTypeNum);

    //col
    setComboNum(projectile_definitions[type].collection,
        0,
        &prCollectionNum, &prCollectionCmb);
    //seq
    setIntegerNum(projectile_definitions[type].shape,
        &prSequence);
    //deto
    setComboNum(projectile_definitions[type].detonation_effect,
        NUMBER_OF_EFFECT_TYPES,
        &prDetonationEffectNum, &prDetonationEffect);
    //media deto
    setComboNum(projectile_definitions[type].media_detonation_effect,
        NUMBER_OF_EFFECT_TYPES,
        &prMediaDetonationEffectNum, &prMediaDetonationEffectCmb);
    //contrail
    setComboNum(projectile_definitions[type].contrail_effect,
        NUMBER_OF_EFFECT_TYPES,
        &prContrailEffectNum, &prContrailEffectCmb);
    //ticks between
    setIntegerNum(projectile_definitions[type].ticks_between_contrails,
        &prTicksBetweenContrail);
    //max contrail
    setIntegerNum(projectile_definitions[type].maximum_contrails,
        &prMaximumContrail);
    //promotion
    setIntegerNum(projectile_definitions[type].media_projectile_promotion,
        &prMediaProjectilePromotion);
    //r
    setIntegerNum(projectile_definitions[type].radius,
        &prRadius);
    //area
    setIntegerNum(projectile_definitions[type].area_of_effect,
        &prAreaOfEffect);
    
    //damage
    //damage type
    setComboNum(projectile_definitions[type].damage.type,
        NUMBER_OF_DAMAGE_TYPES,
        &prDamageTypeNum, &prDamageTypeCmb);
    //damage base
    setIntegerNum(projectile_definitions[type].damage.base,
        &prDamageBase);
    //damage random
    setIntegerNum(projectile_definitions[type].damage.random,
        &prDamageRandom);
    //damage scale
    setIntegerNum(projectile_definitions[type].damage.scale,
        &prDamageScale);
    //damage flag
    if(projectile_definitions[type].damage.flags){
        prDamageFlag.SetCheck(1);
    }else{
        prDamageFlag.SetCheck(0);
    }

    //flags
    int flag = projectile_definitions[type].flags;
    for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
        if(flag & theApp.projectileFlagInformations[i].bindId){
            prFlags[i].SetCheck(1);
        }else{
            prFlags[i].SetCheck(0);
        }
    }

    //speed
    setIntegerNum(projectile_definitions[type].speed,
        &prSpeed);
    //range
    setIntegerNum(projectile_definitions[type].maximum_range,
        &prRange);
    //pitch
    setIntegerNum(projectile_definitions[type].sound_pitch,
        &prPitch);
    //flyby sound
    setComboNum(projectile_definitions[type].flyby_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &prFlyBySoundNum, &prFlyBySoundCmb);
    //bound sound
    setComboNum(projectile_definitions[type].rebound_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &prBoundSoundNum, &prBoundSoundCmb);
}

// CProjectilePage メッセージ ハンドラ
void CProjectilePage::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if(bShow == TRUE){
        prTypeCmb.SetCurSel(theApp.editProjectileTypeId);
        setupDialog();
    }
}
//type
void CProjectilePage::OnCbnSelchangeCombo1()
{
    int sel = prTypeCmb.GetCurSel();
    theApp.editProjectileTypeId = sel;
    setupDialog();
}

//collection
void CProjectilePage::OnCbnSelchangeCombo15()
{
    int sel = prCollectionCmb.GetCurSel();
    projectile_definitions[theApp.editProjectileTypeId].collection = sel;
    setIntegerNum(sel, &prCollectionNum);
    UpdateData();
}
//seq
void CProjectilePage::OnEnChangeEdit37()
{
    projectile_definitions[theApp.editProjectileTypeId].shape = 
        getIntegerNum(&prSequence);
}
//flags
void CProjectilePage::OnBnClickedCheck5()
{
    int flag = 0;
    for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
        if(prFlags[i].GetCheck()){
            flag |= theApp.projectileFlagInformations[i].bindId;
        }
    }
    projectile_definitions[theApp.editProjectileTypeId].flags = flag;
}
//speed
void CProjectilePage::OnEnChangeEdit5()
{
    projectile_definitions[theApp.editProjectileTypeId].speed =
        getIntegerNum(&prSpeed);
}
//range
void CProjectilePage::OnEnChangeEdit75()
{
    projectile_definitions[theApp.editProjectileTypeId].maximum_range =
        getIntegerNum(&prRange);
}
//pitch
void CProjectilePage::OnEnChangeEdit76()
{
    projectile_definitions[theApp.editProjectileTypeId].sound_pitch =
        getIntegerNum(&prPitch);
    
}
//flyby
void CProjectilePage::OnCbnSelchangeCombo4()
{
    int sel = prFlyBySoundCmb.GetCurSel();
    if( sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    projectile_definitions[theApp.editProjectileTypeId].flyby_sound =
        sel;
    setIntegerNum(sel, &prFlyBySoundNum);
    UpdateData();
}
//bound
void CProjectilePage::OnCbnSelchangeCombo5()
{
    int sel = prBoundSoundCmb.GetCurSel();
    if( sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    projectile_definitions[theApp.editProjectileTypeId].rebound_sound =
        sel;
    setIntegerNum(sel, &prBoundSoundNum);
    UpdateData();
}

//effect
void CProjectilePage::OnCbnSelchangeCombo16()
{
    int sel = prDetonationEffect.GetCurSel();
    if( sel == NUMBER_OF_EFFECT_TYPES){
        sel = -1;
    }
    projectile_definitions[theApp.editProjectileTypeId].detonation_effect =
        sel;
    setIntegerNum(sel, &prDetonationEffectNum);
    UpdateData();
}

//media effect
void CProjectilePage::OnCbnSelchangeCombo29()
{
    int sel = prMediaDetonationEffectCmb.GetCurSel();
    if( sel == NUMBER_OF_EFFECT_TYPES){
        sel = -1;
    }
    projectile_definitions[theApp.editProjectileTypeId].media_detonation_effect =
        sel;
    setIntegerNum(sel, &prMediaDetonationEffectNum);
    UpdateData();
}
//contrail
void CProjectilePage::OnCbnSelchangeCombo30()
{
    int sel = prContrailEffectCmb.GetCurSel();
    if( sel == NUMBER_OF_EFFECT_TYPES){
        sel = -1;
    }
    projectile_definitions[theApp.editProjectileTypeId].contrail_effect =
        sel;
    setIntegerNum(sel, &prContrailEffectNum);
    UpdateData();
}
//damage type
void CProjectilePage::OnCbnSelchangeCombo6()
{
    int sel = prDamageTypeCmb.GetCurSel();
    if( sel == NUMBER_OF_DAMAGE_TYPES){
        sel = -1;
    }
    projectile_definitions[theApp.editProjectileTypeId].damage.type =
        sel;
    setIntegerNum(sel, &prDamageTypeNum);
    UpdateData();
}

void CProjectilePage::OnBnClickedCheck22()
{
    int type = theApp.editProjectileTypeId;
    if(prDamageFlag.GetCheck()){
        projectile_definitions[type].damage.flags = _alien_damage;
    }else{
        projectile_definitions[type].damage.flags = 0;
    }
}

//collection
void CProjectilePage::OnBnClickedButton2()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].collection =
        theApp.projectile_default_definitions[type].collection;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton3()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].shape =
        theApp.projectile_default_definitions[type].shape;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton4()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].detonation_effect =
        theApp.projectile_default_definitions[type].detonation_effect;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton5()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].media_detonation_effect =
        theApp.projectile_default_definitions[type].media_detonation_effect;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton43()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].contrail_effect =
        theApp.projectile_default_definitions[type].contrail_effect;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton44()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].ticks_between_contrails =
        theApp.projectile_default_definitions[type].ticks_between_contrails;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton45()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].maximum_contrails =
        theApp.projectile_default_definitions[type].maximum_contrails;
    setupDialog();
}
//promotion
void CProjectilePage::OnBnClickedButton35()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].media_projectile_promotion =
        theApp.projectile_default_definitions[type].media_projectile_promotion;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton8()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].radius =
        theApp.projectile_default_definitions[type].radius;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton9()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].area_of_effect =
        theApp.projectile_default_definitions[type].area_of_effect;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton38()
{
    int type = theApp.editProjectileTypeId;
    memcpy(&(projectile_definitions[type].damage),
        &(theApp.projectile_default_definitions[type].damage),
        sizeof(struct damage_definition));
    setupDialog();
}

void CProjectilePage::OnBnClickedButton39()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].flags =
        theApp.projectile_default_definitions[type].flags;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton40()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].speed =
        theApp.projectile_default_definitions[type].speed;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton46()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].maximum_range =
        theApp.projectile_default_definitions[type].maximum_range;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton47()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].sound_pitch =
        theApp.projectile_default_definitions[type].sound_pitch;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton48()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].flyby_sound =
        theApp.projectile_default_definitions[type].flyby_sound;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton49()
{
    int type = theApp.editProjectileTypeId;
    projectile_definitions[type].rebound_sound =
        theApp.projectile_default_definitions[type].rebound_sound;
    setupDialog();
}

void CProjectilePage::OnBnClickedButton1()
{
    int type = theApp.editProjectileTypeId;
    memcpy(&(projectile_definitions[type]),
        &(theApp.projectile_default_definitions[type]),
        sizeof(struct projectile_definition));
    setupDialog();
}
//damage base
void CProjectilePage::OnEnChangeEdit80()
{
    projectile_definitions[theApp.editProjectileTypeId].damage.base =
        getIntegerNum(&prDamageBase);
}
//damage random
void CProjectilePage::OnEnChangeEdit81()
{
    projectile_definitions[theApp.editProjectileTypeId].damage.random =
        getIntegerNum(&prDamageRandom);
}
//damage scale
void CProjectilePage::OnEnChangeEdit82()
{
    projectile_definitions[theApp.editProjectileTypeId].damage.scale =
        getIntegerNum(&prDamageScale);
}
//delay interval
void CProjectilePage::OnEnChangeEdit39()
{
    projectile_definitions[theApp.editProjectileTypeId].ticks_between_contrails =
        getIntegerNum(&prTicksBetweenContrail);
}
//contrail
void CProjectilePage::OnEnChangeEdit71()
{
    projectile_definitions[theApp.editProjectileTypeId].maximum_contrails =
        getIntegerNum(&prMaximumContrail);
}
//promotion
void CProjectilePage::OnEnChangeEdit72()
{
    projectile_definitions[theApp.editProjectileTypeId].media_projectile_promotion =
        getIntegerNum(&prMediaProjectilePromotion);
}
//radius
void CProjectilePage::OnEnChangeEdit73()
{
    projectile_definitions[theApp.editProjectileTypeId].radius =
        getIntegerNum(&prRadius);
}
//affect range
void CProjectilePage::OnEnChangeEdit74()
{
    projectile_definitions[theApp.editProjectileTypeId].area_of_effect =
        getIntegerNum(&prAreaOfEffect);
}
