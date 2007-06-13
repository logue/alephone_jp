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
    //��ʓI�ȏ����ݒ�
    if(!this->initialize()){
        wxMessageBox(_T("Initialize failure"));
        exit(-1);
    }

    //�E�C���h�E�t���[���𐶐����܂�
    frame = new MapEditorMainFrame(
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
        //�ۑ�
        setting.saveSetting();
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
    hpl::aleph::loadInformation("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES, this->monsterTypeInfo);
    //�I�u�W�F
    hpl::aleph::loadInformation("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS, this->sceneryTypeInfo);
    //�A�C�e��
    hpl::aleph::loadInformation("data/DefinedItems.txt", NUMBER_OF_DEFINED_ITEMS, this->itemTypeInfo);
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
    storedDataDiffPointDelta[0] = storedDataDiffPointDelta[1] = 0;

    //���̍ŏ��̓_
    isFirstOfLineToAdd = true;
    //�ȑO�I�������_
    prevPointIndex = NONE;

    //�O���b�h�ݒ�
    mapeditorone::MapEditorOneInnerSetting innerSetting =
        mapeditorone::MapEditorOneInnerSetting(TAG_NAME_FILE_PATH, INNER_DATA_FILE_PATH);
    mapeditorone::setupGridManager(this->getViewGridManager(),
        &innerSetting);
    this->getViewGridManager()->setGridIntervalIndex(this->setting.getGridSizeIndex());
    nPolygonPoints = 3;

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
    char *cursorSkull = "cursor2.bmp";
    char *cursorPolygon = "cur00004.bmp";
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
    //�J�[�\���f�[�^�ǂݍ���
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
        if(cursorId[i] != -1){
            //�K��̂��̂Ŏg�������
            cursors[i] = wxCursor(cursorId[i]);
        }else{
            //�t�@�C���p�X
            char* fname;
            if(i == ToolType::TI_SKULL){
                fname = cursorSkull;
            }else if(i == ToolType::TI_POLYGON){
                fname = cursorPolygon;
            }
            wxString path = wxConvCurrent->cMB2WX(CURSOR_BASE_DIR);
            wxString pathF = wxConvCurrent->cMB2WX(fname);
            path.Append(pathF);
            //�ǂݍ���
            wxImage bmp;
            bmp.LoadFile(path);
            bmp.SetMaskColour(255,255,255);
            //�J�[�\���ݒ�
            cursors[i] = wxCursor(bmp);
        }
    }

    //�ΏۊO�̐���\�����邩�ǂ���
    this->isRevealHiddenLines = false;
    return true;
}

//�|���S�������������ǂ������������܂�(������)
bool MapEditorWX::isPolygonValidityStored(int polyIndex)
{
    //TODO
    return true;
}

//�|���S�������������X�V���܂�
void MapEditorWX::updatePolygonValidityStored()
{
    //TODO
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
    �r�b�g�}�b�v�̓ǂݍ��݁i�ȈՔŁj
*/
void MapEditorWX::loadBitmap(const char* fname, wxImage* bitmap)
{
    if(!bitmap->LoadFile(wxConvCurrent->cMB2WX(fname), wxBITMAP_TYPE_BMP)){
        hpl::error::halt("Couldn't load bitmap[%s]", fname);
    }
}

/**
    ���݂̃��[�h�E�c�[���ɂ��킹�ăJ�[�\����ύX���܂�
*/
void MapEditorWX::setCursor()
{
    int editMode = this->getEventManager()->getEditModeType();
    if(editMode == EditModeType::EM_DRAW){
        int toolType = this->getEventManager()->getToolType();
        //TODO �J�[�\��
        ::wxSetCursor(cursors[toolType]);
    }else{
    }
}
