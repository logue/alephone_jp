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

	//�A���h�D���ɒǉ����Ă����܂�
//	hpl::aleph::map::HPLDoneHistory* hmgr = wxGetApp().getDoneHistoryManager();
	sel->setMousePosition(mx, my);
	hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();

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
            hpl::aleph::map::setupSelectDataGroupOffsets(mx, my,
                &wxGetApp().selectData, voffset[0], voffset[1],
                OFFSET_X_WORLD, OFFSET_Y_WORLD, div);
			emgr->setGrabItems(true);
        }else{
            //�N���b�N���Ă��Ȃ�
			
			//������I�����Ă��邩����
			if(this->tryToSelectOneItem(ev)){
				//�ЂƂI�����̌㏈��
				//�ΏۑI��(�ς�)
				//�I�t�Z�b�g�ݒ�
				//�s�������ɒǉ�
				this->selectOneThingAfter(mx, my);
			}else{
				//�I������
				//�͈͑I���J�n
				this->selectNothing(mx, my);
			}
        }
	}else{
		//�����I�����Ă��Ȃ�
		//���I���ł��邩�����Ă݂܂�
		if(this->tryToSelectOneItem(ev)){
			//�I�������i�ς݁j�E�Ώۂ�I���i�ς݁j
			//�I�t�Z�b�g�ݒ�
			//�s�������ɒǉ�
			this->selectOneThingAfter(mx, my);
		}else{
			//�I������Ȃ�����
			//�I������
			//�͈͑I���J�n
			this->selectNothing(mx, my);
		}

	}

	//�I�����̍X�V
	wxGetApp().getStockManager()->updateSelects(wxGetApp().selectData);
}
/**
	�Ȃɂ��I���ł��Ȃ������ꍇ
*/
void MapEditorMainFrame::selectNothing(int mx, int my)
{
	//�͈͑I���̊J�n
	wxGetApp().getEventManager()->setSelectGroupStartPoint(mx, my);

	//�I�����ҏW���������A�C�e����������
	//TODO �x���Ȃ�\��������̂ŁA�C�����K�v����
	//(��Ƀ_�C�A���O�̃R���{�{�b�N�X���č\�z����̂Ɏ��Ԃ������)
	this->unselect();

	//�I������
	wxGetApp().selectData.clear();
}

/**
	the function called when select one thing
	@param mx, my �}�E�X���W mouse cursor position
*/
void MapEditorMainFrame::selectOneThingAfter(int mx, int my)
{
	//�I������Ă��Ȃ����ڂɊւ���_�C�A���O�̐ݒ���������܂�
	this->unselect();
	
	int voffset[2];
	hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
	vmgr->getOffset(voffset);
	int div = vmgr->getZoomDivision();

	//�I�t�Z�b�g�ݒ�
	hpl::aleph::map::setupSelectDataGroupOffsets(mx, my,
		&wxGetApp().selectData, voffset[0], voffset[1],
		OFFSET_X_WORLD, OFFSET_Y_WORLD, div);
	
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	sel->setMousePosition(mx, my);
	//��ނɉ����ă_�C�A���O��\������
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

	//�I���ł����̂�
	//�͈͑I���͉������܂�
	hpl::aleph::HPLEventManager *emgr = wxGetApp().getEventManager();
	emgr->exitSelectingGroup();
	emgr->setGrabItems(true);

	//�A���h�D�@�\���̂��߂ɋL�����Ă����܂�
	wxGetApp().getDoneHistoryManager()->push_back(
		hpl::aleph::map::ActionType::None, wxGetApp().selectData);

	//�Ō�ɑI�������ʒu�̃}�E�X�|�C���g���L�����܂�
	emgr->setLastMouseSelectPoint(mx, my);
}

