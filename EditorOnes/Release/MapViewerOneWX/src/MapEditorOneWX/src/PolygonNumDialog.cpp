#include "PolygonNumDialog.h"
#include "MapEditorWX.h"
enum{
    ID_Poly3,
    ID_Poly4,
    ID_Poly5,
    ID_Poly6,
    ID_Poly7,
    ID_Poly8,
};

BEGIN_EVENT_TABLE(PolygonNumDialog, wxDialog)
    EVT_BUTTON(ID_Poly3, PolygonNumDialog::OnPoly3)
    EVT_BUTTON(ID_Poly4, PolygonNumDialog::OnPoly4)
    EVT_BUTTON(ID_Poly5, PolygonNumDialog::OnPoly5)
    EVT_BUTTON(ID_Poly6, PolygonNumDialog::OnPoly6)
    EVT_BUTTON(ID_Poly7, PolygonNumDialog::OnPoly7)
    EVT_BUTTON(ID_Poly8, PolygonNumDialog::OnPoly8)
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
    bmp.LoadFile(_T("data/img/poly3.bmp"), wxBITMAP_TYPE_BMP);
    bitmap_button_1 = new wxBitmapButton(this, ID_Poly3, bmp);
    bmp.LoadFile(_T("data/img/poly4.bmp"), wxBITMAP_TYPE_BMP);
    bitmap_button_2 = new wxBitmapButton(this, ID_Poly4, bmp);
    bmp.LoadFile(_T("data/img/poly5.bmp"), wxBITMAP_TYPE_BMP);
    bitmap_button_3 = new wxBitmapButton(this, ID_Poly5, bmp);
    bmp.LoadFile(_T("data/img/poly6.bmp"), wxBITMAP_TYPE_BMP);
    bitmap_button_4 = new wxBitmapButton(this, ID_Poly6, bmp);
    bmp.LoadFile(_T("data/img/poly7.bmp"), wxBITMAP_TYPE_BMP);
    bitmap_button_5 = new wxBitmapButton(this, ID_Poly7, bmp);
    bmp.LoadFile(_T("data/img/poly8.bmp"), wxBITMAP_TYPE_BMP);
    bitmap_button_6 = new wxBitmapButton(this, ID_Poly8, bmp);

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
