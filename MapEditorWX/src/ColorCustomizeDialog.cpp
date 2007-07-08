#include "ColorCustomizeDialog.h"
#include "MapEditorWX.h"
enum{
    ID_BACKGROUND,
    ID_GRID,
    ID_LINES,
    ID_POLYGONS,
    ID_STRINGS,
    ID_POINTS,
    ID_SAME_HEIGHT_LINES,
    ID_STAIR_LINES,
};
BEGIN_EVENT_TABLE(ColorCustomizeDialog, wxDialog)
    EVT_BUTTON(ID_BACKGROUND, ColorCustomizeDialog::OnBackground)
    EVT_BUTTON(ID_GRID, ColorCustomizeDialog::OnGrid)
    EVT_BUTTON(ID_LINES, ColorCustomizeDialog::OnLines)
    EVT_BUTTON(ID_POLYGONS, ColorCustomizeDialog::OnPolygons)
    EVT_BUTTON(ID_STRINGS, ColorCustomizeDialog::OnStrings)
    EVT_BUTTON(ID_POINTS, ColorCustomizeDialog::OnPoints)
    EVT_BUTTON(ID_SAME_HEIGHT_LINES, ColorCustomizeDialog::OnSameHeightLines)
    EVT_BUTTON(ID_STAIR_LINES, ColorCustomizeDialog::OnStairLines)
    EVT_BUTTON(wxID_OK, ColorCustomizeDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, ColorCustomizeDialog::OnCancel)
//    EVT_PAINT(ColorCustomizeDialog::OnPaint)
END_EVENT_TABLE()

ColorCustomizeDialog::ColorCustomizeDialog()
{
}
ColorCustomizeDialog::~ColorCustomizeDialog()
{
}
bool ColorCustomizeDialog::Create(wxWindow* parent, wxWindowID id, ColorSettings & color)
{
    bool result = wxDialog::Create(parent, id, wxT("Color Customize"));
    label_13 = new wxStaticText(this, wxID_ANY, wxT("Background"));
    button_7 = new wxButton(this, ID_BACKGROUND, wxT("Choose color"));
    panel_1 = new wxPanel(this, wxID_ANY);
    label_14 = new wxStaticText(this, wxID_ANY, wxT("Grid line"));
    button_8 = new wxButton(this, ID_GRID, wxT("Choose color"));
    panel_2 = new wxPanel(this, wxID_ANY);
    label_16 = new wxStaticText(this, wxID_ANY, wxT("Lines"));
    button_9 = new wxButton(this, ID_LINES, wxT("Choose color"));
    panel_3 = new wxPanel(this, wxID_ANY);
    label_15 = new wxStaticText(this, wxID_ANY, wxT("Polygons"));
    button_10 = new wxButton(this, ID_POLYGONS, wxT("Choose color"));
    panel_4 = new wxPanel(this, wxID_ANY);
    label_17 = new wxStaticText(this, wxID_ANY, wxT("Strings"));
    button_11 = new wxButton(this, ID_STRINGS, wxT("Choose color"));
    panel_5 = new wxPanel(this, wxID_ANY);
    label_18 = new wxStaticText(this, wxID_ANY, wxT("Points"));
    button_12 = new wxButton(this, ID_POINTS, wxT("Choose color"));
    panel_6 = new wxPanel(this, wxID_ANY);
    label_a = new wxStaticText(this, wxID_ANY, wxT("Same Height Lines"));
    button_a = new wxButton(this, ID_SAME_HEIGHT_LINES, wxT("Choose color"));
    panel_a = new wxPanel(this, wxID_ANY);
    label_b = new wxStaticText(this, wxID_ANY, wxT("Stair Lines"));
    button_b = new wxButton(this, ID_STAIR_LINES, wxT("Choose color"));
    panel_b = new wxPanel(this, wxID_ANY);
    button_5 = new wxButton(this, wxID_OK, wxT("OK"));
    button_6 = new wxButton(this, wxID_CANCEL, wxT("Cancel"));

    //setup

    //layout
    wxFlexGridSizer* sizer_37 = new wxFlexGridSizer(9, 1, 0, 0);
    wxBoxSizer* sizer_44 = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer* sizer_43 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_42 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_41 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_40 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_39 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_38 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_a = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_b = new wxGridSizer(1, 3, 0, 0);
    sizer_38->Add(label_13, 0, 0, 0);
    sizer_38->Add(button_7, 0, 0, 0);
    sizer_38->Add(panel_1, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_38, 1, wxEXPAND, 0);
    sizer_39->Add(label_14, 0, 0, 0);
    sizer_39->Add(button_8, 0, 0, 0);
    sizer_39->Add(panel_2, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_39, 1, wxEXPAND, 0);
    sizer_40->Add(label_16, 0, 0, 0);
    sizer_40->Add(button_9, 0, 0, 0);
    sizer_40->Add(panel_3, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_40, 1, wxEXPAND, 0);
    sizer_41->Add(label_15, 0, 0, 0);
    sizer_41->Add(button_10, 0, 0, 0);
    sizer_41->Add(panel_4, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_41, 1, wxEXPAND, 0);
    sizer_42->Add(label_17, 0, 0, 0);
    sizer_42->Add(button_11, 0, 0, 0);
    sizer_42->Add(panel_5, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_42, 1, wxEXPAND, 0);
    sizer_43->Add(label_18, 0, 0, 0);
    sizer_43->Add(button_12, 0, 0, 0);
    sizer_43->Add(panel_6, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_43, 1, wxEXPAND, 0);

    sizer_a->Add(label_a, 0, 0, 0);
    sizer_a->Add(button_a, 0, 0, 0);
    sizer_a->Add(panel_a, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_a, 1, wxEXPAND, 0);
    sizer_b->Add(label_b, 0, 0, 0);
    sizer_b->Add(button_b, 0, 0, 0);
    sizer_b->Add(panel_b, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_b, 1, wxEXPAND, 0);

    sizer_44->Add(button_5, 0, 0, 0);
    sizer_44->Add(button_6, 0, 0, 0);
    sizer_37->Add(sizer_44, 1, wxEXPAND, 0);
    SetSizer(sizer_37);
    sizer_37->Fit(this);
    Layout();

    memcpy(&this->colorSetting, &color, sizeof(ColorSettings));

    //FÝ’è
    this->setPanelColors();
    return result;
}
wxColor ColorCustomizeDialog::getColorFromSetting(int type)
{
    int col[COL_NUM];

    for(int tag = 0; tag < ColorType::NUMBER_OF_COLOR_TYPES; tag ++){
        if(type == tag){
            for(int i = 0; i < COL_NUM; i ++){
                col[i] = this->colorSetting.colors[type][i];
            }
            break;
        }
    }
    wxColor color(col[0], col[1], col[2]);
    return color;
}

