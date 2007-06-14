#include "MapEditorMainFrame.h"

#include <cmath>

const double ROUND_DEGREE = 360.0;
const double OBJECT_TRIANGLE_LENGTH = 10.0;
const double WING_DEG = 120.0;

/**
    �}�b�v�f�[�^�̕\��
*/
/**
    �w�i�̕`�� <en> draw background 
*/
void MapEditorMainFrame::drawBackground(wxDC* dc)
{
    wxSize size = wxFrame::GetClientSize();
    //�w�i
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

    //�g�`��
    dc->SetPen(this->gridLargePen);
    dc->SetBrush(wxNullBrush);
    left = voffset[0];
    top = voffset[1];
    width = OFFSET_X_WORLD * 2 / DIV;
    height = OFFSET_Y_WORLD * 2 / DIV;
    dc->DrawRectangle(left, top, width, height);

    //�O���b�h
    //TODO
    //SHRT_MAX��grid�̔{���ł͂Ȃ��I
    //���S����E�A���̕���
    for(int i = OFFSET_X_WORLD; i <= OFFSET_X_WORLD * 2; i += grid){
        if(i == OFFSET_X_WORLD){
            //���S������
            dc->SetPen(this->gridLargePen);
        }else{
            dc->SetPen(this->gridPen);
        }
        int x0 = voffset[0] + i / DIV;
        int y0 = voffset[1] + i / DIV;

        dc->DrawLine(x0, voffset[1], x0, voffset[1] + OFFSET_Y_WORLD * 2 / DIV);
        dc->DrawLine(voffset[0], y0, voffset[0] + OFFSET_X_WORLD * 2 / DIV, y0);

        //������
        int j = OFFSET_X_WORLD * 2 - i;
        int x1 = voffset[0] + j / DIV;
        int y1 = voffset[1] + j / DIV;
        dc->DrawLine(x1, voffset[1], x1, voffset[1] + OFFSET_Y_WORLD * 2 / DIV);
        dc->DrawLine(voffset[0], y1, voffset[0] + OFFSET_X_WORLD * 2 / DIV, y1);
        
    }

}
/**
    �|���S���`��
*/
void MapEditorMainFrame::drawPolygons(wxDC* dc)
{
    //�y���ݒ�
    dc->SetPen(this->linePen);
//    dc->SetBrush(*wxLIGHT_GREY_BRUSH);

    //TODO �������\�[�g�H
    //�\�[�g����Ȃ�validity�̂悤�Ɏ��O�ɂ���Ă����ׂ�

    wxPoint points[8];
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        struct polygon_data* polygon = get_polygon_data(i);
        int type = polygon->type;
        int flags = polygon->flags;
        int vertexCount = polygon->vertex_count;

        //�܂������Ǝv�����c
        if(vertexCount == 0){
            continue;
        }

        //��������������
        //TODO ���������߂���@
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

        //�h��Ԃ��I��
        //TODO ���̂ق��̃��[�h
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
            //������
            if(polygon->floor_height < 0){
                //��������
                int red = (int)(255 * (1.0 - (-(double)polygon->floor_height / MAXIMUM_FLOOR_HEIGHT)));
                brush.SetColour(red, 0, 0);
            }else{
                //�����ԁ���
                int notRed = (int)(255 * (polygon->floor_height / MAXIMUM_FLOOR_HEIGHT));
                brush.SetColour(255, notRed, notRed);
            }
            dc->SetBrush(brush);
            break;
        default:
            //�f�t�H���g
            dc->SetBrush(this->polyBrush);
        }
        //TODO �I�����

        bool select = false;
        if(wxGetApp().selectData.isSelected() &&
            wxGetApp().selectData.containsPolygon(i))
        {
            select = true;
        }
        if(select){
            //�F
            wxColor col = dc->GetBrush().GetColour();
            this->polySelNetBrush.SetColour(col);
            //�l�b�g�|���S��
            dc->SetBrush(this->polySelNetBrush);
        }else{
            //���̂܂�

            //�|���S���`�F�b�N
            if(editMode == EditModeType::EM_DRAW &&
                !wxGetApp().isPolygonValidityStored(i))
            {
                //�s���ȃ|���S��
                dc->SetBrush(this->invalidBrush);
            }
        }
        //TODO ������

        dc->DrawPolygon(vertexCount, points);
    }
}
/**
    ���`��
*/
void MapEditorMainFrame::drawLines(wxDC* dc)
{
    dc->SetPen(*wxBLACK_PEN);
    //��������
    int zMin = wxGetApp().getViewGridManager()->getViewHeightMin();
    int zMax = wxGetApp().getViewGridManager()->getViewHeightMax();

    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data* line = &LineList[i];
        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

        //����
        int floor = line->highest_adjacent_floor;
        int ceiling = line->lowest_adjacent_ceiling;

        bool isHidden = false;
        if(floor < zMin || ceiling > zMax){
            isHidden = true;
            if(wxGetApp().isRevealHiddenLines){
                //�����Ȃ�������������\���B�����Ȃ�
                continue;
            }
        }

        int beginP[2], endP[2];
        wxGetApp().getViewPointFromWorldPoint(begin->vertex, beginP);
        wxGetApp().getViewPointFromWorldPoint(end->vertex, endP);

        //�B���
        if(isHidden){
        }else{
            bool select = false;
            //�I���`�F�b�N
            if(wxGetApp().selectData.isSelected() &&
                wxGetApp().selectData.containsLine(i))
            {
                select = true;
            }
            if(select){
                dc->SetPen(this->selectedLinePen);
            }else{
                //�ʏ�y��
                dc->SetPen(this->linePen);
            }

        }
        //�I���`�F�b�N
        dc->DrawLine(beginP[0], beginP[1], endP[0], endP[1]);
    }
}
void MapEditorMainFrame::drawSides(wxDC* dc)
{
}
void MapEditorMainFrame::drawPoints(wxDC* dc)
{
    //��������
    int zMin = wxGetApp().getViewGridManager()->getViewHeightMin();
    int zMax = wxGetApp().getViewGridManager()->getViewHeightMax();

    //�_�\��
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = get_endpoint_data(i);
        int floor = ep->highest_adjacent_floor_height;
		int ceil = ep->lowest_adjacent_ceiling_height;
		if( floor < zMin || ceil > zMax){
			continue;
		}

        int vpoint[2];
        wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);

        //�_�i�������l�p�j��ł�
        dc->SetPen(this->pointPen);
        dc->SetBrush(this->pointBrush);

        //�I�𒆂Ȃ炵�邵������
        if(wxGetApp().selectData.isSelected() &&
            wxGetApp().selectData.containsPoint(i))
        {
            dc->SetPen(this->selectedLinePen);
            dc->SetBrush(wxNullBrush);
            int SIZE = 5;
            dc->DrawRectangle(vpoint[0] - SIZE / 2, vpoint[1] - SIZE / 2,
                SIZE, SIZE);
        }
    }
}
void MapEditorMainFrame::drawObjects(wxDC* dc)
{
    wxPoint points[3];
    //��������
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
        //���������͈̔͊O�Ȃ�\�����Ȃ�
        if(z < zMin || z > zMax){
            continue;
        }

        int vpoint[2];
        world_point2d wpoint = {x,y};
        wxGetApp().getViewPointFromWorldPoint(wpoint, vpoint);

        //�I����Ԃ��`�F�b�N
        bool select = false;
        if(wxGetApp().selectData.isSelected() &&
            wxGetApp().selectData.containsObject(i)){
                select = true;
        }
        if(type == _saved_monster || type == _saved_player){
            //�O�p�`��`��
            if(type == _saved_monster){
                //�����X�^�[
                if(index >= _civilian_crew &&
					index <= _civilian_security ||
					index >= _civilian_fusion_crew &&
					index <= _civilian_fusion_security)
                {
                    //�{�u
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

            //�O�p�`��`��
            points[0].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH * cos(rad));
            points[0].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH * sin(rad));
            points[1].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * cos(rad_1));
            points[1].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * sin(rad_1));
            points[2].x = vpoint[0] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * cos(rad_2));
            points[2].y = vpoint[1] + (int)(OBJECT_TRIANGLE_LENGTH / 2.0 * sin(rad_2));
            dc->DrawPolygon(3, points);

        }else{
            wxImage* bmp;

            //�r�b�g�}�b�v�\��
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

            //�`��
            bool transparent = true;
            dc->DrawBitmap(*bmp, vpoint[0] - bmp->GetWidth() / 2, vpoint[1] - bmp->GetHeight() /2,
                transparent);
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
