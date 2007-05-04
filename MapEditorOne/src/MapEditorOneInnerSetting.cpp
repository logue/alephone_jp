#include "MapEditorOneInnerSetting.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <windows.h>

mapeditorone::MapEditorOneInnerSetting::MapEditorOneInnerSetting(const char* tagNameFilePath, const char* dataFilePath)
{
    ifstream ifs;
    ifs.open(tagNameFilePath);
    if(!ifs.is_open()){
        MessageBox(L"Cannot open tag file", MB_OK);
        exit(-1);
    }
    ifs.close();

    ifs.open(dataFilePath);
    if(!ifs.is_open){
        MessageBox(L"Cannot open inner data file", MB_OK);
        exit(-1);
    }
    ifs.close();
}
mapeditorone::MapEditorOneInnerSetting::~MapEditorOneInnerSetting()
{
    this->tagMap.clear();
    this->datas.clear();
}

std::string mapeditorone::MapEditorOneInnerSetting::getString(int type)
{
    std::string str = this->datas[type];
    if(str == NULL){
        MessageBox(L"Cannot find setting:", MB_OK);
        exit(-1);
    }
    return str;
}
int mapeditorone::MapEditorOneInnerSetting::getInt(int type)
{
    std::string str = this->getString(type);
    int num = atoi(str.c_str());
    return num;
}
double mapeditorone::MapEditorOneInnerSetting::getDouble(int type)
{
    std::string str = this->getString(type);
    double num = atof(str.c_str());
    return num;
}
