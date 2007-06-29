#include "HeightPaletteDialog.h"
#include "MapEditorWX.h"
enum{
    ID_EDIT,
};

BEGIN_EVENT_TABLE(HeightPaletteDialog, wxDialog)
    EVT_BUTTON(wxID_ADD, HeightPaletteDialog::OnAdd)
    EVT_BUTTON(wxID_DELETE, HeightPaletteDialog::OnDelete)
    EVT_LIST_END_LABEL_EDIT(ID_EDIT, HeightPaletteDialog::OnEdit)
END_EVENT_TABLE()
HeightPaletteDialog::HeightPaletteDialog()
{
}
HeightPaletteDialog::~HeightPaletteDialog()
{
}
bool HeightPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height Pallet"));
    button_24 = new wxButton(this, wxID_ADD, wxEmptyString);
    button_25 = new wxButton(this, wxID_DELETE, wxEmptyString);
    list_ctrl_3 = new wxListCtrl(this, ID_EDIT, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_EDIT_LABELS|wxSUNKEN_BORDER);

    list_ctrl_3->SetMinSize(wxSize(154, 200));

    wxFlexGridSizer* grid_sizer_28 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_29 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_29->Add(button_24, 0, 0, 0);
    grid_sizer_29->Add(button_25, 0, 0, 0);
    grid_sizer_28->Add(grid_sizer_29, 1, wxEXPAND, 0);
    grid_sizer_28->Add(list_ctrl_3, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_28);
    grid_sizer_28->Fit(this);
    Layout();
    return result;
}
void HeightPaletteDialog::OnAdd(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (HeightPaletteDialog::OnAdd) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void HeightPaletteDialog::OnDelete(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (HeightPaletteDialog::OnDelete) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void HeightPaletteDialog::OnEdit(wxListEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (HeightPaletteDialog::OnEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}

/**
    高さから色を求めます
    @param heightPerOne 高さをWORLD_ONEで割ったもの
*/
wxColor HeightPaletteDialog::getColorFromHeight(double heightPerOne){
    wxColor col;
    double zMax = MAXIMUM_FLOOR_HEIGHT / WORLD_ONE;
    double zMin = MINIMUM_FLOOR_HEIGHT / WORLD_ONE;
    if(!this->isFloor()){
        //ceiling
        zMax = MAXIMUM_CEILING_HEIGHT / WORLD_ONE;
        zMin = MINIMUM_CEILING_HEIGHT / WORLD_ONE;
    }
    int r = heightPerOne / (zMax - zMin) * 255;
    col.Set(r, 0, 0);
    return col;
}
/**
    現在のマップの高さ情報を代入します
    今までのものは削除されます
*/
void HeightPaletteDialog::updateHeights()
{
    //初期化 <en> clear all items
    list_ctrl_3->ClearAll();
    //重複を除外するのでsetを用いる
    std::set<int> heights;
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        polygon_data* poly = get_polygon_data(i);
        heights.insert(poly->floor_height);
    }
    //listctrlに追加していく
    std::set<int>::iterator it = heights.begin();
    for(; it != heights.end(); it ++){
        wxListItem item;
        double num = (double)(*it) / WORLD_ONE;
        item.SetText(getString("%f", num));
        //色に変換する
        //TODO
        //list_ctrl_3->
    }
}
/**
    床なのか天井なのか
    <en>Floor or Ceiling
*/
void HeightPaletteDialog::setFloor(bool floor)
{
    this->isFloor_ = floor;
}
bool HeightPaletteDialog::isFloor(){
    return this->isFloor_;
}
