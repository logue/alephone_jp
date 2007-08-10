#include "MapEditorMainFrame.h"

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// file menus

void MapEditorMainFrame::OnPrint(wxCommandEvent& ev)
{
    //�}�b�v�̑S�̑������T�C�Y�ɍ��킹�Ĉ��
}
void MapEditorMainFrame::OnPrintPreview(wxCommandEvent& ev)
{
    //TODO
}
void MapEditorMainFrame::OnPrintSetup(wxCommandEvent& ev)
{
    //TODO
}

void MapEditorMainFrame::initLevel()
{
    //������
    wxGetApp().editLevelIndex = 0;
    //allocate
    if(dynamic_world == NULL){
		build_trig_tables();
        allocate_map_memory();
    }
    //�Y�[���E�I�t�Z�b�g��������
    wxCommandEvent dummy;
    this->OnZoomDefault(dummy);
    this->OnMoveToCenter(dummy);

	
    wxGetApp().getStockManager()->resetDeletes();
	wxGetApp().selectData.clear();

    wxGetApp().isChanged = false;
	
    //���x���ꗗ�폜
    wxGetApp().levelNameList.clear();
    initialize_map_for_new_level();
    //�f�[�^�̏�����
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MAX);
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MIN);

	///dynamic_world->map_index_count = 1;
}

/**
    �_�C�A���O���o���ĕҏW���̃}�b�v��j�󂵂Ă悢���𕷂��o���܂��B
    @param ���[�U����OK���o��ΐ^�B�o�Ȃ���΋U�B
        �܂��A�ҏW����ĂȂ���ΐ^���Ԃ�
*/
int MapEditorMainFrame::askDestructMap()
{
    if(wxGetApp().isChanged){
        wxMessageDialog dlg(this,
			_T("Map has been modified. Are you sure that delete this and create new one?"),
			_T("are you sure? :o"), wxYES_NO | wxCANCEL);
        return dlg.ShowModal();
    }
    return wxID_NO;
}

void MapEditorMainFrame::OnNew(wxCommandEvent& ev)
{
#ifdef MAP_VIEWER
#else
	int result = this->askDestructMap();
	if(result == wxID_YES){
		//�ۑ����܂�
		wxCommandEvent dummy;
		OnSaveAs(dummy);
	}else if(result = wxID_NO){
	}else{
		//cancel
		return;
	}
    initLevel();


    //���łɃ��x���ݒ�
    //TODO
    //���x���ݒ�_�C�A���O�\��
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
    //���e���}�b�v�f�[�^�ɔ��f
    //TODO

#endif
    Refresh();
}

