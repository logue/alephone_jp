// MonsterPage4.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "MonsterPage4.h"


// CMonsterPage4 �_�C�A���O

IMPLEMENT_DYNAMIC(CMonsterPage4, CDialog)

CMonsterPage4::CMonsterPage4(CWnd* pParent /*=NULL*/)
	: CDialog(CMonsterPage4::IDD, pParent)
{

}

CMonsterPage4::~CMonsterPage4()
{
}

void CMonsterPage4::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, monsterType);
    DDX_Control(pDX, IDC_EDIT6, monsterTypeNum);
    DDX_Control(pDX, IDC_EDIT1, monsterAttackFrequency);
    DDX_Control(pDX, IDC_COMBO15, monsterMeleeType);
    DDX_Control(pDX, IDC_EDIT2, monsterMeleeTypeNum);
    DDX_Control(pDX, IDC_EDIT37, monsterMeleeRepeat);
    DDX_Control(pDX, IDC_EDIT39, monsterMeleeError);
    DDX_Control(pDX, IDC_EDIT40, monsterMeleeRange);
    DDX_Control(pDX, IDC_EDIT62, monsterMeleeSequence);
    DDX_Control(pDX, IDC_EDIT63, monsterMeleeDeltaX);
    DDX_Control(pDX, IDC_EDIT64, monsterMeleeDeltaY);
    DDX_Control(pDX, IDC_EDIT65, monsterMeleeDeltaZ);
    DDX_Control(pDX, IDC_EDIT34, monsterAwayTypeNum);
    DDX_Control(pDX, IDC_COMBO28, monsterAwayTypeCmb);
    DDX_Control(pDX, IDC_EDIT38, monsterAwayRepeat);
    DDX_Control(pDX, IDC_EDIT66, monsterAwayError);
    DDX_Control(pDX, IDC_EDIT41, monsterAwayRange);
    DDX_Control(pDX, IDC_EDIT67, monsterAwaySequence);
    DDX_Control(pDX, IDC_EDIT68, monsterAwayDeltaX);
    DDX_Control(pDX, IDC_EDIT69, monsterAwayDeltaY);
    DDX_Control(pDX, IDC_EDIT70, monsterAwayDeltaZ);
}


BEGIN_MESSAGE_MAP(CMonsterPage4, CDialog)
    ON_WM_SHOWWINDOW()
    ON_CBN_SELCHANGE(IDC_COMBO1, &CMonsterPage4::OnCbnSelchangeCombo1)
    ON_BN_CLICKED(IDC_BUTTON1, &CMonsterPage4::OnBnClickedButton1)
    ON_CBN_SELCHANGE(IDC_COMBO15, &CMonsterPage4::OnCbnSelchangeCombo15)
    ON_BN_CLICKED(IDC_BUTTON2, &CMonsterPage4::OnBnClickedButton2)
    ON_CBN_SELCHANGE(IDC_COMBO28, &CMonsterPage4::OnCbnSelchangeCombo28)
    ON_BN_CLICKED(IDC_BUTTON3, &CMonsterPage4::OnBnClickedButton3)
    ON_EN_CHANGE(IDC_EDIT1, &CMonsterPage4::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT37, &CMonsterPage4::OnEnChangeEdit37)
    ON_EN_CHANGE(IDC_EDIT39, &CMonsterPage4::OnEnChangeEdit39)
    ON_EN_CHANGE(IDC_EDIT40, &CMonsterPage4::OnEnChangeEdit40)
    ON_EN_CHANGE(IDC_EDIT62, &CMonsterPage4::OnEnChangeEdit62)
    ON_EN_CHANGE(IDC_EDIT63, &CMonsterPage4::OnEnChangeEdit63)
    ON_EN_CHANGE(IDC_EDIT64, &CMonsterPage4::OnEnChangeEdit64)
    ON_EN_CHANGE(IDC_EDIT65, &CMonsterPage4::OnEnChangeEdit65)
    ON_EN_CHANGE(IDC_EDIT38, &CMonsterPage4::OnEnChangeEdit38)
    ON_EN_CHANGE(IDC_EDIT66, &CMonsterPage4::OnEnChangeEdit66)
    ON_EN_CHANGE(IDC_EDIT41, &CMonsterPage4::OnEnChangeEdit41)
    ON_EN_CHANGE(IDC_EDIT67, &CMonsterPage4::OnEnChangeEdit67)
    ON_EN_CHANGE(IDC_EDIT68, &CMonsterPage4::OnEnChangeEdit68)
    ON_EN_CHANGE(IDC_EDIT69, &CMonsterPage4::OnEnChangeEdit69)
    ON_EN_CHANGE(IDC_EDIT70, &CMonsterPage4::OnEnChangeEdit70)
