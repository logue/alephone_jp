#ifndef _MAP_EDITOR_ONE_SETTING_
#define _MAP_EDITOR_ONE_SETTING_

//#include "stdafx.h"
#include "computer_interface.h"
#include "editor.h"
#include "extensions.h"
#include "FileHandler.h"
#include "game_wad.h"
#include "header.h"
#include "items.h"
#include "lightsource.h"
#include "map.h"
#include "media.h"
#include "monsters.h"
#include "mysound.h"
#include "platforms.h"
#include "scenery_definitions.h"
#include "weapons.h"
#include "collection_definition.h"
#include "shape_definitions.h"
#include "shapes_sdl.h"

//#include "MapEditorSDI.h"
const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

const int NUMBER_OF_LANDSPACES = 4;
//点とクリック地点の距離がこれ以下であれば選択する。
//リスト順に探索する
const int POINT_DISTANCE_EPSILON = 10;
const int OBJECT_DISTANCE_EPSILON = 10;
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
const int TOOL_DIALOG_W = 55;
const int TOOL_DIALOG_H = 120;

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
static char* START_POINT_IMAGE_FILE_PATH = "data/Map Icons/center X.bmp";

//point flags
enum
{
    POINT_FLAG_SOLID = 1,
    POINT_FLAG_MULTI_HIGHEST = 2,
    POINT_FLAG_TRANSPARENCY = 4,

    NUMBER_OF_POINT_FLAGS
};


#include <vector>
#include <string>
#include <cstdio>

//color presets
enum{
    COL_FORGE = 0,
    COL_MARATHON = 1,
    COL_CUSTOM = 2,

    NUMBER_OF_COLOR_PRESETS
};

const int COL_NUM = 3;

namespace ColorType{
    enum{
        Background,
        GridLine,
        Lines,
        Polygons,
        Strings,
        Points,             //5
        SameHeightLines,
        StairLines,
        NUMBER_OF_COLOR_TYPES
    };
};
class ColorSettings{
public:
    int type;
    int colors[ColorType::NUMBER_OF_COLOR_TYPES][COL_NUM];
    void setColor(int type, int r, int g, int b);
};

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
public:
    static MapEditorOneSetting getDefaultSetting();
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

    int getGridSizeIndex();
    void setGridSizeIndex(int index);
    ColorSettings *getColorSetting();
    /**
        引数の色がどのタイプに当てはまるかを判断します
        @return 何も当てはまらない場合は負数
    */
    static int checkColorType(ColorSettings *col);
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
