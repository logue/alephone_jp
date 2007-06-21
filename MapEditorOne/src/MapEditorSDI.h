// MapEditorSDI.h : MapEditorSDI アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル
#include "HPLLibMFC.h"
#include "HPLLogger.h"      //logger for debug

#include "header.h"
#include "extensions.h"
#include "FileHandler.h"
#include "map.h"
#include "game_wad.h"
#include "weapons.h"
#include "items.h"
#include "monsters.h"
#include "media.h"
#include "scenery_definitions.h"
#include "mysound.h"
#include "computer_interface.h"
#include "render.h"
#include "shapes_sdl.h"
#include "shell.h"
#include "editor.h"
#include "platforms.h"
#include "lightsource.h"
#include "shape_definitions.h"
#include "collection_definition.h"

#include "HPLLib/HPLAlephLib.h"

//#include "placement.h"
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "SDLToWin32/SDLToWin32.h"

#include "MonsterPropertyDialog.h"
#include "PolygonTypeDialog.h"
#include "HeightDialog.h"
#include "LevelParameterDialog.h"
#include "TerminalDialog.h"
#include "VisualDialog.h"
#include "ToolDialog.h"
#include "ObjectPlacementDialog.h"
#include "SelectLevelDialog.h"
#include "PolygonPropertyDialog.h"
#include "EditorInforDialog.h"
#include "AnnotationDialog.h"
#include "SelectPolygonDialog.h"
#include "TextureDialog.h"
#include "TextureDialog.h"
#include "TextureChildDialog.h"
#include "LinePropertyDialog.h"
#include "PointPropertyDialog.h"
#include "SidePropertyDialog.h"

#include "MapEditorOneSetting.h"
#include "MapEditorOneInnerSetting.h"
#include "EventManager.h"

#include <HPLLib/HPLAlephLib.h>

// CMapEditorSDIApp:
// このクラスの実装については、MapEditorSDI.cpp を参照してください。
//
/*
const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

const int NUMBER_OF_LANDSPACES = 4;
//点とクリック地点の距離がこれ以下であれば選択する。
//リスト順に探索する
const int POINT_DISTANCE_EPSILON = 5;
const int OBJECT_DISTANCE_EPSILON = 8;
const int LINE_DISTANCE_EPSILON = 5;

static char *DATA_DIR_NAME = "./data/";
static char *INI_FILE_NAME = "./setting.ini";
static char * MAP_ICONS_DIR_NAME = "Map Icons/";
static char * HILIGHTED_ICONS_DIR_NAME = "Highlighted/";
static char * MAP_ICONS_IMAGE_NAME_LIST_FILE_NAME = "MapIconImageList.txt";
*/
const int START_OF_TEXTURE = _collection_walls1;

extern HPLLogger logger;

//map icons


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
    CString jname;
}Information;
//値つき名称
typedef struct InformationBinded_tag{
    CString jname;
    int bind;
}InformationBinded;

//class HPLSelectData;

/**
    MapEditorOneメインアプリケーション
*/
class CMapEditorSDIApp : public CWinApp
{
public:
	CMapEditorSDIApp();
    ~CMapEditorSDIApp();

// オーバーライド
public:
	virtual BOOL InitInstance();
public:
    ///////////////////////
    //レベル関連

    /**レベルの名称*/
    CStringArray LevelNameList;
    
    //選択中のレベルインデックス
    int editLevelIndex;


public:
    ///////////////////////////
    //グリッド・表示関係

    /**選択中の倍率*/
    //int zoomDivision;

    //
    hpl::aleph::view::HPLViewGridManager gridManager;

    /**グリッド表示用間隔(世界距離に対応し、拡大縮小で大きさ変化)*/
    int gridIntervals[NUMBER_OF_GLID];

    //位置オフセット
    //POINT offset;

    /**現在のマウス座標*/
    //POINT nowMousePoint;

    /**一つ前のマウス座標*/
    //POINT oldMousePoint;

    //ポリゴンタイプの色
    COLORREF polygonTypeColor[NUMBER_OF_POLYGON_TYPE];

    //ダブルバッファリング
    CDC doubleBufferDC;
    CBitmap doubleBuffserBitmap;


    ///////////////////////
    //ツール・プロパティダイアログ

    //モードレスモンスタープロパティダイアログ
    CMonsterPropertyDialog *objectPropertyDialog;
    //モードレスポリゴンタイプダイアログ
    CPolygonTypeDialog *polygonTypeDialog;
    //モードレス表示高度ダイアログ
    CHeightDialog *heightDialog;
    //
    CToolDialog *toolDialog;
    //polygon property
    CPolygonPropertyDialog *polygonPropertyDialog;
    //点プロパティ
    CPointPropertyDialog *pointPropertyDialog;

    //texture dialog (palette)
    CTextureDialog *textureDialog;

    ///////////////////////////
    //名称などのストック

