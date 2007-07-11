#ifndef _OBJECT_PROP_DIALOG_
#define _OBJECT_PROP_DIALOG_

#include "DlgCommon.h"

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
    wxPanel* panel_16;
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
    void setObject(map_object& obj);
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

    void OnPaint(wxPaintEvent &event);

	void drawFacing(wxWindow* panel);
};

#endif
