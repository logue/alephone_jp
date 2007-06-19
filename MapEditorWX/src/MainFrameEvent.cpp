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
            //this->objectPropDialog.Show(true);
            return true;
        }
    }

    //no obj selected
    //TODO 選択ID関連の実装
    //this->objectPropDialog->setSelectedObjectIndex(NONE);


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

    int mx = ev.m_x;
    int my = ev.m_y;
    //世界座標にする
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mx, my);

    bool isFirst = wxGetApp().isFirstOfLineToAdd;

    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    
    
    //重なる点があるかどうかチェック
    int pointIndex = NONE;
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = get_endpoint_data(i);
        if(hpl::aleph::map::isSelectPoint(mx, my, ep->vertex.x, ep->vertex.y,
            voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div))
        {
            pointIndex = i;
            break;
        }
    }
    //重なる線があるか判定する

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
            wxGetApp().prevPointIndex = 
        }else{
            //2回目以降のクリック
            //同じ点をクリックしていたら何もしない
            //TODO
            //でなけば線を作成する
            //TODO
        }

        //中継点・始点・終点にする
        wxGetApp().isFirstOfLineToAdd = false;
    }else{
        //線を踏んでいないかチェックします
        bool onLine = false;
        for(int i = 0; i < (int)LineList.size(); i ++){
            line_data* line = get_line_data(i);
            endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
            endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
            if(hpl::aleph::map::isSelectLine(mx, my, begin->vertex.x, begin->vertex.y,
                end->vertex.x, end->vertex.y, voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD,
                div, LINE_DISTANCE_EPSILON))
            {
                //線を踏んでいる
                //TODO 切断します
                //TODO 点を追加して接続しなおします
                onLine = true;
                break;
            }
        }
        if(onLine){
        }else{
            //新規追加
            if(wxGetApp().isFirstOfLineToAdd){
                //最初の点
            }else{
                //点を追加
            }

            //点を追加してから線を追加する
        }
    }
    wxGetApp().isFirstOfLineToAdd = isFirst;
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
    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
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

    if(updatePolygonValidityCount >= UPDATE_POLYGON_VALIDITY_INTERVAL){
        //TODO
    }
    if(ev.ButtonIsDown(wxMOUSE_BTN_LEFT)){
        //左ボタンを押しながら動いている
        bool shift = ev.ShiftDown();
        bool ctrl = ev.ControlDown();
#ifdef MAP_VIEWER
        //Viewer専用の動作
        //クリックしていれば移動
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            
        }
#else

        //編集モードごとに動作が異なる
        
        int toolType = wxGetApp().getEventManager()->getToolType();
        
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            this->moveMapOffset(ev.m_x, ev.m_y);
        }else{
            //Ctrl押さない
            if(editModeType == EditModeType::EM_DRAW){
                //ドローモード
                if(toolType == ToolType::TI_ARROW){
                    //矢印ツールでD&D

                }
            }
        }


#endif
        Refresh();
    }

    //更新
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

}
void MapEditorMainFrame::doMouseMotionOnDrawMode(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnArrowTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnFillTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnHandTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doMouseMotionOnLineTool(wxMouseEvent& ev)
{
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
