// SequencesDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "SequencesDialog.h"


// CSequencesDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CSequencesDialog, CDialog)
CSequencesDialog::CSequencesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSequencesDialog::IDD, pParent)
{
}

CSequencesDialog::~CSequencesDialog()
{
}

void CSequencesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, collectionCmb);
    DDX_Control(pDX, IDC_EDIT2, versionNum);
    DDX_Control(pDX, IDC_COMBO2, typeCmb);
    DDX_Control(pDX, IDC_EDIT3, flagNum);
    DDX_Control(pDX, IDC_EDIT4, colorCountNum);
    DDX_Control(pDX, IDC_EDIT5, CLUTCountNum);
    DDX_Control(pDX, IDC_EDIT6, colorTableOffsetNum);
    DDX_Control(pDX, IDC_EDIT7, highLevelShapeCountNum);
    DDX_Control(pDX, IDC_EDIT8, highLevelShapeOffsetTableOffsetNum);
    DDX_Control(pDX, IDC_EDIT9, lowLevelShapeCountNum);
    DDX_Control(pDX, IDC_EDIT10, lowLevelShapeOffsetTableOffsetNum);
    DDX_Control(pDX, IDC_EDIT11, bitmapCountNum);
    DDX_Control(pDX, IDC_EDIT12, bitmapOffsetTableOffset);
    DDX_Control(pDX, IDC_EDIT13, pixelsToWorldNum);
    DDX_Control(pDX, IDC_EDIT14, sizeNum);
    DDX_Control(pDX, IDC_COMBO3, highLevelShapeIndexCmb);
}


BEGIN_MESSAGE_MAP(CSequencesDialog, CDialog)
    ON_WM_PAINT()
    ON_CBN_SELCHANGE(IDC_COMBO1, &CSequencesDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CSequencesDialog ���b�Z�[�W �n���h��

BOOL CSequencesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CSequencesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    //store collections
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        collectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }
    for(int i = 0; i < NUMBER_OF_COLLECTION_TYPES; i ++){
        typeCmb.InsertString(i, theApp.collectionTypeInformations[i].jname);
    }
    //setupDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CSequencesDialog::setupDialog()
{
    if(!theApp.isShapesLoaded){
        return;
    }
    //
    int col = theApp.collection;
    collectionCmb.SetCurSel(col);

    //collection_definition
    struct collection_definition* colDef = get_collection_definition(col);

    //version
    setIntegerNum(colDef->version, &versionNum);

    //type
    typeCmb.SetCurSel(colDef->type);

    //flags
    setIntegerNum(colDef->flags, &flagNum);

    //color
    setIntegerNum(colDef->color_count, &colorCountNum);
    setIntegerNum(colDef->clut_count, &CLUTCountNum);
    setIntegerNum(colDef->color_table_offset, &colorTableOffsetNum);

    //high level shapes
    setIntegerNum(colDef->high_level_shape_count, &highLevelShapeCountNum);
    setIntegerNum(colDef->high_level_shape_offset_table_offset, &highLevelShapeOffsetTableOffsetNum);

    //low level shapes
    setIntegerNum(colDef->low_level_shape_count, &lowLevelShapeCountNum);
    setIntegerNum(colDef->low_level_shape_offset_table_offset, &lowLevelShapeOffsetTableOffsetNum);

    //bitmaps
    setIntegerNum(colDef->bitmap_count, &bitmapCountNum);
    setIntegerNum(colDef->bitmap_offset_table_offset, &bitmapOffsetTableOffset);

    //pixels
    setIntegerNum(colDef->pixels_to_world, &pixelsToWorldNum);
    
    //size
    setIntegerNum(colDef->size, &sizeNum);

    //********************************* high level shape info ***
    //clear combo
    highLevelShapeIndexCmb.ResetContent();
    //store them
    /*for(int i = 0; i < colDef->high_level_shape_count; i ++){
        high_level_shape_definition* highDef =
            get_high_level_shape_definition(
    }*/
    UpdateData();

}

void CSequencesDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B
    if(theApp.isShapesLoaded){
        int collectionIndex = theApp.collection;
    }
}

//change selection of collection combo box
void CSequencesDialog::OnCbnSelchangeCombo1()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    int sel = collectionCmb.GetCurSel();
    theApp.collection = sel;
    //update dialog's datas
    if(theApp.isShapesLoaded){
        setupDialog();
    }
}
