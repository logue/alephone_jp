// MonsterPage2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "MonsterPage2.h"


// CMonsterPage2 ダイアログ

IMPLEMENT_DYNAMIC(CMonsterPage2, CDialog)

CMonsterPage2::CMonsterPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CMonsterPage2::IDD, pParent)
{

}

BOOL CMonsterPage2::OnInitDialog(){
    BOOL ret = CDialog::OnInitDialog();

    //モンスター種類補充
    for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
        monsterTypeCmb.InsertString(i, theApp.monsterInformations[i].jname);
    }
    int type = theApp.editMonsterTypeId;
    monsterTypeCmb.SetCurSel(type);

    //this->setupDialog();

    return ret;
}

CMonsterPage2::~CMonsterPage2()
{
}

void CMonsterPage2::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, monsterTypeCmb);
    DDX_Control(pDX, IDC_EDIT6, monsterTypeNum);
    DDX_Control(pDX, IDC_CHECK49, monsterFlag[0]);
    DDX_Control(pDX, IDC_CHECK50, monsterFlag[1]);
    DDX_Control(pDX, IDC_CHECK51, monsterFlag[2]);
    DDX_Control(pDX, IDC_CHECK52, monsterFlag[3]);
    DDX_Control(pDX, IDC_CHECK53, monsterFlag[4]);
    DDX_Control(pDX, IDC_CHECK54, monsterFlag[5]);
    DDX_Control(pDX, IDC_CHECK55, monsterFlag[6]);
    DDX_Control(pDX, IDC_CHECK56, monsterFlag[7]);
    DDX_Control(pDX, IDC_CHECK107, monsterFlag[8]);
    DDX_Control(pDX, IDC_CHECK57, monsterFlag[9]);
    DDX_Control(pDX, IDC_CHECK58, monsterFlag[10]);
    DDX_Control(pDX, IDC_CHECK59, monsterFlag[11]);
    DDX_Control(pDX, IDC_CHECK60, monsterFlag[12]);
    DDX_Control(pDX, IDC_CHECK61, monsterFlag[13]);
    DDX_Control(pDX, IDC_CHECK62, monsterFlag[14]);
    DDX_Control(pDX, IDC_CHECK63, monsterFlag[15]);
    DDX_Control(pDX, IDC_CHECK64, monsterFlag[16]);
    DDX_Control(pDX, IDC_CHECK65, monsterFlag[17]);
    DDX_Control(pDX, IDC_CHECK66, monsterFlag[18]);
    DDX_Control(pDX, IDC_CHECK67, monsterFlag[19]);
    DDX_Control(pDX, IDC_CHECK68, monsterFlag[20]);
    DDX_Control(pDX, IDC_CHECK69, monsterFlag[21]);
    DDX_Control(pDX, IDC_CHECK70, monsterFlag[22]);
    DDX_Control(pDX, IDC_CHECK72, monsterFlag[23]);
    DDX_Control(pDX, IDC_CHECK73, monsterFlag[24]);
    DDX_Control(pDX, IDC_CHECK74, monsterFlag[25]);
    DDX_Control(pDX, IDC_CHECK75, monsterFlag[26]);
    DDX_Control(pDX, IDC_CHECK76, monsterFlag[27]);

    DDX_Control(pDX, IDC_CHECK1, monsterImmunities[0]);
    DDX_Control(pDX, IDC_CHECK3, monsterImmunities[1]);
    DDX_Control(pDX, IDC_CHECK5, monsterImmunities[2]);
    DDX_Control(pDX, IDC_CHECK7, monsterImmunities[3]);
    DDX_Control(pDX, IDC_CHECK9, monsterImmunities[4]);
    DDX_Control(pDX, IDC_CHECK11, monsterImmunities[5]);
    DDX_Control(pDX, IDC_CHECK13, monsterImmunities[6]);
    DDX_Control(pDX, IDC_CHECK15, monsterImmunities[7]);
    DDX_Control(pDX, IDC_CHECK17, monsterImmunities[8]);
    DDX_Control(pDX, IDC_CHECK19, monsterImmunities[9]);
    DDX_Control(pDX, IDC_CHECK21, monsterImmunities[10]);
    DDX_Control(pDX, IDC_CHECK23, monsterImmunities[11]);
    DDX_Control(pDX, IDC_CHECK77, monsterImmunities[12]);
    DDX_Control(pDX, IDC_CHECK79, monsterImmunities[13]);
    DDX_Control(pDX, IDC_CHECK81, monsterImmunities[14]);
    DDX_Control(pDX, IDC_CHECK83, monsterImmunities[15]);
    DDX_Control(pDX, IDC_CHECK89, monsterImmunities[16]);
    DDX_Control(pDX, IDC_CHECK90, monsterImmunities[17]);
    DDX_Control(pDX, IDC_CHECK87, monsterImmunities[18]);
    DDX_Control(pDX, IDC_CHECK91, monsterImmunities[19]);
    DDX_Control(pDX, IDC_CHECK93, monsterImmunities[20]);
    DDX_Control(pDX, IDC_CHECK95, monsterImmunities[21]);
    DDX_Control(pDX, IDC_CHECK97, monsterImmunities[22]);
    DDX_Control(pDX, IDC_CHECK108, monsterImmunities[23]);

    DDX_Control(pDX, IDC_CHECK2, monsterWeaknesses[0]);
    DDX_Control(pDX, IDC_CHECK4, monsterWeaknesses[1]);
    DDX_Control(pDX, IDC_CHECK6, monsterWeaknesses[2]);
    DDX_Control(pDX, IDC_CHECK8, monsterWeaknesses[3]);
    DDX_Control(pDX, IDC_CHECK10, monsterWeaknesses[4]);
    DDX_Control(pDX, IDC_CHECK12, monsterWeaknesses[5]);
    DDX_Control(pDX, IDC_CHECK14, monsterWeaknesses[6]);
    DDX_Control(pDX, IDC_CHECK16, monsterWeaknesses[7]);
    DDX_Control(pDX, IDC_CHECK18, monsterWeaknesses[8]);
    DDX_Control(pDX, IDC_CHECK20, monsterWeaknesses[9]);
    DDX_Control(pDX, IDC_CHECK22, monsterWeaknesses[10]);
    DDX_Control(pDX, IDC_CHECK24, monsterWeaknesses[11]);
    DDX_Control(pDX, IDC_CHECK78, monsterWeaknesses[12]);
    DDX_Control(pDX, IDC_CHECK80, monsterWeaknesses[13]);
    DDX_Control(pDX, IDC_CHECK82, monsterWeaknesses[14]);
    DDX_Control(pDX, IDC_CHECK84, monsterWeaknesses[15]);
    DDX_Control(pDX, IDC_CHECK85, monsterWeaknesses[16]);
    DDX_Control(pDX, IDC_CHECK86, monsterWeaknesses[17]);
    DDX_Control(pDX, IDC_CHECK88, monsterWeaknesses[18]);
    DDX_Control(pDX, IDC_CHECK92, monsterWeaknesses[19]);
    DDX_Control(pDX, IDC_CHECK94, monsterWeaknesses[20]);
    DDX_Control(pDX, IDC_CHECK96, monsterWeaknesses[21]);
    DDX_Control(pDX, IDC_CHECK98, monsterWeaknesses[22]);
    DDX_Control(pDX, IDC_CHECK109, monsterWeaknesses[23]);

    DDX_Control(pDX, IDC_CHECK25, monsterEnemy[ 0]);
    DDX_Control(pDX, IDC_CHECK27, monsterEnemy[ 1]);
    DDX_Control(pDX, IDC_CHECK31, monsterEnemy[ 2]);
    DDX_Control(pDX, IDC_CHECK33, monsterEnemy[ 3]);
    DDX_Control(pDX, IDC_CHECK35, monsterEnemy[ 4]);
    DDX_Control(pDX, IDC_CHECK37, monsterEnemy[ 5]);
    DDX_Control(pDX, IDC_CHECK39, monsterEnemy[ 6]);
    DDX_Control(pDX, IDC_CHECK41, monsterEnemy[ 7]);
    DDX_Control(pDX, IDC_CHECK43, monsterEnemy[ 8]);
    DDX_Control(pDX, IDC_CHECK45, monsterEnemy[ 9]);
    DDX_Control(pDX, IDC_CHECK47, monsterEnemy[11]);
    DDX_Control(pDX, IDC_CHECK29, monsterEnemy[12]);
    DDX_Control(pDX, IDC_CHECK100, monsterEnemy[13]);
    DDX_Control(pDX, IDC_CHECK102, monsterEnemy[10]);
    DDX_Control(pDX, IDC_CHECK104, monsterEnemy[14]);
    DDX_Control(pDX, IDC_CHECK106, monsterEnemy[15]);

    DDX_Control(pDX, IDC_CHECK26, monsterFriend[ 0]);
    DDX_Control(pDX, IDC_CHECK28, monsterFriend[ 1]);
    DDX_Control(pDX, IDC_CHECK30, monsterFriend[ 2]);
    DDX_Control(pDX, IDC_CHECK32, monsterFriend[ 3]);
    DDX_Control(pDX, IDC_CHECK34, monsterFriend[ 4]);
    DDX_Control(pDX, IDC_CHECK36, monsterFriend[ 5]);
    DDX_Control(pDX, IDC_CHECK38, monsterFriend[ 6]);
    DDX_Control(pDX, IDC_CHECK40, monsterFriend[ 7]);
    DDX_Control(pDX, IDC_CHECK42, monsterFriend[ 8]);
    DDX_Control(pDX, IDC_CHECK44, monsterFriend[ 9]);
    DDX_Control(pDX, IDC_CHECK46, monsterFriend[11]);
    DDX_Control(pDX, IDC_CHECK48, monsterFriend[12]);
    DDX_Control(pDX, IDC_CHECK99, monsterFriend[13]);
    DDX_Control(pDX, IDC_CHECK101, monsterFriend[10]);
    DDX_Control(pDX, IDC_CHECK103, monsterFriend[14]);
    DDX_Control(pDX, IDC_CHECK105, monsterFriend[15]);
}

