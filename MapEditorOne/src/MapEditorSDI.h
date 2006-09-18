// MapEditorSDI.h : MapEditorSDI アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル
#include "HPLLibMFC.h"
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
#include "AlephOne/computer_interface.h"

//#include "AlephOne/placement.h"


#include "SDLToWin32/SDLToWin32.h"

#include "MonsterPropertyDialog.h"
#include "PolygonTypeDialog.h"
#include "HeightDialog.h"
#include "LevelParameterDialog.h"
#include "TerminalDialog.h"
#include "VisualDialog.h"

// CMapEditorSDIApp:
// このクラスの実装については、MapEditorSDI.cpp を参照してください。
//

const int NUMBER_OF_POLYGON_TYPE = 24;
const int ZOOM_DIVISION_STEP = 5;
const int ZOOM_DIVISION_MAX = 200;
const int ZOOM_DIVISION_MIN = 1;
const int ZOOM_DIVISION_DEFAULT = 100;
const int OFFSET_X_WORLD = 32768;
const int OFFSET_Y_WORLD = 32768;
const int NUMBER_OF_GLID = 5;

const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

const int NUMBER_OF_LANDSPACES = 4;
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
    CString jname;
}Information;
//値つき名称
typedef struct InformationBinded_tag{
    CString jname;
    int bind;
}InformationBinded;

struct selectInformation{
    bool isSelected(){
        return isSelected_;
    }
    void setSelected(bool sel){
        isSelected_ = sel;
    }
    void clear(){
        endpointIndexList.clear();
        lineIndexList.clear();
        polygonIndexList.clear();
        objectIndexList.clear();
        setSelected(false);
    }
    //点のリスト
    vector<int> endpointIndexList;

    //線のリスト
    vector<int> lineIndexList;

    //ポリゴンのリスト
    vector<int> polygonIndexList;

    vector<int> objectIndexList;
private:
    bool isSelected_;

};

/**
    MapEditorOneメインアプリケーション
*/
class CMapEditorSDIApp : public CWinApp
{
public:
	CMapEditorSDIApp();


// オーバーライド
public:
	virtual BOOL InitInstance();
public:
    //レベルの名称
    CStringArray LevelNameList;
    
    //選択中の倍率
    int zoomDivision;

    //グリッド表示用間隔(世界距離に対応し、拡大縮小で大きさ変化)
    int gridIntervals[NUMBER_OF_GLID];
    int nowGridInterval;

    //位置オフセット
    POINT offset;

    POINT nowMousePoint;
    POINT oldMousePoint;

    //選択したものの種類
    int selectType;
    //選択したもののインデックス
    int selectIndex;

    //グリッド
    //ボタン押してる？
    bool isPressLButtonWithShift;

    //選択中のレベルインデックス
    int editLevelIndex;
    //ポリゴンタイプの色
    COLORREF polygonTypeColor[NUMBER_OF_POLYGON_TYPE];

    //モードレスモンスタープロパティダイアログ
    CMonsterPropertyDialog *objectPropertyDialog;
    //モードレスポリゴンタイプダイアログ
    CPolygonTypeDialog *polygonTypeDialog;
    //モードレス表示高度ダイアログ
    CHeightDialog *heightDialog;

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
    InformationBinded gameTypeInformations[NUMBER_OF_GAME_TYPES];
    //環境タイプ
    InformationBinded environmentTypeInformations[NUMBER_OF_ENV_TYPES];
    //ミッションタイプ
    InformationBinded missionTypeInformations[NUMBER_OF_MISSION_TYPES];

    //ターミナルグループ
    Information terminalGroupTypeInformations[NUMBER_OF_GROUP_TYPES];

    //ポリゴンタイプ
    Information polygonTypeInformations[NUMBER_OF_POLYGON_TYPE];

// 実装
	afx_msg void OnAppAbout();
    BOOL isObjectPropertyDialogShow;
    BOOL isHeightDialogShow;
    BOOL isPolygonTypeDialogShow;

    //ダブルバッファリング
    CDC doubleBufferDC;
    CBitmap doubleBuffserBitmap;

    //ポリゴンや線を持ったときの第一ポイントからのオフセット
    //相対座標
    POINT polygonPoints[8];
    int polygonPointNum;

    //選択範囲始点
    POINT selectStartPoint;
    bool isSelectingGroup;

    //複数選択時の選択物リスト
    struct selectInformation selectGroupInformation;


	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnFileOpen();
};

extern CMapEditorSDIApp theApp;