// EffectPage.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "EffectPage.h"


// CEffectPage �_�C�A���O

IMPLEMENT_DYNAMIC(CEffectPage, CDialog)

CEffectPage::CEffectPage(CWnd* pParent /*=NULL*/)
	: CDialog(CEffectPage::IDD, pParent)
{

}

CEffectPage::~CEffectPage()
{
}

void CEffectPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, effectTypeCmb);
    DDX_Control(pDX, IDC_EDIT1, effectTypeNum);
    DDX_Control(pDX, IDC_COMBO15, effectCollectionCmb);
    DDX_Control(pDX, IDC_EDIT2, effectCollectionNum);
    DDX_Control(pDX, IDC_EDIT37, effectSequence);
    DDX_Control(pDX, IDC_EDIT39, effectPitch);
    DDX_Control(pDX, IDC_EDIT40, effectDelay);
    DDX_Control(pDX, IDC_COMBO29, effectDelaySoundCmb);
    DDX_Control(pDX, IDC_EDIT4, effectDelaySoundNum);
    DDX_Control(pDX, IDC_CHECK5, effectFlags[0]);
    DDX_Control(pDX, IDC_CHECK7, effectFlags[1]);
    DDX_Control(pDX, IDC_CHECK9, effectFlags[2]);
    DDX_Control(pDX, IDC_CHECK11, effectFlags[3]);
    DDX_Control(pDX, IDC_CHECK13, effectFlags[4]);
}


BEGIN_MESSAGE_MAP(CEffectPage, CDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &CEffectPage::OnBnClickedButton1)
    ON_WM_SHOWWINDOW()
    ON_CBN_SELCHANGE(IDC_COMBO1, &CEffectPage::OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO15, &CEffectPage::OnCbnSelchangeCombo15)
    ON_EN_CHANGE(IDC_EDIT37, &CEffectPage::OnEnChangeEdit37)
    ON_EN_CHANGE(IDC_EDIT39, &CEffectPage::OnEnChangeEdit39)
    ON_BN_CLICKED(IDC_CHECK5, &CEffectPage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK7, &CEffectPage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK9, &CEffectPage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK11, &CEffectPage::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK13, &CEffectPage::OnBnClickedCheck5)
    ON_EN_CHANGE(IDC_EDIT40, &CEffectPage::OnEnChangeEdit40)
    ON_CBN_SELCHANGE(IDC_COMBO29, &CEffectPage::OnCbnSelchangeCombo29)
    ON_EN_CHANGE(IDC_EDIT4, &CEffectPage::OnEnChangeEdit4)
    ON_BN_CLICKED(IDC_BUTTON2, &CEffectPage::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CEffectPage::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CEffectPage::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CEffectPage::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON13, &CEffectPage::OnBnClickedButton13)
    ON_BN_CLICKED(IDC_BUTTON6, &CEffectPage::OnBnClickedButton6)
END_MESSAGE_MAP()


// CEffectPage ���b�Z�[�W �n���h��

BOOL CEffectPage::OnInitDialog()
{
    BOOL ret = CDialog::OnInitDialog();

    //�G�t�F�N�g��ޕ�[
    for(int i = 0; i < NUMBER_OF_EFFECT_TYPES; i ++){
        effectTypeCmb.InsertString(i, theApp.effectInformations[i].jname);
    }

    //�R���N�V������[
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        effectCollectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }

    //�T�E���h��[
    for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
        effectDelaySoundCmb.InsertString(i, theApp.soundInformations[i].jname);
    }
    effectDelaySoundCmb.InsertString(NUMBER_OF_SOUND_DEFINITIONS,
        L"*none*");
    effectTypeCmb.SetCurSel(theApp.editEffectTypeId);

    return ret;
}

void CEffectPage::setupDialog()
{
    int type = theApp.editEffectTypeId;

    //���
    setIntegerNum(type, &effectTypeNum);

    //�R���N�V����
    setComboNum(effect_definitions[type].collection, 0,
        &effectCollectionNum, &effectCollectionCmb);

    //�V�[�P���XID
    setIntegerNum(effect_definitions[type].shape, &effectSequence);
    
    //�s�b�`
    setIntegerNum(effect_definitions[type].sound_pitch, &effectPitch);

    //�t���O
    int flag = effect_definitions[type].flags;
    for(int i = 0; i < NUMBER_OF_EFFECT_FLAG_INFORMATIONS; i ++){
        if(flag & theApp.effectFlagInformations[i].bindId){
            effectFlags[i].SetCheck(1);
        }else{
            effectFlags[i].SetCheck(0);
        }
    }

    //delay
    setIntegerNum(effect_definitions[type].delay,
        &effectDelay);

    //delay sound
    setComboNum(effect_definitions[type].delay_sound, NUMBER_OF_SOUND_DEFINITIONS,
        &effectDelaySoundNum, &effectDelaySoundCmb);
}

