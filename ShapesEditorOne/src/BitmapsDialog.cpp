// BitmapsDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapsDialog.h"
#include ".\bitmapsdialog.h"


// CBitmapsDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CBitmapsDialog, CDialog)
CBitmapsDialog::CBitmapsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapsDialog::IDD, pParent)
{
    bitmapImagesDialog = NULL;
    bitmapCLUTDialog = NULL;
}

CBitmapsDialog::~CBitmapsDialog()
{
    delete bitmapImagesDialog;
    delete bitmapCLUTDialog;
}

void CBitmapsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, showTypeCmb);
    DDX_Control(pDX, IDC_COMBO2, collectionCmb);
}


BEGIN_MESSAGE_MAP(CBitmapsDialog, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO2, &CBitmapsDialog::OnCbnSelchangeCombo2)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CBitmapsDialog ���b�Z�[�W �n���h��

void CBitmapsDialog::setupDialog()
{
    bitmapImagesDialog->ShowWindow(showMode == eBitmapDialogImages? SW_SHOW : SW_HIDE);
    bitmapCLUTDialog->ShowWindow(showMode == eBitmapDialogCLUT? SW_SHOW : SW_HIDE);

    int sel = showTypeCmb.GetCurSel();
    switch(showMode){
    case eBitmapDialogImages:
        bitmapImagesDialog->isFirstOfSetup = true;
        bitmapImagesDialog->setupDialog();
        break;
    case eBitmapDialogCLUT:
        bitmapCLUTDialog->setupDialog();
        break;
    }
    UpdateData();
}

void CBitmapsDialog::resize(){
    CRect parentRect;
    this->GetClientRect(&parentRect);
    parentRect.top = 30;
    bitmapImagesDialog->MoveWindow(&parentRect);
    bitmapCLUTDialog->MoveWindow(&parentRect);
}
BOOL CBitmapsDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    bitmapImagesDialog = new CBitmapImagesDialog(this);
    bitmapCLUTDialog = new CBitmapCLUTDialog(this);


    // TODO :  �����ɏ�������ǉ����Ă�������
    bitmapImagesDialog->Create(MAKEINTRESOURCE(CBitmapImagesDialog::IDD), this);
    bitmapCLUTDialog->Create(MAKEINTRESOURCE(CBitmapCLUTDialog::IDD), this);

    resize();

    //store show type
    for(int i = 0; i < NUMBER_OF_BITMAPS_DIALOG_SHOW_TYPES; i ++){
        showTypeCmb.InsertString(i, theApp.showTypeInformations[i].jname);
    }
    
    //store collections
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        collectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }
    showTypeCmb.SetCurSel(0);
    collectionCmb.SetCurSel(0);
    showMode = 0;
    setupDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
//show type
void CBitmapsDialog::OnCbnSelchangeCombo1()
{
    // TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    int sel = showTypeCmb.GetCurSel();
    showMode = sel;
    setupDialog();
}

//collection combo
void CBitmapsDialog::OnCbnSelchangeCombo2()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    theApp.collection = collectionCmb.GetCurSel();
    setupDialog();
    //�t�H�[�J�X��show type�ցB
    GetDlgItem(IDC_DUMMY_)->SetFocus();
}

void CBitmapsDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    if(bitmapImagesDialog){
        resize();
    }
}
