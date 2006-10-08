// MonsterPropertyDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "MonsterPropertyDialog.h"
#include ".\monsterpropertydialog.h"


// CMonsterPropertyDialog ダイアログ

IMPLEMENT_DYNAMIC(CMonsterPropertyDialog, CDialog)

CMonsterPropertyDialog::CMonsterPropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMonsterPropertyDialog::IDD, pParent)
{
    parent = pParent;
    //NONE
    selectedObjectIndex = NONE;
    memset(&store, 0, sizeof(map_object));
}

CMonsterPropertyDialog::~CMonsterPropertyDialog()
{
    directionCircleImage.DeleteObject();
    directionMarkerImage.DeleteObject();
}

void CMonsterPropertyDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO2, objectTypeCmb);
    DDX_Control(pDX, IDC_EDIT_OBJECT_TYPE, objectTypeNum);
    DDX_Control(pDX, IDC_COMBO3, objectClassedTypeCmb);
    DDX_Control(pDX, IDC_EDIT_TYPE, objectClassedTypeNum);
    DDX_Control(pDX, IDC_CHECK1, objectFlags[0]);
    DDX_Control(pDX, IDC_CHECK2, objectFlags[1]);
    DDX_Control(pDX, IDC_CHECK3, objectFlags[2]);
    DDX_Control(pDX, IDC_CHECK4, objectFlags[3]);
    DDX_Control(pDX, IDC_CHECK5, objectFlags[4]);
    DDX_Control(pDX, IDC_CHECK6, objectFlags[5]);
    DDX_Control(pDX, IDC_EDIT_POLYGON_INDEX, objectPolygonId);
    DDX_Control(pDX, IDC_COMBO1, objectActivation);
    DDX_Control(pDX, IDC_EDIT3, objectPositionX);
    DDX_Control(pDX, IDC_EDIT4, objectPositionY);
    DDX_Control(pDX, IDC_EDIT5, objectPositionZ);
    DDX_Control(pDX, IDC_EDIT1, objectFacingNum);
}


BEGIN_MESSAGE_MAP(CMonsterPropertyDialog, CDialog)
    ON_WM_CLOSE()
    ON_WM_PAINT()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_CBN_SELCHANGE(IDC_COMBO2, &CMonsterPropertyDialog::OnCbnSelchangeCombo2)
    ON_CBN_SELCHANGE(IDC_COMBO3, &CMonsterPropertyDialog::OnCbnSelchangeCombo3)
    ON_BN_CLICKED(IDC_CHECK1, &CMonsterPropertyDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &CMonsterPropertyDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK3, &CMonsterPropertyDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK4, &CMonsterPropertyDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK5, &CMonsterPropertyDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK6, &CMonsterPropertyDialog::OnBnClickedCheck1)
END_MESSAGE_MAP()



// CMonsterPropertyDialog メッセージ ハンドラ
BOOL CMonsterPropertyDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CMonsterPropertyDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CMonsterPropertyDialog::PostNcDestroy()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CMonsterPropertyDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

void CMonsterPropertyDialog::setupDialog(int indexOfSavedObjectList)
{
    if(!theApp.isObjectPropertyDialogShow){
        theApp.isObjectPropertyDialogShow = TRUE;
        ShowWindow(TRUE);
    }
    if(indexOfSavedObjectList > (int)SavedObjectList.size()){
        MessageBox(L"Out of index(object property)");
        return;
    }
    map_object* obj = &SavedObjectList[indexOfSavedObjectList];
    memcpy(&store, obj, sizeof(map_object));
    selectedObjectIndex = indexOfSavedObjectList;
    objectTypeCmb.SetCurSel(store.type);
    setupDialogByStore();

    //RedrawWindow();
    Invalidate(FALSE);
    UpdateData();
}

