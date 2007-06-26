#include "MapEditorMainFrame.h"
#include "AnnotationDialog.h"

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/**
    左ボタンを押したときに呼ばれる
*/
void MapEditorMainFrame::OnLeftDown(wxMouseEvent &ev)
{
    //カーソル設定
    wxGetApp().setCursor();
    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
    bool shift = ev.ShiftDown();
    bool ctrl = ev.ControlDown();

//    int toolType = wxGetApp().getEventManager()->getToolType();

    if(ctrl){
        Refresh();
        return;
    }
    switch(wxGetApp().getEventManager()->getEditModeType()){
    case EditModeType::EM_DRAW:
        doLButtonOnDrawMode(ev);
        break;
    case EditModeType::EM_POLYGON_TYPE:
        doLButtonOnPolygonMode(ev);
        break;
    case EditModeType::EM_FLOOR_HEIGHT:
        doLButtonOnFloorHeightMode(ev);
        break;
    case EditModeType::EM_CEILING_HEIGHT:
        doLButtonOnCeilingHeightMode(ev);
        break;
    case EditModeType::EM_FLOOR_LIGHT:
        doLButtonOnFloorLightMode(ev);
        break;
    case EditModeType::EM_CEILING_LIGHT:
        doLButtonOnCeilingLightMode(ev);
        break;
    case EditModeType::EM_MEDIA:
        doLButtonOnMediaMode(ev);
        break;
    case EditModeType::EM_FLOOR_TEXTURE:
        doLButtonOnFloorTextureMode(ev);
        break;
    case EditModeType::EM_CEILING_TEXTURE:
        doLButtonOnCeilingTextureMode(ev);
        break;
    }
    Refresh();
}
void MapEditorMainFrame::doLButtonOnDrawMode(wxMouseEvent& ev)
{
    int tool = wxGetApp().getEventManager()->getToolType();
    switch(tool){
    case ToolType::TI_ARROW:
        doLButtonOnArrowTool(ev);
        break;
    case ToolType::TI_FILL:
        doLButtonOnFillTool(ev);
        break;
    case ToolType::TI_HAND:
        doLButtonOnHandTool(ev);
        break;
    case ToolType::TI_LINE:
        doLButtonOnLineTool(ev);
        break;
    case ToolType::TI_MAGNIFY:
        doLButtonOnMagnifyTool(ev);
        break;
    case ToolType::TI_SKULL:
        doLButtonOnSkullTool(ev);
        break;
    case ToolType::TI_TEXT:
        doLButtonOnTextTool(ev);
        break;
    case ToolType::TI_POLYGON:
        doLButtonOnPolygonTool(ev);
        break;
    default:
        hpl::error::halt("Invalid tool type");
    }
}

void MapEditorMainFrame::doLButtonOnArrowTool(wxMouseEvent& ev)
{
    //選択データ
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
    
    //グリッドマネージャー
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    //ビューオフセット
    int voffset[2];
    vmgr->getOffset(voffset);
    int div = vmgr->getZoomDivision();

    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
    int mx = ev.m_x;
    int my = ev.m_y;

    if(sel->isSelected()){
        //既に選択中

        //マウス座標が選択部分に含まれるかチェック
        if(hpl::aleph::map::isPointInSelection(mx, my,
            voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD,
            POINT_DISTANCE_EPSILON, LINE_DISTANCE_EPSILON, OBJECT_DISTANCE_EPSILON,
            sel, zMax, zMin, div))
        {
            //選択部分をクリックしている
            //→オフセットを設定する
            //<en> clicked on selection datas
            //-> set offsets
            this->setupSelectDataGroupOffsets(mx, my);
            return;
        }else{
            //クリックしていない
            //→選択解除
            //<en> no click on selection datas
            //-> release all selections
            sel->clear();
        }
    }
    //何も選択していない状態
    //一つを選択できるか試してみます
    if(this->tryToSelectOneItem(ev)){
        //選択範囲は解除します
        wxGetApp().getEventManager()->setSelectingGroup(false);
    }else{
        //選択されなかった
        //範囲選択の開始
        wxGetApp().getEventManager()->setSelectGroupStartPoint(mx, my);
        //選択情報の解除
        sel->clear();
    }
}

