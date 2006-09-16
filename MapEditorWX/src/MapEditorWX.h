#pragma once

#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "wx/settings.h"

#include "AlephOne/header.h"
#include "AlephOne/extensions.h"
#include "AlephOne/FileHandler.h"
#include "AlephOne/map.h"
#include "AlephOne/game_wad.h"
#include "AlephOne/weapons.h"
#include "AlephOne/items.h"
#include "AlephOne/monsters.h"
#include "AlephOne/scenery_definitions.h"
#include "AlephOne/mysound.h"

#include <vector>
#include <string>
using namespace std;

const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_ZOOM_DIVISION = 3;
const int ZOOM_DIVISION_STEP = 10;
const int ZOOM_DIVISION_MAX = 200;
const int ZOOM_DIVISION_MIN = 1;
const int ZOOM_DIVISION_DEFAULT = 100;
const int OFFSET_X_WORLD = 32768;
const int OFFSET_Y_WORLD = 32768;
const int NUMBER_OF_GLID = 5;

const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

//点とクリック地点の距離がこれ以下であれば選択する。
//リスト順に探索する
const int POINT_DISTANCE_EPSILON = 5;

//選択したものの種類
enum{
    _no_selected,
    _selected_point,
    _selected_line,
    _selected_polygon,
    _selected_object,
};

//名称
typedef struct Information_tag{
    string jname;
}Information;
//値つき名称
typedef struct InformationBinded_tag{
    string jname;
    int bind;
}InformationBinded;

/**
    アプリケーションのメインクラス
*/
class MapEditorWX: public wxApp
{
public:
    virtual bool OnInit();
    vector<string> levelNameList;
    //editing level index
    int editLevelIndex;
    //divide map scale
    int zoomDivision;
    //drawing offset
    int offsetX, offsetY;
    //color for polygon type
    vector<wxColor> polygonTypeColorList;
    //color for height(variables)
    vector<wxColor> heightColorList;
};

//wxString->char
///disabled

DECLARE_APP(MapEditorWX)