void CMonsterPropertyDialog::setupDialogByStore()
{
    //object->type;
    setIntegerNum(store.type, &objectTypeNum);
    //setComboAndIntegerNum(store.type, 0,
    //    &objectTypeNum, &objectTypeCmb);

    //store classed type (index) combo
    storeClassedTypeCombo(store.type);

    //classed type (= index)
    setComboAndIntegerNum(store.index, 0,
        &objectClassedTypeNum, &objectClassedTypeCmb);

    //object->facing
    setIntegerNum(store.facing, &objectFacingNum);

    //object->flags >>> checks
    for(int i = 0; i < NUMBER_OF_OBJECT_FLAGS; i ++){
        int check = 0;
        if(store.flags & theApp.objectFlagInformations[i].bind){
            check = 1;
        }
        this->objectFlags[i].SetCheck(check);
    }
    //object->location
    setIntegerNum(store.location.x, &objectPositionX);
    setIntegerNum(store.location.y, &objectPositionY);
    setIntegerNum(store.location.z, &objectPositionZ);
    //object->polygon_index
    setIntegerNum(store.polygon_index, &objectPolygonId);

    /*
    int objectType = objectTypeCmb.GetCurSel();
    storeClassedTypeCombo(objectType);

    //set num
    setComboAndIntegerNum(objectType, 0,
        &objectClassedTypeNum, &objectClassedTypeCmb);

    //set number
    setIntegerNum(objectType, &objectTypeNum);

    //enable changing
    store.type = objectType;
    if(selectedObjectIndex >= 0){
        int old = SavedObjectList[selectedObjectIndex].type;
        SavedObjectList[selectedObjectIndex].type = objectType;
        if(old != objectType){
            SavedObjectList[selectedObjectIndex].index = 0;
        }
    }*/

    Invalidate(FALSE);
    UpdateData();
}

