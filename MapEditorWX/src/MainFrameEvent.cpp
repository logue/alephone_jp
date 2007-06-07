#include "MapEditorMainFrame.h"

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/**
    ���{�^�����������Ƃ��ɌĂ΂��
*/
void MapEditorMainFrame::OnLeftDown(wxMouseEvent &ev)
{
    //�}�E�X���W�L�^
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
    bool shift = ev.ShiftDown();
    bool ctrl = ev.CtrlDown();

//    int toolType = wxGetApp().getEventManager()->getToolType();

    switch(wxGetApp().getEventManager()->getEditMode()){
    case EditModeType::EM_DRAW:
        if(ctrl){
        }else{
            //�������ɃN���b�N
            doLButtonOnDrawMode(ev);
        }
        break;
    case EditModeType::EM_POLYGON_TYPE:
        //TODO
        break;
    case EditModeType::EM_FLOOR_HEIGHT:
        //TODO
        break;
    case EditModeType::EM_CEILING_HEIGHT:
        //TODO
        break;
    case EditModeType::EM_FLOOR_LIGHT:
        //TODO
        break;
    case EditModeType::EM_CEILING_LIGHT:
        //TODO
        break;
    case EditModeType::EM_MEDIA:
        //TODO
        break;
    case EditModeType::EM_FLOOR_TEXTURE:
        //TODO
        break;
    case EditModeType::EM_CEILING_TEXTURE:
        //TODO
        break;
    }
}
void MapEditorMainFrame::doLButtonOnDrawMode(wxMouseEvent& ev)
{
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
    //�}�E�X���W�L�^
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

    if(ev.ButtonIsDown(wxMOUSE_BTN_LEFT)){
        //���{�^���������Ȃ��瓮���Ă���
        bool shift = ev.ShiftDown();
        bool ctrl = ev.CtrlDown();

        //�ҏW���[�h���Ƃɓ��삪�قȂ�
        
        int toolType = wxGetApp().getEventManager()->getToolType();

#ifdef MAP_VIEWER
        //Viewer��p�̓���
#else

#endif

    }
}
void MapEditorMainFrame::OnMouseWheel(wxMouseEvent &ev)
{
}
