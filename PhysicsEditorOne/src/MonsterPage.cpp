// MonsterPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "MonsterPage.h"
#include "monster_definitions.h"
#include ".\monsterpage.h"


// CMonsterPage ダイアログ

IMPLEMENT_DYNAMIC(CMonsterPage, CDialog)

CMonsterPage::CMonsterPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMonsterPage::IDD, pParent)
{
}

BOOL CMonsterPage::OnInitDialog(){
    CDialog::OnInitDialog();

    //モンスターダイアログセットアップ

    //モンスターコンボボックス用意
    for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
        this->MonsterType.InsertString(i, theApp.monsterInformations[i].jname);
    }

    //コレクションコンボボックス用意
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        this->monsterCollectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }

    //クラスコンボボックス用意
    for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
        this->monsterClassCmb.InsertString(i, theApp.monsterClassInformations[i].jname);
    }

    //アイテムコンボボックス用意
    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
        this->monsterCarryingItemTypeCmb.InsertString(i, theApp.definedItemInformations[i].jname);
    }
    this->monsterCarryingItemTypeCmb.InsertString(NUMBER_OF_DEFINED_ITEMS,
        L"*none*");

    //効果コンボボックス用意
    for(int i = 0; i < NUMBER_OF_EFFECT_TYPES; i ++){
        this->monsterImpactEffect.InsertString(i, theApp.effectInformations[i].jname);
        this->monsterMeleeImpactEffectCmb.InsertString(i, theApp.effectInformations[i].jname);
        this->monsterContrailEffectCmb.InsertString(i, theApp.effectInformations[i].jname);
    }
    this->monsterImpactEffect.InsertString(NUMBER_OF_EFFECT_TYPES,
        L"*none*");
    this->monsterMeleeImpactEffectCmb.InsertString(NUMBER_OF_EFFECT_TYPES,
        L"*none*");
    this->monsterContrailEffectCmb.InsertString(NUMBER_OF_EFFECT_TYPES,
        L"*none*");

    //知能コンボボックス
    for(int i = 0; i < NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS; i ++){
        this->monsterIntelligenceCmb.InsertString(i, theApp.monsterIntelligences[i].jname);
    }

    //速度コンボボックス(指標)
    for(int i = 0; i < NUMBER_OF_SPEED_INFORMATIONS; i ++){
        this->monsterSpeedCmb.InsertString(i, theApp.speeds[i].jname);
    }
    monsterSpeedCmb.InsertString(NUMBER_OF_SPEED_INFORMATIONS, L"*その他*");

    //ドア開閉マスク
    for(int i = 0; i < NUMBER_OF_SPEED_INFORMATIONS; i ++){
        this->monsterDoorRetryMaskCmb.InsertString(i, theApp.monsterDoorRetryMasks[i].jname);
    }
    monsterDoorRetryMaskCmb.InsertString(NUMBER_OF_SPEED_INFORMATIONS, L"*none*");

    //サウンドコンボボックス
    for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
        this->monsterActivateSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        this->monsterFriendlyActivateSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        this->monsterClearSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        this->monsterKillSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        this->monsterApologySoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        this->monsterFriendlyFireSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        this->monsterFramingSoundCmb.InsertString(i, theApp.soundInformations[i].jname);
        monsterRandomSound.InsertString(i, theApp.soundInformations[i].jname);
    }
    this->monsterActivateSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");
    this->monsterFriendlyActivateSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");
    this->monsterClearSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");
    this->monsterKillSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");
    this->monsterApologySoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");
    this->monsterFriendlyFireSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");
    this->monsterFramingSoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");
    monsterRandomSound.InsertString(NUMBER_OF_SOUND_DEFINITIONS, L"*none*");

    this->MonsterType.SetCurSel(theApp.editMonsterTypeId);
    this->setupDialog(theApp.editMonsterTypeId);

    return TRUE;
}

CMonsterPage::~CMonsterPage()
{
}

void CMonsterPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, MonsterType);
    DDX_Control(pDX, IDC_COMBO10, monsterFramingSoundCmb);
    DDX_Control(pDX, IDC_COMBO11, monsterCarryingItemTypeCmb);
    DDX_Control(pDX, IDC_COMBO12, monsterImpactEffect);
    DDX_Control(pDX, IDC_COMBO13, monsterMeleeImpactEffectCmb);
    DDX_Control(pDX, IDC_COMBO14, monsterContrailEffectCmb);
    DDX_Control(pDX, IDC_COMBO17, monsterIntelligenceCmb);
    DDX_Control(pDX, IDC_COMBO18, monsterSpeedCmb);
    DDX_Control(pDX, IDC_COMBO19, monsterDoorRetryMaskCmb);
    DDX_Control(pDX, IDC_COMBO2, monsterCollectionCmb);
    DDX_Control(pDX, IDC_COMBO3, monsterClassCmb);
    DDX_Control(pDX, IDC_COMBO4, monsterActivateSoundCmb);
    DDX_Control(pDX, IDC_COMBO5, monsterFriendlyActivateSoundCmb);
    DDX_Control(pDX, IDC_COMBO6, monsterClearSoundCmb);
    DDX_Control(pDX, IDC_COMBO7, monsterKillSoundCmb);
    DDX_Control(pDX, IDC_COMBO8, monsterApologySoundCmb);
    DDX_Control(pDX, IDC_COMBO9, monsterFriendlyFireSoundCmb);
    DDX_Control(pDX, IDC_EDIT10, monsterFriendlyActivateSoundNum);
    DDX_Control(pDX, IDC_EDIT11, monsterClearSoundNum);
    DDX_Control(pDX, IDC_EDIT12, monsterApologySoundNum);
    DDX_Control(pDX, IDC_EDIT13, monsterKillSoundNum);
    DDX_Control(pDX, IDC_EDIT14, monsterFriendlyFireSoundNum);
    DDX_Control(pDX, IDC_EDIT15, monsterFramingSoundNum);
    DDX_Control(pDX, IDC_EDIT16, monsterRandomSoundNum);
    DDX_Control(pDX, IDC_EDIT17, monsterRandomSoundMaskNum);
    DDX_Control(pDX, IDC_EDIT18, monsterCarryingItemTypeNum);
    DDX_Control(pDX, IDC_EDIT19, monsterRadius);
    DDX_Control(pDX, IDC_EDIT20, monsterHeight);
    DDX_Control(pDX, IDC_EDIT21, monsterPreferredHoverHeight);
    DDX_Control(pDX, IDC_EDIT22, monsterMinimumLedgeDelta);
    DDX_Control(pDX, IDC_EDIT23, monsterMaximumLedgeDelta);
    DDX_Control(pDX, IDC_EDIT24, monsterExternalVelocityScale);
    DDX_Control(pDX, IDC_EDIT25, monsterImpactEffectNum);
    DDX_Control(pDX, IDC_EDIT26, monsterMeleeImpactEffectNum);
    DDX_Control(pDX, IDC_EDIT27, monsterContrailEffectNum);
    DDX_Control(pDX, IDC_EDIT28, monsterDarkVisualArc);
    DDX_Control(pDX, IDC_EDIT29, monsterIntelligence);
    DDX_Control(pDX, IDC_EDIT3, monsterCollectionNumber);
    DDX_Control(pDX, IDC_EDIT30, monsterSpeedNum);
    DDX_Control(pDX, IDC_EDIT31, monsterGravity);
    DDX_Control(pDX, IDC_EDIT32, monsterTerminalSpeedNum);
    DDX_Control(pDX, IDC_EDIT33, monsterDoorRetryMask);
    DDX_Control(pDX, IDC_EDIT36, monsterClut);
    DDX_Control(pDX, IDC_EDIT4, monsterVitality);
    DDX_Control(pDX, IDC_EDIT5, monsterVisualArc);
    DDX_Control(pDX, IDC_EDIT6, monsterTypeNum);
    DDX_Control(pDX, IDC_EDIT7, monsterPitch);
    DDX_Control(pDX, IDC_EDIT8, monsterClass);
    DDX_Control(pDX, IDC_EDIT9, monsterActivateSoundNum);
    DDX_Control(pDX, IDC_COMBO46, monsterRandomSound);
}


BEGIN_MESSAGE_MAP(CMonsterPage, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CMonsterPage::OnEnChangeEdit1)
    ON_BN_CLICKED(IDC_BUTTON1, &CMonsterPage::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMonsterPage::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMonsterPage::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CMonsterPage::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CMonsterPage::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CMonsterPage::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CMonsterPage::OnBnClickedButton7)
    ON_BN_CLICKED(IDC_BUTTON8, &CMonsterPage::OnBnClickedButton8)
    ON_BN_CLICKED(IDC_BUTTON9, &CMonsterPage::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON10, &CMonsterPage::OnBnClickedButton10)
    ON_BN_CLICKED(IDC_BUTTON11, &CMonsterPage::OnBnClickedButton11)
    ON_BN_CLICKED(IDC_BUTTON12, &CMonsterPage::OnBnClickedButton12)