/**
    オフセットを設定します
    @param mx,my ビュー座標の基点位置
*/
void MapEditorMainFrame::setupSelectDataGroupOffsets(int mx, int my)
{
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    //点 <en> points
    for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
        endpoint_data* ep = get_endpoint_data(sel->getSelPoints()->at(i).index);
        //ビュー座標に変換
        int vpoint[2];
        wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);

        //引き算
        sel->getSelPoints()->at(i).offset[0] = vpoint[0] - mx;
        sel->getSelPoints()->at(i).offset[1] = vpoint[1] - my;
    }

    //線 <en> lines
    for(int i = 0; i < (int)sel->getSelLines()->size(); i ++){
        line_data* line = get_line_data(sel->getSelLines()->at(i).index);
        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
        int vpointStart[2];
        int vpointEnd[2];
        wxGetApp().getViewPointFromWorldPoint(begin->vertex, vpointStart);
        wxGetApp().getViewPointFromWorldPoint(end->vertex, vpointEnd);

        //オフセット設定
        sel->getSelLines()->at(i).offset[0][0] = vpointStart[0] - mx;
        sel->getSelLines()->at(i).offset[0][1] = vpointStart[1] - my;
        sel->getSelLines()->at(i).offset[1][0] = vpointEnd[0] - mx;
        sel->getSelLines()->at(i).offset[1][1] = vpointEnd[1] - my;
    }

    //ポリゴン
    for(int i = 0; i < (int)sel->getSelPolygons()->size(); i ++){
        hpl::aleph::map::SelPolygon* selpoly = &sel->getSelPolygons()->at(i);
        polygon_data* poly = get_polygon_data(selpoly->index);
        int n = poly->vertex_count;
        selpoly->num = n;
        for(int j = 0; j < n; j ++){
            int vpoint[2];
            endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[j]);
            wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);

            //オフセット
            selpoly->offset[j][0] = vpoint[0] - mx;
            selpoly->offset[j][1] = vpoint[1] - my;
        }
    }

    //オブジェクト
    for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
        map_object* obj = &SavedObjectList[sel->getSelObjects()->at(i).index];
        //ビュー座標に変換
        int vpoint[2];
        wxGetApp().getViewPointFromWorldPoint(obj->location.x, obj->location.y, vpoint);

        //引き算
        sel->getSelObjects()->at(i).offset[0] = vpoint[0] - mx;
        sel->getSelObjects()->at(i).offset[1] = vpoint[1] - my;
    }

}

