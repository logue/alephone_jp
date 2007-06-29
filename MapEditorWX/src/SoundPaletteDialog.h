#ifndef _SOUND_PALETTE_DIALOG_
#define _SOUND_PALETTE_DIALOG_

#include "DlgCommon.h"

class SoundPaletteDialog: public wxDialog{
    wxButton* button_32;
    wxButton* button_33;
    wxListCtrl* list_ctrl_6;
public:
    SoundPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~SoundPaletteDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnAdd(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnDelete(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEdit(wxListEvent &event); // wxGlade: <event_handler>
};

#endif
