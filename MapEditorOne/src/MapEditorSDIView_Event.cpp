#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"


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

        if(isSelectPoint(mousePoint.x, mousePoint.y, x, y,
            offsetViewX, offsetViewY, offsetWorldX, offsetWorldY, div, distance))
        {
            SelPoint pdata;
            pdata.index = i;
            pdata.offset[0] = drawPoint[0] - mousePoint.x;
            pdata.offset[1] = drawPoint[1] - mousePoint.y;
            theApp.selectGroupInformation.points.push_back(pdata);
            theApp.selectGroupInformation.setSelected(true);
            return;
        }
    }
}

static void doLButtonDownDrawMode(UINT nFlags, CPoint &point)
{
    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;
    if(theApp.selectingToolType == TI_ARROW){
        //selecting tool = TI_ARROW
        if(/*!(nFlags & MK_SHIFT) && */!(nFlags & MK_CONTROL)){
            //clik without modify key

            //group selected
            if(theApp.selectGroupInformation.isSelected()){

                //is point in objects/points/lines/polygons?
                if(isPointInSelection(point.x, point.y,
                    OFFSET_X_VIEW, OFFSET_Y_VIEW, OFFSET_X_WORLD, OFFSET_Y_WORLD,
                    POINT_DISTANCE_EPSILON, LINE_DISTANCE_EPSILON, OBJECT_DISTANCE_EPSILON,
                    &theApp.selectGroupInformation, theApp.viewHeightMax, theApp.viewHeightMin,
                    DIV))
                {
                    //click on selecting group
                    //->remember offset, ready to move

                    //points
                    for(int i = 0; i < (int)theApp.selectGroupInformation.points.size(); i ++){
                        endpoint_data* ep = &EndpointList[theApp.selectGroupInformation.points[i].index];
                        //set pos to view
                        int x = ep->vertex.x;
                        int y = ep->vertex.y;
                        int drawX = (x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                        int drawY = (y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

                        //sub to offset
                        theApp.selectGroupInformation.points[i].offset[0] = drawX - point.x;
                        theApp.selectGroupInformation.points[i].offset[1] = drawY - point.y;
                    }

                    //lines
                    for(int i = 0; i < (int)theApp.selectGroupInformation.lines.size(); i ++){
                        line_data* line = &LineList[theApp.selectGroupInformation.lines[i].index];
                        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
                        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
                        //set offsets
                        theApp.selectGroupInformation.lines[i].offsets[0][0] =
                            (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                            - point.x;
                        theApp.selectGroupInformation.lines[i].offsets[0][1] =
                            (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                            - point.y;
                        theApp.selectGroupInformation.lines[i].offsets[1][0] =
                            (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                            - point.x;
                        theApp.selectGroupInformation.lines[i].offsets[1][1] =
                            (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                            - point.y;

                    }

                    //polygons
                    for(int i = 0; i < (int)theApp.selectGroupInformation.polygons.size(); i ++){
                        //set offset
                        polygon_data *polygon = &PolygonList[theApp.selectGroupInformation.polygons[i].index];
                        int num = polygon->vertex_count;
                        theApp.selectGroupInformation.polygons[i].num = num;
                        for(int j = 0; j < num; j ++){
                            int drawX = (EndpointList[polygon->endpoint_indexes[j]].vertex.x + OFFSET_X_WORLD) / DIV
                                + OFFSET_X_VIEW;
                            int drawY = (EndpointList[polygon->endpoint_indexes[j]].vertex.y + OFFSET_Y_WORLD) / DIV
                                + OFFSET_Y_VIEW;
                            theApp.selectGroupInformation.polygons[i].offsets[j][0] = drawX - point.x;
                            theApp.selectGroupInformation.polygons[i].offsets[j][1] = drawY - point.y;
                        }
                    }

                    //objects
                    for(int i = 0; i < (int)theApp.selectGroupInformation.selObjects.size(); i ++){
                        map_object* obj = &SavedObjectList[theApp.selectGroupInformation.selObjects[i].index];
                        //set pos to view
                        int x = obj->location.x;
                        int y = obj->location.y;
                        int drawX = (x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                        int drawY = (y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

                        //sub to offset
                        theApp.selectGroupInformation.selObjects[i].offset[0] = drawX - point.x;
                        theApp.selectGroupInformation.selObjects[i].offset[1] = drawY - point.y;
                    }
                }else{
                    //release all selection
                    theApp.selectGroupInformation.clear();
                }

            }
            if(!theApp.selectGroupInformation.isSelected()){
                //shiftを押さずにクリック→選択
                theApp.selectGroupInformation.clear();

                theApp.isSelectingGroup = false;

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
                        if(isSelectPoint(point.x, point.y,
                            x, y, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                            OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, OBJECT_DISTANCE_EPSILON))
                        {
                            int drawX = (x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW;
                            int drawY = (y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW;

                            SelObject odata;
                            odata.index = i;
                            odata.offset[0] = drawX - point.x;
                            odata.offset[1] = drawY - point.y;
                            theApp.selectGroupInformation.selObjects.push_back(odata);
                            theApp.selectGroupInformation.setSelected(true);
                            //選択したオブジェクトの情報を表示
                            theApp.objectPropertyDialog->setupDialog(i);
                            break;
                        }
                    }
                }
                if(theApp.selectGroupInformation.isSelected()){
                    //object property
                    theApp.objectPropertyDialog->ShowWindow(TRUE);

                }else{
                    //no selection
                    theApp.objectPropertyDialog->setSelectedObjectIndex(-1);
                }

                ////////////////////
                //points
                if(!theApp.selectGroupInformation.isSelected()){
                    checkSelectPoint(point, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, POINT_DISTANCE_EPSILON);
                }
                if(theApp.selectGroupInformation.isSelected()){
                    //show point property dialog TODO
                }

                //////////////////
                //lines
                if(!theApp.selectGroupInformation.isSelected()){
                    for(int i = 0; i < (int)LineList.size(); i ++){
                        line_data* line = &LineList[i];
                        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
                        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
                        if(isSelectLine(point.x, point.y, begin->vertex.x, begin->vertex.y,
                            end->vertex.x, end->vertex.y, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                            OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, LINE_DISTANCE_EPSILON)){
                            //接近している
                            SelLine ldata;
                            ldata.index = i;

                            //オフセット記録
                            ldata.offsets[0][0] = 
                                (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                                - point.x;
                            ldata.offsets[0][1] = 
                                (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                                - point.y;
                            ldata.offsets[1][0] = 
                                (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                                - point.x;
                            ldata.offsets[1][1] = 
                                (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                                - point.y;
                            theApp.selectGroupInformation.lines.push_back(ldata);
                            theApp.selectGroupInformation.setSelected(true);

                            break;
                        }
                    }
                }

                if(theApp.selectGroupInformation.isSelected()){
                    //線プロパティ表示
                }else{
                    //非表示
                }

                /////////////////
                //polygons
                if(!theApp.selectGroupInformation.isSelected()){
                    for(int i = 0; i < (int)PolygonList.size(); i ++){
                        struct world_point2d world_point;
                        world_point.x = (world_distance)((point.x - OFFSET_X_VIEW) * DIV - OFFSET_X_WORLD);
                        world_point.y = (world_distance)((point.y - OFFSET_Y_VIEW) * DIV - OFFSET_Y_WORLD);

                        if(point_in_polygon(i, &world_point)){
                            polygon_data *polygon = &PolygonList[i];

                            SelPolygon polydata;
                            polydata.index = i;
                            polydata.num = polygon->vertex_count;

                            //show polygon type dialog
                            theApp.polygonTypeDialog->ShowWindow(TRUE);
                            //set selection
                            theApp.polygonTypeDialog->polygonTypeListCtrl.SetItemState(
                                polygon->type, LVIS_SELECTED | LVIS_FOCUSED,
                                LVIS_SELECTED | LVIS_FOCUSED);
                            
                            //show polygon property
                            theApp.polygonPropertyDialog->ShowWindow(TRUE);
                            theApp.polygonPropertyDialog->setupDialog(i);

                            //set offset
                            for(int j = 0; j < polygon->vertex_count; j ++){
                                int drawX = (EndpointList[polygon->endpoint_indexes[j]].vertex.x + OFFSET_X_WORLD) / DIV
                                    + OFFSET_X_VIEW;
                                int drawY = (EndpointList[polygon->endpoint_indexes[j]].vertex.y + OFFSET_Y_WORLD) / DIV
                                    + OFFSET_Y_VIEW;
                                polydata.offsets[j][0] = drawX - point.x;
                                polydata.offsets[j][1] = drawY - point.y;
                            }

                            theApp.selectGroupInformation.polygons.push_back(polydata);
                            theApp.selectGroupInformation.setSelected(true);
                        }
                    }
                }
                
                if(theApp.selectGroupInformation.isSelected()){
                    //show polygon type
                    //show polygon property
                }else{
                }


                //////////////////////////////////
                //ここからの処理はほかよりも後に書く
                if(!theApp.selectGroupInformation.isSelected()){
                    //範囲選択
                    //始点登録
                    theApp.selectStartPoint.x = point.x;
                    theApp.selectStartPoint.y = point.y;
                    theApp.isSelectingGroup = true;

                    theApp.selectGroupInformation.clear();
                }else{
                    theApp.isSelectingGroup = false;
                }
            }
        }
    }else if(theApp.selectingToolType == TI_FILL){
    }else if(theApp.selectingToolType == TI_HAND){
    }else if( theApp.selectingToolType == TI_LINE){
        if(nFlags & MK_LBUTTON){
            theApp.selectGroupInformation.clear();
            world_point2d worldPoint = getWorldPoint2DFromViewPoint(point.x, point.y);
            int settledPointIndex = addPoint(worldPoint);
            if(settledPointIndex == NONE){
                //追加失敗
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
    }else if(theApp.selectingToolType == TI_MAGNIFY){
    }else if(theApp.selectingToolType == TI_SKULL){
        for(int i = 0; i < (int)PolygonList.size(); i ++){
            struct world_point2d world_point;
            world_point.x = (world_distance)((point.x - OFFSET_X_VIEW) * DIV - OFFSET_X_WORLD);
            world_point.y = (world_distance)((point.y - OFFSET_Y_VIEW) * DIV - OFFSET_Y_WORLD);

            if(point_in_polygon(i, &world_point)){
                polygon_data *polygon = &PolygonList[i];
                //invalid height -> skip
                if(polygon->floor_height > theApp.viewHeightMax ||
                    polygon->ceiling_height < theApp.viewHeightMin){
                        continue;
                }
                //add object on the polygon
                int objectIndex = addObject(world_point, i);

                //選択状態にする
                theApp.selectGroupInformation.clear();
                SelObject odata;
                odata.index = objectIndex;
                odata.offset[0] = odata.offset[1] = 0;
                theApp.selectGroupInformation.setSelected(true);
                theApp.selectGroupInformation.selObjects.push_back(odata);

                //選択したオブジェクトの情報を表示
                theApp.objectPropertyDialog->setupDialog(objectIndex);
            }
        }
    }else if(theApp.selectingToolType == TI_TEXT){
    }else if(theApp.selectingToolType == TI_POLYGON){

    }
}
//左ボタン下げ
void CMapEditorSDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(nFlags & MK_CONTROL){
        theApp.isPressLButtonWithCtrl = true;
    }else{
        theApp.isPressLButtonWithCtrl = false;
    }
    theApp.nowMousePoint = point;
    theApp.oldMousePoint = point;

    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;

    if(theApp.selectingToolType != TI_LINE){
        theApp.isFirstOfLineToAdd = true;
        theApp.previousPointIndex = NONE;
    }

    switch(theApp.getEditMode()){
    case EM_DRAW:
        doLButtonDownDrawMode(nFlags, point);
        break;
    case EM_POLYGON_TYPE:
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

/****************************************************************/
//マウス移動
void CMapEditorSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
    setCursor();

    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    theApp.nowMousePoint = point;

    const int DIV = theApp.zoomDivision;

    if(theApp.selectingToolType == TI_ARROW){
        if(nFlags & MK_LBUTTON && nFlags & MK_CONTROL && theApp.isPressLButtonWithCtrl){
            //Control+L=move map view
            //差
            int deltaX = point.x - theApp.oldMousePoint.x;
            int deltaY = point.y - theApp.oldMousePoint.y;
            theApp.offset.x += deltaX;
            theApp.offset.y += deltaY;
            
        }else if(!theApp.isPressLButtonWithCtrl && 
            (nFlags & MK_LBUTTON) && /*!(nFlags & MK_CONTROL) && */
            !(nFlags & MK_CONTROL))
        {
            //選択物の移動
            //world position of mouse pointer
            int x = (point.x - theApp.offset.x) * theApp.zoomDivision - OFFSET_X_WORLD;
            int y = (point.y - theApp.offset.y) * theApp.zoomDivision - OFFSET_Y_WORLD;
            if(theApp.selectGroupInformation.isSelected()){
                //グループを選択している
                //->グループを移動
                //points
                for(int i = 0; i < (int)theApp.selectGroupInformation.points.size(); i ++){
                    struct SelPoint *selData = &theApp.selectGroupInformation.points[i];
                    EndpointList[selData->index].vertex.x = x + selData->offset[0] * DIV;
                    EndpointList[selData->index].vertex.y = y + selData->offset[1] * DIV;
                }
                //lines
                for(int i = 0; i < (int)theApp.selectGroupInformation.lines.size(); i ++){
                    struct SelLine *selData = &theApp.selectGroupInformation.lines[i];
                    EndpointList[LineList[selData->index].endpoint_indexes[0]].vertex.x =
                        x + selData->offsets[0][0] * DIV;
                    EndpointList[LineList[selData->index].endpoint_indexes[0]].vertex.y =
                        y + selData->offsets[0][1] * DIV;
                    EndpointList[LineList[selData->index].endpoint_indexes[1]].vertex.x =
                        x + selData->offsets[1][0] * DIV;
                    EndpointList[LineList[selData->index].endpoint_indexes[1]].vertex.y =
                        y + selData->offsets[1][1] * DIV;
                }
                //polygons
                for(int i = 0; i < (int)theApp.selectGroupInformation.polygons.size(); i ++){
                    struct SelPolygon *selData = &theApp.selectGroupInformation.polygons[i];
                    for(int j = 0; j < selData->num; j ++){
                        EndpointList[PolygonList[selData->index].endpoint_indexes[j]].vertex.x =
                            x + selData->offsets[j][0] * DIV;
                        EndpointList[PolygonList[selData->index].endpoint_indexes[j]].vertex.y =
                            y + selData->offsets[j][1] * DIV;
                    }
                }
                //objects
                for(int i = 0; i < (int)theApp.selectGroupInformation.selObjects.size(); i ++){
                    struct SelObject *selData = &theApp.selectGroupInformation.selObjects[i];
                    SavedObjectList[selData->index].location.x = x + selData->offset[0] * DIV;
                    SavedObjectList[selData->index].location.y = y + selData->offset[1] * DIV;
                }
                
            }
        }
    }
    Invalidate(FALSE);
    theApp.oldMousePoint = point;

    CView::OnMouseMove(nFlags, point);
}

//左ボタン上げ
void CMapEditorSDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    theApp.isPressLButtonWithCtrl = false;
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
        theApp.selectGroupInformation.clear();

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
                struct SelPoint selData;
                selData.index = i;
                //オフセットは次に左ボタンを下げたときに設定する
                theApp.selectGroupInformation.points.push_back(selData);
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
                struct SelLine selData;
                selData.index = i;
                //オフセットは次に左ボタンを下げたときに設定する
                theApp.selectGroupInformation.lines.push_back(selData);
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
                struct SelPolygon selData;
                selData.index = i;
                //オフセットは次に左ボタンを下げたときに設定する
                theApp.selectGroupInformation.polygons.push_back(selData);
            }
        }

        //objects
        for(int i = 0; i < (int)SavedObjectList.size(); i ++){
            map_object* obj = &SavedObjectList[i];
            int x = obj->location.x;
            int y = obj->location.y;
            int drawX = (x + OFFSET_X_WORLD)/DIV + OFFSET_X_VIEW;
            int drawY = (y + OFFSET_Y_WORLD)/DIV + OFFSET_Y_VIEW;

            //チェック
            if(isPointInRect<int>(drawX, drawY, point.x, point.y,
                theApp.selectStartPoint.x, theApp.selectStartPoint.y))
            {
                //追加
                struct SelObject selData;
                selData.index = i;
                //オフセットは次に左ボタンを下げたときに設定する
                theApp.selectGroupInformation.selObjects.push_back(selData);
            }
        }

        //選択したかどうか
        bool isSelected = false;
        if(theApp.selectGroupInformation.points.size() > 0 ||
            theApp.selectGroupInformation.selObjects.size() > 0){
                isSelected = true;
        }
        theApp.selectGroupInformation.setSelected(isSelected);

        //if selecting is only 1 object. setup property dialog
        if(theApp.selectGroupInformation.isSelectOneObject()){
            //オブジェクト情報更新
            theApp.objectPropertyDialog->setupDialog(theApp.selectGroupInformation.selObjects[0].index);
        }else if(theApp.selectGroupInformation.isSelectOnePoint()){
        }else if(theApp.selectGroupInformation.isSelectOneLine()){
        }else if(theApp.selectGroupInformation.isSelectOnePolygon()){
            theApp.polygonPropertyDialog->setupDialog(theApp.selectGroupInformation.polygons[0].index);
        }
    }

    theApp.isSelectingGroup = false;
    Invalidate(FALSE);
    ReleaseCapture();

    CView::OnLButtonUp(nFlags, point);
}
