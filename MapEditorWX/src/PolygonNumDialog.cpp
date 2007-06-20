#include "PolygonNumDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(PolygonNumDialog, wxDialog)
    EVT_BUTTON(wxID_ANY, PolygonNumDialog::OnPoly3)
    EVT_BUTTON(wxID_ANY, PolygonNumDialog::OnPoly4)
    EVT_BUTTON(wxID_ANY, PolygonNumDialog::OnPoly5)
    EVT_BUTTON(wxID_ANY, PolygonNumDialog::OnPoly6)
    EVT_BUTTON(wxID_ANY, PolygonNumDialog::OnPoly7)
    EVT_BUTTON(wxID_ANY, PolygonNumDialog::OnPoly8)
END_EVENT_TABLE()
PolygonNumDialog::PolygonNumDialog()
{
}
PolygonNumDialog::~PolygonNumDialog()
{
}
bool PolygonNumDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Polygon Num"));
    wxBitmap bmp;
    bmp.LoadFile(_T("data/img/poly3.bmp"));
    bitmap_button_1 = new wxBitmapButton(this, wxID_ANY, bmp);
    bmp.LoadFile(_T("data/img/poly4.bmp"));
    bitmap_button_2 = new wxBitmapButton(this, wxID_ANY, bmp);
    bmp.LoadFile(_T("data/img/poly5.bmp"));
    bitmap_button_3 = new wxBitmapButton(this, wxID_ANY, bmp);
    bmp.LoadFile(_T("data/img/poly6.bmp"));
    bitmap_button_4 = new wxBitmapButton(this, wxID_ANY, bmp);
    bmp.LoadFile(_T("data/img/poly7.bmp"));
    bitmap_button_5 = new wxBitmapButton(this, wxID_ANY, bmp);
    bmp.LoadFile(_T("data/img/poly8.bmp"));
    bitmap_button_6 = new wxBitmapButton(this, wxID_ANY, bmp);

    //
    bitmap_button_1->SetSize(bitmap_button_1->GetBestSize());
    bitmap_button_2->SetSize(bitmap_button_2->GetBestSize());
    bitmap_button_3->SetSize(bitmap_button_3->GetBestSize());
    bitmap_button_4->SetSize(bitmap_button_4->GetBestSize());
    bitmap_button_5->SetSize(bitmap_button_5->GetBestSize());
    bitmap_button_6->SetSize(bitmap_button_6->GetBestSize());

    wxFlexGridSizer* grid_sizer_14 = new wxFlexGridSizer(1, 6, 0, 0);
    grid_sizer_14->Add(bitmap_button_1, 0, 0, 0);
    grid_sizer_14->Add(bitmap_button_2, 0, 0, 0);
    grid_sizer_14->Add(bitmap_button_3, 0, 0, 0);
    grid_sizer_14->Add(bitmap_button_4, 0, 0, 0);
    grid_sizer_14->Add(bitmap_button_5, 0, 0, 0);
    grid_sizer_14->Add(bitmap_button_6, 0, 0, 0);
    SetSizer(grid_sizer_14);
    grid_sizer_14->Fit(this);
    Layout();

    return result;
}
void PolygonNumDialog::OnPoly3(wxCommandEvent &event)
{
    SetReturnCode(3);
    Destroy();
}


void PolygonNumDialog::OnPoly4(wxCommandEvent &event)
{
    SetReturnCode(4);
    Destroy();
}


void PolygonNumDialog::OnPoly5(wxCommandEvent &event)
{
    SetReturnCode(5);
    Destroy();
}


void PolygonNumDialog::OnPoly6(wxCommandEvent &event)
{
    SetReturnCode(6);
    Destroy();
}


void PolygonNumDialog::OnPoly7(wxCommandEvent &event)
{
    SetReturnCode(7);
    Destroy();
}


void PolygonNumDialog::OnPoly8(wxCommandEvent &event)
{
    SetReturnCode(8);
    Destroy();
}