/**
    @param ev
    @return 選択に成功した場合真
*/
bool MapEditorMainFrame::tryToSelectOneItem(wxMouseEvent& ev)
{
    //シフトキー
    bool shift = ev.ShiftDown();

    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
    //イベントマネージャー
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();

    //ビューオフセット
    int voffset[2];
    vmgr->getOffset(voffset);
    int div = vmgr->getZoomDivision();

    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
    int mx = ev.m_x;
    int my = ev.m_y;

    if(!shift){
        //シフトキーを押さずにクリックしたら一旦解放する
        sel->clear();
        emgr->setSelectingGroup(false);
    }

    //選択の優先順位は
    //1:オブジェクト
    //2:点
    //3:線
    //4:ポリゴン


    //オブジェクト
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        map_object* obj = &SavedObjectList[i];
        int x = obj->location.x;
        int y = obj->location.y;
        int z = obj->location.z;

        //高さが範囲外かどうか
        if(z > zMax || z < zMin){
            continue;
        }

        //点選択検査
        if(hpl::aleph::map::isSelectPoint(mx, my,
            x, y, voffset[0], voffset[1],
            OFFSET_X_WORLD, OFFSET_Y_WORLD, div, OBJECT_DISTANCE_EPSILON))
        {
            //
            int vpoint[2];
            wxGetApp().getViewPointFromWorldPoint(x, y, vpoint);
            int offset[2];
            offset[0] = vpoint[0] - mx;
            offset[1] = vpoint[1] - my;
            sel->addSelObject(i, offset);
            //オブジェクトのプロパティ・ダイアログを表示する
            //TODO
            this->objPropDialog.setObjIndex(i);
            this->objPropDialog.Show(true);
            return true;
        }
    }

    //no obj selected
    //TODO 選択ID関連の実装
    this->objPropDialog.setObjIndex(NONE);


    //////////
    //点
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = get_endpoint_data(i);

        //高さチェック
        int floor = ep->highest_adjacent_floor_height;
        int ceiling = ep->lowest_adjacent_ceiling_height;
        if(floor > zMax || ceiling < zMin){
            continue;
        }
        if(hpl::aleph::map::isSelectPoint(mx, my,
            ep->vertex.x, ep->vertex.y,
            voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD,
            div, POINT_DISTANCE_EPSILON))
        {
            //見つかった
            int vpoint[2];
            wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);
            int offset[2];
            offset[0] = vpoint[0] - mx;
            offset[1] = vpoint[1] - my;
            sel->addSelPoint(i, offset);
            return true;
        }
    }

    /////////////////////////
    //lines
    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data* line = get_line_data(i);
        endpoint_data* start = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

        //高さチェック
        int floor = line->highest_adjacent_floor;
        int ceiling = line->lowest_adjacent_ceiling;
        if(floor > zMax || ceiling < zMin){
            continue;
        }

        if(hpl::aleph::map::isSelectLine(mx, my,
            start->vertex.x, start->vertex.y, end->vertex.x, end->vertex.y,
            voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, LINE_DISTANCE_EPSILON))
        {
            //選択
            int vstart[2];
            int vend[2];
            wxGetApp().getViewPointFromWorldPoint(start->vertex, vstart);
            wxGetApp().getViewPointFromWorldPoint(end->vertex, vend);

            int offset[2][2];
            offset[0][0] = vstart[0] - mx;
            offset[0][1] = vstart[1] - my;
            offset[1][0] = vend[0] - mx;
            offset[1][1] = vend[1] - my;
            sel->addSelLine(i, offset);
            return true;
        }
    }

    //ポリゴン
    //TODO 高さ順にソートする
    int polyIndex = NONE;
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        if(hpl::aleph::map::isPointInPolygon(mx, my,
            i, OFFSET_X_WORLD, OFFSET_Y_WORLD, div,
            voffset[0], voffset[1]))
        {
            polyIndex = i;
            break;
        }
    }
    if(polyIndex != NONE){
        polygon_data* poly = get_polygon_data(polyIndex);
        int n = poly->vertex_count;
        int offset[MAXIMUM_VERTICES_PER_POLYGON][2];
        
        //ポリゴンプロパティ表示
        //TODO
        this->polyPropDialog.setPolyIndex(polyIndex);
        this->polyPropDialog.Show(true);

        //オフセット
        for(int j = 0; j < n; j ++){
            int vpoint[2];
            wxGetApp().getViewPointFromWorldPoint(get_endpoint_data(poly->endpoint_indexes[j])->vertex, vpoint);
            offset[j][0] = vpoint[0] - mx;
            offset[j][1] = vpoint[1] - my;
        }

        sel->addSelPolygon(polyIndex, offset, n);
        return true;
    }

    return false;
}


