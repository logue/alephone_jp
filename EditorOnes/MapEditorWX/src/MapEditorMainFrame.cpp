#include "MapEditorMainFrame.h"

//大きいペンのサイズ
const int LARGE_PEN_SIZE = 2;
//バッファサイズ
const int BUF_MAX = 1024;

//点とクリック地点の距離がこれ以下であれば選択する。
//リスト順に探索する
//const int POINT_DISTANCE_EPSILON = 5;

BEGIN_EVENT_TABLE(MapEditorMainFrame, wxFrame)
    EVT_MENU(ID_Quit, MapEditorMainFrame::OnQuit)
    EVT_MENU(ID_About, MapEditorMainFrame::OnAbout)
    EVT_MENU(ID_Print, MapEditorMainFrame::OnPrint)
    EVT_MENU(ID_PrintPreview, MapEditorMainFrame::OnPrintPreview)
    EVT_MENU(ID_PrintSetup, MapEditorMainFrame::OnPrintSetup)
    EVT_MENU(ID_New, MapEditorMainFrame::OnNew)
    EVT_MENU(ID_Open, MapEditorMainFrame::OnOpen)
    EVT_MENU(ID_Save, MapEditorMainFrame::OnSave)
    EVT_MENU(ID_SaveAs, MapEditorMainFrame::OnSaveAs)
    EVT_MENU(ID_Merge, MapEditorMainFrame::OnMerge)
	EVT_MENU(ID_SavePhysicsFile, MapEditorMainFrame::OnSavePhysicsFile)

    //edit menu
    EVT_MENU(ID_Undo, MapEditorMainFrame::OnUndo)
    EVT_MENU(ID_Redo, MapEditorMainFrame::OnRedo)
    EVT_MENU(ID_Cut, MapEditorMainFrame::OnCut)
    EVT_MENU(ID_Copy, MapEditorMainFrame::OnCopy)
    EVT_MENU(ID_Paste, MapEditorMainFrame::OnPaste)
	EVT_MENU(ID_Delete, MapEditorMainFrame::OnDelete)
    EVT_MENU(ID_Preference, MapEditorMainFrame::OnPreference)
	
    //show
    EVT_MENU(ID_ToolDialog, MapEditorMainFrame::OnToolDialog)
    EVT_MENU(ID_ZoomIn, MapEditorMainFrame::OnZoomIn)
    EVT_MENU(ID_ZoomOut, MapEditorMainFrame::OnZoomOut)
    EVT_MENU(ID_ZoomDefault, MapEditorMainFrame::OnZoomDefault)
    EVT_MENU(ID_MoveToCenter, MapEditorMainFrame::OnMoveToCenter)
    EVT_MENU(ID_HeightDialog, MapEditorMainFrame::OnHeightDialog)

    //mode
    EVT_MENU(ID_DrawPolygonMode, MapEditorMainFrame::OnDrawPolygonMode)
    EVT_MENU(ID_VisualMode, MapEditorMainFrame::OnVisualMode)
    EVT_MENU(ID_PolygonTypeMode, MapEditorMainFrame::OnPolygonTypeMode)
    EVT_MENU(ID_FloorHeightMode, MapEditorMainFrame::OnFloorHeightMode)
    EVT_MENU(ID_CeilingHeightMode, MapEditorMainFrame::OnCeilingHeightMode)
    EVT_MENU(ID_FloorLightMode, MapEditorMainFrame::OnFloorLightMode)
    EVT_MENU(ID_CeilingHeightMode, MapEditorMainFrame::OnCeilingLightMode)
    EVT_MENU(ID_MediaMode, MapEditorMainFrame::OnMediaMode)
    EVT_MENU(ID_FloorTextureMode, MapEditorMainFrame::OnFloorTextureMode)
    EVT_MENU(ID_CeilingTextureMode, MapEditorMainFrame::OnCeilingTextureMode)

    //special
    EVT_MENU(ID_JumpLevel, MapEditorMainFrame::OnJumpLevel)
    EVT_MENU(ID_LevelInfo, MapEditorMainFrame::OnLevelInfo)
    EVT_MENU(ID_ObjectPlacement, MapEditorMainFrame::OnObjectPlacement)
    EVT_MENU(ID_TerminalViewer, MapEditorMainFrame::OnTerminalViewer)

    //popup
    EVT_MENU(ID_LineProp, MapEditorMainFrame::OnLineProp)
    EVT_MENU(ID_ClockwiseSideProp, MapEditorMainFrame::OnClockwiseSide)
    EVT_MENU(ID_CounterclockwiseSideProp, MapEditorMainFrame::OnCounterclockwiseSide)
    EVT_MENU(ID_PointProp, MapEditorMainFrame::OnPointProp)
    EVT_MENU(ID_PolygonProp, MapEditorMainFrame::OnPolygonProp)
    EVT_MENU(ID_SetVisualModePlayerStartPosition, MapEditorMainFrame::OnSetVisualModePlayerPosition)

    EVT_PAINT(MapEditorMainFrame::OnPaint)
    EVT_LEFT_DOWN(MapEditorMainFrame::OnLeftDown)
    EVT_LEFT_DCLICK(MapEditorMainFrame::OnLeftDoubleClick)
    EVT_RIGHT_DOWN(MapEditorMainFrame::OnRightDown)
    EVT_LEFT_UP(MapEditorMainFrame::OnLeftUp)
    EVT_RIGHT_UP(MapEditorMainFrame::OnRightUp)
    EVT_MOTION(MapEditorMainFrame::OnMotion)
    EVT_MOUSEWHEEL(MapEditorMainFrame::OnMouseWheel)
    EVT_SIZE(MapEditorMainFrame::OnSize)
    EVT_ERASE_BACKGROUND(MapEditorMainFrame::OnEraseBackground)

	EVT_KEY_DOWN(MapEditorMainFrame::OnKeyDown)
