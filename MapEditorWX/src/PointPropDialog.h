#ifndef _POINT_PROP_DIALOG_
#define _POINT_PROP_DIALOG_

#include "DlgCommon.h"

class PointPropDialog: public wxDialog{
private:
    wxStaticBox* sizer_52_staticbox;
    wxRadioButton* radio_btn_7;
    wxRadioButton* radio_btn_8;
    wxCheckBox* checkbox_40;
    wxStaticText* label_29;
    wxTextCtrl* text_ctrl_14;
    wxPanel* panel_8;
    wxStaticText* label_30;
    wxTextCtrl* text_ctrl_15;
    wxPanel* panel_9;
    wxStaticText* label_31;
    wxTextCtrl* text_ctrl_16;
    wxTextCtrl* text_ctrl_18;
    wxStaticText* label_32;
    wxTextCtrl* text_ctrl_17;
    wxTextCtrl* text_ctrl_19;
    wxStaticText* label_33;
    wxChoice* choice_11;
public:
    PointPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PointPropDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnEditFloor(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditCeiling(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditX(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditY(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditTX(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditTY(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPolyChoice(wxCommandEvent &event); // wxGlade: <event_handler>
};

#endif
