#include "MapEditorMainFrame.h"
#include "AnnotationDialog.h"


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

	//�X�g�b�N�}�l�[�W���[
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    //�|�b�v�A�b�v���j���[���o��
    //TODO
    //�}�E�X���W�����[���h���W�ɂ���
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
			//���{�^�������Ȃ���E������
			if(sel->isSelected()){
				//�I�����Ă���
				if(emgr->isGrabItems()){
					//����ł���

					//����ł����̂��͂Ȃ�
					emgr->setGrabItems(false);

					//���W�����̈ʒu�ɖ߂�
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
			//�_�̏�ŉE�N���b�N�������H
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
				//�I��ύX
				selectOneThingBefore();
				int offset[2] = {0};
				sel->addSelPoint(epIndex, offset);
				selectOneThingAfter(mx, my);
				//�I�����̍X�V
				smgr->updateSelects(wxGetApp().selectData);
				Refresh();
				//�_�|�b�v�A�b�v�\��
				PopupMenu(&wxGetApp().pointPopupMenu);
			}else if(lineIndex != NONE){
				//���������ꂽ
				//�I��ύX
				selectOneThingBefore();
				int offset[2][2] = {{0}};
				sel->addSelLine(lineIndex, offset);
				selectOneThingAfter(mx, my);
				//�I�����̍X�V
				smgr->updateSelects(wxGetApp().selectData);
				Refresh();
				//�����v���p�e�B������
				PopupMenu(&wxGetApp().linePopupMenu);
			}else if(polygonIndex != NONE){
				//������
				//�I��ύX
				selectOneThingBefore();
				polygon_data* poly = get_polygon_data(polygonIndex);
				int offset[MAXIMUM_VERTICES_PER_POLYGON][2] = {{0}};
				int num = poly->vertex_count;
				sel->addSelPolygon(polygonIndex, offset, num);
				selectOneThingAfter(mx, my);
				//�I�����̍X�V
				smgr->updateSelects(wxGetApp().selectData);
				Refresh();
				PopupMenu(&wxGetApp().polygonPopupMenu);
			}
		}
    }
	//���ݒ�������
	emgr->setGrabItems(false);
}
///////////////////////////////////////////////////////
void MapEditorMainFrame::OnRightUp(wxMouseEvent& ev)
{
    //�J�[�\���ݒ�
    wxGetApp().setCursor();
    int mx = ev.m_x;
    int my = ev.m_y;

    //�}�E�X���W�L�^
    wxGetApp().getViewGridManager()->setNewMousePoint(mx, my);


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
    emgr->exitSelectingGroup();

    //�|���S����Ԃ��X�V���܂�
    wxGetApp().getStockManager()->updatePolygonValidityStored();
	//�I�����̍X�V
	wxGetApp().getStockManager()->updateSelects(wxGetApp().selectData);

    Refresh();
}