END_EVENT_TABLE()

MapEditorMainFrame::MapEditorMainFrame(const wxString& title,
                                       const wxPoint& pos,
                                       const wxSize& size)
                                       :wxFrame((wxFrame*)NULL,
                                       wxID_ANY, title, pos, size)
{
    this->setupMenus();

    CreateStatusBar();
    SetStatusText( _T("get ready..."));

    
    //ペン・ブラシのセットアップ
    this->setupPenAndBrush(wxGetApp().setting.getColorSetting());

    //マップのアイコンビットマップをファイルから読み込み
    this->loadIconBitmaps(DATA_DIR_NAME);

    //ドローモードでスタート
    wxCommandEvent dummy;
    OnDrawPolygonMode(dummy);

    //tool
    this->toolDialog.Create(this, wxID_ANY);
    this->toolDialog.Show();

    //height
    this->heightDialog.Create(this, wxID_ANY);
    this->heightDialog.Show();
    
    //パレット
    this->heightPaletteDialog.Create(this, wxID_ANY);
    this->lightPaletteDialog.Create(this, wxID_ANY);
    this->mediaPaletteDialog.Create(this, wxID_ANY);
    this->soundPaletteDialog.Create(this, wxID_ANY);

    //プロパティ
    this->objPropDialog.Create(this, wxID_ANY);
    this->polyTypeDialog.Create(this, wxID_ANY);
    this->sidePropDialog.Create(this, wxID_ANY);

    this->initLevel();

	hpl::shapes::HPLShapesManager* shpmgr = wxGetApp().getShapesManager();
    shpmgr->initScreen();

    //Shapesファイル読み込み
    const char* SHAPES_FILE_PATH = "Shapes.shpA";
    bool result = shpmgr->loadShapesFile(SHAPES_FILE_PATH);
	if(result){
		//
		int collection = 5;
		int clut = 0;
		int index = 0;
		double illumination = 1.0;
		//wxGetApp().getShapesImage(&texture, collection, clut, index, illumination);

        {
		    //256x80
		    int palSizeW = 10;
		    int palSizeH = 10;
		    int pitch = 50;
		    int lineNum = 8;
		    this->paletteImg.Create(palSizeW * pitch, palSizeH * lineNum);
		    SDL_Color palette[256];
		    byte** outp = (byte**)malloc(sizeof(byte*));
		    SDL_Surface* surface = wxGetApp().getShapesManager()->getRawSurface(collection, clut, index,
			    illumination, palette, outp);
		    SDL_FreeSurface(surface);
		    free(outp);
		    //パレットに配置していく
		    //collection情報
            struct collection_header* header = get_collection_header(collection);
            int clutNum = header->collection->clut_count;
		    int colorNum = header->collection->color_count;
		    int color_table_offset = header->collection->color_table_offset;
		    int numColors = 0;
            struct rgb_color_value* palette1 = get_collection_colors(collection, clut, numColors);
		    for(int i = 0; i < numColors; i ++){
			    int x = (i % pitch) * palSizeW;
			    int y = (i / pitch) * palSizeH;
			    int w = palSizeW;
			    int h = palSizeH;
			    wxRect rect(x, y, w, h);
			    paletteImg.SetRGB(rect,
				    palette1[i].red,
				    palette1[i].green,
				    palette1[i].blue);
		    }

		    surface = wxGetApp().getShapesManager()->getSurface(collection, clut, index,
			    illumination);
		    //色数の取得
		    wxGetApp().getShapesImageFromSurface(&texture, surface);
		    SDL_FreeSurface(surface);
        }
        //all texture loading
        for(int i = 0; i < MAXIMUM_COLLECTIONS; i ++){
            collection_definition* collectionDef = get_collection_definition(i);
            if(collectionDef == NULL){
                continue;
            }
            if(collectionDef->type != _wall_collection){
                continue;
            }
            collection_header* header = get_collection_header(i);
            if(header == NULL || header->collection == NULL){
                continue;
            }
            if(header->collection->type != _wall_collection){
                continue;
            }
            
            int clutNum = header->collection->clut_count;
            int bmpNum = header->collection->bitmap_count;
            bool invalid = false;
            if(bmpNum < 10){
                invalid = true;
            }
            for(int clut = 0; clut < clutNum; clut ++){
                for(int index = 0; index < bmpNum; index ++){
                    wxImage img;
                    if(invalid){
                        img.Create(100,100);
                    }else{
                        wxGetApp().getYXShapesImage(&img, i, clut, index, illumination);
                    }
                    textureMap[i][clut][index] = img;
                }
            }
        }
        this->textureDialog.Create(this, wxID_ANY);
	}

    //セットアップ
	this->updateMapItems();
    //初期化
    wxGetApp().isChanged = false;
}
MapEditorMainFrame::~MapEditorMainFrame()
{
    this->toolDialog.Close();
}

