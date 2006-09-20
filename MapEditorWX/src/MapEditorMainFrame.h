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
    void OnMotion(wxMouseEvent& ev);
    void OnMouseWheel(wxMouseEvent& ev);

    //centering
    //zoom up
    //zoom in
    //zoom def
    DECLARE_EVENT_TABLE()

};
