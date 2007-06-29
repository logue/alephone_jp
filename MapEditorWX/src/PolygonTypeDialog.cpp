#include "PolygonTypeDialog.h"
#include "MapEditorWX.h"
enum{
    ID_SEL
};
BEGIN_EVENT_TABLE(PolygonTypeDialog, wxDialog)
    EVT_LIST_ITEM_SELECTED(ID_SEL, PolygonTypeDialog::OnSel)
END_EVENT_TABLE()
PolygonTypeDialog::PolygonTypeDialog()
{
}
PolygonTypeDialog::~PolygonTypeDialog()
{
}
bool PolygonTypeDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Polygon Type"));

    list_ctrl_2 = new wxListCtrl(this, ID_SEL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxSUNKEN_BORDER);
    list_ctrl_2->SetMinSize(wxSize(120,120));

    wxBoxSizer* sizer_53 = new wxBoxSizer(wxHORIZONTAL);
    sizer_53->Add(list_ctrl_2, 1, wxEXPAND, 0);
    SetSizer(sizer_53);
    sizer_53->Fit(this);
    Layout();
    return result;
}
void PolygonTypeDialog::OnSel(wxListEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PolygonTypeDialog::OnSel) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
