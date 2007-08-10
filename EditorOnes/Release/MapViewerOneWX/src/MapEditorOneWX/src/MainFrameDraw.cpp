#include "MapEditorMainFrame.h"

#include <cmath>

const double ROUND_DEGREE = 360.0;
const double OBJECT_TRIANGLE_LENGTH = 10.0;
const double WING_DEG = 120.0;

/**
    マップデータの表示
*/
/**
    描画
*/
void MapEditorMainFrame::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxSize size = wxFrame::GetSize();
    if(!wxWindow::IsExposed(0,0,size.GetWidth(), size.GetHeight())){
        return;
    }


    wxBufferedPaintDC dc(this, this->doubleBufferingBitmap);
    PrepareDC(dc);
    //dc.Clear();
//    wxRegionIerator region(GetUpdateRegion());
//    while(
    //dc.DrawLine(10,10,100,20);
    
    wxDC* drawDC = &dc;//&this->doubleBufferingDC;

    hpl::aleph::view::HPLViewGridManager* mgr = wxGetApp().getViewGridManager();
    int DIV = mgr->getZoomDivision();
    int voffset[2];
    mgr->getOffset(voffset);
    int OFFSET_X_VIEW = voffset[0];
    int OFFSET_Y_VIEW = voffset[1];

    //背景描画
    this->drawBackground(drawDC);
    
    //ポリゴン
    this->drawPolygons(drawDC);

    //ライン
    this->drawLines(drawDC);

    //ポイント
    this->drawPoints(drawDC);
    
    //アノテーション
    this->drawAnnotations(drawDC);

    //ドローモードならオブジェクトも表示
    this->drawObjects(drawDC);

    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

    if(emgr->isSelectingGroup()){
        //範囲指定中なら範囲を示す矩形を表示
        int vpoint[2];
        emgr->getSelectGroupStartPoint(vpoint);
        int mpoint[2];
        wxGetApp().getViewGridManager()->getNewMousePoint(mpoint);

		bool isPolygonCreating = emgr->getEditModeType() == EditModeType::EM_DRAW &&
            emgr->getToolType() == ToolType::TI_POLYGON;
		int vGridedPoint[2];
		int mGridedPoint[2] = {mpoint[0], mpoint[1]};
		if(isPolygonCreating){
			this->getGridedViewPoint(mpoint, mGridedPoint);
		}

        //x,y,w,hを計算
        int x = vpoint[0];
        int y = vpoint[1];
        int w = mGridedPoint[0] - x;
        int h = mGridedPoint[1] - y;
        if(mGridedPoint[0] < x){
            x = mGridedPoint[0];
            w = vpoint[0] - x;
        }
        if(mGridedPoint[1] < y){
            y = mGridedPoint[1];
            h = vpoint[1] - y;
        }

        drawDC->SetPen(this->selectingPen);
        drawDC->SetBrush(*wxTRANSPARENT_BRUSH);
        drawDC->DrawRectangle(x,y,w,h);

        if(emgr->getEditModeType() == EditModeType::EM_DRAW &&
            emgr->getToolType() == ToolType::TI_POLYGON)
        {
            int mx = mGridedPoint[0];
            int my = mGridedPoint[1];
            int selStartPoint[2];
            emgr->getSelectGroupStartPoint(selStartPoint);
            //ポリゴン追加モード
            //追加予定ポリゴンを表示
            double polygonPoints[MAXIMUM_VERTICES_PER_POLYGON][2];
            int n = wxGetApp().presetPolygonVertexCount;
            hpl::math::getRectangleScaledPreparedPolygon(mx, my,
                selStartPoint[0], selStartPoint[1], n, polygonPoints);
            wxPoint points[MAXIMUM_VERTICES_PER_POLYGON];
            for(int i = 0; i < n; i ++){
                points[i].x = (int)polygonPoints[i][0];
                points[i].y = (int)polygonPoints[i][1];
            }
            drawDC->DrawPolygon(n, points);
        }
    }

	/*
	if(wxGetApp().getShapesManager()->isLoadedShapesFile()){
		//Shapesファイルから読み込みテスト
		wxBitmap bmp = wxBitmap(this->texture);
		dc.DrawBitmap(bmp,voffset[0],voffset[1],true);

		bmp = wxBitmap(paletteImg);
		dc.DrawBitmap(bmp, 100 + voffset[0], voffset[1], true);

        int W = 100, H = 100, PITCH = 5;
        int W_SPACE = 10, H_SPACE = 10, LINES = 10;
        //draw walls
        std::map<int, std::map<int, std::map<int, wxImage> > >::iterator it;
        int counter = 0;
        for(it = textureMap.begin(); it != textureMap.end(); it ++){
            int collection = it->first;
            std::map<int, std::map<int, wxImage> >::iterator it1;
            for(it1 = it->second.begin(); it1 != it->second.end(); it1 ++){
                int clut = it1->first;
                std::map<int, wxImage>::iterator it2;
                for(it2 = it1->second.begin(); it2 != it1->second.end(); it2 ++){
                    int index = it2->first;
                    wxImage* img = &it2->second;
                    int x = 10 + (index % PITCH ) * (W + W_SPACE);
                    int y = 200 + (index / PITCH) * (H + H_SPACE) + counter * LINES * (H + H_SPACE);
                    wxBitmap bmpImg = wxBitmap(*img);
                    dc.DrawBitmap(bmpImg, x+voffset[0], y+voffset[1]);
                }
            }
            counter ++;
        }
	}
*/
    //バッファから画面へコピー
    dc.Blit(wxPoint(0,0), size,
        drawDC,
        wxPoint(0,0));
}

