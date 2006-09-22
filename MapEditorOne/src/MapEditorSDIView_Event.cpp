#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"


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

    if(theApp.selectingToolType == TI_ARROW){
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
                //オブジェクト情報
                int otype = theApp.objectPropertyDialog->objectTypeCmb.GetCurSel();
                int oindex = theApp.objectPropertyDialog->objectClassedTypeCmb.GetCurSel();
                int facing = getIntegerNum(&theApp.objectPropertyDialog->objectFacingNum);
                int col = 0, clut = 0, sh = 0;
                if(otype == _saved_monster){
                    col = GET_COLLECTION(monster_definitions[oindex].collection);
                    clut = GET_COLLECTION_CLUT(monster_definitions[oindex].collection);
                }
                int collection = BUILD_COLLECTION(col, clut);
                int shapes = BUILD_DESCRIPTOR(collection, sh);
                //オブジェクト配置
                new_map_object2d(&world_point, i, shapes,
                    facing);
            }
        }
    }else if(theApp.selectingToolType == TI_TEXT){
    }else if(theApp.selectingToolType == TI_POLYGON){

    }
    CView::OnLButtonDown(nFlags, point);
    SetCapture();
}

//マウス移動
void CMapEditorSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    theApp.nowMousePoint = point;

    if(theApp.selectingToolType == TI_ARROW){
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
            if(theApp.selectGroupInformation.isSelected()){
                //グループを選択している
                //->グループを移動

            }else if(!theApp.isSelectingGroup && theApp.selectType != _no_selected){
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
