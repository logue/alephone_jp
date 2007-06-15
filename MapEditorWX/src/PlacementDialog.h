#ifndef _PLACEMENT_DIALOG_
#define _PLACEMENT_DIALOG_

#include "DlgCommon.h"

class PlacementDialog: public wxDialog{
private:
    wxStaticText* label_21;
    wxTextCtrl* text_ctrl_8;
    wxStaticText* label_22;
    wxTextCtrl* text_ctrl_9;
    wxStaticText* label_23;
    wxTextCtrl* text_ctrl_10;
    wxStaticText* label_24;
    wxTextCtrl* text_ctrl_11;
    wxStaticText* label_25;
    wxTextCtrl* text_ctrl_12;
    wxButton* button_17;
    wxButton* button_18;
    wxButton* button_19;
    wxCheckBox* checkbox_39;
    wxListCtrl* list_ctrl_1;
    wxButton* button_16;
public:
    PlacementDialog();
    virtual ~PlacementDialog();

    bool Create(wxWindow* parent, wxWindowID id);
    void OnOk(wxCommandEvent& ev);
    void OnEditInitial(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditMinimum(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditMaximum(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEditRandomCount(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnRandomChance(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnInf(wxCommandEvent &ev);
    void OnAllInf(wxCommandEvent &ev);
    void OnSetInitial(wxCommandEvent &ev);
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif
