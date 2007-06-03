// MapEditorSDI.h : MapEditorSDI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��
#include "HPLLibMFC.h"
#include "HPLLogger.h"      //logger for debug

#include "header.h"
#include "extensions.h"
#include "FileHandler.h"
#include "map.h"
#include "game_wad.h"
#include "weapons.h"
#include "items.h"
#include "monsters.h"
#include "media.h"
#include "scenery_definitions.h"
#include "mysound.h"
#include "computer_interface.h"
#include "render.h"
#include "shapes_sdl.h"
#include "shell.h"
#include "editor.h"
#include "platforms.h"
#include "lightsource.h"
#include "shape_definitions.h"
#include "collection_definition.h"

#include "HPLLib/HPLAlephLib.h"

//#include "placement.h"
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "SDLToWin32/SDLToWin32.h"

#include "MonsterPropertyDialog.h"
#include "PolygonTypeDialog.h"
#include "HeightDialog.h"
#include "LevelParameterDialog.h"
#include "TerminalDialog.h"
#include "VisualDialog.h"
#include "ToolDialog.h"
#include "ObjectPlacementDialog.h"
#include "SelectLevelDialog.h"
#include "PolygonPropertyDialog.h"
#include "EditorInforDialog.h"
#include "AnnotationDialog.h"
#include "SelectPolygonDialog.h"
#include "TextureDialog.h"
#include "TextureDialog.h"
#include "TextureChildDialog.h"
#include "LinePropertyDialog.h"
#include "PointPropertyDialog.h"
#include "SidePropertyDialog.h"

#include "MapEditorOneSetting.h"
#include "MapEditorOneInnerSetting.h"
#include "EventManager.h"

#include <HPLLib/HPLAlephLib.h>

// CMapEditorSDIApp:
// ���̃N���X�̎����ɂ��ẮAMapEditorSDI.cpp ���Q�Ƃ��Ă��������B
//

const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

const int NUMBER_OF_LANDSPACES = 4;
//�_�ƃN���b�N�n�_�̋���������ȉ��ł���ΑI������B
//���X�g���ɒT������
const int POINT_DISTANCE_EPSILON = 5;
const int OBJECT_DISTANCE_EPSILON = 8;
const int LINE_DISTANCE_EPSILON = 5;

static char *DATA_DIR_NAME = "./data/";
static char *INI_FILE_NAME = "./setting.ini";
static char * MAP_ICONS_DIR_NAME = "Map Icons/";
static char * HILIGHTED_ICONS_DIR_NAME = "Highlighted/";
static char * MAP_ICONS_IMAGE_NAME_LIST_FILE_NAME = "MapIconImageList.txt";
const int START_OF_TEXTURE = _collection_walls1;

extern HPLLogger logger;

//map icons
enum
{
    MI_CenterX = 0,
    MI_Goal,
    MI_Scenery,
    MI_Sound,
    NUMBER_OF_MAP_ICONS
};


//point flags
enum
{
    POINT_FLAG_SOLID = 1,
    POINT_FLAG_MULTI_HIGHEST = 2,
    POINT_FLAG_TRANSPARENCY = 4,

    NUMBER_OF_POINT_FLAGS
};

const int TOOL_WIDTH = 24;
const int TOOL_HEIGHT = 21;

//�I���������̂̎��
enum{
    _no_selected,
    _selected_point,
    _selected_line,
    _selected_polygon,
    _selected_object,
};

//����
typedef struct Information_tag{
    CString jname;
}Information;
//�l������
typedef struct InformationBinded_tag{
    CString jname;
    int bind;
}InformationBinded;

//class HPLSelectData;

/**
    MapEditorOne���C���A�v���P�[�V����
*/
class CMapEditorSDIApp : public CWinApp
{
public:
	CMapEditorSDIApp();
    ~CMapEditorSDIApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
public:
    ///////////////////////
    //���x���֘A

    /**���x���̖���*/
    CStringArray LevelNameList;
    
    //�I�𒆂̃��x���C���f�b�N�X
    int editLevelIndex;


public:
    ///////////////////////////
    //�O���b�h�E�\���֌W

