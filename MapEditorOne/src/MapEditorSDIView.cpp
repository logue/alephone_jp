// MapEditorSDIView.cpp : CMapEditorSDIView �N���X�̎���
//

#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"

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
	ON_COMMAND(ID_Menu32797, &CMapEditorSDIView::OnMenu32797)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_32795, &CMapEditorSDIView::On32795)
	ON_COMMAND(ID_HEIGHT_FLOOR, &CMapEditorSDIView::OnHeightFloor)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MODE_POLYGONTYPE, &CMapEditorSDIView::OnModePolygontype)
	ON_COMMAND(ID_32808, &CMapEditorSDIView::On32808)
	ON_COMMAND(ID_TEXTURE_FLOOR, OnTextureFloor)
    ON_COMMAND(ID_EDIT_COPY, &CMapEditorSDIView::OnEditCopy)
    ON_COMMAND(ID_EDIT_PASTE, &CMapEditorSDIView::OnEditPaste)
END_MESSAGE_MAP()

// CMapEditorSDIView �R���X�g���N�V����/�f�X�g���N�V����

CMapEditorSDIView::CMapEditorSDIView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//	�C�����Ă��������B
	
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

void CMapEditorSDIView::drawBackground(CDC *cdc)
{
	CRect winRect;
	GetClientRect(&winRect);

	CBrush brush;
	brush.CreateSolidBrush(theApp.setting.getColorSetting()->background);

	//cdc->SelectObject(&blackSmallPen);
	cdc->SelectObject(GetStockObject(NULL_PEN));
	cdc->SelectObject(brush);
	cdc->Rectangle(&winRect);

	brush.DeleteObject();
}

void CMapEditorSDIView::drawGrid(CDC *cdc)
{
	CPen smallPen, midiumPen;
	smallPen.CreatePen(PS_SOLID, 1, theApp.setting.getColorSetting()->gridLine);
	midiumPen.CreatePen(PS_SOLID, 2, theApp.setting.getColorSetting()->gridLine);

    int offset[2];
    theApp.gridManager->getOffset(offset);
	int OFFSET_X_VIEW = offset[0];
	int OFFSET_Y_VIEW = offset[1];
	int DIV = theApp.gridManager->getZoomDivision();

	for(int i = OFFSET_X_WORLD / DIV; i <= OFFSET_X_WORLD * 2 / DIV;
			i += theApp.gridIntervals[theApp.setting.getGridSizeIndex()] / DIV){
		if( i == OFFSET_X_WORLD / DIV){
			cdc->SelectObject(midiumPen);
		}else{
			cdc->SelectObject(smallPen);
		}
		int x0 = OFFSET_X_VIEW + i;
		int y0 = OFFSET_Y_VIEW + i;

		cdc->MoveTo(x0, OFFSET_Y_VIEW);
		cdc->LineTo(x0, OFFSET_Y_VIEW + OFFSET_Y_WORLD * 2 / DIV);
		cdc->MoveTo(OFFSET_X_VIEW, y0);
		cdc->LineTo(OFFSET_X_VIEW + OFFSET_X_WORLD * 2 / DIV, y0);
	}
	for(int i = OFFSET_X_WORLD / DIV; i >= 0;
		i -= theApp.gridIntervals[theApp.setting.getGridSizeIndex()] / DIV){
		if( i == OFFSET_X_WORLD / DIV){
			cdc->SelectObject(midiumPen);
		}else{
			cdc->SelectObject(smallPen);
		}
		int x0 = OFFSET_X_VIEW + i;
		int y0 = OFFSET_Y_VIEW + i;

		cdc->MoveTo(x0, OFFSET_Y_VIEW);
		cdc->LineTo(x0, OFFSET_Y_VIEW + OFFSET_Y_WORLD * 2 / DIV);
		cdc->MoveTo(OFFSET_X_VIEW, y0);
		cdc->LineTo(OFFSET_X_VIEW + OFFSET_X_WORLD * 2 / DIV, y0);
	}
	smallPen.DeleteObject();
	midiumPen.DeleteObject();
}