void MapEditorMainFrame::loadLevel(int i){

    bool check = load_level_from_map(wxGetApp().editLevelIndex);
    if(!check){
        wxMessageBox(_T("failed"));
    }
    //�Z�b�g�A�b�v
    wxGetApp().getStockManager()->resetDeletes();

	//����������
	wxGetApp().getDoneHistoryManager()->init();

	//�v���C���[�|�W�V������ݒ�
	//�v���C���[��{��
	for(int i = 0 ; i < (int)SavedObjectList.size(); i ++){
		map_object* obj = &SavedObjectList[i];
		if(obj->type == _saved_player){
			//�ʒu�擾
			wxGetApp().getVisualModeManager()->setPlayerPosition(obj->location);
			break;
		}
	}

	//�I����ԕ\��������
	this->updateMapItems();
}
void MapEditorMainFrame::OnOpen(wxCommandEvent& ev)
{
	int result = this->askDestructMap();
	if(result == wxID_YES){
		//�ۑ����܂�
		wxCommandEvent dummy;
		OnSaveAs(dummy);
	}else if(result = wxID_NO){
	}else{
		//cancel
		return;
	}

    wxFileDialog fileDialog(this, _T("Choose a file"),
        _T("."), _T(""), _T("*.*"));

    if(fileDialog.ShowModal() == wxID_OK){
        wxString path = fileDialog.GetPath();

        //�^�C�g��
        SetTitle(path);
        
        FileSpecifier mapFile = FileSpecifier(path.mb_str());

        //set map file
        set_map_file(mapFile);

        wxGetApp().filePath = path;
        //������
        initLevel();

        //Level1��ǂݍ���
        loadLevel(0);

        //�C���f�b�N�X
        wxGetApp().levelNameList.clear();
        {
            short index = 0;
            struct entry_point ep;
			//�S�Ẵ}�b�v��ǂݍ���
            int type = 0xff;
            char cstr[256];
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d", ep.level_number);
                wxGetApp().levelNameList.push_back(string(cstr) + string(ep.level_name));
            }
            if(wxGetApp().levelNameList.size() == 0){
                wxGetApp().levelNameList.push_back("unnamed");
            }
        }

        //�ĕ`��
        Refresh();

		wxGetApp().isChanged = false;

    }
}void MapEditorMainFrame::OnSave(wxCommandEvent& ev)
{
    //TODO save correctly
	if(PhysicsModelLoaded || wxGetApp().levelNameList.size() > 1){
		hpl::error::caution("This map seems to be merged. This editor cannot save as merged one. Please save as another file");
        OnSaveAs(ev);
    }else{
		hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
		hpl::aleph::map::deleteMapItems(
			*smgr->getDelPoints(),
			*smgr->getDelLines(),
			*smgr->getDelPolygons(),
			*smgr->getDelSides(),
			*smgr->getDelObjects());
        //���݂̃t�@�C�����ŕۑ�
        if(save_level(wxGetApp().filePath.mb_str())){
            wxGetApp().isChanged = false;
//            wxGetApp().filePath = fname;
        }else{
            hpl::error::caution("save failure");
        }
    }
}
void MapEditorMainFrame::OnSaveAs(wxCommandEvent& ev)
{
    int style = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
    wxString wildcard(_T("AlephOne map (*.sceA)|*.sceA|Any file|*.*"));
    wxFileDialog dlg(this, wxString(_T("Save at...")), 
        wxString(_T("")), wxString(_T("")), wildcard,
        style);
    if(dlg.ShowModal() == wxID_OK){
		hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
		
		hpl::aleph::map::deleteMapItems(
			*smgr->getDelPoints(),
			*smgr->getDelLines(),
			*smgr->getDelPolygons(),
			*smgr->getDelSides(),
			*smgr->getDelObjects());
		
		//dynamic_world->map_index_count = 1;

		//�C���f�b�N�X�����������ǂ�������
		for(int i = 0; i < (int)EndpointList.size(); i ++){
			endpoint_data* ep = get_endpoint_data(i);
			wxASSERT(ep->supporting_polygon_index >= 0);
		}
		for(int i = 0; i < (int)LineList.size(); i ++){
			line_data* line = get_line_data(i);
			wxASSERT(line->clockwise_polygon_owner >= NONE);
			wxASSERT(line->clockwise_polygon_side_index >= NONE);
			wxASSERT(line->counterclockwise_polygon_owner >= NONE);
			wxASSERT(line->counterclockwise_polygon_side_index >= NONE);
			for(int j = 0; j < 2; j ++){
				wxASSERT(line->endpoint_indexes[j] >= 0);
			}
		}
		for(int i = 0; i < (int)PolygonList.size(); i ++){
			polygon_data* poly = get_polygon_data(i);
			wxASSERT(poly->first_object >= NONE);
			for(int j = 0; j < poly->vertex_count; j ++){
				wxASSERT(poly->adjacent_polygon_indexes[j] >= NONE);
				wxASSERT(poly->endpoint_indexes[j] >= 0);
				wxASSERT(poly->line_indexes[j] >= 0);
				wxASSERT(poly->side_indexes[j] >= NONE);
			}
		}
		for(int i = 0; i < (int)SideList.size(); i ++){
			side_data* side = get_side_data(i);
			wxASSERT(side->line_index >= 0);
			wxASSERT(side->polygon_index >= 0);
		}

		for(int i = 0; i < (int)PlatformList.size(); i ++){
			platform_data* platform = &PlatformList[i];
			wxASSERT(platform->polygon_index >= 0);
		}
        //
        wxString fname = dlg.GetPath();
        SetTitle(fname);

        if(save_level(fname.mb_str())){
            wxGetApp().isChanged = false;
            wxGetApp().filePath = fname;
        }else{
            hpl::error::caution("save failure");
        }
    }
}

