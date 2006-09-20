// MapEditorSDIView.cpp : CMapEditorSDIView クラスの実装
//

#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int SELECT_GROUP_DISTANCE_THRESHOLD = 2;


// CMapEditorSDIView

IMPLEMENT_DYNCREATE(CMapEditorSDIView, CView)

BEGIN_MESSAGE_MAP(CMapEditorSDIView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(ID_FILE_OPEN, &CMapEditorSDIView::OnFileOpen)
    ON_COMMAND(ID_FILE_SAVE, &CMapEditorSDIView::OnFileSave)
    ON_COMMAND(ID_32776, On32776)
    ON_COMMAND(ID_ZOOM_IN, &CMapEditorSDIView::OnZoomIn)
    ON_COMMAND(ID_ZOOM_OUT, &CMapEditorSDIView::OnZoomOut)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_COMMAND(ID_ITEM_CENTERING, &CMapEditorSDIView::OnItemCentering)
    ON_COMMAND(ID_ITEM_ZOOM_DEFAULT, &CMapEditorSDIView::OnItemZoomDefault)
    ON_WM_MOUSEWHEEL()
    ON_WM_UPDATEUISTATE()
    ON_COMMAND(ID_32784, &CMapEditorSDIView::On32784)
    ON_COMMAND(ID_32787, &CMapEditorSDIView::On32787)
    ON_COMMAND(ID_32789, &CMapEditorSDIView::On32789)
    ON_COMMAND(ID_32786, &CMapEditorSDIView::On32786)
    ON_COMMAND(ID_32790, &CMapEditorSDIView::On32790)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_COMMAND(ID_FILE_NEW, &CMapEditorSDIView::OnFileNew)
    ON_COMMAND(ID_32796, &CMapEditorSDIView::On32796)
    ON_COMMAND(ID_32788, On32788)
END_MESSAGE_MAP()

// CMapEditorSDIView コンストラクション/デストラクション

CMapEditorSDIView::CMapEditorSDIView()
{
	// TODO: 構築コードをここに追加します。
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。
    
}

CMapEditorSDIView::~CMapEditorSDIView()
{
    //delete theApp.objectPropertyDialog;
}

BOOL CMapEditorSDIView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

// CMapEditorSDIView 描画

void CMapEditorSDIView::OnDraw(CDC* pDC)
{
	CMapEditorSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
    CPen redSmallPen, blackSmallPen, yellowSmallPen, graySmallPen,
        redMidiumPen, grayMidiumPen, blueSmallPen, selectPen;
    redSmallPen.CreatePen(PS_SOLID, 1, RGB(255,0,0));
    blackSmallPen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
    yellowSmallPen.CreatePen(PS_SOLID, 1, RGB(255,255,0));
    redMidiumPen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
    blueSmallPen.CreatePen(PS_SOLID, 1, RGB(0,0,255));
    graySmallPen.CreatePen(PS_SOLID, 1, RGB(200,200,200));
    grayMidiumPen.CreatePen(PS_SOLID, 2, RGB(200,200,200));
    selectPen.CreatePen(PS_DASH, 1, RGB(255,0,0));

    CBrush grayBrush, redBrush, yellowBrush, nullBrush,
        netBrush, blueBrush;
    CBrush polygonBrushes[NUMBER_OF_POLYGON_TYPE];
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        polygonBrushes[i].CreateSolidBrush(theApp.polygonTypeColor[i]);
    }
    grayBrush.CreateSolidBrush(RGB(100, 100, 100));
    redBrush.CreateSolidBrush(RGB(255,0,0));
    yellowBrush.CreateSolidBrush(RGB(255,255,0));
    blueBrush.CreateSolidBrush(RGB(0,0,255));
    LOGBRUSH logBrush = {
        BS_NULL, 0, 0};
    nullBrush.CreateBrushIndirect(&logBrush);
    CBitmap bmp;
    bmp.LoadBitmap(IDB_BITMAP_PATTERN_SELECTED_POLYGON);
    netBrush.CreatePatternBrush(&bmp);
    bmp.DeleteObject();

    CPen* oldPen = pDC->SelectObject(&blackSmallPen);
    CBrush* oldBrush = pDC->SelectObject(&grayBrush);
    
    //ビットマップ読み込み
    /*CBitmap monsterBitmap, itemBitmap, scenaryBitmap, goalBitmap;
    CBitmap soundBitmap;
    monsterBitmap.LoadBitmapW(IDB_BITMAP1);
    itemBitmap.LoadBitmapW(IDB_BITMAP_ITEM);
    scenaryBitmap.LoadBitmapW(IDB_BITMAP_SCENARY);
    goalBitmap.LoadBitmapW(IDB_BITMAP_GOAL);
    soundBitmap.LoadBitmapW(IDB_BITMAP_SOUND);
    */
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* oldBitmap = memDC.GetCurrentBitmap();


    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;
    int ICON_SIZE = 16;

    CDC *cdc = &theApp.doubleBufferDC;
    cdc->SetBkColor(RGB(200,200,200));
    //CDC doubleBufferDC;
    //doubleBufferDC.CreateCompatibleDC(pDC);

    CRect winRect;
    GetClientRect(&winRect);

    //背景
    {
        cdc->SelectObject(&blackSmallPen);
        cdc->SelectObject(&grayBrush);
        cdc->Rectangle(&winRect);
    }

    //範囲
    {
        cdc->SelectObject(blackSmallPen);
        cdc->SelectObject(oldBrush);
        RECT rect;//, winRect;
        //GetClientRect(&winRect);
        rect.left = OFFSET_X_VIEW;
        rect.top = OFFSET_Y_VIEW;
        rect.right = rect.left + OFFSET_X_WORLD * 2 / DIV;
        rect.bottom = rect.top + OFFSET_Y_WORLD * 2 / DIV;
        cdc->Rectangle(&rect);
    }
    /*pDC->BitBlt(0,0,winRect.Width(), winRect.Height(),
        &doubleBufferDC, 0,0, SRCCOPY);
    doubleBufferDC.DeleteDC();
*/

    //グリッド
    {
        cdc->SelectObject(graySmallPen);
        for(int i = OFFSET_X_WORLD / DIV; i <= OFFSET_X_WORLD * 2 / DIV; i += theApp.gridIntervals[theApp.nowGridInterval] / DIV){
            if( i == OFFSET_X_WORLD / DIV){
                cdc->SelectObject(grayMidiumPen);
            }else{
                cdc->SelectObject(graySmallPen);
            }
            int x0 = OFFSET_X_VIEW + i;
            int y0 = OFFSET_Y_VIEW + i;

            cdc->MoveTo(x0, OFFSET_Y_VIEW);
            cdc->LineTo(x0, OFFSET_Y_VIEW + OFFSET_Y_WORLD * 2 / DIV);
            cdc->MoveTo(OFFSET_X_VIEW, y0);
            cdc->LineTo(OFFSET_X_VIEW + OFFSET_X_WORLD * 2 / DIV, y0);
        }
        for(int i = OFFSET_X_WORLD / DIV; i >= 0; i -= theApp.gridIntervals[theApp.nowGridInterval] / DIV){
            if( i == OFFSET_X_WORLD / DIV){
                cdc->SelectObject(grayMidiumPen);
            }else{
                cdc->SelectObject(graySmallPen);
            }
            int x0 = OFFSET_X_VIEW + i;
            int y0 = OFFSET_Y_VIEW + i;

            cdc->MoveTo(x0, OFFSET_Y_VIEW);
            cdc->LineTo(x0, OFFSET_Y_VIEW + OFFSET_Y_WORLD * 2 / DIV);
            cdc->MoveTo(OFFSET_X_VIEW, y0);
            cdc->LineTo(OFFSET_X_VIEW + OFFSET_X_WORLD * 2 / DIV, y0);
        }

    }

    //ポリゴン
    //pDC->SelectObject(&grayBrush);
    int fillMode = WINDING;
    SetPolyFillMode(cdc->m_hDC, fillMode);
    POINT points[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        struct polygon_data* polygon = &PolygonList[i];
        int type = polygon->type;
        cdc->SelectObject(&polygonBrushes[type]);
        bool selected = false;
        if(theApp.selectType == _selected_polygon && theApp.selectIndex == i){
            selected = true;
        }
        if(theApp.selectGroupInformation.isSelected()){
            for(int k = 0; k < (int)theApp.selectGroupInformation.polygonIndexList.size(); k ++){
                if(theApp.selectGroupInformation.polygonIndexList[k] == i){
                    selected = true;
                    break;
                }
            }
        }
        if(selected){
            cdc->SelectObject(&netBrush);
        }
        int flags = polygon->flags;
        int vertexCount = polygon->vertex_count;
        for(int j = 0; j < vertexCount; j ++){
            endpoint_data* ep = &EndpointList[polygon->endpoint_indexes[j]];
            points[j].x = (ep->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
            points[j].y = (ep->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
        }
        Polygon(cdc->m_hDC, points, vertexCount);
    }

    //線
    for(int i = 0; i < (int)LineList.size(); i ++){
        cdc->SelectObject(&blackSmallPen);
        line_data* line = &LineList[i];
        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
        int x0 = (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
        int y0 = (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
        int x1 = (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
        int y1 = (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

        //選択中は太い赤線で
        bool selected = false;
        if(theApp.selectType == _selected_line && theApp.selectIndex == i){
            selected = true;
        }
        if(theApp.selectGroupInformation.isSelected()){
            for(int k = 0; k < (int)theApp.selectGroupInformation.lineIndexList.size(); k ++){
                if(theApp.selectGroupInformation.lineIndexList[k] == i){
                    selected = true;
                    break;
                }
            }
        }
        if(selected){
            cdc->SelectObject(&redMidiumPen);
        }

        cdc->MoveTo(x0, y0);
        cdc->LineTo(x1, y1);
    }

    //ポイント
    cdc->SelectObject(&blueSmallPen);
    cdc->SelectObject(&yellowBrush);
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = &EndpointList[i];
        int x = ep->vertex.x;
        int y = ep->vertex.y;
        int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
        int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;
        RECT rect;
        int SIZE = 1;
        rect.left = drawX - SIZE;
        rect.right = drawX + SIZE;
        rect.top = drawY - SIZE;
        rect.bottom = drawY + SIZE;

        //点を打つ
        cdc->SelectObject(&blueSmallPen);
        cdc->SelectObject(&yellowBrush);
        cdc->Rectangle(&rect);

        //選択中はしるしを。
        bool selected = false;
        if(theApp.selectType == _selected_point && theApp.selectIndex == i){
            selected = true;
        }
        if(theApp.selectGroupInformation.isSelected()){
            for(int k = 0; k < (int)theApp.selectGroupInformation.endpointIndexList.size(); k ++){
                if(theApp.selectGroupInformation.endpointIndexList[k] == i){
                    selected = true;
                    break;
                }
            }
        }
        if( selected){
            cdc->SelectObject(&redMidiumPen);
            //cdc->SetBkMode(TRANSPARENT);
            cdc->SelectObject(&nullBrush);
            RECT rect;
            int SIZE = 5;
            rect.left = drawX - SIZE;
            rect.right = rect.left + SIZE * 2;
            rect.top = drawY - SIZE;
            rect.bottom = rect.top + SIZE * 2;
            cdc->Rectangle(&rect);
        }
    }

    //オブジェクト
    cdc->SelectObject(&blackSmallPen);
    SetPolyFillMode(pDC->m_hDC, fillMode);
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        map_object* obj = &(SavedObjectList[i]);
        int type = obj->type;
        int facing = obj->facing;
        int x = obj->location.x;
        int y = obj->location.y;
        int z = obj->location.z;
        int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
        int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;

        //bitmap表示
        int index = -1;
        if(type == _saved_monster || type == _saved_player){
            index = -1;
        }else if(type == _saved_item){
            index = obj->index;
        }else if(type == _saved_object){
            //scenery
            index = NUMBER_OF_DEFINED_ITEMS + MI_Scenery;
        }else if(type == _saved_goal){
            index = NUMBER_OF_DEFINED_ITEMS + MI_Goal;
        }else{
            //sound
            index = NUMBER_OF_DEFINED_ITEMS + MI_Sound;
        }
        if(index >= 0){
            IMAGEINFO info;
            //theApp.mapIconImageList.GetImageInfo(index, &info);
            CBitmap* bitmap = theApp.bitmapList[index];
            BITMAP bmp;
            CSize sz = bitmap->GetBitmap(&bmp);
            sz.cx = bmp.bmWidth;
            sz.cy = bmp.bmHeight;
            //COLORREF clrBk = RGB(221,221,221);
            //COLORREF clrFg = RGB(255,255,255);
            //theApp.mapIconImageList.Draw(cdc,
            //    index, pt, ILD_TRANSPARENT);
            memDC.SelectObject(bitmap);
            ::TransparentBlt(cdc->m_hDC, drawX - sz.cx / 2, drawY - sz.cy / 2,
                sz.cx, sz.cy, memDC.m_hDC,
                0, 0, sz.cx, sz.cy, RGB(221,221,221));

        }

        if(type == _saved_monster || type == _saved_player){
            cdc->SelectObject(blackSmallPen);
            if(type == _saved_monster){
                if(obj->index >= _civilian_crew &&
                    obj->index <= _civilian_security ||
                    obj->index >= _civilian_fusion_crew &&
                    obj->index <= _civilian_fusion_security)
                {
                    //青
                    cdc->SelectObject(&blueBrush);
                }else{
                    //赤
                    cdc->SelectObject(&redBrush);
                }
            }else{
                //プレイヤーは黄色
                cdc->SelectObject(&yellowBrush);
            }
            int facing = obj->facing;
            double degree = (double)facing / (1<<ANGULAR_BITS) * 360.0;

            //三角形を描く
            POINT points[3];
            points[0].x = (LONG)(drawX + 10 * cos(degreeToRadian(degree)));
            points[0].y = (LONG)(drawY + 10 * sin(degreeToRadian(degree)));
            points[1].x = (LONG)(drawX + 5 * cos(degreeToRadian(degree + 120)));
            points[1].y = (LONG)(drawY + 5 * sin(degreeToRadian(degree + 120)));
            points[2].x = (LONG)(drawX + 5 * cos(degreeToRadian(degree - 120)));
            points[2].y = (LONG)(drawY + 5 * sin(degreeToRadian(degree - 120)));

            cdc->Polygon(points, 3);
        }

        cdc->SetBkMode(TRANSPARENT);
        //選択中はしるしを。
        if(theApp.selectType == _selected_object){
            if( theApp.selectIndex == i){
                cdc->SelectObject(&redMidiumPen);
                cdc->SelectObject(&nullBrush);
                RECT rect;
                int SIZE = 10;
                rect.left = drawX - SIZE;
                rect.right = rect.left + SIZE * 2;
                rect.top = drawY - SIZE;
                rect.bottom = rect.top + SIZE * 2;
                cdc->Rectangle(&rect);
            }
        }

    }

    //アノテーション（マップに表示される文字）の描画
    cdc->SetTextColor(RGB(0,0,0));
    for(int i = 0; i < (int)MapAnnotationList.size(); i ++){
        map_annotation *annotation = &MapAnnotationList[i];
        int x = annotation->location.x;
        int y = annotation->location.y;
        int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
        int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;
        CString msg(annotation->text);
        RECT clientRect;
        GetClientRect(&clientRect);
        cdc->TextOut(drawX, drawY, msg, msg.GetLength());
    }

    //選択範囲
    if(theApp.isSelectingGroup){
        bool selecting = true;
        /*if(!isNearbyPoints(theApp.selectStartPoint.x, theApp.selectStartPoint.y,
            theApp.nowMousePoint.x, theApp.nowMousePoint.y, SELECT_GROUP_DISTANCE_THRESHOLD))
        {
            selecting = true;
        }*/
        if(selecting){
            cdc->SelectObject(&nullBrush);
            cdc->SelectObject(&selectPen);

            cdc->Rectangle(theApp.selectStartPoint.x, theApp.selectStartPoint.y,
                theApp.nowMousePoint.x, theApp.nowMousePoint.y);
        }
    }

    //裏画面をメインへ転送
    pDC->BitBlt(0,0,winRect.Width(), winRect.Height(), 
        cdc, 0, 0, SRCCOPY);

    cdc->SelectObject(&oldPen);
    cdc->SelectObject(&oldBrush);

    redSmallPen.DeleteObject();
    blackSmallPen.DeleteObject();
    yellowSmallPen.DeleteObject();
    redMidiumPen.DeleteObject();
    graySmallPen.DeleteObject();
    grayMidiumPen.DeleteObject();
    blueSmallPen.DeleteObject();
    selectPen.DeleteObject();

    grayBrush.DeleteObject();
    redBrush.DeleteObject();
    yellowBrush.DeleteObject();
    blueBrush.DeleteObject();
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        polygonBrushes[i].DeleteObject();
    }
    nullBrush.DeleteObject();
    netBrush.DeleteObject();

    memDC.SelectObject(oldBitmap);
    memDC.DeleteDC();
/*    
    monsterBitmap.DeleteObject();
    itemBitmap.DeleteObject();
    scenaryBitmap.DeleteObject();
    goalBitmap.DeleteObject();
    soundBitmap.DeleteObject();
  */  
}


// CMapEditorSDIView 印刷

BOOL CMapEditorSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CMapEditorSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMapEditorSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}


// CMapEditorSDIView 診断

#ifdef _DEBUG
void CMapEditorSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CMapEditorSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditorSDIDoc* CMapEditorSDIView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorSDIDoc)));
	return (CMapEditorSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditorSDIView メッセージ ハンドラ

static bool loadMapFromFile(const char* filename){
    FileSpecifier mapFile = FileSpecifier(filename);
    //set map file
    set_map_file(mapFile);
    return true;
}

void CMapEditorSDIView::OnFileOpen()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    	//ファイルオープンダイアログ表示
	CFileDialog dlg(TRUE, L"*.*", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

        //読み込み
        char cstr[256];
        strToChar(filename, cstr);

        //タイトルに設定
        CMapEditorSDIDoc* doc = GetDocument();
        doc->SetTitle(filename);

        
        //マップファイルロード
        loadMapFromFile(cstr);

        //レベル1を読み込んでみる
        {
            theApp.editLevelIndex = 0;
            bool check = load_level_from_map(theApp.editLevelIndex);
            if(!check){
                MessageBox(L"failed");
            }
        }

        /*int s[10];
        for(int i = 0; i < SavedObjectList.size(); i ++){
            int t = SavedObjectList[i].location.x;
            sprintf(cstr, "%d", t);
            //TRACE(CString(cstr)+L"\n");
        }*/
//        char cstr[256];
        //monster_placement_info[0].

        theApp.LevelNameList.RemoveAll();
        
        //int index = 0;
        {
            short index = 0;
            struct entry_point ep;
            int type = 3;
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d,", ep.level_number);
                theApp.LevelNameList.Add(CString(cstr) + CString(ep.level_name));
            }
            /*sprintf(cstr, "%d", theApp.LevelNameList.GetSize());
            MessageBox(CString(cstr));*/
            theApp.selectType = _no_selected;
        }

        theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
        this->Invalidate(FALSE);
    }
}

