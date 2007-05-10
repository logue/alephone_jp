#include "MapEditorOneInnerSetting.h"
#include "HPLLib/HPLAlephLib.h"

#include <fstream>
#include <cstdio>
#include <cstdlib>

#include <windows.h>

const int MAX_FILE_PATH = 260;

mapeditorone::MapEditorOneInnerSetting::MapEditorOneInnerSetting(const char* tagNameFilePath, const char* dataFilePath)
{
    std::ifstream ifs;
    ifs.open(tagNameFilePath);
    if(!ifs.is_open()){
        MessageBox(NULL, L"Cannot open tag file", L"", MB_OK);
        exit(-1);
    }
    //ƒ^ƒO“Ç‚ÝŽæ‚è
    char buf[MAX_FILE_PATH];
    int counter = 0;
    while(ifs.getline(buf, MAX_FILE_PATH) != NULL){
        if(strcmp(buf, "")){
            continue;
        }
        std::string src(buf);
        tagMap[counter] = src;
    }
    ifs.close();

    ifs.open(dataFilePath);
    if(!ifs.is_open()){
        MessageBox(NULL, L"Cannot open inner data file", L"", MB_OK);
        exit(-1);
    }
    while(ifs.getline(buf, MAX_FILE_PATH) != NULL){
        std::string src(buf);
        std::vector<std::string> pair = hpl::string::Split(src, "=");
        if(pair.size() < 2){
            //‹ó”’‚Í–³Ž‹
            continue;
        }
        for(int i = 0; i < mapeditorone::TagType::MaxTagTypes; i ++){
            if(pair[0].compare(tagMap[i]) == 0){
                datas[i] = pair[1];
            }
        }
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
