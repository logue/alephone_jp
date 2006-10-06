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
            theApp.selectGroupInformation.clear();
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
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d,", ep.level_number);
                theApp.LevelNameList.Add(//CString(cstr) + 
                    CString(ep.level_name));
            }
            /*sprintf(cstr, "%d", theApp.LevelNameList.GetSize());
            MessageBox(CString(cstr));*/
            theApp.selectType = _no_selected;
        }
        //�X�e�[�^�X�o�[�ɕ\��
        setStatusBar(0, theApp.LevelNameList.GetAt(0));

        //default zoom
        theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
        
        //default position(center)
        OnItemCentering();

        //
        theApp.isChanged = false;
        this->Invalidate(FALSE);
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
        theApp.selectType = _no_selected;

        this->Invalidate(FALSE);

        //�X�e�[�^�X�o�[�ɕ\��
        setStatusBar(0, theApp.LevelNameList.GetAt(theApp.editLevelIndex));
    }
}

//zoom in / out
void CMapEditorSDIView::addZoom(int step)
{
    int oldZoomDiv = theApp.zoomDivision;
    if( theApp.zoomDivision < 50){
        step = sgn<int>(step);
    }
    theApp.zoomDivision += step;
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