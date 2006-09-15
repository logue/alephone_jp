// MonsterPage3.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "MonsterPage3.h"
#include ".\monsterpage3.h"


// CMonsterPage3 ダイアログ

IMPLEMENT_DYNAMIC(CMonsterPage3, CDialog)

CMonsterPage3::CMonsterPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CMonsterPage3::IDD, pParent)
{

}

CMonsterPage3::~CMonsterPage3()
{
}

void CMonsterPage3::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, monsterTypeCmb);
    DDX_Control(pDX, IDC_EDIT6, monsterTypeNum);
    DDX_Control(pDX, IDC_EDIT37, monsterStationalyNum);
    DDX_Control(pDX, IDC_EDIT40, monsterMoving);
    DDX_Control(pDX, IDC_EDIT43, monsterHitting);
    DDX_Control(pDX, IDC_EDIT46, monsterLightDying);
    DDX_Control(pDX, IDC_EDIT49, monsterLightDeath);
    DDX_Control(pDX, IDC_EDIT52, monsterHeavyDying);
    DDX_Control(pDX, IDC_EDIT55, monsterHeavyDeath);
    DDX_Control(pDX, IDC_EDIT58, monsterTeleportIn);
    DDX_Control(pDX, IDC_EDIT61, monsterTeleportOut);
    DDX_Control(pDX, IDC_CHECK1, collectionUnify);
    DDX_Control(pDX, IDC_CHECK71, clutUnify);
    DDX_Control(pDX, IDC_EDIT35, monsterStationalyCollectionNum);
    DDX_Control(pDX, IDC_EDIT34, monsterCollectionNum);
    DDX_Control(pDX, IDC_EDIT1, monsterCLUT);
    DDX_Control(pDX, IDC_COMBO15, monsterCollectionCmb);
}


BEGIN_MESSAGE_MAP(CMonsterPage3, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
    ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON35, OnBnClickedButton35)
    ON_BN_CLICKED(IDC_BUTTON36, OnBnClickedButton36)
    ON_BN_CLICKED(IDC_BUTTON37, OnBnClickedButton37)
    ON_BN_CLICKED(IDC_BUTTON38, OnBnClickedButton38)
    ON_BN_CLICKED(IDC_BUTTON39, OnBnClickedButton39)
    ON_BN_CLICKED(IDC_BUTTON40, OnBnClickedButton40)
    ON_BN_CLICKED(IDC_BUTTON41, OnBnClickedButton41)
    ON_BN_CLICKED(IDC_BUTTON42, OnBnClickedButton42)
    ON_EN_CHANGE(IDC_EDIT37, OnEnChangeEdit37)
    ON_EN_CHANGE(IDC_EDIT40, OnEnChangeEdit40)
    ON_EN_CHANGE(IDC_EDIT43, OnEnChangeEdit43)
    ON_EN_CHANGE(IDC_EDIT46, OnEnChangeEdit46)
    ON_EN_CHANGE(IDC_EDIT49, OnEnChangeEdit49)
    ON_EN_CHANGE(IDC_EDIT52, OnEnChangeEdit52)
    ON_EN_CHANGE(IDC_EDIT55, OnEnChangeEdit55)
    ON_EN_CHANGE(IDC_EDIT58, OnEnChangeEdit58)
    ON_EN_CHANGE(IDC_EDIT61, OnEnChangeEdit61)
    ON_WM_SHOWWINDOW()
    ON_CBN_SELCHANGE(IDC_COMBO15, &CMonsterPage3::OnCbnSelchangeCombo15)
    ON_EN_CHANGE(IDC_EDIT1, &CMonsterPage3::OnEnChangeEdit1)
END_MESSAGE_MAP()

