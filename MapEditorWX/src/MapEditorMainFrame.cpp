#include "MapEditorMainFrame.h"
/*const int ZOOM_DIVISION_STEP = 10;
const int ZOOM_DIVISION_MAX = 200;
const int ZOOM_DIVISION_MIN = 1;
const int ZOOM_DIVISION_DEFAULT = 100;
const int OFFSET_X_WORLD = 32768;
const int OFFSET_Y_WORLD = 32768;
const int NUMBER_OF_GLID = 5;
*/


//点とクリック地点の距離がこれ以下であれば選択する。
//リスト順に探索する
//const int POINT_DISTANCE_EPSILON = 5;

BEGIN_EVENT_TABLE(MapEditorMainFrame, wxFrame)
    EVT_MENU(ID_Quit, MapEditorMainFrame::OnQuit)
    EVT_MENU(ID_About, MapEditorMainFrame::OnAbout)
    EVT_PAINT(MapEditorMainFrame::OnPaint)
    EVT_MENU(ID_Open, MapEditorMainFrame::OnOpen)
    EVT_LEFT_DOWN(MapEditorMainFrame::OnLeftDown)
    EVT_RIGHT_DOWN(MapEditorMainFrame::OnRightDown)
    EVT_MOTION(MapEditorMainFrame::OnMotion)
    EVT_MOUSEWHEEL(MapEditorMainFrame::OnMouseWheel)
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
}

void MapEditorMainFrame::setupMenus()
{
    //メニューの追加
    //ファイルメニュー
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Open, _T("&Open"), _T("open map file"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Quit, _T("E&xit"), _T("exit program"));

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(ID_About, _T("&About..."), _T("about this program"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _T("&File"));
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
    wxPaintDC dc(this);
    PrepareDC(dc);
    dc.Clear();

    //dc.DrawLine(10,10,100,20);
    
    hpl::aleph::view::HPLViewGridManager* mgr = wxGetApp().getViewGridManager();
    int DIV = mgr->getZoomDivision();
    int voffset[2];
    mgr->getOffset(voffset);
    int OFFSET_X_VIEW = voffset[0];
    int OFFSET_Y_VIEW = voffset[1];

    //背景描画
    this->drawBackground(&dc);
    
    //ポリゴン
    {
        dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(*wxLIGHT_GREY_BRUSH);

        wxPoint points[8];
        for(int i = 0; i < (int)PolygonList.size(); i ++){
            struct polygon_data* polygon = &PolygonList[i];
            int type = polygon->type;
            int flags = polygon->flags;
            int vertexCount = polygon->vertex_count;
            int vpoint[2];
            for(int j = 0; j < vertexCount; j ++){
                wxGetApp().getViewPointFromWorldPoint(EndpointList[polygon->endpoint_indexes[j]].vertex,
                    vpoint);
                points[j].x = vpoint[0];
                points[j].y = vpoint[1];
            }
            dc.DrawPolygon(vertexCount, points);
        }
    }

    //ライン
    {
        dc.SetPen(*wxBLACK_PEN);
        for(int i = 0; i < (int)LineList.size(); i ++){
            line_data* line = &LineList[i];
            endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
            endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
            int x0 = (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
            int y0 = (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
            int x1 = (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
            int y1 = (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
            dc.DrawLine(x0, y0, x1, y1);
        }
    }

    //ポイント
    {
        wxBrush yellowBrush = wxBrush(wxColor(255,255,0));
        wxPen bluePen = wxPen(wxColor(0,0,255));
        //wxPen yellowPen = wxPen(wxColor(255,255,0));
        dc.SetBrush(yellowBrush);
        dc.SetPen(bluePen);
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
            dc.DrawRectangle(left, top, right - left, bottom - top);
        }
    }
    
}

void MapEditorMainFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
    //file dialog open
    wxFileDialog fileDialog(this, _T("Choose a file"),
        _T("."), _T(""), _T("*.*"));

    if(fileDialog.ShowModal() == wxID_OK){
        wxString path = fileDialog.GetPath();

        //タイトル
        SetTitle(path);
        
        FileSpecifier mapFile = FileSpecifier(path.mb_str());

        //set map file
        set_map_file(mapFile);

        wxGetApp().editLevelIndex = 0;
        build_trig_tables();
        //allocate
        if(dynamic_world == NULL){
            allocate_map_memory();
        }
        //Level1を読み込み
        bool check = load_level_from_map(wxGetApp().editLevelIndex);
        if(!check){
            wxMessageBox(_T("failed"));
        }

        //インデックス
        /*wxGetApp().levelNameList.clear();
        {
            short index = 0;
            struct entry_point ep;
            int type = 3;
            char cstr[256];
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d", ep.level_number);
                wxGetApp().levelNameList.push_back(string(cstr) + string(ep.level_name));
            }
        }*/
        //ズーム・オフセットを初期化
        
        wxGetApp().getViewGridManager()->zoomReset();
        wxGetApp().getViewGridManager()->setOffset(0,0);
        //再描画
        Refresh();
    }
}

