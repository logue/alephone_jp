#ifndef _MAP_EDITOR_ONE_SETTING_
#define _MAP_EDITOR_ONE_SETTING_

//#include "stdafx.h"

//#include "MapEditorSDI.h"
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

// CMonsterPropertyDialog �_�C�A���O
const int NUMBER_OF_OBJECT_FLAGS = 6;
const int NUMBER_OF_MISSION_TYPES = 6;
const int NUMBER_OF_ENV_TYPES = 7;
enum
{
    MI_CenterX = 0,
    MI_Goal,
    MI_Scenery,
    MI_Sound,
    NUMBER_OF_MAP_ICONS
};
static char* POLYGON_COLOR_FILE_NAME = "data/PolygonColor.txt";
static char* LOG_FILE_NAME = "log.txt";

#include <vector>
#include <string>
#include <cstdio>

//color presets
enum{
    COL_FORGE,
    COL_MARATHON,
    COL_CUSTOM,

    NUMBER_OF_COLOR_PRESETS
};

const int COL_NUM = 3;

typedef struct ColorSettings_tag{
    int type;
    int background[COL_NUM];
    int gridLine[COL_NUM];
    int lines[COL_NUM];
    int polygons[COL_NUM];
    int strings[COL_NUM];
    int points[COL_NUM];
}ColorSettings;

enum{
    IS_SHOW_GRID,
    IS_FIT_TO_GRID,
    IS_SHOW_MONSTERS,
    IS_SHOW_ITEMS,
    IS_SHOW_SCENERY,
    IS_SHOW_PLAYER,
    IS_SHOW_GLOALS,
    IS_SHOW_SOUNDS,
    IS_SHOW_ANNOTATIONS,
    IS_VISUAL_MODE_CROSSFAIR,
    IS_SHOW_POLYGONS,
    IS_SHOW_LINES,

    NUMBER_OF_EDITOR_FLAGS
};

/**
    edtior's settings
*/
class MapEditorOneSetting{
private:
    std::string initialSettingFileName;

    //grid size(index)
    int gridSizeIndex;

    //color setting
    ColorSettings colorSetting;
public:
    //flags
    bool flags[NUMBER_OF_EDITOR_FLAGS];


public:
    MapEditorOneSetting();
    ~MapEditorOneSetting(){}
public:
    void setIniFileName(const char *iniFileName);
    /**
        try to load file.
        @return false : failure
    */
    bool loadSetting();
    bool saveSetting();
    void setSettingToDefault();
public:
    int getGridSizeIndex();
    void setGridSizeIndex(int index);
    ColorSettings *getColorSetting();
    void setColorSetting(ColorSettings *setting);
    void setColorSetting(int type);

    //�J���[�ݒ�
    static void setColorSetting(int type, ColorSettings *setting);

    //�J���[�ݒ�̃R�s�[
    static void copyColorSetting(ColorSettings *dest, ColorSettings *src);

    //�t�@�C���p�X
    std::string getFilePath();

    //�F�����o�͂��܂�
    void outputColor(FILE* fp, int col[], int colNum);
};

#endif