void MapEditorMainFrame::createDoubleBuffer()
{
    wxSize size = wxFrame::GetSize();
    this->doubleBufferingBitmap = wxBitmap(size.GetWidth(), size.GetHeight());
//    this->doubleBufferingDC.SelectObject(wxNullBitmap);
//    this->doubleBufferingDC.SelectObject(this->doubleBufferingBitmap);
//    PrepareDC(this->doubleBufferingDC);
}

void MapEditorMainFrame::setupMenus()
{
    //メニューの追加

    //ファイルメニュー <en> file menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_New, _T("&New"), _T("create new map"));
    menuFile->Append(ID_Open, _T("&Open"), _T("open map file"));
    menuFile->Append(ID_Save, _T("&Save"), _T("save current map"));
    menuFile->Append(ID_SaveAs, _T("SaveAs ..."), _T("save current map as another name"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Print, _T("&Print"), _T("print current level"));
    menuFile->Append(ID_PrintPreview, _T("Print Preview"), _T("print preview"));
    menuFile->Append(ID_PrintSetup, _T("Print Setup ..."), _T("print setup"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Merge, _T("&Merge ..."), _T("merge map"));
	menuFile->Append(ID_SavePhysicsFile, _T("Save Physics File As..."), _T("extract physics file"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Quit, _T("E&xit"), _T("exit program"));

    //編集メニュー <en> Edit menu
    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(ID_Undo, _T("&Undo"), _T("undo operation"));
    menuEdit->Append(ID_Cut, _T("C&ut"), _T("cut map items"));
    menuEdit->Append(ID_Copy, _T("&Copy"), _T("copy map items"));
    menuEdit->Append(ID_Paste, _T("&Paste"), _T("paste map items on"));
	menuEdit->Append(ID_Delete, _T("&Delete select items"), _T("kill em all"));
    menuEdit->Append(ID_Preference, _T("P&references"), _T("preferences = setup = configure"));

    //show
    wxMenu *menuShow = new wxMenu;
    menuShow->Append(ID_ToolDialog, _T("&ToolDialog"), _T("tool pallet dalog"));
    menuShow->Append(ID_ZoomIn, _T("Zoom &In"), _T("zoom in"));
    menuShow->Append(ID_ZoomOut, _T("Zoom &Out"), _T("zoom out"));
    menuShow->Append(ID_ZoomDefault, _T("Zoom &Default"), _T("set zoom default"));
    menuShow->Append(ID_MoveToCenter, _T("&Move To Center"), _T("move view to center"));
    menuShow->Append(ID_HeightDialog, _T("&Height Dialog"), _T("show/hide hegiht dialog"));

    //mode
    wxMenu *menuMode = new wxMenu;
    menuMode->Append(ID_DrawPolygonMode, _T("&Draw Polygon Mode"), _T("draw polygons mode = edit mode"));
    menuMode->Append(ID_VisualMode, _T("&Visual Mode"), _T("visual mode"));
    menuMode->Append(ID_PolygonTypeMode, _T("&Polygon Type Mode"), _T("modify polygon type mode"));

    wxMenu *subMenuModeHeight = new wxMenu;
    subMenuModeHeight->Append(ID_FloorHeightMode, _T("Floor Height Mode"), _T("floor height"));
    subMenuModeHeight->Append(ID_CeilingHeightMode, _T("Ceiling Height Mode"), _T("ceiling height"));
    menuMode->AppendSubMenu(subMenuModeHeight, _T("&Height"), _T("height"));

    wxMenu *subMenuModeLight = new wxMenu;
    subMenuModeLight->Append(ID_FloorLightMode, _T("Floor Light Mode"), _T("floor light"));
    subMenuModeLight->Append(ID_CeilingLightMode, _T("Ceiling Light Mode"), _T("ceiling light"));
    menuMode->AppendSubMenu(subMenuModeLight, _T("&Light"), _T("light"));

    wxMenu *subMenuModeTexture = new wxMenu;
    subMenuModeTexture->Append(ID_FloorTextureMode, _T("Floor Texture Mode"), _T("floor texture"));
    subMenuModeTexture->Append(ID_CeilingTextureMode, _T("Ceiling Texture Mode"), _T("ceiling texture"));
    menuMode->AppendSubMenu(subMenuModeTexture, _T("&Texture"), _T("texture"));

    menuMode->Append(ID_MediaMode, _T("&Media Mode"), _T("media"));

    //special
    wxMenu *menuSpecial = new wxMenu;
    menuSpecial->Append(ID_JumpLevel, _T("&Jump to other Level ..."), _T("jump to other level"));
    menuSpecial->Append(ID_LevelInfo, _T("&Level information ..."), _T("show current level's information/settings"));
    menuSpecial->Append(ID_ObjectPlacement, _T("Object &Placement ..."), _T("object placement"));
    menuSpecial->Append(ID_TerminalViewer, _T("&Terminal Viewer ..."), _T("terminal viewer"));

    //ヘルプメニュー
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(ID_About, _T("&About..."), _T("about this program"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(menuEdit, _T("&Edit"));
    menuBar->Append(menuShow, _T("&Show"));
    menuBar->Append(menuMode, _T("&Mode"));
    menuBar->Append(menuSpecial, _T("&Special! 8)"));
    menuBar->Append(menuHelp, _T("&Help"));

    SetMenuBar(menuBar);

    wxGetApp().linePopupMenu.SetTitle(_T("line menu"));
    wxGetApp().linePopupMenu.Append(ID_LineProp, _T("Properties..."));
    wxGetApp().linePopupMenu.Append(ID_ClockwiseSideProp, _T("Clockwise side prop..."));
    wxGetApp().linePopupMenu.Append(ID_CounterclockwiseSideProp, _T("Counterclockwise side prop..."));

    wxGetApp().pointPopupMenu.SetTitle(_T("point menu"));
    wxGetApp().pointPopupMenu.Append(ID_PointProp, _T("Properties..."));

    wxGetApp().polygonPopupMenu.SetTitle(_T("polygon menu"));
    wxGetApp().polygonPopupMenu.Append(ID_PolygonProp, _T("Properties..."));
    wxGetApp().polygonPopupMenu.Append(ID_SetVisualModePlayerStartPosition, _T("Set visual mode start position"));
}


void MapEditorMainFrame::OnQuit(wxCommandEvent& event)
{
	wxCloseEvent dummy;
    OnClose(dummy);
}

void MapEditorMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_T("This program is MapEditorOne for AlephOne!"),
        _T("about this..."), wxOK | wxICON_INFORMATION, this);
}



//サイズ変更
void MapEditorMainFrame::OnSize(wxSizeEvent& ev)
{
    this->createDoubleBuffer();
}

void MapEditorMainFrame::OnEraseBackground(wxEraseEvent& ev)
{

}

/**
    マップ描画用ブラシ・ペンのセットアップ
    @param setting カラー設定データ <en> setting data for color
*/
void MapEditorMainFrame::setupPenAndBrush(ColorSettings* setting)
{
    //背景色
    wxColor col = wxColor(wxGetApp().setting.getColorSetting()->colors[ColorType::Background][0],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Background][1],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Background][2]);
    this->backgroundPen = wxPen(col);
    this->backgroundBrush = wxBrush(col);

    //グリッド色
    wxColor edgeCol(wxGetApp().setting.getColorSetting()->colors[ColorType::GridLine][0],
        wxGetApp().setting.getColorSetting()->colors[ColorType::GridLine][1],
        wxGetApp().setting.getColorSetting()->colors[ColorType::GridLine][2]);
    this->gridPen = wxPen(edgeCol);
    this->gridLargePen = wxPen(edgeCol, LARGE_PEN_SIZE);

    //ポリゴンタイプカラー
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        this->polyTypeBrushes[i].SetColour(
            wxGetApp().polygonTypeColors[i][0],
            wxGetApp().polygonTypeColors[i][1],
            wxGetApp().polygonTypeColors[i][2]);
    }

    //ポリゴン選択ネットブラシ
    wxImage bmp;
    wxGetApp().loadBitmap(POLYGON_SELECT_STLIPPLE_BITMAP_FILE_PATH, &bmp);
    bmp.SetMaskColour(255,255,255);
    this->polySelNetBrush = wxBrush(bmp);

    //ダメポリゴンブラシ
    this->invalidBrush.SetColour(wxColor(255,0,0));

    //選択ペン
    this->selectedLinePen.SetColour(wxColor(255,0,0));
    this->selectedLinePen.SetWidth(2);

    //線
    this->linePen.SetColour(
        wxGetApp().setting.getColorSetting()->colors[ColorType::Lines][0],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Lines][1],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Lines][2]);

    //点
    wxColor pcol(
        wxGetApp().setting.getColorSetting()->colors[ColorType::Points][0],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Points][1],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Points][2]);
    this->pointPen.SetColour(pcol);
    this->pointBrush.SetColour(pcol);

    //同じ高さ線の色
    sameHeightLinePen.SetColour(
        wxGetApp().setting.getColorSetting()->colors[ColorType::SameHeightLines][0],
        wxGetApp().setting.getColorSetting()->colors[ColorType::SameHeightLines][1],
        wxGetApp().setting.getColorSetting()->colors[ColorType::SameHeightLines][2]);
    //段差のある線の色
    stairLinePen.SetColour(
        wxGetApp().setting.getColorSetting()->colors[ColorType::StairLines][0],
        wxGetApp().setting.getColorSetting()->colors[ColorType::StairLines][1],
        wxGetApp().setting.getColorSetting()->colors[ColorType::StairLines][2]);

    //ポリゴン
    this->polyBrush.SetColour(
        wxGetApp().setting.getColorSetting()->colors[ColorType::Polygons][0],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Polygons][1],
        wxGetApp().setting.getColorSetting()->colors[ColorType::Polygons][2]);

    //オブジェクトカラー
    //プレイヤーペン(yellow)
    this->playerPen.SetColour(wxColor(255,255,0));
    this->playerBrush.SetColour(wxColor(255,255,0));
    //選択プレイヤー
    this->selectedPlayerPen.SetColour(wxColor(255,0,255));
    this->selectedPlayerBrush.SetColour(wxColor(255,0,255));
    //味方
    this->allyPen.SetColour(wxColor(0,0,255));
    this->allyBrush.SetColour(wxColor(0,0,255));
    //選択味方
    this->selectedAllyPen.SetColour(wxColor(100,0,255));
    this->selectedAllyBrush.SetColour(wxColor(100,0,255));
    //モンスター
    this->monsterPen.SetColour(wxColor(255,0,0));
    this->monsterBrush.SetColour(wxColor(255,0,0));
    //選択モンスター
    this->selectedMonsterPen.SetColour(wxColor(0,255,0));
    this->selectedMonsterBrush.SetColour(wxColor(0,255,0));

    //選択中
    int style = wxDOT;
    this->selectingPen = wxPen(wxColor(255,0,0), 1, style);
}

