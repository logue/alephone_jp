// LevelParameterDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "LevelParameterDialog.h"


// CLevelParameterDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CLevelParameterDialog, CDialog)

CLevelParameterDialog::CLevelParameterDialog(CWnd* pParent /*=NULL*/,
                                             bool isNewLevelDialog)
	: CDialog(CLevelParameterDialog::IDD, pParent)
{
    isNew = isNewLevelDialog;
}

CLevelParameterDialog::~CLevelParameterDialog()
{
}

void CLevelParameterDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, levelName);
    DDX_Control(pDX, IDC_COMBO1, environment);
    DDX_Control(pDX, IDC_COMBO4, landscape);
    DDX_Control(pDX, IDC_CHECK6, gameTypes[0]);
    DDX_Control(pDX, IDC_CHECK7, gameTypes[1]);
    DDX_Control(pDX, IDC_CHECK8, gameTypes[2]);
    DDX_Control(pDX, IDC_CHECK9, gameTypes[3]);
    DDX_Control(pDX, IDC_CHECK15, gameTypes[4]);
    DDX_Control(pDX, IDC_CHECK16, gameTypes[5]);
    DDX_Control(pDX, IDC_CHECK17, gameTypes[6]);
    DDX_Control(pDX, IDC_CHECK18, gameTypes[7]);
    DDX_Control(pDX, IDC_CHECK2, envTypes[0]);
    DDX_Control(pDX, IDC_CHECK3, envTypes[1]);
    DDX_Control(pDX, IDC_CHECK4, envTypes[2]);
    DDX_Control(pDX, IDC_CHECK5, envTypes[3]);
    DDX_Control(pDX, IDC_CHECK10, missionFlags[0]);
    DDX_Control(pDX, IDC_CHECK11, missionFlags[1]);
    DDX_Control(pDX, IDC_CHECK12, missionFlags[2]);
    DDX_Control(pDX, IDC_CHECK13, missionFlags[3]);
    DDX_Control(pDX, IDC_CHECK14, missionFlags[4]);
}


BEGIN_MESSAGE_MAP(CLevelParameterDialog, CDialog)
END_MESSAGE_MAP()


// CLevelParameterDialog ���b�Z�[�W �n���h��

BOOL CLevelParameterDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������

    //�R���{�{�b�N�X�֗�������
    for(int i = 0; i < NUMBER_OF_ENVIRONMENTS; i ++){
        environment.InsertString(i, theApp.environmentInformations[i].jname);
    }
    for(int i = 0; i < NUMBER_OF_LANDSPACES; i ++){
        landscape.InsertString(i, theApp.landscapeInformations[i].jname);
    }
    if(isNew){
        //�V�K���x��
        //�W��
        //���x����
        levelName.SetWindowText(L"new level");
        //��
        environment.SetCurSel(0);
    }else{
        //���x�������擾
        levelName.SetWindowText(theApp.LevelNameList.GetAt(theApp.editLevelIndex));
        //��
        environment.SetCurSel(static_world->environment_code);
        //landscape.SetCurSel(static_world->);

        //flag -> buttons
        //game type
        for(int i = 0; i < NUMBER_OF_GAME_TYPES; i ++){
            if(GET_GAME_TYPE() == i){
                gameTypes[i].SetCheck(TRUE);
            }else{
                gameTypes[i].SetCheck(FALSE);
            }
        }
        //env type
        for(int i = 1; i < NUMBER_OF_ENV_TYPES; i ++){
            if(static_world->environment_flags & theApp.environmentTypeInformations[i].bind){
                envTypes[i-1].SetCheck(TRUE);
            }else{
                envTypes[i-1].SetCheck(FALSE);
            }
        }
        //mission
        for(int i = 1; i < NUMBER_OF_MISSION_TYPES; i ++){
            if(static_world->mission_flags & theApp.missionTypeInformations[i].bind){
                missionFlags[i-1].SetCheck(TRUE);
            }else{
                missionFlags[i-1].SetCheck(FALSE);
            }
        }

    }
    UpdateData();

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
