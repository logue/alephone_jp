#include "MapEditorWX.h"
#include "MapEditorMainFrame.h"

IMPLEMENT_APP(MapEditorWX)

//load color informations

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;
const int WINDOW_DEFAULT_X = 50;
const int WINDOW_DEFAULT_Y = 50;
const int BUF_MAX = 1024;

bool MapEditorWX::OnInit()
{
    //��ʓI�ȏ����ݒ�
    if(!this->initialize()){
        wxMessageBox(_T("Initialize failure"));
        exit(-1);
    }

    //�E�C���h�E�t���[���𐶐����܂�
    MapEditorMainFrame *frame = new MapEditorMainFrame(
        TITLE_TEXT_BASE,
        wxPoint(WINDOW_DEFAULT_X, WINDOW_DEFAULT_Y), wxSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT));
    frame->Show(true);
    //SetTopWindow(frame);

    //load informations
    
    return TRUE;
}

/*
void wxStringToChar(wxString& str, char* cstr)
{
    int i = 0;
    for(i = 0; i < (int)str.length(); i ++){
        cstr[i] = str.GetChar(i);
    }
    cstr[i] = '\0';
}

*/
hpl::aleph::view::HPLViewGridManager* MapEditorWX::getViewGridManager()
{
    return &this->viewGridManager;
}

/**
    �f�[�^��������擾���܂�
    load data strings from file
    @param filePath �t�@�C���p�X file path
    @param maxLines �ő�s��
*/
void MapEditorWX::loadInfo(const char* filePath, int maxLines)
{
    std::ifstream ifs;
    ifs.open(filePath);
    if(!ifs.is_open()){
        hpl::error::halt("Couldn't open tag file:%s", filePath);
    }

}

