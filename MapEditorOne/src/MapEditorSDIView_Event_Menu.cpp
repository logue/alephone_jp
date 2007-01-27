#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"

static bool loadMapFromFile(const char* filename){
    FileSpecifier mapFile = FileSpecifier(filename);
    //set map file
    set_map_file(mapFile);
    return true;
}
//open file
void CMapEditorSDIView::OnFileOpen()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B

    if(theApp.isChanged){
        //warn to save
        if(MessageBox(L"map changed, but no save is found.", L"warn to save",
            MB_OKCANCEL | MB_ICONEXCLAMATION) != IDOK)
        {
            return ;
        }
    }
    	//�t�@�C���I�[�v���_�C�A���O�\��
	CFileDialog dlg(TRUE, L"*.*", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

        //�ǂݍ���
        char cstr[256];
        strToChar(filename, cstr);

        //�^�C�g���ɐݒ�
        CMapEditorSDIDoc* doc = GetDocument();
        doc->SetTitle(filename);

        
        //�}�b�v�t�@�C�����[�h
        loadMapFromFile(cstr);

        //���x��1��ǂݍ���ł݂�
        {
            theApp.selectDatas.clear();
            initialize_map_for_new_level();
            theApp.editLevelIndex = 0;
            bool check = load_level_from_map(theApp.editLevelIndex);
            if(!check){
                MessageBox(L"failed");
            }
        }

        /*int s[10];
        for(int i = 0; i < SavedObjectList.size(); i ++){
            int t = SavedObjectList[i].location.x;
            sprintf(cstr, "%d", t);
            //TRACE(CString(cstr)+L"\n");
        }*/
//        char cstr[256];
        //monster_placement_info[0].

        theApp.LevelNameList.RemoveAll();
        
        //int index = 0;
        {
            short index = 0;
            struct entry_point ep;
            int type = 3;
            int num = 0;
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d,", ep.level_number);
                theApp.LevelNameList.Add(//CString(cstr) + 
                    CString(ep.level_name));
                num ++;
            }
            if(num == 0){
                theApp.LevelNameList.Add(CString("unmerged"));
            }
            /*sprintf(cstr, "%d", theApp.LevelNameList.GetSize());
            MessageBox(CString(cstr));*/
        }
        //�X�e�[�^�X�o�[�ɕ\��
        //setStatusBar(0, theApp.LevelNameList.GetAt(0));

        //default zoom
        theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
        
        //default position(center)
        OnItemCentering();

        //
        theApp.isChanged = false;
        this->Invalidate(FALSE);

        initialize_players();
        int index = new_player(0,0,0);

        set_local_player_index(index);
        set_current_player_index(index);

        allocate_render_memory();

    }
}
//save file
void CMapEditorSDIView::OnFileSave()
{
    CFileDialog dlg(FALSE, L"*.sceA", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.sceA)|*.sceA|Any format (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();
        char cstr[256];
        strToChar(filename, cstr);

        //�ۑ�
        if(!save_level(cstr)){
            MessageBox(L"failure");
        }else{
            theApp.isChanged = false;
        }
    }
}

/**
    Jump Level!
*/
void CMapEditorSDIView::On32776()
{
    // TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    //���x���I���_�C�A���O
    CSelectLevelDialog dlg;
    if(dlg.DoModal() == IDOK){
        load_level_from_map(theApp.editLevelIndex);

        //���S�ֈړ�
        OnItemCentering();

        //Zoom
        OnItemZoomDefault();

        //�I�𖳂�
        theApp.selectDatas.clear();

        this->Invalidate(FALSE);

        //�X�e�[�^�X�o�[�ɕ\��
        //setStatusBar(0, theApp.LevelNameList.GetAt(theApp.editLevelIndex));
    }
}

//zoom in / out
void CMapEditorSDIView::addZoom(int step)
{
    int oldZoomDiv = theApp.zoomDivision;

    //�g�嗦���オ������g�嗦�̑������x�𗎂Ƃ�
    if( theApp.zoomDivision < 50){
        step = hpl::math::sgn<int>(step);
    }

    //�g�嗦����
    theApp.zoomDivision += step;

    //�␳
    if(theApp.zoomDivision < ZOOM_DIVISION_MIN){
        theApp.zoomDivision = ZOOM_DIVISION_MIN;
    }else if(theApp.zoomDivision > ZOOM_DIVISION_MAX){
        theApp.zoomDivision = ZOOM_DIVISION_MAX;
    }
    CRect rect;
    GetClientRect(&rect);

    POINT oldOffset = theApp.offset;
    POINT center;
    center.x = rect.Width() / 2;
    center.y = rect.Height() / 2;
    int newZoomDiv = theApp.zoomDivision;

    //�g�厞�͉�ʂ̒��S�ł͂Ȃ��\���̈�̒��S��^�񒆂Ƃ��Ċg��k�����s��
    //���̂��߃Y����␳����K�v������
    int ax = center.x - oldOffset.x;
    theApp.offset.x = center.x - (ax * oldZoomDiv / newZoomDiv);
    int ay = center.y - oldOffset.y;
    theApp.offset.y = center.y - (ay * oldZoomDiv / newZoomDiv);
    /*
    int delta = OFFSET_X_WORLD / theApp.zoomDivision -
        //(rect.Width() / 2) +
        OFFSET_X_WORLD / oldZoomDiv;
    theApp.offset.x -= delta;
    delta = OFFSET_Y_WORLD / theApp.zoomDivision -
        //(rect.Height() / 2) +
        OFFSET_Y_WORLD / oldZoomDiv;
    theApp.offset.y -= delta;
    */
}