void MapEditorMainFrame::unselect()
{
    hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
    //�_��I�����Ă��Ȃ��̂�index��NONE�ł͂Ȃ�
    if(!sel->isSelectOnePoint() && pointPropDialog.getIndex() != NONE){
        //���̏ꍇ�I����NONE�ɂ���
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


    //�I���̗D�揇�ʂ�
    //1:�I�u�W�F�N�g
    //2:�_
    //-:�A�m�e�[�V����
    //3:��
    //4:�|���S��


    //�I�u�W�F�N�g
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        if(wxGetApp().getStockManager()->isDeleteObject(i)){
            continue;
        }
        map_object* obj = &SavedObjectList[i];
        int x = obj->location.x;
        int y = obj->location.y;
        int z = obj->location.z;

        //�������͈͊O���ǂ���
        if(z > zMax || z < zMin){
            continue;
        }

        //�I�u�W�F�N�g�I������
        if(hpl::aleph::map::isSelectPoint(mx, my,
            x, y, voffset[0], voffset[1],
            OFFSET_X_WORLD, OFFSET_Y_WORLD, div, OBJECT_DISTANCE_EPSILON))
        {
		    if(!shift){
				//�V�t�g�L�[���������ɃN���b�N�������U�������
				selectOneThingBefore();
			}

            //�I��ǉ�
            int offset[2];

            sel->addSelObject(i, offset);
            return true;
        }
    }

    //////////
    //�_
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        if(wxGetApp().getStockManager()->isDeletePoint(i)){
            continue;
        }
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
		    if(!shift){
				//�V�t�g�L�[���������ɃN���b�N�������U�������
				selectOneThingBefore();
			}
            //��������
            int offset[2];
            sel->addSelPoint(i, offset);
            return true;
        }
    }

	//////////////////////////////////////
	//�A�m�e�[�V����
	int annotationIndex = hpl::aleph::map::getSelectAnnotationIndex(mx, my,
		POINT_DISTANCE_EPSILON, zMin, zMax,
		voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
		wxGetApp().getStockManager());
	if(annotationIndex != NONE){
	    if(!shift){
			//�V�t�g�L�[���������ɃN���b�N�������U�������
			selectOneThingBefore();
		}
		map_annotation* annotation = &MapAnnotationList[annotationIndex];
		//�I�t�Z�b�g�ݒ�
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
			//�V�t�g�L�[���������ɃN���b�N�������U�������
			selectOneThingBefore();
		}
		line_data* line = get_line_data(lineIndex);
		endpoint_data* start = get_endpoint_data(line->endpoint_indexes[0]);
		endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

        //�I��

        int offset[2][2];
        sel->addSelLine(lineIndex, offset);
        return true;
    }

    //�|���S��
    //TODO �������Ƀ\�[�g����(�܂�����ĂȂ�)
	int polyIndex = hpl::aleph::map::getSelectPolygonIndex(mx ,my,
		zMin, zMax,
		voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD, div, 
		wxGetApp().getStockManager());
	if(polyIndex != NONE){
	    if(!shift){
			//�V�t�g�L�[���������ɃN���b�N�������U�������
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

	//�I���ł��Ȃ�����

    return false;
}
//�I���ɐ��������ꍇ�̑O����
void MapEditorMainFrame::selectOneThingBefore()
{
	//�I������
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
    //�h��Ԃ��\�ȃ|���S���f�[�^���擾���܂�
    std::vector<polygon_data> polyDatas = hpl::aleph::map::searchValidPolygon(
        wmp, smgr, zMin, zMax);
    if(polyDatas.size() == 0){
        //���s
        hpl::error::caution("No frame to fill as a VALID polygon found (it seems to be a illegal polygon or a none)");
    }else{
        //�ǉ�
        hpl::aleph::map::addPolygon(polyDatas[0]);
        //�X�V
        smgr->updateDeletes();
    }
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

    hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    //�d�Ȃ�_�����邩�ǂ����`�F�b�N
    int pointIndex = hpl::aleph::map::getSelectPointIndex(
        wpoint, POINT_DISTANCE_EPSILON, zMin, zMax, div, smgr);
    //�d�Ȃ�������邩���肷��
    int lineIndex = hpl::aleph::map::getSelectLineIndex(
        wpoint, LINE_DISTANCE_EPSILON, zMin, zMax, div, smgr);

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
        if(wxGetApp().isFirstOfLineToAdd){
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
                    //���ɐ������݂��Ă���
                    //�������Ȃ�
                }else{
                    //�łȂ��ΐ����쐬����
                    line_data line;
                    hpl::aleph::map::createLine(wxGetApp().prevPointIndex,
                        pointIndex, &line);
                    int newLineIndex = hpl::aleph::map::addLine(line);
                }
                wxGetApp().prevPointIndex = pointIndex;
            }
        }

        //�ŏ��̃N���b�N�ł͂Ȃ��Ȃ���
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
                hpl::aleph::map::createPoint(wpoint, &ep);
                int newPointIndex = hpl::aleph::map::addEndpoint(ep);
                assert(newPointIndex != NONE);
            }else{
                //�n�_�A�I�_�̏��擾
                //endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
                //endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
                int epStartIndex = line->endpoint_indexes[0];
                int epEndIndex = line->endpoint_indexes[1];

                //�����폜
                smgr->deleteLine(lineIndex);
                smgr->updateDeletes();

                //�_��ǉ�
                endpoint_data ep;
                hpl::aleph::map::createPoint(wpoint, &ep);
                int newPointIndex = hpl::aleph::map::addEndpoint(ep);
#ifdef __WXDEBUG__
                wxASSERT(newPointIndex != NONE);
#endif
                endpoint_data *newEp = get_endpoint_data(newPointIndex);

                //�n�_���_�̐���ǉ�
                line_data newLine1;
                hpl::aleph::map::createLine(epStartIndex,
                    newPointIndex, &newLine1);
                int newLine1Index = hpl::aleph::map::addLine(newLine1);
#ifdef __WXDEBUG__
                wxASSERT(newLine1Index != NONE);
#endif

                //�_���I�_�̐���ǉ�
                line_data newLine2;
                hpl::aleph::map::createLine(newPointIndex, epEndIndex,
                    &newLine2);
                int newLine2Index = hpl::aleph::map::addLine(newLine2);
#ifdef __WXDEBUG__
                wxASSERT(newLine2Index != NONE);
#endif


                if(wxGetApp().isFirstOfLineToAdd){
                    //�ŏ��Ȃ�Ȃɂ����Ȃ�
                }else{
                    //�O�񁨍���̓_�̊Ԃɐ���ǉ�
                    line_data newLine;
                    hpl::aleph::map::createLine(wxGetApp().prevPointIndex, newPointIndex, &newLine);
                    int lineIndex = hpl::aleph::map::addLine(newLine);
                }
                wxGetApp().prevPointIndex = newPointIndex;
            }
            wxGetApp().isFirstOfLineToAdd = false;

        }else{
            //�V�K�ǉ�
            endpoint_data ep;
            hpl::aleph::map::createPoint(wpoint, &ep);
            int newPointIndex = hpl::aleph::map::addEndpoint(ep);
            if(wxGetApp().isFirstOfLineToAdd){
                //�ŏ��̓_�Ȃ̂Œǉ����Ȃ�
            }else{
                //����ǉ�����
                line_data line;
                hpl::aleph::map::createLine(wxGetApp().prevPointIndex, newPointIndex, &line);
                int newLineIndex = hpl::aleph::map::addLine(line);
            }
            
            wxGetApp().isFirstOfLineToAdd = false;
            wxGetApp().prevPointIndex = newPointIndex;
        }
    }

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

    hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    bool found = false;
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        if(smgr->isDeletePolygon(i)){
            continue;
        }
        polygon_data* poly = get_polygon_data(i);
        if(hpl::aleph::map::isPointInPolygon(wpoint, i)){
            //�_���܂܂��
            //���̃|���S����ɒu��
            //TODO
            int flags = 0;

			//�_�C�A���O����I�u�W�F�N�g���쐬����
            map_object objv = this->objPropDialog.getObject();
            objv.polygon_index = i;
			//�|���S���ʒu���擾
			objv.location.x = wpoint.x;
			objv.location.y = wpoint.y;
			objv.location.z = poly->floor_height;
			if(objv.flags & _map_object_hanging_from_ceiling){
				//TODO �V�䂩��Ԃ牺�����Ă���ꍇ�A�V��ɍ��W�����킹��ׂ����H
			}

            int newIndex = hpl::aleph::map::addMapSavedObject(objv);
			//�I�u�W�F�N�g�_�C�A���O�{�b�N�X���X�V���܂�
			objPropDialog.setObjIndex(newIndex);
			//�I�������̃I�u�W�F�N�g�ɕύX���܂�
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
    //�O���b�h�}�l�[�W���[
    hpl::aleph::view::HPLViewGridManager* vmgr = wxGetApp().getViewGridManager();
    vmgr->getOffset(voffset);
    int div = wxGetApp().getViewGridManager()->getZoomDivision();
    int zMin = vmgr->getViewHeightMin();
    int zMax = vmgr->getViewHeightMax();
#ifdef MAP_VIEWER
#else
    //shift�������Ȃ��炾�ƕҏW���[�h�ɂȂ�
    if(ev.ShiftDown()){
        int annotationIndex = NONE;
        //�A�m�e�[�V������I���ł��邩�����Ă݂܂�
        for(int i = 0; i < (int)MapAnnotationList.size(); i ++){
            map_annotation* annotation = &MapAnnotationList[i];
            if(hpl::aleph::map::isSelectPoint(mx, my,
                annotation->location.x, annotation->location.y,
                voffset[0], voffset[1], OFFSET_X_WORLD, OFFSET_Y_WORLD,
                div, POINT_DISTANCE_EPSILON))
            {
                //�I���o����
                annotationIndex = i;
                break;
            }
        }
        if(annotationIndex != NONE){
            //�A�m�e�[�V������ҏW���܂�
            AnnotationDialog dlg;
            dlg.Create(this, wxID_ANY, MapAnnotationList[annotationIndex]);
            if(dlg.ShowModal() == wxID_OK){
                map_annotation newAn = dlg.getAnnotation();
                //�ύX
                MapAnnotationList[annotationIndex] = newAn;
            }
        }

        //������Ȃ�����
        hpl::error::caution("No annotation found there");
    }else{

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
        //�����X�V����
        wxGetApp().getStockManager()->updateDeletes();
    }
#endif
}
void MapEditorMainFrame::doLButtonOnPolygonTool(wxMouseEvent& ev)
{
#ifdef MAP_VIEWER
#else
    //�͈͑I���J�n
    wxGetApp().getEventManager()->setSelectGroupStartPoint(ev.m_x, ev.m_y);
#endif
}

void MapEditorMainFrame::doLButtonOnPolygonMode(wxMouseEvent& ev)
{
	//���c�[�����I���E�{��
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
			//�I����e�����X�g�R���g���[���ɔ��f
			this->polyTypeDialog.setType(poly->type);
		}
	}
#ifdef MAP_VIEWER
#else
	//�h��Ԃ��c�[�������ݑI�����Ă���^�C�v�œh��Ԃ�
	if(tool == ToolType::TI_FILL){
		if(poly){
			int polyType = this->polyTypeDialog.getType();
			if(polyType >= 0){
				//�^�C�v��ύX
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
