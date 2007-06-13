#ifndef _PLATFORM_DIALOG_
#define _PLATFORM_DIALOG_

#include <wx/dialog.h>

class PlatformDialog: public wxDialog{
public:
    PlatformDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PlatformDialog();

    DECLARE_EVENT_TABLE()
};

#endif
