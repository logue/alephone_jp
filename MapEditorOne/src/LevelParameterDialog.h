#pragma once
#include "afxwin.h"
#include "map.h"


// CLevelParameterDialog ダイアログ

/**
    level parameters dialog
*/
class CLevelParameterDialog : public CDialog
{
	DECLARE_DYNAMIC(CLevelParameterDialog)

public:
	//CLevelParameterDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
    /**
        @param isNewLevelDialog
        新規レベルとして呼び出したかどうか
        新規ならば値は設定しない
        新規でなければ読み込んでいるレベルの情報を反映させる
    */
    CLevelParameterDialog(CWnd* pParent , bool isNewLevelDialog);
	virtual ~CLevelParameterDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_LEVEL_PARAMETER };

    bool isNew;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    CEdit levelName;
public:
    CComboBox environment;
public:
    CComboBox landscape;
public:
    CButton gameTypes[NUMBER_OF_GAME_TYPES];
public:
    CButton envTypes[NUMBER_OF_ENV_TYPES];
public:
    CButton missionFlags[NUMBER_OF_MISSION_TYPES];
public:
    virtual BOOL OnInitDialog();
};