/////////////////////////////////////////////////////////////
void MapEditorMainFrame::doLButtonOnFillTool(wxMouseEvent& ev)
{
    //TODO
    //塗りつぶし可能なポリゴンデータを取得します
    //hp::aleph::map::getValidPolygons();
}
void MapEditorMainFrame::doLButtonOnHandTool(wxMouseEvent& ev)
{
    //MouseMotionに丸投げ
    
}
void MapEditorMainFrame::doLButtonOnLineTool(wxMouseEvent& ev)
{
    //線追加
#ifdef MAP_VIEWER
#else
    //選択解除
    wxGetApp().selectData.clear();

    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();

    int mx = ev.m_x;
    int my = ev.m_y;
    //世界座標にする
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mx, my);

    bool isFirst = wxGetApp().isFirstOfLineToAdd;

    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    
    int voffset[2];
    vmgr->getOffset(voffset);
    int div = wxGetApp().getViewGridManager()->getZoomDivision();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();

    //重なる点があるかどうかチェック
    int pointIndex = hpl::aleph::map::getSelectPointIndex(wpoint, POINT_DISTANCE_EPSILON, zMin, zMax);
    //重なる線があるか判定する
    int lineIndex = hpl::aleph::map::getSelectLineIndex(wpoint, LINE_DISTANCE_EPSILON, zMin, zMax);

    hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
    if(pointIndex != NONE)
    {
        //既存の点をクリックしている
        /*
        1:点の上でクリック
	        1:最初のクリック
		        前回クリック点の更新
	        2:二回目以降のクリック
		        1:既に線が存在している
			        何もしない
		        2:線は存在していない
			        線の追加
		        前回クリック点の更新
        */
        if(isFirst){
            //最初のクリック
            //始点とする
            wxGetApp().prevPointIndex = pointIndex;

        }else{
            //2回目以降のクリック
            //同じ点をクリックしているか？
            if(wxGetApp().prevPointIndex == pointIndex){
                //始点とする
            }else{
                //既に線が存在しているか？
                int lineIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(
                    wxGetApp().prevPointIndex, pointIndex);
                if(lineIndex != NONE){
                    //何もせず現在の点を始点とする
                    wxGetApp().prevPointIndex = pointIndex;
                }else{
                    //でなけば線を作成する
                    //TODO
                }
            }
        }

        //中継点・始点・終点にする
        wxGetApp().isFirstOfLineToAdd = false;
    }else{
        //線を踏んでいないかチェックします
        if(lineIndex != NONE){
            /*
                2:線の上でクリック
	                1:最初のクリック
		                1:ポリゴンに所属する線
			                警告を出して何もしない
		                2:所属しない線
			                その線を削除
			                点を追加
			                線の始点→新点を終点とした新線を追加
			                新点→線の終点を終点とした新線を追加
			                前回クリック点の更新
	                2:二回目以降のクリック
		                同上
            */
            line_data* line = get_line_data(lineIndex);
            assert(line != NULL);

            int newPointIndex = NONE;
            //ポリゴンに所属しているか確かめます
            if(line->clockwise_polygon_owner != NONE || 
                line->counterclockwise_polygon_owner != NONE)
            {
                //ポリゴンに属する線
                //警告を出す。線を分断したりしない
                hpl::error::caution("cannot divide line , because line belongs to polygon (line's index:%d, clockwise polygon's index:%d, counterclockwise polygon's index:%d)",
                    lineIndex, line->clockwise_polygon_owner, line->counterclockwise_polygon_owner);
                //独立した点を追加する
                endpoint_data ep;
                hpl::aleph::map::createPoint(wpoint, &ep, POINT_DISTANCE_EPSILON);
                newPointIndex = hpl::aleph::map::addEndpoint(ep);
                assert(newPointIndex != NONE);
            }else{
                //始点、終点の情報取得
                //endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
                //endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

                //線を削除
                smgr->deleteLine(lineIndex);
                smgr->updateDeletes();
                //点を追加
                endpoint_data ep;
                assert(hpl::aleph::map::createPoint(wpoint, &ep, POINT_DISTANCE_EPSILON));
                newPointIndex = hpl::aleph::map::addEndpoint(ep);
                assert(newPointIndex != NONE);
                endpoint_data *newEp = get_endpoint_data(newPointIndex);

                //始点→点の線を追加
                line_data newLine1;
                assert(hpl::aleph::map::createLine(line->endpoint_indexes[0], line->endpoint_indexes[1], &newLine1));
                int newLine1Index = hpl::aleph::map::addLine(newLine1);
                assert(newLine1Index != NONE);

                //点→終点の線を追加
                line_data newLine2;
                //TODO
            }
        }else{
            //新規追加
            if(wxGetApp().isFirstOfLineToAdd){
                //最初の点
                endpoint_data ep;
                assert(hpl::aleph::map::createPoint(wpoint, &ep, POINT_DISTANCE_EPSILON));

            }else{
                //点を追加
            }

            //点を追加してから線を追加する
        }
    }
    wxGetApp().isFirstOfLineToAdd = isFirst;

    //情報を更新する
    wxGetApp().getStockManager()->updateDeletes();
    
#endif
}
void MapEditorMainFrame::doLButtonOnMagnifyTool(wxMouseEvent& ev)
{
    bool shift = ev.ShiftDown();
    wxCommandEvent dummy;
    if(shift){
        //縮小
        this->OnZoomOut(dummy);
    }else{
        this->OnZoomIn(dummy);
    }
}
void MapEditorMainFrame::doLButtonOnSkullTool(wxMouseEvent& ev)
{
    //オブジェクト配置
#ifdef MAP_VIEWER
#else
    int mx = ev.m_x;
    int my = ev.m_y;
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mx, my);
    //点の中に入るポリゴンを取得します
    //std::vector<int> polyIndexes = hpl::aleph::map::getPolygonIndexesIncludePoint(wpoint);
    //TODO
