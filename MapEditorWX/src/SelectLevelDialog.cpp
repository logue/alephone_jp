#include "SelectLevelDialog.h"
#include "MapEditorWX.h"
enum{
    ID_List,
};

BEGIN_EVENT_TABLE(SelectLevelDialog, wxDialog)
    EVT_LISTBOX(ID_List, SelectLevelDialog::OnList)
//    EVT_BUTTON(wxID_OK, SelectLevelDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, SelectLevelDialog::OnCancel)
END_EVENT_TABLE()
SelectLevelDialog::SelectLevelDialog()
{
}
SelectLevelDialog::~SelectLevelDialog()
{
}
bool SelectLevelDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Select Level"));
    label_57 = new wxStaticText(this, wxID_ANY, wxT("Select level"));

    list_box_4 = new wxListBox(this, wxID_ANY);
//    button_22 = new wxButton(this, wxID_OK, wxEmptyString);
    button_23 = new wxButton(this, wxID_CANCEL, wxEmptyString);

    list_box_4->SetMinSize(wxSize(320, 320));

    wxFlexGridSizer* grid_sizer_17 = new wxFlexGridSizer(3, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_25 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_17->Add(label_57, 0, 0, 0);
    grid_sizer_17->Add(list_box_4, 0, wxEXPAND, 0);
//    grid_sizer_25->Add(button_22, 0, wxRIGHT|wxALIGN_RIGHT, 0);
    grid_sizer_25->Add(button_23, 0, wxRIGHT|wxALIGN_RIGHT, 0);
    grid_sizer_17->Add(grid_sizer_25, 1, wxALIGN_RIGHT, 0);
    SetSizer(grid_sizer_17);
    grid_sizer_17->Fit(this);
    Layout();

    return result;
}
void SelectLevelDialog::OnList(wxCommandEvent &event)
{
    int sel = event.GetSelection();
    this->selectLevel = sel;
}
int SelectLevelDialog::getSelectLevel()
{
    return this->selectLevel;
}


void SelectLevelDialog::OnOk(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (SelectLevelDialog::OnOk) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void SelectLevelDialog::OnCancel(wxCommandEvent &event)
{
    SetReturnCode(wxCANCEL);
    Destroy();
}