/**
    �|���S������
*/
void CMapEditorSDIView::drawPolygons(CDC *cdc)
{
	CBrush nullBrush, netBrush;

	//for polygon type mode
	CBrush polygonBrushes[NUMBER_OF_POLYGON_TYPE];
	for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
		polygonBrushes[i].CreateSolidBrush(theApp.polygonTypeColor[i]);
	}

	//setup selected polygon
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_PATTERN_SELECTED_POLYGON);
	netBrush.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, theApp.setting.getColorSetting()->lines);

	int fillMode = WINDING;
	SetPolyFillMode(cdc->m_hDC, fillMode);

	//no lines
	cdc->SelectObject(GetStockObject(NULL_PEN));

	POINT points[MAXIMUM_VERTICES_PER_POLYGON];
	//sort order from index to height
	int polyMax = static_cast<int>(PolygonList.size());
	int *indexes = new int[polyMax];
	int* datas = new int[polyMax];
	//sortMap(indexes, polyMax, datas);
	delete datas;
	//sort it by floor
	//sortOrderToHeight((int)PolygonList.size(), POLYGON_TAG, indexes, true);

	for(int i = 0; i < (int)PolygonList.size(); i ++){
		int index = i;//indexes[i];
		struct polygon_data* polygon = &PolygonList[index];
		int flags = polygon->flags;
		int vertexCount = polygon->vertex_count;
		if(vertexCount == 0){
			continue;
		}
		int ceil = EndpointList[polygon->endpoint_indexes[0]].lowest_adjacent_ceiling_height;
		int floor = EndpointList[polygon->endpoint_indexes[0]].highest_adjacent_floor_height;
		if( floor < theApp.viewHeightMin ||
			ceil > theApp.viewHeightMax){
				continue;
		}
		for(int j = 0; j < vertexCount; j ++){
			endpoint_data* ep = &EndpointList[polygon->endpoint_indexes[j]];
			int viewPoint[2];
			getViewPointFromWorldPoint2D(ep->vertex, viewPoint);
			points[j].x = viewPoint[0];
			points[j].y = viewPoint[1];
		}
        //�|���S���̐��������m���߂�
        bool validity = isValidPolygon(index);

		CBrush brush;
		int type = 0;
		switch(theApp.getEditMode()){
		case EM_DRAW:
			brush.CreateSolidBrush(theApp.setting.getColorSetting()->polygons);
			cdc->SelectObject(&brush);
			break;
		case EM_POLYGON_TYPE:
			type = polygon->type;
			cdc->SelectObject(&polygonBrushes[type]);
			break;
		case EM_FLOOR_HEIGHT:
			if(polygon->floor_height < 0){
				//divide height
				int red = (int)(255 * (1.0 - (-(double)polygon->floor_height / MAXIMUM_FLOOR_HEIGHT)));
				brush.CreateSolidBrush(RGB(red,0,0));
			}else{
				int notRed = (int)(255 * (polygon->floor_height / MAXIMUM_FLOOR_HEIGHT));
				brush.CreateSolidBrush(RGB(255, notRed, notRed));
			}
			cdc->SelectObject(&brush);
			break;
		default:
			brush.CreateSolidBrush(theApp.setting.getColorSetting()->polygons);
			cdc->SelectObject(&brush);
		}
		//check is_selected 
		//if then draw bold
		if(theApp.selectDatas.isSelected() &&
			theApp.selectDatas.containsPolygon(index)){
			cdc->SelectObject(&netBrush);
		}else{
            /*
			//check polygon invalidate
            if(!hpl::aleph::map::isValidPolygon(index)){
                //�s���ȃ|���S���ł�
                brush.DeleteObject();
                brush.CreateSolidBrush(RGB(255,0,0));
                cdc->SelectObject(&brush);
            }*/
		}
		Polygon(cdc->m_hDC, points, vertexCount);

		brush.DeleteObject();
	}
	delete indexes;

	pen.DeleteObject();
	netBrush.DeleteObject();
	nullBrush.DeleteObject();
}