//上から順にフラグ/耐性/弱点/敵/味方

BEGIN_MESSAGE_MAP(CMonsterPage2, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CMonsterPage2::OnCbnSelchangeCombo1)
    ON_BN_CLICKED(IDC_CHECK49, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK50, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK51, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK52, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK53, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK54, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK55, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK56, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK107, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK57, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK58, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK59, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK60, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK61, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK62, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK63, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK64, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK65, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK66, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK67, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK68, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK69, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK70, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK72, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK73, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK74, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK75, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK76, OnBnClickedCheck3)

    ON_BN_CLICKED(IDC_CHECK1, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK3, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK5, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK7, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK9, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK11, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK13, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK15, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK17, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK19, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK21, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK23, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK77, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK79, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK81, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK83, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK89, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK90, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK87, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK91, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK93, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK95, &CMonsterPage2::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK97, &CMonsterPage2::OnBnClickedCheck1)

    ON_BN_CLICKED(IDC_CHECK2, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK4, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK6, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK8, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK10, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK12, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK14, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK16, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK18, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK20, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK22, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK24, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK78, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK80, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK82, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK84, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK85, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK86, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK88, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK92, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK94, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK96, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK98, &CMonsterPage2::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_BUTTON9, &CMonsterPage2::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON4, &CMonsterPage2::OnBnClickedButton4)

    ON_BN_CLICKED(IDC_CHECK25, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK27, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK31, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK33, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK35, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK37, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK39, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK41, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK43, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK45, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK47, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK29, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK100, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK102, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK104, &CMonsterPage2::OnBnClickedCheck10)
    ON_BN_CLICKED(IDC_CHECK106, &CMonsterPage2::OnBnClickedCheck10)

    ON_BN_CLICKED(IDC_CHECK26, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK28, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK30, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK32, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK34, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK36, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK38, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK40, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK42, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK44, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK46, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK48, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK99, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK101, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK103, &CMonsterPage2::OnBnClickedCheck11)
    ON_BN_CLICKED(IDC_CHECK105, &CMonsterPage2::OnBnClickedCheck11)
    ON_WM_SHOWWINDOW()
    ON_BN_CLICKED(IDC_BUTTON13, &CMonsterPage2::OnBnClickedButton13)
    ON_BN_CLICKED(IDC_BUTTON34, &CMonsterPage2::OnBnClickedButton34)
    END_MESSAGE_MAP()

//耐性ビット更新
void CMonsterPage2::setupImmunities(){
    uint32 bits = this->getImmunitiesBits();
    monster_definitions[theApp.editMonsterTypeId].immunities = bits;
}
//各フラグの状態から耐性ビットを取得
uint32 CMonsterPage2::getImmunitiesBits(){
    uint32 allBits = 0;
    for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
        int bit = monsterImmunities[i].GetCheck();
        if(bit){
            allBits |= FLAG(i);
        }
    }
    return allBits;
}

//弱点ビット更新
void CMonsterPage2::setupWeaknesses(){
    uint32 bits = this->getWeaknessesBits();
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].weaknesses = bits;
}
//各フラグの状態から弱点ビットを取得
uint32 CMonsterPage2::getWeaknessesBits(){
    uint32 allBits = 0;
    for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
        int bit = monsterWeaknesses[i].GetCheck();
        if(bit){
            allBits |= FLAG(i);
        }
    }
    return allBits;
}

//フラグ更新
void CMonsterPage2::setupFlag()
{
    monster_definitions[theApp.editMonsterTypeId].flags = this->getFlagBits();
}
//フラグの状態を統合
uint32 CMonsterPage2::getFlagBits(){
    uint32 allBits = 0;
    for(int i = 0; i < NUMBER_OF_MONSTER_FLAG_INFORMATIONS; i ++){
        int bit = monsterFlag[i].GetCheck();
        if(bit){
            allBits |= FLAG(i);
        }
    }
    return allBits;
}

