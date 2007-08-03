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

	//アンドゥ情報に追加しておきます
//	hpl::aleph::map::HPLDoneHistory* hmgr = wxGetApp().getDoneHistoryManager();
	sel->setMousePosition(mx, my);
	hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

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
			emgr->setGrabItems(true);
        }else{
            //クリックしていない
			
			//何か一つ選択しているか判定
			if(this->tryToSelectOneItem(ev)){
				//ひとつ選択時の後処理
				//対象選択(済み)
				//オフセット設定
				//行動履歴に追加
				this->selectOneThingAfter(mx, my);
			}else{
				//選択解除
				//範囲選択開始
				this->selectNothing(mx, my);
			}
        }
	}else{
		//何も選択していない
		//一つを選択できるか試してみます
		if(this->tryToSelectOneItem(ev)){
			//選択解除（済み）・対象を選択（済み）
			//オフセット設定
			//行動履歴に追加
			this->selectOneThingAfter(mx, my);
		}else{
			//選択されなかった
			//選択解除
			//範囲選択開始
			this->selectNothing(mx, my);
		}

	}

	//選択情報の更新
	wxGetApp().getStockManager()->updateSelects(wxGetApp().selectData);
}
/**
	なにも選択できなかった場合
*/
void MapEditorMainFrame::selectNothing(int mx, int my)
{
	//範囲選択の開始
	wxGetApp().getEventManager()->setSelectGroupStartPoint(mx, my);

	//選択＆編集中だったアイテムを初期化
	//TODO 遅くなる可能性があるので、修正が必要かも
	//(主にダイアログのコンボボックスを再構築するのに時間が取られる)
	this->unselect();

	//選択解除
	wxGetApp().selectData.clear();
}

/**
	the function called when select one thing
	@param mx, my マウス座標 mouse cursor position
*/
void MapEditorMainFrame::selectOneThingAfter(int mx, int my)
{
	//選択されていない項目に関するダイアログの設定を解除します
	this->unselect();
	
	int voffset[2];
	hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
	vmgr->getOffset(voffset);
	int div = vmgr->getZoomDivision();

	//オフセット設定
	hpl::aleph::map::setupSelectDataGroupOffsets(mx, my,
		&wxGetApp().selectData, voffset[0], voffset[1],
		OFFSET_X_WORLD, OFFSET_Y_WORLD, div);
	
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	sel->setMousePosition(mx, my);
	//種類に応じてダイアログを表示する
	if(sel->isSelectOneObject()){
        this->objPropDialog.setObjIndex(sel->getSelObjects()->at(0).index);
		this->objPropDialog.Show(true);
	}else{
        this->objPropDialog.setObjIndex(NONE);
	}
	if(sel->isSelectOnePoint()){
	}else{
	}
	if(sel->isSelectOneAnnotation()){
	}else{
	}
	if(sel->isSelectOneLine()){
	}else{
	}
	/*
	if(sel->isSelectOnePolygon()){
        this->polyPropDialog.setPolyIndex(sel->getSelPolygons()->at(0).index,
			wxGetApp().getStockManager());
        this->polyPropDialog.Show(true);
	}else{
        this->polyPropDialog.setPolyIndex(NONE, wxGetApp().getStockManager());
	}*/

	//選択できたので
	//範囲選択は解除します
	hpl::aleph::HPLEventManager *emgr = wxGetApp().getEventManager();
	emgr->exitSelectingGroup();
	emgr->setGrabItems(true);

	//アンドゥ機能等のために記憶しておきます
	wxGetApp().getDoneHistoryManager()->push_back(
		hpl::aleph::map::ActionType::None, wxGetApp().selectData);

	//最後に選択した位置のマウスポイントを記憶します
	emgr->setLastMouseSelectPoint(mx, my);
}

