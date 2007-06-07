#include "MapEditorWX.h"
#include "MapEditorMainFrame.h"

IMPLEMENT_APP(MapEditorWX)

//load color informations

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;
const int WINDOW_DEFAULT_X = 50;
const int WINDOW_DEFAULT_Y = 50;
const int BUF_MAX = 1024;

static char *DATA_DIR_NAME = "./data/";
static char *INI_FILE_NAME = "./setting.ini";
static char * MAP_ICONS_DIR_NAME = "Map Icons/";
static char * HILIGHTED_ICONS_DIR_NAME = "Highlighted/";
static char * MAP_ICONS_IMAGE_NAME_LIST_FILE_NAME = "MapIconImageList.txt";
const int START_OF_TEXTURE = _collection_walls1;
static char* TAG_NAME_FILE_PATH = "data/InnerSettingTagList.ini";
static char* INNER_DATA_FILE_PATH = "data/InnerSetting.ini";

bool MapEditorWX::OnInit()
{
    //一般的な初期設定
    if(!this->initialize()){
        wxMessageBox(_T("Initialize failure"));
        exit(-1);
    }

    //ウインドウフレームを生成します
    MapEditorMainFrame *frame = new MapEditorMainFrame(
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
    }

    //levelNameList

    //面
    this->editLevelIndex = 0;

    //polygonTypeColorList
    //heightColorList

    //情報読み込み

    //オブジェクト全般
    hpl::aleph::loadInformation("data/ObjectTypes.txt", NUMBER_OF_OBJECT_TYPES, &this->objectTypeInfo);
    //モンスター
    hpl::aleph::loadInformation("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES,, &this->monsterTypeInfo);
    //オブジェ
    hpl::aleph::loadInformation("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS, &this->sceneryTypeInfo);
    //アイテム
    hpl::aleph::loadInformation("data/DefinedItemsTypes.txt", NUMBER_OF_DEFINED_ITEMS, &this->itemTypeInfo);
    //音
    hpl::aleph::loadInformation("data/SoundSourceTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, &this->soundSourceTypeInfo);
    //起動
    hpl::aleph::loadInformation("data/ActivateTypes.txt", NUMBER_OF_ACTIVATE_TYPES, &this->activateTypeInfo);

    //フラグ
    this->flagInfo[0].bind = _map_object_is_invisible;
    this->flagInfo[1].bind = _map_object_hanging_from_ceiling;
    this->flagInfo[2].bind = _map_object_is_blind;
    this->flagInfo[3].bind = _map_object_is_deaf;
    this->flagInfo[4].bind = _map_object_floats;
    this->flagInfo[5].bind = _map_object_is_network_only;

    //ターミナル
    hpl::aleph::loadInformation("data/TerminalGroupTypes.txt", NUMBER_OF_GROUP_TYPES, &this->terminalTypeInfo);

    //ポリゴン
    hpl::aleph::loadInformation("data/PolygonType.txt", NUMBER_OF_POLYGON_TYPE, &this->polygonTypeInfo);

    //環境
    hpl::aleph::loadInformation("data/Environments.txt", NUMBER_OF_ENVIRONMENTS, &this->envInfo);
    //背景
    hpl::aleph::loadInformation("data/Landscapes.txt", NUMBER_OF_LANDSPACES, &this->landscapeInfo);

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
    hpl::aleph::loadInformation("data/AmbientSoundTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, &this->ambientSoundTypeInfo);
    //背景
    hpl::aleph::loadInformation("data/RandomSoundTypes.txt", NUMBER_OF_RANDOM_SOUND_DEFINITIONS, &this->randomSoundTypeInfo);

    //色設定読み込み
    if(!this->loadColorSetting()){
        return false;
    }

    //選択関連
    this->selectData.clear();

    //コピペ用ストック
    storedMapData.removeAll();
    storedDataDiffPointDelta[0] = storedDataDiffPointDelta[1] = 0;

    //線の最初の点
    isFirstOfLineToAdd = true;
    //以前選択した点
    prevPointIndex = NONE;

    //グリッド設定
    mapeditorone::MapEditorOneInnerSetting innerSetting =
        mapeditorone::MapEditorOneInnerSetting(TAG_NAME_FILE_PATH, INNER_DATA_FILE_PATH);
    mapeditorone::setupGridManager(this->getViewGridManager(),
        &innserSetting);

    nPolygonPoints = 3;

    //iconBitmaps
    //textureBitmaps
    return true;
}

/*
void wxStringToChar(wxString& str, char* cstr)
{
    int i = 0;
    for(i = 0; i < (int)str.length(); i ++){
        cstr[i] = str.GetChar(i);
    }
    cstr[i] = '\0';
}

*/
hpl::aleph::view::HPLViewGridManager* MapEditorWX::getViewGridManager()
{
    return &this->viewGridManager;
}
//イベントマネージャーを取得します
hpl::aleph::HPLEventManager* MapEditorWX::getEventManager()
{
    return &this->eventManager;
}

//色設定をファイルから読み込む
bool MapEditorWX::loadColorSetting()
{
    //TODO
    return false;
}