void CMapEditorSDIView::OnFileSave()
{
    CFileDialog dlg(FALSE, L"*.sceA", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.sceA)|*.sceA|Any format (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();
        char cstr[256];
        strToChar(filename, cstr);

        //保存
        if(!save_level(cstr)){
            MessageBox(L"失敗");
        }
    }
}

/**
    Jump Level!
*/
void CMapEditorSDIView::On32776()
{
    // TODO : ここにコマンド ハンドラ コードを追加します。
    //レベル選択ダイアログ
    CSelectLevelDialog dlg;
    if(dlg.DoModal() == IDOK){
        load_level_from_map(theApp.editLevelIndex);

        //中心へ移動
        OnItemCentering();

        //Zoom
        OnItemZoomDefault();

        //選択無し
        theApp.selectType = _no_selected;

        this->Invalidate(FALSE);
    }
}

//zoom in / out
void CMapEditorSDIView::addZoom(int step)
{
    int oldZoomDiv = theApp.zoomDivision;
    if( theApp.zoomDivision < 50){
        step = sgn<int>(step);
    }
    theApp.zoomDivision += step;
    if(theApp.zoomDivision < ZOOM_DIVISION_MIN){
        theApp.zoomDivision = ZOOM_DIVISION_MIN;
    }else if(theApp.zoomDivision > ZOOM_DIVISION_MAX){
        theApp.zoomDivision = ZOOM_DIVISION_MAX;
    }
    CRect rect;
    GetClientRect(&rect);

    POINT oldOffset = theApp.offset;
    POINT center;
    center.x = rect.Width() / 2;
    center.y = rect.Height() / 2;
    int newZoomDiv = theApp.zoomDivision;

    int ax = center.x - oldOffset.x;
    theApp.offset.x = center.x - (ax * oldZoomDiv / newZoomDiv);
    int ay = center.y - oldOffset.y;
    theApp.offset.y = center.y - (ay * oldZoomDiv / newZoomDiv);
    /*
    int delta = OFFSET_X_WORLD / theApp.zoomDivision -
        //(rect.Width() / 2) +
        OFFSET_X_WORLD / oldZoomDiv;
    theApp.offset.x -= delta;
    delta = OFFSET_Y_WORLD / theApp.zoomDivision -
        //(rect.Height() / 2) +
        OFFSET_Y_WORLD / oldZoomDiv;
    theApp.offset.y -= delta;
    */
}

