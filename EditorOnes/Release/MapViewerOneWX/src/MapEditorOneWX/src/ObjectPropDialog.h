#ifndef _OBJECT_PROP_DIALOG_
#define _OBJECT_PROP_DIALOG_

#include "DlgCommon.h"

class DirectionPanel: public wxPanel{
    wxImage directionCircle;
    wxImage directionMarker;
public:
	DirectionPanel(wxWindow* parent, wxWindowID id);
	virtual ~DirectionPanel();
    DECLARE_EVENT_TABLE()
	void OnLeftDown(wxMouseEvent &ev);
	void OnMotion(wxMouseEvent &ev);
    void OnPaint(wxPaintEvent &event);

	void setFacing(int mx, int my);
	void drawFacing(wxWindow* panel, int facing, wxDC* dc);
public:
};

class ObjectPropDialog: public wxDialog{
    wxStaticText* label_45;
    wxTextCtrl* text_ctrl_27;
    wxChoice* choice_21;
    wxStaticText* label_56;
    wxTextCtrl* text_ctrl_32;
    wxChoice* choice_22;
    wxCheckBox* checkbox_46;
    wxCheckBox* checkbox_47;
    wxCheckBox* checkbox_48;
    wxCheckBox* checkbox_49;
    wxCheckBox* checkbox_50;
    wxCheckBox* checkbox_51;
    wxStaticText* label_59;
    wxTextCtrl* text_ctrl_37;
    wxStaticText* label_58;
    wxTextCtrl* text_ctrl_38;
    DirectionPanel* panel_16;
    wxStaticText* label_60;
    wxChoice* choice_23;
    wxPanel* panel_17;
    wxStaticText* label_61;
    wxTextCtrl* text_ctrl_39;
    wxStaticText* label_63;
    wxTextCtrl* text_ctrl_41;
    wxStaticText* label_62;
    wxTextCtrl* text_ctrl_40;
    wxPanel* panel_18;

	//編集しているオブジェクトインデックス
    int objIndex;

public:
    ObjectPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ObjectPropDialog();

    void setObjIndex(int index);
    int getObjIndex();
    map_object getObject();
    void setObject(map_object obj);
private:
    void setupDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnTypeChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnIndexChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnHiddenCheck(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCeilingCheck(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnSeeCheck(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnHearCheck(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnAerialCheck(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnNetCheck(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnLaunchChoice(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnXEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnYEdit(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnZEdit(wxCommandEvent &event); // wxGlade: <event_handler>

public:
	void refreshParent();
};

#endif