/**
    背景の描画 <en> draw background 
*/
void MapEditorMainFrame::drawBackground(wxDC* dc)
{
    wxSize size = wxFrame::GetClientSize();
    //背景
    dc->SetPen(this->backgroundPen);
    dc->SetBrush(this->backgroundBrush);
    int left = 0;
    int top = 0;
    int width = size.GetWidth();
    int height = size.GetHeight();
    dc->DrawRectangle(left, top, width, height);

    int grid = wxGetApp().getViewGridManager()->getGridInterval();
    int voffset[2];
    wxGetApp().getViewGridManager()->getOffset(voffset);
    int DIV = wxGetApp().getViewGridManager()->getZoomDivision();

    //枠描画
    dc->SetPen(this->gridLargePen);
    dc->SetBrush(*wxTRANSPARENT_BRUSH);
    left = voffset[0];
    top = voffset[1];
    width = OFFSET_X_WORLD * 2 / DIV;
    height = OFFSET_Y_WORLD * 2 / DIV;
    dc->DrawRectangle(left, top, width, height);

    if(wxGetApp().setting.getFlag(IS_SHOW_GRID)){
        //グリッド
        //TODO
        //SHRT_MAXはgridの倍数ではない！
        //中心から右、下の方向
        for(int i = OFFSET_X_WORLD; i <= OFFSET_X_WORLD * 2; i += grid){
            if(i == OFFSET_X_WORLD){
                //中心＝太線
                dc->SetPen(this->gridLargePen);
            }else{
                dc->SetPen(this->gridPen);
            }
            int x0 = voffset[0] + i / DIV;
            int y0 = voffset[1] + i / DIV;

            dc->DrawLine(x0, voffset[1], x0, voffset[1] + OFFSET_Y_WORLD * 2 / DIV);
            dc->DrawLine(voffset[0], y0, voffset[0] + OFFSET_X_WORLD * 2 / DIV, y0);

            //左＆上
            int j = OFFSET_X_WORLD * 2 - i;
            int x1 = voffset[0] + j / DIV;
            int y1 = voffset[1] + j / DIV;
            dc->DrawLine(x1, voffset[1], x1, voffset[1] + OFFSET_Y_WORLD * 2 / DIV);
            dc->DrawLine(voffset[0], y1, voffset[0] + OFFSET_X_WORLD * 2 / DIV, y1);
            
        }
    }

}


