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
        redMidiumPen, grayMidiumPen, blueSmallPen;
    redSmallPen.CreatePen(PS_SOLID, 1, RGB(255,0,0));
    blackSmallPen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
    yellowSmallPen.CreatePen(PS_SOLID, 1, RGB(255,255,0));
    redMidiumPen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
    blueSmallPen.CreatePen(PS_SOLID, 1, RGB(0,0,255));
    graySmallPen.CreatePen(PS_SOLID, 1, RGB(200,200,200));
    grayMidiumPen.CreatePen(PS_SOLID, 2, RGB(200,200,200));

    CBrush grayBrush, redBrush, yellowBrush, nullBrush, netBrush;
    CBrush polygonBrushes[NUMBER_OF_POLYGON_TYPE];
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        polygonBrushes[i].CreateSolidBrush(theApp.polygonTypeColor[i]);
    }
    grayBrush.CreateSolidBrush(RGB(100, 100, 100));
    redBrush.CreateSolidBrush(RGB(255,0,0));
    yellowBrush.CreateSolidBrush(RGB(255,255,0));
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
    CBitmap monsterBitmap, itemBitmap, scenaryBitmap, goalBitmap;
    CBitmap soundBitmap;
    monsterBitmap.LoadBitmapW(IDB_BITMAP1);
    itemBitmap.LoadBitmapW(IDB_BITMAP_ITEM);
    scenaryBitmap.LoadBitmapW(IDB_BITMAP_SCENARY);
    goalBitmap.LoadBitmapW(IDB_BITMAP_GOAL);
    soundBitmap.LoadBitmapW(IDB_BITMAP_SOUND);
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* oldBitmap = memDC.GetCurrentBitmap();

    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;
    int ICON_SIZE = 16;

    pDC->SetBkColor(RGB(200,200,200));
    //CDC doubleBufferDC;
    //doubleBufferDC.CreateCompatibleDC(pDC);

    CRect winRect;
    GetClientRect(&winRect);

    CDC *cdc = pDC;
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
        if(theApp.selectType == _selected_polygon && theApp.selectIndex == i){
            cdc->SelectObject(&netBrush);
        }
        int flags = polygon->flags;
        int vertexCount = polygon->vertex_count;
        for(int j = 0; j < vertexCount; j ++){
            endpoint_data* point = &EndpointList[polygon->endpoint_indexes[j]];
            points[j].x = (point->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
            points[j].y = (point->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;
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
        if(theApp.selectType == _selected_line && theApp.selectIndex == i){
            cdc->SelectObject(&redMidiumPen);
        }

        cdc->MoveTo(x0, y0);
        cdc->LineTo(x1, y1);
    }

    //�|�C���g
    cdc->SelectObject(&blueSmallPen);
    cdc->SelectObject(&yellowBrush);
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* point = &EndpointList[i];
        int x = point->vertex.x;
        int y = point->vertex.y;
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
        if(theApp.selectType == _selected_point){
            if( theApp.selectIndex == i){
                cdc->SelectObject(&redMidiumPen);
                cdc->SetBkMode(TRANSPARENT);
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
        CBitmap* handle;
        if(type == _saved_monster || type == _saved_player){
            handle = NULL;
        }else if(type == _saved_item){
            handle = &itemBitmap;
        }else if(type == _saved_object){
            handle = &scenaryBitmap;
        }else if(type == _saved_goal){
            handle = &goalBitmap;
        }else{
            handle = &soundBitmap;
        }
        if(handle != NULL){
            memDC.SelectObject(handle);
            ::TransparentBlt(pDC->m_hDC, drawX - ICON_SIZE / 2, drawY - ICON_SIZE / 2,
                ICON_SIZE, ICON_SIZE, memDC.m_hDC,
                0, 0, ICON_SIZE, ICON_SIZE, RGB(255,255,255));
        }

        if(type == _saved_monster || type == _saved_player){
            cdc->SelectObject(blackSmallPen);
            if(type == _saved_monster){
                pDC->SelectObject(&redBrush);
            }else{
                pDC->SelectObject(&yellowBrush);
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

        //�I�𒆂͂��邵���B
        if(theApp.selectType == _selected_object){
            if( theApp.selectIndex == i){
                cdc->SelectObject(&redMidiumPen);
                cdc->SetBkMode(TRANSPARENT);
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
    cdc->SelectObject(&oldPen);
    cdc->SelectObject(&oldBrush);

    redSmallPen.DeleteObject();
    blackSmallPen.DeleteObject();
    yellowSmallPen.DeleteObject();
    redMidiumPen.DeleteObject();
    graySmallPen.DeleteObject();
    grayMidiumPen.DeleteObject();
    blueSmallPen.DeleteObject();

    grayBrush.DeleteObject();
    redBrush.DeleteObject();
    yellowBrush.DeleteObject();
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        polygonBrushes[i].DeleteObject();
    }
    nullBrush.DeleteObject();
    netBrush.DeleteObject();

    memDC.SelectObject(oldBitmap);
    monsterBitmap.DeleteObject();
    itemBitmap.DeleteObject();
    scenaryBitmap.DeleteObject();
    goalBitmap.DeleteObject();
    soundBitmap.DeleteObject();
    
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
            build_trig_tables();
            if(dynamic_world == NULL){
                allocate_map_memory();
            }
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
        this->RedrawWindow();
    }
}

void CMapEditorSDIView::OnFileSave()
{
    CFileDialog dlg(FALSE, L"*.map", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.map)|*.map|Any format (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();
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

        this->RedrawWindow();
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
    this->RedrawWindow();
}

//�k��
void CMapEditorSDIView::OnZoomOut()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    addZoom(ZOOM_DIVISION_STEP);
    this->RedrawWindow();
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
        this->RedrawWindow();
    }else if(nFlags & MK_LBUTTON && !(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL)){
        //�I�𕨂̈ړ�
        int x = (point.x - theApp.offset.x) * theApp.zoomDivision - OFFSET_X_WORLD;
        int y = (point.y - theApp.offset.y) * theApp.zoomDivision - OFFSET_Y_WORLD;
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
        RedrawWindow();
    }
    theApp.oldMousePoint = point;

    CView::OnMouseMove(nFlags, point);
}

static void noSelected()
{
    //�I������Ȃ�����
    theApp.selectType = _no_selected;
    theApp.objectPropertyDialog->setupDialog(-1);
    //�v���p�e�B�_�C�A���O����
    theApp.objectPropertyDialog->ShowWindow(FALSE);
    theApp.isObjectPropertyDialogShow = FALSE;
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

    if(!(nFlags & MK_SHIFT)){
        //shift���������ɃN���b�N���I��
        bool selected = false;

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
        }else{
            noSelected();
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
        }else{
            noSelected();
        }

        if(!selected){
            //��
            int DISTANCE_EPSILON = 10;
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

        if(!selected){
            noSelected();
        }

        if(!selected){
            //�|���S��
            for(int i = 0; i < (int)PolygonList.size(); i ++){
                struct world_point2d world_point;
                world_point.x = (point.x - OFFSET_X_VIEW) * DIV - OFFSET_X_WORLD;
                world_point.y = (point.y - OFFSET_Y_VIEW) * DIV - OFFSET_Y_WORLD;

                if(point_in_polygon(i, &world_point)){
                    theApp.selectType = _selected_polygon;
                    theApp.selectIndex = i;
                }
            }
        }
        this->RedrawWindow();
    }
    CView::OnLButtonDown(nFlags, point);
    SetCapture();
}
//���{�^���グ
void CMapEditorSDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    theApp.isPressLButtonWithShift = false;
    CView::OnLButtonUp(nFlags, point);
    ReleaseCapture();
}
//���S�ֈړ�
void CMapEditorSDIView::OnItemCentering()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.offset.x = 0;
    theApp.offset.y = 0;
    RedrawWindow();
}
//�g��W��
void CMapEditorSDIView::OnItemZoomDefault()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
    RedrawWindow();
}
//�z�C�[��
BOOL CMapEditorSDIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    static short oldZDelta = zDelta;

    
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(nFlags & MK_CONTROL){
        addZoom( -1 * sgn<int>(zDelta) * ZOOM_DIVISION_STEP);
        RedrawWindow();
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
        //theApp.objectPropertyDialog->Create(CMonsterPropertyDialog::IDD, this);
        theApp.objectPropertyDialog->Create(this);
        //�B��
        theApp.isObjectPropertyDialogShow = FALSE;
        theApp.objectPropertyDialog->ShowWindow(FALSE);

        //theApp.objectPropertyDialog->SetFocus();
        ///theApp.objectPropertyDialog->ModifyStyleEx(0, WS_EX_TOPMOST);
        theApp.polygonTypeDialog = new CPolygonTypeDialog;
        theApp.polygonTypeDialog->Create(this);
        //theApp.polygonTypeDialog->SetFocus();
        //theApp.polygonTypeDialog->ModifyStyleEx(0, WS_EX_TOPMOST);
        theApp.heightDialog = new CHeightDialog;
        theApp.heightDialog->Create(this);
        //theApp.heightDialog->SetFocus();
        //theApp.heightDialog->ModifyStyleEx(0, WS_EX_TOPMOST);
        
        //�_�u���o�b�t�@�����O����
        /*CClientDC dc(this);
        CRect rect;
        GetClientRect(&rect);
        theApp.doubleBufferDC.CreateCompatibleDC(&dc);
        theApp.doubleBuffserBitmap.CreateCompatibleBitmap(
            theApp.doubleBufferDC*/
        isFirst = false;
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
