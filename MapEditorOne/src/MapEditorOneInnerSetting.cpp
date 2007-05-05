#include "MapEditorOneInnerSetting.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <windows.h>

mapeditorone::MapEditorOneInnerSetting::MapEditorOneInnerSetting(const char* tagNameFilePath, const char* dataFilePath)
{
    std::ifstream ifs;
    ifs.open(tagNameFilePath);
    if(!ifs.is_open()){
        MessageBox(NULL, L"Cannot open tag file", L"", MB_OK);
        exit(-1);
    }
    ifs.close();

    ifs.open(dataFilePath);
    if(!ifs.is_open()){
        MessageBox(NULL, L"Cannot open inner data file", L"", MB_OK);
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