    /**�I�𒆂̔{��*/
    //int zoomDivision;

    //
    hpl::aleph::view::HPLViewGridManager gridManager;

    /**�O���b�h�\���p�Ԋu(���E�����ɑΉ����A�g��k���ő傫���ω�)*/
    int gridIntervals[NUMBER_OF_GLID];

    //�ʒu�I�t�Z�b�g
    //POINT offset;

    /**���݂̃}�E�X���W*/
    //POINT nowMousePoint;

    /**��O�̃}�E�X���W*/
    //POINT oldMousePoint;

    //�|���S���^�C�v�̐F
    COLORREF polygonTypeColor[NUMBER_OF_POLYGON_TYPE];

    //�_�u���o�b�t�@�����O
    CDC doubleBufferDC;
    CBitmap doubleBuffserBitmap;


    ///////////////////////
    //�c�[���E�v���p�e�B�_�C�A���O

    //���[�h���X�����X�^�[�v���p�e�B�_�C�A���O
    CMonsterPropertyDialog *objectPropertyDialog;
    //���[�h���X�|���S���^�C�v�_�C�A���O
    CPolygonTypeDialog *polygonTypeDialog;
    //���[�h���X�\�����x�_�C�A���O
    CHeightDialog *heightDialog;
    //
    CToolDialog *toolDialog;
    //polygon property
    CPolygonPropertyDialog *polygonPropertyDialog;
    //�_�v���p�e�B
    CPointPropertyDialog *pointPropertyDialog;

    //texture dialog (palette)
    CTextureDialog *textureDialog;

    ///////////////////////////
    //���̂Ȃǂ̃X�g�b�N

