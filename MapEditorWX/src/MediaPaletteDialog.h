#ifndef _MEDIA_PALETTE_DIALOG_
#define _MEDIA_PALETTE_DIALOG_

#include "DlgCommon.h"

class MediaPaletteDialog: public wxDialog{
    wxButton* button_27;
    wxButton* button_26;
    wxListCtrl* list_ctrl_4;
public:
    MediaPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~MediaPaletteDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnAdd(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnDelete(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEdit(wxListEvent &event); // wxGlade: <event_handler>
public:
	void setupDialog();
};

#endif