BOOL CMonsterPage3::OnInitDialog()
{
    BOOL ret = CDialog::OnInitDialog();

    //モンスター種類補充
    for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
        monsterTypeCmb.InsertString(i, theApp.monsterInformations[i].jname);
    }
    int type = theApp.editMonsterTypeId;

    //コレクション種類補充
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        monsterCollectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }
    //
    collectionUnify.SetCheck(1);

    //
    clutUnify.SetCheck(1);

    monsterTypeCmb.SetCurSel(type);
    //this->setupDialog();

    return ret;
}
void CMonsterPage3::setupDialog()
{
    //モンスタータイプ
    int type = theApp.editMonsterTypeId;
    setIntegerNum(type, &monsterTypeNum);

    //collection
    int collection = monster_definitions[type].collection;
    int col = GET_COLLECTION(collection);
    setComboNum(col, 0,
        &monsterCollectionNum, &monsterCollectionCmb);
    //clut
    int clut = GET_COLLECTION_CLUT(collection);
    setIntegerNum(clut, &monsterCLUT);

    //stationaly
    setIntegerNum(monster_definitions[type].stationary_shape,
        &monsterStationalyNum);
    //moving
    setIntegerNum(monster_definitions[type].moving_shape,
        &monsterMoving);
    //hit
    setIntegerNum(monster_definitions[type].hit_shapes,
        &monsterHitting);
    //soft
    setIntegerNum(monster_definitions[type].soft_dying_shape,
        &monsterLightDying);
    setIntegerNum(monster_definitions[type].soft_dead_shapes,
        &monsterLightDeath);
    //hard
    setIntegerNum(monster_definitions[type].hard_dying_shape,
        &monsterHeavyDying);
    setIntegerNum(monster_definitions[type].hard_dead_shapes,
        &monsterHeavyDeath);
    //teleport
    setIntegerNum(monster_definitions[type].teleport_in_shape,
        &monsterTeleportIn);
    setIntegerNum(monster_definitions[type].teleport_out_shape,
        &monsterTeleportOut);

    this->UpdateData();
}

// CMonsterPage3 メッセージ ハンドラ

/**
    モンスター種類コンボ
*/
void CMonsterPage3::OnCbnSelchangeCombo1()
{
    theApp.editMonsterTypeId = monsterTypeCmb.GetCurSel();
    setupDialog();
}

/**
    stationaly初期化
*/
void CMonsterPage3::OnBnClickedButton5()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].stationary_shape = 
        theApp.monster_default_definitions[type].stationary_shape;
    setupDialog();
}

/**
    moving
*/
void CMonsterPage3::OnBnClickedButton35()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].moving_shape = 
        theApp.monster_default_definitions[type].moving_shape;
    setupDialog();
}

/**
    hitting
*/
void CMonsterPage3::OnBnClickedButton36()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].hit_shapes = 
        theApp.monster_default_definitions[type].hit_shapes;
    setupDialog();
}
/**
    light dying
*/
void CMonsterPage3::OnBnClickedButton37()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].soft_dying_shape = 
        theApp.monster_default_definitions[type].soft_dying_shape;
    setupDialog();
}
/**
    soft_dead
*/
void CMonsterPage3::OnBnClickedButton38()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].soft_dead_shapes = 
        theApp.monster_default_definitions[type].soft_dead_shapes;
    setupDialog();
}
/**
    hard_dying
*/
void CMonsterPage3::OnBnClickedButton39()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].hard_dying_shape = 
        theApp.monster_default_definitions[type].hard_dying_shape;
    setupDialog();
}
/**
    hard_dead
*/
void CMonsterPage3::OnBnClickedButton40()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].hard_dead_shapes = 
        theApp.monster_default_definitions[type].hard_dead_shapes;
    setupDialog();
}
/**
    teleport in
*/
void CMonsterPage3::OnBnClickedButton41()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].teleport_in_shape = 
        theApp.monster_default_definitions[type].teleport_in_shape;
    setupDialog();
}
/**
    teleport out
*/
void CMonsterPage3::OnBnClickedButton42()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].teleport_out_shape = 
        theApp.monster_default_definitions[type].teleport_out_shape;
    setupDialog();
}

