#ifndef _LEVEL_INFO_DIALOG_
#define _LEVEL_INFO_DIALOG_

#include "DlgCommon.h"

class LevelInfoDialog: public wxDialog{
    wxStaticBox* sizer_59_staticbox;
    wxStaticBox* sizer_58_staticbox;
    wxStaticBox* sizer_60_staticbox;
    wxStaticText* label_65;
    wxTextCtrl* text_ctrl_44;
    wxStaticText* label_73;
    wxChoice* choice_28;
    wxStaticText* label_74;
    wxChoice* choice_29;
    wxCheckBox* checkbox_60;
    wxCheckBox* checkbox_62;
    wxCheckBox* checkbox_66;
    wxCheckBox* checkbox_63;
    wxCheckBox* checkbox_64;
    wxCheckBox* checkbox_65;
    wxCheckBox* checkbox_67;
    wxCheckBox* checkbox_61;
    wxCheckBox* checkbox_41;
    wxCheckBox* checkbox_42;
    wxCheckBox* checkbox_43;
    wxCheckBox* checkbox_44;
    wxCheckBox* checkbox_55;
    wxCheckBox* checkbox_56;
    wxCheckBox* checkbox_57;
    wxCheckBox* checkbox_58;
    wxCheckBox* checkbox_59;
    wxButton* button_28;
    wxButton* button_29;
public:
    LevelInfoDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~LevelInfoDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()

    void OnOk(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCancel(wxCommandEvent &event); // wxGlade: <event_handler>
};

#endif