//    ON_BN_CLICKED(IDC_BUTTON13, &CMonsterPage::OnBnClickedButton13)
    ON_BN_CLICKED(IDC_BUTTON14, &CMonsterPage::OnBnClickedButton14)
    ON_BN_CLICKED(IDC_BUTTON15, &CMonsterPage::OnBnClickedButton15)
    ON_BN_CLICKED(IDC_BUTTON16, &CMonsterPage::OnBnClickedButton16)
    ON_BN_CLICKED(IDC_BUTTON17, &CMonsterPage::OnBnClickedButton17)
    ON_BN_CLICKED(IDC_BUTTON18, &CMonsterPage::OnBnClickedButton18)
    ON_BN_CLICKED(IDC_BUTTON19, &CMonsterPage::OnBnClickedButton19)
    ON_BN_CLICKED(IDC_BUTTON20, &CMonsterPage::OnBnClickedButton20)
    ON_BN_CLICKED(IDC_BUTTON21, &CMonsterPage::OnBnClickedButton21)
    ON_BN_CLICKED(IDC_BUTTON22, &CMonsterPage::OnBnClickedButton22)
    ON_BN_CLICKED(IDC_BUTTON23, &CMonsterPage::OnBnClickedButton23)
    ON_BN_CLICKED(IDC_BUTTON24, &CMonsterPage::OnBnClickedButton24)
    ON_BN_CLICKED(IDC_BUTTON25, &CMonsterPage::OnBnClickedButton25)
    ON_BN_CLICKED(IDC_BUTTON26, &CMonsterPage::OnBnClickedButton26)
    ON_BN_CLICKED(IDC_BUTTON27, &CMonsterPage::OnBnClickedButton27)
    ON_BN_CLICKED(IDC_BUTTON28, &CMonsterPage::OnBnClickedButton28)
    ON_BN_CLICKED(IDC_BUTTON29, &CMonsterPage::OnBnClickedButton29)
    ON_BN_CLICKED(IDC_BUTTON30, &CMonsterPage::OnBnClickedButton30)
    ON_BN_CLICKED(IDC_BUTTON31, &CMonsterPage::OnBnClickedButton31)
    ON_BN_CLICKED(IDC_BUTTON32, &CMonsterPage::OnBnClickedButton32)
    ON_BN_CLICKED(IDC_BUTTON33, &CMonsterPage::OnBnClickedButton33)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CMonsterPage::OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO10, OnCbnSelchangeCombo10)
    ON_CBN_SELCHANGE(IDC_COMBO11, &CMonsterPage::OnCbnSelchangeCombo11)
    ON_CBN_SELCHANGE(IDC_COMBO2, &CMonsterPage::OnCbnSelchangeCombo2)
    ON_CBN_SELCHANGE(IDC_COMBO4, OnCbnSelchangeCombo4)
    ON_CBN_SELCHANGE(IDC_COMBO5, OnCbnSelchangeCombo5)
    ON_CBN_SELCHANGE(IDC_COMBO6, OnCbnSelchangeCombo6)
    ON_CBN_SELCHANGE(IDC_COMBO7, OnCbnSelchangeCombo7)
    ON_CBN_SELCHANGE(IDC_COMBO8, OnCbnSelchangeCombo8)
    ON_CBN_SELCHANGE(IDC_COMBO9, OnCbnSelchangeCombo9)
    ON_EN_CHANGE(IDC_EDIT19, OnEnChangeEdit19)
    ON_EN_CHANGE(IDC_EDIT20, &CMonsterPage::OnEnChangeEdit20)
    ON_EN_CHANGE(IDC_EDIT21, &CMonsterPage::OnEnChangeEdit21)
    ON_EN_CHANGE(IDC_EDIT36, &CMonsterPage::OnEnChangeEdit36)
    ON_EN_CHANGE(IDC_EDIT4, &CMonsterPage::OnEnChangeEdit4)
    ON_EN_CHANGE(IDC_EDIT6, &CMonsterPage::OnEnChangeEdit6)
    ON_EN_CHANGE(IDC_EDIT7, &CMonsterPage::OnEnChangeEdit7)
    ON_WM_SHOWWINDOW()
    ON_EN_CHANGE(IDC_EDIT22, OnEnChangeEdit22)
    ON_EN_CHANGE(IDC_EDIT23, OnEnChangeEdit23)
    ON_EN_CHANGE(IDC_EDIT24, OnEnChangeEdit24)
    ON_CBN_SELCHANGE(IDC_COMBO3, &CMonsterPage::OnCbnSelchangeCombo3)
    ON_EN_CHANGE(IDC_EDIT5, &CMonsterPage::OnEnChangeEdit5)
    ON_CBN_SELCHANGE(IDC_COMBO17, &CMonsterPage::OnCbnSelchangeCombo17)
    ON_EN_CHANGE(IDC_EDIT29, &CMonsterPage::OnEnChangeEdit29)
    ON_CBN_SELCHANGE(IDC_COMBO18, &CMonsterPage::OnCbnSelchangeCombo18)
    ON_EN_CHANGE(IDC_EDIT30, &CMonsterPage::OnEnChangeEdit30)
    ON_EN_CHANGE(IDC_EDIT31, &CMonsterPage::OnEnChangeEdit31)
    ON_EN_CHANGE(IDC_EDIT32, &CMonsterPage::OnEnChangeEdit32)
    ON_CBN_SELCHANGE(IDC_COMBO19, &CMonsterPage::OnCbnSelchangeCombo19)
    ON_CBN_SELCHANGE(IDC_COMBO12, &CMonsterPage::OnCbnSelchangeCombo12)
    ON_CBN_SELCHANGE(IDC_COMBO13, &CMonsterPage::OnCbnSelchangeCombo13)
    ON_CBN_SELCHANGE(IDC_COMBO14, &CMonsterPage::OnCbnSelchangeCombo14)
    ON_EN_CHANGE(IDC_EDIT16, &CMonsterPage::OnEnChangeEdit16)
    ON_CBN_SELCHANGE(IDC_COMBO46, &CMonsterPage::OnCbnSelchangeCombo46)
    ON_EN_CHANGE(IDC_EDIT28, &CMonsterPage::OnEnChangeEdit28)
    ON_EN_CHANGE(IDC_EDIT17, &CMonsterPage::OnEnChangeEdit17)
END_MESSAGE_MAP()


// CMonsterPage メッセージ ハンドラ

/**
    MonsterType(disable)
*/
void CMonsterPage::OnEnChangeEdit1()
{}

/**
    MonsterType
*/
void CMonsterPage::OnCbnSelchangeCombo1()
{
    //番号をEditBoxへ反映
    theApp.editMonsterTypeId = MonsterType.GetCurSel();
    this->setupDialog(theApp.editMonsterTypeId);
}



