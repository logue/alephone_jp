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
            //this->objectPropDialog.Show(true);
            return true;
        }
    }

    //no obj selected
    //TODO �I��ID�֘A�̎���
    //this->objectPropDialog->setSelectedObjectIndex(NONE);


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

    int mx = ev.m_x;
    int my = ev.m_y;
    //���E���W�ɂ���
    world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mx, my);

    bool isFirst = wxGetApp().isFirstOfLineToAdd;

    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    
    
    //�d�Ȃ�_�����邩�ǂ����`�F�b�N
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
    //�d�Ȃ�������邩���肷��

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
            wxGetApp().prevPointIndex = 
        }else{
            //2��ڈȍ~�̃N���b�N
            //�����_���N���b�N���Ă����牽�����Ȃ�
            //TODO
            //�łȂ��ΐ����쐬����
            //TODO
        }

        //���p�_�E�n�_�E�I�_�ɂ���
        wxGetApp().isFirstOfLineToAdd = false;
    }else{
        //���𓥂�ł��Ȃ����`�F�b�N���܂�
        bool onLine = false;
        for(int i = 0; i < (int)LineList.size(); i ++){
            line_data* line = get_line_data(i);
            endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
            endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
            if(hpl::aleph::map::isSelectLine(mx, my, begin->vertex.x, begin->vertex.y,
                end->vertex.x, end->vertex.y, voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD,
                div, LINE_DISTANCE_EPSILON))
            {
                //���𓥂�ł���
                //TODO �ؒf���܂�
                //TODO �_��ǉ����Đڑ����Ȃ����܂�
                onLine = true;
                break;
            }
        }
        if(onLine){
        }else{
            //�V�K�ǉ�
            if(wxGetApp().isFirstOfLineToAdd){
                //�ŏ��̓_
            }else{
                //�_��ǉ�
            }

            //�_��ǉ����Ă������ǉ�����
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
    //�}�E�X���W�L�^
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
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

    if(updatePolygonValidityCount >= UPDATE_POLYGON_VALIDITY_INTERVAL){
        //TODO
    }
    if(ev.ButtonIsDown(wxMOUSE_BTN_LEFT)){
        //���{�^���������Ȃ��瓮���Ă���
        bool shift = ev.ShiftDown();
        bool ctrl = ev.ControlDown();
#ifdef MAP_VIEWER
        //Viewer��p�̓���
        //�N���b�N���Ă���Έړ�
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            
        }
#else

        //�ҏW���[�h���Ƃɓ��삪�قȂ�
        
        int toolType = wxGetApp().getEventManager()->getToolType();
        
        if(ctrl ||
            editModeType == EditModeType::EM_DRAW && toolType == ToolType::TI_HAND)
        {
            this->moveMapOffset(ev.m_x, ev.m_y);
        }else{
            //Ctrl�����Ȃ�
            if(editModeType == EditModeType::EM_DRAW){
                //�h���[���[�h
                if(toolType == ToolType::TI_ARROW){
                    //���c�[����D&D

                }
            }
        }


#endif
        Refresh();
    }

    //�X�V
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
