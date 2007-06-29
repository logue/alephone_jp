#include "TextureDialog.h"
#include "MapEditorWX.h"
enum{
    ID_TYPE,
};

BEGIN_EVENT_TABLE(TextureDialog, wxDialog)
    // begin wxGlade: TextureDialog::event_table
    EVT_CHOICE(wxID_ANY, TextureDialog::OnType)
    // end wxGlade
END_EVENT_TABLE()
TextureDialog::TextureDialog()
{
}
TextureDialog::~TextureDialog()
{
}
bool TextureDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Texture"));

    label_75 = new wxStaticText(this, wxID_ANY, wxT("type"));
    choice_30 = new wxChoice(this, wxID_ANY);
    panel_13 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER|wxTAB_TRAVERSAL);

    panel_13->SetMinSize(wxSize(480, 120));
    panel_13->SetScrollRate(10, 10);

    wxFlexGridSizer* grid_sizer_44 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_45 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_45->Add(label_75, 0, 0, 0);
    grid_sizer_45->Add(choice_30, 0, 0, 0);
    grid_sizer_44->Add(grid_sizer_45, 1, wxEXPAND, 0);
    grid_sizer_44->Add(panel_13, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_44);
    grid_sizer_44->Fit(this);
    Layout();

    //TODO Shapesファイルが読み込まれていない場合は警告を出して閉じる
    if(false){
        hpl::error::caution("Shapes file not loaded");
        Destroy();
    }
    return result;
}
void TextureDialog::OnType(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TextureDialog::OnType) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
void TextureDialog::setFloor(bool floor)
{
    this->isFloor_ = floor;
}