/**
    moster_definitions[]のデータをダイアログアイテムに反映
*/
void CMonsterPage::setupDialog(int type){
    char cstr[256];

    //種類
    sprintf(cstr, "%d", type);
    monsterTypeNum.SetWindowTextW(CString(cstr));

    //モンスター情報を全体へ反映
    //コレクション番号
    int16 collection = monster_definitions[type].collection;
    int16 col = GET_COLLECTION(collection);
    setComboNum(col, -1,
        &monsterCollectionNumber, &monsterCollectionCmb);

    //CLUT
    int clut = GET_COLLECTION_CLUT(collection);
    setIntegerNum(GET_COLLECTION_CLUT(collection),
        &monsterClut);

    //耐久力(Vitality)
    setIntegerNum(monster_definitions[type].vitality,
        &monsterVitality);

    //クラス
    setComboNumBinded(monster_definitions[type]._class,
        NUMBER_OF_CLASS_INFORMATIONS,
        theApp.monsterClassInformations,
        &monsterClass, &monsterClassCmb);


    //半径
    setIntegerNum(monster_definitions[type].radius,
        &monsterRadius);

    //高さ
    setIntegerNum(monster_definitions[type].height,
        &monsterHeight);

    //跳躍
    setIntegerNum(monster_definitions[type].preferred_hover_height,
        &monsterPreferredHoverHeight);

    //最小俯角
    double angle = (double)monster_definitions[type].minimum_ledge_delta;// / FULL_CIRCLE * 360.0;
    setIntegerNum((int)angle,
        &monsterMinimumLedgeDelta);

    //最大俯角
    setIntegerNum(monster_definitions[type].maximum_ledge_delta,
        &monsterMaximumLedgeDelta);

    //速度比率
    setIntegerNum(monster_definitions[type].external_velocity_scale,
        &monsterExternalVelocityScale);

    //所持アイテム
    setComboNum(monster_definitions[type].carrying_item_type,
        NUMBER_OF_DEFINED_ITEMS,
        &monsterCarryingItemTypeNum, &monsterCarryingItemTypeCmb);

    //サウンド-------------
    //ピッチ
    sprintf(cstr, "%d", monster_definitions[type].sound_pitch);
    monsterPitch.SetWindowTextW(CString(cstr));
    //setIntegerNum(monster_definitions[type].sound_pitch,
    //    &monsterPitch);

    //起動
    setComboNum(monster_definitions[type].activation_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterActivateSoundNum, &monsterActivateSoundCmb);

    //味方起動
    setComboNum(monster_definitions[type].friendly_activation_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterFriendlyActivateSoundNum, &monsterFriendlyActivateSoundCmb);

    //一掃
    setComboNum(monster_definitions[type].clear_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterClearSoundNum, &monsterClearSoundCmb);

    //死亡
    setComboNum(monster_definitions[type].kill_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterKillSoundNum, &monsterKillSoundCmb);

    //弁明
    setComboNum(monster_definitions[type].apology_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterApologySoundNum, &monsterApologySoundCmb);

    //誤射
    setComboNum(monster_definitions[type].friendly_fire_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterFriendlyFireSoundNum, &monsterFriendlyFireSoundCmb);

    //燃焼
    setComboNum(monster_definitions[type].flaming_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterFramingSoundNum, &monsterFramingSoundCmb);

    //ランダム音
    setComboNum(monster_definitions[type].random_sound,
        NUMBER_OF_SOUND_DEFINITIONS,
        &monsterRandomSoundNum, &monsterRandomSound);

    //ランダムサウンドマスク
    setIntegerNum(monster_definitions[type].random_sound_mask,
        &monsterRandomSoundMaskNum);

    //------
    //衝撃
    setComboNum(monster_definitions[type].impact_effect,
        NUMBER_OF_EFFECT_TYPES,
        &monsterImpactEffectNum, &monsterImpactEffect);

    //近接衝撃
    setComboNum(monster_definitions[type].melee_impact_effect,
        NUMBER_OF_EFFECT_TYPES,
        &monsterMeleeImpactEffectNum, &monsterMeleeImpactEffectCmb);

    //背後効果
    setComboNum(monster_definitions[type].contrail_effect,
        NUMBER_OF_EFFECT_TYPES,
        &monsterContrailEffectNum, &monsterContrailEffectCmb);

    //視野角
    setIntegerNum(monster_definitions[type].half_visual_arc,
        &monsterVisualArc);

    //縦視野角(間違えた～～～！)
    setIntegerNum(monster_definitions[type].half_vertical_visual_arc,
        &monsterDarkVisualArc);

    //知能
    setComboNumBinded(monster_definitions[type].intelligence, -1,
        (BindInformation*)&theApp.monsterIntelligences, &monsterIntelligence,
        &monsterIntelligenceCmb);

    //速度
    setComboNumBinded(monster_definitions[type].speed, 
        NUMBER_OF_SPEED_INFORMATIONS,
        theApp.speeds,
        &monsterSpeedNum, &monsterSpeedCmb);

    //重力
    setIntegerNum(monster_definitions[type].gravity,
        &monsterGravity);

    //終端速度
    setIntegerNum(monster_definitions[type].terminal_velocity,
        &monsterTerminalSpeedNum);

    //ドア開閉頻度マスク
    setComboNumBinded(monster_definitions[type].door_retry_mask, 
        NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS,
        theApp.monsterDoorRetryMasks,
        &monsterDoorRetryMask, &monsterDoorRetryMaskCmb);

    this->UpdateData();
    
}

void CMonsterPage::OnEnChangeEdit6()
{
    // TODO:  これが RICHEDIT コントロールの場合、
    // まず、CDialog::OnInitDialog() 関数をオーバーライドして、OR 状態の ENM_CHANGE
    // フラグをマスクに入れて、CRichEditCtrl().SetEventMask() を呼び出さない限り、
    // コントロールは、この通知を送信しません。

    // TODO:  ここにコントロール通知ハンドラ コードを追加してください。
}

/**
    Vitality
*/
void CMonsterPage::OnEnChangeEdit4()
{
    // TODO:  これが RICHEDIT コントロールの場合、
    // まず、CDialog::OnInitDialog() 関数をオーバーライドして、OR 状態の ENM_CHANGE
    // フラグをマスクに入れて、CRichEditCtrl().SetEventMask() を呼び出さない限り、
    // コントロールは、この通知を送信しません。

    // TODO:  ここにコントロール通知ハンドラ コードを追加してください。
    
    int type = theApp.editMonsterTypeId;
    
    //バイタリティ値取得
    CString str;
    this->monsterVitality.GetWindowTextW(str);

    char cstr[256];
    //値変更
    strToChar(str, cstr);
    int vitality = atoi(cstr);
    monster_definitions[type].vitality = vitality;
}

void CMonsterPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    // TODO: ここにメッセージ ハンドラ コードを追加します。
    if(bShow == TRUE){
        //Typeコンボボックスを自動で選択し、状態を更新します
        this->MonsterType.SetCurSel(theApp.editMonsterTypeId);

        //状態更新
        this->setupDialog(theApp.editMonsterTypeId);
    }
}

