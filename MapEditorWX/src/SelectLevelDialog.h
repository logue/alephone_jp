#ifndef _SELECT_LEVEL_DIALOG_
#define _SELECT_LEVEL_DIALOG_

#include "DlgCommon.h"

class SelectLevelDialog: public wxDialog{
    wxStaticText* label_57;
    wxListBox* list_box_4;
    wxButton* button_22;
    wxButton* button_23;
    int selectLevel;
public:
    int getSelectLevel();

    SelectLevelDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~SelectLevelDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnList(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnOk(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCancel(wxCommandEvent &event); // wxGlade: <event_handler>
};

#endif