/**
    ポリゴン描画
*/
void MapEditorMainFrame::drawPolygons(wxDC* dc)
{
    if(!wxGetApp().setting.getFlag(IS_SHOW_POLYGONS)){
        return;
    }
    //ペン設定
    dc->SetPen(this->linePen);
//    dc->SetBrush(*wxLIGHT_GREY_BRUSH);

    //TODO 高さ順ソート？
    //ソートするならvalidityのように事前にやっておくべき

    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();

    wxPoint points[8];
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        struct polygon_data* polygon = get_polygon_data(i);
        int type = polygon->type;
        int flags = polygon->flags;
        int vertexCount = polygon->vertex_count;

        if(wxGetApp().getStockManager()->isDeletePolygon(i)){
            continue;
        }
        //まあ無いと思うが…
        if(vertexCount == 0){
            continue;
        }

        //高さ制限をつける
        //TODO 高さを求める方法
        int ceilHeight = polygon->ceiling_height;//get_endpoint_data(polygon->endpoint_indexes[0])->lowest_adjacent_ceiling_height;
        int floorHeight = polygon->floor_height;//get_endpoint_data(polygon->endpoint_indexes[0])->highest_adjacent_floor_height;
//        hpl::error::caution("%d,%d",floorHeight,ceilHeight);
        if(!vmgr->isValidHeight(floorHeight, ceilHeight)){
            continue;
        }
        int vpoint[2];
        for(int j = 0; j < vertexCount; j ++){
            wxGetApp().getViewPointFromWorldPoint(EndpointList[polygon->endpoint_indexes[j]].vertex,
                vpoint);
            points[j].x = vpoint[0];
            points[j].y = vpoint[1];
        }

        //塗りつぶし選択
        //TODO そのほかのモード
        int editMode = wxGetApp().getEventManager()->getEditModeType();
        wxBrush brush;
        switch(editMode){
/*        case EditModeType::EM_DRAW:
            dc->SetBrush(this->polySelNetBrush);
            break;*/
        case EditModeType::EM_POLYGON_TYPE:
            dc->SetBrush(this->polyTypeBrushes[polygon->type]);
            break;
        case EditModeType::EM_FLOOR_HEIGHT:
			brush.SetColour(wxGetApp().getColorFromHeight(polygon->floor_height));
            dc->SetBrush(brush);
            break;
        case EditModeType::EM_CEILING_HEIGHT:
			brush.SetColour(wxGetApp().getColorFromHeight(polygon->ceiling_height));
            dc->SetBrush(brush);
            break;
		case EditModeType::EM_FLOOR_TEXTURE:
			if(wxGetApp().getShapesManager()->isLoadedShapesFile()){
				wxBrush tbr = this->getTexturedBrush(polygon->floor_texture);
				dc->SetBrush(tbr);
			}
			break;
		case EditModeType::EM_CEILING_TEXTURE:
			if(wxGetApp().getShapesManager()->isLoadedShapesFile()){
				wxBrush tbr = this->getTexturedBrush(polygon->ceiling_texture);
				dc->SetBrush(tbr);
			}
			break;
        default:
            //デフォルト
            dc->SetBrush(this->polyBrush);
        }
        //TODO 選択情報

        bool select = false;
//        if(wxGetApp().selectData.isSelected() &&
//            wxGetApp().selectData.containsPolygon(i))
		if(wxGetApp().getStockManager()->isSelectPolygon(i))
        {
            select = true;
        }
        if(select){
            //色
            wxColor col = dc->GetBrush().GetColour();
            this->polySelNetBrush.SetColour(col);
            //ネットポリゴン
            dc->SetBrush(this->polySelNetBrush);
        }else{
            //そのまま

            //ポリゴンチェック
            if(editMode == EditModeType::EM_DRAW &&
                !wxGetApp().getStockManager()->isPolygonValidityStored(i))
            {
                //不正なポリゴン
                dc->SetBrush(this->invalidBrush);
            }
        }

        dc->DrawPolygon(vertexCount, points);
    }
}
wxBrush MapEditorMainFrame::getTexturedBrush(int shapesDescriptor)
{
	int collectionCLUT = GET_DESCRIPTOR_COLLECTION(shapesDescriptor);
	int collection = GET_COLLECTION(collectionCLUT);
	int clut = GET_COLLECTION_CLUT(collectionCLUT);
	int index = GET_DESCRIPTOR_SHAPE(shapesDescriptor);
	wxBrush tbr(this->textureMap[collection][clut][index]);
	return tbr;
}

