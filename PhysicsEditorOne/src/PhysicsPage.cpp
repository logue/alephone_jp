// PhysicsPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "PhysicsPage.h"


// CPhysicsPage ダイアログ

IMPLEMENT_DYNAMIC(CPhysicsPage, CDialog)

CPhysicsPage::CPhysicsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CPhysicsPage::IDD, pParent)
{

}

CPhysicsPage::~CPhysicsPage()
{
}

void CPhysicsPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO2, pTypeCmb);
    DDX_Control(pDX, IDC_EDIT3, pTypeNum);
    DDX_Control(pDX, IDC_EDIT2, pMaximumForwardVelocity);
    DDX_Control(pDX, IDC_EDIT37, pMaximumBackwardVelocity);
    DDX_Control(pDX, IDC_EDIT39, pMaximumPerpendicularVelocity);
    DDX_Control(pDX, IDC_EDIT40, pAcceleration);
    DDX_Control(pDX, IDC_EDIT104, pDeceleration);
    DDX_Control(pDX, IDC_EDIT105, pAirborneDeceleration);
    DDX_Control(pDX, IDC_EDIT4, pGravitationalAcceleration);
    DDX_Control(pDX, IDC_EDIT36, pClimbingAcceleration);
    DDX_Control(pDX, IDC_EDIT6, pTerminalVelocity);
    DDX_Control(pDX, IDC_EDIT34, pExternalDeceleration);
    DDX_Control(pDX, IDC_EDIT7, pAngularAcceleration);
    DDX_Control(pDX, IDC_EDIT38, pAngularDeceleration);
    DDX_Control(pDX, IDC_EDIT9, pMaximumAngularVelocity);
    DDX_Control(pDX, IDC_EDIT41, pAngularRecenteringVelocity);
    DDX_Control(pDX, IDC_EDIT42, pFastAngularVelocity);
    DDX_Control(pDX, IDC_EDIT43, pFastAngularMaximum);
    DDX_Control(pDX, IDC_EDIT11, pMaximumElevation);
    DDX_Control(pDX, IDC_EDIT44, pExternalAngularDeceleration);
    DDX_Control(pDX, IDC_EDIT12, pStepDelta);
    DDX_Control(pDX, IDC_EDIT46, pStepAmplitude);
    DDX_Control(pDX, IDC_EDIT83, pRadius);
    DDX_Control(pDX, IDC_EDIT47, pHeight);
    DDX_Control(pDX, IDC_EDIT48, pDeadHeight);
    DDX_Control(pDX, IDC_EDIT49, pCameraHeight);
    DDX_Control(pDX, IDC_EDIT15, pSplashHeight);
    DDX_Control(pDX, IDC_EDIT50, pHalfCameraSeparation);
}


BEGIN_MESSAGE_MAP(CPhysicsPage, CDialog)
    ON_WM_SHOWWINDOW()
    ON_CBN_SELCHANGE(IDC_COMBO2, &CPhysicsPage::OnCbnSelchangeCombo2)
    ON_EN_CHANGE(IDC_EDIT2, &CPhysicsPage::OnEnChangeEdit2)
    ON_EN_CHANGE(IDC_EDIT37, &CPhysicsPage::OnEnChangeEdit37)
    ON_EN_CHANGE(IDC_EDIT39, &CPhysicsPage::OnEnChangeEdit39)
    ON_EN_CHANGE(IDC_EDIT40, &CPhysicsPage::OnEnChangeEdit40)
    ON_EN_CHANGE(IDC_EDIT104, &CPhysicsPage::OnEnChangeEdit104)
    ON_EN_CHANGE(IDC_EDIT105, &CPhysicsPage::OnEnChangeEdit105)
    ON_EN_CHANGE(IDC_EDIT4, &CPhysicsPage::OnEnChangeEdit4)
    ON_EN_CHANGE(IDC_EDIT36, &CPhysicsPage::OnEnChangeEdit36)
    ON_EN_CHANGE(IDC_EDIT6, &CPhysicsPage::OnEnChangeEdit6)
    ON_EN_CHANGE(IDC_EDIT34, &CPhysicsPage::OnEnChangeEdit34)
    ON_EN_CHANGE(IDC_EDIT7, &CPhysicsPage::OnEnChangeEdit7)
    ON_EN_CHANGE(IDC_EDIT38, &CPhysicsPage::OnEnChangeEdit38)
    ON_EN_CHANGE(IDC_EDIT9, &CPhysicsPage::OnEnChangeEdit9)
    ON_EN_CHANGE(IDC_EDIT41, &CPhysicsPage::OnEnChangeEdit41)
    ON_EN_CHANGE(IDC_EDIT42, &CPhysicsPage::OnEnChangeEdit42)
    ON_EN_CHANGE(IDC_EDIT43, &CPhysicsPage::OnEnChangeEdit43)
    ON_EN_CHANGE(IDC_EDIT11, &CPhysicsPage::OnEnChangeEdit11)
    ON_EN_CHANGE(IDC_EDIT44, &CPhysicsPage::OnEnChangeEdit44)
    ON_EN_CHANGE(IDC_EDIT12, &CPhysicsPage::OnEnChangeEdit12)
    ON_EN_CHANGE(IDC_EDIT46, &CPhysicsPage::OnEnChangeEdit46)
    ON_EN_CHANGE(IDC_EDIT83, &CPhysicsPage::OnEnChangeEdit83)
    ON_EN_CHANGE(IDC_EDIT47, &CPhysicsPage::OnEnChangeEdit47)
    ON_EN_CHANGE(IDC_EDIT48, &CPhysicsPage::OnEnChangeEdit48)
    ON_EN_CHANGE(IDC_EDIT49, &CPhysicsPage::OnEnChangeEdit49)
    ON_EN_CHANGE(IDC_EDIT15, &CPhysicsPage::OnEnChangeEdit15)
    ON_EN_CHANGE(IDC_EDIT50, &CPhysicsPage::OnEnChangeEdit50)
