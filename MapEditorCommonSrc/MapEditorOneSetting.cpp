//#include "stdafx.h"
//#include "HPLLibCommon.h"
#include "MapEditorOneSetting.h"
#include <fstream>
#include "HPLLib/HPLError.h"
#include "HPLLib/HPLStringModifier.h"

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
        hpl::error::halt("Not setting file path");
    }
    std::ifstream ifs(initialSettingFileName.c_str());
    if(!ifs.is_open()){
//        hpl::error::halt("Couldn't open map setting file");
        return false;
    }else{
        const int CORRECT_CHECKSUM = 9;
        int checksum = 0;

        const int MAX_LENGTH = 256;
        char buf[MAX_LENGTH];
        while(ifs.getline(buf, MAX_LENGTH)){
            std::string line = std::string(buf);
            if(buf[0] == '#' || line.compare("") == 0){
                continue;
            }
            std::vector<std::string> splitted = hpl::string::Split(line, "=");
            if((int)splitted.size() < 2){
                continue;
            }
            std::vector<std::string> colors = hpl::string::Split(splitted[1], ",");

            if(splitted[0].compare(GRID_SIZE_INDEX_TAG) == 0){
                gridSizeIndex = atoi(splitted[1].c_str());
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_COLOR_PRESET_TAG) == 0){
                colorSetting.type = atoi(splitted[1].c_str());
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_BACKGROUND_TAG) == 0){
                for(int i = 0; i < COL_NUM; i ++){
                    colorSetting.background[i] = atoi(colors[i].c_str());
                }
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_GRID_TAG) == 0){
                for(int i = 0; i < COL_NUM; i ++){
                    colorSetting.gridLine[i] = atoi(colors[i].c_str());
                }
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_LINES_TAG) == 0){
                for(int i = 0; i < COL_NUM; i ++){
                    colorSetting.lines[i] = atoi(colors[i].c_str());
                }
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_POLYGONS_TAG) == 0){
                for(int i = 0; i < COL_NUM; i ++){
                    colorSetting.polygons[i] = atoi(colors[i].c_str());
                }
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_STRINGS_TAG) == 0){
                for(int i = 0; i < COL_NUM; i ++){
                    colorSetting.strings[i] = atoi(colors[i].c_str());
                }
                checksum ++;
            }else if(splitted[0].compare(COLOR_SETTING_POINTS_TAG) == 0){
                for(int i = 0; i < COL_NUM; i ++){
                    colorSetting.points[i] = atoi(colors[i].c_str());
                }
                checksum ++;
            }else if(splitted[0].compare(EDITOR_FLAGS_TAG) == 0){
                for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
                    flags[i] = (atoi(colors[i].c_str()) != 0)? true: false;
                }
                checksum ++;
            }else {
                std::string str = splitted[0];
                hpl::error::halt("Illegal setting tag:[%s]", str.c_str());
            }
        }
        ifs.close();
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
        fprintf(fp, "%s=", COLOR_SETTING_BACKGROUND_TAG);
        outputColor(fp, this->colorSetting.background, COL_NUM);
        fprintf(fp, "\n%s=", COLOR_SETTING_GRID_TAG);
        outputColor(fp, this->colorSetting.gridLine, COL_NUM);
        fprintf(fp, "\n%s=", COLOR_SETTING_LINES_TAG);
        outputColor(fp, this->colorSetting.lines, COL_NUM);
        fprintf(fp, "\n%s=", COLOR_SETTING_POLYGONS_TAG);
        outputColor(fp, this->colorSetting.polygons, COL_NUM);
        fprintf(fp, "\n%s=", COLOR_SETTING_STRINGS_TAG);
        outputColor(fp, this->colorSetting.strings, COL_NUM);
        fprintf(fp, "\n%s=", COLOR_SETTING_POINTS_TAG);
        outputColor(fp, this->colorSetting.points, COL_NUM);
        fprintf(fp, "\n%s=", EDITOR_FLAGS_TAG);
        for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
            fprintf(fp, "%d,", flags[i]? 1: 0);
        }
        fclose(fp);
    }
    return true;
}

void MapEditorOneSetting::outputColor(FILE* fp, int col[], int colNum)
{
    for(int i = 0; i < colNum; i ++){
        fprintf(fp, "%d", col[i]);
        if(i < COL_NUM - 1){
            fprintf(fp, ",");
        }
    }
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
        setting->background[0] = 255;
        setting->background[1] = 255;
        setting->background[2] = 255;
        setting->gridLine[0] = 100;
        setting->gridLine[1] = 100;
        setting->gridLine[2] = 100;
        setting->lines[0] = 0;
        setting->lines[1] = 0;
        setting->lines[2] = 0;
        setting->polygons[0] = 200;
        setting->polygons[1] = 200;
        setting->polygons[2] = 200;
        setting->strings[0] = 0;
        setting->strings[1] = 0;
        setting->strings[2] = 0;
        setting->points[0] = 0;
        setting->points[1] = 0;
        setting->points[2] = 255;
    case COL_CUSTOM:
        break;
    case COL_MARATHON:
        setting->background[0] = 0;
        setting->background[1] = 0;
        setting->background[2] = 0;
        setting->gridLine[0] = 10;
        setting->gridLine[1] = 10;
        setting->gridLine[2] = 10;
        setting->lines[0] = 50;
        setting->lines[1] = 255;
        setting->lines[2] = 0;
        setting->polygons[0] = 0;
        setting->polygons[1] = 50;
        setting->polygons[2] = 0;
        setting->strings[0] = 100;
        setting->strings[1] = 255;
        setting->strings[2] = 0;
        setting->points[0] = 255;
        setting->points[1] = 255;
        setting->points[2] = 0;
        break;
    default:
        hpl::error::halt("Invalid color preset type:[%d]", type);
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

std::string MapEditorOneSetting::getFilePath()
{
    return initialSettingFileName;
}

MapEditorOneSetting MapEditorOneSetting::getDefaultSetting()
{
    MapEditorOneSetting setting;
    setting.setSettingToDefault();
    return setting;
}

int MapEditorOneSetting::checkColorType(ColorSettings *col)
{
    ColorSettings temp;
    MapEditorOneSetting::setColorSetting(COL_FORGE, &temp);
    if(memcmp(col, &temp, sizeof(ColorSettings)) == 0){
        return COL_FORGE;
    }
    MapEditorOneSetting::setColorSetting(COL_MARATHON, &temp);
    if(memcmp(col, &temp, sizeof(ColorSettings)) == 0){
        return COL_MARATHON;
    }

    //ÉJÉXÉ^ÉÄ
    return -1;
}
