// HeightDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "HeightDialog.h"
#include ".\heightdialog.h"


// CHeightDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CHeightDialog, CDialog)

CHeightDialog::CHeightDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHeightDialog::IDD, pParent)
    , isRevealHiddenLines(FALSE)
{

}

CHeightDialog::~CHeightDialog()
{
}

void CHeightDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER2, maxSlider);
    DDX_Control(pDX, IDC_SLIDER1, minSlider);
    DDX_Control(pDX, IDC_EDIT1, maxNum);
    DDX_Control(pDX, IDC_EDIT6, minNum);
    DDX_Check(pDX, IDC_CHECK1, isRevealHiddenLines);
}


BEGIN_MESSAGE_MAP(CHeightDialog, CDialog)
    ON_WM_CLOSE()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CHeightDialog::OnNMCustomdrawSlider2)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CHeightDialog::OnNMCustomdrawSlider1)
    ON_EN_CHANGE(IDC_EDIT1, &CHeightDialog::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT6, &CHeightDialog::OnEnChangeEdit6)
    ON_BN_CLICKED(IDC_CHECK1, &CHeightDialog::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CHeightDialog ���b�Z�[�W �n���h��
// CMonsterPropertyDialog ���b�Z�[�W �n���h��
BOOL CHeightDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CHeightDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CHeightDialog::PostNcDestroy()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CHeightDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CHeightDialog::DestroyWindow()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    //�\������������
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}


BOOL CHeightDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    int max = SHRT_MAX;
    maxSlider.SetRange(-max, max);
    maxSlider.SetPos(-max);

    minSlider.SetRange(-max, max);
    minSlider.SetPos(max);


    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
//max
void CHeightDialog::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    int pos = -maxSlider.GetPos();
    setIntegerNum(pos, &maxNum);
    theApp.viewHeightMax = pos;
    parent->Invalidate(FALSE);
    *pResult = 0;
}

//min
void CHeightDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    int pos = -minSlider.GetPos();
    setIntegerNum(pos, &minNum);
    theApp.viewHeightMin = pos;
    parent->Invalidate(FALSE);
    *pResult = 0;
}
//maxnum
void CHeightDialog::OnEnChangeEdit1()
{
    int num = getIntegerNum(&maxNum);
    maxSlider.SetPos(-num);
    parent->Invalidate(FALSE);
    UpdateData();
}
//minnum
void CHeightDialog::OnEnChangeEdit6()
{
    int num = getIntegerNum(&minNum);
    minSlider.SetPos(-num);
    parent->Invalidate(FALSE);
    UpdateData();
}

//reveal hidden lines
void CHeightDialog::OnBnClickedCheck1()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    theApp.isRevealHiddenLines = this->isRevealHiddenLines == TRUE?true:false;
}
