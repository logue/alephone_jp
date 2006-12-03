// SequencesDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "SequencesDialog.h"


// CSequencesDialog ダイアログ

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
    DDX_Control(pDX, IDC_EDIT15, highNumberOfViews);
    DDX_Control(pDX, IDC_EDIT16, highFramesPerView);
    DDX_Control(pDX, IDC_EDIT17, highTicksPerView);
    DDX_Control(pDX, IDC_EDIT18, highKeyFrame);
    DDX_Control(pDX, IDC_EDIT19, highTransferMode);
    DDX_Control(pDX, IDC_EDIT20, highPeriod);
    DDX_Control(pDX, IDC_COMBO4, highFirstFrameSound);
    DDX_Control(pDX, IDC_COMBO5, highKeyFrameSound);
    DDX_Control(pDX, IDC_COMBO6, highLastFrameSound);
    DDX_Control(pDX, IDC_EDIT21, highPixelsToWorld);
    DDX_Control(pDX, IDC_EDIT22, highLoopFrames);
}


BEGIN_MESSAGE_MAP(CSequencesDialog, CDialog)
    ON_WM_PAINT()
    ON_CBN_SELCHANGE(IDC_COMBO1, &CSequencesDialog::OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO3, &CSequencesDialog::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CSequencesDialog メッセージ ハンドラ

BOOL CSequencesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CSequencesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //store collections
    for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
        collectionCmb.InsertString(i, theApp.collectionInformations[i].jname);
    }
    for(int i = 0; i < NUMBER_OF_COLLECTION_TYPES; i ++){
        typeCmb.InsertString(i, theApp.collectionTypeInformations[i].jname);
    }
    //setupDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
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
    for(int i = 0; i < colDef->high_level_shape_count; i ++){
        high_level_shape_definition* highDef =
            get_high_level_shape_definition(theApp.collection, i);
        char buf[256];
        sprintf(buf, "%d:%s", i, highDef->name);
        highLevelShapeIndexCmb.InsertString(i, CString(buf));
    }
    if(colDef->high_level_shape_count > 0){
        highLevelShapeIndexCmb.SetCurSel(0);
    }

    UpdateData();

}

void CSequencesDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: ここにメッセージ ハンドラ コードを追加します。
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。
    if(theApp.isShapesLoaded){
        int collectionIndex = theApp.collection;
    }
}

//change selection of collection combo box
void CSequencesDialog::OnCbnSelchangeCombo1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int sel = collectionCmb.GetCurSel();
    theApp.collection = sel;
    //update dialog's datas
    if(theApp.isShapesLoaded){
        setupDialog();
    }
}

void CSequencesDialog::OnCbnSelchangeCombo3()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    if(theApp.isShapesLoaded){
        setupHighLevelData();
    }
}

void CSequencesDialog::setupHighLevelData()
{
    int collection = theApp.collection;
    int highLevelIndex = highLevelShapeIndexCmb.GetCurSel();
    high_level_shape_definition* highDef = get_high_level_shape_definition(collection, highLevelIndex);

    setIntegerNum(highDef->number_of_views, &highNumberOfViews);
    setIntegerNum(highDef->frames_per_view, &highFramesPerView);
    setIntegerNum(highDef->ticks_per_frame, &highTicksPerView);
    setIntegerNum(highDef->key_frame, &highKeyFrame);
    setIntegerNum(highDef->transfer_mode, &highTransferMode);
    setIntegerNum(highDef->transfer_mode_period, &highPeriod);
    //sound

    setIntegerNum(highDef->pixels_to_world, &highPixelsToWorld);
    setIntegerNum(highDef->loop_frame, &highLoopFrames);

    UpdateData();
}