/**
    コレクションコンボ
*/
void CMonsterPage::OnCbnSelchangeCombo2()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int sel = this->monsterCollectionCmb.GetCurSel();
    setIntegerNum(sel, &monsterCollectionNumber);
    UpdateData();

    //データ変更
    int type = theApp.editMonsterTypeId;

    int clut = getIntegerNum(&monsterClut);
    int col = sel;
    int collection = BUILD_COLLECTION(col, clut);
    monster_definitions[type].collection = collection;

    //シークェンス情報を全て設定する
    /*monster_definitions[type].stationary_shape = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].stationary_shape));
    monster_definitions[type].moving_shape = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].moving_shape));
    monster_definitions[type].hit_shapes = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].hit_shapes));
    monster_definitions[type].soft_dying_shape = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].soft_dying_shape));
    monster_definitions[type].soft_dead_shapes = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].soft_dead_shapes));
    monster_definitions[type].hard_dying_shape = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].hard_dying_shape));
    monster_definitions[type].hard_dead_shapes = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].hard_dead_shapes));
    monster_definitions[type].teleport_in_shape = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].teleport_in_shape));
    monster_definitions[type].teleport_out_shape = BUILD_DESCRIPTOR(collection,
        GET_DESCRIPTOR_SHAPE(monster_definitions[type].teleport_out_shape));
        */
}

/**
    CLUT Edit Box
*/
void CMonsterPage::OnEnChangeEdit36()
{
    char cstr[256];
    CString str;
    this->monsterCollectionNumber.GetWindowTextW(str);
    strToChar(str, cstr);
    int col = atoi(cstr);
    this->monsterClut.GetWindowTextW(str);
    strToChar(str, cstr);
    int clut = atoi(cstr);

    int type = theApp.editMonsterTypeId;
    monster_definitions[type].collection = BUILD_COLLECTION(col, clut);
}


/**
    半径
*/
void CMonsterPage::OnEnChangeEdit19()
{
    // TODO :  これが RICHEDIT コントロールの場合、まず、CDialog::OnInitDialog() 関数をオーバーライドして、
    // OR 状態の ENM_CORRECTTEXT フラグをマスクに入れて、
    // CRichEditCtrl().SetEventMask() を呼び出さない限り、
    // コントロールは、この通知を送信しません。

    // TODO :  ここにコントロール通知ハンドラ コードを追加してください。
    char cstr[256];
    CString str;
    this->monsterRadius.GetWindowTextW(str);
    strToChar(str, cstr);
    int radius = atoi(cstr);
    monster_definitions[theApp.editMonsterTypeId].radius = radius;
}

/**
    高さ
*/
void CMonsterPage::OnEnChangeEdit20()
{
    // TODO:  これが RICHEDIT コントロールの場合、
    // まず、CDialog::OnInitDialog() 関数をオーバーライドして、OR 状態の ENM_CHANGE
    // フラグをマスクに入れて、CRichEditCtrl().SetEventMask() を呼び出さない限り、
    // コントロールは、この通知を送信しません。

    // TODO:  ここにコントロール通知ハンドラ コードを追加してください。
    char cstr[256];
    CString str;
    this->monsterHeight.GetWindowTextW(str);
    strToChar(str, cstr);
    int height = atoi(cstr);
    monster_definitions[theApp.editMonsterTypeId].height = height;
}

/**
    可能跳躍
*/
void CMonsterPage::OnEnChangeEdit21()
{
    // TODO:  これが RICHEDIT コントロールの場合、
    // まず、CDialog::OnInitDialog() 関数をオーバーライドして、OR 状態の ENM_CHANGE
    // フラグをマスクに入れて、CRichEditCtrl().SetEventMask() を呼び出さない限り、
    // コントロールは、この通知を送信しません。

    // TODO:  ここにコントロール通知ハンドラ コードを追加してください。
    char cstr[256];
    CString str;
    this->monsterPreferredHoverHeight.GetWindowTextW(str);
    strToChar(str, cstr);
    int preHeight = atoi(cstr);
    monster_definitions[theApp.editMonsterTypeId].preferred_hover_height = preHeight;
}

/**
    コレクション初期化
*/
void CMonsterPage::OnBnClickedButton2()
{
    //コレクション番号を元に戻す
    int type = theApp.editMonsterTypeId;
    int col = GET_COLLECTION(theApp.monster_default_definitions[type].collection);
    int clut = GET_COLLECTION_CLUT(monster_definitions[type].collection);
    monster_definitions[type].collection = BUILD_COLLECTION(col, clut);

    this->setupDialog(type);
}
/**
    パレット初期化
*/
void CMonsterPage::OnBnClickedButton3()
{
    //パレット番号を元に戻す
    int type = theApp.editMonsterTypeId;
    int col = GET_COLLECTION(monster_definitions[type].collection);
    int clut = GET_COLLECTION_CLUT(theApp.monster_default_definitions[type].collection);
    monster_definitions[type].collection = BUILD_COLLECTION(col, clut);

    this->setupDialog(type);
}
/**
    バイタリティ初期化
*/
void CMonsterPage::OnBnClickedButton4()
{
    int type = theApp.editMonsterTypeId;
    int vitality = theApp.monster_default_definitions[type].vitality;
    monster_definitions[type].vitality = vitality;
    this->setupDialog(type);
}
/**
    種類初期化
*/
void CMonsterPage::OnBnClickedButton5()
{
    int type = theApp.editMonsterTypeId;
    int cls = theApp.monster_default_definitions[type]._class;
    monster_definitions[type]._class = cls;
    this->setupDialog(type);
}
/**
    半径初期化
*/
void CMonsterPage::OnBnClickedButton6()
{
    int type = theApp.editMonsterTypeId;
    int r = theApp.monster_default_definitions[type].radius;
    monster_definitions[type].radius = r;
    this->setupDialog(type);
}
/**
    高さ初期化
*/
void CMonsterPage::OnBnClickedButton7()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].height = theApp.monster_default_definitions[type].height;
    this->setupDialog(type);
}
/**
    可能跳躍高度初期化
*/
void CMonsterPage::OnBnClickedButton8()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].preferred_hover_height = theApp.monster_default_definitions[type].preferred_hover_height;
    this->setupDialog(type);
}
/**
    最小俯角初期化
*/
void CMonsterPage::OnBnClickedButton9()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].minimum_ledge_delta =
        theApp.monster_default_definitions[type].minimum_ledge_delta;
    this->setupDialog(type);
}
/**
    最大俯角初期化
*/
void CMonsterPage::OnBnClickedButton10()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].maximum_ledge_delta =
        theApp.monster_default_definitions[type].maximum_ledge_delta;
    this->setupDialog(type);
}
/**
    速度比率初期化
*/
void CMonsterPage::OnBnClickedButton11()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].external_velocity_scale = theApp.monster_default_definitions[type].external_velocity_scale;
    this->setupDialog(type);
}
/**
    所持アイテム初期化
*/
void CMonsterPage::OnBnClickedButton12()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].carrying_item_type = theApp.monster_default_definitions[type].carrying_item_type;
    this->setupDialog(type);
}

