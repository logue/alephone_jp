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
    memset(&obj, 0, sizeof(map_object));
}

CMonsterPropertyDialog::~CMonsterPropertyDialog()
{
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

void CMonsterPropertyDialog::setupDialog(map_object *object)
{
    if(object == NULL){
        //obj = NULL;
    }else{
        memcpy(&obj, object, sizeof(map_object));

        //コンボを空にする
        //
        objectClassedTypeCmb.Clear();
        
        //object->type;
        setComboAndIntegerNum(object->type, 0,
            &objectTypeNum, &objectTypeCmb);
        
        Information *informations = NULL;
        int max = 0;
        switch(object->type){
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
        for(int i = 0; i < max; i ++){
            objectClassedTypeCmb.InsertString(i, informations[i].jname);
        }
        
        //object->index;
        setComboAndIntegerNum(object->index, 0,
            &objectClassedTypeNum, &objectClassedTypeCmb);

        //object->facing
        setIntegerNum(object->facing, &objectFacingNum);

        //object->flags >>> checks
        for(int i = 0; i < NUMBER_OF_OBJECT_FLAGS; i ++){
            int check = 0;
            if(object->flags & theApp.objectFlagInformations[i].bind){
                check = 1;
            }
            this->objectFlags[i].SetCheck(check);
        }
        //object->location
        setIntegerNum(object->location.x, &objectPositionX);
        setIntegerNum(object->location.y, &objectPositionY);
        setIntegerNum(object->location.z, &objectPositionZ);
        //object->polygon_index
        setIntegerNum(object->polygon_index, &objectPolygonId);
    }

    RedrawWindow();
}

BOOL CMonsterPropertyDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください

    for(int i = 0; i < NUMBER_OF_OBJECT_TYPES; i ++){
        objectTypeCmb.InsertString(i, theApp.objectTypeInformations[i].jname);
    }

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

        //背景色
        picDC->Rectangle(r);
        picDC->SelectObject(oldBrush);


        POINT center = r.CenterPoint();
        //目盛り
        const double GUIDE_LENGTH = 40;
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
            int facing = obj.facing;
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
    }

    //dc.SelectObject(oldBrush);
    //dc.SelectObject(oldPen);
    yellowBrush.DeleteObject();
    blackSmallPen.DeleteObject();
    whiteBrush.DeleteObject();
}

BOOL CMonsterPropertyDialog::DestroyWindow()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    this->ShowWindow(FALSE);
    theApp.isObjectPropertyDialogShow = FALSE;
    return TRUE;//CDialog::DestroyWindow();
}

void CMonsterPropertyDialog::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(nFlags & MK_LBUTTON){
        clickFacing(point.x, point.y);
    }
    CDialog::OnMouseMove(nFlags, point);
}

void CMonsterPropertyDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    
    CDialog::OnLButtonDown(nFlags, point);
}

void CMonsterPropertyDialog::clickFacing(int px, int py)
{
    CWnd *pictureBox = GetDlgItem(IDC_STATIC_ANGLE);
    CRect rect;
    pictureBox->GetClientRect(&rect);
}

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
