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
    build_trig_tables();
    //allocate
    if(dynamic_world == NULL){
        allocate_map_memory();
    }
    //�Y�[���E�I�t�Z�b�g��������
    wxCommandEvent dummy;
    this->OnZoomDefault(dummy);
    this->OnMoveToCenter(dummy);


    wxGetApp().getStockManager()->resetDeletes();
    wxGetApp().isChanged = false;
    //���x���ꗗ�폜
    wxGetApp().levelNameList.clear();
    initialize_map_for_new_level();
    //�f�[�^�̏�����
    wxGetApp().getStockManager()->resetDeletes();
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MAX);
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MIN);

	//�v���p�e�B�R���{�{�b�N�X��ݒ�
	this->polyPropDialog.updateCombo();
}

/**
    �_�C�A���O���o���ĕҏW���̃}�b�v��j�󂵂Ă悢���𕷂��o���܂��B
    @param ���[�U����OK���o��ΐ^�B�o�Ȃ���΋U�B
        �܂��A�ҏW����ĂȂ���ΐ^���Ԃ�
*/
bool MapEditorMainFrame::askDestructMap()
{
    if(wxGetApp().isChanged){
        wxMessageDialog dlg(this, _T("Map has been modified. Are you sure that delete this and create new one?"));
        if(dlg.ShowModal() == wxID_OK){
            return true;
        }else{
            //����
            return false;
        }
    }
    return true;
}

void MapEditorMainFrame::OnNew(wxCommandEvent& ev)
{
    if(!this->askDestructMap()){
        return ;
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

    Refresh();
}

static void loadLevel(int i){
    bool check = load_level_from_map(wxGetApp().editLevelIndex);
    if(!check){
        wxMessageBox(_T("failed"));
    }
    //�Z�b�g�A�b�v
    wxGetApp().getStockManager()->updateDeletes();

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
}
void MapEditorMainFrame::OnOpen(wxCommandEvent& WXUNUSED(ev))
{
    //���Z�[�u�`�F�b�N
    if(!this->askDestructMap()){
        return ;
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

		//�v���p�e�B�R���{�{�b�N�X��ݒ�
		this->polyPropDialog.updateCombo();

        //�ĕ`��
        Refresh();
    }
}void MapEditorMainFrame::OnSave(wxCommandEvent& ev)
{
    //TODO save correctly
    if(wxGetApp().isChanged || wxGetApp().levelNameList.size() > 1){
        OnSaveAs(ev);
    }else{
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
    //bool result = 
}
void MapEditorMainFrame::OnRedo(wxCommandEvent& ev)
{
    //TODO REDO
}
void MapEditorMainFrame::OnCut(wxCommandEvent& ev)
{
    //TODO
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
	int div = wxGetApp().getViewGridManager()->getZoomDivision();
	if(!wxGetApp().getCopyPasteManager()->paste(div)){
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
    this->pointPropDialog.Show(false);
    this->polyPropDialog.Show(false);
    this->linePropDialog.Show(false);
    this->sidePropDialog.Show(false);
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
    if(!this->askDestructMap()){
        return ;
    }
    SelectLevelDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        int sel = dlg.getSelectLevel();
        wxGetApp().editLevelIndex = sel;
        //�X�e�[�W�ǂݍ���
//        initLevel();
        loadLevel(sel);
        Refresh();
    }
}
void MapEditorMainFrame::OnLevelInfo(wxCommandEvent& ev)
{
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //�ݒ蔽�f
    }
}
void MapEditorMainFrame::OnObjectPlacement(wxCommandEvent& ev)
{
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
    this->linePropDialog.setLineIndex(wxGetApp().popupLineIndex);
    this->linePropDialog.Show(true);
}
void MapEditorMainFrame::OnClockwiseSide(wxCommandEvent& ev)
{
    //TODO
    this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->clockwise_polygon_side_index);
    this->sidePropDialog.Show(true);
}
void MapEditorMainFrame::OnCounterclockwiseSide(wxCommandEvent& ev)
{
    //TODO
    this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->counterclockwise_polygon_side_index);
    this->sidePropDialog.Show(true);
}
void MapEditorMainFrame::OnPointProp(wxCommandEvent& ev)
{
    this->pointPropDialog.setIndex(wxGetApp().popupEndpointIndex);
    this->pointPropDialog.Show(true);
}
void MapEditorMainFrame::OnPolygonProp(wxCommandEvent& ev)
{
    this->polyPropDialog.setPolyIndex(wxGetApp().popupPolygonIndex);
    this->polyPropDialog.Show(true);
}
void MapEditorMainFrame::OnSetVisualModePlayerPosition(wxCommandEvent& ev)
{
	//wxASSERT(wxGetApp().popupPolygonIndex != NONE);
	//�|���S���̏��̍������擾
	polygon_data* poly = get_polygon_data(wxGetApp().popupPolygonIndex);
#ifdef __WXDEBUG__
	hpl::error::halt("polygon index was invalid", wxGetApp().popupPolygonIndex);
#endif
	int height = poly->floor_height;
	int mpoint[2];
	wxGetApp().getViewGridManager()->getNewMousePoint(mpoint);
	//���[���h���W�ɕϊ�
	world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mpoint[0], mpoint[1]);
	wxGetApp().getVisualModeManager()->setPlayerPosition(wpoint.x, wpoint.y, height);
}