/**
    線描画
*/
void MapEditorMainFrame::drawLines(wxDC* dc)
{
    if(!wxGetApp().setting.getFlag(IS_SHOW_LINES)){
        return;
    }
    dc->SetPen(*wxBLACK_PEN);
    //高さ制限
    int zMin = wxGetApp().getViewGridManager()->getViewHeightMin();
    int zMax = wxGetApp().getViewGridManager()->getViewHeightMax();

    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data* line = &LineList[i];
        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

        if(wxGetApp().getStockManager()->isDeleteLine(i)){
            continue;
        }
        //高さ
        int floor = line->highest_adjacent_floor;
        int ceiling = line->lowest_adjacent_ceiling;

        bool isHidden = false;
        if(floor < zMin || ceiling > zMax){
            isHidden = true;
            if(!wxGetApp().isRevealHiddenLines){
                //見えない線をうっすら表示。をしない
                continue;
            }
        }

        int beginP[2], endP[2];
        wxGetApp().getViewPointFromWorldPoint(begin->vertex, beginP);
        wxGetApp().getViewPointFromWorldPoint(end->vertex, endP);

        if(isHidden){
            dc->SetPen(*wxGREY_PEN);
        }else{
            bool select = false;
            //選択チェック
//            if(wxGetApp().selectData.isSelected() &&
//                wxGetApp().selectData.containsLine(i))
			if(wxGetApp().getStockManager()->isSelectLine(i))
            {
                select = true;
            }
            if(select){
                dc->SetPen(this->selectedLinePen);
            }else{
                wxPen* lPen = &this->linePen;
                
                if(LINE_IS_TRANSPARENT(line) != 0){
                    if(!hpl::aleph::map::isValidIndex(line->clockwise_polygon_owner, PolygonList.size()) ||
                        !hpl::aleph::map::isValidIndex(line->counterclockwise_polygon_owner, PolygonList.size()))
                    {
                        //nope
                    }else{
                        polygon_data* right = get_polygon_data(line->clockwise_polygon_owner);
                        polygon_data* left = get_polygon_data(line->counterclockwise_polygon_owner);
#ifdef __WXDEBUG__
                        wxASSERT( right && left);
#endif
                        if(right->floor_height == left->floor_height &&
                            right->ceiling_height == left->ceiling_height)
                        {
                            lPen = &this->sameHeightLinePen;
                        }else{
                            lPen = &this->stairLinePen;
                        }
                    }
                }
                //通常ペン
                dc->SetPen(*lPen);
            }

        }
        //選択チェック
        dc->DrawLine(beginP[0], beginP[1], endP[0], endP[1]);
//#ifdef DEBUG
        //デバッグモード
        //矢印にして表示
        const double WING_DEG = 150;
        const int WING_LEN = 10;
        double deg = hpl::math::getDegreeFromVector(endP[0] - beginP[0], endP[1] - beginP[1]);
        for(int j = -1; j < 2; j += 2){
            double wingDeg = deg + j * WING_DEG;
            double rad = hpl::math::getRadianFromDegree(wingDeg);
            int wingP[2] ={
                endP[0] + WING_LEN * cos(rad),
                endP[1] + WING_LEN * sin(rad),
            };
            dc->DrawLine(endP[0], endP[1], wingP[0], wingP[1]);
        }
//#endif
    }
}
void MapEditorMainFrame::drawSides(wxDC* dc)
{
}
void MapEditorMainFrame::drawPoints(wxDC* dc)
{
    //高さ制限
    int zMin = wxGetApp().getViewGridManager()->getViewHeightMin();
    int zMax = wxGetApp().getViewGridManager()->getViewHeightMax();

    //点表示
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        if(wxGetApp().getStockManager()->isDeletePoint(i)){
            continue;
        }
        endpoint_data* ep = get_endpoint_data(i);
        int floor = ep->highest_adjacent_floor_height;
		int ceil = ep->lowest_adjacent_ceiling_height;
		if( floor < zMin || ceil > zMax){
			continue;
		}

        int vpoint[2];
        wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);

        int SIZE = 5;
        //点（小さい四角）を打つ
        dc->SetPen(this->pointPen);
        dc->SetBrush(this->pointBrush);
        dc->DrawRectangle(vpoint[0] - SIZE / 2, vpoint[1] - SIZE / 2,
                SIZE, SIZE);
        //選択中ならしるしをつける
