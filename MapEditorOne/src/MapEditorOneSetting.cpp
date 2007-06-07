//#include "stdafx.h"
//#include "HPLLibCommon.h"
#include "MapEditorOneSetting.h"

MapEditorOneSetting::MapEditorOneSetting()
{
    this->initialSettingFileName = "";
}
void MapEditorOneSetting::setIniFileName(const char *iniFileName)
{
    initialSettingFileName = std::string(iniFileName);
}

static char *GRID_SIZE_INDEX_TAG = "GRID_SIZE_INDEX";
static char *COLOR_SETTING_COLOR_PRESET_TAG = "COLOR_PRESET";
static char *COLOR_SETTING_BACKGROUND_TAG = "BACKGROUND";
static char *COLOR_SETTING_GRID_TAG = "GRID";
static char *COLOR_SETTING_LINES_TAG = "LINES";
static char *COLOR_SETTING_POLYGONS_TAG = "POLYGONS";
static char *COLOR_SETTING_STRINGS_TAG = "STRINGS";
static char *COLOR_SETTING_POINTS_TAG = "POINTS";
static char *EDITOR_FLAGS_TAG = "FLAGS";

/**
    try to load file.
    @return false : failure
*/
bool MapEditorOneSetting::loadSetting()
{
    if(initialSettingFileName.compare("") == 0){
        return false;
    }
    FILE *fp = fopen(initialSettingFileName.c_str(), "r");
    if(fp == NULL){
        return false;
    }else{
        const int CORRECT_CHECKSUM = 9;
        int checksum = 0;

        const int MAX_LENGTH = 256;
        char buf[MAX_LENGTH];
        while(fgets(buf, MAX_LENGTH, fp)){
            string line = string(buf);
            if(buf[0] == '#' || line.compare("") == 0){
                continue;
            }
            vector<string> splitted = hpl::string::Split(line, "=");
            if((int)splitted.size() < 2){
                continue;
            }
            vector<string> colors = hpl::string::Split(splitted[1], ",");

            if(splitted[0].compare(GRID_SIZE_INDEX_TAG) == 0){
                gridSizeIndex = atoi(splitted[1].c_str());
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_COLOR_PRESET_TAG) == 0){
                colorSetting.type = atoi(splitted[1].c_str());
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_BACKGROUND_TAG) == 0){
                colorSetting.background = RGB(atoi(colors[0].c_str()),
                    atoi(colors[1].c_str()),
                    atoi(colors[2].c_str()));
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_GRID_TAG) == 0){
                colorSetting.gridLine = RGB(atoi(colors[0].c_str()),
                    atoi(colors[1].c_str()),
                    atoi(colors[2].c_str()));
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_LINES_TAG) == 0){
                colorSetting.lines = RGB(atoi(colors[0].c_str()),
                    atoi(colors[1].c_str()),
                    atoi(colors[2].c_str()));
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_POLYGONS_TAG) == 0){
                colorSetting.polygons = RGB(atoi(colors[0].c_str()),
                    atoi(colors[1].c_str()),
                    atoi(colors[2].c_str()));
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_STRINGS_TAG) == 0){
                colorSetting.strings = RGB(atoi(colors[0].c_str()),
                    atoi(colors[1].c_str()),
                    atoi(colors[2].c_str()));
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_POINTS_TAG) == 0){
                colorSetting.points = RGB(atoi(colors[0].c_str()),
                    atoi(colors[1].c_str()),
                    atoi(colors[2].c_str()));
                checksum ++;
            }else if(splitted[0].compare(EDITOR_FLAGS_TAG) == 0){
                for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
                    flags[i] = (atoi(colors[i].c_str()) != 0)? true: false;
                }
                checksum ++;
            }else {
                CString str = CString(splitted[0].c_str());
                AfxMessageBox(CString("Illigal Setting Tag!:") + str);
            }
        }
        fclose(fp);
        /*if(checksum < CORRECT_CHECKSUM){
            AfxMessageBox("invalid setting data");
            return false;
        }*/
    }
    return true;
}
bool MapEditorOneSetting::saveSetting()
{
    if(initialSettingFileName.compare("") == 0){
        return false;
    }
    FILE *fp = fopen(initialSettingFileName.c_str(), "w");
    if(fp == NULL){
        return false;
    }else{
        fprintf(fp, "%s=%d\n", GRID_SIZE_INDEX_TAG, gridSizeIndex);
        fprintf(fp, "%s=%d\n", COLOR_SETTING_COLOR_PRESET_TAG, colorSetting.type);
        fprintf(fp, "%s=%d,%d,%d\n", COLOR_SETTING_BACKGROUND_TAG, GetRValue(colorSetting.background),
            GetGValue(colorSetting.background),
            GetBValue(colorSetting.background));
        fprintf(fp, "%s=%d,%d,%d\n", COLOR_SETTING_GRID_TAG, GetRValue(colorSetting.gridLine),
            GetGValue(colorSetting.gridLine),
            GetBValue(colorSetting.gridLine));
        fprintf(fp, "%s=%d,%d,%d\n", COLOR_SETTING_LINES_TAG, GetRValue(colorSetting.lines),
            GetGValue(colorSetting.lines),
            GetBValue(colorSetting.lines));
        fprintf(fp, "%s=%d,%d,%d\n", COLOR_SETTING_POLYGONS_TAG, GetRValue(colorSetting.polygons),
            GetGValue(colorSetting.polygons),
            GetBValue(colorSetting.polygons));
        fprintf(fp, "%s=%d,%d,%d\n", COLOR_SETTING_STRINGS_TAG, GetRValue(colorSetting.strings),
            GetGValue(colorSetting.strings),
            GetBValue(colorSetting.strings));
        fprintf(fp, "%s=%d,%d,%d\n", COLOR_SETTING_POINTS_TAG, GetRValue(colorSetting.points),
            GetGValue(colorSetting.points),
            GetBValue(colorSetting.points));
        fprintf(fp, "%s=", EDITOR_FLAGS_TAG);
        for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
            fprintf(fp, "%d,", flags[i]? 1: 0);
        }
        fclose(fp);
    }
    return true;
}

