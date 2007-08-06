#include "PlacementDialog.h"
#include "MapEditorWX.h"

static wxRegEx REG_NUM = _T("[0-9]*");

//元に戻したいときの記憶
static struct object_frequency_definition placementStored[2*MAXIMUM_OBJECT_TYPES];

const int LABEL_COLUMN_WIDTH = 200;

// maximum random occurences of the object (from map.h
//(-32766,32765] -1 = 65535 to infinity
const int16 RANDOM_COUNT_INF = -1;
const uint16 RANDOM_CHANCE_INF = 32765;

namespace PlacementType{
	enum{
		Initial,
		Minimum,
		Maximum,
		RandomCount,
		RandomChance,
		RandomPlace,

		MAX_PLACEMENT_TYPE
	};
};

enum{
    ID_INITIAL,
    ID_MINIMUM,
    ID_MAXIMUM,
    ID_RANDOM_COUNT,
    ID_RANDOM_CHANCE,
    ID_INF,
    ID_ALL_INF,
    ID_SET_INITIAL,
    ID_SEL,
	ID_RANDOM_PLACE,
};

BEGIN_EVENT_TABLE(PlacementDialog, wxDialog)
    EVT_TEXT(ID_INITIAL, PlacementDialog::OnEditInitial)
    EVT_TEXT(ID_MINIMUM, PlacementDialog::OnEditMinimum)
    EVT_TEXT(ID_MAXIMUM, PlacementDialog::OnEditMaximum)
    EVT_TEXT(ID_RANDOM_COUNT, PlacementDialog::OnEditRandomCount)
    EVT_TEXT(ID_RANDOM_CHANCE, PlacementDialog::OnRandomChance)
    EVT_BUTTON(ID_INF, PlacementDialog::OnInf)
    EVT_BUTTON(ID_ALL_INF, PlacementDialog::OnAllInf)
    EVT_BUTTON(ID_SET_INITIAL, PlacementDialog::OnSetInitial)
    EVT_BUTTON(wxID_OK, PlacementDialog::OnOk)
    EVT_LIST_ITEM_SELECTED(ID_SEL, PlacementDialog::OnSel)
	EVT_CHECKBOX(ID_RANDOM_PLACE, PlacementDialog::OnRandomPlace)
END_EVENT_TABLE()

static wxString getIntegerString(int num)
{
	wxString str;
	if(num == 0){
		str = wxString(_T(" "));
	}else{
		str = getString("%d", num);
	}
	return str;
}

static int getType(int sel)
{
	int type = (sel >= NUMBER_OF_DEFINED_ITEMS) ? _saved_monster: _saved_item;
	return type;
}
static int getIndex(int sel)
{
	int index = (sel >= NUMBER_OF_DEFINED_ITEMS) ? (sel - NUMBER_OF_DEFINED_ITEMS) :(sel ) ;
	return index;
}

PlacementDialog::PlacementDialog():wxDialog()
{
}

PlacementDialog::~PlacementDialog()
{
}

const int COLUMN_NUM = 7;

