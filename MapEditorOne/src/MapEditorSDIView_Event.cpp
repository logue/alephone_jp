#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"

/**
    簡易バージョン
*/
void getViewPointFromWorldPoint2D(world_point2d wpoint, int* dest){
    int offset[2];
    theApp.gridManager->getOffset(offset);
    int div = theApp.gridManager->getZoomDivision();
    hpl::aleph::map::getViewPointFromWorldPoint2D(wpoint, dest, OFFSET_X_WORLD, OFFSET_Y_WORLD,
        div, offset[0], offset[1]);
}
void getViewPointFromWorldPoint2D(int x, int y, int* dest){
    world_point2d point = {x,y};
    getViewPointFromWorldPoint2D(point, dest);
}
world_point2d getWorldPoint2DFromViewPoint(int x, int y){
    int offset[2];
    theApp.gridManager->getOffset(offset);
    int div = theApp.gridManager->getZoomDivision();
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(x, y, OFFSET_X_WORLD, OFFSET_Y_WORLD, div, offset[0], offset[1]);
    return wpoint;
}

//static void getWorldPointFromViewPoint2D(

/**
    マウス座標が点に近いかどうかを調べて選択情報に設定
    @param mousePoint view座標系のマウスポイント座標
    @param offsetViewX view座標系のズレ補正
    @param offsetViewY view座標系のズレ補正
    @param offsetWorldX world座標系のズレ補正
    @param offsetWorldY world座標系のズレ補正
    @param div ズーム
    @param distance 距離の閾値。これ以下なら選択
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
    選択開始位置を記憶
*/
void CMapEditorSDIView::setStartPointForSelectGroup(int px, int py){
    theApp.selectStartPoint.x = px;
    theApp.selectStartPoint.y = py;
    theApp.isSelectingGroup = true;
}

/**
    左ボタンをドローモードで押す
*/
void CMapEditorSDIView::doLButtonDownDrawMode(UINT nFlags, CPoint &point)
{
    int viewOffset[2];
    theApp.gridManager->getOffset(viewOffset);
    int OFFSET_X_VIEW = viewOffset[0];
    int OFFSET_Y_VIEW = viewOffset[1];
    int DIV = theApp.gridManager->getZoomDivision();

    if(theApp.selectingToolType == TI_ARROW){
        //selecting tool = TI_ARROW
        //矢印ツール時

        if(!(nFlags & MK_CONTROL)){
            //コントロールキーを押さずに
            //clik without modify key

            if(theApp.selectDatas.isSelected())
            {
                //複数を選択中

                if(isPointInSelection(point.x, point.y,
                    OFFSET_X_VIEW, OFFSET_Y_VIEW, OFFSET_X_WORLD, OFFSET_Y_WORLD,
                    POINT_DISTANCE_EPSILON, LINE_DISTANCE_EPSILON, OBJECT_DISTANCE_EPSILON,
                    &theApp.selectDatas, theApp.viewHeightMax, theApp.viewHeightMin,
                    DIV))
                {
                    //複数選択をクリック

                    //click on selecting group
                    //->remember offset, ready to move
                    this->setupSelectDataGroupOffsets(point);

                }else{
                    //release all selection
                    theApp.selectDatas.clear();
                }

            }else {
                //ctrlを押さずにクリック→選択
                //グループ選択ではない
                //シフトキーと一緒に押した？（選択の追加）
                bool isWithShift = (nFlags & MK_SHIFT) != 0;
                if(!isWithShift){
                    //シフトキーを押さずにクリックしたらいったん解放する
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
                            int drawViewP[2];
                            getViewPointFromWorldPoint2D(obj->location.x, obj->location.y, drawViewP);

                            int offset[2];
                            offset[0] = drawViewP[0] - point.x;
                            offset[1] = drawViewP[1] - point.y;
                            theApp.selectDatas.addSelObject(i, offset);
                            //選択したオブジェクトの情報を表示
                            theApp.objectPropertyDialog->setupDialog(i);
                            break;
                        }
                    }
                }
                if(theApp.selectDatas.isSelected()){
                    //object property
                    //オブジェクトプロパティウインドウを表示する
                    theApp.objectPropertyDialog->ShowWindow(TRUE);

                }else{
                    //no selection
                    theApp.objectPropertyDialog->setSelectedObjectIndex(-1);
                }

                ////////////////////
                //points
                if(!theApp.selectDatas.isSelected()){
                    checkSelectPoint(point, viewOffset[0], viewOffset[1],
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
                            //接近している
                            //オフセット記録
                            int offset[2][2];
                            offset[0][0] = 
                                (begin->vertex.x + OFFSET_X_WORLD) / DIV + viewOffset[0]
                                - point.x;
                            offset[0][1] = 
                                (begin->vertex.y + OFFSET_Y_WORLD) / DIV + viewOffset[1]
                                - point.y;
                            offset[1][0] = 
                                (end->vertex.x + OFFSET_X_WORLD) / DIV + viewOffset[0]
                                - point.x;
                            offset[1][1] = 
                                (end->vertex.y + OFFSET_Y_WORLD) / DIV + viewOffset[1]
                                - point.y;
                            theApp.selectDatas.addSelLine(i, offset);

                            break;
                        }
                    }
                }

                if(theApp.selectDatas.isSelected()){
                    //線プロパティ表示
                }else{
                    //非表示
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
                            getViewPointFromWorldPoint2D(EndpointList[polygon->endpoint_indexes[j]].vertex, drawPoint);
                            int drawX = drawPoint[0];
                            int drawY = drawPoint[1];
                            offset[j][0] = drawX - point.x;
                            offset[j][1] = drawY - point.y;
                        }

                        theApp.selectDatas.addSelPolygon(index, offset, num);
                    }
                }

                //////////////////////////////////
                //ここからの処理はほかよりも後に書く
                if(!theApp.selectDatas.isSelected()){
                    //選択されなかった
                    //no selection found

                    //範囲選択
                    //始点登録
                    //
                    setStartPointForSelectGroup(point.x, point.y);

                    theApp.selectDatas.clear();
                }else{
                    theApp.isSelectingGroup = false;
                }
            }
        }
    }else if(theApp.selectingToolType == TI_FILL){
        //TODO

        //塗れるポリゴンっぽい線の集合を探す
        int* lines = new int[8];
        delete lines;
    }else if(theApp.selectingToolType == TI_HAND){
        //全体を移動
        //D&Dの部分で実装済み

    }else if( theApp.selectingToolType == TI_LINE){
        //線引きツール

#ifdef MAP_VIEWER
#else
        if(nFlags & MK_LBUTTON){
            theApp.selectDatas.clear();
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
        //オブジェクト配置ツール時
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

                //選択状態にする
                theApp.selectDatas.clear();

                int index = objectIndex;
                int offset[2] = {0,0};
                theApp.selectDatas.addSelObject(index, offset);

                //選択したオブジェクトの情報を表示
                theApp.objectPropertyDialog->setupDialog(objectIndex);
            }
        }