/**
    �S�̏�����
*/
void CEffectPage::OnBnClickedButton1()
{
    OnBnClickedButton2();
    OnBnClickedButton3();
    OnBnClickedButton4();
    OnBnClickedButton5();
    OnBnClickedButton13();
    OnBnClickedButton6();
}

void CEffectPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);
    if(bShow == TRUE){
        //�^�C�v�ǂݍ���
        effectTypeCmb.SetCurSel(theApp.editEffectTypeId);

        setupDialog();
    }
}

/**
    ��ރR���{
*/
void CEffectPage::OnCbnSelchangeCombo1()
{
    int type = effectTypeCmb.GetCurSel();
    theApp.editEffectTypeId = type;
    setupDialog();
}
/**
    �R���N�V�����R���{
*/
void CEffectPage::OnCbnSelchangeCombo15()
{
    int sel = effectCollectionCmb.GetCurSel();
    effect_definitions[theApp.editEffectTypeId].collection = sel;
    setIntegerNum(sel, &effectCollectionNum);
}
/**
    �V�[�N�G���XID
*/
void CEffectPage::OnEnChangeEdit37()
{
    effect_definitions[theApp.editEffectTypeId].shape =
        getIntegerNum(&effectSequence);
}
/**
    �T�E���h�s�b�`
*/
void CEffectPage::OnEnChangeEdit39()
{
    effect_definitions[theApp.editEffectTypeId].sound_pitch =
        getIntegerNum(&effectPitch);
}

/**
    �t���O����
*/
void CEffectPage::OnBnClickedCheck5()
{
    //�G�t�F�N�g�t���O
    int flag = 0;
    for(int i = 0; i < NUMBER_OF_EFFECT_FLAG_INFORMATIONS; i ++){
        if(effectFlags[i].GetCheck()){
            flag |= theApp.effectFlagInformations[i].bindId;
        }
    }
    effect_definitions[theApp.editEffectTypeId].flags = flag;
}
/**
    �x��
*/
void CEffectPage::OnEnChangeEdit40()
{
    int num = getIntegerNum(&effectDelay);
    effect_definitions[theApp.editEffectTypeId].delay = num;
}
/**
    delay sound combo
*/
void CEffectPage::OnCbnSelchangeCombo29()
{
    int sel = effectDelaySoundCmb.GetCurSel();
    effect_definitions[theApp.editEffectTypeId].delay_sound = sel;
    //�ԍ�
    setIntegerNum(sel, &effectDelaySoundNum);
}

/**
    �x���T�E���hdisable
*/
void CEffectPage::OnEnChangeEdit4()
{
}
/**
    �R���N�V����������
*/
void CEffectPage::OnBnClickedButton2()
{
    int type = theApp.editEffectTypeId;
    effect_definitions[type].collection = 
        theApp.effect_default_definitions[type].collection;
    setupDialog();
}

void CEffectPage::OnBnClickedButton3()
{
    int type = theApp.editEffectTypeId;
    effect_definitions[type].shape = 
        theApp.effect_default_definitions[type].shape;
    setupDialog();
}

void CEffectPage::OnBnClickedButton4()
{
    int type = theApp.editEffectTypeId;
    effect_definitions[type].sound_pitch = 
        theApp.effect_default_definitions[type].sound_pitch;
    setupDialog();
}

void CEffectPage::OnBnClickedButton5()
{
    int type = theApp.editEffectTypeId;
    effect_definitions[type].flags = 
        theApp.effect_default_definitions[type].flags;
    setupDialog();
}

void CEffectPage::OnBnClickedButton13()
{
    int type = theApp.editEffectTypeId;
    effect_definitions[type].delay = 
        theApp.effect_default_definitions[type].delay;
    setupDialog();
}

void CEffectPage::OnBnClickedButton6()
{
    int type = theApp.editEffectTypeId;
    effect_definitions[type].delay_sound = 
        theApp.effect_default_definitions[type].delay_sound;
    setupDialog();
}