//敵ビット更新
void CMonsterPage2::setupEnemy()
{
    monster_definitions[theApp.editMonsterTypeId].enemies = this->getEnemyBits();
}
//各フラグの状態から敵ビットを取得
uint32 CMonsterPage2::getEnemyBits()
{
    uint32 allBits = 0;
    for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
        int bit = monsterEnemy[i].GetCheck();
        if(bit){
            allBits |= FLAG(i);
        }
    }
    return allBits;
}

//味方ビット更新
void CMonsterPage2::setupFriend()
{
    monster_definitions[theApp.editMonsterTypeId].friends = this->getFriendBits();
}
//各フラグの状態から味方ビットを取得
uint32 CMonsterPage2::getFriendBits()
{
    uint32 allBits = 0;
    for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
        int bit = monsterFriend[i].GetCheck();
        if(bit){
            allBits |= FLAG(i);
        }
    }
    return allBits;
}

/**
    ダイアログセットアップ
*/
void CMonsterPage2::setupDialog(){
    int type = theApp.editMonsterTypeId;

    //モンスター種類
    setIntegerNum(type, &monsterTypeNum);

    //フラグから状態をセット
    {
        uint32 flags = monster_definitions[type].flags;
        for(int i = 0; i < NUMBER_OF_MONSTER_FLAG_INFORMATIONS; i ++){
            if((flags & theApp.monsterFlags[i].bindId) != 0){
                monsterFlag[i].SetCheck(1);
            }else{
                monsterFlag[i].SetCheck(0);
            }
        }
    }

    //敵味方セット
    {
        uint32 enemies = monster_definitions[type].enemies;
        uint32 friends = monster_definitions[type].friends;
        for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
            if((enemies & theApp.monsterClassInformations[i].bindId) != 0){
                monsterEnemy[i].SetCheck(1);
            }else{
                monsterEnemy[i].SetCheck(0);
            }
            if((friends & theApp.monsterClassInformations[i].bindId) != 0){
                monsterFriend[i].SetCheck(1);
            }else{
                monsterFriend[i].SetCheck(0);
            }
        }
    }

    //耐性・弱点をセット
    {
        uint32 immunities = monster_definitions[type].immunities;
        uint32 weaknesses = monster_definitions[type].weaknesses;
        for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
            if((immunities & FLAG(i)) != 0){
                monsterImmunities[i].SetCheck(1);
            }else{
                monsterImmunities[i].SetCheck(0);
            }
            if((weaknesses & FLAG(i)) != 0){
                monsterWeaknesses[i].SetCheck(1);
            }else{
                monsterWeaknesses[i].SetCheck(0);
            }
        }
    }
}

// CMonsterPage2 メッセージ ハンドラ

//immunities
void CMonsterPage2::OnBnClickedCheck1()
{
    setupImmunities();
}
//weaknesses
void CMonsterPage2::OnBnClickedCheck2()
{
    setupWeaknesses();
}
//flag
void CMonsterPage2::OnBnClickedCheck3()
{
    setupFlag();
}
//enemy
void CMonsterPage2::OnBnClickedCheck10()
{
    setupEnemy();
}

//friend
void CMonsterPage2::OnBnClickedCheck11()
{
    setupFriend();
}

/**
    初期化
*/
void CMonsterPage2::OnBnClickedButton9()
{
    OnBnClickedButton4();
    OnBnClickedButton13();
    OnBnClickedButton34();
}

/**
    耐性/弱点初期化
*/
void CMonsterPage2::OnBnClickedButton4()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].immunities = 
        theApp.monster_default_definitions[type].immunities;
    monster_definitions[type].weaknesses = 
        theApp.monster_default_definitions[type].weaknesses;
    setupDialog();
}

/**
    モンスター種類コンボ
*/
void CMonsterPage2::OnCbnSelchangeCombo1()
{
    int sel = monsterTypeCmb.GetCurSel();
    theApp.editMonsterTypeId = sel;
    this->setupDialog();
}

void CMonsterPage2::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if( bShow == TRUE){
        //更新
        monsterTypeCmb.SetCurSel(theApp.editMonsterTypeId);

        this->setupDialog();
    }
}
//敵・味方初期化ボタン
void CMonsterPage2::OnBnClickedButton13()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].enemies = 
        theApp.monster_default_definitions[type].enemies;
    monster_definitions[type].friends = 
        theApp.monster_default_definitions[type].friends;
    setupDialog();
}
//特徴初期化ボタン
void CMonsterPage2::OnBnClickedButton34()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].flags = 
        theApp.monster_default_definitions[type].flags;
    setupDialog();
}
