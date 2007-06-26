#include "MapEditorMainFrame.h"
#include "AnnotationDialog.h"

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/**
    ���{�^�����������Ƃ��ɌĂ΂��
*/
void MapEditorMainFrame::OnLeftDown(wxMouseEvent &ev)
{
    //�J�[�\���ݒ�
    wxGetApp().setCursor();
    //�}�E�X���W�L�^
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
    //�I���f�[�^
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
    
    //�O���b�h�}�l�[�W���[
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    //�r���[�I�t�Z�b�g
    int voffset[2];
    vmgr->getOffset(voffset);
    int div = vmgr->getZoomDivision();

    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
    int mx = ev.m_x;
    int my = ev.m_y;

    if(sel->isSelected()){
        //���ɑI��

        //�}�E�X���W���I�𕔕��Ɋ܂܂�邩�`�F�b�N
        if(hpl::aleph::map::isPointInSelection(mx, my,
            voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD,
            POINT_DISTANCE_EPSILON, LINE_DISTANCE_EPSILON, OBJECT_DISTANCE_EPSILON,
            sel, zMax, zMin, div))
        {
            //�I�𕔕����N���b�N���Ă���
            //���I�t�Z�b�g��ݒ肷��
            //<en> clicked on selection datas
            //-> set offsets
            this->setupSelectDataGroupOffsets(mx, my);
            return;
        }else{
            //�N���b�N���Ă��Ȃ�
            //���I������
            //<en> no click on selection datas
            //-> release all selections
            sel->clear();
        }
    }
    //�����I�����Ă��Ȃ����
    //���I���ł��邩�����Ă݂܂�
    if(this->tryToSelectOneItem(ev)){
        //�I��͈͉͂������܂�
        wxGetApp().getEventManager()->setSelectingGroup(false);
    }else{
        //�I������Ȃ�����
        //�͈͑I���̊J�n
        wxGetApp().getEventManager()->setSelectGroupStartPoint(mx, my);
        //�I�����̉���
        sel->clear();
    }
}

/**
    �I�t�Z�b�g��ݒ肵�܂�
    @param mx,my �r���[���W�̊�_�ʒu
*/
void MapEditorMainFrame::setupSelectDataGroupOffsets(int mx, int my)
{
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    //�_ <en> points
    for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
        endpoint_data* ep = get_endpoint_data(sel->getSelPoints()->at(i).index);
        //�r���[���W�ɕϊ�
        int vpoint[2];
        wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);

        //�����Z
        sel->getSelPoints()->at(i).offset[0] = vpoint[0] - mx;
        sel->getSelPoints()->at(i).offset[1] = vpoint[1] - my;
    }

    //�� <en> lines
    for(int i = 0; i < (int)sel->getSelLines()->size(); i ++){
        line_data* line = get_line_data(sel->getSelLines()->at(i).index);
        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
        int vpointStart[2];
        int vpointEnd[2];
        wxGetApp().getViewPointFromWorldPoint(begin->vertex, vpointStart);
        wxGetApp().getViewPointFromWorldPoint(end->vertex, vpointEnd);

        //�I�t�Z�b�g�ݒ�
        sel->getSelLines()->at(i).offset[0][0] = vpointStart[0] - mx;
        sel->getSelLines()->at(i).offset[0][1] = vpointStart[1] - my;
        sel->getSelLines()->at(i).offset[1][0] = vpointEnd[0] - mx;
        sel->getSelLines()->at(i).offset[1][1] = vpointEnd[1] - my;
    }

    //�|���S��
    for(int i = 0; i < (int)sel->getSelPolygons()->size(); i ++){
        hpl::aleph::map::SelPolygon* selpoly = &sel->getSelPolygons()->at(i);
        polygon_data* poly = get_polygon_data(selpoly->index);
        int n = poly->vertex_count;
        selpoly->num = n;
        for(int j = 0; j < n; j ++){
            int vpoint[2];
            endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[j]);
            wxGetApp().getViewPointFromWorldPoint(ep->vertex, vpoint);

            //�I�t�Z�b�g
            selpoly->offset[j][0] = vpoint[0] - mx;
            selpoly->offset[j][1] = vpoint[1] - my;
        }
    }

    //�I�u�W�F�N�g
    for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
        map_object* obj = &SavedObjectList[sel->getSelObjects()->at(i).index];
        //�r���[���W�ɕϊ�
        int vpoint[2];
        wxGetApp().getViewPointFromWorldPoint(obj->location.x, obj->location.y, vpoint);

        //�����Z
        sel->getSelObjects()->at(i).offset[0] = vpoint[0] - mx;
        sel->getSelObjects()->at(i).offset[1] = vpoint[1] - my;
    }

}

/**
    @param ev
    @return �I���ɐ��������ꍇ�^
*/
bool MapEditorMainFrame::tryToSelectOneItem(wxMouseEvent& ev)
{
    //�V�t�g�L�[
    bool shift = ev.ShiftDown();

    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
    //�C�x���g�}�l�[�W���[
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();

    //�r���[�I�t�Z�b�g
    int voffset[2];
    vmgr->getOffset(voffset);
    int div = vmgr->getZoomDivision();

    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
    int mx = ev.m_x;
    int my = ev.m_y;

    if(!shift){
        //�V�t�g�L�[���������ɃN���b�N�������U�������
        sel->clear();
        emgr->setSelectingGroup(false);
    }

    //�I���̗D�揇�ʂ�
    //1:�I�u�W�F�N�g
    //2:�_
    //3:��
    //4:�|���S��


    //�I�u�W�F�N�g
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        map_object* obj = &SavedObjectList[i];
        int x = obj->location.x;
        int y = obj->location.y;
        int z = obj->location.z;

        //�������͈͊O���ǂ���
        if(z > zMax || z < zMin){
            continue;
        }

        //�_�I������
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
            //�I�u�W�F�N�g�̃v���p�e�B�E�_�C�A���O��\������
            //TODO
            this->objPropDialog.setObjIndex(i);
            this->objPropDialog.Show(true);
            return true;
        }
    }

    //no obj selected
    //TODO �I��ID�֘A�̎���
    this->objPropDialog.setObjIndex(NONE);


    //////////
    //�_
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = get_endpoint_data(i);

        //�����`�F�b�N
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
            //��������
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

        //�����`�F�b�N
        int floor = line->highest_adjacent_floor;
        int ceiling = line->lowest_adjacent_ceiling;
        if(floor > zMax || ceiling < zMin){
            continue;
        }

        if(hpl::aleph::map::isSelectLine(mx, my,
            start->vertex.x, start->vertex.y, end->vertex.x, end->vertex.y,
            voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, LINE_DISTANCE_EPSILON))
        {
            //�I��
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

    //�|���S��
    //TODO �������Ƀ\�[�g����
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
        
        //�|���S���v���p�e�B�\��
        //TODO
        this->polyPropDialog.setPolyIndex(polyIndex);
        this->polyPropDialog.Show(true);

        //�I�t�Z�b�g
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
    //�h��Ԃ��\�ȃ|���S���f�[�^���擾���܂�
    //hp::aleph::map::getValidPolygons();
}
void MapEditorMainFrame::doLButtonOnHandTool(wxMouseEvent& ev)
{
    //MouseMotion�Ɋۓ���
    
}
void MapEditorMainFrame::doLButtonOnLineTool(wxMouseEvent& ev)
{
    //���ǉ�
#ifdef MAP_VIEWER
#else
    //�I������
    wxGetApp().selectData.clear();

    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();

    int mx = ev.m_x;
    int my = ev.m_y;
    //���E���W�ɂ���
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mx, my);

    bool isFirst = wxGetApp().isFirstOfLineToAdd;

    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    
    int voffset[2];
    vmgr->getOffset(voffset);
    int div = wxGetApp().getViewGridManager()->getZoomDivision();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();

    //�d�Ȃ�_�����邩�ǂ����`�F�b�N
    int pointIndex = hpl::aleph::map::getSelectPointIndex(wpoint, POINT_DISTANCE_EPSILON, zMin, zMax);
    //�d�Ȃ�������邩���肷��
    int lineIndex = hpl::aleph::map::getSelectLineIndex(wpoint, LINE_DISTANCE_EPSILON, zMin, zMax);

    hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
    if(pointIndex != NONE)
    {
        //�����̓_���N���b�N���Ă���
        /*
        1:�_�̏�ŃN���b�N
	        1:�ŏ��̃N���b�N
		        �O��N���b�N�_�̍X�V
	        2:���ڈȍ~�̃N���b�N
		        1:���ɐ������݂��Ă���
			        �������Ȃ�
		        2:���͑��݂��Ă��Ȃ�
			        ���̒ǉ�
		        �O��N���b�N�_�̍X�V
        */
        if(isFirst){
            //�ŏ��̃N���b�N
            //�n�_�Ƃ���
            wxGetApp().prevPointIndex = pointIndex;

        }else{
            //2��ڈȍ~�̃N���b�N
            //�����_���N���b�N���Ă��邩�H
            if(wxGetApp().prevPointIndex == pointIndex){
                //�n�_�Ƃ���
            }else{
                //���ɐ������݂��Ă��邩�H
                int lineIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(
                    wxGetApp().prevPointIndex, pointIndex);
                if(lineIndex != NONE){
                    //�����������݂̓_���n�_�Ƃ���
                    wxGetApp().prevPointIndex = pointIndex;
                }else{
                    //�łȂ��ΐ����쐬����
                    //TODO
                }
            }
        }

        //���p�_�E�n�_�E�I�_�ɂ���
        wxGetApp().isFirstOfLineToAdd = false;
    }else{
        //���𓥂�ł��Ȃ����`�F�b�N���܂�
        if(lineIndex != NONE){
            /*
                2:���̏�ŃN���b�N
	                1:�ŏ��̃N���b�N
		                1:�|���S���ɏ��������
			                �x�����o���ĉ������Ȃ�
		                2:�������Ȃ���
			                ���̐����폜
			                �_��ǉ�
			                ���̎n�_���V�_���I�_�Ƃ����V����ǉ�
			                �V�_�����̏I�_���I�_�Ƃ����V����ǉ�
			                �O��N���b�N�_�̍X�V
	                2:���ڈȍ~�̃N���b�N
		                ����
            */
            line_data* line = get_line_data(lineIndex);
            assert(line != NULL);

            int newPointIndex = NONE;
            //�|���S���ɏ������Ă��邩�m���߂܂�
            if(line->clockwise_polygon_owner != NONE || 
                line->counterclockwise_polygon_owner != NONE)
            {
                //�|���S���ɑ������
                //�x�����o���B���𕪒f�����肵�Ȃ�
                hpl::error::caution("cannot divide line , because line belongs to polygon (line's index:%d, clockwise polygon's index:%d, counterclockwise polygon's index:%d)",
                    lineIndex, line->clockwise_polygon_owner, line->counterclockwise_polygon_owner);
                //�Ɨ������_��ǉ�����
                endpoint_data ep;
                hpl::aleph::map::createPoint(wpoint, &ep, POINT_DISTANCE_EPSILON);
                newPointIndex = hpl::aleph::map::addEndpoint(ep);
                assert(newPointIndex != NONE);
            }else{
                //�n�_�A�I�_�̏��擾
                //endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
                //endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

                //�����폜
                smgr->deleteLine(lineIndex);
                smgr->updateDeletes();
                //�_��ǉ�
                endpoint_data ep;
                assert(hpl::aleph::map::createPoint(wpoint, &ep, POINT_DISTANCE_EPSILON));
                newPointIndex = hpl::aleph::map::addEndpoint(ep);
                assert(newPointIndex != NONE);
                endpoint_data *newEp = get_endpoint_data(newPointIndex);

                //�n�_���_�̐���ǉ�
                line_data newLine1;
                assert(hpl::aleph::map::createLine(line->endpoint_indexes[0], line->endpoint_indexes[1], &newLine1));
                int newLine1Index = hpl::aleph::map::addLine(newLine1);
                assert(newLine1Index != NONE);

                //�_���I�_�̐���ǉ�
                line_data newLine2;
                //TODO
            }
        }else{
            //�V�K�ǉ�
            if(wxGetApp().isFirstOfLineToAdd){
                //�ŏ��̓_
                endpoint_data ep;
                assert(hpl::aleph::map::createPoint(wpoint, &ep, POINT_DISTANCE_EPSILON));

            }else{
                //�_��ǉ�
            }

            //�_��ǉ����Ă������ǉ�����
        }
    }
    wxGetApp().isFirstOfLineToAdd = isFirst;

    //�����X�V����
    wxGetApp().getStockManager()->updateDeletes();
    
