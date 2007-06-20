#include "TerminalDialog.h"

enum{
    ID_TERMINAL,
    ID_SCREEN,
    ID_INFO,
    ID_TEXT_EDIT
};

BEGIN_EVENT_TABLE(TerminalDialog, wxDialog)
    EVT_LISTBOX(ID_TERMINAL, TerminalDialog::OnSelTerminal)
    EVT_LISTBOX(ID_SCREEN, TerminalDialog::OnSelScreen)
    EVT_LISTBOX(ID_INFO, TerminalDialog::OnSelInfo)
    EVT_TEXT(ID_TEXT_EDIT, TerminalDialog::OnEdit)
    EVT_BUTTON(wxID_OK, TerminalDialog::OnOk)
END_EVENT_TABLE()

TerminalDialog::TerminalDialog():wxDialog()
{
}

TerminalDialog::~TerminalDialog()
{
}
bool TerminalDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Terminal"));
    if(!result){
        return result;
    }
    list_box_1 = new wxListBox(this, ID_TERMINAL);
    list_box_2 = new wxListBox(this, ID_SCREEN);
    list_box_3 = new wxListBox(this, ID_INFO);
    panel_7 = new wxPanel(this, wxID_ANY);
    text_ctrl_13 = new wxTextCtrl(this, ID_TEXT_EDIT, wxEmptyString);
    button_20 = new wxButton(this, wxID_OK, wxEmptyString);

    list_box_1->SetMinSize(wxSize(-1, 200));
    list_box_2->SetMinSize(wxSize(-1, 100));
    panel_7->SetMinSize(wxSize(500, 200));
    text_ctrl_13->SetMinSize(wxSize(500, 200));

    wxFlexGridSizer* grid_sizer_5 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_7 = new wxFlexGridSizer(3, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_6 = new wxFlexGridSizer(3, 1, 0, 0);
    grid_sizer_6->Add(list_box_1, 0, 0, 0);
    grid_sizer_6->Add(list_box_2, 0, 0, 0);
    grid_sizer_6->Add(list_box_3, 0, 0, 0);
    grid_sizer_5->Add(grid_sizer_6, 1, wxEXPAND, 0);
    grid_sizer_7->Add(panel_7, 1, wxEXPAND, 0);
    grid_sizer_7->Add(text_ctrl_13, 0, 0, 0);
    grid_sizer_7->Add(button_20, 0, wxALIGN_RIGHT, 0);
    grid_sizer_5->Add(grid_sizer_7, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_5);
    grid_sizer_5->Fit(this);
    Layout();
    return result;
}
void TerminalDialog::OnOk(wxCommandEvent& ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void TerminalDialog::OnSelTerminal(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TerminalDialog::OnSelTerminal) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void TerminalDialog::OnSelScreen(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TerminalDialog::OnSelScreen) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void TerminalDialog::OnSelInfo(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TerminalDialog::OnSelInfo) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void TerminalDialog::OnEdit(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TerminalDialog::OnEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
