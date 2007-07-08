#ifndef _PLATFORM_DIALOG_
#define _PLATFORM_DIALOG_

#include "DlgCommon.h"

class PlatformDialog: public wxDialog{
public:
    wxStaticBox* sizer_31_staticbox;
    wxStaticBox* sizer_27_staticbox;
    wxStaticBox* sizer_28_staticbox;
    wxStaticBox* sizer_19_staticbox;
    wxStaticBox* sizer_12_staticbox;
    wxStaticBox* sizer_11_staticbox;
    wxStaticBox* sizer_10_staticbox;
    wxStaticText* label_1;
    wxChoice* choice_1;
    wxStaticText* label_2;
    wxTextCtrl* text_ctrl_1;
    wxChoice* choice_2;
    wxStaticText* label_3;
    wxTextCtrl* text_ctrl_2;
    wxChoice* choice_3;
    wxCheckBox* checkbox_7;
    wxStaticText* label_4;
    wxTextCtrl* text_ctrl_3;
    wxCheckBox* checkbox_8;
    wxStaticText* label_5;
    wxTextCtrl* text_ctrl_4;
    wxCheckBox* checkbox_1;
    wxCheckBox* checkbox_2;
    wxCheckBox* checkbox_3;
    wxCheckBox* checkbox_4;
    wxCheckBox* checkbox_5;
    wxCheckBox* checkbox_6;
    wxCheckBox* checkbox_9;
    wxStaticText* label_6;
    wxChoice* choice_4;
    wxRadioButton* radio_btn_1;
    wxRadioButton* radio_btn_2;
    wxRadioButton* radio_btn_3;
    wxCheckBox* checkbox_10;
    wxStaticText* label_7;
    wxChoice* choice_5;
    wxCheckBox* checkbox_15;
    wxCheckBox* checkbox_16;
    wxCheckBox* checkbox_17;
    wxCheckBox* checkbox_18;
    wxCheckBox* checkbox_19;
    wxStaticText* label_8;
    wxChoice* choice_6;
    wxRadioButton* radio_btn_4;
    wxRadioButton* radio_btn_5;
    wxRadioButton* radio_btn_6;
    wxCheckBox* checkbox_12;
    wxCheckBox* checkbox_13;
    wxCheckBox* checkbox_14;
    wxCheckBox* checkbox_20;
    wxCheckBox* checkbox_21;
    wxCheckBox* checkbox_22;
    wxCheckBox* checkbox_24;
    wxCheckBox* checkbox_23;
    wxCheckBox* checkbox_25;
    wxCheckBox* checkbox_26;
    wxButton* button_1;
    wxButton* button_2;

    int polyIndex;
    int platformIndex;
public:
    PlatformDialog();
    bool Create(wxWindow* parent, wxWindowID id, int pindex);
    virtual ~PlatformDialog();
    DECLARE_EVENT_TABLE()

    void OnOk(wxCommandEvent& ev);
    void OnCancel(wxCommandEvent& ev);
    
public:
};

#endif