#endif

    }else if(theApp.selectingToolType == TI_TEXT){
        //テキスト入力ツール
#ifdef MAP_VIEWER
#else
        //add annotation
        //show dialog
        CAnnotationDialog dlg(this);
        if(dlg.DoModal() == IDOK){
            struct world_point2d world_point = hpl::aleph::map::getWorldPoint2DFromViewPoint(point.x, point.y,
                OFFSET_X_WORLD, OFFSET_Y_WORLD, DIV, OFFSET_X_VIEW, OFFSET_Y_VIEW);

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
        //規定ポリゴン作成ツール
#ifdef MAP_VIEWER
#else
        //set start point
        setStartPointForSelectGroup(point.x, point.y);
#endif
    }
}

/**
    セットアップ
*/
void CMapEditorSDIView::setupSelectDataGroupOffsets(POINT point)
{
    //points
    std::vector<struct hpl::aleph::map::SelPoint>* selpoints = theApp.selectDatas.getSelPoints();
    for(int i = 0; i < (int)selpoints->size(); i ++){
        endpoint_data* ep = &EndpointList[selpoints->at(i).index];
        //set pos to view
        int x = ep->vertex.x;
        int y = ep->vertex.y;
        //ビュー座標に変換
        int drawP[2];
        getViewPointFromWorldPoint2D(ep->vertex, drawP);

        //sub to offset
        selpoints->at(i).offset[0] = drawP[0] - point.x;
        selpoints->at(i).offset[1] = drawP[1] - point.y;
    }

    //lines
    std::vector<struct hpl::aleph::map::SelLine>* sellines = theApp.selectDatas.getSelLines();
    for(int i = 0; i < (int)sellines->size(); i ++){
        struct hpl::aleph::map::SelLine* selData = &sellines->at(i);
        line_data* line = &LineList[selData->index];
        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
        int beginViewP[2], endViewP[2];
        getViewPointFromWorldPoint2D(begin->vertex, beginViewP);
        getViewPointFromWorldPoint2D(end->vertex, endViewP);
        //set offsets
        sellines->at(i).offset[0][0] = beginViewP[0] - point.x;
        sellines->at(i).offset[0][1] = beginViewP[1] - point.y;
        sellines->at(i).offset[1][0] = endViewP[0] - point.x;
        sellines->at(i).offset[1][1] = endViewP[1] - point.y;

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
            int drawViewP[2];
            getViewPointFromWorldPoint2D(
                EndpointList[polygon->endpoint_indexes[j]].vertex, drawViewP);
            selData->offset[j][0] = drawViewP[0] - point.x;
            selData->offset[j][1] = drawViewP[1] - point.y;
        }
    }

    //objects
    std::vector<struct hpl::aleph::map::SelObject>* selobjects = theApp.selectDatas.getSelObjects();
    for(int i = 0; i < (int)selobjects->size(); i ++){
        struct hpl::aleph::map::SelObject* selData = &selobjects->at(i);
        map_object* obj = &SavedObjectList[selData->index];
        //set pos to view
        int drawViewP[2];
        getViewPointFromWorldPoint2D(obj->location.x, obj->location.y, drawViewP);

        //sub to offset
        selData->offset[0] = drawViewP[0] - point.x;
        selData->offset[1] = drawViewP[1] - point.y;
    }
}