    //大別
    Information objectTypeInformations[NUMBER_OF_MAP_OBJECT_TYPES];
    //モンスターの種類
    Information monsterTypeInformations[NUMBER_OF_MONSTER_TYPES];
    //オブジェの種類
    Information sceneryTypeInformations[NUMBER_OF_SCENERY_DEFINITIONS];
    //アイテムの種類
    Information itemTypeInformations[NUMBER_OF_DEFINED_ITEMS];
    //音
    Information soundSourceInformations[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
    //起動
    Information activateTypeInformations[NUMBER_OF_ACTIVATE_TYPES];
    //フラグ
    InformationBinded objectFlagInformations[NUMBER_OF_OBJECT_FLAGS];

    //環境
    Information environmentInformations[NUMBER_OF_ENVIRONMENTS];
    //背景
    Information landscapeInformations[NUMBER_OF_LANDSPACES];
    //ゲームタイプ
    //InformationBinded gameTypeInformations[NUMBER_OF_GAME_TYPES];
    //環境タイプ
    InformationBinded environmentTypeInformations[NUMBER_OF_ENV_TYPES];
    //ミッションタイプ
    InformationBinded missionTypeInformations[NUMBER_OF_MISSION_TYPES];

    //ターミナルグループ
    Information terminalGroupTypeInformations[NUMBER_OF_GROUP_TYPES];

    //ポリゴンタイプ
    Information polygonTypeInformations[NUMBER_OF_POLYGON_TYPE];

    //ambient sounds
    Information ambientSoundTypeInformations[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
    //random sounds
    Information randomSoundTypeInformations[NUMBER_OF_RANDOM_SOUND_DEFINITIONS];

    // 実装
	afx_msg void OnAppAbout();


    /////////////////////

    //複数選択時の選択物リスト
    //TODO add selection
    //struct selectInformation selectGroupInformation;
    hpl::aleph::map::HPLSelectData selectDatas;

    //コピーアンドペースト用のデータリスト
    //ペースト時にこれらを元に新規作成します
    hpl::aleph::map::HPLRealMapData storedMapData;
    //その場に展開すると重なるので、どれだけずらすか(world座標)
    int storedDataPointDelta[2];

    //変更点の履歴
    hpl::aleph::map::HPLDoneHistory history;

    //selection group
    //vector<struct selectInformation> selectGroupInformationList;

    //SDL surface to win api device context
	SDLToWindows *m_SDLToWindows;

    //map icons
    vector<HBITMAP> bitmapList;


    //show / hide polygons, lines. points
    //表示している高さの範囲。選択にも反映される
    int viewHeightMax;
    int viewHeightMin;
    bool isRevealHiddenLines;

    //save check
    //when true, warn to save
    bool isChanged;

    //flag of first adding of lines
    bool isFirstOfLineToAdd;

    /////////////////////////////////////
    //線情報
    //前回の選択した点のインデックス
    //prev point user clicked.
    //if there is not, set NONE
    int previousPointIndex;

    //編集設定
    //Editor setting
    MapEditorOneSetting setting;

    //is shapes file loaded
    bool isLoadedShapesFile;

    //polygon to draw by preset
    int numberOfPolygonPoints;

    //is now on the point
    bool isNowOnThePoint;

    //texture bitmaps
    vector<vector<CBitmap*> > textureBitmaps;

    /**編集モードとメニューIDの対応*/
    map<int, int> menuIDMap;

	//ポリゴンが正しいかどうかを検査します（高速版）
	bool isPolygonValidityStored(int polyIndex);

	//ポリゴンの整合性を更新します
	void updatePolygonValidityStored();
private:
    //イベント管理
    mapeditorone::EventManager eventManager;
	//ポリゴンの整合性情報
	std::vector<bool> polygonValidity;
public:
    /**
        イベントマネージャー取得
    */
    mapeditorone::EventManager* getEventManager();

    //initialize all datas for application
    bool initialize();

    /**
        色設定をファイルから読み込む
    */
    bool loadColorSetting();
    
    /**
        グリッド関連をセットアップ
    */
    void setupGridManager(hpl::aleph::view::HPLViewGridManager* mgr,
        mapeditorone::MapEditorOneInnerSetting* innerSetting);

    /**
        アイコン用画像を読み込み
    */
    void loadIconBitmaps();

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnFileOpen();
};

extern CMapEditorSDIApp theApp;

//load information list
void loadInformations(const char* filename, int max, 
                      Information *informations);

//load bitmap/icon from resources to ImageList
void loadIcon(int id, CImageList* imageList);
//void loadBitmap(int id, CImageList* imageList, COLORREF key);

//load bitmap/icon from file
HBITMAP loadBitmapFromFile(const char *pathName);

//set object property to default
void setObjectPropertyToDefault();

void setCursor();

/**
   add objet on polygon
   return added object's index
*/
int addObject(struct world_point2d &world_point, int polygonIndex);

/**
    add point on polygon
    if it is on line, add point to the line and polygon
    @return added point's index
*/
int addPoint(struct world_point2d &world_point);

int addLine(int beginPointIndex, int endPointIndex);

void addPolygon(polygon_data* data);

/**
    get platform_data by using polygon index
    only platform has polygon index. not polygon have

    return NULL in no exists
*/
int searchPlatformIndexByPolygonIndex(int index);

//CString GetModulePathFileName(CString pName);

//簡易版
//
void getViewPointFromWorldPoint2D(world_point2d wpoint, int* dest);

