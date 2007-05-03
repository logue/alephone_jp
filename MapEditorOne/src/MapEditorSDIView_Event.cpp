#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"

/**
    �}�E�X���W���_�ɋ߂����ǂ����𒲂ׂđI�����ɐݒ�
    @param mousePoint view���W�n�̃}�E�X�|�C���g���W
    @param offsetViewX view���W�n�̃Y���␳
    @param offsetViewY view���W�n�̃Y���␳
    @param offsetWorldX world���W�n�̃Y���␳
    @param offsetWorldY world���W�n�̃Y���␳
    @param div �Y�[��
    @param distance ������臒l�B����ȉ��Ȃ�I��
*/
static void checkSelectPoint(POINT& mousePoint,
                             int offsetViewX, int offsetViewY,
                             int offsetWorldX, int offsetWorldY,
                             int div,
                             int distance)
{
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = &EndpointList[i];
        int x = ep->vertex.x;
        int y = ep->vertex.y;
        int drawPoint[2];
        getViewPointFromWorldPoint2D(ep->vertex, drawPoint);

        if(hpl::aleph::map::isSelectPoint(mousePoint.x, mousePoint.y, x, y,
            offsetViewX, offsetViewY, offsetWorldX, offsetWorldY, div, distance))
        {
            int offset[2];
            offset[0] = drawPoint[0] - mousePoint.x;
            offset[1] = drawPoint[1] - mousePoint.y;
            theApp.selectDatas.addSelPoint(i, offset);
            return;
        }
    }
}

/**
    �I���J�n�ʒu���L��
*/
void CMapEditorSDIView::setStartPointForSelectGroup(int px, int py){
    theApp.selectStartPoint.x = px;
    theApp.selectStartPoint.y = py;
    theApp.isSelectingGroup = true;
}