/**
    ピッチ
*/
void CMonsterPage::OnBnClickedButton14()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].sound_pitch =
        theApp.monster_default_definitions[type].sound_pitch;
    this->setupDialog(type);
}
/**
    起動音
*/
void CMonsterPage::OnBnClickedButton15()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].activation_sound =
        theApp.monster_default_definitions[type].activation_sound;
    this->setupDialog(type);

}
/**
    味方起動音
*/
void CMonsterPage::OnBnClickedButton16()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].friendly_activation_sound =
        theApp.monster_default_definitions[type].friendly_activation_sound;
    this->setupDialog(type);
}
/**
    起動音
*/
void CMonsterPage::OnBnClickedButton17()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].activation_sound =
        theApp.monster_default_definitions[type].activation_sound;
    this->setupDialog(type);
}
/**
    死亡音
*/
void CMonsterPage::OnBnClickedButton18()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].activation_sound =
        theApp.monster_default_definitions[type].activation_sound;
    this->setupDialog(type);
}
/**
    弁明音
*/
void CMonsterPage::OnBnClickedButton19()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].apology_sound =
        theApp.monster_default_definitions[type].apology_sound;
    this->setupDialog(type);
}
/**
    誤射音
*/
void CMonsterPage::OnBnClickedButton20()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].friendly_fire_sound =
        theApp.monster_default_definitions[type].friendly_fire_sound;
    this->setupDialog(type);
}
/**
    燃焼音
*/
void CMonsterPage::OnBnClickedButton21()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].flaming_sound =
        theApp.monster_default_definitions[type].flaming_sound;
    this->setupDialog(type);
}
/**
    ランダム音
*/
void CMonsterPage::OnBnClickedButton22()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].random_sound =
        theApp.monster_default_definitions[type].random_sound;
    this->setupDialog(type);
}
/**
    ランダム音マスク
*/
void CMonsterPage::OnBnClickedButton23()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].random_sound_mask =
        theApp.monster_default_definitions[type].random_sound_mask;
    this->setupDialog(type);
}
/**
    衝撃効果
*/
void CMonsterPage::OnBnClickedButton24()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].impact_effect =
        theApp.monster_default_definitions[type].impact_effect;
    this->setupDialog(type);
}
/**
    近距離効果
*/
void CMonsterPage::OnBnClickedButton25()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].melee_impact_effect =
        theApp.monster_default_definitions[type].melee_impact_effect;
    this->setupDialog(type);
}
/**
    背後効果
*/
void CMonsterPage::OnBnClickedButton26()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].contrail_effect =
        theApp.monster_default_definitions[type].contrail_effect;
    this->setupDialog(type);
}
/**
    横視野角
*/
void CMonsterPage::OnBnClickedButton27()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].half_visual_arc =
        theApp.monster_default_definitions[type].half_visual_arc;
    this->setupDialog(type);
}
/**
    縦視野角
*/
void CMonsterPage::OnBnClickedButton28()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].half_vertical_visual_arc =
        theApp.monster_default_definitions[type].half_vertical_visual_arc;
    this->setupDialog(type);
}
/**
    知能
*/
void CMonsterPage::OnBnClickedButton29()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].intelligence=
        theApp.monster_default_definitions[type].intelligence;
    this->setupDialog(type);
}
/**
    速度
*/
void CMonsterPage::OnBnClickedButton30()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].speed=
        theApp.monster_default_definitions[type].speed;
    this->setupDialog(type);
}
/**
    重力
*/
void CMonsterPage::OnBnClickedButton31()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].gravity =
        theApp.monster_default_definitions[type].gravity;
    this->setupDialog(type);
}
/**
    終端速度
*/
void CMonsterPage::OnBnClickedButton32()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].terminal_velocity =
        theApp.monster_default_definitions[type].terminal_velocity;
    this->setupDialog(type);
}
/**
    開閉頻度マスク
*/
void CMonsterPage::OnBnClickedButton33()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].door_retry_mask =
        theApp.monster_default_definitions[type].door_retry_mask;
    this->setupDialog(type);
}

/**
    このページ全て初期化
*/
void CMonsterPage::OnBnClickedButton1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    //全部呼び出す
    OnBnClickedButton2();
    OnBnClickedButton3();
    OnBnClickedButton4();
    OnBnClickedButton5();
    OnBnClickedButton6();
    OnBnClickedButton7();
    OnBnClickedButton8();
    OnBnClickedButton9();
    OnBnClickedButton10();
    OnBnClickedButton11();
    OnBnClickedButton12();
