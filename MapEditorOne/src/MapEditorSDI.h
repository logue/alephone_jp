// MapEditorSDI.h : MapEditorSDI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��
#include "HPLLibMFC.h"
#include "HPLLogger.h"      //logger for debug

#include "AlephOne/header.h"
#include "AlephOne/extensions.h"
#include "AlephOne/FileHandler.h"
#include "AlephOne/map.h"
#include "AlephOne/game_wad.h"
#include "AlephOne/weapons.h"
#include "AlephOne/items.h"
#include "AlephOne/monsters.h"
#include "AlephOne/scenery_definitions.h"
#include "AlephOne/mysound.h"
#include "AlephOne/computer_interface.h"
#include "AlephOne/render.h"
#include "AlephOne/shapes_sdl.h"
#include "AlephOne/shell.h"
#include "AlephOne/editor.h"
#include "AlephOne/platforms.h"

//#include "AlephOne/placement.h"
#include <map>
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

#include "MapEditorOneSetting.h"

// CMapEditorSDIApp:
// ���̃N���X�̎����ɂ��ẮAMapEditorSDI.cpp ���Q�Ƃ��Ă��������B
//

const int NUMBER_OF_POLYGON_TYPE = 24;
const int ZOOM_DIVISION_STEP = 5;
const int ZOOM_DIVISION_MAX = 200;
const int ZOOM_DIVISION_MIN = 1;
const int ZOOM_DIVISION_DEFAULT = 100;
const int OFFSET_X_WORLD = 32768;
const int OFFSET_Y_WORLD = 32768;
const int NUMBER_OF_GLID = 5;

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

//map icons
enum
{
    MI_CenterX = 0,
    MI_Goal,
    MI_Scenery,
    MI_Sound,
    NUMBER_OF_MAP_ICONS
};

//tools
enum
{
    TI_ARROW = 0,
    TI_FILL,
    TI_HAND,
    TI_LINE,
    TI_MAGNIFY,
    TI_SKULL,
    TI_TEXT,
    TI_POLYGON,
    NUMBER_OF_TOOLS //7
};

//�ҏW���[�h
enum
{
    EM_DRAW,
    EM_VISUAL,
    EM_FLOOR_HEIGHT,
    EM_CEILING_HEIGHT,
    EM_FLOOR_TEXTURE,
    EM_CEILING_TEXTURE,
    EM_FLOOR_LIGHT,
    EM_CEILING_LIGHT,
    EM_MEDIA,
    EM_SOUND,
    EM_POLYGON_TYPE,
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
    //���x���̖���
    CStringArray LevelNameList;
    
    //�I�𒆂̔{��
    int zoomDivision;

    //�O���b�h�\���p�Ԋu(���E�����ɑΉ����A�g��k���ő傫���ω�)
    int gridIntervals[NUMBER_OF_GLID];
    //int nowGridInterval;

    //�ʒu�I�t�Z�b�g
    POINT offset;

    POINT nowMousePoint;
    POINT oldMousePoint;

    //�I���������̂̎��
//    int selectType;
    //�I���������̂̃C���f�b�N�X
//    int selectIndex;

    //�O���b�h
    //�{�^�������Ă�H
    bool isPressLButtonWithCtrl;

    //�I�𒆂̃��x���C���f�b�N�X
    int editLevelIndex;
    //�|���S���^�C�v�̐F
    COLORREF polygonTypeColor[NUMBER_OF_POLYGON_TYPE];

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

// ����
	afx_msg void OnAppAbout();
    /*BOOL isObjectPropertyDialogShow;
    BOOL isHeightDialogShow;
    BOOL isPolygonTypeDialogShow;
    BOOL isToolDialogShow;
    BOOL isPolygonPropertyDialogShow;
*/
    //�_�u���o�b�t�@�����O
    CDC doubleBufferDC;
    CBitmap doubleBuffserBitmap;

    //�|���S��������������Ƃ��̃}�E�X���W����̃I�t�Z�b�g
    //���΍��W
//    POINT polygonPoints[8];
//    int polygonPointNum;

    //�I��͈͎n�_
    POINT selectStartPoint;
    bool isSelectingGroup;

    //�����I�����̑I�𕨃��X�g
    struct selectInformation selectGroupInformation;

    //selection group
    //TODO use this
    vector<struct selectInformation> selectGroupInformationList;

    //SDL surface to win api device context
	SDLToWindows *m_SDLToWindows;

    //icons
    //CImageList mapIconImageList;
    //vector<CBitmap*> bitmapList;
    vector<HBITMAP> bitmapList;

    //select tool
    int selectingToolType;

    //show / hide polygons, lines. points
    int viewHeightMax;
    int viewHeightMin;

    //save check
    //when true, warn to save
    bool isChanged;

    //flag of first adding of lines
    bool isFirstOfLineToAdd;

    //prev point user clicked.
    //if there is not, set NONE
    int previousPointIndex;

    //Editor setting
    MapEditorOneSetting setting;

private:
    //edit mode
    int editMode;
public:
    map<int, int> menuIDMap;
    void setEditMode(int mode);
    int getEditMode();
    
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

//@return if failure, return under 0(-1)
//TODO construct these
int searchSelectEndpoint(int viewPX, int viewPY);
int searchSelectObject(int viewPX, int viewPY);
int searchSelectLine(int viewPX, int viewPY);
int searchSelectPolygon(int viewPX, int viewPY);

//convert view <-> world point
world_point2d getWorldPoint2DFromViewPoint(int viewPX, int viewPY);
void getViewPointFromWorldPoint2D(world_point2d& point, int *dest);

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
platform_data *searchPlatformByPolygonIndex(int index);

//CString GetModulePathFileName(CString pName);
