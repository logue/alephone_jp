#include "MapEditorMainFrame.h"
#include "AnnotationDialog.h"


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

	//ストックマネージャー
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    //ポップアップメニューを出す
    //TODO
    //マウス座標をワールド座標にする
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    int div = vmgr->getZoomDivision();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();

    int editMode = emgr->getEditModeType();
    int toolType = emgr->getToolType();
	int voffset[2];
	vmgr->getOffset(voffset);

	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

	hpl::aleph::map::HPLDoneHistory* dmgr = wxGetApp().getDoneHistoryManager();

    if(editMode == EditModeType::EM_DRAW && toolType == ToolType::TI_ARROW){
		if(sel->isSelected() && emgr->isGrabItems()){
			//左ボタン押しながら右押した
			if(sel->isSelected()){
				//選択していた
				if(emgr->isGrabItems()){
					//つかんでいた

					//つかんでいたのをはなす
					emgr->setGrabItems(false);

					//座標を元の位置に戻す
					hpl::aleph::map::HPLSelectData dummy1;
					hpl::aleph::map::HPLRealMapData dummy2;
					hpl::aleph::map::HPLActionItem act = hpl::aleph::map::HPLActionItem(0, dummy1, dummy2);
					dmgr->getTail(&act);
					int lastMousePosition[2];
					act.selectData.getMousePosition(lastMousePosition);
					world_point2d worldLastMousePosition = 
						wxGetApp().getWorldPointFromViewPoint(
							lastMousePosition[0], lastMousePosition[1]);
					hpl::aleph::map::HPLSelectData* actSel = &act.selectData;
					//points
					for(int i = 0; i < (int)actSel->getSelPoints()->size(); i ++){
						hpl::aleph::map::SelPoint* selp = &actSel->getSelPoints()->at(i);
						endpoint_data* ep = get_endpoint_data(selp->index);
						ep->vertex.x = worldLastMousePosition.x + selp->offset[0] * div;
						ep->vertex.y = worldLastMousePosition.y + selp->offset[1] * div;
					}

					//lines
					for(int i = 0; i < (int)actSel->getSelLines()->size(); i ++){
						hpl::aleph::map::SelLine* sell = &actSel->getSelLines()->at(i);
						line_data* line = get_line_data(sell->index);
						for(int j = 0; j < 2; j ++){
							endpoint_data* ep = get_endpoint_data(line->endpoint_indexes[j]);
							ep->vertex.x = worldLastMousePosition.x + sell->offset[j][0] * div;
							ep->vertex.y = worldLastMousePosition.y + sell->offset[j][1] * div;
						}
					}

					//polygons
					for(int i = 0; i < (int)actSel->getSelPolygons()->size(); i ++){
						hpl::aleph::map::SelPolygon* selp = &actSel->getSelPolygons()->at(i);
						polygon_data* poly = get_polygon_data(selp->index);
						int n = poly->vertex_count;
						for(int j = 0; j < n; j ++){
							endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[j]);
							ep->vertex.x = worldLastMousePosition.x + selp->offset[j][0] * div;
							ep->vertex.y = worldLastMousePosition.y + selp->offset[j][1] * div;
						}
					}

					//objects
					for(int i = 0; i < (int)actSel->getSelObjects()->size(); i ++){
						hpl::aleph::map::SelObject* selp = &actSel->getSelObjects()->at(i);
						map_object* obj = &SavedObjectList[selp->index];
						obj->location.x = worldLastMousePosition.x + selp->offset[0] * div;
						obj->location.y = worldLastMousePosition.y + selp->offset[1] * div;
					}

					//annotations
					for(int i = 0; i < (int)actSel->getSelAnnotations()->size(); i ++){
						hpl::aleph::map::SelAnnotation* selp =
							&actSel->getSelAnnotations()->at(i);
						map_annotation* annotation = &MapAnnotationList[selp->index];
						annotation->location.x =
							worldLastMousePosition.x + selp->offset[0] * div;
						annotation->location.y =
							worldLastMousePosition.y + selp->offset[1] * div;
					}
					Refresh();
				}
			}
		}else{
			//点の上で右クリックしたか？
			int epIndex = hpl::aleph::map::getSelectPointIndex(mx ,my,
				POINT_DISTANCE_EPSILON, zMin, zMax,
				voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
				smgr);
			wxGetApp().popupEndpointIndex = epIndex;
			int lineIndex = hpl::aleph::map::getSelectLineIndex(mx ,my,
				LINE_DISTANCE_EPSILON, zMin, zMax,
				voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
				smgr);
			wxGetApp().popupLineIndex = lineIndex;
			int polygonIndex = hpl::aleph::map::getSelectPolygonIndex(mx ,my,
				zMin, zMax,
				voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
				smgr);
			wxGetApp().popupPolygonIndex = polygonIndex;
			if(epIndex != NONE){
				//選択変更
				selectOneThingBefore();
				int offset[2] = {0};
				sel->addSelPoint(epIndex, offset);
				selectOneThingAfter(mx, my);
				//選択情報の更新
				smgr->updateSelects(wxGetApp().selectData);
				Refresh();
				//点ポップアップ表示
				PopupMenu(&wxGetApp().pointPopupMenu);
			}else if(lineIndex != NONE){
				//線が押された
				//選択変更
				selectOneThingBefore();
				int offset[2][2] = {{0}};
				sel->addSelLine(lineIndex, offset);
				selectOneThingAfter(mx, my);
				//選択情報の更新
				smgr->updateSelects(wxGetApp().selectData);
				Refresh();
				//→線プロパティをだす
				PopupMenu(&wxGetApp().linePopupMenu);
			}else if(polygonIndex != NONE){
				//押した
				//選択変更
				selectOneThingBefore();
				polygon_data* poly = get_polygon_data(polygonIndex);
				int offset[MAXIMUM_VERTICES_PER_POLYGON][2] = {{0}};
				int num = poly->vertex_count;
				sel->addSelPolygon(polygonIndex, offset, num);
				selectOneThingAfter(mx, my);
				//選択情報の更新
				smgr->updateSelects(wxGetApp().selectData);
				Refresh();
				PopupMenu(&wxGetApp().polygonPopupMenu);
			}
		}
    }
	//つかみ中を解除
	emgr->setGrabItems(false);
}
///////////////////////////////////////////////////////
void MapEditorMainFrame::OnRightUp(wxMouseEvent& ev)
{
    //カーソル設定
    wxGetApp().setCursor();
    int mx = ev.m_x;
    int my = ev.m_y;

    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(mx, my);


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
    emgr->exitSelectingGroup();

    //ポリゴン状態を更新します
    wxGetApp().getStockManager()->updatePolygonValidityStored();
	//選択情報の更新
	wxGetApp().getStockManager()->updateSelects(wxGetApp().selectData);

    Refresh();
}

