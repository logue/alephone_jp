#ifndef _LINE_PROP_DIALOG_
#define _LINE_PROP_DIALOG_

#include "DlgCommon.h"

class LinePropDialog: public wxDialog{
    wxStaticBox* sizer_54_staticbox;
    wxStaticText* label_64;
    wxTextCtrl* text_ctrl_42;
    wxTextCtrl* text_ctrl_43;
    wxCheckBox* checkbox_45;
    wxCheckBox* checkbox_52;
    wxCheckBox* checkbox_53;
    wxCheckBox* checkbox_54;
    wxRadioBox* radio_box_1;
    wxStaticText* label_66;
    wxTextCtrl* text_ctrl_45;
    wxStaticText* label_67;
    wxTextCtrl* text_ctrl_46;
    wxStaticText* label_70;
    wxTextCtrl* text_ctrl_47;
    wxStaticText* label_71;
    wxTextCtrl* text_ctrl_50;
    wxStaticText* label_69;
    wxTextCtrl* text_ctrl_51;
    wxStaticText* label_72;
    wxTextCtrl* text_ctrl_52;
    wxStaticText* label_68;
    wxTextCtrl* text_ctrl_53;
    wxButton* button_35;
    wxButton* button_36;

    //線対象
    int lineIndex;
public:
    LinePropDialog();
    bool Create(wxWindow* parent, wxWindowID id, int lineIndex_);
    virtual ~LinePropDialog();

    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnEndpoint1Edit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEndpoint2Edit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnLandscape(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnElevation(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnVariableElev(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnHasTransSide(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnRadioSel(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFloor(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCeiling(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnClockwiseSide(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCClockwiseSide(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnClockwisePoly(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCClockwisePoly(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnOk(wxCommandEvent &ev);
    void OnCancel(wxCommandEvent &ev);

    void setupDialog();
    void setLineIndex(int index);
    int getLineIndex();
public:
	line_data getLine();
};

#endif