/**
    アイコン用のビットマップファイルを読み込みます
*/
void MapEditorMainFrame::loadIconBitmaps(const char* baseDirPath)
{
    //アイコンビットマップとファイル名、そしてアイテムIDとの対応データをファイルから読み込みます
    const int NUMBER_OF_MAP_ICON_FILES = NUMBER_OF_DEFINED_ITEMS +
        NUMBER_OF_MAP_ICONS;
    hpl::aleph::Information mapIconInfo[NUMBER_OF_MAP_ICON_FILES];

    //ファイル名作成
    char buf[BUF_MAX];
    sprintf(buf, "%s%s", baseDirPath, MAP_ICONS_IMAGE_NAME_LIST_FILE_NAME);
    hpl::aleph::loadInformation(buf, NUMBER_OF_MAP_ICON_FILES, mapIconInfo);

    for(int i = 0; i < 2 * NUMBER_OF_DEFINED_ITEMS + 2 * NUMBER_OF_MAP_ICONS; i ++){
        std::string path = std::string(baseDirPath) + std::string(MAP_ICONS_DIR_NAME);
        const int HILIGHTED_OFFSET = NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MAP_ICONS;

        int index = i;
        if(i >= HILIGHTED_OFFSET){
            //選択（ハイライト状態）
            path += std::string(HILIGHTED_ICONS_DIR_NAME);
            index -= HILIGHTED_OFFSET;
        }
        path += mapIconInfo[index].jname;

        //TODO ビットマップファイル読み込み
        if(i < HILIGHTED_OFFSET){
            //通常状態
            if(index < NUMBER_OF_DEFINED_ITEMS){
                //アイテム
                wxGetApp().loadBitmap(path.c_str(), &this->itemBitmaps[index]);
                this->itemBitmaps[index].SetMaskColour(255,255,255);
            }else{
                index -= NUMBER_OF_DEFINED_ITEMS;
                //マップアイコン
                wxGetApp().loadBitmap(path.c_str(), &this->mapItemBitmaps[index]);
                this->mapItemBitmaps[index].SetMaskColour(255,255,255);
            }
        }else{
            //選択＝ハイライト状態
            if(index < NUMBER_OF_DEFINED_ITEMS){
                //アイテム
                wxGetApp().loadBitmap(path.c_str(), &this->hilightedItemBitmaps[index]);
                this->hilightedItemBitmaps[index].SetMaskColour(255,255,255);
            }else{
                index -= NUMBER_OF_DEFINED_ITEMS;
                //マップアイコン
                wxGetApp().loadBitmap(path.c_str(), &this->hilightedMapItemBitmaps[index]);
                this->hilightedMapItemBitmaps[index].SetMaskColour(255,255,255);
            }
        }
    }
	wxGetApp().loadImage(START_POINT_IMAGE_FILE_PATH, &this->visualModeStartPositionImage,
		255,255,255);
}
/**
    編集モードメニューのチェックを全てはずします
*/
void MapEditorMainFrame::uncheckModesOnMenu()
{
    //TODO menu
    //ドローモード
    wxMenuBar* menuBar = wxFrame::GetMenuBar();
    //モードメニュー
    wxMenu* menu = menuBar->GetMenu(3);
    //アイテム取得
    wxMenuItemList lst = menu->GetMenuItems();
//    lst.
}

