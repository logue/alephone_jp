#include "MediaPaletteDialog.h"
#include "MapEditorWX.h"
enum{
    ID_EDIT,
};

BEGIN_EVENT_TABLE(MediaPaletteDialog, wxDialog)
    EVT_BUTTON(wxID_ADD, MediaPaletteDialog::OnAdd)
    EVT_BUTTON(wxID_DELETE, MediaPaletteDialog::OnDelete)
    EVT_LIST_END_LABEL_EDIT(ID_EDIT, MediaPaletteDialog::OnEdit)
END_EVENT_TABLE()
MediaPaletteDialog::MediaPaletteDialog()
{
}
MediaPaletteDialog::~MediaPaletteDialog()
{
}
bool MediaPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height Pallet"));

    button_27 = new wxButton(this, wxID_ADD, wxEmptyString);
    button_26 = new wxButton(this, wxID_DELETE, wxEmptyString);
    list_ctrl_4 = new wxListCtrl(this, ID_EDIT, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxSUNKEN_BORDER);

    list_ctrl_4->SetMinSize(wxSize(154, 200));

    wxFlexGridSizer* grid_sizer_30 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_31 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_31->Add(button_27, 0, 0, 0);
    grid_sizer_31->Add(button_26, 0, 0, 0);
    grid_sizer_30->Add(grid_sizer_31, 1, wxEXPAND, 0);
    grid_sizer_30->Add(list_ctrl_4, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_30);
    grid_sizer_30->Fit(this);
    Layout();
    return result;
}
void MediaPaletteDialog::OnAdd(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (MediaPaletteDialog::OnAdd) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void MediaPaletteDialog::OnDelete(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (MediaPaletteDialog::OnDelete) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void MediaPaletteDialog::OnEdit(wxListEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (MediaPaletteDialog::OnEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