/**
    ポリゴンを選択したかどうか判断します
*/
void checkPolygonSelect(UINT nFlags, CPoint point)
{
    theApp.selectDatas.clear();

    struct world_point2d world_point = getWorldPoint2DFromViewPoint(point.x, point.y);

    //ポリゴンの中にマウスポインタが入っているか
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

//左ボタン下げ
void CMapEditorSDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(nFlags & MK_CONTROL){
        //コントロールボタンを押している
        theApp.isPressLButtonWithCtrl = true;
    }else{
        theApp.isPressLButtonWithCtrl = false;
    }
    theApp.gridManager->setNewMousePoint(point.x, point.y);

    int offset[2];
    theApp.gridManager->getOffset(offset);
    int OFFSET_X_VIEW = offset[0];
    int OFFSET_Y_VIEW = offset[1];
    int DIV = theApp.gridManager->getZoomDivision();


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
            //Ctrlを押しながら
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

/**
    オフセット移動
*/
void CMapEditorSDIView::moveMapOffset(int newPx, int newPy){
    int oldMousePoint[2];
    theApp.gridManager->getOldMousePoint(oldMousePoint);
    int deltaX = newPx - oldMousePoint[0];
    int deltaY = newPy - oldMousePoint[1];

    int offset[2];
    theApp.gridManager->getOffset(offset);
    offset[0] += deltaX;
    offset[1] += deltaY;
    theApp.gridManager->setOffset(offset[0], offset[1]);
}
/****************************************************************/
//マウス移動
void CMapEditorSDIView::OnMouseMove(UINT nFlags, CPoint point)
{
    setCursor();

    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    theApp.gridManager->setNewMousePoint(point.x, point.y);

    const int DIV = theApp.gridManager->getZoomDivision();
    int offset[2];
    theApp.gridManager->getOffset(offset);
#ifdef MAP_VIEWER
    //クリックしていれば移動
    if(nFlags & MK_LBUTTON &&
        (nFlags & MK_CONTROL && theApp.isPressLButtonWithCtrl ||
        theApp.getEditMode() == EM_DRAW && theApp.selectingToolType == TI_HAND ||
//        theApp.getEditMode() == EM_DRAW && (theApp.selectingToolType == TI_ARROW)||
        nFlags & MK_CONTROL)){
        moveMapOffset(point.x, point.y);
    }
#else
    if(nFlags & MK_LBUTTON && ((nFlags & MK_CONTROL && theApp.isPressLButtonWithCtrl) ||
        (theApp.getEditMode() == EM_DRAW && theApp.selectingToolType == TI_HAND)))
    {
        //コントロールキー押しながら左→オフセット移動
        //Control+L=move map view
        moveMapOffset(point.x, point.y);
    }else{
        if(theApp.getEditMode() == EM_DRAW){
            //ドローモード
            if(theApp.selectingToolType == TI_ARROW){
                //矢印ツール
                if(!theApp.isPressLButtonWithCtrl && 
                    (nFlags & MK_LBUTTON) && /*!(nFlags & MK_CONTROL) && */
                    !(nFlags & MK_CONTROL))
                {
                    //選択物の移動
                    //world position of mouse pointer
                    world_point2d worldP = getWorldPoint2DFromViewPoint(point.x, point.y);
                    int x = worldP.x; //(point.x - theApp.offset.x) * DIV - OFFSET_X_WORLD;
                    int y = worldP.y; //(point.y - theApp.offset.y) * DIV - OFFSET_Y_WORLD;
                    if(theApp.selectDatas.isSelected()){
                        //グループを選択している
                        //->グループを移動
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
                //点を踏んでないか確認
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
                    if(hpl::aleph::map::isSelectPoint(world_point, point->vertex, POINT_DISTANCE_EPSILON * theApp.gridManager->getZoomDivision()))
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
    theApp.gridManager->setNewMousePoint(point.x, point.y);

    CView::OnMouseMove(nFlags, point);
}

//左ボタン上げ
void CMapEditorSDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

    //Ctrlを押しながら左ボタンを押しているか
    theApp.isPressLButtonWithCtrl = false;

    if(theApp.selectingToolType == TI_ARROW){
        //矢印ツール

        bool okSelect = false;
        if(theApp.selectDatas.isSelectOneObject()){
            //オブジェクト情報更新
            theApp.objectPropertyDialog->setupDialog(theApp.selectDatas.getSelObjects()->at(0).index);
        }else if(theApp.selectDatas.isSelectOnePoint()){
        }else if(theApp.selectDatas.isSelectOneLine()){
        }else if(theApp.selectDatas.isSelectOnePolygon()){
            //ポリゴン情報更新
            theApp.polygonPropertyDialog->setupDialog(theApp.selectDatas.getSelPolygons()->at(0).index);
        }

        if(theApp.isSelectingGroup){
            //範囲選択中


            //if selecting is only 1 object. setup property dialog

            //int OFFSET_X_VIEW = theApp.offset.x;
            //int OFFSET_Y_VIEW = theApp.offset.y;
            theApp.selectDatas.clear();

            int DIV = theApp.gridManager->getZoomDivision();
            //選択されているものをリストに登録する
            //点
            for(int i = 0; i < (int)EndpointList.size(); i ++){
                endpoint_data* ep = &EndpointList[i];
                int x = ep->vertex.x;
                int y = ep->vertex.y;
                int drawP[2];
                getViewPointFromWorldPoint2D(ep->vertex, drawP);
                int drawX = drawP[0];
                int drawY = drawP[1];
                //チェック
                if(hpl::math::isPointInRect<int>(drawX, drawY, point.x, point.y,
                    theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                {
                    //追加
                    int index = i;
                    int offset[2] = {0,0};
                    //オフセットは次に左ボタンを下げたときに設定する
                    theApp.selectDatas.addSelPoint(index, offset);
                }
            }
            //線
            for(int i = 0; i < (int)LineList.size(); i ++){
                line_data* line = &LineList[i];
                endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
                endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
                int vpoint[2];
                getViewPointFromWorldPoint2D(begin->vertex, vpoint);
                int x0 = vpoint[0];
                int y0 = vpoint[1];
                getViewPointFromWorldPoint2D(end->vertex, vpoint);
                int x1 = vpoint[0];
                int y1 = vpoint[1];
                if(hpl::math::isLineInRect(x0, y0, x1, y1, point.x, point.y,
                    theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                {
                    int index = i;
                    int offset[2][2] = {{0,0},{0,0}};
                    //オフセットは次に左ボタンを下げたときに設定する
                    theApp.selectDatas.addSelLine(index, offset);
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
                    int vpoint[2];
                    getViewPointFromWorldPoint2D(ep->vertex, vpoint);
                    int drawX = vpoint[0];
                    int drawY = vpoint[1];
                    if(!hpl::math::isPointInRect<int>(drawX, drawY, point.x, point.y,
                        theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                    {
                        inner = false;
                        break;
                    }
                }
                if(inner){
                    //登録
                    int index = i;
                    int offset[8][2];
                    memset(offset, 0, sizeof(int) * 8 * 2);
                    int num = 8;
                    //オフセットは次に左ボタンを下げたときに設定する
                    theApp.selectDatas.addSelPolygon(index, offset, num);
                }
            }

            //objects
            for(int i = 0; i < (int)SavedObjectList.size(); i ++){
                map_object* obj = &SavedObjectList[i];
                int x = obj->location.x;
                int y = obj->location.y;
                int vpoint[2];
                getViewPointFromWorldPoint2D(obj->location.x, obj->location.y, vpoint);
                int drawX = vpoint[0];
                int drawY = vpoint[1];

                //チェック
                if(hpl::math::isPointInRect<int>(drawX, drawY, point.x, point.y,
                    theApp.selectStartPoint.x, theApp.selectStartPoint.y))
                {
                    //追加
                    int index = i;
                    int offset[2] = {0,0};
                    //オフセットは次に左ボタンを下げたときに設定する
                    theApp.selectDatas.addSelObject(index, offset);
                }
            }

            //選択したかどうか
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
    //ボタンアップ→選択解除
    theApp.isSelectingGroup = false;
    Invalidate(FALSE);
    ReleaseCapture();

    CView::OnLButtonUp(nFlags, point);
}

// press event of Right button
void CMapEditorSDIView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

    theApp.gridManager->setNewMousePoint(point.x, point.y);
/*
    int OFFSET_X_VIEW = theApp.offset.x;
    int OFFSET_Y_VIEW = theApp.offset.y;
    */
    int DIV = theApp.gridManager->getZoomDivision();

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
        //縮小
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
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

    Invalidate(FALSE);
    ReleaseCapture();
    CView::OnRButtonUp(nFlags, point);
}