/**
    ���{�^�����h���[���[�h�ŉ���
*/
void CMapEditorSDIView::doLButtonDownDrawMode(UINT nFlags, CPoint &point)
{
    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;

    if(theApp.selectingToolType == TI_ARROW){
        //selecting tool = TI_ARROW
        //���c�[����

        if(/*!(nFlags & MK_SHIFT) && */!(nFlags & MK_CONTROL)){
            //�R���g���[���L�[����������
            //clik without modify key
            
            //���ړ�����
            //->ready for move

            //���ɑI�����Ă�����
            //group selected
            if(//theApp.isSelectingGroup && 
                theApp.selectDatas.isSelected()){

                //�_���N���b�N�������ǂ���
                //is point in objects/points/lines/polygons?
                if(isPointInSelection(point.x, point.y,
                    OFFSET_X_VIEW, OFFSET_Y_VIEW, OFFSET_X_WORLD, OFFSET_Y_WORLD,
                    POINT_DISTANCE_EPSILON, LINE_DISTANCE_EPSILON, OBJECT_DISTANCE_EPSILON,
                    &theApp.selectDatas, theApp.viewHeightMax, theApp.viewHeightMin,
                    DIV))
                {
                    //click on selecting group
                    //->remember offset, ready to move

                    //points
                    std::vector<struct hpl::aleph::map::SelPoint>* selpoints = theApp.selectDatas.getSelPoints();
                    for(int i = 0; i < (int)selpoints->size(); i ++){
                        endpoint_data* ep = &EndpointList[selpoints->at(i).index];
                        //set pos to view
                        int x = ep->vertex.x;
                        int y = ep->vertex.y;
                        int drawX = (x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                        int drawY = (y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

                        //sub to offset
                        selpoints->at(i).offset[0] = drawX - point.x;
                        selpoints->at(i).offset[1] = drawY - point.y;
                    }

                    //lines
                    std::vector<struct hpl::aleph::map::SelLine>* sellines = theApp.selectDatas.getSelLines();
                    for(int i = 0; i < (int)sellines->size(); i ++){
                        struct hpl::aleph::map::SelLine* selData = &sellines->at(i);
                        line_data* line = &LineList[selData->index];
                        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
                        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
                        //set offsets
                        sellines->at(i).offset[0][0] =
                            (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                            - point.x;
                        sellines->at(i).offset[0][1] =
                            (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                            - point.y;
                        sellines->at(i).offset[1][0] =
                            (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                            - point.x;
                       sellines->at(i).offset[1][1] =
                            (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                            - point.y;

                    }

                    //polygons
                    std::vector<struct hpl::aleph::map::SelPolygon>* selpolygons = theApp.selectDatas.getSelPolygons();
                    for(int i = 0; i < (int)selpolygons->size(); i ++){
                        struct hpl::aleph::map::SelPolygon* selData = &selpolygons->at(i);
                        //set offset
                        polygon_data *polygon = &PolygonList[selData->index];
                        int num = polygon->vertex_count;
                        selpolygons->at(i).num = num;
                        for(int j = 0; j < num; j ++){
                            int drawX = (EndpointList[polygon->endpoint_indexes[j]].vertex.x + OFFSET_X_WORLD) / DIV
                                + OFFSET_X_VIEW;
                            int drawY = (EndpointList[polygon->endpoint_indexes[j]].vertex.y + OFFSET_Y_WORLD) / DIV
                                + OFFSET_Y_VIEW;
                            selData->offset[j][0] = drawX - point.x;
                            selData->offset[j][1] = drawY - point.y;
                        }
                    }

                    //objects
                    std::vector<struct hpl::aleph::map::SelObject>* selobjects = theApp.selectDatas.getSelObjects();
                    for(int i = 0; i < (int)selobjects->size(); i ++){
                        struct hpl::aleph::map::SelObject* selData = &selobjects->at(i);
                        map_object* obj = &SavedObjectList[selData->index];
                        //set pos to view
                        int x = obj->location.x;
                        int y = obj->location.y;
                        int drawX = (x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                        int drawY = (y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

                        //sub to offset
                        selData->offset[0] = drawX - point.x;
                        selData->offset[1] = drawY - point.y;
                    }
                }else{
                    //release all selection
                    theApp.selectDatas.clear();
                }

            }else {
                //ctrl���������ɃN���b�N���I��
                //�O���[�v�I���ł͂Ȃ�
                //�V�t�g�L�[�ƈꏏ�ɉ������H�i�I���̒ǉ��j
                bool isWithShift = (nFlags & MK_SHIFT) != 0;
                if(!isWithShift){
                    //�V�t�g�L�[���������ɃN���b�N�����炢������������
                    theApp.selectDatas.clear();
                    theApp.isSelectingGroup = false;
                }

                //objects
                {
                    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
                        map_object* obj = &(SavedObjectList[i]);
                        int type = obj->type;
                        int facing = obj->facing;
                        int x = obj->location.x;
                        int y = obj->location.y;
                        int z = obj->location.z;
                        if(z > theApp.viewHeightMax ||
                            z < theApp.viewHeightMin){
                                continue;
                        }
                        if(hpl::aleph::map::isSelectPoint(point.x, point.y,
                            x, y, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                            OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, OBJECT_DISTANCE_EPSILON))
                        {
                            int drawX = (x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                            int drawY = (y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

                            int offset[2];
                            offset[0] = drawX - point.x;
                            offset[1] = drawY - point.y;
                            theApp.selectDatas.addSelObject(i, offset);
                            //�I�������I�u�W�F�N�g�̏���\��
                            theApp.objectPropertyDialog->setupDialog(i);
                            break;
                        }
                    }
                }
                if(theApp.selectDatas.isSelected()){
                    //object property
                    //�I�u�W�F�N�g�v���p�e�B�E�C���h�E��\������
                    theApp.objectPropertyDialog->ShowWindow(TRUE);

                }else{
                    //no selection
                    theApp.objectPropertyDialog->setSelectedObjectIndex(-1);
                }

                ////////////////////
                //points
                if(!theApp.selectDatas.isSelected()){
                    checkSelectPoint(point, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, POINT_DISTANCE_EPSILON);
                }
                if(theApp.selectDatas.isSelected()){
                    //show point property dialog TODO
                }

                //////////////////
                //lines
                if(!theApp.selectDatas.isSelected()){
                    for(int i = 0; i < (int)LineList.size(); i ++){
                        line_data* line = &LineList[i];
                        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
                        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
                        if(hpl::aleph::map::isSelectLine(point.x, point.y, begin->vertex.x, begin->vertex.y,
                            end->vertex.x, end->vertex.y, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                            OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, LINE_DISTANCE_EPSILON))
                        {
                            //�ڋ߂��Ă���
                            //�I�t�Z�b�g�L�^
                            int offset[2][2];
                            offset[0][0] = 
                                (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                                - point.x;
                            offset[0][1] = 
                                (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                                - point.y;
                            offset[1][0] = 
                                (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                                - point.x;
                            offset[1][1] = 
                                (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                                - point.y;
                            theApp.selectDatas.addSelLine(i, offset);

                            break;
                        }
                    }
                }

                if(theApp.selectDatas.isSelected()){
                    //���v���p�e�B�\��
                }else{
                    //��\��
                }

                /////////////////
                //polygons
                if(!theApp.selectDatas.isSelected()){
                    struct world_point2d world_point = getWorldPoint2DFromViewPoint(point.x, point.y);
                    int polygonIndex = getPolygonIdPointIn(world_point);
                    if(polygonIndex != NONE){
                        polygon_data *polygon = &PolygonList[polygonIndex];

                        int index = polygonIndex;
                        int num = polygon->vertex_count;
                        int offset[8][2];
                        
                        //show polygon property
                        theApp.polygonPropertyDialog->ShowWindow(TRUE);
                        theApp.polygonPropertyDialog->setupDialog(polygonIndex);

                        //set offset
                        for(int j = 0; j < num; j ++){
                            int drawPoint[2];
                            getViewPointFromWorldPoint2D(EndpointList[polygon->endpoint_indexes[j]].vertex,
                                drawPoint);
                            int drawX = drawPoint[0];
                            int drawY = drawPoint[1];
                            offset[j][0] = drawX - point.x;
                            offset[j][1] = drawY - point.y;
                        }

                        theApp.selectDatas.addSelPolygon(index, offset, num);
                    }
                }

                //////////////////////////////////
                //��������̏����͂ق�������ɏ���
                if(!theApp.selectDatas.isSelected()){
                    //�͈͑I��
                    //�n�_�o�^
                    setStartPointForSelectGroup(point.x, point.y);

                    theApp.selectDatas.clear();
                }else{
                    theApp.isSelectingGroup = false;
                }
            }
        }
    }else if(theApp.selectingToolType == TI_FILL){
        //TODO

        //�h���|���S�����ۂ����̏W����T��
        int* lines = new int[8];
        delete lines;
    }else if(theApp.selectingToolType == TI_HAND){
        //�S�̂��ړ�
        //D&D�̕����Ŏ����ς�

    }else if( theApp.selectingToolType == TI_LINE){
        //�������c�[��

#ifdef MAP_VIEWER
#else
        if(nFlags & MK_LBUTTON){
            theApp.selectDatas.clear();
            world_point2d worldPoint = getWorldPoint2DFromViewPoint(point.x, point.y);
            int settledPointIndex = addPoint(worldPoint);
            if(settledPointIndex == NONE){
                //�ǉ����s
                theApp.isFirstOfLineToAdd = true;
            }else{
                if(theApp.isFirstOfLineToAdd){
                    theApp.isFirstOfLineToAdd = false;
                    //add point(first)
                }else{
                    //add point and line
                    //add line
                    addLine(theApp.previousPointIndex, settledPointIndex);
                }
                theApp.previousPointIndex = settledPointIndex;
            }
        }
#endif

    }else if(theApp.selectingToolType == TI_MAGNIFY){
        //zoom in/out
        if(nFlags & MK_CONTROL){
            //with ctrl
            //->zoom out
            OnZoomOut();
        }else{
            //zoom in
            OnZoomIn();
        }

    }else if(theApp.selectingToolType == TI_SKULL){
        //�I�u�W�F�N�g�z�u�c�[����
#ifdef MAP_VIEWER
#else
        struct world_point2d world_point = getWorldPoint2DFromViewPoint(point.x, point.y);

        int polygonIndex = getPolygonIdPointIn(world_point);
        if(polygonIndex != NONE){
            polygon_data *polygon = &PolygonList[polygonIndex];
            //invalid height -> skip
            if(polygon->floor_height > theApp.viewHeightMax ||
                polygon->ceiling_height < theApp.viewHeightMin){
            }else{
                //add object on the polygon
                int objectIndex = addObject(world_point, polygonIndex);

                //�I����Ԃɂ���
                theApp.selectDatas.clear();

                int index = objectIndex;
                int offset[2] = {0,0};
                theApp.selectDatas.addSelObject(index, offset);

                //�I�������I�u�W�F�N�g�̏���\��
                theApp.objectPropertyDialog->setupDialog(objectIndex);
            }
        }
#endif

    }else if(theApp.selectingToolType == TI_TEXT){
        //�e�L�X�g���̓c�[��
#ifdef MAP_VIEWER
#else
        //add annotation
        //show dialog
        CAnnotationDialog dlg(this);
        if(dlg.DoModal() == IDOK){
            struct world_point2d world_point = getWorldPoint2DFromViewPoint(point.x, point.y);

            int polygonIndex = getPolygonIdPointIn(world_point);

            if(dlg.isOnlyDisplayWhenPolygonShown){
            }else{
                polygonIndex = NONE;
            }
            char cstr[MAXIMUM_ANNOTATION_TEXT_LENGTH];
            strToChar(dlg.annotationText, cstr);
            addAnnotationText(world_point, string(cstr));

        }
        //focus this window
        this->SetFocus();
#endif
    }else if(theApp.selectingToolType == TI_POLYGON){
        //�K��|���S���쐬�c�[��
#ifdef MAP_VIEWER
#else
        //set start point
        setStartPointForSelectGroup(point.x, point.y);
#endif
    }
}

/**
    �|���S����I���������ǂ������f���܂�
*/
void checkPolygonSelect(UINT nFlags, CPoint point)
{
    theApp.selectDatas.clear();

    struct world_point2d world_point = getWorldPoint2DFromViewPoint(point.x, point.y);

    //�|���S���̒��Ƀ}�E�X�|�C���^�������Ă��邩
    int polygonIndex = getPolygonIdPointIn(world_point);
    if(polygonIndex != NONE){
        polygon_data *polygon = &PolygonList[polygonIndex];

        int index = polygonIndex;
        int num = polygon->vertex_count;
        int offset[8][2];
        memset(offset, 0, sizeof(int)*8 * 2);
        
        //show polygon property
        theApp.polygonPropertyDialog->ShowWindow(TRUE);
        theApp.polygonPropertyDialog->setupDialog(polygonIndex);

        theApp.selectDatas.addSelPolygon(index, offset, num);
    }
}

//���{�^������
void CMapEditorSDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(nFlags & MK_CONTROL){
        //�R���g���[���{�^���������Ă���
        theApp.isPressLButtonWithCtrl = true;
    }else{
        theApp.isPressLButtonWithCtrl = false;
    }
    theApp.nowMousePoint = point;
    theApp.oldMousePoint = point;

    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;


    switch(theApp.getEditMode()){
    case EM_DRAW:
        if(theApp.selectingToolType != TI_LINE){
            theApp.isFirstOfLineToAdd = true;
            theApp.previousPointIndex = NONE;
        }
        if(theApp.selectingToolType == TI_HAND){
            theApp.isPressLButtonWithCtrl = true;
        }
        if(nFlags & MK_CONTROL){
        }else{
            doLButtonDownDrawMode(nFlags, point);
        }
        break;
    case EM_POLYGON_TYPE:
        checkPolygonSelect(nFlags, point);
        break;
    case EM_FLOOR_HEIGHT:
        //change height
        break;
    case EM_CEILING_HEIGHT:
        //change height
        break;
    case EM_FLOOR_LIGHT:
        //change light
        break;
    case EM_CEILING_LIGHT:
        //change light
        break;
    case EM_MEDIA:
        //change media
        break;
    case EM_FLOOR_TEXTURE:
        //change texture
        break;
    case EM_CEILING_TEXTURE:
        //change texture
        break;
    default:
        AfxMessageBox(L"Illigal edit mode!");
    }
    this->Invalidate(FALSE);
    CView::OnLButtonDown(nFlags, point);
    SetCapture();
}

void CMapEditorSDIView::moveMapOffset(int newPx, int newPy){
    int deltaX = newPx - theApp.oldMousePoint.x;
    int deltaY = newPy - theApp.oldMousePoint.y;
    theApp.offset.x += deltaX;
    theApp.offset.y += deltaY;
}
/****************************************************************/
//�}�E�X�ړ�
void CMapEditorSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
    setCursor();

    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    theApp.nowMousePoint = point;

    const int DIV = theApp.zoomDivision;
#ifdef MAP_VIEWER
    //�N���b�N���Ă���Έړ�
    if(nFlags & MK_LBUTTON &&
        (nFlags & MK_CONTROL && theApp.isPressLButtonWithCtrl ||
        theApp.getEditMode() == EM_DRAW && theApp.selectingToolType == TI_HAND ||
//        theApp.getEditMode() == EM_DRAW && (theApp.selectingToolType == TI_ARROW)||
        nFlags & MK_CONTROL)){
        moveMapOffset(point.x, point.y);
    }
#else
    if(nFlags & MK_LBUTTON && ((nFlags & MK_CONTROL && theApp.isPressLButtonWithCtrl) ||
        (theApp.getEditMode() == EM_DRAW && theApp.selectingToolType == TI_HAND))){
        //Control+L=move map view
        moveMapOffset(point.x, point.y);
    }else{
        if(theApp.getEditMode() == EM_DRAW){
            if(theApp.selectingToolType == TI_ARROW){
                if(!theApp.isPressLButtonWithCtrl && 
                    (nFlags & MK_LBUTTON) && /*!(nFlags & MK_CONTROL) && */
                    !(nFlags & MK_CONTROL))
                {
                    //�I�𕨂̈ړ�
                    //world position of mouse pointer
                    int x = (point.x - theApp.offset.x) * theApp.zoomDivision - OFFSET_X_WORLD;
                    int y = (point.y - theApp.offset.y) * theApp.zoomDivision - OFFSET_Y_WORLD;
                    if(theApp.selectDatas.isSelected()){
                        //�O���[�v��I�����Ă���
                        //->�O���[�v���ړ�
                        //points
                        std::vector<struct hpl::aleph::map::SelPoint>* selpoints =
                            theApp.selectDatas.getSelPoints();
                        for(int i = 0; i < (int)selpoints->size(); i ++){
                            struct hpl::aleph::map::SelPoint* selData = &selpoints->at(i);
                            EndpointList[selData->index].vertex.x = x + selData->offset[0] * DIV;
                            EndpointList[selData->index].vertex.y = y + selData->offset[1] * DIV;
                        }
                        //lines
                        std::vector<struct hpl::aleph::map::SelLine>* sellines =
                            theApp.selectDatas.getSelLines();
                        for(int i = 0; i < (int)sellines->size(); i ++){
                            struct hpl::aleph::map::SelLine* selData = &sellines->at(i);
                            EndpointList[LineList[selData->index].endpoint_indexes[0]].vertex.x =
                                x + selData->offset[0][0] * DIV;
                            EndpointList[LineList[selData->index].endpoint_indexes[0]].vertex.y =
                                y + selData->offset[0][1] * DIV;
                            EndpointList[LineList[selData->index].endpoint_indexes[1]].vertex.x =
                                x + selData->offset[1][0] * DIV;
                            EndpointList[LineList[selData->index].endpoint_indexes[1]].vertex.y =
                                y + selData->offset[1][1] * DIV;
                        }
                        std::vector<struct hpl::aleph::map::SelPolygon>* selpolygons =
                            theApp.selectDatas.getSelPolygons();
                        //polygons
                        for(int i = 0; i < (int)selpolygons->size(); i ++){
                            struct hpl::aleph::map::SelPolygon* selData = &selpolygons->at(i);
                            for(int j = 0; j < selData->num; j ++){
                                EndpointList[PolygonList[selData->index].endpoint_indexes[j]].vertex.x =
                                    x + selData->offset[j][0] * DIV;
                                EndpointList[PolygonList[selData->index].endpoint_indexes[j]].vertex.y =
                                    y + selData->offset[j][1] * DIV;
                            }
                        }
                        //objects
                        std::vector<struct hpl::aleph::map::SelObject>* selobjects =
                            theApp.selectDatas.getSelObjects();
                        for(int i = 0; i < (int)selobjects->size(); i ++){
                            struct hpl::aleph::map::SelObject* selData = &selobjects->at(i);
                            SavedObjectList[selData->index].location.x = x + selData->offset[0] * DIV;
                            SavedObjectList[selData->index].location.y = y + selData->offset[1] * DIV;
                        }
                        
                    }
                }
            }else if(theApp.selectingToolType == TI_FILL){
            }else if(theApp.selectingToolType == TI_HAND){
                if(nFlags & MK_LBUTTON){
                    moveMapOffset(point.x, point.y);
                }
            }else if(theApp.selectingToolType == TI_LINE){
                //�_�𓥂�łȂ����m�F
                int endpointIndex = NONE;
                bool found = false;
                world_point2d world_point = getWorldPoint2DFromViewPoint(point.x, point.y);
                for(int i = 0; i < (int)EndpointList.size(); i ++){
                    endpoint_data *point = &EndpointList[i];
                    //check height
                    if( point->highest_adjacent_floor_height > theApp.viewHeightMax ||
                        point->lowest_adjacent_ceiling_height < theApp.viewHeightMin)
                    {
                        continue;
                    }
                    if(hpl::aleph::map::isSelectPoint(world_point, point->vertex, POINT_DISTANCE_EPSILON * theApp.zoomDivision))
                    {
                        theApp.isNowOnThePoint = true;
                        found = true;
                        break;
                    }
                }
                if(!found){
                    theApp.isNowOnThePoint = false;
                }
            }else if(theApp.selectingToolType == TI_MAGNIFY){
            }else if(theApp.selectingToolType == TI_POLYGON){
            }else if(theApp.selectingToolType == TI_SKULL){
            }else if(theApp.selectingToolType == TI_TEXT){
            }
        }else{
        }
    }// if/not ctrled
#endif
    Invalidate(FALSE);
    theApp.oldMousePoint = point;

    CView::OnMouseMove(nFlags, point);
}

//���{�^���グ
void CMapEditorSDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    theApp.isPressLButtonWithCtrl = false;

    if(theApp.selectingToolType == TI_ARROW){
        //���c�[��

        bool okSelect = false;
        if(theApp.selectDatas.isSelectOneObject()){
            //�I�u�W�F�N�g���X�V
            theApp.objectPropertyDialog->setupDialog(theApp.selectDatas.getSelObjects()->at(0).index);
        }else if(theApp.selectDatas.isSelectOnePoint()){
        }else if(theApp.selectDatas.isSelectOneLine()){
        }else if(theApp.selectDatas.isSelectOnePolygon()){
            //�|���S�����X�V
            theApp.polygonPropertyDialog->setupDialog(theApp.selectDatas.getSelPolygons()->at(0).index);
        }
        if(theApp.isSelectingGroup){
            /*if(isNearbyPoints(point.x, point.y, 
                theApp.selectStartPoint.x, theApp.selectStartPoint.y, SELECT_GROUP_DISTANCE_THRESHOLD))
            {
                //
                theApp.selectDatas.setSelected(false);
            }else{
                okSelect = true;
            }*/
            okSelect = true;
        }
        if(okSelect){
            //if selecting is only 1 object. setup property dialog

            theApp.selectDatas.clear();

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
                if(hpl::math::isPointInRect<int>(drawX, drawY, point.x, point.y,
                    theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                {
                    //�ǉ�
                    int index = i;
                    int offset[2] = {0,0};
                    //�I�t�Z�b�g�͎��ɍ��{�^�����������Ƃ��ɐݒ肷��
                    theApp.selectDatas.addSelPoint(index, offset);
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
                if(hpl::math::isLineInRect(x0, y0, x1, y1, point.x, point.y,
                    theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                {
                    int index = i;
                    int offset[2][2] = {{0,0},{0,0}};
                    //�I�t�Z�b�g�͎��ɍ��{�^�����������Ƃ��ɐݒ肷��
                    theApp.selectDatas.addSelLine(index, offset);
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
                    if(!hpl::math::isPointInRect<int>(drawX, drawY, point.x, point.y,
                        theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                    {
                        inner = false;
                        break;
                    }
                }
                if(inner){
                    //�o�^
                    int index = i;
                    int offset[8][2];
                    memset(offset, 0, sizeof(int) * 8 * 2);
                    int num = 8;
                    //�I�t�Z�b�g�͎��ɍ��{�^�����������Ƃ��ɐݒ肷��
                    theApp.selectDatas.addSelPolygon(index, offset, num);
                }
            }

            //objects
            for(int i = 0; i < (int)SavedObjectList.size(); i ++){
                map_object* obj = &SavedObjectList[i];
                int x = obj->location.x;
                int y = obj->location.y;
                int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
                int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;

                //�`�F�b�N
                if(hpl::math::isPointInRect<int>(drawX, drawY, point.x, point.y,
                    theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                {
                    //�ǉ�
                    int index = i;
                    int offset[2] = {0,0};
                    //�I�t�Z�b�g�͎��ɍ��{�^�����������Ƃ��ɐݒ肷��
                    theApp.selectDatas.addSelObject(index, offset);
                }
            }

            //�I���������ǂ���
            bool isSelected = false;
            if(theApp.selectDatas.getSelPoints()->size() > 0 ||
                theApp.selectDatas.getSelObjects()->size() > 0){
                    isSelected = true;
            }
            theApp.selectDatas.setSelected(isSelected);
        }
    }else if(theApp.selectingToolType == TI_FILL){
    }else if(theApp.selectingToolType == TI_HAND){
    }else if(theApp.selectingToolType == TI_LINE){
    }else if(theApp.selectingToolType == TI_MAGNIFY){
    }else if(theApp.selectingToolType == TI_POLYGON){
        if(theApp.isSelectingGroup){
            //create preset polygon

        }
    }else if(theApp.selectingToolType == TI_SKULL){
    }else if(theApp.selectingToolType == TI_TEXT){
    }
    theApp.isSelectingGroup = false;
    Invalidate(FALSE);
    ReleaseCapture();

    CView::OnLButtonUp(nFlags, point);
}

// press event of Right button
void CMapEditorSDIView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

    theApp.nowMousePoint = point;
    theApp.oldMousePoint = point;

    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;

    if(theApp.selectingToolType != TI_LINE){
        theApp.isFirstOfLineToAdd = true;
        theApp.previousPointIndex = NONE;
    }

    if(theApp.selectingToolType == TI_ARROW){
    }else if(theApp.selectingToolType == TI_FILL){
    }else if(theApp.selectingToolType == TI_HAND){
    }else if( theApp.selectingToolType == TI_LINE){
        if(nFlags & MK_RBUTTON){
            //stop adding points
            theApp.isFirstOfLineToAdd = true;
            theApp.previousPointIndex = NONE;
        }
    }else if(theApp.selectingToolType == TI_MAGNIFY){
        //�k��
        OnZoomOut();
    }else if(theApp.selectingToolType == TI_SKULL){
    }else if(theApp.selectingToolType == TI_TEXT){
    }else if(theApp.selectingToolType == TI_POLYGON){

    }
    Invalidate(FALSE);
    CView::OnRButtonDown(nFlags, point);
    SetCapture();
}

void CMapEditorSDIView::OnRButtonUp(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

    Invalidate(FALSE);
    ReleaseCapture();
    CView::OnRButtonUp(nFlags, point);
}

