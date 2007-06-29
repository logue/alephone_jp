#ifndef _HEIGHT_PALLET_DIALOG_
#define _HEIGHT_PALLET_DIALOG_

#include "DlgCommon.h"

class HeightPaletteDialog: public wxDialog{
    wxButton* button_24;
    wxButton* button_25;
    wxListCtrl* list_ctrl_3;
public:
    HeightPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~HeightPaletteDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnAdd(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnDelete(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEdit(wxListEvent &event); // wxGlade: <event_handler>
};

#endif
