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
}
void MapEditorMainFrame::OnPrintSetup(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnNew(wxCommandEvent& ev)
{
    if(wxGetApp().isChanged){
        wxMessageDialog dlg(this, _T("Map has been modified. Are you sure that delete this and create new one?"));
        if(dlg.ShowModal() == wxID_CANCEL){
            //����
            return;
        }
    }
    initialize_map_for_new_level();
    //���x���ꗗ�폜
    wxGetApp().levelNameList.clear();

    wxGetApp().isChanged = false;

    //���łɃ��x���ݒ�
    //TODO
    //���x���ݒ�_�C�A���O�\��
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
    //���e���}�b�v�f�[�^�ɔ��f
    //TODO

    //�f�[�^�̏�����
    wxGetApp().getStockManager()->resetDeletes();
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MAX);
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MIN);
    Refresh();
}
void MapEditorMainFrame::OnNewLevel(wxCommandEvent& ev)
{
    //�V�K���x���쐬
    //TODO �s�v�H
    //�}�[�W����Ă���}�b�v�͕ۑ��ł��Ȃ�


}

void MapEditorMainFrame::OnOpen(wxCommandEvent& WXUNUSED(ev))
{
    //TODO ���Z�[�u�`�F�b�N

    //file dialog open
    wxFileDialog fileDialog(this, _T("Choose a file"),
        _T("."), _T(""), _T("*.*"));

    if(fileDialog.ShowModal() == wxID_OK){
        wxString path = fileDialog.GetPath();

        //�^�C�g��
        SetTitle(path);
        
        FileSpecifier mapFile = FileSpecifier(path.mb_str());

        //set map file
        set_map_file(mapFile);

        wxGetApp().editLevelIndex = 0;
        build_trig_tables();
        //allocate
        if(dynamic_world == NULL){
            allocate_map_memory();
        }
        //Level1��ǂݍ���
        bool check = load_level_from_map(wxGetApp().editLevelIndex);
        if(!check){
            wxMessageBox(_T("failed"));
        }

        //�C���f�b�N�X
        wxGetApp().levelNameList.clear();
        {
            short index = 0;
            struct entry_point ep;
            int type = 3;
            char cstr[256];
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d", ep.level_number);
                wxGetApp().levelNameList.push_back(string(cstr) + string(ep.level_name));
            }
            if(wxGetApp().levelNameList.size() == 0){
                wxGetApp().levelNameList.push_back("unnamed");
            }
        }
        //�Y�[���E�I�t�Z�b�g��������
        wxCommandEvent dummy;
        this->OnZoomDefault(dummy);
        this->OnMoveToCenter(dummy);

        wxGetApp().filePath = path;
        wxGetApp().isChanged = false;

        wxGetApp().getStockManager()->resetDeletes();
        //�ĕ`��
        Refresh();
    }
}void MapEditorMainFrame::OnSave(wxCommandEvent& ev)
{
    //TODO save correctly
    if(wxGetApp().isChanged){
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

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// edit menus
void MapEditorMainFrame::OnUndo(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnCut(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnCopy(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPaste(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPreference(wxCommandEvent& ev)
{
    //Call up editor preferences dialog
    EditorPreferencesDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //�t�@�C���ɕۑ�
        if(!wxGetApp().setting.saveSetting()){
            hpl::error::caution("Fail to save setting as [%s]", wxGetApp().setting.getFilePath().c_str());
        }
        //�y���̍�蒼��
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
    
    //�O�̒i�K
    int editMode = wxGetApp().getEventManager()->getEditModeType();

    //��U�S�ă`�F�b�N���͂����܂�
    this->uncheckModesOnMenu();

    //�h���[���[�h�ɂ��܂�
    wxGetApp().getEventManager()->setEditModeType(EditModeType::EM_DRAW);

    //�S���̃_�C�A���O����܂�
    this->closeAllModelessDialogs();
}
void MapEditorMainFrame::closeAllModelessDialogs()
{
    this->objectPropDialog.Show(false);
    this->pointPropDialog.Show(false);
    this->polygonPropDialog.Show(false);
    this->linPropDialog.Show(false);
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
    //�|���S���^�C�v�_�C�A���O�\��
    this->polyTypeDialog.Show(true);
}
void MapEditorMainFrame::OnFloorHeightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_FLOOR_HEIGHT);
    //�����p���b�g�_�C�A���O�\��
    this->heightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingHeightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_CEILING_HEIGHT);
    //�����p���b�g�_�C�A���O�\��
    this->heightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnFloorLightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_FLOOR_LIGHT);
    //���C�g�p���b�g�_�C�A���O�\��
    //TODO this->lightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingLightMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_CEILING_LIGHT);
    //���C�g�p���b�g�_�C�A���O�\��
    //TODO this->lightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnMediaMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_MEDIA);
    //���f�B�A�p���b�g�_�C�A���O�\��
    //TODO this->mediaPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnFloorTextureMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_FLOOR_TEXTURE);
    //�e�N�X�`���_�C�A���O�\��
    this->textureDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingTextureMode(wxCommandEvent& ev)
{
    //���[�h�ύX
    this->changeEditMode(EditModeType::EM_CEILING_TEXTURE);
    //�e�N�X�`���_�C�A���O�\��
    this->textureDialog.Show(true);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// special menus
void MapEditorMainFrame::OnJumpLevel(wxCommandEvent& ev)
{
    //TODO
    SelectLevelDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
    }
}
void MapEditorMainFrame::OnLevelInfo(wxCommandEvent& ev)
{
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //���e�ύX
        //TODO
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
    //
    TerminalDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
}