//�g��
void CMapEditorSDIView::OnZoomIn()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    addZoom(-ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//�k��
void CMapEditorSDIView::OnZoomOut()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    addZoom(ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//���S�ֈړ�
void CMapEditorSDIView::OnItemCentering()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.offset.x = 0;
    theApp.offset.y = 0;
    Invalidate(FALSE);
}
//�g��W��
void CMapEditorSDIView::OnItemZoomDefault()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
    Invalidate(FALSE);
}
//object info dialog on/off
void CMapEditorSDIView::On32784()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.objectPropertyDialog->ShowWindow(!theApp.objectPropertyDialog->IsWindowVisible());
    int flags = MF_BYCOMMAND;
    if(theApp.objectPropertyDialog->IsWindowVisible()){
        flags |= MF_CHECKED;
    }else{
        flags |= MF_UNCHECKED;
    }
    GetMenu()->CheckMenuItem(ID_32784, flags);
}
//level information(same to new)
void CMapEditorSDIView::On32787()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CLevelParameterDialog dlg(this, false);
    if(dlg.DoModal() == IDOK){
        //�l�ݒ�
    }
}
//show/hide height dialog
void CMapEditorSDIView::On32789()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.heightDialog->ShowWindow(!theApp.heightDialog->IsWindowVisible());
}
//show/hide polygon type dialog
void CMapEditorSDIView::On32786()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.polygonTypeDialog->ShowWindow(!theApp.polygonTypeDialog->IsWindowVisible());
}
//edit terminals
void CMapEditorSDIView::On32790()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CTerminalDialog dlg(this);
    if(dlg.DoModal() == IDOK){
        //�ύX��ۑ�

    }
}

void CMapEditorSDIView::changeMode(int mode)
{
    int oldMode = theApp.getEditMode();
    int nextMode = mode;
    theApp.setEditMode(nextMode);
    //�`�F�b�N��ύX
    int flags = 0;
    flags = MF_BYCOMMAND | MF_UNCHECKED;
    //GetMenu()->CheckMenuItem(theApp.menuIDMap[oldMode], flags);
    flags = MF_BYCOMMAND | MF_CHECKED;
    //GetMenu()->CheckMenuItem(theApp.menuIDMap[nextMode], flags);

    //change mode
    if(mode != EM_DRAW){
        theApp.selectDatas.clear();
    }
    if(mode != EM_FLOOR_TEXTURE && mode != EM_CEILING_TEXTURE){
        //hide texture palette
        theApp.textureDialog->ShowWindow(FALSE);
    }
    Invalidate(FALSE);

}
//draw polygon mode
void CMapEditorSDIView::On32795()
{
    changeMode(EM_DRAW);
}
//height -> floor
void CMapEditorSDIView::OnHeightFloor()
{
    changeMode(EM_FLOOR_HEIGHT);
}
//polygontype mode
void CMapEditorSDIView::OnModePolygontype()
{
    changeMode(EM_POLYGON_TYPE);

    //show polygon type dialog
    theApp.polygonTypeDialog->ShowWindow(TRUE);
    //set selection as default
    theApp.polygonTypeDialog->polygonTypeListCtrl.SetItemState(
        0, LVIS_SELECTED | LVIS_FOCUSED,
        LVIS_SELECTED | LVIS_FOCUSED);
    //hide other dialog
    theApp.objectPropertyDialog->ShowWindow(FALSE);
    theApp.polygonPropertyDialog->ShowWindow(FALSE);
    
}

// new file
void CMapEditorSDIView::OnFileNew()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    //�m�F�_�C�A���O
    //�}�b�v���_�C�A���O�\��
    CLevelParameterDialog dlg(this, true);
    if(dlg.DoModal() == IDOK){
        //�}�b�v���폜
        initialize_map_for_new_level();
        //���x���ꗗ�폜
        theApp.LevelNameList.RemoveAll();
        //
        Invalidate(FALSE);
        theApp.isChanged = false;
    }
}
//visual mode dialog
void CMapEditorSDIView::On32796()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    if(theApp.isLoadedShapesFile){
        setStatusBar(0, _T("start visual mode"));
        CVisualDialog dlg(this);

        if(dlg.DoModal() == IDOK){
        }
    }else{
        AfxMessageBox(L"visual mode requires Shapes files of Marathon!!!");
    }
}
//object placement
void CMapEditorSDIView::On32788()
{
    // TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CObjectPlacementDialog dlg(this);
    setStatusBar(0, L"object placement");
    if(dlg.DoModal() == IDOK){
        //���e�𔽉f
    }
}
//tool dialog
void CMapEditorSDIView::OnMenu32797()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    theApp.toolDialog->ShowWindow(!theApp.toolDialog->IsWindowVisible());
}

//Preferences
void CMapEditorSDIView::On32808()
{
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    CEditorInforDialog dlg(AfxGetMainWnd());
    if(dlg.DoModal() == IDOK){
        //enable change
        theApp.setting.setGridSizeIndex(dlg.gridIndex);

        theApp.setting.setColorSetting(&dlg.colorSetting);

        for(int i = 0; i < NUMBER_OF_EDITOR_FLAGS; i ++){
            theApp.setting.flags[i] = dlg.flags[i];
        }
        Invalidate(FALSE);
    }
}

//texture mode
void CMapEditorSDIView::OnTextureFloor()
{
    changeMode(EM_FLOOR_TEXTURE);
    //show texture palette
    theApp.textureDialog->setupDialog(0);
    theApp.textureDialog->ShowWindow(TRUE);
}