//        if(wxGetApp().selectData.isSelected() &&
//			wxGetApp().selectData.containsPoint(i))
		if(wxGetApp().getStockManager()->isSelectPoint(i))
        {
            dc->SetPen(this->selectedLinePen);
            dc->SetBrush(*wxTRANSPARENT_BRUSH);
            dc->DrawRectangle(vpoint[0] - SIZE / 2, vpoint[1] - SIZE / 2,
                SIZE, SIZE);
        }
    }
}
void MapEditorMainFrame::drawObjects(wxDC* dc)
{
    wxPoint points[3];
    //高さ制限
    int zMin = wxGetApp().getViewGridManager()->getViewHeightMin();
    int zMax = wxGetApp().getViewGridManager()->getViewHeightMax();

    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        if(wxGetApp().getStockManager()->isDeleteObject(i)){
            continue;
        }
        map_object* obj = &(SavedObjectList[i]);

        int type = obj->type;
        if(type == _saved_monster &&
            !wxGetApp().setting.getFlag(IS_SHOW_MONSTERS)){
            continue;
        }
        if(type == _saved_player &&
            !wxGetApp().setting.getFlag(IS_SHOW_PLAYER)){
            continue;
        }
        if(type == _saved_item &&
            !wxGetApp().setting.getFlag(IS_SHOW_ITEMS)){
            continue;
        }
        if(type == _saved_goal &&
            !wxGetApp().setting.getFlag(IS_SHOW_GLOALS)){
            continue;
        }
        if(type == _saved_sound_source &&
            !wxGetApp().setting.getFlag(IS_SHOW_SOUNDS)){
            continue;
        }
        if(type == _saved_object &&
            !wxGetApp().setting.getFlag(IS_SHOW_SCENERY)){
            continue;
        }
        int index = obj->index;

        int facing = obj->facing;
    
        int x = obj->location.x;
        int y = obj->location.y;
        int z = obj->location.z;

        //check height
        //高さ制限の範囲外なら表示しない
        if(z < zMin || z > zMax){
            continue;
        }

        int vpoint[2];
        world_point2d wpoint = {x,y};
        wxGetApp().getViewPointFromWorldPoint(wpoint, vpoint);

        //選択状態をチェック
        bool select = false;
//        if(wxGetApp().selectData.isSelected() &&
//            wxGetApp().selectData.containsObject(i)){
		if(wxGetApp().getStockManager()->isSelectObject(i))
		{
                select = true;
        }
        if(type == _saved_monster || type == _saved_player){
            //三角形を描く
            if(type == _saved_monster){
                //モンスター
                if(index >= _civilian_crew &&
					index <= _civilian_security ||
					index >= _civilian_fusion_crew &&
					index <= _civilian_fusion_security)
                {
                    //ボブ
                    if(select){
                        dc->SetPen(this->selectedAllyPen);
                        dc->SetBrush(this->selectedAllyBrush);
                    }else{
                        dc->SetPen(this->allyPen);
                        dc->SetBrush(this->allyBrush);
                    }
                }else{
                    //moonster
                    if(select){
                        dc->SetPen(this->selectedMonsterPen);
                        dc->SetBrush(this->selectedMonsterBrush);
                    }else{
                        dc->SetPen(this->monsterPen);
                        dc->SetBrush(this->monsterBrush);
                    }
                }

            }else{
                //player
                if(select){
                    dc->SetPen(this->selectedPlayerPen);
                    dc->SetBrush(this->selectedPlayerBrush);
                }else{
                    dc->SetPen(this->playerPen);
                    dc->SetBrush(this->playerBrush);
                }
            }

            double deg = (double)facing / (1<<ANGULAR_BITS) * ROUND_DEGREE;
            double rad = hpl::math::getRadianFromDegree(deg);
            double rad_1 = hpl::math::getRadianFromDegree(deg + WING_DEG);
            double rad_2 = hpl::math::getRadianFromDegree((double)(deg - WING_DEG));

            //三角形を描く
            points[0].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH * cos(rad));
            points[0].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH * sin(rad));
            points[1].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * cos(rad_1));
            points[1].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * sin(rad_1));
            points[2].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * cos(rad_2));
            points[2].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * sin(rad_2));
            dc->DrawPolygon(3, points);

        }else{
            wxImage* bmp;

            //ビットマップ表示
            switch(type){
            case _saved_item:
                if(select){
                    bmp = &this->hilightedItemBitmaps[index];
                }else{
                    bmp = &this->itemBitmaps[index];
                }
                break;
            case _saved_object:
                //scenery
                if(select){
                    bmp = &this->hilightedMapItemBitmaps[MI_Scenery];
                }else{
                    bmp = &this->mapItemBitmaps[MI_Scenery];
                }
                break;
            case _saved_goal:
                //goal(flag)
                if(select){
                    bmp = &this->hilightedMapItemBitmaps[MI_Goal];
                }else{
                    bmp = &this->mapItemBitmaps[MI_Goal];
                }
                break;
            default:
                //sound
                if(select){
                    bmp = &this->hilightedMapItemBitmaps[MI_Sound];
                }else{
                    bmp = &this->mapItemBitmaps[MI_Sound];
                }
            }

            //描画
            bool transparent = true;
            dc->DrawBitmap(*bmp, vpoint[0] - bmp->GetWidth() / 2, vpoint[1] - bmp->GetHeight() /2,
                transparent);
        }
    }

	//ビジュアルモードのスタートポイントの表示
	{
		//座標変換
		int vpoint[2];
		world_point3d location = wxGetApp().getVisualModeManager()->getPlayerPosition();
		world_point2d wpoint = {location.x, location.y};
		wxGetApp().getViewPointFromWorldPoint(wpoint, vpoint);
		wxImage* img = &visualModeStartPositionImage;
		bool transparent = true;
		dc->DrawBitmap(*img, vpoint[0] - img->GetWidth() / 2, vpoint[1] - img->GetHeight() / 2, 
			transparent );
			
	}

}
void MapEditorMainFrame::drawAnnotations(wxDC* dc)
{
    if(!wxGetApp().setting.getFlag(IS_SHOW_ANNOTATIONS)){
        return;
    }
    wxColor oldCol = dc->GetTextForeground();
    wxColor col(wxGetApp().setting.getColorSetting()->colors[ColorType::Strings][0],
                wxGetApp().setting.getColorSetting()->colors[ColorType::Strings][1],
                wxGetApp().setting.getColorSetting()->colors[ColorType::Strings][2]);
    dc->SetTextForeground(col);
    dc->SetBrush(*wxTRANSPARENT_BRUSH);

    for(int i = 0; i < (int)MapAnnotationList.size(); i ++){
        map_annotation *annotation = &MapAnnotationList[i];
        int drawPoint[2];
        wxGetApp().getViewPointFromWorldPoint(annotation->location, drawPoint);

        //点の位置を青丸で表示
	    dc->SetPen(*wxRED_PEN);
		//もし選択されていたら赤丸
        if(wxGetApp().selectData.isSelected() &&
            wxGetApp().selectData.containsAnnotation(i)){
			dc->SetPen(*wxGREEN_PEN);
        }

        dc->DrawCircle(drawPoint[0], drawPoint[1], POINT_DISTANCE_EPSILON);
        //文字列描画
        wxString str(wxConvCurrent->cMB2WX(annotation->text));
        dc->DrawText(str, drawPoint[0], drawPoint[1]);
    }
    dc->SetTextForeground(oldCol);
}
