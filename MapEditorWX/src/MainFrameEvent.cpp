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

    switch(wxGetApp().getEventManager()->getEditModeType()){
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
    int tool = wxGetApp().getEventManager()->getToolType();
    switch(tool){
    case ToolType::TI_ARROW:
        break;
    case ToolType::TI_FILL:
        break;
    case ToolType::TI_HAND:
        break;
    case ToolType::TI_LINE:
        break;
    case ToolType::TI_MAGNIFY:
        break;
    case ToolType::TI_SKULL:
        break;
    case ToolType::TI_TEXT:
        break;
    case ToolType::TI_POLYGON:
        break;
    default:
        hpl::error::halt("Invalid tool type");
    }
}
void MapEditorMainFrame::doLButtonOnArrowTool(wxMouseEvent& ev)
{
    //�I��
}
void MapEditorMainFrame::doLButtonOnFillTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnHandTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnLineTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnMagnifyTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnSkullTool(wxMouseEvent& ev)
{
}
void MapEditorMainFrame::doLButtonOnTextTool(wxMouseEvent& ev)
{
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
}
void MapEditorMainFrame::doLButtonOnPolygonTool(wxMouseEvent& ev)
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
