#include "HeightPaletteDialog.h"
#include "MapEditorWX.h"
enum{
    ID_EDIT,
};

BEGIN_EVENT_TABLE(HeightPaletteDialog, wxDialog)
    EVT_BUTTON(wxID_ADD, HeightPaletteDialog::OnAdd)
    EVT_BUTTON(wxID_DELETE, HeightPaletteDialog::OnDelete)
    EVT_LIST_END_LABEL_EDIT(ID_EDIT, HeightPaletteDialog::OnEdit)
END_EVENT_TABLE()
HeightPaletteDialog::HeightPaletteDialog()
{
}
HeightPaletteDialog::~HeightPaletteDialog()
{
}
bool HeightPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height Pallet"));
    button_24 = new wxButton(this, wxID_ADD, wxEmptyString);
    button_25 = new wxButton(this, wxID_DELETE, wxEmptyString);
    list_ctrl_3 = new wxListCtrl(this, ID_EDIT, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_EDIT_LABELS|wxSUNKEN_BORDER);

    list_ctrl_3->SetMinSize(wxSize(154, 200));

    wxFlexGridSizer* grid_sizer_28 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_29 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_29->Add(button_24, 0, 0, 0);
    grid_sizer_29->Add(button_25, 0, 0, 0);
    grid_sizer_28->Add(grid_sizer_29, 1, wxEXPAND, 0);
    grid_sizer_28->Add(list_ctrl_3, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_28);
    grid_sizer_28->Fit(this);
    Layout();
    return result;
}
void HeightPaletteDialog::OnAdd(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (HeightPaletteDialog::OnAdd) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void HeightPaletteDialog::OnDelete(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (HeightPaletteDialog::OnDelete) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void HeightPaletteDialog::OnEdit(wxListEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (HeightPaletteDialog::OnEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