END_MESSAGE_MAP()


// CPhysicsPage メッセージ ハンドラ

void CPhysicsPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    if(bShow == TRUE){
        pTypeCmb.SetCurSel(theApp.editPhysicsTypeId);
        setupDialog();
    }
}

BOOL CPhysicsPage::OnInitDialog()
{
    BOOL ret = CDialog::OnInitDialog();

    //種類
    for(int i = 0; i < NUMBER_OF_PHYSICS_MODELS; i ++){
        pTypeCmb.InsertString(i, theApp.physicsInformations[i].jname);
    }
    pTypeCmb.SetCurSel(theApp.editPhysicsTypeId);
    setupDialog();

    return ret;
}

void CPhysicsPage::setupDialog()
{
    int type = theApp.editPhysicsTypeId;

    //種類
    setIntegerNum(type, &pTypeNum);

    setIntegerNum(physics_models[type].maximum_forward_velocity, &pMaximumForwardVelocity);
    setIntegerNum(physics_models[type].maximum_backward_velocity, &pMaximumBackwardVelocity);
    setIntegerNum(physics_models[type].maximum_perpendicular_velocity, &pMaximumPerpendicularVelocity);
    setIntegerNum(physics_models[type].acceleration, &pAcceleration);
    setIntegerNum(physics_models[type].deceleration, &pDeceleration);
    setIntegerNum(physics_models[type].airborne_deceleration, &pAirborneDeceleration);
    setIntegerNum(physics_models[type].gravitational_acceleration, &pGravitationalAcceleration);
    setIntegerNum(physics_models[type].climbing_acceleration, &pClimbingAcceleration);
    setIntegerNum(physics_models[type].terminal_velocity, &pTerminalVelocity);
    setIntegerNum(physics_models[type].external_deceleration, &pExternalDeceleration);

    setIntegerNum(physics_models[type].angular_acceleration, &pAngularAcceleration);
    setIntegerNum(physics_models[type].angular_deceleration, &pAngularDeceleration);
    setIntegerNum(physics_models[type].maximum_angular_velocity, &pMaximumAngularVelocity);
    setIntegerNum(physics_models[type].angular_recentering_velocity, &pAngularRecenteringVelocity);
    setIntegerNum(physics_models[type].fast_angular_velocity, &pFastAngularVelocity);
    setIntegerNum(physics_models[type].fast_angular_maximum, &pFastAngularMaximum);
    setIntegerNum(physics_models[type].maximum_elevation, &pMaximumElevation);
    setIntegerNum(physics_models[type].external_angular_deceleration, &pExternalAngularDeceleration);

    setIntegerNum(physics_models[type].step_delta, &pStepDelta);
    setIntegerNum(physics_models[type].step_amplitude, &pStepAmplitude);
    setIntegerNum(physics_models[type].radius, &pRadius);
    setIntegerNum(physics_models[type].height, &pHeight);
    setIntegerNum(physics_models[type].dead_height, &pDeadHeight);
    setIntegerNum(physics_models[type].camera_height, &pCameraHeight);
    setIntegerNum(physics_models[type].splash_height, &pSplashHeight);

    setIntegerNum(physics_models[type].half_camera_separation, &pHalfCameraSeparation);
}
/**
    種類コンボ
*/
void CPhysicsPage::OnCbnSelchangeCombo2()
{
    theApp.editPhysicsTypeId = pTypeCmb.GetCurSel();
    setupDialog();
}
//max forward vel
void CPhysicsPage::OnEnChangeEdit2()
{
    physics_models[theApp.editPhysicsTypeId].maximum_forward_velocity =
        getIntegerNum(&pMaximumForwardVelocity);
}

