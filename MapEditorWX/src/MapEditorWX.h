#pragma once

#include <wx/wxprec.h>
#include <wx/bitmap.h>

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

#include <HPLLib/HPLAlephLib.h>
#include <MapEditorOneSetting.h>
#include <MapEditorOneInnerSetting.h>

#include <vector>
#include <string>

static wxString TITLE_TEXT_BASE = wxString(_T("Map Editor One"));

//選択したものの種類
enum{
    _no_selected,
    _selected_point,
    _selected_line,
    _selected_polygon,
    _selected_object,
};

/**
    アプリケーションのメインクラス
*/
class MapEditorWX: public wxApp
{
public:

    //////////////////////////////////////////////
    ////// Level names
    //level names stock
    std::vector<std::string> levelNameList;

    //editing level index
    int editLevelIndex;

    //color for polygon type
    std::vector<wxColor> polygonTypeColorList;
    
    //color for height(variables)
    std::vector<wxColor> heightColorList;

    ///////////////////////
    //オブジェクト関連
    //オブジェクトタイプ
    hpl::aleph::Information objectTypeInfo[NUMBER_OF_MAP_OBJECT_TYPES];
        //モンスター
        hpl::aleph::Information monsterTypeInfo[NUMBER_OF_MONSTER_TYPES];
        //オブジェ
        hpl::aleph::Information sceneryTypeInfo[NUMBER_OF_SCENERY_DEFINITIONS];
        //アイテム
        hpl::aleph::Information itemTypeInfo[NUMBER_OF_DEFINED_ITEMS];
        //音
        hpl::aleph::Information soundSourceTypeInfo[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
        //起動
        hpl::aleph::Information activateTypeInfo[NUMBER_OF_ACTIVATE_TYPES];

    //フラグ
    hpl::aleph::InformationBinded flagInfo[NUMBER_OF_OBJECT_FLAGS];

    ////////////////////////
    //マップ関連
    //環境
    hpl::aleph::Information envInfo[NUMBER_OF_ENVIRONMENTS];
    //背景
    hpl::aleph::Information landscapeInfo[NUMBER_OF_LANDSPACES];
    //TODO ゲームタイプ
    //NUMBER_OF_GAME_TYPES
    //環境タイプ
    hpl::aleph::InformationBinded envTypeInfo[NUMBER_OF_ENV_TYPES];
    //ミッションタイプ
    hpl::aleph::InformationBinded missionTypeInfo[NUMBER_OF_MISSION_TYPES];

    //ターミナルタイプ
    hpl::aleph::Information terminalTypeInfo[NUMBER_OF_GROUP_TYPES];

    //ポリゴンタイプ
    hpl::aleph::Information polygonTypeInfo[NUMBER_OF_POLYGON_TYPE];

    //周囲音楽
    hpl::aleph::Information ambientSoundTypeInfo[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
    //ランダムサウンド
    hpl::aleph::Information randomSoundTypeInfo[NUMBER_OF_RANDOM_SOUND_DEFINITIONS];

    ////////////////////////
    //選択情報
    //選択対象のID
    hpl::aleph::map::HPLSelectData selectData;

    //コピペで保持するデータ
    hpl::aleph::map::HPLRealMapData storedMapData;
    //ずらす位置
    int storedDataDiffPointDelta[2];

    //マップアイコン
    std::vector<wxBitmap> iconBitmaps;

    ///////////////////////
    // 線追加
    //線追加における最初の点指定か？
    bool isFirstOfLineToAdd;
    //前回選択した点のインデックス
    int prevPointIndex;

    //編集設定
    MapEditorOneSetting setting;

    //Shapesモードか？
    bool isLoadedShapesFile;

    //プリセットで追加するポリゴンの頂点数
    int nPolygonPoints;

    //テクスチャデータ
    std::vector<std::vector<wxBitmap> > textureBitmaps;

    //編集モードとメニューIDの対応
    std::map<int, int> menuIDMap;

private:
    
    ///////////////////////
    // view grid
    /** ビュー＆グリッドマネージャー */
    hpl::aleph::view::HPLViewGridManager viewGridManager;

    //マップが変更されたか
    bool isChanged;

    //イベント管理
    hpl::aleph::HPLEventManager eventManager;

    //色設定をファイルから読み込む
    bool loadColorSetting();
public:


    /**
        ビューグリッドの調整マネージャーを取得します
    */
    hpl::aleph::view::HPLViewGridManager* getViewGridManager();

    virtual bool OnInit();
    /**
        一般的な初期化
    */
    bool initialize();

    //////////////////////////
    // ポリゴン整合性
    //ポリゴンが正しいかどうかを検査します(高速版)
    bool isPolygonValidityStored(int polyIndex);

    //ポリゴン整合性情報を更新します
    void updatePolygonValidityStored();

    //イベントマネージャーを取得します
    hpl::aleph::HPLEventManager* getEventManager();
};

//wxString->char
///disabled

DECLARE_APP(MapEditorWX)

//void wxStringToChar(wxString& str, char* cstr);
