#pragma once

//dialogues
//modal
#include "AnnotationDialog.h"
#include "ColorCustomizeDialog.h"
#include "EditorPreferencesDialog.h"
#include "LevelInfoDialog.h"
#include "PlacementDialog.h"
#include "PlatformDialog.h"
#include "PolygonNumDialog.h"
#include "SelectLevelDialog.h"
#include "TerminalDialog.h"
#include "VisualDialog.h"

//modeless
//tool
#include "ToolDialog.h"
//height
#include "HeightDialog.h"
//palettes
#include "HeightPaletteDialog.h"
#include "LightPaletteDialog.h"
#include "MediaPaletteDialog.h"
#include "SoundPaletteDialog.h"
#include "TextureDialog.h"
//properties
#include "ObjectPropDialog.h"
#include "LinePropDialog.h"
#include "PointPropDialog.h"
#include "PolygonPropDialog.h"
#include "PolygonTypeDialog.h"
#include "SidePropDialog.h"


#include "MapEditorWX.h"
#include "HPLLib/HPLAlephLib.h"

/**
    event id
*/
enum
{
    ID_New = wxID_NEW,
    ID_Open = wxID_OPEN,
    ID_Save = wxID_SAVE,
    ID_SaveAs = wxID_SAVEAS,
    ID_Print = wxID_PRINT,
    ID_PrintPreview = wxID_PREVIEW,
    ID_PrintSetup = wxID_PRINT_SETUP,
    ID_Quit = wxID_EXIT,
    ID_About = wxID_ABOUT,

    ID_Undo = wxID_UNDO,
    ID_Redo = wxID_REDO,
    ID_Cut = wxID_CUT,
    ID_Copy = wxID_COPY,
    ID_Paste = wxID_PASTE,
    ID_Preference = wxID_PREFERENCES,

    ID_Merge = 1,
    //show
    ID_ToolDialog,
    ID_ZoomIn,
    ID_ZoomOut,
    ID_ZoomDefault,
    ID_MoveToCenter,
//    ID_ObjectPropDialog,
    ID_HeightDialog,

    //mode
    ID_DrawPolygonMode,
    ID_VisualMode,
    ID_PolygonTypeMode,
    ID_FloorHeightMode,
    ID_CeilingHeightMode,
    ID_FloorLightMode,
    ID_CeilingLightMode,
    ID_MediaMode,
    ID_FloorTextureMode,
    ID_CeilingTextureMode,

    //Special
    ID_JumpLevel,
    ID_LevelInfo,
    ID_ObjectPlacement,
    ID_TerminalViewer,

    //popup menu
    ID_LineProp,
    ID_ClockwiseSideProp,
    ID_CounterclockwiseSideProp,
    ID_PointProp,
};  

//リソースID
enum{
    ID_ANNOTATION_DIALOG,

};

/**
    editor's main frame
*/
class MapEditorMainFrame: public wxFrame
{
public:
    //プロパティ類 <en> properties
    ObjectPropDialog objPropDialog;
    LinePropDialog linePropDialog;
    PointPropDialog pointPropDialog;
    PolygonTypeDialog polyTypeDialog;
    PolygonPropDialog polyPropDialog;
    SidePropDialog sidePropDialog;
private:
    //ダブルバッファリング用Bitmap
    wxBitmap doubleBufferingBitmap;
    //wxMemoryDC doubleBufferingDC;
//    wxBufferedPaintDC bufferedPainDC

    /////////////////////
    //ダイアログ(モードレス)
    //tool
    ToolDialog toolDialog;
    //高さ <en> height
    HeightDialog heightDialog;
    //パレット類 <en> palettes
    HeightPaletteDialog heightPaletteDialog;
    LightPaletteDialog lightPaletteDialog;
    MediaPaletteDialog mediaPaletteDialog;
    TextureDialog textureDialog;

    SoundPaletteDialog soundPaletteDialog;

    //TODO モーダルだが、Side選択ダイアログも作ろう
    //TODO JumpLevel, LevelInfo

    //起動時と、色設定変更時にこれらを変更すること
    //TODO 設定変更コード
    //グリッド線細線
    wxPen gridPen;
    //グリッド線太線
    wxPen gridLargePen;
    //背景ペン
    wxPen backgroundPen;
    //背景ブラシ
    wxBrush backgroundBrush;
    //タイプ別ポリゴン色
    wxBrush polyTypeBrushes[NUMBER_OF_POLYGON_TYPE];
    //ポリゴン選択網掛けブラシ
    wxBrush polySelNetBrush;
    //インヴァリッドなポリゴン
    wxBrush invalidBrush;
    //選択色
    wxPen selectedLinePen;
    //通常線
    wxPen linePen;
    //通常点
    wxPen pointPen;
    wxBrush pointBrush;
    //通常ポリゴン
    wxBrush polyBrush;

    //同じ高さの線色
    wxPen sameHeightLinePen;
    //段差のある線色
    wxPen stairLinePen;

