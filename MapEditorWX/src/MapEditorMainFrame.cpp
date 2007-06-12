#include "MapEditorMainFrame.h"

//大きいペンのサイズ
const int LARGE_PEN_SIZE = 2;

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
    EVT_MENU(ID_NewLevel, MapEditorMainFrame::OnNewLevel)
    EVT_MENU(ID_Open, MapEditorMainFrame::OnOpen)
    EVT_MENU(ID_Save, MapEditorMainFrame::OnSave)
    EVT_MENU(ID_SaveAs, MapEditorMainFrame::OnSaveAs)

    //edit menu
    EVT_MENU(ID_Undo, MapEditorMainFrame::OnUndo)
    EVT_MENU(ID_Cut, MapEditorMainFrame::OnCut)
    EVT_MENU(ID_Copy, MapEditorMainFrame::OnCopy)
    EVT_MENU(ID_Paste, MapEditorMainFrame::OnPaste)
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

    EVT_PAINT(MapEditorMainFrame::OnPaint)
    EVT_LEFT_DOWN(MapEditorMainFrame::OnLeftDown)
    EVT_RIGHT_DOWN(MapEditorMainFrame::OnRightDown)
    EVT_MOTION(MapEditorMainFrame::OnMotion)
    EVT_MOUSEWHEEL(MapEditorMainFrame::OnMouseWheel)
    EVT_SIZE(MapEditorMainFrame::OnSize)
    EVT_ERASE_BACKGROUND(MapEditorMainFrame::OnEraseBackground)
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

    //ダイアログ
    //TODO dlg
    this->toolDialog.Create(this, -1, wxT("ToolDialog"));
    this->toolDialog.Show();

    //ペン・ブラシのセットアップ
    this->setupPenAndBrush(wxGetApp().setting.getColorSetting());

    //ダブルバッファリングのバッファ用意
//    this->createDoubleBuffer();
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
    menuFile->Append(ID_NewLevel, _T("&NewLevel"), _T("insert new level"));
    menuFile->Append(ID_Open, _T("&Open"), _T("open map file"));
    menuFile->Append(ID_Save, _T("&Save"), _T("save current map"));
    menuFile->Append(ID_SaveAs, _T("SaveAs ..."), _T("save current map as another name"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Print, _T("&Print"), _T("print current level"));
    menuFile->Append(ID_PrintPreview, _T("Print Preview"), _T("print preview"));
    menuFile->Append(ID_PrintSetup, _T("Print Setup ..."), _T("print setup"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Quit, _T("E&xit"), _T("exit program"));

    //編集メニュー <en> Edit menu
    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(ID_Undo, _T("&Undo"), _T("undo operation"));
    menuEdit->Append(ID_Cut, _T("C&ut"), _T("cut map items"));
    menuEdit->Append(ID_Copy, _T("&Copy"), _T("copy map items"));
    menuEdit->Append(ID_Paste, _T("&Paste"), _T("paste map items on"));
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
    menuBar->Append(menuSpecial, _T("&Special! (^o^)/"));
    menuBar->Append(menuHelp, _T("&Help"));

    SetMenuBar(menuBar);
}


void MapEditorMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MapEditorMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_T("This program is MapEditorOne for AlephOne!"),
        _T("about this..."), wxOK | wxICON_INFORMATION, this);
}

/**
    描画
*/
void MapEditorMainFrame::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxSize size = wxFrame::GetSize();
    if(!wxWindow::IsExposed(0,0,size.GetWidth(), size.GetHeight())){
        return;
    }
    wxBufferedPaintDC dc(this, this->doubleBufferingBitmap);
    PrepareDC(dc);
    //dc.Clear();
//    wxRegionIerator region(GetUpdateRegion());
//    while(
    //dc.DrawLine(10,10,100,20);
    
    wxDC* drawDC = &dc;//&this->doubleBufferingDC;

    hpl::aleph::view::HPLViewGridManager* mgr = wxGetApp().getViewGridManager();
    int DIV = mgr->getZoomDivision();
    int voffset[2];
    mgr->getOffset(voffset);
    int OFFSET_X_VIEW = voffset[0];
    int OFFSET_Y_VIEW = voffset[1];

    //背景描画
    this->drawBackground(drawDC);
    
    //ポリゴン
    this->drawPolygons(drawDC);

    //ライン
    this->drawLines(drawDC);

    //ポイント
    {
        wxBrush yellowBrush = wxBrush(wxColor(255,255,0));
        wxPen bluePen = wxPen(wxColor(0,0,255));
        //wxPen yellowPen = wxPen(wxColor(255,255,0));
        drawDC->SetBrush(yellowBrush);
        drawDC->SetPen(bluePen);
        for(int i = 0; i < (int)EndpointList.size(); i ++){
            endpoint_data* point = &EndpointList[i];
            int x = point->vertex.x;
            int y = point->vertex.y;
            int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
            int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;
            int SIZE = 1;
            int left = drawX - SIZE;
            int right = drawX + SIZE;
            int top = drawY - SIZE;
            int bottom = drawY + SIZE;

            //点を打つ
            drawDC->DrawRectangle(left, top, right - left, bottom - top);
        }
    }
    
    //アノテーション
    this->drawAnnotations(drawDC);

    //バッファから画面へコピー
    dc.Blit(wxPoint(0,0), size,
        drawDC,
        wxPoint(0,0));
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
    wxColor col = wxColor(wxGetApp().setting.getColorSetting()->background[0],
        wxGetApp().setting.getColorSetting()->background[1],
        wxGetApp().setting.getColorSetting()->background[2]);
    this->backgroundPen = wxPen(col);
    this->backgroundBrush = wxBrush(col);

    //グリッド色
    wxColor edgeCol(wxGetApp().setting.getColorSetting()->gridLine[0],
        wxGetApp().setting.getColorSetting()->gridLine[1],
        wxGetApp().setting.getColorSetting()->gridLine[2]);
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
    wxBitmap bmp;
    wxGetApp().loadBitmap(POLYGON_SELECT_STLIPPLE_BITMAP_FILE_PATH, &bmp);
    this->polySelNetBrush = wxBrush(bmp);

}

