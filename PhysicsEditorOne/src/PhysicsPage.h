#pragma once
#include "afxwin.h"


// CPhysicsPage ダイアログ

class CPhysicsPage : public CDialog
{
	DECLARE_DYNAMIC(CPhysicsPage)

public:
	CPhysicsPage(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CPhysicsPage();
    virtual BOOL OnInitDialog();
    void setupDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_PHYSICS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    CComboBox pTypeCmb;
public:
    CEdit pTypeNum;
public:
    CEdit pMaximumForwardVelocity;
public:
    CEdit pMaximumBackwardVelocity;
public:
    CEdit pMaximumPerpendicularVelocity;
public:
    CEdit pAcceleration;
public:
    CEdit pDeceleration;
public:
    CEdit pAirborneDeceleration;
public:
    CEdit pGravitationalAcceleration;
public:
    CEdit pClimbingAcceleration;
public:
    CEdit pTerminalVelocity;
public:
    CEdit pExternalDeceleration;
public:
    CEdit pAngularAcceleration;
public:
    CEdit pAngularDeceleration;
public:
    CEdit pMaximumAngularVelocity;
public:
    CEdit pAngularRecenteringVelocity;
public:
    CEdit pFastAngularVelocity;
public:
    CEdit pFastAngularMaximum;
public:
    CEdit pMaximumElevation;
public:
    CEdit pExternalAngularDeceleration;
public:
    CEdit pStepDelta;
public:
    CEdit pStepAmplitude;
public:
    CEdit pRadius;
public:
    CEdit pHeight;
public:
    CEdit pDeadHeight;
public:
    CEdit pCameraHeight;
public:
    CEdit pSplashHeight;
public:
    CEdit pHalfCameraSeparation;
public:
    afx_msg void OnCbnSelchangeCombo2();
public:
    afx_msg void OnEnChangeEdit2();
public:
    afx_msg void OnEnChangeEdit37();
public:
    afx_msg void OnEnChangeEdit39();
public:
    afx_msg void OnEnChangeEdit40();
public:
    afx_msg void OnEnChangeEdit104();
public:
    afx_msg void OnEnChangeEdit105();
public:
    afx_msg void OnEnChangeEdit4();
public:
    afx_msg void OnEnChangeEdit36();
public:
    afx_msg void OnEnChangeEdit6();
public:
    afx_msg void OnEnChangeEdit34();
public:
    afx_msg void OnEnChangeEdit7();
public:
    afx_msg void OnEnChangeEdit38();
public:
    afx_msg void OnEnChangeEdit9();
public:
    afx_msg void OnEnChangeEdit41();
public:
    afx_msg void OnEnChangeEdit42();
public:
    afx_msg void OnEnChangeEdit43();
public:
    afx_msg void OnEnChangeEdit11();
public:
    afx_msg void OnEnChangeEdit44();
public:
    afx_msg void OnEnChangeEdit12();
public:
    afx_msg void OnEnChangeEdit46();
public:
    afx_msg void OnEnChangeEdit83();
public:
    afx_msg void OnEnChangeEdit47();
public:
    afx_msg void OnEnChangeEdit48();
public:
    afx_msg void OnEnChangeEdit49();
public:
    afx_msg void OnEnChangeEdit15();
public:
    afx_msg void OnEnChangeEdit50();
};
