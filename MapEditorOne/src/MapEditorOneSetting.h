#ifndef _MAP_EDITOR_ONE_SETTING_
#define _MAP_EDITOR_ONE_SETTING_

//#include "stdafx.h"
#include "header.h"
#include "extensions.h"
#include "FileHandler.h"
#include "map.h"
#include "game_wad.h"
#include "weapons.h"
#include "items.h"
#include "monsters.h"
#include "scenery_definitions.h"
#include "mysound.h"
#include "computer_interface.h"
#include "editor.h"

//#include "MapEditorSDI.h"
const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

const int NUMBER_OF_LANDSPACES = 4;
//点とクリック地点の距離がこれ以下であれば選択する。
//リスト順に探索する
const int POINT_DISTANCE_EPSILON = 5;
const int OBJECT_DISTANCE_EPSILON = 8;
const int LINE_DISTANCE_EPSILON = 5;

// CMonsterPropertyDialog ダイアログ
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

//ポリゴン選択時のあみかけbmp
static char* POLYGON_SELECT_STLIPPLE_BITMAP_FILE_PATH = "data/img/bmp00005.bmp";

//ツールダイアログのサイズ
const int TOOL_DIALOG_W = 75;
const int TOOL_DIALOG_H = 100;

//ツールパレット
static char *TOOL_BAR_ICONS_DIR_NAMR = "Toolbar/";
static char *SELECTED_ICONS_DIR_NAME = "Selected/";
static char *TOOL_BAR_ICONS_IMAGE_LIST_FILE_NAME = "ToolBarImageList.txt";

//ツールアイテムのサイズ
const int TOOL_WIDTH = 24;
const int TOOL_HEIGHT = 21;

//ツールパレットのアイコンビットマップファイルの数
const int NUMBER_OF_TOOL_BAR_ICON_FILES = 8;
static char *DATA_DIR_NAME = "./data/";

static char *INI_FILE_NAME = "./setting.ini";
static char * MAP_ICONS_DIR_NAME = "Map Icons/";
static char * HILIGHTED_ICONS_DIR_NAME = "Highlighted/";
static char * MAP_ICONS_IMAGE_NAME_LIST_FILE_NAME = "MapIconImageList.txt";
const int START_OF_TEXTURE = _collection_walls1;
static char* TAG_NAME_FILE_PATH = "data/InnerSettingTagList.ini";
static char* INNER_DATA_FILE_PATH = "data/InnerSetting.ini";

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

    //カラー設定
    static void setColorSetting(int type, ColorSettings *setting);

    //カラー設定のコピー
    static void copyColorSetting(ColorSettings *dest, ColorSettings *src);

    //ファイルパス
    std::string getFilePath();

    //色情報を出力します
    void outputColor(FILE* fp, int col[], int colNum);
};

#endif
