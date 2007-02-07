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
        MessageBox(TEXT("Failed"));
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
    //polygon index
    index = index_;
    polygon_data *polygon = &PolygonList[index];
    memcpy(&store, polygon, sizeof(polygon_data));

    setupDialogByStore();
}

void CPolygonPropertyDialog::setupLightSourceIndex(CComboBox* combo,
                                                   int index, int max)
{
    //clear 
    combo->ResetContent();
    //store lights
    {
        char cstr[10];
        for(int i = 0; i < (int)LightList.size(); i ++){
            sprintf(cstr, "%d", i);
            combo->InsertString(i, CString(cstr));
        }
    }
    //set cur select
    if(index == NONE){
        index = max;
    }
    combo->SetCurSel(index);
}

void CPolygonPropertyDialog::setupDialogByStore()
{
    //id
    setIntegerNum(index, &idNum);

    //type
    //選択
    typeCmb.SetCurSel(store.type);

    //per
    setIntegerNum(store.permutation, &permutationNum);

    //floor light
    this->setupLightSourceIndex(&floorLightCmb, store.floor_lightsource_index,
        (int)LightList.size());

    //ceiling light
    this->setupLightSourceIndex(&ceilingLightCmb, store.ceiling_lightsource_index,
        (int)LightList.size());

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
    //media light
    this->setupLightSourceIndex(&mediaLightCmb, store.media_lightsource_index,
        (int)LightList.size());

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
    setCombo(store.ambient_sound_image_index, NUMBER_OF_AMBIENT_SOUND_DEFINITIONS,
        &ambientSoundIndexNum);
    //random sound
    setCombo(store.random_sound_image_index, NUMBER_OF_RANDOM_SOUND_DEFINITIONS,
        &randomSoundCmb);

    UpdateData();
}

//show platform dialog
void CPolygonPropertyDialog::OnBnClickedButton1()
{
    int platformIndex = searchPlatformIndexByPolygonIndex(index);
    if(platformIndex == NONE){
        char cstr[10];
        sprintf(cstr, "%d", index);
        AfxMessageBox(CString("Cannot search platform of polygon=") + 
            CString(cstr) );
    }else{
        CPlatformDialog dlg((CWnd*)this, platformIndex);
        if(dlg.DoModal() == IDOK){
            //値をプラットフォームデータに反映
            platform_data* platform = &PlatformList[searchPlatformIndexByPolygonIndex(index)];
            //null?
        }
    }
}

BOOL CPolygonPropertyDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString none = CString("* none *");
    // TODO:  ここに初期化を追加してください
    //store polygon type names
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        typeCmb.InsertString(i, theApp.polygonTypeInformations[i].jname);
    }

    //store sound sources
    for(int i = 0; i < NUMBER_OF_AMBIENT_SOUND_DEFINITIONS; i ++){
        ambientSoundIndexNum.InsertString(i, theApp.ambientSoundTypeInformations[i].jname);
    }
    ambientSoundIndexNum.InsertString(NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, none);

    for(int i = 0; i < NUMBER_OF_RANDOM_SOUND_DEFINITIONS; i ++){
        randomSoundCmb.InsertString(i, theApp.randomSoundTypeInformations[i].jname);
    }
    randomSoundCmb.InsertString(NUMBER_OF_RANDOM_SOUND_DEFINITIONS, none);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