void MapEditorMainFrame::doLUpOnArrowTool(wxMouseEvent& ev)
{
    //�I���f�[�^
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;

    //�O���b�h�}�l�[�W���[
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
	hpl::aleph::map::HPLDoneHistory* dmgr = wxGetApp().getDoneHistoryManager();

	//��������ł�����s�������Ɏc��
	if(sel->isSelected() && emgr->isGrabItems()){
		dmgr->push_back(
			hpl::aleph::map::ActionType::Move, *sel);
#ifdef __WXDEBUG__
//		hpl::error::caution("undo index=%d", dmgr->getIndex());
#endif
	}
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

	//�ŏ��ɑI�����ڂɒǉ����ꂽ��
	bool isFirst = true;

	//���ݒ�������
	emgr->setGrabItems(false);

    if(emgr->isSelectingGroup()){

        //�͈͑I�𒆂������B��`���̃A�C�e����I���Ƃ���
        //�I���J�n�ʒu
        int selStartPoint[2];
        emgr->getSelectGroupStartPoint(selStartPoint);
        
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
                //�o�^
				int offset[MAXIMUM_VERTICES_PER_POLYGON][2] = {{0}};
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
				if(isFirst){
					isFirst = false;
					sel->clear();
				}
                //�ǉ�
                int offset[2] = {0,0};
                sel->addSelObject(i, offset);
            }
        }

    }
	//�ǂ���I�����Ă��Ȃ����`�F�b�N
	if(isFirst && !sel->isSelected()){
		//�I�����Ă��Ȃ�

		//�O��̈ʒu
		int oldVPoint[2];
		wxGetApp().getViewGridManager()->getOldMousePoint(oldVPoint);
		
		//���݂̈ʒu�Ƃ̋������v�Z
		double distance = hpl::math::getLength(mx - oldVPoint[0], my - oldVPoint[1]);
		if(distance > SAME_POSITION_CLICK_THRESHOLD){
			//�قڌ��݂̈ʒu�ŃN���b�N����
			//	�Ȃ�ΑI������
			sel->clear();
		}
	}

	/*
	if(sel->isSelected()){
		//�R�s�y���o�^
		wxGetApp().getDoneHistoryManager()->push_back(hpl::aleph::map::ActionType::Move, *sel);
	}
	*/
	//������
	emgr->setGrabItems(false);
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
        //���X�V
        wxGetApp().getStockManager()->updateDeletes();
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

	hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

    int mx = ev.m_x;
    int my = ev.m_y;

    if(sel->isSelected() && emgr->isGrabItems()){
        //�I��
        //�I�𕨂̈ړ�
        
		//�}�E�X��臒l�ȏ㓮���Ă�����A�C�e���𓮂���
		//�}�E�X���Ō�ɑI���������W
		int lastMousePosition[2];
		sel->getMousePosition(lastMousePosition);
		if(hpl::math::getLength(mx - lastMousePosition[0], my - lastMousePosition[1])
			>SAME_POSITION_CLICK_THRESHOLD)
		{
			//���[���h���W�n�ɂ���
			world_point2d wmp = wxGetApp().getWorldPointFromViewPoint(mx, my);

			//�_
			for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
				struct hpl::aleph::map::SelPoint* selp = &sel->getSelPoints()->at(i);
				int index = selp->index;
				//�ʒu�ύX
				get_endpoint_data(index)->vertex.x = wmp.x + selp->offset[0] * div;
				get_endpoint_data(index)->vertex.y = wmp.y + selp->offset[1] * div;

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

			//�A�m�e�[�V����
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
/////////////////////////////////////////////////
/////////////////////////////////////////////////
//  ���_�u���N���b�N <en> Mouse Left Button Double Click
void MapEditorMainFrame::OnLeftDoubleClick(wxMouseEvent& ev)
{
    //�J�[�\���ݒ�
    wxGetApp().setCursor();

    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    int editMode = emgr->getEditModeType();
    int toolType = emgr->getToolType();
    if(editMode == EditModeType::EM_DRAW &&
        toolType == ToolType::TI_LINE)
    {
        //�����[�h�Ń_�u���N���b�N

        //���̒ǉ�
        this->doLButtonOnLineTool(ev);

        //���ҏW���̏�����
        wxGetApp().resetLineEditInfo();
    }

    Refresh();
}

//�L�[�_�E��
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
	�}�b�v�f�[�^�ɕҏW���������ꍇ�ɍs���鏈�����L�q���܂�
	�E�_/��/Side/�I�u�W�F�N�g/�|���S���̃v���p�e�B�_�C�A���O�č\�z�i�ǉ��݂̂�OK�j
	�E�I�����̍X�V
	�E�폜���̍X�V
*/
void MapEditorMainFrame::updateMapItems()
{
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
	smgr->updateSelects(wxGetApp().selectData);
	smgr->updateDeletes();
	smgr->updatePolygonValidityStored();

	//���[�h���X�_�C�A���O����
	//�|���S���v���p�e�B
	//this->polyPropDialog.updateCombo();

	//�|���S���E����Fix���s��
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

	//�ҏW��m�点��
	wxGetApp().isChanged = true;
	Refresh();

}