//max back vel
void CPhysicsPage::OnEnChangeEdit37()
{
    physics_models[theApp.editPhysicsTypeId].maximum_backward_velocity =
        getIntegerNum(&pMaximumBackwardVelocity);
}
//max perpendicular vel
void CPhysicsPage::OnEnChangeEdit39()
{
    physics_models[theApp.editPhysicsTypeId].maximum_perpendicular_velocity =
        getIntegerNum(&pMaximumPerpendicularVelocity);
}

//accel
void CPhysicsPage::OnEnChangeEdit40()
{
    physics_models[theApp.editPhysicsTypeId].acceleration =
        getIntegerNum(&pAcceleration);
}
//dec
void CPhysicsPage::OnEnChangeEdit104()
{
    physics_models[theApp.editPhysicsTypeId].deceleration =
        getIntegerNum(&pDeceleration);
}
//air
void CPhysicsPage::OnEnChangeEdit105()
{
    physics_models[theApp.editPhysicsTypeId].airborne_deceleration =
        getIntegerNum(&pAirborneDeceleration);
}

void CPhysicsPage::OnEnChangeEdit4()
{
    physics_models[theApp.editPhysicsTypeId].gravitational_acceleration =
        getIntegerNum(&pGravitationalAcceleration);
}

void CPhysicsPage::OnEnChangeEdit36()
{
    physics_models[theApp.editPhysicsTypeId].climbing_acceleration =
        getIntegerNum(&pClimbingAcceleration);
}
//terminal
void CPhysicsPage::OnEnChangeEdit6()
{
    physics_models[theApp.editPhysicsTypeId].terminal_velocity =
        getIntegerNum(&pTerminalVelocity);
}
//external dec
void CPhysicsPage::OnEnChangeEdit34()
{
    physics_models[theApp.editPhysicsTypeId].external_deceleration =
        getIntegerNum(&pExternalDeceleration);
}
////////////////////////////

void CPhysicsPage::OnEnChangeEdit7()
{
    physics_models[theApp.editPhysicsTypeId].angular_acceleration =
        getIntegerNum(&pAngularAcceleration);
}

void CPhysicsPage::OnEnChangeEdit38()
{
    physics_models[theApp.editPhysicsTypeId].angular_deceleration =
        getIntegerNum(&pAngularDeceleration);
}

void CPhysicsPage::OnEnChangeEdit9()
{
    physics_models[theApp.editPhysicsTypeId].maximum_angular_velocity =
        getIntegerNum(&pMaximumAngularVelocity);
}

void CPhysicsPage::OnEnChangeEdit41()
{
    physics_models[theApp.editPhysicsTypeId].angular_recentering_velocity =
        getIntegerNum(&pAngularRecenteringVelocity);
}
void CPhysicsPage::OnEnChangeEdit42()
{
    physics_models[theApp.editPhysicsTypeId].fast_angular_velocity =
        getIntegerNum(&pFastAngularVelocity);
}

void CPhysicsPage::OnEnChangeEdit43()
{
    physics_models[theApp.editPhysicsTypeId].fast_angular_maximum =
        getIntegerNum(&pFastAngularMaximum);
}

void CPhysicsPage::OnEnChangeEdit11()
{
    physics_models[theApp.editPhysicsTypeId].maximum_elevation =
        getIntegerNum(&pMaximumElevation);
}

void CPhysicsPage::OnEnChangeEdit44()
{
    physics_models[theApp.editPhysicsTypeId].external_angular_deceleration =
        getIntegerNum(&pExternalAngularDeceleration);
}
///////////////
void CPhysicsPage::OnEnChangeEdit12()
{
    physics_models[theApp.editPhysicsTypeId].step_delta =
        getIntegerNum(&pStepDelta);
}

void CPhysicsPage::OnEnChangeEdit46()
{
    physics_models[theApp.editPhysicsTypeId].step_amplitude =
        getIntegerNum(&pStepAmplitude);
}

void CPhysicsPage::OnEnChangeEdit83()
{
    physics_models[theApp.editPhysicsTypeId].radius =
        getIntegerNum(&pRadius);
}

void CPhysicsPage::OnEnChangeEdit47()
{
    physics_models[theApp.editPhysicsTypeId].height =
        getIntegerNum(&pHeight);
}

void CPhysicsPage::OnEnChangeEdit48()
{
    physics_models[theApp.editPhysicsTypeId].dead_height =
        getIntegerNum(&pDeadHeight);
}

void CPhysicsPage::OnEnChangeEdit49()
{
    physics_models[theApp.editPhysicsTypeId].camera_height =
        getIntegerNum(&pCameraHeight);
}

void CPhysicsPage::OnEnChangeEdit15()
{
    physics_models[theApp.editPhysicsTypeId].splash_height =
        getIntegerNum(&pSplashHeight);
}

void CPhysicsPage::OnEnChangeEdit50()
{
    physics_models[theApp.editPhysicsTypeId].half_camera_separation =
        getIntegerNum(&pHalfCameraSeparation);
}
