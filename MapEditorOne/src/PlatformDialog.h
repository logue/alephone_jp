#pragma once
#include "afxwin.h"


// CPlatformDialog ダイアログ

class CPlatformDialog : public CDialog
{
	DECLARE_DYNAMIC(CPlatformDialog)

private:
    CPlatformDialog(CWnd*){}
public:
	CPlatformDialog(CWnd* pParent , int index);   // 標準コンストラクタ
	virtual ~CPlatformDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_PLATFORM };

public:
    int platformIndex;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    CComboBox typeCmb;
public:
    CEdit speedNum;
public:
    CEdit delayNum;
public:
    CComboBox speedCmb;
public:
    CComboBox delayCmb;
public:
    CButton autoMin;
public:
    CButton autoMax;
public:
    CEdit minHeight;
public:
    CEdit maxHeight;
public:
    CButton door;
public:
    CComboBox presetCmb;
public:
    CButton floorToCeiling;
public:
    CButton initActivate;
public:
    CButton initExtended;
public:
    CButton ctrlPlayer;
public:
    CButton ctrlAliens;
public:
    CButton biteDamage;
public:
    CButton biteReverse;
public:
    CButton actOnce;
public:
    CButton actActivateLight;
public:
    CButton actActivateAdj;
public:
    CButton actDeactivateAdj;
public:
    CButton actAdj;
public:
    CButton deDeactivateLight;
public:
    CButton deDeactivateAdj;
public:
    CButton deActivateAdj;
public:
    CButton miscCannotExternal;
public:
    CButton miscUseNative;
public:
    CButton miscDelayBeforeAct;
public:
    CButton miscNotActParent;
public:
    CButton miscContractSlower;
public:
    CButton miscLocked;
public:
    CButton miscSecret;
public:
    CComboBox tagCmb;
};
