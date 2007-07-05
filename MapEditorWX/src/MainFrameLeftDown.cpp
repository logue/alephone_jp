#include "MapEditorMainFrame.h"
#include "AnnotationDialog.h"

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/**
    左ボタンを押したときに呼ばれる
*/
void MapEditorMainFrame::OnLeftDown(wxMouseEvent &ev)
{
    //線・点・オブジェクト・ポリゴン・Sideの指定を解除する
    linePropDialog.setLineIndex(NONE);
    pointPropDialog.setIndex(NONE);
    objPropDialog.setObjIndex(NONE);
    polyPropDialog.setPolyIndex(NONE);
    sidePropDialog.setIndex(NONE);

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
            hpl::aleph::map::setupSelectDataGroupOffsets(mx, my,
                &wxGetApp().selectData, voffset[0], voffset[1],
                OFFSET_X_WORLD, OFFSET_Y_WORLD, div);
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
        if(wxGetApp().getStockManager()->delObjects[i]){
            continue;
        }
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
        if(wxGetApp().getStockManager()->delPoints[i]){
            continue;
        }
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
        if(wxGetApp().getStockManager()->delLines[i]){
            continue;
        }
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
        if(wxGetApp().getStockManager()->delPolygons[i]){
            continue;
        }
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
    hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    int mx = ev.m_x;
    int my = ev.m_y;
    world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(mx, my);

    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
    //TODO
    //塗りつぶし可能なポリゴンデータを取得します
    std::vector<polygon_data> polyDatas = hpl::aleph::map::searchValidPolygon(
        wmp, smgr, zMin, zMax);
    if(polyDatas.size() == 0){
        //失敗
        hpl::error::caution("No frame to fill as a VALID polygon found (it seems to be a illegal polygon or a none)");
    }else{
        //追加
        hpl::aleph::map::addPolygon(polyDatas[0]);
        //更新
        smgr->updateDeletes();
    }
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

    hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    //重なる点があるかどうかチェック
    int pointIndex = hpl::aleph::map::getSelectPointIndex(
        wpoint, POINT_DISTANCE_EPSILON, zMin, zMax, div, smgr);
    //重なる線があるか判定する
    int lineIndex = hpl::aleph::map::getSelectLineIndex(
        wpoint, LINE_DISTANCE_EPSILON, zMin, zMax, div, smgr);

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
        if(wxGetApp().isFirstOfLineToAdd){
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
                    //既に線が存在している
                    //何もしない
                }else{
                    //でなけば線を作成する
                    line_data line;
                    hpl::aleph::map::createLine(wxGetApp().prevPointIndex,
                        pointIndex, &line);
                    int newLineIndex = hpl::aleph::map::addLine(line);
                }
                wxGetApp().prevPointIndex = pointIndex;
            }
        }

        //最初のクリックではなくなった
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
                hpl::aleph::map::createPoint(wpoint, &ep);
                int newPointIndex = hpl::aleph::map::addEndpoint(ep);
                assert(newPointIndex != NONE);
            }else{
                //始点、終点の情報取得
                //endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
                //endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
                int epStartIndex = line->endpoint_indexes[0];
                int epEndIndex = line->endpoint_indexes[1];

                //線を削除
                smgr->deleteLine(lineIndex);
                smgr->updateDeletes();

                //点を追加
                endpoint_data ep;
                hpl::aleph::map::createPoint(wpoint, &ep);
                int newPointIndex = hpl::aleph::map::addEndpoint(ep);
#ifdef __WXDEBUG__
                wxASSERT(newPointIndex != NONE);
#endif
                endpoint_data *newEp = get_endpoint_data(newPointIndex);

                //始点→点の線を追加
                line_data newLine1;
                hpl::aleph::map::createLine(epStartIndex,
                    newPointIndex, &newLine1);
                int newLine1Index = hpl::aleph::map::addLine(newLine1);
#ifdef __WXDEBUG__
                wxASSERT(newLine1Index != NONE);
#endif

                //点→終点の線を追加
                line_data newLine2;
                hpl::aleph::map::createLine(newPointIndex, epEndIndex,
                    &newLine2);
                int newLine2Index = hpl::aleph::map::addLine(newLine2);
#ifdef __WXDEBUG__
                wxASSERT(newLine2Index != NONE);
#endif


                if(wxGetApp().isFirstOfLineToAdd){
                    //最初ならなにもしない
                }else{
                    //前回→今回の点の間に線を追加
                    line_data newLine;
                    hpl::aleph::map::createLine(wxGetApp().prevPointIndex, newPointIndex, &newLine);
                    int lineIndex = hpl::aleph::map::addLine(newLine);
                }
                wxGetApp().prevPointIndex = newPointIndex;
            }
            wxGetApp().isFirstOfLineToAdd = false;

        }else{
            //新規追加
            endpoint_data ep;
            hpl::aleph::map::createPoint(wpoint, &ep);
            int newPointIndex = hpl::aleph::map::addEndpoint(ep);
            if(wxGetApp().isFirstOfLineToAdd){
                //最初の点なので追加しない
            }else{
                //線を追加する
                line_data line;
                hpl::aleph::map::createLine(wxGetApp().prevPointIndex, newPointIndex, &line);
                int newLineIndex = hpl::aleph::map::addLine(line);
            }
            
            wxGetApp().isFirstOfLineToAdd = false;
            wxGetApp().prevPointIndex = newPointIndex;
        }
    }

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

    hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    bool found = false;
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        if(smgr->delPolygons[i]){
            continue;
        }
        polygon_data* poly = get_polygon_data(i);
        if(hpl::aleph::map::isPointInPolygon(wpoint, i)){
            //点が含まれる
            //このポリゴン上に置く
            //TODO
            int flags = 0;
            map_object objv = this->objPropDialog.getObject();
            objv.polygon_index = i;
            int newIndex = hpl::aleph::map::addMapSavedObject(obj);
            found = true;
            break;
        }
    }
    if(!found){
        hpl::error::caution("You must place objects ON POLYGON");
    }
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
    //情報を更新する
    wxGetApp().getStockManager()->updateDeletes();

#endif
}
void MapEditorMainFrame::doLButtonOnPolygonTool(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
    //範囲選択開始
    //TODO
    wxGetApp().getEventManager()->setSelectingGroup(true);
    wxGetApp().getEventManager()->setSelectGroupStartPoint(ev.m_x, ev.m_y);
#endif
}

void MapEditorMainFrame::doLButtonOnPolygonMode(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
#endif
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