    //���
    Information objectTypeInformations[NUMBER_OF_MAP_OBJECT_TYPES];
    //�����X�^�[�̎��
    Information monsterTypeInformations[NUMBER_OF_MONSTER_TYPES];
    //�I�u�W�F�̎��
    Information sceneryTypeInformations[NUMBER_OF_SCENERY_DEFINITIONS];
    //�A�C�e���̎��
    Information itemTypeInformations[NUMBER_OF_DEFINED_ITEMS];
    //��
    Information soundSourceInformations[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
    //�N��
    Information activateTypeInformations[NUMBER_OF_ACTIVATE_TYPES];
    //�t���O
    InformationBinded objectFlagInformations[NUMBER_OF_OBJECT_FLAGS];

    //��
    Information environmentInformations[NUMBER_OF_ENVIRONMENTS];
    //�w�i
    Information landscapeInformations[NUMBER_OF_LANDSPACES];
    //�Q�[���^�C�v
    //InformationBinded gameTypeInformations[NUMBER_OF_GAME_TYPES];
    //���^�C�v
    InformationBinded environmentTypeInformations[NUMBER_OF_ENV_TYPES];
    //�~�b�V�����^�C�v
    InformationBinded missionTypeInformations[NUMBER_OF_MISSION_TYPES];

    //�^�[�~�i���O���[�v
    Information terminalGroupTypeInformations[NUMBER_OF_GROUP_TYPES];

    //�|���S���^�C�v
    Information polygonTypeInformations[NUMBER_OF_POLYGON_TYPE];

    //ambient sounds
    Information ambientSoundTypeInformations[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
    //random sounds
    Information randomSoundTypeInformations[NUMBER_OF_RANDOM_SOUND_DEFINITIONS];

    // ����
	afx_msg void OnAppAbout();


    /////////////////////

    //�����I�����̑I�𕨃��X�g
    //TODO add selection
    //struct selectInformation selectGroupInformation;
    hpl::aleph::map::HPLSelectData selectDatas;

    //�R�s�[�A���h�y�[�X�g�p�̃f�[�^���X�g
    //�y�[�X�g���ɂ��������ɐV�K�쐬���܂�
    hpl::aleph::map::HPLRealMapData storedMapData;
    //���̏�ɓW�J����Əd�Ȃ�̂ŁA�ǂꂾ�����炷��(world���W)
    int storedDataPointDelta[2];

    //�ύX�_�̗���
    hpl::aleph::map::HPLDoneHistory history;

    //selection group
    //vector<struct selectInformation> selectGroupInformationList;

    //SDL surface to win api device context
	SDLToWindows *m_SDLToWindows;

    //map icons
    vector<HBITMAP> bitmapList;


    //show / hide polygons, lines. points
    //�\�����Ă��鍂���͈̔́B�I���ɂ����f�����
    int viewHeightMax;
    int viewHeightMin;
    bool isRevealHiddenLines;

    //save check
    //when true, warn to save
    bool isChanged;

    //flag of first adding of lines
    bool isFirstOfLineToAdd;

    /////////////////////////////////////
    //�����
    //�O��̑I�������_�̃C���f�b�N�X
    //prev point user clicked.
    //if there is not, set NONE
    int previousPointIndex;

    //�ҏW�ݒ�
    //Editor setting
    MapEditorOneSetting setting;

    //is shapes file loaded
    bool isLoadedShapesFile;

    //polygon to draw by preset
    int numberOfPolygonPoints;

    //is now on the point
    bool isNowOnThePoint;

    //texture bitmaps
    vector<vector<CBitmap*> > textureBitmaps;

    /**�ҏW���[�h�ƃ��j���[ID�̑Ή�*/
    map<int, int> menuIDMap;

	//�|���S�������������ǂ������������܂��i�����Łj
	bool isPolygonValidityStored(int polyIndex);

	//�|���S���̐��������X�V���܂�
	void updatePolygonValidityStored();
private:
    //�C�x���g�Ǘ�
    mapeditorone::EventManager eventManager;
	//�|���S���̐��������
	std::vector<bool> polygonValidity;
public:
    /**
        �C�x���g�}�l�[�W���[�擾
    */
    mapeditorone::EventManager* getEventManager();

    //initialize all datas for application
    bool initialize();

    /**
        �F�ݒ���t�@�C������ǂݍ���
    */
    bool loadColorSetting();
    
    /**
        �O���b�h�֘A���Z�b�g�A�b�v
    */
    void setupGridManager(hpl::aleph::view::HPLViewGridManager* mgr,
        mapeditorone::MapEditorOneInnerSetting* innerSetting);

    /**
        �A�C�R���p�摜��ǂݍ���
    */
    void loadIconBitmaps();

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnFileOpen();
};

extern CMapEditorSDIApp theApp;

//load information list
void loadInformations(const char* filename, int max, 
                      Information *informations);

//load bitmap/icon from resources to ImageList
void loadIcon(int id, CImageList* imageList);
//void loadBitmap(int id, CImageList* imageList, COLORREF key);

//load bitmap/icon from file
HBITMAP loadBitmapFromFile(const char *pathName);

//set object property to default
void setObjectPropertyToDefault();

void setCursor();

/**
    change is this 
*/
object_frequency_definition *getIndexOfPlacement(int index);
void addInitialPlacement(int objectType, int index, int num);
void subInitialPlacement(int objectType, int index, int num);

/**
   add objet on polygon
   return added object's index
*/
int addObject(struct world_point2d &world_point, int polygonIndex);

/**
    add point on polygon
    if it is on line, add point to the line and polygon
    @return added point's index
*/
int addPoint(struct world_point2d &world_point);

int addLine(int beginPointIndex, int endPointIndex);

void addPolygon(polygon_data* data);

/**
    get line index from point of edge.
    @return index of point
        NONE : not found
*/
int getLineIndexFromPointIndex(int pointIndex);
int getPolygonIndexFromLineIndex(int lineIndex);
int getPolygonIndexFromPointIndex(int pointIndex);

/**
    get platform_data by using polygon index
    only platform has polygon index. not polygon have

    return NULL in no exists
*/
int searchPlatformIndexByPolygonIndex(int index);

//CString GetModulePathFileName(CString pName);

//�ȈՔ�
//
void getViewPointFromWorldPoint2D(world_point2d wpoint, int* dest);

