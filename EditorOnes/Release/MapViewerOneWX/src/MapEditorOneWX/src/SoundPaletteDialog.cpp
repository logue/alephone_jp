#include "SoundPaletteDialog.h"
#include "MapEditorWX.h"
enum{
    ID_EDIT,
};

BEGIN_EVENT_TABLE(SoundPaletteDialog, wxDialog)
    // begin wxGlade: SoundPaletteDialog::event_table
    EVT_BUTTON(wxID_ADD, SoundPaletteDialog::OnAdd)
    EVT_BUTTON(wxID_DELETE, SoundPaletteDialog::OnDelete)
    EVT_LIST_END_LABEL_EDIT(ID_EDIT, SoundPaletteDialog::OnEdit)
    // end wxGlade
END_EVENT_TABLE()
SoundPaletteDialog::SoundPaletteDialog()
{
}
SoundPaletteDialog::~SoundPaletteDialog()
{
}
bool SoundPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Sound Pallet"));

    button_32 = new wxButton(this, wxID_ADD, wxEmptyString);
    button_33 = new wxButton(this, wxID_DELETE, wxEmptyString);
    list_ctrl_6 = new wxListCtrl(this, ID_EDIT, wxDefaultPosition, wxDefaultSize,
		wxLC_REPORT|wxSUNKEN_BORDER | wxLC_SINGLE_SEL);
    return result;
}
void SoundPaletteDialog::OnAdd(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (SoundPaletteDialog::OnAdd) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void SoundPaletteDialog::OnDelete(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (SoundPaletteDialog::OnDelete) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
void SoundPaletteDialog::OnEdit(wxListEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (SoundPaletteDialog::OnEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
