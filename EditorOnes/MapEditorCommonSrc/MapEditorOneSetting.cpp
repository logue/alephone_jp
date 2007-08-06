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
static char *EDITOR_FLAGS_TAG = "FLAGS";
static char* COLOR_SETTING_COLOR_PRESET_TAG = "COLOR_PRESET";
static char* COLOR_SETTING_TAGS[100] ={
    "BACKGROUND",
    "GRID",
    "LINES",
    "POLYGONS",
    "STRINGS",
    "POINTS",
    "SAME_HEIGHT_LINES",
    "STAIR_LINES"
};

void ColorSettings::setColor(int type, int r, int g, int b)
{
    colors[type][0] = r;
    colors[type][1] = g;
    colors[type][2] = b;
}

static void tagFault(const char* str)
{
    hpl::error::halt("Illegal setting tag:[%s]", str);
}

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
            }else if(splitted[0].compare(EDITOR_FLAGS_TAG) == 0){
                for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
                    flags[i] = (atoi(colors[i].c_str()) != 0)? true: false;
                }
                checksum ++;
            }else{
                bool found = false;
                for(int tag = 0; tag < ColorType::NUMBER_OF_COLOR_TYPES; tag ++){
                    if(splitted[0].compare(COLOR_SETTING_TAGS[tag]) == 0){
                        for(int i = 0; i < COL_NUM; i ++){
                            colorSetting.colors[tag][i] = atoi(colors[i].c_str());
                        }
                        found = true;
                        checksum++;
                        break;
                    }
                }
                if(!found){
                    tagFault(splitted[0].c_str());
                }
            }
        }
        ifs.close();
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
        for(int i = 0; i < ColorType::NUMBER_OF_COLOR_TYPES; i ++){
            fprintf(fp, "%s=", COLOR_SETTING_TAGS[i]);
            outputColor(fp, this->colorSetting.colors[i], COL_NUM);
        }
        fprintf(fp, "\n%s=", EDITOR_FLAGS_TAG);
        for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
            fprintf(fp, "%d,", flags[i]? 1: 0);
        }
        fprintf(fp,"\n");
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
	fprintf(fp,"\n");
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

	//save setting
	this->saveSetting();
}
void MapEditorOneSetting::setColorSetting(int type)
{
    MapEditorOneSetting::setColorSetting(type, &colorSetting);
	this->saveSetting();
}

//static
void MapEditorOneSetting::setColorSetting(int type, ColorSettings *setting)
{
    setting->type = type;
    switch(type){
    case COL_FORGE:
        setting->setColor(ColorType::Background, 255, 255, 255);
        setting->setColor(1, 100, 100, 100);
        setting->setColor(2, 0, 0, 0);
        setting->setColor(3, 200, 200, 200);
        setting->setColor(4, 0, 0, 0);
        setting->setColor(5, 0, 0, 255);
        setting->setColor(ColorType::SameHeightLines, 200, 100, 200);
        setting->setColor(ColorType::StairLines, 150, 100, 150);
    case COL_CUSTOM:
        break;
    case COL_MARATHON:
        setting->setColor(ColorType::Background, 0, 0, 0);
        setting->setColor(1, 50, 50, 50);
        setting->setColor(2, 50, 255, 0);
        setting->setColor(3, 0, 50, 0);
        setting->setColor(4, 100, 255, 0);
        setting->setColor(5, 255, 255, 0);
        setting->setColor(ColorType::SameHeightLines, 50, 100, 50);
        setting->setColor(ColorType::StairLines, 150, 200, 150);
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

/**
    デフォルト設定を取得します
*/
MapEditorOneSetting MapEditorOneSetting::getDefaultSetting()
{
    MapEditorOneSetting setting;
    setting.setSettingToDefault();
    return setting;
}

/**
    col1とcol2が一致するかどうか確かめます
*/
static bool equalsColorSetting(ColorSettings& col1, ColorSettings& col2)
{
    for(int i = 0; i < ColorType::NUMBER_OF_COLOR_TYPES; i ++){
        if(col1.colors[i][0] != col2.colors[i][0] ||
            col1.colors[i][1] != col2.colors[i][1] ||
            col1.colors[i][2] != col2.colors[i][2])
        {
            return false;
        }

    }
    return true;
}

/**
    カラータイプを探り当てます
*/
int MapEditorOneSetting::checkColorType(ColorSettings *col)
{
    ColorSettings temp;
    MapEditorOneSetting::setColorSetting(COL_FORGE, &temp);
    if(equalsColorSetting(*col, temp)){
        return COL_FORGE;
    }
    MapEditorOneSetting::setColorSetting(COL_MARATHON, &temp);
    if(equalsColorSetting(*col, temp)){
        return COL_MARATHON;
    }

    //カスタム
    return COL_CUSTOM;
}

/**
	フラグの取得
*/
bool MapEditorOneSetting::getFlag(int flagId)
{
	wxASSERT(flagId >= 0 && flagId < NUMBER_OF_EDITOR_FLAGS);
	return this->flags[flagId];
}
void MapEditorOneSetting::setFlag(int flagId, bool flg)
{
	wxASSERT(flagId >= 0 && flagId < NUMBER_OF_EDITOR_FLAGS);
	this->flags[flagId] = flg;
}