/**
    ����`�悵�܂�
*/
void CMapEditorSDIView::drawLines(CDC *cdc)
{
	CPen pen, selectedPen, hiddenLinePen;
	pen.CreatePen(PS_SOLID, 1, theApp.setting.getColorSetting()->lines);
	selectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
	hiddenLinePen.CreatePen(PS_SOLID, 1, RGB(200,200,200));

	for(int i = 0; i < (int)LineList.size(); i ++){
		line_data* line = &LineList[i];
		endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
		endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
		int floor = line->highest_adjacent_floor;
		int ceil = line->lowest_adjacent_ceiling;

		bool isHiddenLine = false;
		if(floor < theApp.viewHeightMin || ceil > theApp.viewHeightMax){
			isHiddenLine = true;
			if(theApp.isRevealHiddenLines){
				continue;
			}
		}

		int beginPoint[2], endPoint[2];
		getViewPointFromWorldPoint2D(begin->vertex, beginPoint);
		getViewPointFromWorldPoint2D(end->vertex, endPoint);

		//�I�𒆂͑����Ԑ���
		bool selected = false;
		if(isHiddenLine){
			//�B����i�\�����j
			cdc->SelectObject(&hiddenLinePen);
		}else{
			int index = i;
			if(theApp.selectDatas.isSelected() &&
				theApp.selectDatas.containsLine(index)){
				cdc->SelectObject(&selectedPen);

				if(theApp.selectDatas.isSelectOneSide()){
					//side�\��
				}
			}else{
				cdc->SelectObject(&pen);
			}
		}
		cdc->MoveTo(beginPoint[0], beginPoint[1]);
		cdc->LineTo(endPoint[0], endPoint[1]);
	}
	pen.DeleteObject();
	selectedPen.DeleteObject();
	hiddenLinePen.DeleteObject();
}

