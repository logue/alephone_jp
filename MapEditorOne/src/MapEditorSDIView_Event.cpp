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
    }
    CView::OnLButtonDown(nFlags, point);
    SetCapture();
}
