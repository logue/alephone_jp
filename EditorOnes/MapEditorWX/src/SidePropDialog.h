#ifndef _SIDE_PROP_DIALOG_
#define _SIDE_PROP_DIALOG_

#include "DlgCommon.h"

class SidePropDialog: public wxDialog{
    wxStaticBox* sizer_57_copy_1_staticbox;
    wxStaticBox* sizer_57_copy_staticbox;
    wxStaticBox* sizer_57_staticbox;
    wxStaticBox* sizer_56_staticbox;
    wxStaticBox* sizer_55_staticbox;
    wxStaticText* label_80;
    wxTextCtrl* text_ctrl_55;
    wxStaticText* label_81;
    wxChoice* choice_27;
    wxCheckBox* checkbox_68;
    wxCheckBox* checkbox_69;
    wxCheckBox* checkbox_70;
    wxStaticText* label_87;
    wxChoice* choice_25;
    wxStaticText* label_88;
    wxChoice* choice_26;
    wxCheckBox* checkbox_71;
    wxCheckBox* checkbox_72;
    wxCheckBox* checkbox_73;
    wxCheckBox* checkbox_74;
    wxCheckBox* checkbox_75;
    wxStaticText* label_89;
    wxTextCtrl* text_ctrl_61;
    wxStaticText* label_93;
    wxTextCtrl* text_ctrl_65;
    wxStaticText* label_97;
    wxStaticText* label_90;
    wxTextCtrl* text_ctrl_62;
    wxStaticText* label_94;
    wxTextCtrl* text_ctrl_66;
    wxStaticText* label_98;
    wxStaticText* label_91;
    wxTextCtrl* text_ctrl_63;
    wxStaticText* label_95;
    wxTextCtrl* text_ctrl_67;
    wxStaticText* label_99;
    wxStaticText* label_92;
    wxTextCtrl* text_ctrl_64;
    wxStaticText* label_96;
    wxTextCtrl* text_ctrl_68;
    wxStaticText* label_100;
    wxStaticText* label_102;
    wxTextCtrl* text_ctrl_70;
    wxStaticText* label_82;
    wxTextCtrl* text_ctrl_57;
    wxStaticText* label_101;
    wxTextCtrl* text_ctrl_69;
    wxStaticText* label_83;
    wxTextCtrl* text_ctrl_58;
    wxStaticText* label_84;
    wxTextCtrl* text_ctrl_59;
    wxPanel* panel_14;
    wxStaticText* label_85;
    wxTextCtrl* text_ctrl_60;
    wxStaticText* label_86;
    wxChoice* choice_24;
    wxStaticText* label_83_copy;
    wxTextCtrl* text_ctrl_58_copy;
    wxStaticText* label_84_copy;
    wxTextCtrl* text_ctrl_59_copy;
    wxPanel* panel_14_copy;
    wxStaticText* label_85_copy;
    wxTextCtrl* text_ctrl_60_copy;
    wxStaticText* label_86_copy;
    wxChoice* choice_24_copy;
    wxStaticText* label_83_copy_1;
    wxTextCtrl* text_ctrl_58_copy_1;
    wxStaticText* label_84_copy_1;
    wxTextCtrl* text_ctrl_59_copy_1;
    wxPanel* panel_14_copy_1;
    wxStaticText* label_85_copy_1;
    wxTextCtrl* text_ctrl_60_copy_1;
    wxStaticText* label_86_copy_1;
    wxChoice* choice_24_copy_1;
    wxButton* button_38;
    wxButton* button_39;

    int index;
    void setIndex(int ind);
    int getIndex();
public:
    SidePropDialog();
    bool Create(wxWindow* parent, wxWindowID id, int sideIndex);
    virtual ~SidePropDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
	void OnOk(wxCommandEvent& ev);
	void OnCancel(wxCommandEvent& ev);
	void OnControlPanelTypeChoice(wxCommandEvent& ev);
	void setupPermutationChoice(int controlPanelType);
public:
	side_data getSide();
};

#endif
