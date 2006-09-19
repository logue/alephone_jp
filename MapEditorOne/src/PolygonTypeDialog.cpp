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
    imageList.DeleteImageList();
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
    //�摜�ǂݍ���
    imageList.Create(16,16, ILC_MASK, 24, 2);
    int id[] ={
        IDI_ICON0_POLYGON_NORMAL,
        IDI_ICON1_POLYGON_ITEM_IMPASSABLE,
        IDI_ICON2_POLYGON_MONTER_IMPASSIBLE,
        IDI_ICON3_POLYGON_HILL,
        IDI_ICON4_POLYGON_BASE,
        IDI_ICON5_POLYGON_PLATFORM,
        IDI_ICON6_POLYGON_ENLIGHT,
        IDI_ICON7_POLYGON_ENPLATFORM,
        IDI_ICON8_POLYGON_DISLIGHT,
        IDI_ICON9_POLYGON_DISPLATFORM,
        IDI_ICON10_POLYGON_TELEPORTER,

        IDI_ICON11_POLYGON_ZONE_BORDER,
        IDI_ICON12_POLYGON_GOAL,
        IDI_ICON13_POLYGON_VISIBLE_TRIGGER,
        IDI_ICON14_POLYGON_INVISIBLE_TRIGGER,
        IDI_ICON15_POLYGON_DUAL_TRIGGER,
        IDI_ICON16_POLYGON_ITEM_TRIGGER,
        IDI_ICON17_POLYGON_EXPLORE,
        IDI_ICON18_POLYGON_EXIT,
        IDI_ICON19_POLYGON_MINOR,
        IDI_ICON20_POLYGON_MAJOR,

        IDI_ICON21_POLIGON_GLUE,
        IDI_ICON22_POLYGON_GLUE_TRIGGER,
        IDI_ICON23_POLYGON_SUPER_GLUE,
    };
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        loadIcon(id[i], &this->imageList);
    }
    polygonTypeListCtrl.SetImageList(&imageList, LVSIL_SMALL);
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        polygonTypeListCtrl.InsertItem(i, theApp.polygonTypeInformations[i].jname, i);
    }
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