#endif
}
void MapEditorMainFrame::doLButtonOnTextTool(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
    //アノテーション追加
    //ダイアログ準備
    AnnotationDialog dlg;
    map_annotation sample;
    //初期化
    memset(&sample, 0, SIZEOF_map_annotation);

    //マウス座標の位置に追加する
    int viewX = ev.m_x;
    int viewY = ev.m_y;
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(viewX, viewY);
    sample.location.x = wpoint.x;
    sample.location.y = wpoint.y;
    sample.polygon_index = NONE;

    //ダイアログ表示
    dlg.Create(this, ID_ANNOTATION_DIALOG, sample);
    if(dlg.ShowModal() == wxID_OK){
        //決定
        //アノテーションデータを取得
        map_annotation newAnnotation = dlg.getAnnotation();
        //追加
        hpl::aleph::map::addAnnotation(newAnnotation);
    }
#endif
}
void MapEditorMainFrame::doLButtonOnPolygonTool(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
    //範囲選択開始
    //TODO
    //wxGetApp().getEventManager()->
#endif
}

void MapEditorMainFrame::doLButtonOnPolygonMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnFloorHeightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnCeilingHeightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnFloorLightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnCeilingLightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnMediaMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnFloorTextureMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnCeilingTextureMode(wxMouseEvent& ev)
{
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/**
    右ボタンを押したときに呼ばれる
*/
void MapEditorMainFrame::OnRightDown(wxMouseEvent& ev)
{
    //カーソル設定
    wxGetApp().setCursor();
    int mx = ev.m_x;
    int my = ev.m_y;
    //マウス座標記録
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    vmgr->setNewMousePoint(mx, my);

    //ポップアップメニューを出す
    //TODO
    //マウス座標をワールド座標にする
    world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(mx, my);
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    int div = vmgr->getZoomDivision();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();

    int editMode = emgr->getEditModeType();
    int toolType = emgr->getToolType();
    if(editMode == EditModeType::EM_DRAW && toolType == ToolType::TI_ARROW){
        //点の上で右クリックしたか？
        int epIndex = hpl::aleph::map::getSelectPointIndex(wmp, POINT_DISTANCE_EPSILON * div, zMin, zMax);
        if(epIndex != NONE){
            //点ポップアップ表示
            PopupMenu(&wxGetApp().pointPopupMenu);
        }else{
            //点は押されなかった
            int lineIndex = hpl::aleph::map::getSelectLineIndex(wmp, LINE_DISTANCE_EPSILON * div, zMin, zMax);
            if(lineIndex != NONE){
                //線が押された
                //→線プロパティをだす
                PopupMenu(&wxGetApp().linePopupMenu);
            }
        }
    }

}
///////////////////////////////////////////////////////
void MapEditorMainFrame::OnRightUp(wxMouseEvent& ev)
{
    //カーソル設定
    wxGetApp().setCursor();
    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
}
void MapEditorMainFrame::OnLeftUp(wxMouseEvent& ev)
{
    //カーソル設定
    wxGetApp().setCursor();
    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

    //イベントマネージャー
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

    int editMode = emgr->getEditModeType();
    int toolType = emgr->getToolType();
    if(editMode == EditModeType::EM_DRAW){
        if(toolType == ToolType::TI_ARROW){
            this->doLUpOnArrowTool(ev);
        }else if(toolType == ToolType::TI_POLYGON){
            this->doLUpOnPolygonTool(ev);
        }
    }
    emgr->setSelectingGroup(false);

    //ポリゴン状態を更新します
    wxGetApp().getStockManager()->updatePolygonValidityStored();
    Refresh();
}

void MapEditorMainFrame::doLUpOnArrowTool(wxMouseEvent& ev)
{
    //選択データ
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    //グリッドマネージャー
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

    if(sel->isSelectOneObject()){
        //オブジェクトを選択していたら
        //オブジェクト情報ダイアログ表示
        //TODO
        this->objPropDialog.Show(true);
    }else if(sel->isSelectOnePolygon()){
        //ポリゴン情報ダイアログ表示
    }
    //TODO
    //点、線、Sideは右クリックメニューでプロパティを選択した時のみ表示する
    
    int mx = ev.m_x;
    int my = ev.m_y;

    if(emgr->isSelectingGroup()){
        //範囲選択中だった。矩形内のアイテムを選択とする
        //選択開始位置
        int selStartPoint[2];
        emgr->getSelectGroupStartPoint(selStartPoint);
        
        //選択情報初期化
        sel->clear();
        
        //点 <en> points
        for(int i = 0; i < (int)EndpointList.size(); i ++){
            endpoint_data* ep = get_endpoint_data(i);
            //高さチェック
            if(!vmgr->isValidHeight(ep->highest_adjacent_floor_height,
                ep->lowest_adjacent_ceiling_height))
            {
                continue;
            }
            int vpoint[2];
            wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);
            if(hpl::math::isPointInRect<int>(vpoint[0], vpoint[1],
                mx, my, selStartPoint[0], selStartPoint[1]))
            {
                //追加
                int offset[2] = {0,0};
                sel->addSelPoint(i, offset);
            }
        }

        //線 <en> lines
        for(int i = 0; i < (int)LineList.size(); i ++){
            line_data* line = get_line_data(i);
            endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
            endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
            int beginVPoint[2];
            int endVPoint[2];
            wxGetApp().getViewPointFromWorldPoint(begin->vertex, beginVPoint);
            wxGetApp().getViewPointFromWorldPoint(end->vertex, endVPoint);

            //高さチェック
            if(!vmgr->isValidHeight(line->highest_adjacent_floor,
                line->lowest_adjacent_ceiling))
            {
                continue;
            }
            if(hpl::math::isLineInRect(beginVPoint[0], beginVPoint[1],
                endVPoint[0], endVPoint[1],
                mx, my, selStartPoint[0], selStartPoint[1]))
            {
                //追加
                int offset[2][2] = {{0,0},{0,0}};
                sel->addSelLine(i, offset);
            }
        }

        //ポリゴン
        for(int i = 0; i < (int)PolygonList.size(); i ++){
            polygon_data* poly = get_polygon_data(i);
            int n = poly->vertex_count;
            if(n < 1 || n >= MAXIMUM_VERTICES_PER_POLYGON){
                continue;
            }
            //高さチェック
            if(!vmgr->isValidHeight(poly->floor_height,
                poly->ceiling_height))
            {
                continue;
            }
            //全ての点が矩形内ならポリゴンを選択
            bool inner = true;
            for(int j = 0; j < n; j ++){
                endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[j]);
                int vpoint[2];
                wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);
                if(!hpl::math::isPointInRect<int>(vpoint[0], vpoint[1],
                    mx, my, selStartPoint[0], selStartPoint[1]))
                {
                    inner = false;
                    break;
                }
            }
            if(inner){
                //登録
                int offset[MAXIMUM_VERTICES_PER_POLYGON][2];
                memset(offset, 0, sizeof(int) * MAXIMUM_VERTICES_PER_POLYGON * 2);
                sel->addSelPolygon(i, offset, n);
            }
        }
    

        //オブジェクト
        for(int i = 0; i < (int)SavedObjectList.size(); i ++){
            map_object* obj = &(SavedObjectList[i]);
            //高さチェック
            if(!vmgr->isValidHeight(obj->location.z,
                obj->location.z))
            {
                continue;
            }
            int vpoint[2];
            wxGetApp().getViewPointFromWorldPoint(obj->location.x, 
                obj->location.y, vpoint);
            if(hpl::math::isPointInRect<int>(vpoint[0], vpoint[1],
                mx, my, selStartPoint[0], selStartPoint[1]))
            {
                //追加
                int offset[2] = {0,0};
                sel->addSelObject(i, offset);
            }
        }

    }
}
void MapEditorMainFrame::doLUpOnPolygonTool(wxMouseEvent& ev)
{
    int selStartPoint[2];
    wxGetApp().getEventManager()->getSelectGroupStartPoint(selStartPoint);
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    if(emgr->isSelectingGroup()){
        //n角形の座標を計算
        double polyPointsView[MAXIMUM_VERTICES_PER_POLYGON][2];
        int n = wxGetApp().presetPolygonVertexCount;
        hpl::math::getRectangleScaledPreparedPolygon(ev.m_x, ev.m_y,
            selStartPoint[0], selStartPoint[1], n,
            polyPointsView);
        //ワールド座標形に変換
        world_point2d polyPointsWorld[MAXIMUM_VERTICES_PER_POLYGON];
        for(int i = 0; i < n; i ++){
            polyPointsWorld[i] = wxGetApp().getWorldPointFromViewPoint(
                (int)polyPointsView[i][0], (int)polyPointsView[i][1]);
        }
        //ポリゴン生成
        hpl::aleph::map::addNewPolygon(polyPointsWorld, n);
    }
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/**
    マウスが移動したときに呼ばれる
*/
void MapEditorMainFrame::OnMotion(wxMouseEvent &ev)
{
    //カーソル設定
    wxGetApp().setCursor();

    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

    int editModeType = wxGetApp().getEventManager()->getEditModeType();

    const int UPDATE_POLYGON_VALIDITY_INTERVAL = 10;
    static int updatePolygonValidityCount = UPDATE_POLYGON_VALIDITY_INTERVAL;

    //ポリゴン整合性チェックカウント
    updatePolygonValidityCount ++;


    int mx = ev.m_x;
    int my = ev.m_y;
    if(ev.ButtonIsDown(wxMOUSE_BTN_LEFT)){
        if(updatePolygonValidityCount >= UPDATE_POLYGON_VALIDITY_INTERVAL){
            //ポリゴン整合性を更新
            wxGetApp().getStockManager()->updatePolygonValidityStored();
        }

        //左ボタンを押しながら動いている
        bool shift = ev.ShiftDown();
        bool ctrl = ev.ControlDown();
#ifdef MAP_VIEWER
        //Viewer専用の動作
        //クリックしていれば移動
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            //オフセット移動
            moveMapOffset(mx, my);
        }
#else

        //編集モードごとに動作が異なる
        
        int toolType = wxGetApp().getEventManager()->getToolType();
        
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            //コントロール押しながら、
            //あるいはハンドツールでD&D
            //→オフセット移動
            this->moveMapOffset(ev.m_x, ev.m_y);
        }else{
            //Ctrl押さない

            switch(editModeType){
            case EditModeType::EM_DRAW:
                doMouseMotionOnDrawMode(ev);
                break;
            case EditModeType::EM_POLYGON_TYPE:
                doMouseMotionOnPolygonMode(ev);
                break;
            case EditModeType::EM_FLOOR_HEIGHT:
                doMouseMotionOnFloorHeightMode(ev);
                break;
            case EditModeType::EM_CEILING_HEIGHT:
                doMouseMotionOnCeilingHeightMode(ev);
                break;
            case EditModeType::EM_FLOOR_LIGHT:
                doMouseMotionOnFloorLightMode(ev);
                break;
            case EditModeType::EM_CEILING_LIGHT:
                doMouseMotionOnCeilingLightMode(ev);
                break;
            case EditModeType::EM_MEDIA:
                doMouseMotionOnMediaMode(ev);
                break;
            case EditModeType::EM_FLOOR_TEXTURE:
                doMouseMotionOnFloorTextureMode(ev);
                break;
            case EditModeType::EM_CEILING_TEXTURE:
                doMouseMotionOnCeilingTextureMode(ev);
                break;
            }
        }


#endif
        Refresh();
    }else{
        //押していない状態
        if(editModeType == EditModeType::EM_DRAW &&
            wxGetApp().getEventManager()->getToolType() == ToolType::TI_LINE)
        {
            this->doMouseMotionOnLineTool(ev);
        }
    }

    //更新
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

}
void MapEditorMainFrame::doMouseMotionOnDrawMode(wxMouseEvent& ev)
{
    switch(wxGetApp().getEventManager()->getToolType()){
    case ToolType::TI_ARROW:
        doMouseMotionOnArrowTool(ev);
        break;
    case ToolType::TI_FILL:
        doMouseMotionOnFillTool(ev);
        break;
    case ToolType::TI_HAND:
        doMouseMotionOnHandTool(ev);
        break;
    case ToolType::TI_LINE:
        //線ツールはD&Dは考慮しない
        //doMouseMotionOnLineTool(ev);
        break;
    case ToolType::TI_MAGNIFY:
        doMouseMotionOnMagnifyTool(ev);
        break;
    case ToolType::TI_SKULL:
        doMouseMotionOnSkullTool(ev);
        break;
    case ToolType::TI_TEXT:
        doMouseMotionOnTextTool(ev);
        break;
    case ToolType::TI_POLYGON:
        doMouseMotionOnPolygonTool(ev);
        break;
    default:
        hpl::error::halt("Invalid tool type");
    }
}
void MapEditorMainFrame::doMouseMotionOnArrowTool(wxMouseEvent& ev)
{
    //もし範囲選択中なら？
    //ここですることはない

    //もし選択中のマップアイテムがあれば、それらを移動させる
    
    //選択情報
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    int div = vmgr->getZoomDivision();

    int mx = ev.m_x;
    int my = ev.m_y;

    if(sel->isSelected()){
        //選択中
        //選択物の移動
        
        //ワールド座標系にする
        world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(mx, my);

        //点
        for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
            struct hpl::aleph::map::SelPoint* selp = &sel->getSelPoints()->at(i);
            //位置変更
            get_endpoint_data(selp->index)->vertex.x = wmp.x + selp->offset[0] * div;
            get_endpoint_data(selp->index)->vertex.y = wmp.x + selp->offset[1] * div;
        }

        //線
        for(int i = 0; i < (int)sel->getSelLines()->size(); i ++){
            struct hpl::aleph::map::SelLine* sell = &sel->getSelLines()->at(i);
            int index = sell->index;
            line_data* line = get_line_data(index);
            for(int j = 0; j < 2; j ++){
                get_endpoint_data(line->endpoint_indexes[j])->vertex.x =
                    wmp.x + sell->offset[j][0] * div;
                get_endpoint_data(line->endpoint_indexes[j])->vertex.y =
                    wmp.y + sell->offset[j][1] * div;
            }
        }

        //ポリゴン
        for(int i = 0; i < (int)sel->getSelPolygons()->size(); i ++){
            struct hpl::aleph::map::SelPolygon* selp = &sel->getSelPolygons()->at(i);
            polygon_data* poly = get_polygon_data(selp->index);
            for(int j = 0; j < selp->num; j ++){
                get_endpoint_data(poly->endpoint_indexes[j])->vertex.x =
                    wmp.x + selp->offset[j][0] * div;
                get_endpoint_data(poly->endpoint_indexes[j])->vertex.y =
                    wmp.y + selp->offset[j][1] * div;
            }
        }

        //オブジェクト
        for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
            struct hpl::aleph::map::SelObject* selo = &sel->getSelObjects()->at(i);
            SavedObjectList[selo->index].location.x = wmp.x + selo->offset[0] * div;
            SavedObjectList[selo->index].location.y = wmp.y + selo->offset[1] * div;
        }
    }
}
void MapEditorMainFrame::doMouseMotionOnFillTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnHandTool(wxMouseEvent& ev)
{
    //移動
    this->moveMapOffset(ev.m_x, ev.m_y);
}
/**
    線ツール
*/
void MapEditorMainFrame::doMouseMotionOnLineTool(wxMouseEvent& ev)
{
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();

    int voffset[2];
    vmgr->getOffset(voffset);
    world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(ev.m_x, ev.m_y);
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
    int div = vmgr->getZoomDivision();

    //点を踏んでいないか確認
    int endpointIndex = hpl::aleph::map::getSelectPointIndex(wmp, POINT_DISTANCE_EPSILON * div, zMin, zMax);
    if(endpointIndex != NONE){
        wxGetApp().isNowOnThePoint = true;
        wxGetApp().isNowOnTheLine = false;
    }else{
        wxGetApp().isNowOnThePoint = false;

        int lineIndex = hpl::aleph::map::getSelectLineIndex(wmp, POINT_DISTANCE_EPSILON * div, zMin, zMax);
        if(lineIndex != NONE){
            wxGetApp().isNowOnTheLine = true;
        }else{
            wxGetApp().isNowOnTheLine = false;
        }
    }
}
void MapEditorMainFrame::doMouseMotionOnMagnifyTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnSkullTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnTextTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnPolygonTool(wxMouseEvent& ev)
{
}