void MapEditorOneSetting::setSettingToDefault()
{
    gridSizeIndex = 0;
    setColorSetting(COL_FORGE);
    for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
        flags[i] = true;
    }
}

int MapEditorOneSetting::getGridSizeIndex()
{
    return gridSizeIndex;
}
void MapEditorOneSetting::setGridSizeIndex(int index)
{
    gridSizeIndex = index;
}
ColorSettings *MapEditorOneSetting::getColorSetting()
{
    return &colorSetting;
}
void MapEditorOneSetting::setColorSetting(ColorSettings *setting)
{
    if(setting->type != COL_CUSTOM){
        setColorSetting(setting->type);
    }else{
        memcpy(&colorSetting, setting, sizeof(ColorSettings));
    }
}
void MapEditorOneSetting::setColorSetting(int type)
{
    MapEditorOneSetting::setColorSetting(type, &colorSetting);
}

//static
void MapEditorOneSetting::setColorSetting(int type, ColorSettings *setting)
{
    setting->type = type;
    switch(type){
    case COL_FORGE:
        setting->background = RGB(255,255,255);
        setting->gridLine = RGB(100,100,100);
        setting->lines = RGB(0,0,0);
        setting->polygons = RGB(200,200,200);
        setting->strings = RGB(0,0,0);
        setting->points = RGB(0,0,255);
    case COL_CUSTOM:
        break;
    case COL_MARATHON:
        setting->background = RGB(0,0,0);
        setting->gridLine = RGB(10,10,10);
        setting->lines = RGB(50,255,0);
        setting->polygons = RGB(0,50,0);
        setting->strings = RGB(100,255,0);
        setting->points = RGB(255,255,0);
        break;
    default:
        char buf[256];
        sprintf(buf, "%d", type);
        AfxMessageBox(CString("Invalid color preset type:") + CString(buf));
    }
}

//static
void MapEditorOneSetting::copyColorSetting(ColorSettings *dest, ColorSettings *src)
{
    if(src->type != COL_CUSTOM){
        MapEditorOneSetting::setColorSetting(src->type, dest);
    }else{
        memcpy(dest, src, sizeof(ColorSettings));
    }
}

CString MapEditorOneSetting::getFilePath()
{
    CString str = CString(initialSettingFileName.c_str());
    return str;
}
