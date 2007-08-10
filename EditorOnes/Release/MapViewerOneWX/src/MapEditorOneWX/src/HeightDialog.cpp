#include "HeightDialog.h"
#include "MapEditorWX.h"

const int BUF_MAX = 1024;
const int LINE_SIZE = 1;

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
    slider_2 = new wxSlider(this, ID_FLOOR_SLIDER, 0, 0, 10, wxDefaultPosition, wxDefaultSize,
        wxSL_VERTICAL | wxSL_INVERSE);
    slider_3 = new wxSlider(this, ID_CEILING_SLIDER, 0, 0, 10, wxDefaultPosition, wxDefaultSize,
        wxSL_VERTICAL | wxSL_INVERSE);
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

    //高さ初期化
    //floor
    int zMin = SHRT_MIN;
    int zMax = SHRT_MAX;
    this->text_ctrl_5->SetValue(getString("%d", zMin));
    //最大値・最小値
    this->slider_2->SetRange(zMin,zMax);
    this->slider_2->SetLineSize(LINE_SIZE);
    this->slider_2->SetPageSize(zMin / WORLD_ONE);
    this->slider_2->SetValue(zMin);

    this->text_ctrl_6->SetValue(getString("%d", zMax));
    this->slider_3->SetRange(zMin,zMax);
    this->slider_3->SetLineSize(LINE_SIZE);
    this->slider_3->SetPageSize(zMin / WORLD_ONE);
    this->slider_3->SetValue(zMax);

    return result;
}

void HeightDialog::OnEditFloor(wxCommandEvent& ev)
{
    int pos = atoi(ev.GetString().mb_str());
    wxGetApp().getViewGridManager()->setViewHeightMin(pos);
    //スライダーの位置を変更する
    this->slider_2->SetValue(pos);
    this->GetParent()->Refresh();
}
void HeightDialog::OnEditCeiling(wxCommandEvent& ev)
{
    int pos = atoi(ev.GetString().mb_str());
    wxGetApp().getViewGridManager()->setViewHeightMax(pos);
    //スライダーの位置を変更する
    this->slider_3->SetValue(pos);
    this->GetParent()->Refresh();
}
void HeightDialog::OnSliderFloor(wxCommandEvent& ev)
{
    int pos = slider_2->GetValue();
    wxGetApp().getViewGridManager()->setViewHeightMin(pos);
    //
    this->text_ctrl_5->SetValue(getString("%d", pos));
    this->GetParent()->Refresh();
}
void HeightDialog::OnSliderCeiling(wxCommandEvent& ev)
{
    int pos = slider_3->GetValue();
    wxGetApp().getViewGridManager()->setViewHeightMax(pos);
    //テキストボックスの値を変更する
    this->text_ctrl_6->SetValue(getString("%d", pos));
    this->GetParent()->Refresh();
}
void HeightDialog::OnDrawCheck(wxCommandEvent& ev)
{
    //シングルトンさんのisDrawHiddenLinesを操作する
    wxGetApp().isRevealHiddenLines = ev.IsChecked();
    this->GetParent()->Refresh();
}
