#ifndef _TERMINAL_DIALOG_
#define _TERMINAL_DIALOG_

#include "DlgCommon.h"

class TerminalDialog: public wxDialog{
private:
    wxListBox* list_box_1;
    wxListBox* list_box_2;
    wxListBox* list_box_3;
    wxPanel* panel_7;
    wxTextCtrl* text_ctrl_13;
    wxButton* button_20;
public:
    TerminalDialog();
    virtual ~TerminalDialog();

    bool Create(wxWindow* parent, wxWindowID id);
    void OnOk(wxCommandEvent& ev);
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnSelTerminal(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnSelScreen(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnSelInfo(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEdit(wxCommandEvent &event); // wxGlade: <event_handler>
};

#endif