//    OnBnClickedButton13();
    OnBnClickedButton14();
    OnBnClickedButton15();
    OnBnClickedButton16();
    OnBnClickedButton17();
    OnBnClickedButton18();
    OnBnClickedButton19();
    OnBnClickedButton20();
    OnBnClickedButton21();
    OnBnClickedButton22();
    OnBnClickedButton23();
    OnBnClickedButton24();
    OnBnClickedButton25();
    OnBnClickedButton26();
    
}

/**
    所持アイテム
*/
void CMonsterPage::OnCbnSelchangeCombo11()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int sel = this->monsterCarryingItemTypeCmb.GetCurSel();

    //データ変更
    int type = theApp.editMonsterTypeId;
    //コンボボックスはmaxが無しに当たるが、データは-1が無しに当たる
    if( sel == NUMBER_OF_DEFINED_ITEMS){
        sel = -1;
    }
    monster_definitions[type].carrying_item_type = sel;
    this->setupDialog(type);
}

/**
    ピッチ
*/
void CMonsterPage::OnEnChangeEdit7()
{
    // TODO:  これが RICHEDIT コントロールの場合、
    // まず、CDialog::OnInitDialog() 関数をオーバーライドして、OR 状態の ENM_CHANGE
    // フラグをマスクに入れて、CRichEditCtrl().SetEventMask() を呼び出さない限り、
    // コントロールは、この通知を送信しません。

    // TODO:  ここにコントロール通知ハンドラ コードを追加してください。
    char cstr[256];
    CString str;
    this->monsterPitch.GetWindowTextW(str);
    strToChar(str, cstr);
    _fixed pitch = atoi(cstr);
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].sound_pitch = pitch;
}


/**
    起動音コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo4()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    int type = theApp.editMonsterTypeId;
    int soundId = this->monsterActivateSoundCmb.GetCurSel();
    if( soundId == NUMBER_OF_SOUND_DEFINITIONS){
        soundId = -1;
    }
    monster_definitions[type].activation_sound = soundId;
    setIntegerNum(soundId, &monsterActivateSoundNum);
    UpdateData();
}

/**
    味方起動コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo5()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    int type = theApp.editMonsterTypeId;
    int soundId = this->monsterFriendlyActivateSoundCmb.GetCurSel();
    if( soundId == NUMBER_OF_SOUND_DEFINITIONS){
        soundId = -1;
    }
    monster_definitions[type].friendly_activation_sound = soundId;
    setIntegerNum(soundId, &monsterFriendlyActivateSoundNum);
    UpdateData();
}

/**
    一掃音コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo6()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    int type = theApp.editMonsterTypeId;
    int soundId = this->monsterClearSoundCmb.GetCurSel();
    if( soundId == NUMBER_OF_SOUND_DEFINITIONS){
        soundId = -1;
    }
    monster_definitions[type].clear_sound = soundId;
    setIntegerNum(soundId, &monsterClearSoundNum);
    UpdateData();
}

/**
    死亡音コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo7()
{
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    int type = theApp.editMonsterTypeId;
    int soundId = this->monsterKillSoundCmb.GetCurSel();
    if( soundId == NUMBER_OF_SOUND_DEFINITIONS){
        soundId = -1;
    }
    monster_definitions[type].kill_sound = soundId;
    setIntegerNum(soundId, &monsterKillSoundNum);
    UpdateData();
}

/**
    弁明音コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo8()
{
    int type = theApp.editMonsterTypeId;
    int soundId = this->monsterApologySoundCmb.GetCurSel();
    if( soundId == NUMBER_OF_SOUND_DEFINITIONS){
        soundId = -1;
    }
    monster_definitions[type].apology_sound = soundId;
    setIntegerNum(soundId, &monsterApologySoundNum);
    UpdateData();
}

/**
    誤射音コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo9()
{
    int type = theApp.editMonsterTypeId;
    int soundId = this->monsterFriendlyFireSoundCmb.GetCurSel();
    if( soundId == NUMBER_OF_SOUND_DEFINITIONS){
        soundId = -1;
    }
    monster_definitions[type].friendly_fire_sound = soundId;
    this->setupDialog(type);
}

/**
    燃焼音
*/
void CMonsterPage::OnCbnSelchangeCombo10()
{
    int type = theApp.editMonsterTypeId;
    int soundId = this->monsterFramingSoundCmb.GetCurSel();
    if( soundId == NUMBER_OF_SOUND_DEFINITIONS){
        soundId = -1;
    }
    monster_definitions[type].flaming_sound = soundId;
    setIntegerNum(soundId, &monsterFramingSoundNum);
    UpdateData();
}

/**
    最小俯角
*/
void CMonsterPage::OnEnChangeEdit22()
{
    int angle = getIntegerNum(&monsterMinimumLedgeDelta);
    //double min_ledge = (double)angle / 360.0 * FULL_CIRCLE;
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].minimum_ledge_delta =
        (int)angle;
}

/**
    最大俯角
*/
void CMonsterPage::OnEnChangeEdit23()
{
    char cstr[256];
    CString str;
    this->monsterMaximumLedgeDelta.GetWindowTextW(str);
    strToChar(str, cstr);
    int max_ledge = atoi(cstr);
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].maximum_ledge_delta = max_ledge;
}

/**
    速度比率
*/
void CMonsterPage::OnEnChangeEdit24()
{
    char cstr[256];
    CString str;
    this->monsterExternalVelocityScale.GetWindowTextW(str);
    strToChar(str, cstr);
    _fixed speed = atoi(cstr);
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].external_velocity_scale = speed;
}

/**
    クラスコンボ
*/
void CMonsterPage::OnCbnSelchangeCombo3()
{
    int type = theApp.editMonsterTypeId;
    int sel = this->monsterClassCmb.GetCurSel();
    //値変更
    monster_definitions[type]._class = 
        theApp.monsterClassInformations[sel].bindId;
    setIntegerNum(sel, &monsterClass);
    UpdateData();
}

