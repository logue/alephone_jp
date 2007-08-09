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
    list_ctrl_3 = new wxListCtrl(this, ID_EDIT, wxDefaultPosition, wxDefaultSize,
		wxLC_REPORT|wxLC_EDIT_LABELS|wxSUNKEN_BORDER | wxLC_SINGLE_SEL);

    list_ctrl_3->SetMinSize(wxSize(180, 200));

    wxFlexGridSizer* grid_sizer_28 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_29 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_29->Add(button_24, 0, 0, 0);
    grid_sizer_29->Add(button_25, 0, 0, 0);
    grid_sizer_28->Add(grid_sizer_29, 1, wxEXPAND, 0);
    grid_sizer_28->Add(list_ctrl_3, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_28);
    grid_sizer_28->Fit(this);
    Layout();
	//setup columns
	char *columnNames[100] = {"Index", "Color"};
	const int COLUMN_NUM = 2;
    for(int i = 0; i < COLUMN_NUM; i ++){
        list_ctrl_3->InsertColumn(i, wxConvertMB2WX(columnNames[i]));
    }
    return result;
}
void HeightPaletteDialog::OnAdd(wxCommandEvent &event)
{
	wxString str = ::wxGetTextFromUser(_T(""), _T("Input height"), _T("0"));
	if(str != wxEmptyString){
		wxListItem item;
		//高さを追加
		item.SetText(str);
		item.SetId(list_ctrl_3->GetItemCount());
		item.SetColumn(0);
		item.SetBackgroundColour(wxGetApp().getColorFromHeight(atoi(str.mb_str())));
		list_ctrl_3->InsertItem(item);
		item.SetColumn(1);
		item.SetText(_T("hoge"));
		list_ctrl_3->SetItem(item);
	}
}


void HeightPaletteDialog::OnDelete(wxCommandEvent &event)
{
	int sel = event.GetSelection();
	//TODO
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
wxColor HeightPaletteDialog::getColorFromHeight(double height){
    wxColor col = wxGetApp().getColorFromHeight(height);
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
	//TODO すでに追加しておいた分はどうするのか？
	//標準以外の高さ情報はどうするのか？
	int numMax = (int)PolygonList.size();
	wxString *strings = new wxString[numMax];
	wxColor *colors = new wxColor[numMax];

    for(int i = 0; i < (int)PolygonList.size(); i ++){
        polygon_data* poly = get_polygon_data(i);
		int height = poly->ceiling_height;
		if(this->isFloor()){
			height = poly->floor_height;
		}
        strings[i] = getString("%d", height);
		colors[i] = wxGetApp().getColorFromHeight(height);
    }
	wxGetApp().setupPaletteListControl(numMax, 
		list_ctrl_3, strings, colors);
	delete [] strings;
	delete [] colors;
}
/**
    床なのか天井なのか
    <en>Floor or Ceiling
*/
void HeightPaletteDialog::setFloor(bool floor)
{
    this->isFloor_ = floor;
	//TODO
	std::set<int> heightStock;
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		polygon_data* poly = get_polygon_data(i);
		int height = poly->ceiling_height;
		if(this->isFloor()){
			height = poly->floor_height;
		}
		if(heightStock.find(height) == heightStock.end()){
			//new height stock
			heightStock.insert(height);
		}
	}
	int max = (int)heightStock.size();
	wxString* strings = new wxString[max];
	wxColor* colors = new wxColor[max];
	int counter = 0;
	for(std::set<int>::iterator it = heightStock.begin(); it != heightStock.end(); it ++){
		int val = (*it);
		strings[counter] = getString("%d", val);
		colors[counter] = wxGetApp().getColorFromHeight(val);
		counter ++;
	}
	wxGetApp().setupPaletteListControl(max, list_ctrl_3,
		strings, colors);
	delete [] colors;
	delete [] strings;
}
bool HeightPaletteDialog::isFloor(){
    return this->isFloor_;
}
/**
	指定した高さに該当するアイテムを選択状態にします
*/
void HeightPaletteDialog::setSelection(int height)
{
	int index = NONE;
	int max = list_ctrl_3->GetItemCount();
	for(int i = 0; i < max; i ++){
		wxListItem item;
		item.SetId(i);
		item.SetColumn(1);
		wxASSERT(list_ctrl_3->GetItem(item));
		//
		wxString heightStr = list_ctrl_3->GetItemText(i);
		const char* str = list_ctrl_3->GetItemText(i).mb_str();//heightStr.mb_str();
		if(atoi(str) == height){
			list_ctrl_3->SetItemState(i, wxLIST_STATE_SELECTED, 0);
			return;
		}
	}
	wxASSERT(false);
}