static void addListItem(wxListCtrl* lstctrl, object_frequency_definition* placement, wxString type,
                        int id)
{
    assert(placement);
    wxString str[COLUMN_NUM];
    str[0] = type;
	str[1] = getIntegerString(placement->initial_count);
    str[2] = getIntegerString(placement->minimum_count);
    str[3] = getIntegerString(placement->maximum_count);
    str[4] = getIntegerString(placement->random_count);
    str[5] = getIntegerString(placement->random_chance);
    str[6] = getIntegerString(placement->flags);

    for(int j = 0; j < COLUMN_NUM; j ++){
        wxListItem item;
        item.SetId(id);
        item.SetColumn(j);
        item.SetText(str[j]);
        if(j == 0){
            lstctrl->InsertItem(item);
        }else{
            lstctrl->SetItem(item);
        }
    }
}
static void setListItem(wxListCtrl* lstctrl, object_frequency_definition* placement, int id)
{
    assert(placement);
    wxString str[COLUMN_NUM];
    str[0] = _T("");
	str[1] = getIntegerString(placement->initial_count);
    str[2] = getIntegerString(placement->minimum_count);
    str[3] = getIntegerString(placement->maximum_count);
    str[4] = getIntegerString(placement->random_count);
    str[5] = getIntegerString(placement->random_chance);
    str[6] = getIntegerString(placement->flags);

    for(int j = 1; j < COLUMN_NUM; j ++){
        wxListItem item;
        item.SetId(id);
        item.SetColumn(j);
        item.SetText(str[j]);
        lstctrl->SetItem(item);
    }
}
bool PlacementDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Placement"),
		wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER | wxDEFAULT_DIALOG_STYLE);
    if(!result){
        return result;
    }
    label_21 = new wxStaticText(this, wxID_ANY, wxT("Initial"));
    text_ctrl_8 = new wxTextCtrl(this, ID_INITIAL, wxEmptyString);
    label_22 = new wxStaticText(this, wxID_ANY, wxT("Minimum"));
    text_ctrl_9 = new wxTextCtrl(this, ID_MINIMUM, wxEmptyString);
    label_23 = new wxStaticText(this, wxID_ANY, wxT("Maximum"));
    text_ctrl_10 = new wxTextCtrl(this, ID_MAXIMUM, wxEmptyString);
    label_24 = new wxStaticText(this, wxID_ANY, wxT("Random count"));
    text_ctrl_11 = new wxTextCtrl(this, ID_RANDOM_COUNT, wxEmptyString);
    label_25 = new wxStaticText(this, wxID_ANY, wxT("Random chance"));
    text_ctrl_12 = new wxTextCtrl(this, ID_RANDOM_CHANCE, wxEmptyString);
    button_17 = new wxButton(this, ID_INF, wxT("Supply this infinitly"));
    button_18 = new wxButton(this, ID_ALL_INF, wxT("We cannot exterminate all monsters"));
    button_19 = new wxButton(this, ID_SET_INITIAL, wxT("Set the number of monster to initial"));

	//TODO いつの状態を保存するか？
	//ダイアログを開いたときの状態?
	button_19->Disable();

    checkbox_39 = new wxCheckBox(this, ID_RANDOM_PLACE, wxT("place at random location"));
    list_ctrl_1 = new wxListCtrl(this, ID_SEL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxSUNKEN_BORDER);
    button_16 = new wxButton(this, wxID_OK, wxT("OK"));

    list_ctrl_1->SetMinSize(wxSize(600, 300));

    wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(3, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_2 = new wxFlexGridSizer(1, 3, 0, 0);
    wxFlexGridSizer* grid_sizer_4 = new wxFlexGridSizer(4, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_3 = new wxFlexGridSizer(5, 2, 0, 0);
    grid_sizer_3->Add(label_21, 0, 0, 0);
    grid_sizer_3->Add(text_ctrl_8, 0, 0, 0);
    grid_sizer_3->Add(label_22, 0, 0, 0);
    grid_sizer_3->Add(text_ctrl_9, 0, 0, 0);
    grid_sizer_3->Add(label_23, 0, 0, 0);
    grid_sizer_3->Add(text_ctrl_10, 0, 0, 0);
    grid_sizer_3->Add(label_24, 0, 0, 0);
    grid_sizer_3->Add(text_ctrl_11, 0, 0, 0);
    grid_sizer_3->Add(label_25, 0, 0, 0);
    grid_sizer_3->Add(text_ctrl_12, 0, 0, 0);
    grid_sizer_2->Add(grid_sizer_3, 1, wxEXPAND, 0);
    grid_sizer_4->Add(button_17, 0, 0, 0);
    grid_sizer_4->Add(button_18, 0, 0, 0);
    grid_sizer_4->Add(button_19, 0, 0, 0);
    grid_sizer_4->Add(checkbox_39, 0, 0, 0);
    grid_sizer_2->Add(grid_sizer_4, 1, wxEXPAND, 0);
    grid_sizer_1->Add(grid_sizer_2, 1, wxEXPAND, 0);
    grid_sizer_1->Add(list_ctrl_1, 1, wxEXPAND, 0);
    grid_sizer_1->Add(button_16, 0, wxALIGN_RIGHT, 0);
    SetSizer(grid_sizer_1);
    grid_sizer_1->Fit(this);
    Layout();

    //データ設定
    char columnNames[][100] = {
        "Type", "Initial", "Min", "Max", 
        "Rnd Count", "Rnd Chance", "Flags"
    };
    for(int i = 0; i < COLUMN_NUM; i ++){
		int width = -1;

		if(i == 0){
			width = LABEL_COLUMN_WIDTH;
		}else{
		}
        list_ctrl_1->InsertColumn(i, wxConvertMB2WX(columnNames[i]), width);
    }

    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
        object_frequency_definition* placement = hpl::aleph::map::getPlacementData(_saved_item, i);
        addListItem(this->list_ctrl_1, placement, 
            wxConvertMB2WX(wxGetApp().itemTypeInfo[i].jname.c_str()), i);
    }
    for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
        object_frequency_definition* placement = hpl::aleph::map::getPlacementData(_saved_monster, i);
        addListItem(this->list_ctrl_1, placement, 
            wxConvertMB2WX(wxGetApp().monsterTypeInfo[i].jname.c_str()),
            i + NUMBER_OF_DEFINED_ITEMS);
    }

	//最初の状態を記憶しておく
	for(int i = 0; i < 2*MAXIMUM_OBJECT_TYPES; i ++){
		placementStored[i] = object_placement_info[i];
	}

    return result;
}

//OKボタン押した時
void PlacementDialog::OnOk(wxCommandEvent& ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}

static void setInfinity(int type, int index)
{
	object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);
	wxASSERT(placement);
	placement->random_count = RANDOM_COUNT_INF;
	placement->random_chance = RANDOM_CHANCE_INF;
}