void MapEditorMainFrame::OnMerge(wxCommandEvent& ev)
{
    //�f�B���N�g�����w�肵�A�t�H�[�}�b�g�ɏ]���ă��x�����}�[�W����
    //TODO
}
void MapEditorMainFrame::OnSavePhysicsFile(wxCommandEvent& ev)
{
	//TODO ���o���Ă���PhysicsFiles��ۑ�
	if(!PhysicsModelLoaded){
		//�ǂݍ��܂�Ă��Ȃ�
		hpl::error::caution("No physics data included in this map");
	}else{
		//�ǂݍ��܂�Ă���
		std::string str("P0%1d_%s.phyA");
		int levelIndex = wxGetApp().editLevelIndex;
		if(levelIndex >= 10){
			str = std::string("P%2d_%s.phyA");
		}
		wxString fname = getString(str.c_str(),
			levelIndex, wxGetApp().levelNameList[levelIndex].c_str());

		//�t�@�C���o�͐�_�C�A���O
		wxString wildcard(_T("AlephOne physics file data(*.phyA)|*.phyA|Any file|*.*"));
	    int style = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
		wxFileDialog dlg(this, wxString(_T("Save at...")), 
			wxString(_T("")), fname, wildcard,
			style);
		if(dlg.ShowModal() == wxID_OK){
			//
			fname = dlg.GetPath();
		
			export_definition_structures(fname.mb_str());
		}
			
	}
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// edit menus
void MapEditorMainFrame::OnUndo(wxCommandEvent& ev)
{
    //TODO
    /*
        �������ׂ���
        �E�}�b�v�A�C�e���̒ǉ�
        �E              �̍폜
        �E              �̐ݒ�ύX(�ړ��܂�)
        ���炢���ȁH�i����ȊO�̏����ɂ��Ă͖����B�v�]������Ή����銴���j
    */
	hpl::aleph::map::HPLSelectData dummy1;
	hpl::aleph::map::HPLRealMapData dummy2;
	hpl::aleph::map::HPLActionItem act = hpl::aleph::map::HPLActionItem(0, dummy1, dummy2);
	hpl::aleph::map::HPLDoneHistory* dmgr = wxGetApp().getDoneHistoryManager();
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

	if(dmgr->getIndex() > 0){
		bool result = dmgr->back(&act);
		if(!result){
			dmgr->forward(&act);
		}else if(act.type == hpl::aleph::map::ActionType::Move){
			//������x�擾�����݂�
			result = dmgr->back(&act);
		}
		if(result){
			if(act.type == hpl::aleph::map::ActionType::None ||
				act.type == hpl::aleph::map::ActionType::Move)
			{
				//�ړ������ɖ߂�
				for(int i = 0; i < (int)act.selectData.getSelPoints()->size(); i ++){
					int index = act.selectData.getSelPoints()->at(i).index;
					endpoint_data* ep = get_endpoint_data(index);
					//TODO �폜�E�ǉ���Undo�@�\���������悤�B
					//���ꂾ�����ƍ폜����Ă���ꍇ�G���[�ɂȂ�
					if(smgr->isDeletePoint(index) || ep == NULL){
						//TODO ���}���u�I
						continue;
					}
					ep->vertex = act.pointVertexMap[index];
				}
				for(int i = 0; i < (int)act.selectData.getSelObjects()->size(); i ++){
					int index = act.selectData.getSelObjects()->at(i).index;
					if(smgr->isDeleteObject(index) || index >= (int)SavedObjectList.size()){
						continue;
					}
					map_object* obj = &SavedObjectList[index];
					obj->location = act.objectLocationMap[index];
				}
				//lines
				for(int i = 0; i < (int)act.selectData.getSelLines()->size(); i ++){
					int index = act.selectData.getSelLines()->at(i).index;
					line_data* line = get_line_data(index);
					for(int j = 0; j < 2; j ++){
						int epIndex = line->endpoint_indexes[j];
						get_endpoint_data(epIndex)->vertex = act.pointVertexMap[epIndex];
					}
				}

				//polygons
				for(int i = 0; i < (int)act.selectData.getSelPolygons()->size(); i ++){
					int index = act.selectData.getSelPolygons()->at(i).index;
					polygon_data* poly = get_polygon_data(index);
					for(int j = 0; j < poly->vertex_count; j ++){
						int epIndex = poly->endpoint_indexes[j];
						get_endpoint_data(epIndex)->vertex = act.pointVertexMap[epIndex];
					}
				}

			}else{
				hpl::error::halt("This function is disable");
			}

		}else{
	#ifdef __WXDEBUG__
			hpl::error::caution("Undo���s�Bindex=%d", dmgr->getIndex());
	#endif
		}

		//�X�V
		this->updateMapItems();
	}
}
void MapEditorMainFrame::OnRedo(wxCommandEvent& ev)
{
    //TODO REDO
}
void MapEditorMainFrame::OnCut(wxCommandEvent& ev)
{
    //TODO �R�s�[���č폜
	OnCopy(ev);
	OnDelete(ev);
}
void MapEditorMainFrame::OnDelete(wxCommandEvent& ev)
{
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

	if(sel->isSelected()){
		//TODO �I��Ώۂ��L�^����Undo�ɗp����
		//

#ifdef MAP_VIEWER
		//objects
		for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
			smgr->deleteObject(sel->getSelObjects()->at(i).index);
		}
#else
		//objects
		for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
			smgr->deleteObject(sel->getSelObjects()->at(i).index);
		}
		//�I��Ώۂ��폜�ΏۂƂ���
		for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
			hpl::aleph::map::SelPoint* opt = &sel->getSelPoints()->at(i);
			smgr->deletePoint(opt->index);
		}
		//lines
		for(int i = 0; i < (int)sel->getSelLines()->size(); i ++){
			smgr->deleteLine(sel->getSelLines()->at(i).index);
		}
		/*
		//sides
		for(int i = 0; i < sel->getSelSides()->size(); i ++){
			smgr->deleteSide(sel->getSelSides()->at(i).index);
		}*/
		//polygons
		for(int i = 0; i < (int)sel->getSelPolygons()->size(); i ++){
			smgr->deletePolygon(sel->getSelPolygons()->at(i).index);
		}
