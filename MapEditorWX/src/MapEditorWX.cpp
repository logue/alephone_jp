#include "MapEditorWX.h"
#include "MapEditorMainFrame.h"

IMPLEMENT_APP(MapEditorWX)

//load color informations

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;
const int WINDOW_DEFAULT_X = 50;
const int WINDOW_DEFAULT_Y = 50;
const int BUF_MAX = 1024;


bool MapEditorWX::OnInit()
{
    //一般的な初期設定
    if(!this->initialize()){
        wxMessageBox(_T("Initialize failure"));
        exit(-1);
    }

    //ウインドウフレームを生成します
    frame = new MapEditorMainFrame(
        TITLE_TEXT_BASE,
        wxPoint(WINDOW_DEFAULT_X, WINDOW_DEFAULT_Y), wxSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT));
    frame->Show(true);
    //SetTopWindow(frame);

    
    return TRUE;
}

bool MapEditorWX::initialize()
{
    //設定読み込み
    setting.setIniFileName(INI_FILE_NAME);
    if(!setting.loadSetting()){
        hpl::error::caution("No setting file found. I'll make default one.");
        setting.setSettingToDefault();
        //保存
        setting.saveSetting();
    }
    //levelNameList

    //面
    this->editLevelIndex = 0;

    //polygonTypeColorList
    //heightColorList

    //情報読み込み

    //オブジェクト全般
    hpl::aleph::loadInformation("data/ObjectTypes.txt", NUMBER_OF_OBJECT_TYPES, this->objectTypeInfo);
    //モンスター
    hpl::aleph::loadInformation("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES, this->monsterTypeInfo);
    //オブジェ
    hpl::aleph::loadInformation("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS, this->sceneryTypeInfo);
    //アイテム
    hpl::aleph::loadInformation("data/DefinedItems.txt", NUMBER_OF_DEFINED_ITEMS, this->itemTypeInfo);
    //音
    hpl::aleph::loadInformation("data/SoundSourceTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, this->soundSourceTypeInfo);
    //起動
    hpl::aleph::loadInformation("data/ActivateTypes.txt", NUMBER_OF_ACTIVATE_TYPES, this->activateTypeInfo);

    //フラグ
    this->flagInfo[0].bind = _map_object_is_invisible;
    this->flagInfo[1].bind = _map_object_hanging_from_ceiling;
    this->flagInfo[2].bind = _map_object_is_blind;
    this->flagInfo[3].bind = _map_object_is_deaf;
    this->flagInfo[4].bind = _map_object_floats;
    this->flagInfo[5].bind = _map_object_is_network_only;

    //ターミナル
    hpl::aleph::loadInformation("data/TerminalGroupTypes.txt", NUMBER_OF_GROUP_TYPES, this->terminalTypeInfo);

    //ポリゴン
    hpl::aleph::loadInformation("data/PolygonType.txt", NUMBER_OF_POLYGON_TYPE, this->polygonTypeInfo);

    //環境
    hpl::aleph::loadInformation("data/Environments.txt", NUMBER_OF_ENVIRONMENTS, this->envInfo);
    //背景
    hpl::aleph::loadInformation("data/Landscapes.txt", NUMBER_OF_LANDSPACES, this->landscapeInfo);

    //env type(bind)
    this->envTypeInfo[0].bind = _environment_normal;
    this->envTypeInfo[1].bind = _environment_vacuum;
    this->envTypeInfo[2].bind = _environment_magnetic;
    this->envTypeInfo[3].bind = _environment_rebellion;
    this->envTypeInfo[4].bind = _environment_low_gravity;
    this->envTypeInfo[5].bind = _environment_network;
    this->envTypeInfo[6].bind = _environment_single_player;
    //mission type(bind)
    this->missionTypeInfo[0].bind = _mission_none;
    this->missionTypeInfo[1].bind = _mission_extermination;
    this->missionTypeInfo[2].bind = _mission_exploration;
    this->missionTypeInfo[3].bind = _mission_retrieval;
    this->missionTypeInfo[4].bind = _mission_repair;
    this->missionTypeInfo[5].bind = _mission_rescue;

    //背景
    hpl::aleph::loadInformation("data/AmbientSoundTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, this->ambientSoundTypeInfo);
    //背景
    hpl::aleph::loadInformation("data/RandomSoundTypes.txt", NUMBER_OF_RANDOM_SOUND_DEFINITIONS, this->randomSoundTypeInfo);

    //色設定読み込み
    if(!hpl::aleph::loadColorSetting(POLYGON_COLOR_FILE_NAME, this->polygonTypeColors, NUMBER_OF_POLYGON_TYPE)){
        return false;
    }

    //選択関連
    this->selectData.clear();

    //コピペ用ストック
    storedDataDiffPointDelta[0] = storedDataDiffPointDelta[1] = 0;

    //線の最初の点
    isFirstOfLineToAdd = true;
    //以前選択した点
    prevPointIndex = NONE;

    //グリッド設定
    mapeditorone::MapEditorOneInnerSetting innerSetting =
        mapeditorone::MapEditorOneInnerSetting(TAG_NAME_FILE_PATH, INNER_DATA_FILE_PATH);
    mapeditorone::setupGridManager(this->getViewGridManager(),
        &innerSetting);
    this->getViewGridManager()->setGridIntervalIndex(this->setting.getGridSizeIndex());
    nPolygonPoints = 3;

    //マップのアイコンビットマップをファイルから読み込み
    this->loadIconBitmaps(DATA_DIR_NAME);

    //TODO textureBitmaps

    /*
        TI_ARROW = 0,
        TI_FILL,
        TI_HAND,
        TI_LINE,
        TI_MAGNIFY,
        TI_SKULL,
        TI_TEXT,
        TI_POLYGON,
    */
    char CURSOR_BASE_DIR[] = "data/img/";
    char *cursorSkull = "cursor2.cur";
    char *cursorPolygon = "cur00004.cur";
    int cursorId[] ={
        wxCURSOR_ARROW,
        wxCURSOR_PAINT_BRUSH,
        wxCURSOR_HAND,
        wxCURSOR_PENCIL,
        wxCURSOR_MAGNIFIER,
        -1,
        wxCURSOR_IBEAM,
        -1
    };
    //カーソルデータ読み込み
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
        if(cursorId[i] != -1){
            cursors[i] = wxCursor(cursorId[i]);
        }else{
            //ファイルパス
            char* fname;
            if(i == ToolType::TI_SKULL){
                fname = cursorSkull;
            }else if(i == ToolType::TI_POLYGON){
                fname = cursorPolygon;
            }
            wxString path = wxConvCurrent->cMB2WX(CURSOR_BASE_DIR);
            wxString pathF = wxConvCurrent->cMB2WX(fname);
            path.Append(pathF);
            //読み込み
            wxImage bmp;
            bmp.LoadFile(path, wxBITMAP_TYPE_CUR);
            //カーソル設定
            cursors[i] = wxCursor(bmp);
        }
    }
    return true;
}

hpl::aleph::view::HPLViewGridManager* MapEditorWX::getViewGridManager()
{
    return &this->viewGridManager;
}
//イベントマネージャーを取得します
hpl::aleph::HPLEventManager* MapEditorWX::getEventManager()
{
    return &this->eventManager;
}

//ビュー座標をワールド座標に直す操作の簡易版
world_point2d MapEditorWX::getWorldPointFromViewPoint(int vx, int vy)
{
    hpl::aleph::view::HPLViewGridManager* mgr = this->getViewGridManager();
    int offset[2];
    mgr->getOffset(offset);
    int DIV = mgr->getZoomDivision();
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(vx, vy,
        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, offset[0], offset[1]);
    return wpoint;
}
//
void MapEditorWX::getViewPointFromWorldPoint(world_point2d& wpoint, int vpoint[2])
{
    hpl::aleph::view::HPLViewGridManager* mgr = this->getViewGridManager();
    int offset[2];
    mgr->getOffset(offset);
    int DIV = mgr->getZoomDivision();
    hpl::aleph::map::getViewPointFromWorldPoint2D(wpoint, vpoint,
        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, offset[0], offset[1]);
}

/**
    アイコン用のビットマップファイルを読み込みます
*/
void MapEditorWX::loadIconBitmaps(const char* baseDirPath)
{
    //アイコンビットマップとファイル名、そしてアイテムIDとの対応データをファイルから読み込みます
    const int NUMBER_OF_MAP_ICON_FILES = NUMBER_OF_DEFINED_ITEMS +
        NUMBER_OF_MAP_ICONS;
    hpl::aleph::Information mapIconInfo[NUMBER_OF_MAP_ICON_FILES];

    //ファイル名作成
    char buf[BUF_MAX];
    sprintf(buf, "%s%s", baseDirPath, MAP_ICONS_IMAGE_NAME_LIST_FILE_NAME);
    hpl::aleph::loadInformation(buf, NUMBER_OF_MAP_ICON_FILES, mapIconInfo);

    for(int i = 0; i < 2 * NUMBER_OF_DEFINED_ITEMS + 2 * NUMBER_OF_MAP_ICONS; i ++){
        std::string path = std::string(baseDirPath) + std::string(MAP_ICONS_DIR_NAME);
        const int HILIGHTED_OFFSET = NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MAP_ICONS;

        int index = i;
        if(i >= HILIGHTED_OFFSET){
            //選択（ハイライト状態）
            path += std::string(HILIGHTED_ICONS_DIR_NAME);
            index -= HILIGHTED_OFFSET;
        }
        path += mapIconInfo[index].jname;

        //TODO ビットマップファイル読み込み
        if(i < HILIGHTED_OFFSET){
            //通常状態
            if(index < NUMBER_OF_DEFINED_ITEMS){
                //アイテム
                this->loadBitmap(path.c_str(), &this->itemIconBitmaps[index]);
            }else{
                index -= NUMBER_OF_DEFINED_ITEMS;
                //マップアイコン
                this->loadBitmap(path.c_str(), &this->mapIconBitmaps[index]);
            }
        }else{
            //選択＝ハイライト状態
            if(index < NUMBER_OF_DEFINED_ITEMS){
                //アイテム
                this->loadBitmap(path.c_str(), &this->hilightedItemIconBitmaps[index]);
            }else{
                index -= NUMBER_OF_DEFINED_ITEMS;
                //マップアイコン
                this->loadBitmap(path.c_str(), &this->hilightedMapIconBitmaps[index]);
            }
        }
    }
}

/**
    ビットマップの読み込み（簡易版）
*/
void MapEditorWX::loadBitmap(const char* fname, wxBitmap* bitmap)
{
    if(!bitmap->LoadFile(wxConvCurrent->cMB2WX(fname), wxBITMAP_TYPE_BMP)){
        hpl::error::halt("Couldn't load bitmap[%s]", fname);
    }
}

/**
    現在のモード・ツールにあわせてカーソルを変更します
*/
void MapEditorWX::setCursor()
{
    int editMode = this->getEventManager()->getEditModeType();
    if(editMode == EditModeType::EM_DRAW){
        int toolType = this->getEventManager()->getToolType();
        //TODO カーソル
        ::wxSetCursor(cursors[toolType]);
    }else{
    }
}
