#include "MapEditorOneInnerSetting.h"
#include "HPLLib/HPLAlephLib.h"

#include <fstream>
#include <cstdio>
#include <cstdlib>

#ifdef WIN32
#include <windows.h>
#endif

const int MAX_FILE_PATH = 260;

static void messageBox(const char* format, ...){
}

mapeditorone::MapEditorOneInnerSetting::MapEditorOneInnerSetting(const char* tagNameFilePath, const char* dataFilePath)
{
    char buf[MAX_FILE_PATH];
    {
        std::ifstream ifs;
        ifs.open(tagNameFilePath);
        if(!ifs.is_open()){
#ifdef WIN32
            MessageBox(NULL, L"Cannot open tag file", L"", MB_OK);
#else
            fprintf(stderr, "Couldn't open tag file");
#endif

            exit(-1);
        }
        //タグ読み取り
        int counter = 0;
        while(ifs.getline(buf, MAX_FILE_PATH) != NULL){
            if(strcmp(buf, "") == 0){
                continue;
            }
            std::string src(buf);
            tagMap[counter] = src;
            counter ++;
        }
        if(counter < mapeditorone::TagType::MaxTagTypes){
            MessageBox(NULL, L"The number of InnerSetting tags is too few", L"Error", MB_OK);
            exit(1);
        }
        ifs.close();
    }

    {
        ifstream ifs(dataFilePath);
        if(!ifs.is_open()){
            MessageBox(NULL, L"Cannot open inner data file", L"", MB_OK);
            exit(-1);
        }
        int counter = 0;
        while(ifs.getline(buf, MAX_FILE_PATH) != NULL){
            std::string src(buf);
            std::vector<std::string> pair = hpl::string::Split(src, "=");
            if(pair.size() < 2){
                //空白は無視
                continue;
            }
            for(int i = 0; i < mapeditorone::TagType::MaxTagTypes; i ++){
                if(pair[0].compare(tagMap[i]) == 0){
                    datas[i] = pair[1];
                    counter ++;
                    break;
                }
            }
        }
        if(counter < mapeditorone::TagType::MaxTagTypes){
            MessageBox(NULL, L"The number of InnerSetting datas is too few", L"Error", MB_OK);
            exit(1);
        }
        ifs.close();
    }
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


//グリッド情報をセットアップする
void mapeditorone::setupGridManager(hpl::aleph::view::HPLViewGridManager* mgr,
    mapeditorone::MapEditorOneInnerSetting* innerSetting)
{
    int intervals[] ={
        WORLD_ONE * 2, WORLD_ONE, WORLD_ONE / 2, WORLD_ONE / 4, WORLD_ONE / 8
    };
    hpl::aleph::view::ZoomProperties zoomProp;
    zoomProp.zoomDivisionStep = innerSetting->getInt(mapeditorone::TagType::ZOOM_DIVISION_STEP);
    zoomProp.zoomDivisionDefault = innerSetting->getInt(mapeditorone::TagType::ZOOM_DIVISION_DEFAULT);
    zoomProp.zoomDivisionMin = innerSetting->getInt(mapeditorone::TagType::ZOOM_DIVISION_MIN);
    zoomProp.zoomDivisionMax = innerSetting->getInt(mapeditorone::TagType::ZOOM_DIVISION_MAX);
    zoomProp.zoomDivStepThreshold = innerSetting->getInt(mapeditorone::TagType::ZOOM_DIV_STEP_THRESHOLD);
    zoomProp.zoomDivisionStepDetail = innerSetting->getInt(mapeditorone::TagType::ZOOM_DIVISION_STEP_DETAIL);
    for(int i = 0; i < NUMBER_OF_GLID; i ++){
        zoomProp.gridIntervals[i] = intervals[i];
    }
    mgr->setProp(&zoomProp);
}