void PlacementDialog::OnInf(wxCommandEvent &ev)
{
	//この項目を
	//random_count=-1
	//random_chance=65535
	//に設定します。
	//ただし、初期配置数も全体の数に関係してくる。
	int listIndex = this->listSelectIndex;
	int type = getType(listIndex);
	int index = getIndex(listIndex);
	object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);
	if(!placement){
		hpl::error::caution("You must select item / monster first");
		return;
	}
	setInfinity(type, index);
	setListItem(this->list_ctrl_1, placement, listIndex);
}
void PlacementDialog::OnAllInf(wxCommandEvent &ev)
{
    //全ての要素についてOnInf設定を行います
	for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MONSTER_TYPES; i ++){
		int type = getType(i);
		int index = getType(i);
		object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);
		wxASSERT(placement);
		setInfinity(type, index);
		setListItem(this->list_ctrl_1, placement, i);
	}
}
void PlacementDialog::OnSetInitial(wxCommandEvent &ev)
{
    //起動時に取得した情報を流し込む
	//最初の状態を記憶しておく
	for(int i = 0; i < 2*MAXIMUM_OBJECT_TYPES; i ++){
		object_placement_info[i] = placementStored[i];
	}
	//更新
	for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
		int type = _saved_item;
		int index = i;
		object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);
		setListItem(this->list_ctrl_1, placement, i);
	}
	for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
		int type = _saved_monster;
		int index = i;
		object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);
		setListItem(this->list_ctrl_1, placement, i + NUMBER_OF_DEFINED_ITEMS);
	}
}

void PlacementDialog::OnEditInitial(wxCommandEvent &event)
{
	this->setItem(PlacementType::Initial, event.GetString());
}


void PlacementDialog::setItem(int placementType, wxString str)
{
	int listIndex = this->listSelectIndex;
	int type = getType(listIndex);
	int index = getIndex(listIndex);
	object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);
	if(!placement){
		hpl::error::caution("You must select item / monster first");
		return;
	}
	if(REG_NUM.Matches(str)){
		int val = atoi(str.mb_str());
#ifdef __WXDEBUG__
		wxASSERT(placementType >= 0 && placementType < PlacementType::MAX_PLACEMENT_TYPE);
#endif
		switch(placementType){
		case PlacementType::Initial:
			placement->initial_count = val;
			break;
		case PlacementType::Minimum:
			placement->minimum_count = val;
			break;
		case PlacementType::Maximum:
			placement->maximum_count = val;
			break;
		case PlacementType::RandomCount:
			placement->random_count = val;
			break;
		case PlacementType::RandomChance:
			placement->random_chance = val;
			break;
		case PlacementType::RandomPlace:
			placement->flags = val;
			break;
		}
		setListItem(this->list_ctrl_1, placement, listIndex);
	}else{
		hpl::error::caution("Invalid argument. only number you can set");
	}
}
void PlacementDialog::OnEditMinimum(wxCommandEvent &event)
{
	this->setItem(PlacementType::Minimum, event.GetString());
}


void PlacementDialog::OnEditMaximum(wxCommandEvent &event)
{
	this->setItem(PlacementType::Maximum, event.GetString());
}


void PlacementDialog::OnEditRandomCount(wxCommandEvent &event)
{
	this->setItem(PlacementType::RandomCount, event.GetString());
}


void PlacementDialog::OnRandomChance(wxCommandEvent &event)
{
	this->setItem(PlacementType::RandomChance, event.GetString());
}
void PlacementDialog::OnSel(wxListEvent &ev)
{
    int sel = ev.GetIndex();
	if(sel >= 0 && list_ctrl_1->GetSelectedItemCount() == 1){
		listSelectIndex = sel;
		int type = getType(sel);//(sel >= NUMBER_OF_DEFINED_ITEMS) ? _saved_monster: _saved_item;
		int index = getIndex(sel);//(type == _saved_item) ? (sel ) : (sel - NUMBER_OF_DEFINED_ITEMS);
		object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);

		this->text_ctrl_8->SetValue(getString("%d", placement->initial_count));
		this->text_ctrl_9->SetValue(getString("%d", placement->minimum_count));
		this->text_ctrl_10->SetValue(getString("%d", placement->maximum_count));
		this->text_ctrl_11->SetValue(getString("%d", placement->random_count));
		this->text_ctrl_12->SetValue(getString("%d", placement->random_chance));
		checkbox_39->SetValue(placement->flags != 0);
		Refresh();
	}
}
void PlacementDialog::OnRandomPlace(wxCommandEvent& ev)
{
	bool value = ev.IsChecked();
	this->setItem(PlacementType::RandomChance, getString("%d", value ? _reappears_in_random_location : 0));
/*	int listIndex = this->listSelectIndex;
	int type = getType(listIndex);
	int index = getIndex(listIndex);
	object_frequency_definition* placement = hpl::aleph::map::getPlacementData(type, index);
	if(placement){
		placement->flags = value ? _reappears_in_random_location : 0;
		setListItem(this->list_ctrl_1, placement, listIndex);
	}else{
		hpl::error::caution("You must select item / monster first");
	}*/
}