END_MESSAGE_MAP()

BOOL CMonsterPage4::OnInitDialog()
{
    BOOL ret = CDialog::OnInitDialog();

    //�����X�^�[�^�C�v�R���{�Z�b�g�A�b�v
    for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
        monsterType.InsertString(i, theApp.monsterInformations[i].jname);
    }
    monsterType.SetCurSel(theApp.editMonsterTypeId);

    //�U���^�C�v���v���W�F�N�e�B����� ��[
    for(int i = 0; i < NUMBER_OF_PROJECTILE_TYPES; i ++){
        monsterMeleeType.InsertString(i, theApp.projectileInformations[i].jname);
        monsterAwayTypeCmb.InsertString(i, theApp.projectileInformations[i].jname);
    }
    monsterMeleeType.InsertString(NUMBER_OF_PROJECTILE_TYPES, L"*none*");
    monsterAwayTypeCmb.InsertString(NUMBER_OF_PROJECTILE_TYPES, L"*none*");

    setupDialog();

    return ret;
}
void CMonsterPage4::setupDialog()
{
    int type = theApp.editMonsterTypeId;

    //���
    setIntegerNum(type, &monsterTypeNum);

    //�p�x
    setIntegerNum(monster_definitions[type].attack_frequency,
        &monsterAttackFrequency);

    //�ߋ���
    //���
    setComboNum(monster_definitions[type].melee_attack.type,
        NUMBER_OF_PROJECTILE_TYPES, 
        &monsterMeleeTypeNum, &monsterMeleeType);
    //�J��Ԃ�
    setIntegerNum(monster_definitions[type].melee_attack.repetitions,
        &monsterMeleeRepeat);
    //�G���[
    setIntegerNum(monster_definitions[type].melee_attack.error,
        &monsterMeleeError);
    //�͈�
    setIntegerNum(monster_definitions[type].melee_attack.range,
        &monsterMeleeRange);
    //Seq
    setIntegerNum(monster_definitions[type].melee_attack.attack_shape,
        &monsterMeleeSequence);
    //X
    setIntegerNum(monster_definitions[type].melee_attack.dx,
        &monsterMeleeDeltaX);
    //Y
    setIntegerNum(monster_definitions[type].melee_attack.dy,
        &monsterMeleeDeltaY);
    //Z
    setIntegerNum(monster_definitions[type].melee_attack.dz,
        &monsterMeleeDeltaZ);

    //������
    //���
    setComboNum(monster_definitions[type].ranged_attack.type,
        NUMBER_OF_PROJECTILE_TYPES,
        &monsterAwayTypeNum, &monsterAwayTypeCmb);
    //�J��Ԃ�
    setIntegerNum(monster_definitions[type].ranged_attack.repetitions,
        &monsterAwayRepeat);
    //�G���[
    setIntegerNum(monster_definitions[type].ranged_attack.error,
        &monsterAwayError);
    //�͈�
    setIntegerNum(monster_definitions[type].ranged_attack.range,
        &monsterAwayRange);
    //Seq
    setIntegerNum(monster_definitions[type].ranged_attack.attack_shape,
        &monsterAwaySequence);
    //X
    setIntegerNum(monster_definitions[type].ranged_attack.dx,
        &monsterAwayDeltaX);
    //Y
    setIntegerNum(monster_definitions[type].ranged_attack.dy,
        &monsterAwayDeltaY);
    //Z
    setIntegerNum(monster_definitions[type].ranged_attack.dz,
        &monsterAwayDeltaZ);

}

// CMonsterPage4 ���b�Z�[�W �n���h��

void CMonsterPage4::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if( bShow == TRUE){
        //�X�V
        monsterType.SetCurSel(theApp.editMonsterTypeId);

        this->setupDialog();
    }
}

/**
    �����X�^�[�^�C�v�R���{
*/
void CMonsterPage4::OnCbnSelchangeCombo1()
{
    theApp.editMonsterTypeId = monsterType.GetCurSel();
    setupDialog();
}

/**
    �U���p�x������
*/
void CMonsterPage4::OnBnClickedButton1()
{
    int type = theApp.editMonsterTypeId;
    monster_definitions[type].attack_frequency =
        theApp.monster_default_definitions[type].attack_frequency;
    setupDialog();
}