    //アイテムビットマップ
    wxImage itemBitmaps[NUMBER_OF_DEFINED_ITEMS];
    //ハイライト版
    wxImage hilightedItemBitmaps[NUMBER_OF_DEFINED_ITEMS];

    //マップ要素ビットマップ（特殊）
    wxImage mapItemBitmaps[NUMBER_OF_MAP_ICONS];
    //ハイライト版
    wxImage hilightedMapItemBitmaps[NUMBER_OF_MAP_ICONS];

    //
//    wxBitmap 
    //モンスターペン
    wxPen monsterPen;
    wxPen selectedMonsterPen;
    wxBrush monsterBrush;
    wxBrush selectedMonsterBrush;
    //プレイヤーペン・ブラシ
    wxPen playerPen;
    wxPen selectedPlayerPen;
    wxBrush playerBrush;
    wxBrush selectedPlayerBrush;
    //味方ペン・ブラシ <en> ally
    wxPen allyPen;
    wxPen selectedAllyPen;
    wxBrush allyBrush;
    wxBrush selectedAllyBrush;

    //範囲選択表示
    wxPen selectingPen;

    wxImage texture;
public:
    MapEditorMainFrame(const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
    virtual ~MapEditorMainFrame();

    //メニュー<en> menu
    //ファイルメニュー <en>Files menu
    void OnNew(wxCommandEvent& ev);
    void OnOpen(wxCommandEvent& ev);
    void OnSave(wxCommandEvent& ev);
    void OnSaveAs(wxCommandEvent& ev);
    void OnPrint(wxCommandEvent& ev);
    void OnPrintPreview(wxCommandEvent& ev);
    void OnPrintSetup(wxCommandEvent& ev);
    void OnQuit(wxCommandEvent& ev);
    void OnAbout(wxCommandEvent& ev);
    void OnMerge(wxCommandEvent& ev);

    //編集メニュー<en>Edit menus
    void OnUndo(wxCommandEvent& ev);
    void OnRedo(wxCommandEvent& ev);
    void OnCut(wxCommandEvent& ev);
    void OnCopy(wxCommandEvent& ev);
    void OnPaste(wxCommandEvent& ev);
    void OnPreference(wxCommandEvent& ev);

    //表示メニュー<en>show
    void OnToolDialog(wxCommandEvent& ev);
    void OnZoomIn(wxCommandEvent& ev);
    void OnZoomOut(wxCommandEvent& ev);
    void OnZoomDefault(wxCommandEvent& ev);
    void OnMoveToCenter(wxCommandEvent& ev);
//    void OnObjectPropDialog(wxCommandEvent& ev);
    void OnHeightDialog(wxCommandEvent& ev);

    //モード<en>Mode
    void OnDrawPolygonMode(wxCommandEvent& ev);
    void OnVisualMode(wxCommandEvent& ev);
    void OnPolygonTypeMode(wxCommandEvent& ev);
    void OnFloorHeightMode(wxCommandEvent& ev);
    void OnCeilingHeightMode(wxCommandEvent& ev);
    void OnFloorLightMode(wxCommandEvent& ev);
    void OnCeilingLightMode(wxCommandEvent& ev);
    void OnMediaMode(wxCommandEvent& ev);
    void OnFloorTextureMode(wxCommandEvent& ev);
    void OnCeilingTextureMode(wxCommandEvent& ev);

    //特別メニュー<en>Special!
    void OnJumpLevel(wxCommandEvent& ev);
    void OnLevelInfo(wxCommandEvent& ev);
    void OnObjectPlacement(wxCommandEvent& ev);
    void OnTerminalViewer(wxCommandEvent& ev);

    //ポップアップメニュー <en> popup menu
    void OnLineProp(wxCommandEvent& ev);
    void OnClockwiseSide(wxCommandEvent& ev);
    void OnCounterclockwiseSide(wxCommandEvent& ev);
    void OnPointProp(wxCommandEvent& ev);

    void OnPaint(wxPaintEvent& ev);

    void OnLeftDown(wxMouseEvent& ev);
    void OnLeftUp(wxMouseEvent& ev);
    void OnRightDown(wxMouseEvent& ev);
    void OnRightUp(wxMouseEvent& ev);
    void OnMotion(wxMouseEvent& ev);
    void OnMouseWheel(wxMouseEvent& ev);
    void OnLeftDoubleClick(wxMouseEvent& ev);

    //サイズ変更<en>change window size event
    void OnSize(wxSizeEvent& ev);
    //ダブルバッファリング時の背景削除停止用<en>to disable erasing backgroud for double buffering
    void OnEraseBackground(wxEraseEvent& ev);

    //
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()

private:
    /**
        ダブルバッファリング準備
        起動時とウインドウサイズ変更時に呼ぶ
        <en> setup buffer for double buffering
        call this when (1)starting and (2)resizing window
    */
    void createDoubleBuffer();
    /**
        メニューのセットアップ
        <en> setup menu items
    */
    void setupMenus();

    /**
        マップデータの表示
        <en> draw map items
    */
    /**
        背景描画
        <en> draw background, drawable area, and grid
        @param dc デバイスコンテキスト <en> device context
    */
    void drawBackground(wxDC* dc);
    void drawPolygons(wxDC* dc);
    void drawLines(wxDC* dc);
    void drawSides(wxDC* dc);
    void drawPoints(wxDC* dc);
    void drawObjects(wxDC* dc);
    void drawAnnotations(wxDC* dc);

    //////////////////////////////////
    // 名称規定：doLButtonOn[編集モード名]
    //           doLButtonOn[ドローモードのツール名]
    // <en>     :doLButtonOn[name of Edit Mode]
    //          :doLButtonOn[name of tool in Draw Mode]
    /**
        マウスイベント処理
    */
    void doLButtonOnDrawMode(wxMouseEvent& ev);
        void doLButtonOnArrowTool(wxMouseEvent& ev);
        void doLButtonOnFillTool(wxMouseEvent& ev);
        void doLButtonOnHandTool(wxMouseEvent& ev);
        void doLButtonOnLineTool(wxMouseEvent& ev);
        void doLButtonOnMagnifyTool(wxMouseEvent& ev);
        void doLButtonOnSkullTool(wxMouseEvent& ev);
        void doLButtonOnTextTool(wxMouseEvent& ev);
        void doLButtonOnPolygonTool(wxMouseEvent& ev);
    void doLButtonOnPolygonMode(wxMouseEvent& ev);
    void doLButtonOnFloorHeightMode(wxMouseEvent& ev);
    void doLButtonOnCeilingHeightMode(wxMouseEvent& ev);
    void doLButtonOnFloorLightMode(wxMouseEvent& ev);
    void doLButtonOnCeilingLightMode(wxMouseEvent& ev);
    void doLButtonOnMediaMode(wxMouseEvent& ev);
    void doLButtonOnFloorTextureMode(wxMouseEvent& ev);
    void doLButtonOnCeilingTextureMode(wxMouseEvent& ev);

    /**
        マウス左ボタンをあげたとき
    */
    void doLUpOnArrowTool(wxMouseEvent& ev);
    void doLUpOnPolygonTool(wxMouseEvent& ev);

    // オフセットを指定したマウスポイントによって移動させます
    void moveMapOffset(int x, int y);

    /////////////////////////////////////
    // 名称規定：doMouseMotionOn[]
    /**
        矢印ツール@ドローモードでD&D
    */
    void doMouseMotionOnDrawMode(wxMouseEvent& ev);
        void doMouseMotionOnArrowTool(wxMouseEvent& ev);
        void doMouseMotionOnFillTool(wxMouseEvent& ev);
        void doMouseMotionOnHandTool(wxMouseEvent& ev);
        void doMouseMotionOnLineTool(wxMouseEvent& ev);
        void doMouseMotionOnMagnifyTool(wxMouseEvent& ev);
        void doMouseMotionOnSkullTool(wxMouseEvent& ev);
        void doMouseMotionOnTextTool(wxMouseEvent& ev);
        void doMouseMotionOnPolygonTool(wxMouseEvent& ev);
    void doMouseMotionOnPolygonMode(wxMouseEvent& ev);
    void doMouseMotionOnFloorHeightMode(wxMouseEvent& ev);
    void doMouseMotionOnCeilingHeightMode(wxMouseEvent& ev);
    void doMouseMotionOnFloorLightMode(wxMouseEvent& ev);
    void doMouseMotionOnCeilingLightMode(wxMouseEvent& ev);
    void doMouseMotionOnMediaMode(wxMouseEvent& ev);
    void doMouseMotionOnFloorTextureMode(wxMouseEvent& ev);
    void doMouseMotionOnCeilingTextureMode(wxMouseEvent& ev);

    /**
        マップ描画用ブラシ・ペンのセットアップ
        @param setting カラー設定データ <en> setting data for color
    */
    void setupPenAndBrush(ColorSettings* setting);

    /**
        アイコン用のビットマップファイルを読み込みます
    */
    void loadIconBitmaps(const char* baseDirPath);

    /**
        編集モードメニューのチェックを全てはずします
    */
    void uncheckModesOnMenu();

    /**
        オフセットを設定します
        @param mx,my ビュー座標の基点位置
    */
    void setupSelectDataGroupOffsets(int mx, int my);

    /**
        @param ev
        @return 選択に成功した場合真
    */
    bool tryToSelectOneItem(wxMouseEvent& ev);

    /**
        新しいモードに切り替えます
    */
    void changeEditMode(int mode);

    void closeAllModelessDialogs();

    void initLevel();

    /**
        ダイアログを出して編集中のマップを破壊してよいかを聞き出します。
        
        @param ユーザからOKが出れば真。出なければ偽。
            また、編集されてなければ真が返る
    */
    bool askDestructMap();
};
