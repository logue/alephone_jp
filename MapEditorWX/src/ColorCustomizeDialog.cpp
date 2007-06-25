#include "ColorCustomizeDialog.h"
#include "MapEditorWX.h"
enum{
    ID_BACKGROUND,
    ID_GRID,
    ID_LINES,
    ID_POLYGONS,
    ID_STRINGS,
    ID_POINTS,
};
BEGIN_EVENT_TABLE(ColorCustomizeDialog, wxDialog)
    EVT_BUTTON(ID_BACKGROUND, ColorCustomizeDialog::OnBackground)
    EVT_BUTTON(ID_GRID, ColorCustomizeDialog::OnGrid)
    EVT_BUTTON(ID_LINES, ColorCustomizeDialog::OnLines)
    EVT_BUTTON(ID_POLYGONS, ColorCustomizeDialog::OnPolygons)
    EVT_BUTTON(ID_STRINGS, ColorCustomizeDialog::OnStrings)
    EVT_BUTTON(ID_POINTS, ColorCustomizeDialog::OnPoints)
    EVT_BUTTON(wxID_OK, ColorCustomizeDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, ColorCustomizeDialog::OnCancel)
    EVT_PAINT(ColorCustomizeDialog::OnPaint)
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
    button_7 = new wxButton(this, wxID_ANY, wxT("Choose color"));
    panel_1 = new wxPanel(this, wxID_ANY);
    label_14 = new wxStaticText(this, wxID_ANY, wxT("Grid line"));
    button_8 = new wxButton(this, wxID_ANY, wxT("Choose color"));
    panel_2 = new wxPanel(this, wxID_ANY);
    label_16 = new wxStaticText(this, wxID_ANY, wxT("Lines"));
    button_9 = new wxButton(this, wxID_ANY, wxT("Choose color"));
    panel_3 = new wxPanel(this, wxID_ANY);
    label_15 = new wxStaticText(this, wxID_ANY, wxT("Polygons"));
    button_10 = new wxButton(this, wxID_ANY, wxT("Choose color"));
    panel_4 = new wxPanel(this, wxID_ANY);
    label_17 = new wxStaticText(this, wxID_ANY, wxT("Strings"));
    button_11 = new wxButton(this, wxID_ANY, wxT("Choose color"));
    panel_5 = new wxPanel(this, wxID_ANY);
    label_18 = new wxStaticText(this, wxID_ANY, wxT("Points"));
    button_12 = new wxButton(this, wxID_ANY, wxT("Choose color"));
    panel_6 = new wxPanel(this, wxID_ANY);
    button_5 = new wxButton(this, wxID_ANY, wxT("OK"));
    button_6 = new wxButton(this, wxID_ANY, wxT("Cancel"));

    //setup

    //layout
    wxFlexGridSizer* sizer_37 = new wxFlexGridSizer(7, 1, 0, 0);
    wxBoxSizer* sizer_44 = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer* sizer_43 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_42 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_41 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_40 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_39 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* sizer_38 = new wxGridSizer(1, 3, 0, 0);
    sizer_38->Add(label_13, 0, 0, 0);
    sizer_38->Add(button_7, 0, 0, 0);
    sizer_38->Add(panel_1, 1, wxEXPAND, 0);
    sizer_37->Add(sizer_38, 1, wxEXPAND, 0);
    sizer_39->Add(label_14, 0, 0, 0);
    sizer_39->Add(button_8, 0, 0, 0);
    sizer_39->Add(panel_2, 1, 0, 0);
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
    sizer_44->Add(button_5, 0, 0, 0);
    sizer_44->Add(button_6, 0, 0, 0);
    sizer_37->Add(sizer_44, 1, wxEXPAND, 0);
    SetSizer(sizer_37);
    sizer_37->Fit(this);
    Layout();

    memcpy(&this->colorSetting, &color, sizeof(ColorSettings));

    return result;
}
void ColorCustomizeDialog::OnOk(wxCommandEvent& ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void ColorCustomizeDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void ColorCustomizeDialog::OnBackground(wxCommandEvent &event)
{
    //TODO カラー選択ダイアログを出す
    event.Skip();
    std::cout<<"Event handler (ColorCustomizeDialog::OnBackground) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ColorCustomizeDialog::OnGrid(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ColorCustomizeDialog::OnGrid) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ColorCustomizeDialog::OnLines(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ColorCustomizeDialog::OnLines) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ColorCustomizeDialog::OnPolygons(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ColorCustomizeDialog::OnPolygons) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ColorCustomizeDialog::OnStrings(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ColorCustomizeDialog::OnStrings) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ColorCustomizeDialog::OnPoints(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ColorCustomizeDialog::OnPoints) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}

void ColorCustomizeDialog::OnPaint(wxPaintEvent &event)
{
    //設定した色で塗る
    this->drawPanel(this->panel_1, ColorType::Background);
    this->drawPanel(this->panel_2, ColorType::GridLine);
    this->drawPanel(this->panel_3, ColorType::Lines);
    this->drawPanel(this->panel_4, ColorType::Polygons);
    this->drawPanel(this->panel_5, ColorType::Strings);
    this->drawPanel(this->panel_6, ColorType::Points);
}
/**
    @param type MapEditorOneSetting.hをみよう
*/
void ColorCustomizeDialog::drawPanel(wxPanel* panel, int type)
{
    wxPaintDC dc(panel);
    wxRect rect = panel->GetClientRect();
    int col[COL_NUM];

    switch(type){
    case ColorType::Background:
        for(int i = 0; i < COL_NUM; i ++){
            col[i] = this->colorSetting.background[0];
        }
        break;
    case ColorType::GridLine:
        for(int i = 0; i < COL_NUM; i ++){
            col[i] = this->colorSetting.gridLine[0];
        }
        break;
    case ColorType::Lines:
        for(int i = 0; i < COL_NUM; i ++){
            col[i] = this->colorSetting.lines[0];
        }
        break;
    case ColorType::Polygons:
        for(int i = 0; i < COL_NUM; i ++){
            col[i] = this->colorSetting.polygons[0];
        }
        break;
    case ColorType::Strings:
        for(int i = 0; i < COL_NUM; i ++){
            col[i] = this->colorSetting.strings[0];
        }
        break;
    case ColorType::Points:
        for(int i = 0; i < COL_NUM; i ++){
            col[i] = this->colorSetting.points[0];
        }
        break;
    default:
        break;
    }
    dc.SetBrush(wxBrush(wxColor(col[0], col[1], col[2])));
    dc.DrawRectangle(rect);
}
ColorSettings ColorCustomizeDialog::getColor()
{
    ColorSettings color;
    memcpy(&color, &this->colorSetting, sizeof(ColorSettings));
    return color;
}