//拡大
void CMapEditorSDIView::OnZoomIn()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    addZoom(-ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//縮小
void CMapEditorSDIView::OnZoomOut()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    addZoom(ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//マウス移動
void CMapEditorSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    theApp.nowMousePoint = point;

    if(nFlags & MK_LBUTTON && nFlags & MK_SHIFT && theApp.isPressLButtonWithShift){
        //差
        int deltaX = point.x - theApp.oldMousePoint.x;
        int deltaY = point.y - theApp.oldMousePoint.y;
        theApp.offset.x += deltaX;
        theApp.offset.y += deltaY;
        this->Invalidate(FALSE);
    }else if(!theApp.isPressLButtonWithShift && 
        (nFlags & MK_LBUTTON) && !(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL)){
        //選択物の移動
        int x = (point.x - theApp.offset.x) * theApp.zoomDivision - OFFSET_X_WORLD;
        int y = (point.y - theApp.offset.y) * theApp.zoomDivision - OFFSET_Y_WORLD;
        if(!theApp.isSelectingGroup && theApp.selectType != _no_selected){
            if(theApp.selectType == _selected_object){
                SavedObjectList[theApp.selectIndex].location.x = x;
                SavedObjectList[theApp.selectIndex].location.y = y;
                //オブジェクト情報更新
                theApp.objectPropertyDialog->setupDialog(theApp.selectIndex);
            }else if(theApp.selectType == _selected_point){
                EndpointList[theApp.selectIndex].vertex.x = x;
                EndpointList[theApp.selectIndex].vertex.y = y;
            }else if(theApp.selectType == _selected_line){
                EndpointList[LineList[theApp.selectIndex].endpoint_indexes[0]].vertex.x = 
                    (world_distance)(x + theApp.polygonPoints[0].x * theApp.zoomDivision);
                EndpointList[LineList[theApp.selectIndex].endpoint_indexes[0]].vertex.y = 
                    (world_distance)(y + theApp.polygonPoints[0].y * theApp.zoomDivision);
                EndpointList[LineList[theApp.selectIndex].endpoint_indexes[1]].vertex.x = 
                    (world_distance)(x + theApp.polygonPoints[1].x * theApp.zoomDivision);
                EndpointList[LineList[theApp.selectIndex].endpoint_indexes[1]].vertex.y = 
                    (world_distance)(y + theApp.polygonPoints[1].y * theApp.zoomDivision);
            }
        }
        Invalidate(FALSE);
    }
    theApp.oldMousePoint = point;

    CView::OnMouseMove(nFlags, point);
}

//左ボタン下げ
void CMapEditorSDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(nFlags & MK_SHIFT){
        theApp.isPressLButtonWithShift = true;
    }else{
        theApp.isPressLButtonWithShift = false;
    }
    theApp.nowMousePoint = point;
    theApp.oldMousePoint = point;

    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;

    if(!(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL)){
        //shiftを押さずにクリック→選択
        bool selected = false;

        theApp.isSelectingGroup = false;

        {
            int DISTANCE_EPSILON = 8;
            //オブジェクト
            for(int i = 0; i < (int)SavedObjectList.size() && !selected; i ++){
                map_object* obj = &(SavedObjectList[i]);
                int type = obj->type;
                int facing = obj->facing;
                int x = obj->location.x;
                int y = obj->location.y;
                int z = obj->location.z;
                int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
                int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;

                POINT objPoint;
                objPoint.x = drawX;
                objPoint.y = drawY;


                //nearby check
                if(isNearbyPoints(point.x,point.y, objPoint.x,objPoint.y, DISTANCE_EPSILON)){
                    theApp.selectType = _selected_object;
                    theApp.selectIndex = i;
                    //選択したオブジェクトの情報を表示
                    theApp.objectPropertyDialog->setupDialog(i);
                    selected = true;
                    break;
                }
            }
        }
        if(selected){
            theApp.objectPropertyDialog->ShowWindow(TRUE);
            theApp.isObjectPropertyDialogShow = TRUE;

            //線プロパティ消す
            //ポリゴンプロパティ消す
        }else{
            //選択されなかった
            theApp.selectType = _no_selected;
            theApp.objectPropertyDialog->setupDialog(-1);
            //プロパティダイアログ消す
            theApp.objectPropertyDialog->ShowWindow(FALSE);
            theApp.isObjectPropertyDialogShow = FALSE;
        }

        if(!selected){
            int DISTANCE_EPSILON = 5;
            //ポイント
            for(int i = 0; i < (int)EndpointList.size(); i ++){
                endpoint_data* ep = &EndpointList[i];
                int x = ep->vertex.x;
                int y = ep->vertex.y;
                int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
                int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;
                if(isNearbyPoints(point.x,point.y, drawX,drawY, DISTANCE_EPSILON)){
                    theApp.selectType = _selected_point;
                    theApp.selectIndex = i;
                    //選択したオブジェクトの情報を表示
                    
                    selected = true;
                    break;
                }
            }
        }
        if(selected){
        }

        if(!selected){
            //線
            int DISTANCE_EPSILON = 5;
            for(int i = 0; i < (int)LineList.size(); i ++){
                line_data* line = &LineList[i];
                endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
                endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
                int x0 = (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                int y0 = (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
                int x1 = (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                int y1 = (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

                if(isNearbyPointToLine(point.x, point.y, x0, y0, x1, y1, DISTANCE_EPSILON)){
                    //接近している
                    theApp.selectType = _selected_line;
                    theApp.selectIndex = i;
                    selected = true;
                    //オフセット記録
                    theApp.polygonPointNum = 2;
                    theApp.polygonPoints[0].x = x0 - point.x;
                    theApp.polygonPoints[0].y = y0 - point.y;
                    theApp.polygonPoints[1].x = x1 - point.x;
                    theApp.polygonPoints[1].y = y1 - point.y;


                    break;
                }
            }
        }

        if(selected){
            //線プロパティ表示
        }else{
            //非表示
        }

        if(!selected){
            //ポリゴン
            for(int i = 0; i < (int)PolygonList.size(); i ++){
                struct world_point2d world_point;
                world_point.x = (world_distance)((point.x - OFFSET_X_VIEW) * DIV - OFFSET_X_WORLD);
                world_point.y = (world_distance)((point.y - OFFSET_Y_VIEW) * DIV - OFFSET_Y_WORLD);

                if(point_in_polygon(i, &world_point)){
                    theApp.selectType = _selected_polygon;
                    theApp.selectIndex = i;
                    selected = true;
                }
            }
        }
        
        if(selected){
            //ポリゴンプロパティ
        }else{
            //非表示
        }


        //////////////////////////////////
        //ここからの処理はほかよりも後に書く
        if(!selected){
            theApp.selectType = _no_selected;
            //範囲選択
            //始点登録
            theApp.selectStartPoint.x = point.x;
            theApp.selectStartPoint.y = point.y;
            theApp.isSelectingGroup = true;

            theApp.selectGroupInformation.clear();
        }else{
            theApp.isSelectingGroup = false;
        }
        this->Invalidate(FALSE);
    }
    CView::OnLButtonDown(nFlags, point);
    SetCapture();
}
//左ボタン上げ
void CMapEditorSDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    theApp.isPressLButtonWithShift = false;
    bool okSelect = false;
    if(theApp.isSelectingGroup){
        /*if(isNearbyPoints(point.x, point.y, 
            theApp.selectStartPoint.x, theApp.selectStartPoint.y, SELECT_GROUP_DISTANCE_THRESHOLD))
        {
            //
            theApp.selectGroupInformation.setSelected(false);
        }else{
            okSelect = true;
        }*/
        okSelect = true;
    }
    if(okSelect){
        theApp.selectType = _no_selected;

        int DIV = theApp.zoomDivision;
        int OFFSET_X_VIEW = theApp.offset.x;
        int OFFSET_Y_VIEW = theApp.offset.y;
        //選択されているものをリストに登録する
        //点
        for(int i = 0; i < (int)EndpointList.size(); i ++){
            endpoint_data* ep = &EndpointList[i];
            int x = ep->vertex.x;
            int y = ep->vertex.y;
            int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
            int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;
            //チェック
            if(isPointInRect<int>(drawX, drawY, point.x, point.y,
                theApp.selectStartPoint.x, theApp.selectStartPoint.y))
            {
                //追加
                theApp.selectGroupInformation.endpointIndexList.push_back(i);
            }
        }
        //線
        for(int i = 0; i < (int)LineList.size(); i ++){
            line_data* line = &LineList[i];
            endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
            endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
            int x0 = (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
            int y0 = (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
            int x1 = (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
            int y1 = (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
            if(isLineInRect(x0, y0, x1, y1, point.x, point.y,
                theApp.selectStartPoint.x, theApp.selectStartPoint.y))
            {
                theApp.selectGroupInformation.lineIndexList.push_back(i);
            }
        }

        //ポリゴン
        //POINT points[MAXIMUM_VERTICES_PER_POLYGON][2];
        for(int i = 0; i < (int)PolygonList.size(); i ++){
            struct polygon_data* polygon = &PolygonList[i];
            int vertexCount = polygon->vertex_count;
            bool inner = true;
            if(vertexCount == 0){
                inner = false;
            }
            for(int j = 0; j < vertexCount && inner; j ++){
                endpoint_data* ep = &EndpointList[polygon->endpoint_indexes[j]];
                int drawX = (ep->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                int drawY = (ep->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
                if(!isPointInRect<int>(drawX, drawY, point.x, point.y,
                    theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                {
                    inner = false;
                    break;
                }
            }
            if(inner){
                //登録
                theApp.selectGroupInformation.polygonIndexList.push_back(i);
            }
        }

        if(theApp.selectGroupInformation.endpointIndexList.size() > 0){
            theApp.selectGroupInformation.setSelected(true);
        }
    }

    theApp.isSelectingGroup = false;
    Invalidate(FALSE);
    ReleaseCapture();

    CView::OnLButtonUp(nFlags, point);
}
//中心へ移動
void CMapEditorSDIView::OnItemCentering()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.offset.x = 0;
    theApp.offset.y = 0;
    Invalidate(FALSE);
}
//拡大標準
void CMapEditorSDIView::OnItemZoomDefault()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
    Invalidate(FALSE);
}
//ホイール
BOOL CMapEditorSDIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    static short oldZDelta = zDelta;

    
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(nFlags & MK_CONTROL){
        addZoom( -1 * sgn<int>(zDelta) * ZOOM_DIVISION_STEP);
        Invalidate(FALSE);
    }
    return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMapEditorSDIView::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
{
    // この機能は Windows 2000 かそれ以降のバージョンを必要とします。
    // シンボル _WIN32_WINNTと WINVER は >= 0x0500 にならなければなりません。
    // TODO: ここにメッセージ ハンドラ コードを追加します。
}

void CMapEditorSDIView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

    static bool isFirst = true;

    if(isFirst){
        theApp.objectPropertyDialog = new CMonsterPropertyDialog;
        theApp.objectPropertyDialog->Create(this);
        //隠す
        theApp.isObjectPropertyDialogShow = FALSE;
        theApp.objectPropertyDialog->ShowWindow(FALSE);
        theApp.polygonTypeDialog = new CPolygonTypeDialog;
        theApp.polygonTypeDialog->Create(this);
        theApp.isPolygonTypeDialogShow = FALSE;
        theApp.polygonTypeDialog->ShowWindow(FALSE);
        theApp.heightDialog = new CHeightDialog;
        theApp.heightDialog->Create(this);
        
        //tool
        theApp.toolDialog = new CToolDialog;
        theApp.toolDialog->Create(this);
        theApp.isToolDialogShow = TRUE;
        theApp.toolDialog->ShowWindow(TRUE);

        isFirst = false;
        //
        //ビットマップ読み込み
        COLORREF key = RGB(221,221,221);
        theApp.mapIconImageList.Create(16, 16, ILC_MASK|ILC_COLOR32, 
        NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MAP_ICONS, 2);
        int idAssignment[] ={
            //items
            //start by IDB_BITMAP21=AlienWeapon sorted by names
            //look items.h for order 
            IDB_BITMAP39,   //knife = fist = none 0
            IDB_BITMAP39,   //magnum
            IDB_BITMAP40,
            IDB_BITMAP33,   //plasma
            IDB_BITMAP32,
            IDB_BITMAP24,   //rifle
            IDB_BITMAP23,
            IDB_BITMAP36,
            IDB_BITMAP44,   //missile
            IDB_BITMAP45,
            IDB_BITMAP28,   //invisible 10

            IDB_BITMAP37,   //invincible
            IDB_BITMAP29,   //infravision
            IDB_BITMAP21,   //alien
            IDB_BITMAP21,   //alien ammo (none)
            IDB_BITMAP31,   //frame
            IDB_BITMAP30,   
            IDB_BITMAP52,   //extravision
            IDB_BITMAP34,   //oxygen
            IDB_BITMAP43,   //energy
            IDB_BITMAP20,                   //20
            
            IDB_BITMAP42,
            IDB_BITMAP48,   //shotgun
            IDB_BITMAP47,
            IDB_BITMAP38,   //spht
            IDB_BITMAP36,   //chip

            IDB_BITMAP49,   //balls(unused except red one)
            IDB_BITMAP49,   //red (used)
            IDB_BITMAP49,
            IDB_BITMAP49,
            IDB_BITMAP49,                   //30
            
            IDB_BITMAP49,
            IDB_BITMAP49,
            IDB_BITMAP49,
            
            IDB_BITMAP50,   //smg
            IDB_BITMAP53,

            //other icons
            IDB_BITMAP26,   //center x
            IDB_BITMAP35,   //goal
            IDB_BITMAP46,   //scenery
            IDB_BITMAP51,   //sound

            0   //terminater
        };

        for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MAP_ICONS; i ++){
            //loadBitmap(idAssignment[i], &(theApp.mapIconImageList), key);
            CBitmap *bitmap = new CBitmap();
            bitmap->LoadBitmap(idAssignment[i]);
            theApp.bitmapList.push_back(bitmap);
        }
    }

}
//object info dialog on/off
void CMapEditorSDIView::On32784()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.isObjectPropertyDialogShow = !theApp.isObjectPropertyDialogShow;
    theApp.objectPropertyDialog->ShowWindow(theApp.isObjectPropertyDialogShow);
}
//level information(same to new)
void CMapEditorSDIView::On32787()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    CLevelParameterDialog dlg(this, false);
    if(dlg.DoModal() == IDOK){
        //値設定
    }
}
//show/hide height dialog
void CMapEditorSDIView::On32789()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.isHeightDialogShow = !theApp.isHeightDialogShow;
    theApp.heightDialog->ShowWindow(theApp.isHeightDialogShow);
}
//show/hide polygon type dialog
void CMapEditorSDIView::On32786()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.isPolygonTypeDialogShow = !theApp.isPolygonTypeDialogShow;
    theApp.polygonTypeDialog->ShowWindow(theApp.isPolygonTypeDialogShow);
}
//edit terminals
void CMapEditorSDIView::On32790()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    CTerminalDialog dlg(this);
    if(dlg.DoModal() == IDOK){
        //変更を保存

    }
}

void CMapEditorSDIView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: ここにメッセージ ハンドラ コードを追加します。
    //裏画面を作り直す
    
    CSize size = theApp.doubleBuffserBitmap.GetBitmapDimension();
    if(cx != size.cx || cy != size.cy){
        theApp.doubleBufferDC.DeleteDC();
        theApp.doubleBuffserBitmap.DeleteObject();
        
        createDoubleBuffer();
    }

}
void CMapEditorSDIView::createDoubleBuffer()
{
    CClientDC dc(this);
    CRect rect;
    GetClientRect(&rect);
    
    theApp.doubleBufferDC.CreateCompatibleDC(&dc);
    theApp.doubleBuffserBitmap.CreateCompatibleBitmap(
        &dc, rect.Width(), rect.Height());
    theApp.doubleBufferDC.SelectObject(&theApp.doubleBuffserBitmap);
}

int CMapEditorSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    createDoubleBuffer();
    build_trig_tables();
    if(dynamic_world == NULL){
        allocate_map_memory();
    }
    CRect cl_rect;
    GetClientRect(&cl_rect);
    theApp.m_SDLToWindows=new SDLToWindows(this->m_hWnd, cl_rect);
    screenSurface = theApp.m_SDLToWindows->getSurface();
    /*
    struct view_data view;
    view.
    initialize_view_data(&view);
    initialize_screen
    */
    /*    */
    struct screen_mode_data scr;
    scr.acceleration = 0;
    scr.bit_depth = bit_depth;
    scr.draw_every_other_line = 0;
    scr.fullscreen = 0;
    scr.gamma_level = 4;
    scr.high_resolution = 1;
    scr.size = 2;
    initialize_screen(&scr, false);

    initialize_shape_handler();
    FileSpecifier ShapesFile("Shapes");
    if(!ShapesFile.Exists()){
        MessageBox(L"no shapes file");
    }else{
        open_shapes_file(ShapesFile);
        for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
            mark_collection_for_loading(i);
        }
        load_collections(false, false);
    }

    return 0;
}

void CMapEditorSDIView::OnFileNew()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    //確認ダイアログ
    //マップ情報ダイアログ表示
    CLevelParameterDialog dlg(this, true);
    if(dlg.DoModal() == IDOK){
        //マップ情報削除
        initialize_map_for_new_level();
        //レベル一覧削除
        theApp.LevelNameList.RemoveAll();
        //
        Invalidate(FALSE);
    }
}
//visual mode dialog
void CMapEditorSDIView::On32796()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    CVisualDialog dlg(this);
    if(dlg.DoModal() == IDOK){
    }
}
//level info
void CMapEditorSDIView::On32788()
{
    // TODO : ここにコマンド ハンドラ コードを追加します。
    CLevelParameterDialog dlg(this, false);
    if(dlg.DoModal() == IDOK){
        //内容を反映
    }
}
