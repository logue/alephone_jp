#pragma once

#include "MapEditorWX.h"

/**
    event id
*/
enum
{
    ID_Quit = wxID_EXIT,
    ID_About = wxID_ABOUT,
    ID_New,
    ID_Open,
};

/**
    editor's main frame
*/
class MapEditorMainFrame: public wxFrame
{
public:
    MapEditorMainFrame(const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnOpen(wxCommandEvent& event);

    void OnLeftDown(wxMouseEvent& ev);
    void OnRightDown(wxMouseEvent& ev);
    void OnMotion(wxMouseEvent& ev);
    void OnMouseWheel(wxMouseEvent& ev);

    //centering
    //zoom up
    //zoom in
    //zoom def
    DECLARE_EVENT_TABLE()

private:
    /**
        メニューのセットアップ
    */
    void setupMenus();

    /**
        マップデータの表示
    */
    void drawBackground(wxPaintDC* dc);
    void drawPolygons(wxPaintDC* dc);
    void drawLines(wxPaintDC* dc);
    void drawSides(wxPaintDC* dc);
    void drawPoints(wxPaintDC* dc);
    void drawObjects(wxPaintDC* dc);

    /**
        マウスイベント処理
    */
    void doLButtonOnDrawMode(wxMouseEvent& ev);
    void doLButtonOnPolygonMode(wxMouseEvent& ev);
    void doLButtonOnFloorHeightMode(wxMouseEvent& ev);
    void doLButtonOnCeilingHeightMode(wxMouseEvent& ev);
    void doLButtonOnFloorLightMode(wxMouseEvent& ev);
    void doLButtonOnCeilingLightMode(wxMouseEvent& ev);
    void doLButtonOnMediaMode(wxMouseEvent& ev);
    void doLButtonOnFloorTextureMode(wxMouseEvent& ev);
    void doLButtonOnCeilingTextureMode(wxMouseEvent& ev);
};
