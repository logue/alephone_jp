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

#include <HPLAlephLib.h>

#include <vector>
#include <string>
using namespace std;


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
    //level names stock
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

void wxStringToChar(wxString& str, char* cstr);
