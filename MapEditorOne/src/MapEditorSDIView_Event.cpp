#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"

static bool checkSelectPoint(POINT& mousePoint,
                             int offsetViewX, int offsetViewY,
                             int offsetWorldX, int offsetWorldY,
                             int div,
                             int distance)
{
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = &EndpointList[i];
        int x = ep->vertex.x;
        int y = ep->vertex.y;
        if(isSelectPoint(mousePoint.x, mousePoint.y, x, y,
            offsetViewX, offsetViewY, offsetWorldX, offsetWorldY, div, distance))
        {
            theApp.selectType = _selected_point;
            theApp.selectIndex = i;
            return true;
        }
    }
    return false;
}


//左ボタン下げ
void CMapEditorSDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(nFlags & MK_CONTROL){
        theApp.isPressLButtonWithShift = true;
    }else{
        theApp.isPressLButtonWithShift = false;
    }
    theApp.nowMousePoint = point;
    theApp.oldMousePoint = point;

    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    int DIV = theApp.zoomDivision;
    int POINT_DISTANCE_EPSILON = 5;
    int OBJECT_DISTANCE_EPSILON = 8;
    int LINE_DISTANCE_EPSILON = 5;

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
                bool selected = false;

                theApp.isSelectingGroup = false;

                //objects
                {
                    for(int i = 0; i < (int)SavedObjectList.size() && !selected; i ++){
                        map_object* obj = &(SavedObjectList[i]);
                        int type = obj->type;
                        int facing = obj->facing;
                        int x = obj->location.x;
                        int y = obj->location.y;
                        int z = obj->location.z;
                        if(isSelectPoint(point.x, point.y,
                            x, y, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                            OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, OBJECT_DISTANCE_EPSILON)){

                            theApp.selectType = _selected_object;
                            theApp.selectIndex = i;
                            //選択したオブジェクトの情報を表示
                            theApp.objectPropertyDialog->setupDialog(obj);
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
                    //theApp.objectPropertyDialog->setupDialog(-1);
                }

                ////////////////////
                //points
                if(!selected){
                    selected = checkSelectPoint(point, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                        OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, POINT_DISTANCE_EPSILON);
                }
                if(selected){
                }

                //////////////////
                //lines
                if(!selected){
                    for(int i = 0; i < (int)LineList.size(); i ++){
                        line_data* line = &LineList[i];
                        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
                        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
                        if(isSelectLine(point.x, point.y, begin->vertex.x, begin->vertex.y,
                            end->vertex.x, end->vertex.y, OFFSET_X_VIEW, OFFSET_Y_VIEW,
                            OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, LINE_DISTANCE_EPSILON)){
                            //接近している
                            theApp.selectType = _selected_line;
                            theApp.selectIndex = i;
                            selected = true;
                            //オフセット記録
                            theApp.polygonPointNum = 2;
                            theApp.polygonPoints[0].x = 
                                (begin->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                                - point.x;
                            theApp.polygonPoints[0].y = 
                                (begin->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                                - point.y;
                            theApp.polygonPoints[1].x = 
                                (end->vertex.x + OFFSET_X_WORLD) / DIV + OFFSET_X_VIEW
                                - point.x;
                            theApp.polygonPoints[1].y = 
                                (end->vertex.y + OFFSET_Y_WORLD) / DIV + OFFSET_Y_VIEW
                                - point.y;


                            break;
                        }
                    }
                }

                if(selected){
                    //線プロパティ表示
                }else{
                    //非表示
                }

                /////////////////
                //polygons
                if(!selected){
                    for(int i = 0; i < (int)PolygonList.size(); i ++){
                        struct world_point2d world_point;
                        world_point.x = (world_distance)((point.x - OFFSET_X_VIEW) * DIV - OFFSET_X_WORLD);
                        world_point.y = (world_distance)((point.y - OFFSET_Y_VIEW) * DIV - OFFSET_Y_WORLD);

                        if(point_in_polygon(i, &world_point)){
                            theApp.selectType = _selected_polygon;
                            theApp.selectIndex = i;
                            selected = true;

                            //set offset
                            polygon_data *polygon = &PolygonList[i];
                            int num = polygon->vertex_count;
                            theApp.polygonPointNum = num;
                            for(int j = 0; j < num; j ++){
                                int drawX = (EndpointList[polygon->endpoint_indexes[j]].vertex.x + OFFSET_X_WORLD) / DIV
                                    + OFFSET_X_VIEW;
                                int drawY = (EndpointList[polygon->endpoint_indexes[j]].vertex.y + OFFSET_Y_WORLD) / DIV
                                    + OFFSET_Y_VIEW;
                                theApp.polygonPoints[j].x = drawX - point.x;
                                theApp.polygonPoints[j].y = drawY - point.y;
                            }
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
        }
    }else if(theApp.selectingToolType == TI_FILL){
    }else if(theApp.selectingToolType == TI_HAND){
    }else if( theApp.selectingToolType == TI_LINE){
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
                //オブジェクト情報
                map_object obj;
                obj.type = theApp.objectPropertyDialog->objectTypeCmb.GetCurSel();
                obj.index = theApp.objectPropertyDialog->objectClassedTypeCmb.GetCurSel();
                obj.facing = getIntegerNum(&theApp.objectPropertyDialog->objectFacingNum);
                obj.flags = theApp.objectPropertyDialog->getFlags();
                obj.polygon_index = i;
                obj.location.x = world_point.x;
                obj.location.y = world_point.y;
                //calc height
                if(obj.flags & _map_object_hanging_from_ceiling){
                    obj.location.z = polygon->ceiling_height;
                }else{
                    obj.location.z = polygon->floor_height;
                }
                //追加
                SavedObjectList.push_back(obj);
            }
        }
    }else if(theApp.selectingToolType == TI_TEXT){
    }else if(theApp.selectingToolType == TI_POLYGON){

    }
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
        if(nFlags & MK_LBUTTON && nFlags & MK_CONTROL && theApp.isPressLButtonWithShift){
            //Control+L=move map view
            //差
            int deltaX = point.x - theApp.oldMousePoint.x;
            int deltaY = point.y - theApp.oldMousePoint.y;
            theApp.offset.x += deltaX;
            theApp.offset.y += deltaY;
            this->Invalidate(FALSE);
            
        }else if(!theApp.isPressLButtonWithShift && 
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
            }else if(!theApp.isSelectingGroup && theApp.selectType != _no_selected){
                //single selection
                //->move it
                if(theApp.selectType == _selected_object){
                    SavedObjectList[theApp.selectIndex].location.x = x;
                    SavedObjectList[theApp.selectIndex].location.y = y;
                    //オブジェクト情報更新
                    theApp.objectPropertyDialog->setupDialog(&SavedObjectList[theApp.selectIndex]);
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
                }else if(theApp.selectType == _selected_polygon){
                    for(int j = 0; j < theApp.polygonPointNum; j ++){
                        EndpointList[PolygonList[theApp.selectIndex].endpoint_indexes[j]].vertex.x =
                            (world_distance)(x + theApp.polygonPoints[j].x * theApp.zoomDivision);
                        EndpointList[PolygonList[theApp.selectIndex].endpoint_indexes[j]].vertex.y =
                            (world_distance)(y + theApp.polygonPoints[j].y * theApp.zoomDivision);
                    }
                }
            }
            Invalidate(FALSE);
        }
    }
    theApp.oldMousePoint = point;

    CView::OnMouseMove(nFlags, point);
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
        theApp.selectGroupInformation.clear();
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
    }

    theApp.isSelectingGroup = false;
    Invalidate(FALSE);
    ReleaseCapture();

    CView::OnLButtonUp(nFlags, point);
}