/**
    �ߐڍU����ރR���{
*/
void CMonsterPage4::OnCbnSelchangeCombo15()
{
    int atype = monsterMeleeType.GetCurSel();
    if( atype == NUMBER_OF_PROJECTILE_TYPES){
        atype = -1;
    }
    monster_definitions[theApp.editMonsterTypeId].melee_attack.type =
        atype;
    setIntegerNum(atype, &monsterMeleeTypeNum);
}

/**
    �ߐڏ�����
*/
void CMonsterPage4::OnBnClickedButton2()
{
    int type = theApp.editMonsterTypeId;
    memcpy(&(monster_definitions[type].melee_attack),
        &(theApp.monster_default_definitions[type].melee_attack),
        sizeof(struct attack_definition));
    setupDialog();
}

/**
    ��������ރR���{
*/
void CMonsterPage4::OnCbnSelchangeCombo28()
{
    int atype = monsterAwayTypeCmb.GetCurSel();
    if( atype == NUMBER_OF_PROJECTILE_TYPES){
        atype = -1;
    }
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.type =
        atype;
    setIntegerNum(atype, &monsterAwayTypeNum);
}

/**
    ������������
*/
void CMonsterPage4::OnBnClickedButton3()
{
    int type = theApp.editMonsterTypeId;
    memcpy(&(monster_definitions[type].ranged_attack),
        &(theApp.monster_default_definitions[type].ranged_attack),
        sizeof(struct attack_definition));
    setupDialog();
}
/**
    �p�x
*/
void CMonsterPage4::OnEnChangeEdit1()
{
    monster_definitions[theApp.editMonsterTypeId].attack_frequency = 
        getIntegerNum(&monsterAttackFrequency);
}

/**
    �ߋ����J��Ԃ�
*/
void CMonsterPage4::OnEnChangeEdit37()
{
    monster_definitions[theApp.editMonsterTypeId].melee_attack.repetitions = 
        getIntegerNum(&monsterMeleeRepeat);
}

/**
    �ߋ����G���[
*/
void CMonsterPage4::OnEnChangeEdit39()
{
    monster_definitions[theApp.editMonsterTypeId].melee_attack.error = 
        getIntegerNum(&monsterMeleeError);
}

/**
    �ߋ����͈�
*/
void CMonsterPage4::OnEnChangeEdit40()
{
    monster_definitions[theApp.editMonsterTypeId].melee_attack.range = 
        getIntegerNum(&monsterMeleeRange);
}

/**
    �U���V�[�P���X
*/
void CMonsterPage4::OnEnChangeEdit62()
{
    monster_definitions[theApp.editMonsterTypeId].melee_attack.attack_shape = 
        getIntegerNum(&monsterMeleeSequence);
}

/**
    �ߋ���DX
*/
void CMonsterPage4::OnEnChangeEdit63()
{
    monster_definitions[theApp.editMonsterTypeId].melee_attack.dx = 
        getIntegerNum(&monsterMeleeDeltaX);
}

/**
    �ߋ���dy
*/
void CMonsterPage4::OnEnChangeEdit64()
{
    monster_definitions[theApp.editMonsterTypeId].melee_attack.dy = 
        getIntegerNum(&monsterMeleeDeltaY);
}

/**
    �ߋ���dz
*/
void CMonsterPage4::OnEnChangeEdit65()
{
    monster_definitions[theApp.editMonsterTypeId].melee_attack.dz = 
        getIntegerNum(&monsterMeleeDeltaZ);
}

/**
    �������J��Ԃ�
*/
void CMonsterPage4::OnEnChangeEdit38()
{
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.repetitions = 
        getIntegerNum(&monsterAwayRepeat);
}

/**
    �������G���[
*/
void CMonsterPage4::OnEnChangeEdit66()
{
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.error = 
        getIntegerNum(&monsterAwayError);
}

/**
    �������͈�
*/
void CMonsterPage4::OnEnChangeEdit41()
{
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.range = 
        getIntegerNum(&monsterAwayRange);
}

/**
    �������V�[�P���X
*/
void CMonsterPage4::OnEnChangeEdit67()
{
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.attack_shape = 
        getIntegerNum(&monsterAwaySequence);
}

/**
    ������dx
*/
void CMonsterPage4::OnEnChangeEdit68()
{
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.dx = 
        getIntegerNum(&monsterAwayDeltaX);
}

/**
    ������dy
*/
void CMonsterPage4::OnEnChangeEdit69()
{
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.dy = 
        getIntegerNum(&monsterAwayDeltaY);
}

/**
    ������dz
*/
void CMonsterPage4::OnEnChangeEdit70()
{
    monster_definitions[theApp.editMonsterTypeId].ranged_attack.dz = 
        getIntegerNum(&monsterAwayDeltaZ);
}
