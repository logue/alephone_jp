#include "MapEditorWX.h"
#include "MapEditorMainFrame.h"

IMPLEMENT_APP(MapEditorWX)

//load color informations

bool MapEditorWX::OnInit()
{
    MapEditorMainFrame *frame = new MapEditorMainFrame(
        _T("map editor one"),
        wxPoint(50,50), wxSize(800, 600));
    frame->Show(true);
    //SetTopWindow(frame);

    //load informations
    
    return TRUE;
}

void wxStringToChar(wxString& str, char* cstr)
{
    int i = 0;
    for(i = 0; i < (int)str.length(); i ++){
        cstr[i] = str.GetChar(i);
    }
    cstr[i] = '\0';
}

