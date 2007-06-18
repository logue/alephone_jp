#include "HeightDialog.h"
#include "MapEditorWX.h"

//ID
enum{
    ID_FLOOR_SLIDER,
    ID_CEILING_SLIDER,
    ID_DRAW_HIDDEN_CHECK,
    ID_FLOOR_EDIT,
    ID_CEILING_EDIT,
};

BEGIN_EVENT_TABLE(HeightDialog, wxDialog)
    EVT_TEXT(ID_FLOOR_EDIT, HeightDialog::OnEditFloor)
    EVT_TEXT(ID_CEILING_EDIT, HeightDialog::OnEditCeiling)
    EVT_SLIDER(ID_FLOOR_SLIDER, HeightDialog::OnSliderFloor)
    EVT_SLIDER(ID_CEILING_SLIDER, HeightDialog::OnSliderCeiling)
    EVT_CHECKBOX(ID_DRAW_HIDDEN_CHECK, HeightDialog::OnDrawCheck)
END_EVENT_TABLE()
HeightDialog::HeightDialog()
{
}
HeightDialog::~HeightDialog()
{
}
bool HeightDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height"));

    //create items
    label_9 = new wxStaticText(this, wxID_ANY, wxT("Floor"));
    text_ctrl_5 = new wxTextCtrl(this, ID_FLOOR_EDIT, wxEmptyString);
    slider_2 = new wxSlider(this, ID_FLOOR_SLIDER, 0, 0, 10, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL);
    slider_3 = new wxSlider(this, ID_CEILING_SLIDER, 0, 0, 10, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL);
    label_10 = new wxStaticText(this, wxID_ANY, wxT("Ceiling"));
    text_ctrl_6 = new wxTextCtrl(this, ID_CEILING_EDIT, wxEmptyString);
    checkbox_11 = new wxCheckBox(this, ID_DRAW_HIDDEN_CHECK, wxT("Draw hidden lines"));

    //set properties
    text_ctrl_5->SetMinSize(wxSize(50, -1));
    slider_2->SetMinSize(wxSize(-1, 200));
    slider_3->SetMinSize(wxSize(-1, 200));
    text_ctrl_6->SetMinSize(wxSize(50, -1));

    //do layout
    wxBoxSizer* sizer_22 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_23 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_25 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_24 = new wxBoxSizer(wxVERTICAL);
    sizer_24->Add(label_9, 0, 0, 0);
    sizer_24->Add(text_ctrl_5, 0, 0, 0);
    sizer_23->Add(sizer_24, 1, wxEXPAND, 0);
    sizer_23->Add(slider_2, 0, 0, 0);
    sizer_23->Add(slider_3, 0, 0, 0);
    sizer_25->Add(label_10, 0, 0, 0);
    sizer_25->Add(text_ctrl_6, 0, 0, 0);
    sizer_23->Add(sizer_25, 1, wxEXPAND, 0);
    sizer_22->Add(sizer_23, 1, wxEXPAND, 0);
    sizer_22->Add(checkbox_11, 0, 0, 0);
    SetSizer(sizer_22);
    sizer_22->Fit(this);
    Layout();

    return result;
}

void HeightDialog::OnEditFloor(wxCommandEvent& ev)
{
    //TODO
    //スライダーの位置を変更する
}
void HeightDialog::OnEditCeiling(wxCommandEvent& ev)
{
    //TODO
    //同上
}
void HeightDialog::OnSliderFloor(wxCommandEvent& ev)
{
    //TODO
    //テキストボックスの値を変更する
}
void HeightDialog::OnSliderCeiling(wxCommandEvent& ev)
{
    //TODO
    //同上
}
void HeightDialog::OnDrawCheck(wxCommandEvent& ev)
{
    //TODO
    //シングルトンさんのisDrawHiddenLinesを操作する
}