/**
    横視野角
*/
void CMonsterPage::OnEnChangeEdit5()
{
    int type = theApp.editMonsterTypeId;
    CString str;
    this->monsterVisualArc.GetWindowTextW(str);
    char cstr[256];
    strToChar(str, cstr);
    monster_definitions[type].half_visual_arc = atoi(cstr);
}

/**
    知能コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo17()
{
    int type = theApp.editMonsterTypeId;
    int sel = monsterIntelligenceCmb.GetCurSel();
    monster_definitions[type].intelligence =
        theApp.monsterIntelligences[sel].bindId;
    setIntegerNum(monster_definitions[type].intelligence, &monsterClass);
    UpdateData();
}

/**
    知能
*/
void CMonsterPage::OnEnChangeEdit29()
{
    //nope
}

/**
    速度コンボ
*/
void CMonsterPage::OnCbnSelchangeCombo18()
{
    int type = theApp.editMonsterTypeId;
    int sel = monsterSpeedCmb.GetCurSel();
    if( sel == NUMBER_OF_SPEED_INFORMATIONS){
        
    }else{
        int num = theApp.speeds[sel].bindId;
        monster_definitions[type].speed = num;
        setIntegerNum(num, &monsterSpeedNum);
        UpdateData();
    }
}

/**
    速度
*/
void CMonsterPage::OnEnChangeEdit30()
{
    int type = theApp.editMonsterTypeId;
    int speed = getIntegerNum(&monsterSpeedNum);
    monster_definitions[type].speed = speed;
    int sel = monsterSpeedCmb.GetCurSel();
    int index = NUMBER_OF_SPEED_INFORMATIONS;
    for(int i = 0; i < NUMBER_OF_SPEED_INFORMATIONS; i ++){
        if(speed == theApp.speeds[i].bindId){
            index = i;
            break;
        }
    }
    if(index != sel && sel < NUMBER_OF_SPEED_INFORMATIONS){
        //bind数値からはずれた
        monsterSpeedCmb.SetCurSel(NUMBER_OF_SPEED_INFORMATIONS);
    }else if(sel == NUMBER_OF_SPEED_INFORMATIONS &&
        index < NUMBER_OF_SPEED_INFORMATIONS){
        //もともとその他がbind数値になった
        monsterSpeedCmb.SetCurSel(index);
    }else if(sel != index && index < NUMBER_OF_SPEED_INFORMATIONS &&
        sel < NUMBER_OF_SPEED_INFORMATIONS){
        //別のものになった
        monsterSpeedCmb.SetCurSel(index);
    }//あとはその他→その他、インデックス→インデックスなので無視
    //そうしないとループに入る
}

/**
    重力
*/
void CMonsterPage::OnEnChangeEdit31()
{
    monster_definitions[theApp.editMonsterTypeId].gravity =
        getIntegerNum(&monsterGravity);
}

/**
    終端速度
*/
void CMonsterPage::OnEnChangeEdit32()
{
    monster_definitions[theApp.editMonsterTypeId].terminal_velocity =
        getIntegerNum(&monsterTerminalSpeedNum);
}

/**
    ドア開閉試行マスクコンボ
*/
void CMonsterPage::OnCbnSelchangeCombo19()
{
    int sel = monsterDoorRetryMaskCmb.GetCurSel();
    int type = theApp.editMonsterTypeId;
    int num = theApp.monsterDoorRetryMasks[sel].bindId;
    monster_definitions[type].door_retry_mask = num;
    setIntegerNum(num, &monsterDoorRetryMask);
    UpdateData();
}
//衝撃効果
void CMonsterPage::OnCbnSelchangeCombo12()
{
    int type = theApp.editMonsterTypeId;
    int sel = monsterImpactEffect.GetCurSel();
    if( sel == NUMBER_OF_EFFECT_TYPES){
        sel = -1;
    }
    monster_definitions[type].impact_effect = sel;
    //値設定
    setIntegerNum(sel, &monsterImpactEffectNum);
    UpdateData();
}
//近接効果
void CMonsterPage::OnCbnSelchangeCombo13()
{
    int sel = monsterMeleeImpactEffectCmb.GetCurSel();
    if( sel == NUMBER_OF_EFFECT_TYPES){
        sel = -1;
    }
    monster_definitions[theApp.editMonsterTypeId].melee_impact_effect =
        sel;
    //値設定
    setIntegerNum(sel, &monsterMeleeImpactEffectNum);
    UpdateData();
}
//背後効果
void CMonsterPage::OnCbnSelchangeCombo14()
{
    int sel = monsterContrailEffectCmb.GetCurSel();
    if( sel == NUMBER_OF_EFFECT_TYPES){
        sel = -1;
    }
    monster_definitions[theApp.editMonsterTypeId].contrail_effect=
        sel;
    //値設定
    setIntegerNum(sel, &monsterContrailEffectNum);
    UpdateData();
}

//random sound disable
void CMonsterPage::OnEnChangeEdit16()
{
}
//random sound cmb
void CMonsterPage::OnCbnSelchangeCombo46()
{
    int sel = monsterRandomSound.GetCurSel();
    if(sel == NUMBER_OF_SOUND_DEFINITIONS){
        sel = -1;
    }
    monster_definitions[theApp.editMonsterTypeId].random_sound =
        sel;
    setIntegerNum(sel, &monsterRandomSoundNum);
    UpdateData();
}
//縦視野角
void CMonsterPage::OnEnChangeEdit28()
{
    monster_definitions[theApp.editMonsterTypeId].half_vertical_visual_arc =
        getIntegerNum(&monsterDarkVisualArc);
}
//random sound mask
void CMonsterPage::OnEnChangeEdit17()
{
    monster_definitions[theApp.editMonsterTypeId].random_sound_mask =
        getIntegerNum(&monsterRandomSoundMaskNum);
}
