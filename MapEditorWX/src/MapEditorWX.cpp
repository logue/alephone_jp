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

    //�J�[�\���ǂݍ��� <en> load cursor images
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
    char *cursorLine = "LineCursor1.bmp";
    char *cursorFill = "pot.bmp";
    char *cursorMag = "mag1.bmp";

    int cursorId[] ={
        wxCURSOR_ARROW,
        -1,
        wxCURSOR_HAND,
        -1,
        -1,
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
            }else if(i == ToolType::TI_LINE){
                fname = cursorLine;
            }else if(i == ToolType::TI_FILL){
                fname = cursorFill;
            }else if(i == ToolType::TI_MAGNIFY){
                fname = cursorMag;
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
    {
        wxImage img;
        loadImage("data/img/onLine.bmp", &img, 255,255,255);
        onLineCursor = wxCursor(img);
        loadImage("data/img/onPoint.bmp", &img, 255,255,255);
        onPointCursor = wxCursor(img);
        loadImage("data/img/onPoint2.bmp", &img, 255,255,255);
        onPointCursorAdding = wxCursor(img);
        loadImage("data/img/onLine2.bmp", &img, 255,255,255);
        onLineCursorAdding = wxCursor(img);
        loadImage("data/img/LineCursor2.bmp", &img, 255,255,255);
        lineToolCursorAdding = wxCursor(img);

    }

    //�ΏۊO�̐���\�����邩�ǂ���
    this->isRevealHiddenLines = false;
    
    this->isNowOnTheLine = this->isNowOnThePoint = false;

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
//�X�g�b�N�}�l�[�W�����擾���܂�
hpl::aleph::HPLStockManager* MapEditorWX::getStockManager()
{
    return &this->stockManager;
}
//Shapes�}�l�[�W���[�擾
hpl::shapes::HPLShapesManager* MapEditorWX::getShapesManager()
{
    return &this->shapesManager;
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
void MapEditorWX::loadImage(const char* fname, wxImage* bitmap)
{
    loadBitmap(fname, bitmap);
}
/**
    �J���[�}�X�N�t���œǂݍ���
*/
void MapEditorWX::loadImage(const char* fname, wxImage* img, int r, int g, int b)
{
    loadBitmap(fname, img);
    //�J���[�}�X�N�ݒ�
    img->SetMaskColour(r,g,b);
}

/**
    ���݂̃��[�h�E�c�[���ɂ��킹�ăJ�[�\����ύX���܂�
*/
void MapEditorWX::setCursor()
{
    int editMode = this->getEventManager()->getEditModeType();
    int toolType = this->getEventManager()->getToolType();
    if(editMode == EditModeType::EM_DRAW){
        if(toolType == ToolType::TI_LINE){
            if(this->isNowOnTheLine){
                if(this->isFirstOfLineToAdd){
                    //���̏�ɂ���
                    wxSetCursor(this->onLineCursor);
                }else{
                    wxSetCursor(this->onLineCursorAdding);
                }
            }else if(toolType == ToolType::TI_LINE && this->isNowOnThePoint){
                if(this->isFirstOfLineToAdd){
                    //�_�̏�ɂ���
                    wxSetCursor(this->onPointCursor);
                }else{
                    wxSetCursor(this->onPointCursorAdding);
                }
            }else{
                if(this->isFirstOfLineToAdd){
                    wxSetCursor(cursors[toolType]);
                }else{
                    wxSetCursor(this->lineToolCursorAdding);
                }
            }
        }else{
            //TODO �J�[�\��
            ::wxSetCursor(cursors[toolType]);
        }
    }else{
        //���ɂ���
        ::wxSetCursor(cursors[0]);
    }
}
/**
    ���ҏW�������������܂�
*/
void MapEditorWX::resetLineEditInfo()
{
    prevPointIndex = NONE;
    isFirstOfLineToAdd = true;
}

void MapEditorWX::getShapesImage(wxImage* img, int collection, int clut, int index, double illumination)
{
	//�T�[�t�F�C�X�擾
    
	SDL_Surface* surface = this->getShapesManager()->getSurface(collection, clut, index, illumination);
	img->Create(surface->w, surface->h);
	SDL_LockSurface(surface);
	for(int x = 0; x < surface->w; x ++){
		for(int y = 0; y < surface->h; y ++){
            Uint32 pixel = hpl::surface::getpixel(surface, x, y);
            unsigned char r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            img->SetRGB(x, y, r, g, b);
		}
	}
	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
    
/*
    SDL_Color palette[256];
    byte** outp = (byte**)malloc(sizeof(byte*));
    SDL_Surface* surface = this->getShapesManager()->getRawSurface(collection, clut, index, illumination,
        palette, outp);
    img->Create(surface->w, surface->h);
	for(int x = 0; x < surface->w; x ++){
		for(int y = 0; y < surface->h; y ++){
            int pixel = (int)hpl::surface::getpixel(surface, x, y);
            img->SetRGB(x, y, palette[pixel].b, palette[pixel].g, palette[pixel].r);
        }
    }
    SDL_FreeSurface(surface);
    free(outp);*/
}

//char->wx
wxString getString(const char* format, ...)
{
    char message[BUF_MAX];
    va_list maker;
    va_start(maker, format);
    vsprintf(message, format, maker);
    wxString str = wxConvertMB2WX(message);
    return str;
}
