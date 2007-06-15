#ifndef _COLOR_CUSTOMIZE_DIALOG_
#define _COLOR_CUSTOMIZE_DIALOG_

#include "DlgCommon.h"

class ColorCustomizeDialog: public wxDialog{
public:
    wxStaticText* label_13;
    wxButton* button_7;
    wxPanel* panel_1;
    wxStaticText* label_14;
    wxButton* button_8;
    wxPanel* panel_2;
    wxStaticText* label_16;
    wxButton* button_9;
    wxPanel* panel_3;
    wxStaticText* label_15;
    wxButton* button_10;
    wxPanel* panel_4;
    wxStaticText* label_17;
    wxButton* button_11;
    wxPanel* panel_5;
    wxStaticText* label_18;
    wxButton* button_12;
    wxPanel* panel_6;
    wxButton* button_5;
    wxButton* button_6;

    ColorCustomizeDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ColorCustomizeDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
    void OnOk(wxCommandEvent& wv);
    void OnCancel(wxCommandEvent &ev);
    void OnBackground(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnGrid(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnLines(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPolygons(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnStrings(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPoints(wxCommandEvent &event); // wxGlade: <event_handler>
};

#endif