void MapEditorMainFrame::doMouseMotionOnPolygonMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnFloorHeightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnCeilingHeightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnFloorLightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnCeilingLightMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnMediaMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnFloorTextureMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnCeilingTextureMode(wxMouseEvent& ev)
{
}

void MapEditorMainFrame::OnMouseWheel(wxMouseEvent &ev)
{
    //カーソル設定
    wxGetApp().setCursor();

    int zDelta = ev.m_wheelRotation;
    hpl::aleph::view::HPLViewGridManager* mgr = wxGetApp().getViewGridManager();

    //コントロールキー
    bool ctrl = ev.ControlDown();
    if(ctrl){
        wxSize size = wxFrame::GetSize();
        if(zDelta < 0){
            mgr->zoomIn(size.GetWidth(), size.GetHeight());
        }else{
            mgr->zoomOut(size.GetWidth(), size.GetHeight());
        }
        Refresh();
    }
}

// オフセットを指定したマウスポイントによって移動させます
void MapEditorMainFrame::moveMapOffset(int x, int y)
{
    hpl::aleph::view::HPLViewGridManager* mgr = wxGetApp().getViewGridManager();
    //以前のマウスポジションを得ます
    int oldMPoint[2];
    mgr->getOldMousePoint(oldMPoint);
    int deltaX = x - oldMPoint[0];
    int deltaY = y - oldMPoint[1];

    //オフセットを設定します
    int voffset[2];
    mgr->getOffset(voffset);
    voffset[0] += deltaX;
    voffset[1] += deltaY;
    mgr->setOffset(voffset[0], voffset[1]);
}