// initialize dialog
BOOL CMonsterPropertyDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください

    //load object type combo
    for(int i = 0; i < NUMBER_OF_OBJECT_TYPES; i ++){
        objectTypeCmb.InsertString(i, theApp.objectTypeInformations[i].jname);
    }
    //activation
    for(int i = 0; i < NUMBER_OF_ACTIVATE_TYPES; i ++){
        objectActivation.InsertString(i, theApp.activateTypeInformations[i].jname);
    }
    //setup bitmaps
    directionCircleImage.LoadBitmap(IDB_BITMAP_CIRCLE);
    directionMarkerImage.LoadBitmap(IDB_BITMAP_MARKER);

    //set default(selectedObjectIndex is -1)
    memset(&store, 0, sizeof(map_object));
    setupDialogByStore();
    objectTypeCmb.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CMonsterPropertyDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    //ブラシ
    CBrush whiteBrush;
    whiteBrush.CreateSolidBrush(RGB(255,255,255));
    //CBrush *oldBrush = dc.SelectObject(&whiteBrush);
    CPen blackSmallPen;
    blackSmallPen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
    CBrush yellowBrush;
    yellowBrush.CreateSolidBrush(RGB(255,255,0));


    // TODO : ここにメッセージ ハンドラ コードを追加します。
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。
    {
        CWnd *pictureBox = GetDlgItem(IDC_STATIC_ANGLE);
        //領域確保
        CRect r;
        pictureBox->GetClientRect(&r);

        CDC *picDC = pictureBox->GetDC();
        CBrush *oldBrush = picDC->SelectObject(&whiteBrush);
        CPen *oldPen = picDC->SelectObject(&blackSmallPen);
        CDC memDC;
        memDC.CreateCompatibleDC(picDC);

        //背景色
        picDC->Rectangle(r);
        picDC->SelectObject(oldBrush);


        POINT center = r.CenterPoint();
        //facing
        {
            memDC.SelectObject(&directionCircleImage);
            BITMAP bmpInfo;
            directionCircleImage.GetBitmap(&bmpInfo);
            int x = center.x - bmpInfo.bmWidth / 2;
            int y = center.y - bmpInfo.bmHeight / 2;
            picDC->BitBlt(x,y,bmpInfo.bmWidth, bmpInfo.bmHeight,
                &memDC, 0,0, SRCCOPY);

        }

        //marker
        {
            memDC.SelectObject(&directionMarkerImage);
            BITMAP bmpInfo;
            directionMarkerImage.GetBitmap(&bmpInfo);
            int facing = store.facing;
            int degree = facing * 360 / 512 ;
            int x = (int)(center.x + bmpInfo.bmWidth * cos(degreeToRadian(degree)));
            int y = (int)(center.y + bmpInfo.bmHeight * sin(degreeToRadian(degree)));
            x -= bmpInfo.bmWidth / 2;
            y -= bmpInfo.bmHeight / 2;
            ::TransparentBlt(picDC->m_hDC,
                x, x,
                bmpInfo.bmWidth, bmpInfo.bmHeight, memDC.m_hDC,
                    0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255,255,255));
        }

        //目盛り
        /*const double GUIDE_LENGTH = 40;
        const int ANGULAR_DIVIDES = 8;
        for(int i = 0; i < ANGULAR_DIVIDES; i ++){
            double dx = GUIDE_LENGTH / 2 * 
                cos(degreeToRadian(i * 360 / ANGULAR_DIVIDES));
            double dy = GUIDE_LENGTH / 2 * 
                sin(degreeToRadian(i * 360 / ANGULAR_DIVIDES));
            double x0 = center.x + dx;
            double y0 = center.x + dy;
            double x1 = center.x - dx;
            double y1 = center.y - dy;
            picDC->MoveTo((LONG)x0, (LONG)y0);
            picDC->LineTo((LONG)x1, (LONG)y1);
        }
        //if(obj){
            picDC->SelectObject(blackSmallPen);
            picDC->SelectObject(yellowBrush);
            //描画
            const double SIZE = 20;
            int facing = store.facing;
            double degree = (double)facing / (1<<ANGULAR_BITS) * 360.0;
            POINT pt[3];
            pt[0].x = (LONG)(center.x + SIZE * cos(degreeToRadian(degree)));
            pt[0].y = (LONG)(center.y + SIZE * sin(degreeToRadian(degree)));
            pt[1].x = (LONG)(center.x + SIZE / 2 * cos(degreeToRadian(degree + 120)));
            pt[1].y = (LONG)(center.y + SIZE / 2 * sin(degreeToRadian(degree + 120)));
            pt[2].x = (LONG)(center.x + SIZE / 2 * cos(degreeToRadian(degree - 120)));
            pt[2].y = (LONG)(center.y + SIZE / 2 * sin(degreeToRadian(degree - 120)));
            Polygon(picDC->m_hDC, pt, 3);
        //}
        */
        memDC.DeleteDC();
    }

    //dc.SelectObject(oldBrush);
    //dc.SelectObject(oldPen);
    yellowBrush.DeleteObject();
    blackSmallPen.DeleteObject();
    whiteBrush.DeleteObject();
}

//destroy window
BOOL CMonsterPropertyDialog::DestroyWindow()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    this->ShowWindow(FALSE);
    theApp.isObjectPropertyDialogShow = FALSE;
    return TRUE;//CDialog::DestroyWindow();
}
////////////////////////////////////
//on mouse move
void CMonsterPropertyDialog::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(nFlags & MK_LBUTTON){
        clickFacing(point.x, point.y);
    }
    CDialog::OnMouseMove(nFlags, point);
}

