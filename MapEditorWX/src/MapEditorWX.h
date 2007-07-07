/*
MapEditorOne
Marathon and AlephOne's Map file editor
Copyright (C) 2007  Koji Koizumi(HN:HogePiyo)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#pragma once

#include <wx/wxprec.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include <wx/cursor.h>
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "wx/settings.h"


#include <HPLLib/HPLAlephLib.h>
#include <MapEditorOneSetting.h>
#include <MapEditorOneInnerSetting.h>


#include <vector>
#include <string>

static wxString TITLE_TEXT_BASE = wxString(_T("Map Editor One"));

class MapEditorMainFrame;

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
    int polygonTypeColors[NUMBER_OF_POLYGON_TYPE][3];
    
    //color for height(variables)
    //TODO height 用途
    int heightColorList[2][3];

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

/*    //アイテムアイコン
    wxBitmap itemIconBitmaps[NUMBER_OF_DEFINED_ITEMS];
    wxBitmap hilightedItemIconBitmaps[NUMBER_OF_DEFINED_ITEMS];

    //マップアイコン
    wxBitmap mapIconBitmaps[NUMBER_OF_MAP_ICONS];
    wxBitmap hilightedMapIconBitmaps[NUMBER_OF_MAP_ICONS];
*/

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
    //TODO texture
    std::vector<std::vector<wxBitmap> > textureBitmaps;

    //編集モードとメニューIDの対応
    //TODO menu
    std::map<int, int> menuIDMap;

    //リソースファイル
    wxXmlResource xrc;

    //高さが範囲外の線を表示するかどうか(デフォルト:false)
    bool isRevealHiddenLines;

    //マップが変更されたか
    bool isChanged;
    //ファイルパス
    wxString filePath;

    //プリセットで追加するポリゴンの頂点数
    int presetPolygonVertexCount;

    //現在のポイントは点の上にあるか？
    //ただし、高さ範囲の外にある場合考慮しない
    bool isNowOnThePoint;
    bool isNowOnTheLine;

    wxMenu linePopupMenu;
    wxMenu pointPopupMenu;

    //popup用インデックス覚書
    int popupEndpointIndex;
    int popupLineIndex;
    //public メンバ変数 ここまで
private:
    
    ///////////////////////
    // view grid
    /** ビュー＆グリッドマネージャー */
    hpl::aleph::view::HPLViewGridManager viewGridManager;

    //イベント管理
    hpl::aleph::HPLEventManager eventManager;

    //ストック情報管理
    hpl::aleph::HPLStockManager stockManager;

    //Shapesマネージャー
    hpl::shapes::HPLShapesManager shapesManager;

    //ツールごとのカーソル
    wxCursor cursors[ToolType::NUMBER_OF_TOOLS];

    //オンラインカーソル
    wxCursor onLineCursor;
    //オンポイントカーソル
    wxCursor onPointCursor;
    //通常ラインカーソル
    //wxCursor lineToolCursor;

    //追加中カーソル
    wxCursor onLineCursorAdding;
    wxCursor onPointCursorAdding;
    wxCursor lineToolCursorAdding;

    //バケツ
    wxCursor fillCursor;
    //虫眼鏡
    wxCursor magCursor;

    //ウインドウフレーム
    MapEditorMainFrame *frame;
public:
    ///////////////////////////////////
    ///////////////////////////////////
    // 関数

    /**
        ビューグリッドの調整マネージャーを取得します
    */
    hpl::aleph::view::HPLViewGridManager* getViewGridManager();

    //Shapesマネージャー取得
    hpl::shapes::HPLShapesManager* getShapesManager();

    virtual bool OnInit();
    /**
        一般的な初期化
    */
    bool initialize();


    //イベントマネージャーを取得します
    hpl::aleph::HPLEventManager* getEventManager();

    //ストックマネージャを取得します
    hpl::aleph::HPLStockManager* getStockManager();

    //ビュー座標をワールド座標に直す操作の簡易版
    world_point2d getWorldPointFromViewPoint(int vx, int vy);
    //
    void getViewPointFromWorldPoint(world_point2d& wpoint, int vpoint[2]);
    void getViewPointFromWorldPoint(int x, int y, int vpoint[2])
    {
        world_point2d wpoint = {x,y};
        this->getViewPointFromWorldPoint(wpoint, vpoint);
    }

    /**
        ビットマップの読み込み（簡易版）
    */
    void loadBitmap(const char* fname, wxImage* bitmap);
    void loadImage(const char* fname, wxImage* bitmap);
    /**
        カラーマスク付きで読み込み
    */
    void loadImage(const char* fname, wxImage* img, int r, int g, int b);

    /**
        現在のモード・ツールにあわせてカーソルを変更します
    */
    void setCursor();

    /**
        線編集情報を初期化します
    */
    void resetLineEditInfo();

    void getShapesImage(wxImage* img, int collection, int clut, int index);
private:

};

//実体を持たせます
DECLARE_APP(MapEditorWX)

//char->wx
wxString getString(const char* format, ...);