void ColorCustomizeDialog::setPanelColors()
{
    panel_1->SetBackgroundColour(getColorFromSetting(ColorType::Background));
    panel_2->SetBackgroundColour(getColorFromSetting(ColorType::GridLine));
    panel_3->SetBackgroundColour(getColorFromSetting(ColorType::Lines));
    panel_4->SetBackgroundColour(getColorFromSetting(ColorType::Polygons));
    panel_5->SetBackgroundColour(getColorFromSetting(ColorType::Strings));
    panel_6->SetBackgroundColour(getColorFromSetting(ColorType::Points));
    Refresh();
}
void ColorCustomizeDialog::OnOk(wxCommandEvent& ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void ColorCustomizeDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}
void ColorCustomizeDialog::setColor(int cols[]){
    wxColor defCol(cols[0], cols[1], cols[2]);
    wxColor col = wxGetColourFromUser(this, defCol);
    cols[0] = col.Red();
    cols[1] = col.Green();
    cols[2] = col.Blue();
    this->colorSetting.type = COL_CUSTOM;
    this->setPanelColors();
}

void ColorCustomizeDialog::OnBackground(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::Background]);
}


void ColorCustomizeDialog::OnGrid(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::GridLine]);
}


void ColorCustomizeDialog::OnLines(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::Lines]);
}


void ColorCustomizeDialog::OnPolygons(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::Polygons]);
}


void ColorCustomizeDialog::OnStrings(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::Strings]);
}


void ColorCustomizeDialog::OnPoints(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::Points]);
}
void ColorCustomizeDialog::OnSameHeightLines(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::SameHeightLines]);
}
void ColorCustomizeDialog::OnStairLines(wxCommandEvent &event)
{
    setColor(colorSetting.colors[ColorType::StairLines]);
}

void ColorCustomizeDialog::OnPaint(wxPaintEvent &event)
{
}
/**
    @param type MapEditorOneSetting.h‚ð‚Ý‚æ‚¤
*/
void ColorCustomizeDialog::drawPanel(wxPanel* panel, int type)
{

}
ColorSettings ColorCustomizeDialog::getColor()
{
    ColorSettings color;
    memcpy(&color, &this->colorSetting, sizeof(ColorSettings));
    return color;
}
