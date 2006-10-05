// PolygonPropertyDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PolygonPropertyDialog.h"


// CPolygonPropertyDialog ダイアログ

IMPLEMENT_DYNAMIC(CPolygonPropertyDialog, CDialog)

CPolygonPropertyDialog::CPolygonPropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPolygonPropertyDialog::IDD, pParent)
{
    memset(&store, 0, sizeof(polygon_data));
}

CPolygonPropertyDialog::~CPolygonPropertyDialog()
{
}

void CPolygonPropertyDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, idNum);
    DDX_Control(pDX, IDC_COMBO1, typeCmb);
    DDX_Control(pDX, IDC_EDIT2, permutationNum);
    DDX_Control(pDX, IDC_COMBO4, floorLightCmb);
    DDX_Control(pDX, IDC_COMBO5, ceilingLightCmb);
    DDX_Control(pDX, IDC_EDIT5, areaNum);
    DDX_Control(pDX, IDC_EDIT6, firstObjectNum);
    DDX_Control(pDX, IDC_EDIT4, floorExZone);
    DDX_Control(pDX, IDC_EDIT3, lineExZone);
    DDX_Control(pDX, IDC_EDIT8, floorTrans);
    DDX_Control(pDX, IDC_EDIT7, ceilingTrans);
    DDX_Control(pDX, IDC_EDIT9, firstNeighbourNum);
    DDX_Control(pDX, IDC_EDIT10, nearCountNum);
    DDX_Control(pDX, IDC_EDIT11, centerXNum);
    DDX_Control(pDX, IDC_EDIT12, centerYNum);
    DDX_Control(pDX, IDC_EDIT13, floorOriginNum);
    DDX_Control(pDX, IDC_EDIT14, ceilingOrigiinNum);
    DDX_Control(pDX, IDC_COMBO9, mediaCmb);
    DDX_Control(pDX, IDC_COMBO8, mediaLightCmb);
    DDX_Control(pDX, IDC_EDIT15, soundSourceIndexNum);
    DDX_Control(pDX, IDC_COMBO7, ambientSoundIndexNum);
    DDX_Control(pDX, IDC_COMBO6, randomSoundCmb);
    DDX_Control(pDX, IDC_EDIT16, floorOriginYNum);
    DDX_Control(pDX, IDC_EDIT17, ceilingOriginYNum);
}


BEGIN_MESSAGE_MAP(CPolygonPropertyDialog, CDialog)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_BUTTON1, &CPolygonPropertyDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPolygonPropertyDialog メッセージ ハンドラ

BOOL CPolygonPropertyDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CPolygonPropertyDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CPolygonPropertyDialog::PostNcDestroy()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CPolygonPropertyDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}
void CPolygonPropertyDialog::setupDialog(int index_)
{
    if(index_ < 0 || index_ >= (int)PolygonList.size()){
        char cstr[256];
        sprintf(cstr, "illigal polygon index:%d", index_);
        MessageBox(CString(cstr));
        return;
    }
    index = index_;
    polygon_data *polygon = &PolygonList[index];
    memcpy(&store, polygon, sizeof(polygon_data));

    setupDialogByStore();
}
void CPolygonPropertyDialog::setupDialogByStore()
{
    //id
    setIntegerNum(index, &idNum);

    //type

    //per
    setIntegerNum(store.permutation, &permutationNum);

    //floor light
    //ceiling light

    //area
    setIntegerNum(store.area, &areaNum);

    //first object
    setIntegerNum(store.first_object, &firstObjectNum);

    //floor ex zone
    setIntegerNum(store.first_exclusion_zone_index, &floorExZone);

    //line ex zone
    setIntegerNum(store.line_exclusion_zone_count, &lineExZone);

    //floor trans
    setIntegerNum(store.floor_transfer_mode, &floorTrans);
    //ceiling trans
    setIntegerNum(store.ceiling_transfer_mode, &ceilingTrans);

    //1st neighbour
    setIntegerNum(store.first_neighbor_index, & firstNeighbourNum);
    //neighbours
    setIntegerNum(store.neighbor_count, &nearCountNum);

    //center
    setIntegerNum(store.center.x, &centerXNum);
    setIntegerNum(store.center.y, &centerYNum);

    //origin
    setIntegerNum(store.floor_origin.x, &floorOriginNum);
    setIntegerNum(store.floor_origin.y, &floorOriginYNum);
    setIntegerNum(store.ceiling_origin.x, &ceilingOrigiinNum);
    setIntegerNum(store.ceiling_origin.y, &ceilingOriginYNum);

    //media

    //snd src
    setIntegerNum(store.sound_source_indexes, &soundSourceIndexNum);

    BOOL enabling = TRUE;
    if(store.type == _polygon_is_platform){
        //ボタン有効
    }else{
        enabling = FALSE;
    }
    GetDlgItem(IDC_BUTTON1)->EnableWindow(enabling);

    //ambient sound
    //random sound

    UpdateData();
}

//show 
void CPolygonPropertyDialog::OnBnClickedButton1()
{
    CPolygonDialog dlg;
    if(dlg.DoModal() == IDOK){
        //値をプラットフォームデータに反映
        platform_data* platform = searchPlatformByPolygonIndex(index);
        //null?
    }
}
