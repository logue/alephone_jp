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
    //��ʓI�ȏ����ݒ�
    if(!this->initialize()){
        wxMessageBox(_T("Initialize failure"));
        exit(-1);
    }

    //�E�C���h�E�t���[���𐶐����܂�
    MapEditorMainFrame *frame = new MapEditorMainFrame(
        TITLE_TEXT_BASE,
        wxPoint(WINDOW_DEFAULT_X, WINDOW_DEFAULT_Y), wxSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT));
    frame->Show(true);
    //SetTopWindow(frame);

    
    return TRUE;
}

bool MapEditorWX::initialize()
{
    //�ݒ�ǂݍ���
    setting.setIniFileName(INI_FILE_NAME);
    if(!setting.loadSetting()){
        hpl::error::caution("No setting file found. I'll make default one.");
        setting.setSettingToDefault();
    }

    //levelNameList

    //��
    this->editLevelIndex = 0;

    //polygonTypeColorList
    //heightColorList

    //���ǂݍ���

    //�I�u�W�F�N�g�S��
    hpl::aleph::loadInformation("data/ObjectTypes.txt", NUMBER_OF_OBJECT_TYPES, &this->objectTypeInfo);
    //�����X�^�[
    hpl::aleph::loadInformation("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES,, &this->monsterTypeInfo);
    //�I�u�W�F
    hpl::aleph::loadInformation("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS, &this->sceneryTypeInfo);
    //�A�C�e��
    hpl::aleph::loadInformation("data/DefinedItemsTypes.txt", NUMBER_OF_DEFINED_ITEMS, &this->itemTypeInfo);
    //��
    hpl::aleph::loadInformation("data/SoundSourceTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, &this->soundSourceTypeInfo);
    //�N��
    hpl::aleph::loadInformation("data/ActivateTypes.txt", NUMBER_OF_ACTIVATE_TYPES, &this->activateTypeInfo);

    //�t���O
    this->flagInfo[0].bind = _map_object_is_invisible;
    this->flagInfo[1].bind = _map_object_hanging_from_ceiling;
    this->flagInfo[2].bind = _map_object_is_blind;
    this->flagInfo[3].bind = _map_object_is_deaf;
    this->flagInfo[4].bind = _map_object_floats;
    this->flagInfo[5].bind = _map_object_is_network_only;

    //�^�[�~�i��
    hpl::aleph::loadInformation("data/TerminalGroupTypes.txt", NUMBER_OF_GROUP_TYPES, &this->terminalTypeInfo);

    //�|���S��
    hpl::aleph::loadInformation("data/PolygonType.txt", NUMBER_OF_POLYGON_TYPE, &this->polygonTypeInfo);

    //��
    hpl::aleph::loadInformation("data/Environments.txt", NUMBER_OF_ENVIRONMENTS, &this->envInfo);
    //�w�i
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

    //�w�i
    hpl::aleph::loadInformation("data/AmbientSoundTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, &this->ambientSoundTypeInfo);
    //�w�i
    hpl::aleph::loadInformation("data/RandomSoundTypes.txt", NUMBER_OF_RANDOM_SOUND_DEFINITIONS, &this->randomSoundTypeInfo);

    //�F�ݒ�ǂݍ���
    if(!this->loadColorSetting()){
        return false;
    }

    //�I���֘A
    this->selectData.clear();

    //�R�s�y�p�X�g�b�N
    storedMapData.removeAll();
    storedDataDiffPointDelta[0] = storedDataDiffPointDelta[1] = 0;

    //���̍ŏ��̓_
    isFirstOfLineToAdd = true;
    //�ȑO�I�������_
    prevPointIndex = NONE;

    //�O���b�h�ݒ�
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
//�C�x���g�}�l�[�W���[���擾���܂�
hpl::aleph::HPLEventManager* MapEditorWX::getEventManager()
{
    return &this->eventManager;
}

//�F�ݒ���t�@�C������ǂݍ���
bool MapEditorWX::loadColorSetting()
{
    //TODO
    return false;
}