#endif
		sel->clear();
		//�폜�����s���ꂽ�̂ŃR���{�X�V
		this->updateMapItems();
	}
}

void MapEditorMainFrame::OnCopy(wxCommandEvent& ev)
{
    //TODO �f�o�b�O
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	if(sel->isSelected()){
		//�I�𒆂̕�������
		//���L������
		wxGetApp().getCopyPasteManager()->copy(*sel);
	}
}
void MapEditorMainFrame::OnPaste(wxCommandEvent& ev)
{
    //TODO �f�o�b�O
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	int div = wxGetApp().getViewGridManager()->getZoomDivision();
	if(wxGetApp().getCopyPasteManager()->paste(div, sel)){
		//����
		//�ǉ����ꂽ�̂ŃR���{���X�V
		this->updateMapItems();
	}else{
		//���s
	}
}
void MapEditorMainFrame::OnPreference(wxCommandEvent& ev)
{
    //Call up editor preferences dialog
    EditorPreferencesDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //�t�@�C���ɕۑ� <en> save preference setting to file
        if(!wxGetApp().setting.saveSetting()){
            hpl::error::caution("Fail to save setting as [%s]", wxGetApp().setting.getFilePath().c_str());
        }
        //�y���̍�蒼�� <en> recreate pens and brushes
        setupPenAndBrush(wxGetApp().setting.getColorSetting());
        Refresh();
    }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// show/hide menus
