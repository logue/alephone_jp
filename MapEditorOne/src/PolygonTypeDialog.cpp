// PolygonTypeDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PolygonTypeDialog.h"


// CPolygonTypeDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CPolygonTypeDialog, CDialog)

CPolygonTypeDialog::CPolygonTypeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPolygonTypeDialog::IDD, pParent)
{

}

CPolygonTypeDialog::~CPolygonTypeDialog()
{
}

void CPolygonTypeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, polygonTypeListCtrl);
}


BEGIN_MESSAGE_MAP(CPolygonTypeDialog, CDialog)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPolygonTypeDialog ���b�Z�[�W �n���h��

BOOL CPolygonTypeDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    polygonTypeListCtrl.InsertItem(0, L"�W��", IDI_ICON_POLYGON_NORMAL);
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

BOOL CPolygonTypeDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CPolygonTypeDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CPolygonTypeDialog::PostNcDestroy()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CPolygonTypeDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CPolygonTypeDialog::DestroyWindow()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    theApp.isPolygonTypeDialogShow = FALSE;
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}
