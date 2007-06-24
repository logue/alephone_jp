#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_

#include "MapDemergerOneWX.h"

class MainFrame: public wxFrame{
public:
    MainFrame(const wxString& title);
    DECLARE_EVENT_TABLE()
};

#endif
