// MapEditorSDIView.cpp : CMapEditorSDIView �N���X�̎���
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
	// �W������R�}���h
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

// CMapEditorSDIView �R���X�g���N�V����/�f�X�g���N�V����

CMapEditorSDIView::CMapEditorSDIView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
    
}

CMapEditorSDIView::~CMapEditorSDIView()
{
    //delete theApp.objectPropertyDialog;
}

BOOL CMapEditorSDIView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

// CMapEditorSDIView �`��

void CMapEditorSDIView::OnDraw(CDC* pDC)
{
	CMapEditorSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
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
    
    //�r�b�g�}�b�v�ǂݍ���
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

    //�w�i
    {
        cdc->SelectObject(&blackSmallPen);
        cdc->SelectObject(&grayBrush);
        cdc->Rectangle(&winRect);
    }

    //�͈�
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

    //�O���b�h
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

    //�|���S��
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

    //��
    for(int i = 0; i < (int)LineList.size(); i ++){
        cdc->SelectObject(&blackSmallPen);
        line_data* line = &LineList[i];
        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
        int x0 = (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
        int y0 = (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
        int x1 = (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
        int y1 = (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

        //�I�𒆂͑����Ԑ���
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

    //�|�C���g
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

        //�_��ł�
        cdc->SelectObject(&blueSmallPen);
        cdc->SelectObject(&yellowBrush);
        cdc->Rectangle(&rect);

        //�I�𒆂͂��邵���B
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

    //�I�u�W�F�N�g
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

        //bitmap�\��
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
                    //��
                    cdc->SelectObject(&blueBrush);
                }else{
                    //��
                    cdc->SelectObject(&redBrush);
                }
            }else{
                //�v���C���[�͉��F
                cdc->SelectObject(&yellowBrush);
            }
            int facing = obj->facing;
            double degree = (double)facing / (1<<ANGULAR_BITS) * 360.0;

            //�O�p�`��`��
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
        //�I�𒆂͂��邵���B
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

    //�A�m�e�[�V�����i�}�b�v�ɕ\������镶���j�̕`��
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

    //�I��͈�
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

    //����ʂ����C���֓]��
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


// CMapEditorSDIView ���

BOOL CMapEditorSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ����̈������
	return DoPreparePrinting(pInfo);
}

void CMapEditorSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CMapEditorSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}


// CMapEditorSDIView �f�f

#ifdef _DEBUG
void CMapEditorSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CMapEditorSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditorSDIDoc* CMapEditorSDIView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorSDIDoc)));
	return (CMapEditorSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditorSDIView ���b�Z�[�W �n���h��

static bool loadMapFromFile(const char* filename){
    FileSpecifier mapFile = FileSpecifier(filename);
    //set map file
    set_map_file(mapFile);
    return true;
}

void CMapEditorSDIView::OnFileOpen()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    	//�t�@�C���I�[�v���_�C�A���O�\��
	CFileDialog dlg(TRUE, L"*.*", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

        //�ǂݍ���
        char cstr[256];
        strToChar(filename, cstr);

        //�^�C�g���ɐݒ�
        CMapEditorSDIDoc* doc = GetDocument();
        doc->SetTitle(filename);

        
        //�}�b�v�t�@�C�����[�h
        loadMapFromFile(cstr);

        //���x��1��ǂݍ���ł݂�
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

        //�ۑ�
        if(!save_level(cstr)){
            MessageBox(L"���s");
        }
    }
}

/**
    Jump Level!
*/
void CMapEditorSDIView::On32776()
{
    // TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    //���x���I���_�C�A���O
    CSelectLevelDialog dlg;
    if(dlg.DoModal() == IDOK){
        load_level_from_map(theApp.editLevelIndex);

        //���S�ֈړ�
        OnItemCentering();

        //Zoom
        OnItemZoomDefault();

        //�I�𖳂�
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

//�g��
void CMapEditorSDIView::OnZoomIn()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    addZoom(-ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//�k��
void CMapEditorSDIView::OnZoomOut()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    addZoom(ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//�}�E�X�ړ�
void CMapEditorSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    theApp.nowMousePoint = point;

    if(nFlags & MK_LBUTTON && nFlags & MK_SHIFT && theApp.isPressLButtonWithShift){
        //��
        int deltaX = point.x - theApp.oldMousePoint.x;
        int deltaY = point.y - theApp.oldMousePoint.y;
        theApp.offset.x += deltaX;
        theApp.offset.y += deltaY;
        this->Invalidate(FALSE);
    }else if(!theApp.isPressLButtonWithShift && 
        (nFlags & MK_LBUTTON) && !(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL)){
        //�I�𕨂̈ړ�
        int x = (point.x - theApp.offset.x) * theApp.zoomDivision - OFFSET_X_WORLD;
        int y = (point.y - theApp.offset.y) * theApp.zoomDivision - OFFSET_Y_WORLD;
        if(!theApp.isSelectingGroup && theApp.selectType != _no_selected){
            if(theApp.selectType == _selected_object){
                SavedObjectList[theApp.selectIndex].location.x = x;
                SavedObjectList[theApp.selectIndex].location.y = y;
                //�I�u�W�F�N�g���X�V
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

//���{�^������
void CMapEditorSDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
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
        //shift���������ɃN���b�N���I��
        bool selected = false;

        theApp.isSelectingGroup = false;

        {
            int DISTANCE_EPSILON = 8;
            //�I�u�W�F�N�g
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
                    //�I�������I�u�W�F�N�g�̏���\��
                    theApp.objectPropertyDialog->setupDialog(i);
                    selected = true;
                    break;
                }
            }
        }
        if(selected){
            theApp.objectPropertyDialog->ShowWindow(TRUE);
            theApp.isObjectPropertyDialogShow = TRUE;

            //���v���p�e�B����
            //�|���S���v���p�e�B����
        }else{
            //�I������Ȃ�����
            theApp.selectType = _no_selected;
            theApp.objectPropertyDialog->setupDialog(-1);
            //�v���p�e�B�_�C�A���O����
            theApp.objectPropertyDialog->ShowWindow(FALSE);
            theApp.isObjectPropertyDialogShow = FALSE;
        }

        if(!selected){
            int DISTANCE_EPSILON = 5;
            //�|�C���g
            for(int i = 0; i < (int)EndpointList.size(); i ++){
                endpoint_data* ep = &EndpointList[i];
                int x = ep->vertex.x;
                int y = ep->vertex.y;
                int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
                int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;
                if(isNearbyPoints(point.x,point.y, drawX,drawY, DISTANCE_EPSILON)){
                    theApp.selectType = _selected_point;
                    theApp.selectIndex = i;
                    //�I�������I�u�W�F�N�g�̏���\��
                    
                    selected = true;
                    break;
                }
            }
        }
        if(selected){
        }

        if(!selected){
            //��
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
                    //�ڋ߂��Ă���
                    theApp.selectType = _selected_line;
                    theApp.selectIndex = i;
                    selected = true;
                    //�I�t�Z�b�g�L�^
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
            //���v���p�e�B�\��
        }else{
            //��\��
        }

        if(!selected){
            //�|���S��
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
            //�|���S���v���p�e�B
        }else{
            //��\��
        }


        //////////////////////////////////
        //��������̏����͂ق�������ɏ���
        if(!selected){
            theApp.selectType = _no_selected;
            //�͈͑I��
            //�n�_�o�^
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
//���{�^���グ
void CMapEditorSDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
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
        //�I������Ă�����̂����X�g�ɓo�^����
        //�_
        for(int i = 0; i < (int)EndpointList.size(); i ++){
            endpoint_data* ep = &EndpointList[i];
            int x = ep->vertex.x;
            int y = ep->vertex.y;
            int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
            int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;
            //�`�F�b�N
            if(isPointInRect<int>(drawX, drawY, point.x, point.y,
                theApp.selectStartPoint.x, theApp.selectStartPoint.y))
            {
                //�ǉ�
                theApp.selectGroupInformation.endpointIndexList.push_back(i);
            }
        }
        //��
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

        //�|���S��
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
                //�o�^
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
//���S�ֈړ�
void CMapEditorSDIView::OnItemCentering()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.offset.x = 0;
    theApp.offset.y = 0;
    Invalidate(FALSE);
}
//�g��W��
void CMapEditorSDIView::OnItemZoomDefault()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
    Invalidate(FALSE);
}
//�z�C�[��
BOOL CMapEditorSDIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    static short oldZDelta = zDelta;

    
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(nFlags & MK_CONTROL){
        addZoom( -1 * sgn<int>(zDelta) * ZOOM_DIVISION_STEP);
        Invalidate(FALSE);
    }
    return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMapEditorSDIView::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
{
    // ���̋@�\�� Windows 2000 ������ȍ~�̃o�[�W������K�v�Ƃ��܂��B
    // �V���{�� _WIN32_WINNT�� WINVER �� >= 0x0500 �ɂȂ�Ȃ���΂Ȃ�܂���B
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
}

void CMapEditorSDIView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO : �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

    static bool isFirst = true;

    if(isFirst){
        theApp.objectPropertyDialog = new CMonsterPropertyDialog;
        theApp.objectPropertyDialog->Create(this);
        //�B��
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
        //�r�b�g�}�b�v�ǂݍ���
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
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.isObjectPropertyDialogShow = !theApp.isObjectPropertyDialogShow;
    theApp.objectPropertyDialog->ShowWindow(theApp.isObjectPropertyDialogShow);
}
//level information(same to new)
void CMapEditorSDIView::On32787()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CLevelParameterDialog dlg(this, false);
    if(dlg.DoModal() == IDOK){
        //�l�ݒ�
    }
}
//show/hide height dialog
void CMapEditorSDIView::On32789()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.isHeightDialogShow = !theApp.isHeightDialogShow;
    theApp.heightDialog->ShowWindow(theApp.isHeightDialogShow);
}
//show/hide polygon type dialog
void CMapEditorSDIView::On32786()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.isPolygonTypeDialogShow = !theApp.isPolygonTypeDialogShow;
    theApp.polygonTypeDialog->ShowWindow(theApp.isPolygonTypeDialogShow);
}
//edit terminals
void CMapEditorSDIView::On32790()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CTerminalDialog dlg(this);
    if(dlg.DoModal() == IDOK){
        //�ύX��ۑ�

    }
}

void CMapEditorSDIView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    //����ʂ���蒼��
    
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
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    //�m�F�_�C�A���O
    //�}�b�v���_�C�A���O�\��
    CLevelParameterDialog dlg(this, true);
    if(dlg.DoModal() == IDOK){
        //�}�b�v���폜
        initialize_map_for_new_level();
        //���x���ꗗ�폜
        theApp.LevelNameList.RemoveAll();
        //
        Invalidate(FALSE);
    }
}
//visual mode dialog
void CMapEditorSDIView::On32796()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CVisualDialog dlg(this);
    if(dlg.DoModal() == IDOK){
    }
}
//level info
void CMapEditorSDIView::On32788()
{
    // TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CLevelParameterDialog dlg(this, false);
    if(dlg.DoModal() == IDOK){
        //���e�𔽉f
    }
}
