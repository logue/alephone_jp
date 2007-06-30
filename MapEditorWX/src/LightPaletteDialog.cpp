#include "LightPaletteDialog.h"
#include "MapEditorWX.h"
enum{
    ID_EDIT
};

BEGIN_EVENT_TABLE(LightPaletteDialog, wxDialog)
    EVT_BUTTON(wxID_ADD, LightPaletteDialog::OnAdd)
    EVT_BUTTON(wxID_DELETE, LightPaletteDialog::OnDelete)
    EVT_LIST_END_LABEL_EDIT(ID_EDIT, LightPaletteDialog::OnEdit)
END_EVENT_TABLE()
LightPaletteDialog::LightPaletteDialog()
{
}
LightPaletteDialog::~LightPaletteDialog()
{
}
bool LightPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Light Pallet"));

    button_31 = new wxButton(this, wxID_ADD, wxEmptyString);
    button_30 = new wxButton(this, wxID_DELETE, wxEmptyString);
    list_ctrl_5 = new wxListCtrl(this, ID_EDIT, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxSUNKEN_BORDER);

    list_ctrl_5->SetMinSize(wxSize(150, 200));

    wxFlexGridSizer* grid_sizer_40 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_41 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_41->Add(button_31, 0, 0, 0);
    grid_sizer_41->Add(button_30, 0, 0, 0);
    grid_sizer_40->Add(grid_sizer_41, 1, wxEXPAND, 0);
    grid_sizer_40->Add(list_ctrl_5, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_40);
    grid_sizer_40->Fit(this);
    Layout();

    
    return result;
}
void LightPaletteDialog::OnAdd(wxCommandEvent &event)
{
    //TODO
}
void LightPaletteDialog::OnDelete(wxCommandEvent &event)
{
    //TODO
}
void LightPaletteDialog::OnEdit(wxListEvent &event)
{
    //TODO
}

void LightPaletteDialog::setFloor(bool fl)
{
    this->isFloor_ = fl;
}