#endif
}
void MapEditorMainFrame::doLButtonOnMagnifyTool(wxMouseEvent& ev)
{
    bool shift = ev.ShiftDown();
    wxCommandEvent dummy;
    if(shift){
        //�k��
        this->OnZoomOut(dummy);
    }else{
        this->OnZoomIn(dummy);
    }
}
void MapEditorMainFrame::doLButtonOnSkullTool(wxMouseEvent& ev)
{
    //�I�u�W�F�N�g�z�u
#ifdef MAP_VIEWER
#else
    int mx = ev.m_x;
    int my = ev.m_y;
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mx, my);
    //�_�̒��ɓ���|���S�����擾���܂�
    //std::vector<int> polyIndexes = hpl::aleph::map::getPolygonIndexesIncludePoint(wpoint);
    //TODO
#endif
}
void MapEditorMainFrame::doLButtonOnTextTool(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
    //�A�m�e�[�V�����ǉ�
    //�_�C�A���O����
    AnnotationDialog dlg;
    map_annotation sample;
    //������
    memset(&sample, 0, SIZEOF_map_annotation);

    //�}�E�X���W�̈ʒu�ɒǉ�����
    int viewX = ev.m_x;
    int viewY = ev.m_y;
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(viewX, viewY);
    sample.location.x = wpoint.x;
    sample.location.y = wpoint.y;
    sample.polygon_index = NONE;

    //�_�C�A���O�\��
    dlg.Create(this, ID_ANNOTATION_DIALOG, sample);
    if(dlg.ShowModal() == wxID_OK){
        //����
        //�A�m�e�[�V�����f�[�^���擾
        map_annotation newAnnotation = dlg.getAnnotation();
        //�ǉ�
        hpl::aleph::map::addAnnotation(newAnnotation);
    }
#endif
}
void MapEditorMainFrame::doLButtonOnPolygonTool(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
    //�͈͑I���J�n
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
    �E�{�^�����������Ƃ��ɌĂ΂��
*/
void MapEditorMainFrame::OnRightDown(wxMouseEvent& ev)
{
    //�J�[�\���ݒ�
    wxGetApp().setCursor();
    int mx = ev.m_x;
    int my = ev.m_y;
    //�}�E�X���W�L�^
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    vmgr->setNewMousePoint(mx, my);

    //�|�b�v�A�b�v���j���[���o��
    //TODO
    //�}�E�X���W�����[���h���W�ɂ���
    world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(mx, my);
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    int div = vmgr->getZoomDivision();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();

    int editMode = emgr->getEditModeType();
    int toolType = emgr->getToolType();
    if(editMode == EditModeType::EM_DRAW && toolType == ToolType::TI_ARROW){
        //�_�̏�ŉE�N���b�N�������H
        int epIndex = hpl::aleph::map::getSelectPointIndex(wmp, POINT_DISTANCE_EPSILON * div, zMin, zMax);
        if(epIndex != NONE){
            //�_�|�b�v�A�b�v�\��
            PopupMenu(&wxGetApp().pointPopupMenu);
        }else{
            //�_�͉�����Ȃ�����
            int lineIndex = hpl::aleph::map::getSelectLineIndex(wmp, LINE_DISTANCE_EPSILON * div, zMin, zMax);
            if(lineIndex != NONE){
                //���������ꂽ
                //�����v���p�e�B������
                PopupMenu(&wxGetApp().linePopupMenu);
            }
        }
    }

}
///////////////////////////////////////////////////////
void MapEditorMainFrame::OnRightUp(wxMouseEvent& ev)
{
    //�J�[�\���ݒ�
    wxGetApp().setCursor();
    //�}�E�X���W�L�^
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
}
void MapEditorMainFrame::OnLeftUp(wxMouseEvent& ev)
{
    //�J�[�\���ݒ�
    wxGetApp().setCursor();
    //�}�E�X���W�L�^
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

    //�C�x���g�}�l�[�W���[
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

    //�|���S����Ԃ��X�V���܂�
    wxGetApp().getStockManager()->updatePolygonValidityStored();
    Refresh();
}

void MapEditorMainFrame::doLUpOnArrowTool(wxMouseEvent& ev)
{
    //�I���f�[�^
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    //�O���b�h�}�l�[�W���[
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

    if(sel->isSelectOneObject()){
        //�I�u�W�F�N�g��I�����Ă�����
        //�I�u�W�F�N�g���_�C�A���O�\��
        //TODO
        this->objPropDialog.Show(true);
    }else if(sel->isSelectOnePolygon()){
        //�|���S�����_�C�A���O�\��
    }
    //TODO
    //�_�A���ASide�͉E�N���b�N���j���[�Ńv���p�e�B��I���������̂ݕ\������
    
    int mx = ev.m_x;
    int my = ev.m_y;

    if(emgr->isSelectingGroup()){
        //�͈͑I�𒆂������B��`���̃A�C�e����I���Ƃ���
        //�I���J�n�ʒu
        int selStartPoint[2];
        emgr->getSelectGroupStartPoint(selStartPoint);
        
        //�I����񏉊���
        sel->clear();
        
        //�_ <en> points
        for(int i = 0; i < (int)EndpointList.size(); i ++){
            endpoint_data* ep = get_endpoint_data(i);
            //�����`�F�b�N
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
                //�ǉ�
                int offset[2] = {0,0};
                sel->addSelPoint(i, offset);
            }
        }

        //�� <en> lines
        for(int i = 0; i < (int)LineList.size(); i ++){
            line_data* line = get_line_data(i);
            endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
            endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
            int beginVPoint[2];
            int endVPoint[2];
            wxGetApp().getViewPointFromWorldPoint(begin->vertex, beginVPoint);
            wxGetApp().getViewPointFromWorldPoint(end->vertex, endVPoint);

            //�����`�F�b�N
            if(!vmgr->isValidHeight(line->highest_adjacent_floor,
                line->lowest_adjacent_ceiling))
            {
                continue;
            }
            if(hpl::math::isLineInRect(beginVPoint[0], beginVPoint[1],
                endVPoint[0], endVPoint[1],
                mx, my, selStartPoint[0], selStartPoint[1]))
            {
                //�ǉ�
                int offset[2][2] = {{0,0},{0,0}};
                sel->addSelLine(i, offset);
            }
        }

        //�|���S��
        for(int i = 0; i < (int)PolygonList.size(); i ++){
            polygon_data* poly = get_polygon_data(i);
            int n = poly->vertex_count;
            if(n < 1 || n >= MAXIMUM_VERTICES_PER_POLYGON){
                continue;
            }
            //�����`�F�b�N
            if(!vmgr->isValidHeight(poly->floor_height,
                poly->ceiling_height))
            {
                continue;
            }
            //�S�Ă̓_����`���Ȃ�|���S����I��
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
                //�o�^
                int offset[MAXIMUM_VERTICES_PER_POLYGON][2];
                memset(offset, 0, sizeof(int) * MAXIMUM_VERTICES_PER_POLYGON * 2);
                sel->addSelPolygon(i, offset, n);
            }
        }
    

        //�I�u�W�F�N�g
        for(int i = 0; i < (int)SavedObjectList.size(); i ++){
            map_object* obj = &(SavedObjectList[i]);
            //�����`�F�b�N
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
                //�ǉ�
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
        //n�p�`�̍��W���v�Z
        double polyPointsView[MAXIMUM_VERTICES_PER_POLYGON][2];
        int n = wxGetApp().presetPolygonVertexCount;
        hpl::math::getRectangleScaledPreparedPolygon(ev.m_x, ev.m_y,
            selStartPoint[0], selStartPoint[1], n,
            polyPointsView);
        //���[���h���W�`�ɕϊ�
        world_point2d polyPointsWorld[MAXIMUM_VERTICES_PER_POLYGON];
        for(int i = 0; i < n; i ++){
            polyPointsWorld[i] = wxGetApp().getWorldPointFromViewPoint(
                (int)polyPointsView[i][0], (int)polyPointsView[i][1]);
        }
        //�|���S������
        hpl::aleph::map::addNewPolygon(polyPointsWorld, n);
    }
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/**
    �}�E�X���ړ������Ƃ��ɌĂ΂��
*/
void MapEditorMainFrame::OnMotion(wxMouseEvent &ev)
{
    //�J�[�\���ݒ�
    wxGetApp().setCursor();

    //�}�E�X���W�L�^
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

    int editModeType = wxGetApp().getEventManager()->getEditModeType();

    const int UPDATE_POLYGON_VALIDITY_INTERVAL = 10;
    static int updatePolygonValidityCount = UPDATE_POLYGON_VALIDITY_INTERVAL;

    //�|���S���������`�F�b�N�J�E���g
    updatePolygonValidityCount ++;


    int mx = ev.m_x;
    int my = ev.m_y;
    if(ev.ButtonIsDown(wxMOUSE_BTN_LEFT)){
        if(updatePolygonValidityCount >= UPDATE_POLYGON_VALIDITY_INTERVAL){
            //�|���S�����������X�V
            wxGetApp().getStockManager()->updatePolygonValidityStored();
        }

        //���{�^���������Ȃ��瓮���Ă���
        bool shift = ev.ShiftDown();
        bool ctrl = ev.ControlDown();
#ifdef MAP_VIEWER
        //Viewer��p�̓���
        //�N���b�N���Ă���Έړ�
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            //�I�t�Z�b�g�ړ�
            moveMapOffset(mx, my);
        }
#else

        //�ҏW���[�h���Ƃɓ��삪�قȂ�
        
        int toolType = wxGetApp().getEventManager()->getToolType();
        
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            //�R���g���[�������Ȃ���A
            //���邢�̓n���h�c�[����D&D
            //���I�t�Z�b�g�ړ�
            this->moveMapOffset(ev.m_x, ev.m_y);
        }else{
            //Ctrl�����Ȃ�

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
        //�����Ă��Ȃ����
        if(editModeType == EditModeType::EM_DRAW &&
            wxGetApp().getEventManager()->getToolType() == ToolType::TI_LINE)
        {
            this->doMouseMotionOnLineTool(ev);
        }
    }

    //�X�V
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
        //���c�[����D&D�͍l�����Ȃ�
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
    //�����͈͑I�𒆂Ȃ�H
    //�����ł��邱�Ƃ͂Ȃ�

    //�����I�𒆂̃}�b�v�A�C�e��������΁A�������ړ�������
    
    //�I�����
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    int div = vmgr->getZoomDivision();

    int mx = ev.m_x;
    int my = ev.m_y;

    if(sel->isSelected()){
        //�I��
        //�I�𕨂̈ړ�
        
        //���[���h���W�n�ɂ���
        world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(mx, my);

        //�_
        for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
            struct hpl::aleph::map::SelPoint* selp = &sel->getSelPoints()->at(i);
            //�ʒu�ύX
            get_endpoint_data(selp->index)->vertex.x = wmp.x + selp->offset[0] * div;
            get_endpoint_data(selp->index)->vertex.y = wmp.x + selp->offset[1] * div;
        }

        //��
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

        //�|���S��
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

        //�I�u�W�F�N�g
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
    //�ړ�
    this->moveMapOffset(ev.m_x, ev.m_y);
}
/**
    ���c�[��
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

    //�_�𓥂�ł��Ȃ����m�F
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
    //�J�[�\���ݒ�
    wxGetApp().setCursor();

    int zDelta = ev.m_wheelRotation;
    hpl::aleph::view::HPLViewGridManager* mgr = wxGetApp().getViewGridManager();

    //�R���g���[���L�[
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

// �I�t�Z�b�g���w�肵���}�E�X�|�C���g�ɂ���Ĉړ������܂�
void MapEditorMainFrame::moveMapOffset(int x, int y)
{
    hpl::aleph::view::HPLViewGridManager* mgr = wxGetApp().getViewGridManager();
    //�ȑO�̃}�E�X�|�W�V�����𓾂܂�
    int oldMPoint[2];
    mgr->getOldMousePoint(oldMPoint);
    int deltaX = x - oldMPoint[0];
    int deltaY = y - oldMPoint[1];

    //�I�t�Z�b�g��ݒ肵�܂�
    int voffset[2];
    mgr->getOffset(voffset);
    voffset[0] += deltaX;
    voffset[1] += deltaY;
    mgr->setOffset(voffset[0], voffset[1]);
}