/**
    新しいモードに切り替えます
*/
void MapEditorMainFrame::changeEditMode(int mode)
{
    //モードのチェックをすべてはずします
    this->uncheckModesOnMenu();

    //チェックをつけます
    //TODO 
    if(mode != EditModeType::EM_DRAW){
        //選択状態を解除
        wxGetApp().selectData.clear();

        //線・点・プラットフォーム・オブジェクト
        //以上のプロパティダイアログを消します
        //this->linePropDialog.Show(false);
//        this->pointPropDialog.Show(false);
        this->objPropDialog.Show(false);

		//矢印ツールに戻す
		wxGetApp().getEventManager()->setToolType(ToolType::TI_ARROW);
    }
    if(mode != EditModeType::EM_FLOOR_TEXTURE &&
        mode != EditModeType::EM_CEILING_TEXTURE)
    {
        //テクスチャモード以外
        //hide texture palette
        this->textureDialog.Show(false);
    }

    if(mode != EditModeType::EM_POLYGON_TYPE){
        //ポリゴンタイプダイアログを消す
        this->polyTypeDialog.Show(false);
    }
    if(mode != EditModeType::EM_CEILING_HEIGHT &&
        mode != EditModeType::EM_FLOOR_HEIGHT)
    {
        //高さウインドウを消す
        this->heightPaletteDialog.Show(false);
    }
    if(mode != EditModeType::EM_CEILING_LIGHT &&
        mode != EditModeType::EM_FLOOR_LIGHT)
    {
        this->lightPaletteDialog.Show(false);
    }
    if(mode != EditModeType::EM_MEDIA)
    {
		this->mediaPaletteDialog.Show(false);
    }
    if(mode != EditModeType::EM_SOUND)
    {
		this->soundPaletteDialog.Show(false);
    }

	wxGetApp().getEventManager()->setEditModeType(mode);

    Refresh();
}

/**
	グリッドにあわせた座標を取得します
*/
world_point2d MapEditorMainFrame::getGridedWorldPoint(world_point2d src)
{
	if(wxGetApp().setting.getFlag(IS_FIT_TO_GRID)){
		int grid = wxGetApp().getViewGridManager()->getGridInterval();
		wxASSERT(grid > 0);
		src.x = grid * (int)(src.x / grid + (src.x > 0?1:0));
		src.y = grid * (int)(src.y / grid + (src.y > 0?1:0));
	}
	return src;
}
void MapEditorMainFrame::getGridedViewPoint(int vpointSrc[2], int vpointDest[2])
{
	world_point2d wpointSrc = wxGetApp().getWorldPointFromViewPoint(
		vpointSrc[0], vpointSrc[1]);
	world_point2d wpointDest = this->getGridedWorldPoint(wpointSrc);
	wxGetApp().getViewPointFromWorldPoint(
		wpointDest, vpointDest);
}
void MapEditorMainFrame::getGridedViewPoint(int vx, int vy, int vpointDest[2])
{
	int vpointSrc[2] = {vx, vy};
	this->getGridedViewPoint(vpointSrc, vpointDest);
}
