#ifndef _HEIGHT_DIALOG_
#define _HEIGHT_DIALOG_

#include "DlgCommon.h"

class HeightDialog: public wxDialog{
protected:
    wxStaticText* label_9;
    wxTextCtrl* text_ctrl_5;
    wxSlider* slider_2;
    wxSlider* slider_3;
    wxStaticText* label_10;
    wxTextCtrl* text_ctrl_6;
    wxCheckBox* checkbox_11;
public:
    HeightDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual  ~HeightDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif
