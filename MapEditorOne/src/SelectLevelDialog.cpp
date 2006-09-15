// SelectLevelDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "SelectLevelDialog.h"
#include ".\selectleveldialog.h"


// CSelectLevelDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CSelectLevelDialog, CDialog)
CSelectLevelDialog::CSelectLevelDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectLevelDialog::IDD, pParent)
{
}

CSelectLevelDialog::~CSelectLevelDialog()
{
}

void CSelectLevelDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, selectLevelListBox);
}


BEGIN_MESSAGE_MAP(CSelectLevelDialog, CDialog)
    ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
    ON_WM_CREATE()
    ON_LBN_DBLCLK(IDC_LIST1, OnLbnDblclkList1)
END_MESSAGE_MAP()


// CSelectLevelDialog ���b�Z�[�W �n���h��

//�N���b�N
void CSelectLevelDialog::OnLbnSelchangeList1()
{
    // TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    theApp.editLevelIndex = selectLevelListBox.GetCurSel();
}

//������
int CSelectLevelDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO :  �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B
    //���X�g�{�b�N�X�ɗ�������
    return 0;
}

BOOL CSelectLevelDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    char cstr[256];

    // TODO :  �����ɏ�������ǉ����Ă�������
    for(int i = 0; i < theApp.LevelNameList.GetSize(); i ++){
        sprintf(cstr, "%d.", i+1);
        selectLevelListBox.AddString(CString(cstr) + CString(theApp.LevelNameList.GetAt(i)));
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

//�_�u���N���b�N
void CSelectLevelDialog::OnLbnDblclkList1()
{
    // TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    //�I��
    theApp.editLevelIndex = selectLevelListBox.GetCurSel();

    //����
    EndDialog(IDOK);
}