/**
    �_�̕\��
    @param cdc �f�o�C�X�R���e�L�X�g
*/
void CMapEditorSDIView::drawPoints(CDC *cdc)
{
	CPen pen, selectedPen;
	pen.CreatePen(PS_SOLID, 1, theApp.setting.getColorSetting()->points);
	selectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
	CBrush brush;
	brush.CreateSolidBrush(theApp.setting.getColorSetting()->points);

	for(int i = 0; i < (int)EndpointList.size(); i ++){
		endpoint_data* ep = &EndpointList[i];
		int floor = ep->highest_adjacent_floor_height;
		int ceil = ep->lowest_adjacent_ceiling_height;
		if( floor < theApp.viewHeightMin ||
			ceil > theApp.viewHeightMax){
				continue;
		}
		int drawPoint[2];
		getViewPointFromWorldPoint2D(ep->vertex, drawPoint);
		int drawX = drawPoint[0];
		int drawY = drawPoint[1];
		RECT rect;
		int SIZE = 2;
		rect.left = drawX - SIZE;
		rect.right = drawX + SIZE;
		rect.top = drawY - SIZE;
		rect.bottom = drawY + SIZE;

		//�_��ł�
		cdc->SelectObject(&pen);
		cdc->SelectObject(&brush);
		cdc->Rectangle(&rect);

		int index = i;
		//�I�𒆂͂��邵���B
		if(theApp.selectDatas.isSelected() &&
			theApp.selectDatas.containsPoint(index)){
			cdc->SelectObject(&selectedPen);
			//cdc->SetBkMode(TRANSPARENT);
			cdc->SelectObject(GetStockObject(NULL_BRUSH));
			RECT rect;
			int SIZE = 5;
			rect.left = drawX - SIZE;
			rect.right = rect.left + SIZE * 2;
			rect.top = drawY - SIZE;
			rect.bottom = rect.top + SIZE * 2;
			cdc->Rectangle(&rect);
		}
	}
	pen.DeleteObject();
	brush.DeleteObject();
	selectedPen.DeleteObject();
}
void CMapEditorSDIView::drawObjects(CDC *cdc)
{
	//ready for bitmap blit
	CDC memDC;
	memDC.CreateCompatibleDC(cdc);
	CBitmap* oldBitmap = memDC.GetCurrentBitmap();

	CPen monsterPen, selectedMonsterPen;
	CBrush playerBrush, selectedPlayerBrush;
	CBrush monsterBrush, selectedMonsterBrush;
	CBrush bobBrush, selectedBobBrush;

	monsterPen.CreatePen(PS_SOLID, 1, theApp.setting.getColorSetting()->lines);
	selectedMonsterPen.CreatePen(PS_SOLID, 1, RGB(255,0,0));
	//yellow
	playerBrush.CreateSolidBrush(RGB(255,255,0));
	//purple
	selectedPlayerBrush.CreateSolidBrush(RGB(255,0,255));
	//red
	monsterBrush.CreateSolidBrush(RGB(255,0,0));
	//green
	selectedMonsterBrush.CreateSolidBrush(RGB(0,255,0));
	//blue
	bobBrush.CreateSolidBrush(RGB(0,0,255));
	//gray-blue
	selectedBobBrush.CreateSolidBrush(RGB(100,100,255));

	int fillMode = WINDING;
	SetPolyFillMode(cdc->m_hDC, fillMode);
	for(int i = 0; i < (int)SavedObjectList.size(); i ++){
		map_object* obj = &(SavedObjectList[i]);
		int type = obj->type;
		int facing = obj->facing;
		int x = obj->location.x;
		int y = obj->location.y;
		int z = obj->location.z;

		//check height
		if( z < theApp.viewHeightMin ||
			z > theApp.viewHeightMax)
		{
			continue;
		}

		int drawPoint[2];
		world_point2d worldPoint = {x,y};
		getViewPointFromWorldPoint2D(worldPoint, drawPoint);
		int drawX = drawPoint[0];
		int drawY = drawPoint[1];

		int index = -1;
		if(type == _saved_monster || type == _saved_player){
			//draw with pen and brush
			index = -1;
		}else if(type == _saved_item){
			//draw with bmp
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

		//check for selecting
		bool isSelected = false;
		if(theApp.selectDatas.isSelected() &&
			theApp.selectDatas.containsObject(i)){
				isSelected = true;
		}

		if(index >= 0){
			if(isSelected){
				//highlight!
				index += NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MAP_ICONS;
			}
			HBITMAP hbmp = theApp.bitmapList[index];
			//CBitmap* bitmap = CBitmap::FromHandle();
			BITMAP bmp;
			GetObject(hbmp, sizeof(BITMAP), &bmp);
			CSize sz;
			sz.cx = bmp.bmWidth;
			sz.cy = bmp.bmHeight;
			memDC.SelectObject(hbmp);
			::TransparentBlt(cdc->m_hDC, drawX - sz.cx / 2, drawY - sz.cy / 2,
				sz.cx, sz.cy, memDC.m_hDC,
				0, 0, sz.cx, sz.cy, RGB(221,221,221));
		}else{
			//without bmp
			if(isSelected){
				cdc->SelectObject(selectedMonsterPen);
			}else{
				cdc->SelectObject(monsterPen);
			}
			if(type == _saved_monster){
				if(obj->index >= _civilian_crew &&
					obj->index <= _civilian_security ||
					obj->index >= _civilian_fusion_crew &&
					obj->index <= _civilian_fusion_security)
				{
					//bobs
					if(isSelected){
						cdc->SelectObject(&selectedBobBrush);
					}else{
						cdc->SelectObject(&bobBrush);
					}
				}else{
					//other monsters
					cdc->SelectObject(monsterPen);
					if(isSelected){
						cdc->SelectObject(&selectedMonsterBrush);
					}else{
						cdc->SelectObject(&monsterBrush);
					}
				}
			}else{
				//player
				if(isSelected){
					cdc->SelectObject(&selectedPlayerBrush);
				}else{
					cdc->SelectObject(&playerBrush);
				}
			}
			int facing = obj->facing;
			double degree = (double)facing / (1<<ANGULAR_BITS) * 360.0;

			//�O�p�`��`��
			POINT points[3];
			points[0].x = (LONG)(drawX + 10 * cos(hpl::math::getRadianFromDegree(degree)));
			points[0].y = (LONG)(drawY + 10 * sin(hpl::math::getRadianFromDegree(degree)));
			points[1].x = (LONG)(drawX + 5 * cos(hpl::math::getRadianFromDegree(degree + 120)));
			points[1].y = (LONG)(drawY + 5 * sin(hpl::math::getRadianFromDegree(degree + 120)));
			points[2].x = (LONG)(drawX + 5 * cos(hpl::math::getRadianFromDegree(degree - 120)));
			points[2].y = (LONG)(drawY + 5 * sin(hpl::math::getRadianFromDegree(degree - 120)));

			cdc->Polygon(points, 3);
		}

		//cdc->SetBkMode(TRANSPARENT);

		/*if(isSelected){
			cdc->SelectObject(&redMidiumPen);
			cdc->SelectObject(&nullBrush);
			RECT rect;
			int SIZE = 10;
			rect.left = drawX - SIZE;
			rect.right = rect.left + SIZE * 2;
			rect.top = drawY - SIZE;
			rect.bottom = rect.top + SIZE * 2;
			cdc->Rectangle(&rect);
		}*/

	}

	memDC.DeleteDC();
}

void CMapEditorSDIView::drawStrings(CDC *cdc)
{

	cdc->SetTextColor(theApp.setting.getColorSetting()->strings);
	for(int i = 0; i < (int)MapAnnotationList.size(); i ++){
		map_annotation *annotation = &MapAnnotationList[i];
		int drawPoint[2];
		getViewPointFromWorldPoint2D(annotation->location, drawPoint);

		//message
		CString msg(annotation->text);
		//RECT clientRect;
		//GetClientRect(&clientRect);
		cdc->TextOut(drawPoint[0], drawPoint[1], msg, msg.GetLength());
	}
	cdc->SetTextColor(RGB(0,0,0));
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/**
    �`��S��
*/
void CMapEditorSDIView::OnDraw(CDC* pDC)
{
	CMapEditorSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    draw(pDC);
}
void CMapEditorSDIView::draw(CDC* pDC){
    
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B


	CDC *cdc = &theApp.doubleBufferDC;
	cdc->SetBkColor(RGB(200,200,200));
	//CDC doubleBufferDC;
	//doubleBufferDC.CreateCompatibleDC(pDC);

	CRect winRect;
	GetClientRect(&winRect);

	//�w�i
	drawBackground(cdc);

	//�͈�
	{
        int offset[2];
        theApp.gridManager->getOffset(offset);
		int OFFSET_X_VIEW = offset[0];
		int OFFSET_Y_VIEW = offset[1];
		int DIV = theApp.gridManager->getZoomDivision();
		int ICON_SIZE = 16;

		CPen pen;
		pen.CreatePen(PS_SOLID, 1, theApp.setting.getColorSetting()->gridLine);
		cdc->SelectObject(pen);
		cdc->SelectObject(GetStockObject(NULL_BRUSH));
		RECT rect;
		rect.left = OFFSET_X_VIEW;
		rect.top = OFFSET_Y_VIEW;
		rect.right = rect.left + OFFSET_X_WORLD * 2 / DIV;
		rect.bottom = rect.top + OFFSET_Y_WORLD * 2 / DIV;
		cdc->Rectangle(&rect);
		pen.DeleteObject();
	}

	//�O���b�h
	drawGrid(cdc);

	//TODO sort by HEIGHT!

	//�|���S��
	drawPolygons(cdc);

	//��
	drawLines(cdc);

	//�|�C���g
	drawPoints(cdc);

	if(theApp.getEditMode() == EM_DRAW){
		drawObjects(cdc);
	}

	//�A�m�e�[�V�����i�}�b�v�ɕ\������镶���j�̕`��
	drawStrings(cdc);

    int mpoint[2];
    theApp.gridManager->getNewMousePoint(mpoint);
	//�I��͈�
	if(theApp.isSelectingGroup){
		bool selecting = true;
		/*if(!isNearbyPoints(theApp.selectStartPoint.x, theApp.selectStartPoint.y,
			theApp.nowMousePoint.x, theApp.nowMousePoint.y, SELECT_GROUP_DISTANCE_THRESHOLD))
		{
			selecting = true;
		}*/
		if(selecting){
			CPen pen;
			pen.CreatePen(PS_DASH, 1, RGB(255,0,0));

			cdc->SelectObject(GetStockObject(NULL_BRUSH));
			cdc->SelectObject(&pen);

			cdc->Rectangle(theApp.selectStartPoint.x, theApp.selectStartPoint.y,
				mpoint[0], mpoint[1]);

			pen.DeleteObject();
		}

        //�|���S���ǉ����[�h�Ȃ�ǉ��\��|���S����\���H
	}

	//����ʂ����C���֓]��
	pDC->BitBlt(0,0,winRect.Width(), winRect.Height(), 
		cdc, 0, 0, SRCCOPY);

	/*cdc->SelectObject(&oldPen);
	cdc->SelectObject(&oldBrush);
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
	MessageBox(L"What document-type do you want to print?");
}

void CMapEditorSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
	MessageBox(L"What document-type do you want to print?");
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

//�z�C�[��
/**
    �z�C�[���C�x���g
    @param nFlags �����ɂȂɂ�����Ă��邩(�L�[�Ȃ�)
    @param zDelta �Y�[���ω��ʂ̕�
    @param pt �z�C�[�����񂵂��Ƃ��̃}�E�X�|�C���g
*/
BOOL CMapEditorSDIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
//	static short oldZDelta = zDelta;

	
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if(nFlags & MK_CONTROL){
		//addZoom( -1 * hpl::math::sgn<int>(zDelta) * ZOOM_DIVISION_STEP);
        CRect rect;
        GetClientRect(&rect);
        if(zDelta < 0){
            theApp.gridManager->zoomIn(rect.Width(), rect.Height());
        }else{
            theApp.gridManager->zoomOut(rect.Width(), rect.Height());
        }
/*        //�\���X�V
        CDC* pDC = this->GetDC();
        draw(pDC);*/
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

		isFirst = false;


		On32795();
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
	 
	struct screen_mode_data scr;
	scr.acceleration = 0;
	scr.bit_depth = screenSurface->format->BitsPerPixel;
	scr.draw_every_other_line = 0;
	scr.fullscreen = 0;
	scr.gamma_level = 0;
	scr.high_resolution = 1;
	scr.size = 2;
	//SDL_Init(SDL_INIT_VIDEO);
	initialize_screen(&scr, false);

	theApp.isLoadedShapesFile = false;
#ifdef MAP_VIEWER
#else
	initialize_shape_handler();

	FileSpecifier ShapesFile("Shapes");
	if(!ShapesFile.Exists()){
		MessageBox(L"no shapes file");
	}else{
		theApp.isLoadedShapesFile = true;
		open_shapes_file(ShapesFile);
		for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
			mark_collection_for_loading(i);
		}
		load_collections(false, false);
	}
#endif
	delete theApp.m_SDLToWindows;


	theApp.objectPropertyDialog = new CMonsterPropertyDialog;
	theApp.objectPropertyDialog->Create(this);
	//�B��
	theApp.objectPropertyDialog->ShowWindow(FALSE);
	//�l���f�t�H���g�ɐݒ�
	setObjectPropertyToDefault();

	//polygon type dialog
	theApp.polygonTypeDialog = new CPolygonTypeDialog;
	theApp.polygonTypeDialog->Create(this);
	theApp.polygonTypeDialog->ShowWindow(FALSE);

	//height dialog
	theApp.heightDialog = new CHeightDialog;
	theApp.heightDialog->Create(this);

	//tool
	theApp.toolDialog = new CToolDialog;
	theApp.toolDialog->Create(this);
	theApp.toolDialog->ShowWindow(TRUE);

	//polygon property
	theApp.polygonPropertyDialog = new CPolygonPropertyDialog;
	theApp.polygonPropertyDialog->Create(this);
	theApp.polygonPropertyDialog->ShowWindow(FALSE);

	theApp.textureDialog = new CTextureDialog;
	theApp.textureDialog->Create(this);
	theApp.textureDialog->ShowWindow(FALSE);

	//point property
	theApp.pointPropertyDialog = new CPointPropertyDialog;
	theApp.pointPropertyDialog->Create(this);
	theApp.pointPropertyDialog->ShowWindow(FALSE);

	//load texture
	if(theApp.isLoadedShapesFile){
		int clut = 0;
		SDL_Color palette[256];

		int excol = NONE;
		float illumination = 1.0f;
		byte **outp = (byte**)malloc(sizeof(byte*));
		for(int i = 0; i < NUMBER_OF_MEDIA_TYPES; i ++){
			int collection = START_OF_TEXTURE + i;
			struct collection_header* header = get_collection_header(collection);
			//get number of bitmaps
			int bitmapNum = header->collection->bitmap_count;
			
			vector<CBitmap*> vec;
			theApp.textureBitmaps.push_back(vec);

			for(int j = 0; j < bitmapNum; j ++){
				//load shapes
				int col = BUILD_COLLECTION(collection, clut);
				int shapes = BUILD_DESCRIPTOR(col, j);
				SDL_Surface *surface = get_shape_surface(shapes, excol, outp,
					illumination, false, palette);
				CBitmap *bitmap = new CBitmap();
				bitmap->CreateCompatibleBitmap(GetDC(), surface->w, surface->h);
				int sizeW = surface->w, sizeH = surface->h;
				//copy to bitmap
				copySurfaceToBitmap(GetDC(), bitmap, surface, palette);
				SDL_FreeSurface(surface);

				theApp.textureBitmaps[i].push_back(bitmap);
			}
		}
		free(outp);
	}
	//delete theApp.m_SDLToWindows;
	return 0;
}

BOOL CMapEditorSDIView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	setCursor();
	return TRUE;
	//if(nHitTest == HTCLIENT){
	 /*	  LPWSTR cursors[] = {
			IDC_ARROW,
			IDC_CROSS,
			IDC_APPSTARTING,
			IDC_HAND,
			IDC_CROSS,
			IDC_APPSTARTING,
			IDC_HAND
		};
		//�J�[�\���ω�
		HCURSOR cursor = LoadCursor(AfxGetInstanceHandle(), cursors[theApp.selectingToolType]);
		SetCursor(cursor);
		return TRUE;*/
	//}
	//return CView::OnSetCursor(pWnd, nHitTest, message);
}



//view���W
const int DELTA = 10;
void CMapEditorSDIView::OnEditCopy()
{

    //�I��͈͂�ێ�����
    theApp.storedMapData.set(&theApp.selectDatas);
    theApp.storedDataPointDelta[0] = DELTA;
    theApp.storedDataPointDelta[1] = DELTA;
}


void CMapEditorSDIView::OnEditPaste()
{
    //�_�������ǁ��|���S�����I�u�W�F�N�g�̏��ō쐬
    //�R�s�[����ID�Ő��A�_�̊֌W�������߁A�V����ID�ō쐬����

    std::map<int, endpoint_data>* cpoints = theApp.storedMapData.getPoints();
    std::map<int, line_data>* clines = theApp.storedMapData.getLines();
    std::map<int, side_data>* csides = theApp.storedMapData.getSides();
    std::map<int, polygon_data>* cpolygons = theApp.storedMapData.getPolygons();
    std::map<int, map_object>* cobjects = theApp.storedMapData.getObjects();
    //�V����������|���S����ID�ƁA�R�s�[����ID�̑Ή�[��,�V]
    std::map<int, int> pointIndexTable;
    std::map<int, int> lineIndexTable;
    std::map<int, int> sideIndexTable;
    std::map<int, int> polygonIndexTable;
    std::map<int, int> objectIndexTable;
    
    theApp.selectDatas.clear();

    int div = theApp.gridManager->getZoomDivision();
    for(std::map<int, endpoint_data>::iterator it = cpoints->begin();
        it != cpoints->end(); it ++){
        //�R�s�[����ID
        int cid = it->first;
        endpoint_data cep = it->second;
        //
        endpoint_data ep;
        memcpy(&ep, &cep, sizeof(endpoint_data));

        //�ʒu�C��
        ep.vertex.x += theApp.storedDataPointDelta[0] * div;
        ep.vertex.y += theApp.storedDataPointDelta[1] * div;

        //���͐G�炸�B
        EndpointList.push_back(ep);
        int newIndex = (int)EndpointList.size() - 1;
        pointIndexTable[cid] = newIndex;
        int offset[] = {0,0};
        theApp.selectDatas.addSelPoint(newIndex, offset);
    }
    //��
    for(std::map<int, line_data>::iterator it = clines->begin();
        it != clines->end(); it ++){
        //�R�s�[����ID
        int cid = it->first;
        line_data cep = it->second;
        //
        line_data ep;
        memcpy(&ep, &cep, sizeof(line_data));

        for(int i = 0; i < 2; i ++){
            ep.endpoint_indexes[i] = pointIndexTable[ep.endpoint_indexes[i]];
        }
        //polygon�ԍ����Â��܂܂Ȃ̂ŁAsetupPolygon()�ŏC�����邱��

        LineList.push_back(ep);
        int newIndex = (int)LineList.size() - 1;
        lineIndexTable[cid] = newIndex;
        int offset[][2] = {{0,0},{0,0}};
        theApp.selectDatas.addSelLine(newIndex, offset);
    }
    //��
    for(std::map<int, side_data>::iterator it = csides->begin();
        it != csides->end(); it ++){
        //�R�s�[����ID
        int cid = it->first;
        side_data cep = it->second;
        //
        side_data ep;
        memcpy(&ep, &cep, sizeof(side_data));

        //����Ă���̔ԍ�
        ep.line_index = lineIndexTable[cep.line_index];

        SideList.push_back(ep);
        int newIndex = (int)SideList.size() - 1;
        sideIndexTable[cid] = newIndex;
        theApp.selectDatas.addSelSide(newIndex);
    }
    //�|���S��
    for(std::map<int, polygon_data>::iterator it = cpolygons->begin();
        it != cpolygons->end(); it ++){
        //�R�s�[����ID
        int cid = it->first;
        polygon_data cep = it->second;
        //
        polygon_data ep;
        memcpy(&ep, &cep, sizeof(polygon_data));

        //
        ep.center.x += theApp.storedDataPointDelta[0] * div;
        ep.center.y += theApp.storedDataPointDelta[1] * div;
        for(int i = 0; i < ep.vertex_count; i ++){
            ep.endpoint_indexes[i] = pointIndexTable[cep.endpoint_indexes[i]];
        }
        for(int i = 0; i < ep.vertex_count - 1; i ++){
            ep.line_indexes[i] = lineIndexTable[cep.line_indexes[i]];
        }
        ep.first_object = NONE;

        //TODO ���̍��ڂ͂悭�킩���

        PolygonList.push_back(ep);
        int newIndex = (int)PolygonList.size() - 1;
        polygonIndexTable[cid] = newIndex;
        int offset[8][2];
        for(int i = 0; i < 8; i ++){
            offset[i][0] = 0;
            offset[i][1] = 0;
        }
        theApp.selectDatas.addSelPolygon(newIndex, offset, ep.vertex_count);
    }
    //�I�u�W�F�N�g
    for(std::map<int, map_object>::iterator it = cobjects->begin();
        it != cobjects->end(); it ++){
        //�R�s�[����ID
        int cid = it->first;
        map_object cep = it->second;
        //
        map_object ep;
        memcpy(&ep, &cep, sizeof(map_object));

        //
        ep.location.x += theApp.storedDataPointDelta[0] * theApp.gridManager->getZoomDivision();
        ep.location.y += theApp.storedDataPointDelta[1] * theApp.gridManager->getZoomDivision();

        SavedObjectList.push_back(ep);
        int newIndex = (int)SavedObjectList.size() - 1;
        objectIndexTable[cid] = newIndex;
        int offset[2] = {0,0};
        theApp.selectDatas.addSelObject(newIndex, offset);
    }

    theApp.selectDatas.setSelected(true);

    theApp.storedDataPointDelta[0] += DELTA;
    theApp.storedDataPointDelta[1] += DELTA;

}