void MapEditorMainFrame::OnToolDialog(wxCommandEvent& ev)
{
    this->toolDialog.Show(!this->toolDialog.IsShown());
}
void MapEditorMainFrame::OnZoomIn(wxCommandEvent& ev)
{
    wxSize size = this->GetSize();
    wxGetApp().getViewGridManager()->zoomIn(size.GetWidth(), size.GetHeight());
}
void MapEditorMainFrame::OnZoomOut(wxCommandEvent& ev)
{
    wxSize size = this->GetSize();
    wxGetApp().getViewGridManager()->zoomOut(size.GetWidth(), size.GetHeight());
}
void MapEditorMainFrame::OnZoomDefault(wxCommandEvent& ev)
{
    wxGetApp().getViewGridManager()->zoomReset();
}
void MapEditorMainFrame::OnMoveToCenter(wxCommandEvent& ev)
{
    //���S�����[���h���W�̐^�񒆂ɗ���悤�ɂ���
    wxGetApp().getViewGridManager()->setOffset(0,0);
}
void MapEditorMainFrame::OnHeightDialog(wxCommandEvent& ev)
{
    bool shown = this->heightDialog.IsShown();
    this->heightDialog.Show(!shown);
    if(shown){
        //TODO ���j���[�Ƀ`�F�b�N������
        //this->GetMenuBar()->GetMenu(0)->Get
    }else{
    }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// mode menus
/*
    ���[�h���X�_�C�A���O�������ς��ɂȂ�̂ŁA���j���[�I�����ɐ؂�ւ���
    ���ꂼ��̃��[�h�ŊJ���Ă���\���̂��郂�[�h���X�_�C�A���O�͈ȉ��̂Ƃ���
    �EDraw(Polygon)Mode
        �_���_�C�A���O        PointProp
        �����_�C�A���O        LineProp
        �|���S�����_�C�A���O  PolygonProp
        Side���_�C�A���O      SideProp
        �I�u�W�F�N�g���_�C�A���O  ObjectProp
    �EPolygonType
        PolygonType
    �EFloor/Ceiling HeightMode
        HeightPalette (setFloor(bool))
    �EFloor/CeilingTexture
        Texture
    �EMedia
        MediaPalette
    �ELight
        LightPalette
*/

void MapEditorMainFrame::OnDrawPolygonMode(wxCommandEvent& ev)
{
    //���݂̏�Ԃ��擾
    bool checked = ev.IsChecked();
    
    //���[�h�ύX
	this->changeEditMode(EditModeType::EM_DRAW);

    //��U�S�ă`�F�b�N���͂����܂�
    this->uncheckModesOnMenu();

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();
}
void MapEditorMainFrame::closeAllModelessDialogs()
{
    this->objPropDialog.Show(false);
//    this->pointPropDialog.Show(false);
    //this->polyPropDialog.Show(false);
    //this->linePropDialog.Show(false);
//    this->sidePropDialog.Show(false);
    this->polyTypeDialog.Show(false);
    this->mediaPaletteDialog.Show(false);
    this->heightPaletteDialog.Show(false);
    this->lightPaletteDialog.Show(false);
    this->textureDialog.Show(false);
}

void MapEditorMainFrame::OnVisualMode(wxCommandEvent& ev)
{
    //���[�_���\��
    VisualDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
    }

}
void MapEditorMainFrame::OnPolygonTypeMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_POLYGON_TYPE);

    //�S���̃_�C�A���O����܂�
    //this->closeAllModelessDialogs();

    //�|���S���^�C�v�_�C�A���O�\��
	this->polyTypeDialog.setupDialog();
    this->polyTypeDialog.Show(true);
}
void MapEditorMainFrame::OnFloorHeightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_FLOOR_HEIGHT);

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();

    //���̍���
    this->heightPaletteDialog.setFloor(true);
    //�����p���b�g�_�C�A���O�\��
    this->heightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingHeightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_CEILING_HEIGHT);

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();

    //�V��̍���
    this->heightPaletteDialog.setFloor(false);
    //�����p���b�g�_�C�A���O�\��
    this->heightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnFloorLightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_FLOOR_LIGHT);

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();

    this->lightPaletteDialog.setFloor(true);
    //���C�g�p���b�g�_�C�A���O�\��
    this->lightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingLightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_CEILING_LIGHT);

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();

    this->lightPaletteDialog.setFloor(false);
    //���C�g�p���b�g�_�C�A���O�\��
    this->lightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnMediaMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_MEDIA);
 
    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();

    //���f�B�A�p���b�g�_�C�A���O�\��
	this->mediaPaletteDialog.setupDialog();
    this->mediaPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnFloorTextureMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_FLOOR_TEXTURE);

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();

    //�e�N�X�`���_�C�A���O�\��
    this->textureDialog.setFloor(true);
    this->textureDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingTextureMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_CEILING_TEXTURE);

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();

    this->textureDialog.setFloor(false);
    //�e�N�X�`���_�C�A���O�\��
    this->textureDialog.Show(true);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// special menus
