#ifndef _MAP_EDITOR_ONE_SETTING_
#define _MAP_EDITOR_ONE_SETTING_

//#include "stdafx.h"

//#include "MapEditorSDI.h"

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
