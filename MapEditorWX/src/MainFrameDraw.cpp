#include "MapEditorMainFrame.h"

const double ROUND_DEGREE = 360.0;
const double OBJECT_TRIANGLE_LENGTH = 10.0;
const double OBJECT_TRIANGLE_WING_DEGREE = 120.0;

/**
    マップデータの表示
*/
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
    dc->SetBrush(wxNullBrush);
    left = voffset[0];
    top = voffset[1];
    width = OFFSET_X_WORLD * 2 / DIV;
    height = OFFSET_Y_WORLD * 2 / DIV;
    dc->DrawRectangle(left, top, width, height);

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
/**
    ポリゴン描画
*/
void MapEditorMainFrame::drawPolygons(wxDC* dc)
{
    //色設定
    wxPen linePen(wxGetApp().setting.getColorSetting()->lines[0],
        wxGetApp().setting.getColorSetting()->lines[1],
        wxGetApp().setting.getColorSetting()->lines[2]);

    dc->SetPen(linePen);
//    dc->SetBrush(*wxLIGHT_GREY_BRUSH);

    //TODO 高さ順ソート？
    //ソートするならvalidityのように事前にやっておくべき

    wxPoint points[8];
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        struct polygon_data* polygon = get_polygon_data(i);
        int type = polygon->type;
        int flags = polygon->flags;
        int vertexCount = polygon->vertex_count;

        //まあ無いと思うが…
        if(vertexCount == 0){
            continue;
        }

        //高さ制限をつける
        //TODO 高さを求める方法
        int ceilHeight = polygon->ceiling_height;//get_endpoint_data(polygon->endpoint_indexes[0])->lowest_adjacent_ceiling_height;
        int floorHeight = polygon->floor_height;//get_endpoint_data(polygon->endpoint_indexes[0])->highest_adjacent_floor_height;
        if(floorHeight < wxGetApp().getViewGridManager()->getViewHeightMin() ||
            ceilHeight > wxGetApp().getViewGridManager()->getViewHeightMax()){
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
        case EditModeType::EM_DRAW:
            brush.SetColour(wxGetApp().setting.getColorSetting()->polygons[0],
                wxGetApp().setting.getColorSetting()->polygons[1],
                wxGetApp().setting.getColorSetting()->polygons[2]);
            dc->SetBrush(brush);
            break;
        case EditModeType::EM_POLYGON_TYPE:
            dc->SetBrush(this->polyTypeBrushes[polygon->type]);
            break;
        case EditModeType::EM_FLOOR_HEIGHT:
            //床高さ
            if(polygon->floor_height < 0){
                //負→黒赤
                int red = (int)(255 * (1.0 - (-(double)polygon->floor_height / MAXIMUM_FLOOR_HEIGHT)));
                brush.SetColour(red, 0, 0);
            }else{
                //正→赤→白
                int notRed = (int)(255 * (polygon->floor_height / MAXIMUM_FLOOR_HEIGHT));
                brush.SetColour(255, notRed, notRed);
            }
            dc->SetBrush(brush);
            break;
        default:
            brush.SetColour(wxGetApp().setting.getColorSetting()->polygons[0],
                wxGetApp().setting.getColorSetting()->polygons[1],
                wxGetApp().setting.getColorSetting()->polygons[2]);
            dc->SetBrush(brush);
        }
        //TODO 選択情報

        //TODO 整合性

        dc->DrawPolygon(vertexCount, points);
    }
}
/**
    線描画
*/
void MapEditorMainFrame::drawLines(wxDC* dc)
{
    dc->SetPen(*wxBLACK_PEN);
    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data* line = &LineList[i];
        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
        int beginP[2], endP[2];
        wxGetApp().getViewPointFromWorldPoint(begin->vertex, beginP);
        wxGetApp().getViewPointFromWorldPoint(end->vertex, endP);
        dc->DrawLine(beginP[0], beginP[1], endP[0], endP[1]);
    }
}
void MapEditorMainFrame::drawSides(wxDC* dc)
{
}
void MapEditorMainFrame::drawPoints(wxDC* dc)
{
}
void MapEditorMainFrame::drawObjects(wxDC* dc)
{
    wxPoint points[3];
    //高さ制限
    int zMin = wxGetApp().getViewGridManager()->getViewHeightMin();
    int zMax = wxGetApp().getViewGridManager()->getViewHeightMax();

    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        map_object* obj = &(SavedObjectList[i]);

        int type = obj->type;
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

        int vpoing[2];
        world_point2d wpoint = {x,y};
        wxGetApp().getViewPointFromWorldPoint(wpoint, vpoint);

        //選択状態をチェック
        bool select = false;
        if(wxGetApp().selectData.isSelected() &&
            wxGetApp().selectData.containsObject(i)){
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
            double rad1 = hpl::math::getRadianFromDegree(deg + OBJECT_TRIANGLE_WING_DEGREE);
            double rad2 = hpl::math::getRadianFromDegree(deg - OBJECT_TRIANGLE_WING_DEGREE);

            //三角形を描く
            points[0].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH * cos(rad));
            points[0].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH * sin(rad));
            points[1].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * cos(rad1));
            points[1].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * sin(rad1));
            points[2].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * cos(rad2));
            points[2].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * sin(rad2));
            dc->DrawPolygon(3. points);

        }else{
            //
            //ビットマップ表示
            case _saved_item:
                break;
            case _saved_object:
                //scenery
                break;
            case _saved_goal:
                break;
            default:
            //sound
        }
    }
}
void MapEditorMainFrame::drawAnnotations(wxDC* dc)
{
    wxColor oldCol = dc->GetTextForeground();
    wxColor col(wxGetApp().setting.getColorSetting()->strings[0],
                wxGetApp().setting.getColorSetting()->strings[1],
                wxGetApp().setting.getColorSetting()->strings[2]);
    dc->SetTextForeground(col);
    for(int i = 0; i < (int)MapAnnotationList.size(); i ++){
        map_annotation *annotation = &MapAnnotationList[i];
        int drawPoint[2];
        wxGetApp().getViewPointFromWorldPoint(annotation->location, drawPoint);

        //
        wxString str(wxConvCurrent->cMB2WX(annotation->text));
        dc->DrawText(str, drawPoint[0], drawPoint[1]);
    }
    dc->SetTextForeground(oldCol);
}