void MapEditorMainFrame::doLUpOnArrowTool(wxMouseEvent& ev)
{
    //選択データ
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    //グリッドマネージャー
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
	hpl::aleph::map::HPLDoneHistory* dmgr = wxGetApp().getDoneHistoryManager();

	//何かつかんでいたら行動履歴に残す
	if(sel->isSelected() && emgr->isGrabItems()){
		dmgr->push_back(
			hpl::aleph::map::ActionType::Move, *sel);
#ifdef __WXDEBUG__
//		hpl::error::caution("undo index=%d", dmgr->getIndex());
#endif
	}
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

	//最初に選択項目に追加されたか
	bool isFirst = true;

	//つかみ中を解除
	emgr->setGrabItems(false);

    if(emgr->isSelectingGroup()){

        //範囲選択中だった。矩形内のアイテムを選択とする
        //選択開始位置
        int selStartPoint[2];
        emgr->getSelectGroupStartPoint(selStartPoint);
        
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
                //登録
				int offset[MAXIMUM_VERTICES_PER_POLYGON][2] = {{0}};
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
                //追加
                int offset[2] = {0,0};
                sel->addSelObject(i, offset);
            }
        }

    }
	//どれも選択していないかチェック
	if(isFirst && !sel->isSelected()){
		//選択していない

		//前回の位置
		int oldVPoint[2];
		wxGetApp().getViewGridManager()->getOldMousePoint(oldVPoint);
		
		//現在の位置との距離を計算
		double distance = hpl::math::getLength(mx - oldVPoint[0], my - oldVPoint[1]);
		if(distance > SAME_POSITION_CLICK_THRESHOLD){
			//ほぼ現在の位置でクリックした
			//	ならば選択解除
			sel->clear();
		}
	}

	/*
	if(sel->isSelected()){
		//コピペ情報登録
		wxGetApp().getDoneHistoryManager()->push_back(hpl::aleph::map::ActionType::Move, *sel);
	}
	*/
	//離した
	emgr->setGrabItems(false);
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
        //情報更新
        wxGetApp().getStockManager()->updateDeletes();
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

	hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

    int mx = ev.m_x;
    int my = ev.m_y;

    if(sel->isSelected() && emgr->isGrabItems()){
        //選択中
        //選択物の移動
        
		//マウスが閾値以上動いていたらアイテムを動かす
		//マウスが最後に選択した座標
		int lastMousePosition[2];
		sel->getMousePosition(lastMousePosition);
		if(hpl::math::getLength(mx - lastMousePosition[0], my - lastMousePosition[1])
			>SAME_POSITION_CLICK_THRESHOLD)
		{
			//ワールド座標系にする
			world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(mx, my);

			//点
			for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
				struct hpl::aleph::map::SelPoint* selp = &sel->getSelPoints()->at(i);
				int index = selp->index;
				//位置変更
				get_endpoint_data(index)->vertex.x = wmp.x + selp->offset[0] * div;
				get_endpoint_data(index)->vertex.y = wmp.y + selp->offset[1] * div;

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

			//アノテーション
			//<en> annotation string
			for(int i = 0; i < (int)sel->getSelAnnotations()->size(); i ++){
				hpl::aleph::map::SelAnnotation* sela = &sel->getSelAnnotations()->at(i);
				MapAnnotationList[sela->index].location.x = wmp.x + sela->offset[0] * div;
				MapAnnotationList[sela->index].location.y = wmp.y + sela->offset[1] * div;
			}
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
    int endpointIndex = hpl::aleph::map::getSelectPointIndex(wmp, 
        POINT_DISTANCE_EPSILON , zMin, zMax, div, wxGetApp().getStockManager());
    if(endpointIndex != NONE){
        wxGetApp().isNowOnThePoint = true;
        wxGetApp().isNowOnTheLine = false;
    }else{
        wxGetApp().isNowOnThePoint = false;

        int lineIndex = hpl::aleph::map::getSelectLineIndex(wmp,
            LINE_DISTANCE_EPSILON, zMin, zMax, div, wxGetApp().getStockManager());
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
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//  左ダブルクリック <en> Mouse Left Button Double Click
void MapEditorMainFrame::OnLeftDoubleClick(wxMouseEvent& ev)
{
    //カーソル設定
    wxGetApp().setCursor();

    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    int editMode = emgr->getEditModeType();
    int toolType = emgr->getToolType();
    if(editMode == EditModeType::EM_DRAW &&
        toolType == ToolType::TI_LINE)
    {
        //線モードでダブルクリック

        //線の追加
        this->doLButtonOnLineTool(ev);

        //線編集情報の初期化
        wxGetApp().resetLineEditInfo();
    }

    Refresh();
}

//キーダウン
void MapEditorMainFrame::OnKeyDown(wxKeyEvent& ev)
{
	bool ctrl = ev.ControlDown();
	bool shift = ev.ShiftDown();
	//alt or apple/command key ;)
	bool alt = ev.AltDown() || ev.CmdDown();
	
	int code = ev.GetKeyCode();
	wxCommandEvent dummy;
	//memset(&dummy, 0, sizeof(wxCommandEvent));

	if(ctrl){
		if(code == 'C'){
			//Copy!
			this->OnCopy(dummy);
		}else if(code == 'V'){
			//Paste!
			this->OnPaste(dummy);
		}else if(code == 'Z'){
			//Undo!
			this->OnUndo(dummy);
		}else if(code == 'S'){
			if(shift){
				//Save As!
				this->OnSaveAs(dummy);
			}else{
				//Save!
				this->OnSave(dummy);
			}
		}
	}else{
		if(code == WXK_DELETE){
			wxCommandEvent dummy;
			OnDelete(dummy);
		}
	}
	Refresh();
}

/**
	マップデータに編集があった場合に行われる処理を記述します
	・点/線/Side/オブジェクト/ポリゴンのプロパティダイアログ再構築（追加のみでOK）
	・選択情報の更新
	・削除情報の更新
*/
void MapEditorMainFrame::updateMapItems()
{
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
	smgr->updateSelects(wxGetApp().selectData);
	smgr->updateDeletes();
	smgr->updatePolygonValidityStored();

	//モードレスダイアログ限定
	//ポリゴンプロパティ
	//this->polyPropDialog.updateCombo();

	//ポリゴン・線のFixを行う
	for(int i = 0; i < (int)LineList.size(); i ++){
		if(smgr->isDeleteLine(i)){
			continue;
		}
		hpl::aleph::map::fixLine(i, smgr);
	}
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		if(smgr->isDeletePolygon(i)){
			continue;
		}
		hpl::aleph::map::fixPolygon(i, smgr);
	}

	//編集を知らせる
	wxGetApp().isChanged = true;
	Refresh();

}

