#include "MapEditorWX.h"
#include "MapEditorMainFrame.h"

IMPLEMENT_APP(MapEditorWX)

//load color informations

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;
const int WINDOW_DEFAULT_X = 50;
const int WINDOW_DEFAULT_Y = 50;
const int BUF_MAX = 1024;


bool MapEditorWX::OnInit()
{
    //一般的な初期設定
    if(!this->initialize()){
        wxMessageBox(_T("Initialize failure"));
        exit(-1);
    }

    //ウインドウフレームを生成します
    frame = new MapEditorMainFrame(
        TITLE_TEXT_BASE,
        wxPoint(WINDOW_DEFAULT_X, WINDOW_DEFAULT_Y), wxSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT));
    frame->Show(true);
    //SetTopWindow(frame);

    
    return TRUE;
}

bool MapEditorWX::initialize()
{
    //設定読み込み
    setting.setIniFileName(INI_FILE_NAME);
    if(!setting.loadSetting()){
        hpl::error::caution("No setting file found. I'll make default one.");
        setting.setSettingToDefault();
        //保存
        setting.saveSetting();
    }
    //levelNameList

    //面
    this->editLevelIndex = 0;

    //polygonTypeColorList
    //heightColorList

    //情報読み込み

    //オブジェクト全般
    hpl::aleph::loadInformation("data/ObjectTypes.txt", NUMBER_OF_OBJECT_TYPES, this->objectTypeInfo);
    //モンスター
    hpl::aleph::loadInformation("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES, this->monsterTypeInfo);
    //オブジェ
    hpl::aleph::loadInformation("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS, this->sceneryTypeInfo);
    //アイテム
    hpl::aleph::loadInformation("data/DefinedItems.txt", NUMBER_OF_DEFINED_ITEMS, this->itemTypeInfo);
    //音
    hpl::aleph::loadInformation("data/SoundSourceTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, this->soundSourceTypeInfo);
    //起動
    hpl::aleph::loadInformation("data/ActivateTypes.txt", NUMBER_OF_ACTIVATE_TYPES, this->activateTypeInfo);

    //フラグ
    this->flagInfo[0].bind = _map_object_is_invisible;
    this->flagInfo[1].bind = _map_object_hanging_from_ceiling;
    this->flagInfo[2].bind = _map_object_is_blind;
    this->flagInfo[3].bind = _map_object_is_deaf;
    this->flagInfo[4].bind = _map_object_floats;
    this->flagInfo[5].bind = _map_object_is_network_only;

    //ターミナル
    hpl::aleph::loadInformation("data/TerminalGroupTypes.txt", NUMBER_OF_GROUP_TYPES, this->terminalTypeInfo);

    //ポリゴン
    hpl::aleph::loadInformation("data/PolygonType.txt", NUMBER_OF_POLYGON_TYPE, this->polygonTypeInfo);

    //環境
    hpl::aleph::loadInformation("data/Environments.txt", NUMBER_OF_ENVIRONMENTS, this->envInfo);
    //背景
    hpl::aleph::loadInformation("data/Landscapes.txt", NUMBER_OF_LANDSPACES, this->landscapeInfo);

    //env type(bind)
    this->envTypeInfo[0].bind = _environment_normal;
    this->envTypeInfo[1].bind = _environment_vacuum;
    this->envTypeInfo[2].bind = _environment_magnetic;
    this->envTypeInfo[3].bind = _environment_rebellion;
    this->envTypeInfo[4].bind = _environment_low_gravity;
    this->envTypeInfo[5].bind = _environment_network;
    this->envTypeInfo[6].bind = _environment_single_player;
    //mission type(bind)
    this->missionTypeInfo[0].bind = _mission_none;
    this->missionTypeInfo[1].bind = _mission_extermination;
    this->missionTypeInfo[2].bind = _mission_exploration;
    this->missionTypeInfo[3].bind = _mission_retrieval;
    this->missionTypeInfo[4].bind = _mission_repair;
    this->missionTypeInfo[5].bind = _mission_rescue;

    //背景
    hpl::aleph::loadInformation("data/AmbientSoundTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS, this->ambientSoundTypeInfo);
    //背景
    hpl::aleph::loadInformation("data/RandomSoundTypes.txt", NUMBER_OF_RANDOM_SOUND_DEFINITIONS, this->randomSoundTypeInfo);

    //色設定読み込み
    if(!hpl::aleph::loadColorSetting(POLYGON_COLOR_FILE_NAME, this->polygonTypeColors, NUMBER_OF_POLYGON_TYPE)){
        return false;
    }

    //選択関連
    this->selectData.clear();

    //コピペ用ストック
    storedDataDiffPointDelta[0] = storedDataDiffPointDelta[1] = 0;

    //線の最初の点
    isFirstOfLineToAdd = true;
    //以前選択した点
    prevPointIndex = NONE;

    //グリッド設定
    mapeditorone::MapEditorOneInnerSetting innerSetting =
        mapeditorone::MapEditorOneInnerSetting(TAG_NAME_FILE_PATH, INNER_DATA_FILE_PATH);
    mapeditorone::setupGridManager(this->getViewGridManager(),
        &innerSetting);
    this->getViewGridManager()->setGridIntervalIndex(this->setting.getGridSizeIndex());
    nPolygonPoints = 3;

    //TODO textureBitmaps

    //カーソル読み込み <en> load cursor images
    /*
        TI_ARROW = 0,
        TI_FILL,
        TI_HAND,
        TI_LINE,
        TI_MAGNIFY,
        TI_SKULL,
        TI_TEXT,
        TI_POLYGON,
    */
    char CURSOR_BASE_DIR[] = "data/img/";
    char *cursorSkull = "cursor2.bmp";
    char *cursorPolygon = "cur00004.bmp";
    char *cursorLine = "LineCursor1.bmp";
    char *cursorFill = "pot.bmp";
    char *cursorMag = "mag1.bmp";

    int cursorId[] ={
        wxCURSOR_ARROW,
        -1,
        wxCURSOR_HAND,
        -1,
        -1,
        -1,
        wxCURSOR_IBEAM,
        -1
    };
    //カーソルデータ読み込み
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
        if(cursorId[i] != -1){
            //規定のもので使えるもの
            cursors[i] = wxCursor(cursorId[i]);
        }else{
            //ファイルパス
            char* fname;
            if(i == ToolType::TI_SKULL){
                fname = cursorSkull;
            }else if(i == ToolType::TI_POLYGON){
                fname = cursorPolygon;
            }else if(i == ToolType::TI_LINE){
                fname = cursorLine;
            }else if(i == ToolType::TI_FILL){
                fname = cursorFill;
            }else if(i == ToolType::TI_MAGNIFY){
                fname = cursorMag;
            }
            wxString path = wxConvCurrent->cMB2WX(CURSOR_BASE_DIR);
            wxString pathF = wxConvCurrent->cMB2WX(fname);
            path.Append(pathF);
            //読み込み
            wxImage bmp;
            bmp.LoadFile(path);
            bmp.SetMaskColour(255,255,255);
            //カーソル設定
            cursors[i] = wxCursor(bmp);
        }
    }
    {
        wxImage img;
        loadImage("data/img/onLine.bmp", &img, 255,255,255);
        onLineCursor = wxCursor(img);
        loadImage("data/img/onPoint.bmp", &img, 255,255,255);
        onPointCursor = wxCursor(img);
        loadImage("data/img/onPoint2.bmp", &img, 255,255,255);
        onPointCursorAdding = wxCursor(img);
        loadImage("data/img/onLine2.bmp", &img, 255,255,255);
        onLineCursorAdding = wxCursor(img);
        loadImage("data/img/LineCursor2.bmp", &img, 255,255,255);
        lineToolCursorAdding = wxCursor(img);

    }

    //対象外の線を表示するかどうか
    this->isRevealHiddenLines = false;
    
    this->isNowOnTheLine = this->isNowOnThePoint = false;

    return true;
}


hpl::aleph::view::HPLViewGridManager* MapEditorWX::getViewGridManager()
{
    return &this->viewGridManager;
}
//イベントマネージャーを取得します
hpl::aleph::HPLEventManager* MapEditorWX::getEventManager()
{
    return &this->eventManager;
}
//ストックマネージャを取得します
hpl::aleph::HPLStockManager* MapEditorWX::getStockManager()
{
    return &this->stockManager;
}
//Shapesマネージャー取得
hpl::shapes::HPLShapesManager* MapEditorWX::getShapesManager()
{
    return &this->shapesManager;
}

//ビュー座標をワールド座標に直す操作の簡易版
world_point2d MapEditorWX::getWorldPointFromViewPoint(int vx, int vy)
{
    hpl::aleph::view::HPLViewGridManager* mgr = this->getViewGridManager();
    int offset[2];
    mgr->getOffset(offset);
    int DIV = mgr->getZoomDivision();
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(vx, vy,
        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, offset[0], offset[1]);
    return wpoint;
}
//
void MapEditorWX::getViewPointFromWorldPoint(world_point2d& wpoint, int vpoint[2])
{
    hpl::aleph::view::HPLViewGridManager* mgr = this->getViewGridManager();
    int offset[2];
    mgr->getOffset(offset);
    int DIV = mgr->getZoomDivision();
    hpl::aleph::map::getViewPointFromWorldPoint2D(wpoint, vpoint,
        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, offset[0], offset[1]);
}


/**
    ビットマップの読み込み（簡易版）
*/
void MapEditorWX::loadBitmap(const char* fname, wxImage* bitmap)
{
    if(!bitmap->LoadFile(wxConvCurrent->cMB2WX(fname), wxBITMAP_TYPE_BMP)){
        hpl::error::halt("Couldn't load bitmap[%s]", fname);
    }

}
void MapEditorWX::loadImage(const char* fname, wxImage* bitmap)
{
    loadBitmap(fname, bitmap);
}
/**
    カラーマスク付きで読み込み
*/
void MapEditorWX::loadImage(const char* fname, wxImage* img, int r, int g, int b)
{
    loadBitmap(fname, img);
    //カラーマスク設定
    img->SetMaskColour(r,g,b);
}

/**
    現在のモード・ツールにあわせてカーソルを変更します
*/
void MapEditorWX::setCursor()
{
    int editMode = this->getEventManager()->getEditModeType();
    int toolType = this->getEventManager()->getToolType();
    if(editMode == EditModeType::EM_DRAW){
        if(toolType == ToolType::TI_LINE){
            if(this->isNowOnTheLine){
                if(this->isFirstOfLineToAdd){
                    //線の上にいる
                    wxSetCursor(this->onLineCursor);
                }else{
                    wxSetCursor(this->onLineCursorAdding);
                }
            }else if(toolType == ToolType::TI_LINE && this->isNowOnThePoint){
                if(this->isFirstOfLineToAdd){
                    //点の上にいる
                    wxSetCursor(this->onPointCursor);
                }else{
                    wxSetCursor(this->onPointCursorAdding);
                }
            }else{
                if(this->isFirstOfLineToAdd){
                    wxSetCursor(cursors[toolType]);
                }else{
                    wxSetCursor(this->lineToolCursorAdding);
                }
            }
        }else{
            //TODO カーソル
            ::wxSetCursor(cursors[toolType]);
        }
    }else{
        //矢印にする
        ::wxSetCursor(cursors[0]);
    }
}
/**
    線編集情報を初期化します
*/
void MapEditorWX::resetLineEditInfo()
{
    prevPointIndex = NONE;
    isFirstOfLineToAdd = true;
}

void MapEditorWX::getShapesImage(wxImage* img, int collection, int clut, int index, double illumination)
{
	//サーフェイス取得
    
	SDL_Surface* surface = this->getShapesManager()->getSurface(collection, clut, index, illumination);
	img->Create(surface->w, surface->h);
	SDL_LockSurface(surface);
	for(int x = 0; x < surface->w; x ++){
		for(int y = 0; y < surface->h; y ++){
            Uint32 pixel = hpl::surface::getpixel(surface, x, y);
            unsigned char r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            img->SetRGB(x, y, r, g, b);
		}
	}
	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
    
/*
    SDL_Color palette[256];
    byte** outp = (byte**)malloc(sizeof(byte*));
    SDL_Surface* surface = this->getShapesManager()->getRawSurface(collection, clut, index, illumination,
        palette, outp);
    img->Create(surface->w, surface->h);
	for(int x = 0; x < surface->w; x ++){
		for(int y = 0; y < surface->h; y ++){
            int pixel = (int)hpl::surface::getpixel(surface, x, y);
            img->SetRGB(x, y, palette[pixel].b, palette[pixel].g, palette[pixel].r);
        }
    }
    SDL_FreeSurface(surface);
    free(outp);*/
}

//char->wx
wxString getString(const char* format, ...)
{
    char message[BUF_MAX];
    va_list maker;
    va_start(maker, format);
    vsprintf(message, format, maker);
    wxString str = wxConvertMB2WX(message);
    return str;
}
