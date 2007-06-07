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
    hpl::aleph::loadInformation("data/ObjectTypes.txt", NUMBER_OF_OBJECT_TYPES, this->objectTypeInfo);
    //�����X�^�[
    hpl::aleph::loadInformation("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES,, this->monsterTypeInfo);
    //�I�u�W�F
    hpl::aleph::loadInformation("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS, this->sceneryTypeInfo);
    //�A�C�e��
    hpl::aleph::loadInformation("data/DefinedItemsTypes.txt", NUMBER_OF_DEFINED_ITEMS, this->itemTypeInfo);
    //��
    hpl::aleph::loadInformation("data/SoundSourceTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, this->soundSourceTypeInfo);
    //�N��
    hpl::aleph::loadInformation("data/ActivateTypes.txt", NUMBER_OF_ACTIVATE_TYPES, this->activateTypeInfo);

    //�t���O
    this->flagInfo[0].bind = _map_object_is_invisible;
    this->flagInfo[1].bind = _map_object_hanging_from_ceiling;
    this->flagInfo[2].bind = _map_object_is_blind;
    this->flagInfo[3].bind = _map_object_is_deaf;
    this->flagInfo[4].bind = _map_object_floats;
    this->flagInfo[5].bind = _map_object_is_network_only;

    //�^�[�~�i��
    hpl::aleph::loadInformation("data/TerminalGroupTypes.txt", NUMBER_OF_GROUP_TYPES, this->terminalTypeInfo);

    //�|���S��
    hpl::aleph::loadInformation("data/PolygonType.txt", NUMBER_OF_POLYGON_TYPE, this->polygonTypeInfo);

    //��
    hpl::aleph::loadInformation("data/Environments.txt", NUMBER_OF_ENVIRONMENTS, this->envInfo);
    //�w�i
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

    //�w�i
    hpl::aleph::loadInformation("data/AmbientSoundTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, this->ambientSoundTypeInfo);
    //�w�i
    hpl::aleph::loadInformation("data/RandomSoundTypes.txt", NUMBER_OF_RANDOM_SOUND_DEFINITIONS, this->randomSoundTypeInfo);

    //�F�ݒ�ǂݍ���
    if(!hpl::aleph::loadColorSetting(POLYGON_COLOR_FILE_NAME, this->polygonTypeColors, NUMBER_OF_POLYGON_TYPE)){
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

    //�}�b�v�̃A�C�R���r�b�g�}�b�v���t�@�C������ǂݍ���
    this->loadIconBitmaps(DATA_DIR_NAME);

    //TODO textureBitmaps
    return true;
}

hpl::aleph::view::HPLViewGridManager* MapEditorWX::getViewGridManager()
{
    return &this->viewGridManager;
}
//�C�x���g�}�l�[�W���[���擾���܂�
hpl::aleph::HPLEventManager* MapEditorWX::getEventManager()
{
    return &this->eventManager;
}

//�r���[���W�����[���h���W�ɒ�������̊ȈՔ�
world_point2d MapEditorWX::getWorldPointFromViewPoint(int vx, int vy)
{
    hpl::aleph::map::HPLViewGridManager* mgr = this->getViewGridManager();
    int offset[2];
    mgr->getOffset(offset);
    int DIV = mgr->getZoomDivision();
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(
        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, offset[0], offset[1]);
    return wpoint;
}
//
void MapEditorWX::getViewPointFromWorldPoint(world_point2d& wpoint, int vpoint[2])
{
    hpl::aleph::map::HPLViewGridManager* mgr = this->getViewGridManager();
    int offset[2];
    mgr->getOffset(offset);
    int DIV = mgr->getZoomDivision();
    hpl::aleph::map::getViewPointFromWorldPoint2D(wpoint.x, wpoint.y, vpoint,
        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, offset[0], offset[1]);
}

/**
    �A�C�R���p�̃r�b�g�}�b�v�t�@�C����ǂݍ��݂܂�
*/
void MapEditorWX::loadIconBitmaps(const char* baseDirPath)
{
    //�A�C�R���r�b�g�}�b�v�ƃt�@�C�����A�����ăA�C�e��ID�Ƃ̑Ή��f�[�^���t�@�C������ǂݍ��݂܂�
    const int NUMBER_OF_MAP_ICON_FILES = NUMBER_OF_DEFINED_ITEMS +
        NUMBER_OF_MAP_ICONS;
    hpl::aleph::Information mapIconInfo[NUMBER_OF_MAP_ICON_FILES];

    //�t�@�C�����쐬
    char buf[BUF_MAX];
    sprintf(buf, "%s%s", baseDirPath, MAP_ICONS_IMAGE_NAME_LIST_FILE_NAME);
    hpl::aleph::loadInformations(buf, NUMBER_OF_MAP_ICON_FILES, mapIconInfo);

    for(int i = 0; i < 2 * NUMBER_OF_DEFINED_ITEMS + 2 * NUMBER_OF_MAP_ICONS; i ++){
        std::string path = std::string(baseDirPath) + std::string(MAP_ICONS_DIR_NAME);
        const int HILIGHTED_OFFSET = NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MAP_ICONS;

        int index = i;
        if(i >= HILIGHTED_OFFSET){
            //�I���i�n�C���C�g��ԁj
            path += std::string(HILIGHTED_ICONS_DIR_NAME);
            index -= HILIGHTED_OFFSET;
        }
        path += mapIconInfo[index].jname;

        //TODO �r�b�g�}�b�v�t�@�C���ǂݍ���
        if(i < HILIGHTED_OFFSET){
            //�ʏ���
            if(index < NUMBER_OF_DEFINED_ITEMS){
                //�A�C�e��
                this->loadBitmap(path.c_str(), &this->itemIconBitmaps[index]);
            }else{
                //�}�b�v�A�C�R��
                this->loadBitmap(path.c_str(), &this->mapIconBitmaps[index]);
            }
        }else{
            //�I�����n�C���C�g���
            if(index < NUMBER_OF_DEFINED_ITEMS){
                //�A�C�e��
                this->loadBitmap(path.c_str(), &this->hilightedItemIconBitmaps[index]);
            }else{
                //�}�b�v�A�C�R��
                this->loadBitmap(path.c_str(), &this->hilightedMapIconBitmaps[index]);
            }
        }
    }
}

/**
    �r�b�g�}�b�v�̓ǂݍ��݁i�ȈՔŁj
*/
void MapEditorWX::loadBitmap(const char* fname, wxBitmap* bitmap)
{
    bitmap->LoadFile(wxConvCurrent->cMB2WX(fname), wxBITMAP_TYPE_BMP);
}