void MapEditorMainFrame::OnJumpLevel(wxCommandEvent& ev)
{
    //TODO
    //�ۑ��m�F
    //���Z�[�u�`�F�b�N
	int result = this->askDestructMap();
	if(result == wxID_YES){
		//�ۑ����܂�
		wxCommandEvent dummy;
		OnSaveAs(dummy);
	}else if(result = wxID_NO){
	}else{
		//cancel
		return;
	}

	SelectLevelDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        int sel = dlg.getSelectLevel();
        wxGetApp().editLevelIndex = sel;
        //�X�e�[�W�ǂݍ���
//        initLevel();
        loadLevel(sel);
		this->updateMapItems();
        Refresh();
    }
}
void MapEditorMainFrame::OnLevelInfo(wxCommandEvent& ev)
{
	//�ҏW�ݒ�
	wxGetApp().isChanged = true;
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //�ݒ蔽�f
    }
}
void MapEditorMainFrame::OnObjectPlacement(wxCommandEvent& ev)
{
	//�ҏW�ݒ�
	wxGetApp().isChanged = true;
    //�I�u�W�F�N�g�z�u�_�C�A���O
    PlacementDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
}
void MapEditorMainFrame::OnTerminalViewer(wxCommandEvent& ev)
{
    //�^�[�~�i��
    TerminalDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

void MapEditorMainFrame::OnLineProp(wxCommandEvent& ev)
{
	//�ҏW�ݒ�
	wxGetApp().isChanged = true;
    //this->linePropDialog.setLineIndex(wxGetApp().popupLineIndex);
    //this->linePropDialog.Show(true);
	int lineIndex = wxGetApp().popupLineIndex;
	line_data* org = get_line_data(lineIndex);
	wxASSERT(org);
	LinePropDialog dlg;
	dlg.Create(this, wxID_ANY, lineIndex);
	if(dlg.ShowModal() == wxID_OK){
#ifdef MAPVIEWER
#else
		*org = dlg.getLine();
#endif
		//memcpy(org, &data, sizeof(line_data));
	}
}
void MapEditorMainFrame::OnClockwiseSide(wxCommandEvent& ev)
{
	//�ҏW�ݒ�
	wxGetApp().isChanged = true;
    //this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->clockwise_polygon_side_index);
    //this->sidePropDialog.Show(true);
	int index = get_line_data(wxGetApp().popupLineIndex)->clockwise_polygon_side_index;
	this->openSidePropDialog(index);
}
void MapEditorMainFrame::openSidePropDialog(int sideIndex)
{
	if(hpl::aleph::map::isValidIndex(sideIndex, SideList.size())){
		SidePropDialog dlg;
		dlg.Create(this, wxID_ANY, sideIndex);
		if(dlg.ShowModal() == wxID_OK){
#ifdef MAPVIEWER
#else
			side_data data = dlg.getSide();
			side_data* org = get_side_data(sideIndex);
			*org = data;
#endif
		}
	}else{
		hpl::error::caution("invalid side index[%d]", sideIndex);
	}
}

void MapEditorMainFrame::OnCounterclockwiseSide(wxCommandEvent& ev)
{
	//�ҏW�ݒ�
	wxGetApp().isChanged = true;
    //TODO
//    this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->counterclockwise_polygon_side_index);
//    this->sidePropDialog.Show(true);
	int index = get_line_data(wxGetApp().popupLineIndex)->counterclockwise_polygon_side_index;
	this->openSidePropDialog(index);
}
void MapEditorMainFrame::OnPointProp(wxCommandEvent& ev)
{
	//�ҏW�ݒ�
	wxGetApp().isChanged = true;
	PointPropDialog dlg;
	int endpointIndex = wxGetApp().popupEndpointIndex;
	dlg.Create(this, wxID_ANY, endpointIndex);
	if(dlg.ShowModal() == wxID_OK){
#ifdef MAPVIEWER
#else
		endpoint_data data = dlg.getEndpoint();
		endpoint_data* org = get_endpoint_data(endpointIndex);
		obj_copy(*org, data);
#endif
	}
}

/**
	�|���S���v���p�e�B���j���[
*/
void MapEditorMainFrame::OnPolygonProp(wxCommandEvent& ev)
{
	//�ҏW�ݒ�
	wxGetApp().isChanged = true;
	int polyIndex = wxGetApp().popupPolygonIndex;
	polygon_data* org = get_polygon_data(polyIndex);
	wxASSERT(org);
	PolygonPropDialog dlg;
	dlg.Create(this, wxID_ANY, polyIndex);
	if(dlg.ShowModal() == wxID_OK){
		polygon_data data = dlg.getPolygon();
		//�R�s�[
		//memcpy(org, &data, sizeof(polygon_data));
#ifdef MAPVIEWER
#else
		*org = data;
#endif
	}
}
void MapEditorMainFrame::OnSetVisualModePlayerPosition(wxCommandEvent& ev)
{
	if(!hpl::aleph::map::isValidIndex(wxGetApp().popupPolygonIndex, PolygonList.size())){
		return;
	}
	//�|���S���̏��̍������擾
	polygon_data* poly = get_polygon_data(wxGetApp().popupPolygonIndex);

	int height = poly->floor_height;
	int mpoint[2];
	wxGetApp().getViewGridManager()->getNewMousePoint(mpoint);
	//���[���h���W�ɕϊ�
	world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mpoint[0], mpoint[1]);
	wxGetApp().getVisualModeManager()->setPlayerPosition(wpoint.x, wpoint.y, height);
}

