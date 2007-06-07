#include "MapEditorMainFrame.h"

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/**
    左ボタンを押したときに呼ばれる
*/
void MapEditorMainFrame::OnLeftDown(wxMouseEvent &ev)
{
    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
    bool shift = ev.ShiftDown();
    bool ctrl = ev.CtrlDown();

//    int toolType = wxGetApp().getEventManager()->getToolType();

    switch(wxGetApp().getEventManager()->getEditMode()){
    case EditModeType::EM_DRAW:
        if(ctrl){
        }else{
            //押さずにクリック
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
    右ボタンを押したときに呼ばれる
*/
void MapEditorMainFrame::OnRightDown(wxMouseEvent& ev)
{
    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/**
    マウスが移動したときに呼ばれる
*/
void MapEditorMainFrame::OnMotion(wxMouseEvent &ev)
{
    //マウス座標記録
    wxGetApp().getViewGridManager()->setNewMousePoint(ev.m_x, ev.m_y);

    if(ev.ButtonIsDown(wxMOUSE_BTN_LEFT)){
        //左ボタンを押しながら動いている
        bool shift = ev.ShiftDown();
        bool ctrl = ev.CtrlDown();

        //編集モードごとに動作が異なる
        
        int toolType = wxGetApp().getEventManager()->getToolType();

#ifdef MAP_VIEWER
        //Viewer専用の動作
#else

#endif

    }
}
void MapEditorMainFrame::OnMouseWheel(wxMouseEvent &ev)
{
}