//on mouse Left button down
void CMonsterPropertyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    clickFacing(point.x, point.y);
    CDialog::OnLButtonDown(nFlags, point);
}
//click at facing
void CMonsterPropertyDialog::clickFacing(int px, int py)
{
    CWnd *pictureBox = GetDlgItem(IDC_STATIC_ANGLE);
    CRect rect;
    pictureBox->GetClientRect(&rect);
    if(!isPointInRect<LONG>((LONG)px, (LONG)py, rect.left, rect.top, rect.right, rect.bottom)){
        return;
    }
    //中心座標
    int centerx = rect.left + rect.Width() / 2;
    int centery = rect.top + rect.Height() / 2;
    //sub
    int dx = centerx + rect.left - px;
    int dy = centery + rect.top - py;
    double rad = getDegreeFromVector(dx, dy);
    int degree = (int)radianToDegree(rad);
    //[0,360]->[0,512]
    int facing = degree / 360 * 512;
    store.facing = facing;
    //enable changing
    if(selectedObjectIndex >= 0){
        SavedObjectList[selectedObjectIndex].facing = facing;
    }

    UpdateData();
    Invalidate(FALSE);
}
//////////////////////////////
//get flags num
int CMonsterPropertyDialog::getFlags()
{
    //checkbox >>> flags
    int flags = 0;
    for(int i = 0; i < NUMBER_OF_OBJECT_FLAGS; i ++){
        if(objectFlags[i].GetCheck()){
            flags |= theApp.objectFlagInformations[i].bind;
        }
    }
    return flags;
}

void CMonsterPropertyDialog::storeClassedTypeCombo(int objectType)
{
    objectClassedTypeCmb.ResetContent();
    Information *informations = NULL;
    int max = 0;
    switch(objectType){
    case _saved_monster:
        max = NUMBER_OF_MONSTER_TYPES;
        informations = theApp.monsterTypeInformations;
        break;
    case _saved_object:
        max = NUMBER_OF_SCENERY_DEFINITIONS;
        informations = theApp.sceneryTypeInformations;
        break;
    case _saved_item:
        max = NUMBER_OF_DEFINED_ITEMS;
        informations = theApp.itemTypeInformations;
        break;
    case _saved_player:
        /*max = 1;
        informations = theApp.;*/
        break;
    case _saved_goal:
        /*max = 1;
        informations = theApp.monsterTypeInformations;*/
        break;
    case _saved_sound_source:
        max = NUMBER_OF_AMBIENT_SOUND_DEFINITIONS;
        informations = theApp.soundSourceInformations;
        break;
    default:
        MessageBox(L"object type error");
    }
    //store them
    for(int i = 0; i < max; i ++){
        objectClassedTypeCmb.InsertString(i, informations[i].jname);
    }
}

//select type combo
void CMonsterPropertyDialog::OnCbnSelchangeCombo2()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int oldType = store.type;
    int objectType = objectTypeCmb.GetCurSel();
    store.type = objectType;
    if(selectedObjectIndex >= 0){
        SavedObjectList[selectedObjectIndex].type = objectType;
    }
    //change object 
    setupDialogByStore();

    if(oldType != store.type){
        //set select
        this->objectClassedTypeCmb.SetCurSel(0);
    }
    //基本数増加
    addInitialPlacement(store.type, store.index, 1);
    UpdateData();
}
//classed type combo
void CMonsterPropertyDialog::OnCbnSelchangeCombo3()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    //set num
    int oldIndex = store.index;
    int index = objectClassedTypeCmb.GetCurSel();
    setIntegerNum(index, &objectClassedTypeNum);

    if(index != oldIndex){
        //initial ++;
        addInitialPlacement(store.type, index, 1);
    }
    //enable changing
    store.index = index;
    if(selectedObjectIndex >= 0){
        SavedObjectList[selectedObjectIndex].index = index;
    }
    UpdateData();
}
void CMonsterPropertyDialog::setSelectedObjectIndex(int indexOfSavedObjectList)
{
    selectedObjectIndex = indexOfSavedObjectList;
}
int CMonsterPropertyDialog::getSelectedObjectIndex()
{
    return selectedObjectIndex;
}
//change flags
void CMonsterPropertyDialog::OnBnClickedCheck1()
{
    //setup flags
    int flags = getFlags();

    //enable changing
    store.flags = flags;
    if(selectedObjectIndex >= 0){
        SavedObjectList[selectedObjectIndex].flags = flags;
    }


}
