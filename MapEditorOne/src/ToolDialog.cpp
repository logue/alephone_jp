// ToolDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ToolDialog.h"
#include ".\tooldialog.h"


// CToolDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CToolDialog, CDialog)
CToolDialog::CToolDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CToolDialog::IDD, pParent)
{
    imageList.Create(TOOL_WIDTH, TOOL_HEIGHT, ILC_COLOR32, NUMBER_OF_TOOLS * 2, 2);

    //�A�C�R���ǂݍ���
    int assignment[]={
        //unselected
        IDB_BITMAP5,
        IDB_BITMAP6,
        IDB_BITMAP8,
        IDB_BITMAP12,
        IDB_BITMAP13,
        IDB_BITMAP14,
        IDB_BITMAP17,
        IDB_BITMAP3,

        //selected
        IDB_BITMAP4,
        IDB_BITMAP7,
        IDB_BITMAP9,
        IDB_BITMAP11,
        IDB_BITMAP13,
        IDB_BITMAP15,
        IDB_BITMAP16,
        IDB_BITMAP17,
    };
    for(int i = 0; i < NUMBER_OF_TOOLS * 2; i ++){
        loadBitmap(assignment[i], &imageList, RGB(255,0,0));
    }
}

CToolDialog::~CToolDialog()
{
    imageList.DeleteImageList();
}

void CToolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolDialog, CDialog)
    ON_WM_CLOSE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CToolDialog ���b�Z�[�W �n���h��

BOOL CToolDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CToolDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CToolDialog::PostNcDestroy()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CToolDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CToolDialog::DestroyWindow()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    theApp.isToolDialogShow = FALSE;
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

BOOL CToolDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CToolDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B
    //draw tools
    for(int i = 0; i < NUMBER_OF_TOOLS; i ++){
        POINT pt;

        pt.x = (i % 2) * TOOL_WIDTH;
        pt.y = (i / 2) * TOOL_HEIGHT;

        imageList.Draw(&dc, i, pt, SRCCOPY);
    }
}