////////////////////////
/**
    stationaly
*/
void CMonsterPage3::OnEnChangeEdit37()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].stationary_shape =
        getIntegerNum(&monsterStationalyNum);
//        BUILD_DESCRIPTOR(monster_definitions[type].collection,
//            GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterStationalyNum)));
}
/**
    moving
*/
void CMonsterPage3::OnEnChangeEdit40()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].moving_shape =
        getIntegerNum(&monsterMoving);
    /*    BUILD_DESCRIPTOR(monster_definitions[type].collection,
            GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterMoving)));
*/}
/**
    hitting
*/
void CMonsterPage3::OnEnChangeEdit43()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[theApp.editMonsterTypeId].hit_shapes =
        getIntegerNum(&monsterHitting);
//        BUILD_DESCRIPTOR(monster_definitions[type].collection,
//            GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterHitting)));
}
/**
    soft_dying
*/
void CMonsterPage3::OnEnChangeEdit46()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[theApp.editMonsterTypeId].soft_dying_shape =
        getIntegerNum(&monsterLightDying);
//        BUILD_DESCRIPTOR(monster_definitions[type].collection,
//            GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterLightDying)));
}
/**
    soft_dead
*/
void CMonsterPage3::OnEnChangeEdit49()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[theApp.editMonsterTypeId].soft_dead_shapes =
        getIntegerNum(&monsterLightDeath);
 //       BUILD_DESCRIPTOR(monster_definitions[type].collection,
 //       GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterLightDeath)));
}
/**
    hard_dying
*/
void CMonsterPage3::OnEnChangeEdit52()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[theApp.editMonsterTypeId].hard_dying_shape =
        getIntegerNum(&monsterHeavyDying);
//        BUILD_DESCRIPTOR(monster_definitions[type].collection,
//        GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterHeavyDying)));
}
/**
    hard_dead
*/
void CMonsterPage3::OnEnChangeEdit55()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[theApp.editMonsterTypeId].hard_dead_shapes =
        getIntegerNum(&monsterHeavyDeath);
//        BUILD_DESCRIPTOR(monster_definitions[type].collection,
//        GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterHeavyDeath)));
}
/**
    teleport in
*/
void CMonsterPage3::OnEnChangeEdit58()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[theApp.editMonsterTypeId].teleport_in_shape =
        getIntegerNum(&monsterTeleportIn);
//        BUILD_DESCRIPTOR(monster_definitions[type].collection,
//        GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterTeleportIn)));
}
/**
    teleport out
*/
void CMonsterPage3::OnEnChangeEdit61()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[theApp.editMonsterTypeId].teleport_out_shape =
        getIntegerNum(&monsterTeleportOut);
//        BUILD_DESCRIPTOR(monster_definitions[type].collection,
//        GET_DESCRIPTOR_SHAPE(getIntegerNum(&monsterTeleportOut)));
}

void CMonsterPage3::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if(bShow == TRUE){
        monsterTypeCmb.SetCurSel(theApp.editMonsterTypeId);

        //
        collectionUnify.SetCheck(1);

        //
        clutUnify.SetCheck(1);

        this->setupDialog();
    }
}

//コレクションいじり
void CMonsterPage3::OnCbnSelchangeCombo15()
{
    int type = theApp.editMonsterTypeId;
    int col = monsterCollectionCmb.GetCurSel();
    int clut = GET_COLLECTION_CLUT(monster_definitions[type].collection);
    monster_definitions[type].collection = BUILD_COLLECTION( col, clut);
    setIntegerNum(col, &monsterCollectionNum);
}

/**
    パレット
*/
void CMonsterPage3::OnEnChangeEdit1()
{
    int type = theApp.editMonsterTypeId;
    int clut = getIntegerNum(&monsterCLUT);
    int col = GET_COLLECTION(monster_definitions[type].collection);
    monster_definitions[type].collection =
        BUILD_COLLECTION(col, clut);
}
