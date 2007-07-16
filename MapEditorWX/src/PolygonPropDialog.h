#ifndef _POLYGON_PROP_DIALOG_
#define _POLYGON_PROP_DIALOG_

#include "DlgCommon.h"

class PolygonPropDialog: public wxDialog{
    wxStaticText* label_34;
    wxTextCtrl* text_ctrl_20;
    wxStaticText* label_46;
    wxTextCtrl* text_ctrl_21;
    wxStaticText* label_35;
    wxChoice* choice_12;
    wxStaticText* label_47;
    wxTextCtrl* text_ctrl_22;
    wxStaticText* label_36;
    wxTextCtrl* text_ctrl_25;
    wxStaticText* label_48;
    wxTextCtrl* text_ctrl_23;
    wxStaticText* label_37;
    wxChoice* choice_13;
    wxStaticText* label_49;
    wxTextCtrl* text_ctrl_24;
    wxStaticText* label_38;
    wxChoice* choice_14;
    wxStaticText* label_26;
    wxTextCtrl* text_ctrl_33;
    wxStaticText* label_27;
    wxTextCtrl* text_ctrl_35;
    wxStaticText* label_39;
    wxTextCtrl* text_ctrl_26;
    wxStaticText* label_55;
    wxTextCtrl* text_ctrl_34;
    wxStaticText* label_28;
    wxTextCtrl* text_ctrl_36;
    wxStaticText* label_40;
    wxChoice* choice_19;
    wxStaticText* label_54;
    wxChoice* choice_15;
    wxStaticText* label_41;
    wxTextCtrl* text_ctrl_28;
    wxStaticText* label_53;
    wxChoice* choice_16;
    wxStaticText* label_42;
    wxTextCtrl* text_ctrl_29;
    wxStaticText* label_52;
    wxChoice* choice_20;
    wxStaticText* label_43;
    wxTextCtrl* text_ctrl_30;
    wxStaticText* label_51;
    wxChoice* choice_17;
    wxStaticText* label_44;
    wxTextCtrl* text_ctrl_31;
    wxStaticText* label_50;
    wxChoice* choice_18;
    wxButton* button_21;
    wxPanel* panel_10;
    wxPanel* panel_11;
    wxPanel* panel_12;

	wxTextCtrl* textFloorHeight;
	wxTextCtrl* textCeilingHeight;
    int polyIndex;
public:
    PolygonPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PolygonPropDialog();

    void setPolyIndex(int index);
    int getPolyIndex();
    void setupDialog();

    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnIDEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFirstNeighborEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnTypeChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnNearCountEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPermuEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCenterXEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFloorLightEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCenterYEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCeilingLightEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnAreaEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFloorOriginXEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFloorOriginYEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCeilingOriginXEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCeilingOriginYEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFirstObjChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnMediaChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFirstExZoneEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnMediaLightChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnLineExZoneEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnSndSrcIndexChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnFloorTransEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnAmbSndChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCeilingTransEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnRndSndChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPlatformBtn(wxCommandEvent &event); // wxGlade: <event_handler>
	void OnFloorHeightEdit(wxCommandEvent &event);
	void OnceilingHeightEdit(wxCommandEvent &event);
};

#endif