void MapEditorMainFrame::unselect()
{
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
    //点を選択していないのにindexがNONEではない
    if(!sel->isSelectOnePoint() && pointPropDialog.getIndex() != NONE){
        //その場合選択をNONEにする
		this->pointPropDialog.setIndex(NONE);
    }
	if(!sel->isSelectOneObject() && objPropDialog.getObjIndex() != NONE)
		this->objPropDialog.setObjIndex(NONE);
/*	if(!sel->isSelectOneLine() && linePropDialog.getLineIndex() != NONE)
		this->linePropDialog.setLineIndex(NONE);*/
	if(!sel->isSelectOneSide() && sidePropDialog.getIndex() != NONE)
		this->sidePropDialog.setIndex(NONE);
/*	if(!sel->isSelectOnePolygon() && polyPropDialog.getPolyIndex() != NONE)
		this->polyPropDialog.setPolyIndex(NONE, wxGetApp().getStockManager());
		*/
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


    //選択の優先順位は
    //1:オブジェクト
    //2:点
    //-:アノテーション
    //3:線
    //4:ポリゴン


    //オブジェクト
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        if(wxGetApp().getStockManager()->isDeleteObject(i)){
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

        //オブジェクト選択検査
        if(hpl::aleph::map::isSelectPoint(mx, my,
            x, y, voffset[0], voffset[1],
            OFFSET_X_WORLD, OFFSET_Y_WORLD, div, OBJECT_DISTANCE_EPSILON))
        {
		    if(!shift){
				//シフトキーを押さずにクリックしたら一旦解放する
				selectOneThingBefore();
			}

            //選択追加
            int offset[2];

            sel->addSelObject(i, offset);
            return true;
        }
    }

    //////////
    //点
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        if(wxGetApp().getStockManager()->isDeletePoint(i)){
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
		    if(!shift){
				//シフトキーを押さずにクリックしたら一旦解放する
				selectOneThingBefore();
			}
            //見つかった
            int offset[2];
            sel->addSelPoint(i, offset);
            return true;
        }
    }

	//////////////////////////////////////
	//アノテーション
	int annotationIndex = hpl::aleph::map::getSelectAnnotationIndex(mx, my,
		POINT_DISTANCE_EPSILON, zMin, zMax,
		voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
		wxGetApp().getStockManager());
	if(annotationIndex != NONE){
	    if(!shift){
			//シフトキーを押さずにクリックしたら一旦解放する
			selectOneThingBefore();
		}
		map_annotation* annotation = &MapAnnotationList[annotationIndex];
		//オフセット設定
		int offset[2];
		int vpoint[2];
		wxGetApp().getViewPointFromWorldPoint(annotation->location, vpoint);
		offset[0] = vpoint[0] - mx;
		offset[1] = vpoint[1] - my;
		sel->addSelAnnotation(annotationIndex, offset);
		return true;
	}

    /////////////////////////
    //lines
	int lineIndex = hpl::aleph::map::getSelectLineIndex(mx ,my,
		LINE_DISTANCE_EPSILON, zMin, zMax,
		voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
		wxGetApp().getStockManager());
	if(lineIndex != NONE){
	    if(!shift){
			//シフトキーを押さずにクリックしたら一旦解放する
			selectOneThingBefore();
		}
		line_data* line = get_line_data(lineIndex);
		endpoint_data* start = get_endpoint_data(line->endpoint_indexes[0]);
		endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

        //選択

        int offset[2][2];
        sel->addSelLine(lineIndex, offset);
        return true;
    }

    //ポリゴン
    //TODO 高さ順にソートする(まだやってない)
	int polyIndex = hpl::aleph::map::getSelectPolygonIndex(mx ,my,
		zMin, zMax,
		voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
		wxGetApp().getStockManager());
	if(polyIndex != NONE){
	    if(!shift){
			//シフトキーを押さずにクリックしたら一旦解放する
			selectOneThingBefore();
		}
        polygon_data* poly = get_polygon_data(polyIndex);
#ifdef __WXDEBUG__
		wxASSERT(poly);
#endif
        int n = poly->vertex_count;
        int offset[MAXIMUM_VERTICES_PER_POLYGON][2];
        
        sel->addSelPolygon(polyIndex, offset, n);
        return true;
    }

	//選択できなかった

    return false;
}
//選択に成功した場合の前処理
void MapEditorMainFrame::selectOneThingBefore()
{
	//選択解除
	wxGetApp().selectData.clear();
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
        if(smgr->isDeletePolygon(i)){
            continue;
        }
        polygon_data* poly = get_polygon_data(i);
        if(hpl::aleph::map::isPointInPolygon(wpoint, i)){
            //点が含まれる
            //このポリゴン上に置く
            //TODO
            int flags = 0;

			//ダイアログからオブジェクトを作成する
            map_object objv = this->objPropDialog.getObject();
            objv.polygon_index = i;
			//ポリゴン位置を取得
			objv.location.x = wpoint.x;
			objv.location.y = wpoint.y;
			objv.location.z = poly->floor_height;
			if(objv.flags & _map_object_hanging_from_ceiling){
				//TODO 天井からぶら下がっている場合、天井に座標を合わせるべきか？
			}

            int newIndex = hpl::aleph::map::addMapSavedObject(objv);
			//オブジェクトダイアログボックスを更新します
			objPropDialog.setObjIndex(newIndex);
			//選択をこのオブジェクトに変更します
			wxGetApp().selectData.clear();
			int offset[2] = {0};
			wxGetApp().selectData.addSelObject(newIndex, offset);
			//TODO Prepare "Add" Undo
            found = true;
            break;
        }
    }
    if(!found){
        hpl::error::caution("You must place objects ON POLYGON");
    }
	this->updateMapItems();
#endif
}
void MapEditorMainFrame::doLButtonOnTextTool(wxMouseEvent& ev)
{
    int mx = ev.m_x;
    int my = ev.m_y;
    int voffset[2];
    //グリッドマネージャー
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    vmgr->getOffset(voffset);
    int div = wxGetApp().getViewGridManager()->getZoomDivision();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
#ifdef MAP_VIEWER
#else
    //shiftを押しながらだと編集モードになる
    if(ev.ShiftDown()){
        int annotationIndex = NONE;
        //アノテーションを選択できるか試してみます
        for(int i = 0; i < (int)MapAnnotationList.size(); i ++){
            map_annotation* annotation = &MapAnnotationList[i];
            if(hpl::aleph::map::isSelectPoint(mx, my,
                annotation->location.x, annotation->location.y,
                voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD,
                div, POINT_DISTANCE_EPSILON))
            {
                //選択出来た
                annotationIndex = i;
                break;
            }
        }
        if(annotationIndex != NONE){
            //アノテーションを編集します
            AnnotationDialog dlg;
            dlg.Create(this, wxID_ANY, MapAnnotationList[annotationIndex]);
            if(dlg.ShowModal() == wxID_OK){
                map_annotation newAn = dlg.getAnnotation();
                //変更
                MapAnnotationList[annotationIndex] = newAn;
            }
        }

        //見つからなかった
        hpl::error::caution("No annotation found there");
    }else{

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
    }
#endif
}
void MapEditorMainFrame::doLButtonOnPolygonTool(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
    //範囲選択開始
    wxGetApp().getEventManager()->setSelectGroupStartPoint(ev.m_x, ev.m_y);
#endif
}

void MapEditorMainFrame::doLButtonOnPolygonMode(wxMouseEvent& ev)
{
	//矢印ツール→選択・閲覧
	int tool = wxGetApp().getEventManager()->getToolType();
	int mx = ev.m_x;
	int my = ev.m_y;
	int voffset[2];
	hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
	vmgr->getOffset(voffset);
	int div = vmgr->getZoomDivision();
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
	int zMin = vmgr->getViewHeightMin();
	int zMax = vmgr->getViewHeightMax();

	int polyIndex = hpl::aleph::map::getSelectPolygonIndex(mx ,my,
		voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, zMin, zMax, div,
		smgr);
	polygon_data* poly = get_polygon_data(polyIndex);
	if(tool == ToolType::TI_ARROW){
		if(poly){
			//選択内容をリストコントロールに反映
			this->polyTypeDialog.setType(poly->type);
		}
	}
#ifdef MAP_VIEWER
#else
	//塗りつぶしツール→現在選択しているタイプで塗りつぶし
	if(tool == ToolType::TI_FILL){
		if(poly){
			int polyType = this->polyTypeDialog.getType();
			if(polyType >= 0){
				//タイプを変更
				poly->type = polyType;
				Refresh();
			}
		}
	}
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
