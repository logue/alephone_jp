#ifndef _LIGHT_PALETTE_DIALOG_
#define _LIGHT_PALETTE_DIALOG_

#include "DlgCommon.h"

class LightPaletteDialog: public wxDialog{
    wxButton* button_31;
    wxButton* button_30;
    wxListCtrl* list_ctrl_5;
    bool isFloor_;
public:
    LightPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~LightPaletteDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnAdd(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnDelete(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEdit(wxListEvent &event); // wxGlade: <event_handler>
public:
    void setFloor(bool fl);
};

#endif
