#include "PolygonPropDialog.h"
#include "PlatformDialog.h"

static char* CREATE_BUTTON_LABEL = "Create platform";
static char* DELETE_BUTTON_LABEL = "Delete platform";

#include "MapEditorWX.h"
namespace PolyProp{
enum{
	/*
    ID_ID,
    ID_FirstNeighbor,
	*/
    ID_Type,
	/*
    ID_NearCount,
    ID_Perm,
    ID_CenterX,
    ID_FloorLight,
    ID_CenterY,
    ID_CeilingLight,
    ID_Area,
    ID_FloorOriginX,
    ID_FloorOriginY,
    ID_CeilingOriginX,
    ID_CeilingOriginY,
    ID_FirstObj,
    ID_Media,
    ID_FirstExZone,
    ID_MediaLight,
    ID_LineExZone,
    ID_SndSrcIndex,
    ID_FloorTrans,
    ID_AmbSnd,
    ID_CeilingTrans,
    ID_RndSnd,
	*/
    ID_Platform,
	/*
	ID_FloorHeight,
	ID_CeilingHeight,
	*/
	ID_CreatePlatform,
};
};
BEGIN_EVENT_TABLE(PolygonPropDialog, wxDialog)
    EVT_CHOICE(PolyProp::ID_Type, PolygonPropDialog::OnTypeChoice)
    EVT_BUTTON(PolyProp::ID_Platform, PolygonPropDialog::OnPlatformBtn)
    EVT_BUTTON(PolyProp::ID_CreatePlatform, PolygonPropDialog::OnCreatePlatformBtn)
    EVT_BUTTON(wxID_OK, PolygonPropDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, PolygonPropDialog::OnCancel)
END_EVENT_TABLE()
PolygonPropDialog::PolygonPropDialog()
{
}
PolygonPropDialog::~PolygonPropDialog()
{
}
bool PolygonPropDialog::Create(wxWindow* parent, wxWindowID id,
							   int polygonIndex)
{
    bool result = wxDialog::Create(parent, id, _T("Polygon Properties"));
    label_34 = new wxStaticText(this, wxID_ANY, wxT("Polygon ID"));
    text_ctrl_20 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_46 = new wxStaticText(this, wxID_ANY, wxT("First neighbour"));
    text_ctrl_21 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_35 = new wxStaticText(this, wxID_ANY, wxT("Type"));
    choice_12 = new wxChoice(this, PolyProp::ID_Type);
    label_47 = new wxStaticText(this, wxID_ANY, wxT("Near count"));
    text_ctrl_22 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_36 = new wxStaticText(this, wxID_ANY, wxT("Permutation"));
    text_ctrl_25 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_48 = new wxStaticText(this, wxID_ANY, wxT("Center X"));
    text_ctrl_23 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_37 = new wxStaticText(this, wxID_ANY, wxT("Floor light"));
    choice_13 = new wxChoice(this, wxID_ANY);
    label_49 = new wxStaticText(this, wxID_ANY, wxT("Center Y"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    text_ctrl_24 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_38 = new wxStaticText(this, wxID_ANY, wxT("Ceiling light"));
    choice_14 = new wxChoice(this, wxID_ANY);
    label_26 = new wxStaticText(this, wxID_ANY, wxT("Floor origin"));
    text_ctrl_33 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_27 = new wxStaticText(this, wxID_ANY, wxT("x"));
    text_ctrl_35 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_39 = new wxStaticText(this, wxID_ANY, wxT("Area"));
    text_ctrl_26 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_55 = new wxStaticText(this, wxID_ANY, wxT("Ceiling origin"));
    text_ctrl_34 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_28 = new wxStaticText(this, wxID_ANY, wxT("x"));
    text_ctrl_36 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_40 = new wxStaticText(this, wxID_ANY, wxT("First object"));
    //choice_19 = new wxChoice(this, PolyProp::ID_FirstObj);
	text_ctrl_firstObject = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_54 = new wxStaticText(this, wxID_ANY, wxT("Media"));
    choice_15 = new wxChoice(this, wxID_ANY);
    label_41 = new wxStaticText(this, wxID_ANY, wxT("First ex zone"));
    text_ctrl_28 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_53 = new wxStaticText(this, wxID_ANY, wxT("Media light"));
    choice_16 = new wxChoice(this, wxID_ANY);
    label_42 = new wxStaticText(this, wxID_ANY, wxT("Line ex zone"));
    text_ctrl_29 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_52 = new wxStaticText(this, wxID_ANY, wxT("Snd src index"));
    choice_20 = new wxChoice(this, wxID_ANY);
    label_43 = new wxStaticText(this, wxID_ANY, wxT("Floor trans"));
    text_ctrl_30 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_51 = new wxStaticText(this, wxID_ANY, wxT("Amb snd"));
    choice_17 = new wxChoice(this, wxID_ANY);
    label_44 = new wxStaticText(this, wxID_ANY, wxT("Ceiling trans"));
    text_ctrl_31 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_50 = new wxStaticText(this, wxID_ANY, wxT("Rnd snd"));
    choice_18 = new wxChoice(this, wxID_ANY);
    button_21 = new wxButton(this, PolyProp::ID_Platform, wxT("Platform settings"));
	//プラットフォームデータの作成
    //panel_10 = new wxPanel(this, wxID_ANY);
	button_createPlatform = new wxButton(this, PolyProp::ID_CreatePlatform, wxConvertMB2WX(CREATE_BUTTON_LABEL));
    panel_11 = new wxPanel(this, wxID_ANY);
    panel_12 = new wxPanel(this, wxID_ANY);
	textFloorHeight = new wxTextCtrl(this, wxID_ANY);
	textCeilingHeight = new wxTextCtrl(this, wxID_ANY);
	button_OK = new wxButton(this, wxID_OK);
	button_Cancel = new wxButton(this, wxID_CANCEL);

    choice_12->SetMinSize(wxSize(100, 22));
    choice_13->SetMinSize(wxSize(100, 22));
    choice_14->SetMinSize(wxSize(100, 22));
    text_ctrl_33->SetMinSize(wxSize(30, 20));
    text_ctrl_35->SetMinSize(wxSize(30, 20));
    text_ctrl_34->SetMinSize(wxSize(30, 20));
    text_ctrl_36->SetMinSize(wxSize(30, 20));
    //choice_19->SetMinSize(wxSize(100, 22));
	text_ctrl_firstObject->SetMinSize(wxSize(30, 20));
    choice_15->SetMinSize(wxSize(100, 22));
    choice_16->SetMinSize(wxSize(100, 22));
    choice_20->SetMinSize(wxSize(100, 22));
    choice_17->SetMinSize(wxSize(100, 22));
    choice_18->SetMinSize(wxSize(100, 22));

    wxFlexGridSizer* grid_sizer_13 = new wxFlexGridSizer(14, 4, 0, 0);
    wxGridSizer* grid_sizer_9 = new wxGridSizer(1, 3, 0, 0);
    wxGridSizer* grid_sizer_8 = new wxGridSizer(1, 3, 0, 0);
    grid_sizer_13->Add(label_34, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_20, 0, 0, 0);
    grid_sizer_13->Add(label_46, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_21, 0, 0, 0);
    grid_sizer_13->Add(label_35, 0, 0, 0);
    grid_sizer_13->Add(choice_12, 0, 0, 0);
    grid_sizer_13->Add(label_47, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_22, 0, 0, 0);
    grid_sizer_13->Add(label_36, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_25, 0, 0, 0);
    grid_sizer_13->Add(label_48, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_23, 0, 0, 0);
    grid_sizer_13->Add(label_37, 0, 0, 0);
    grid_sizer_13->Add(choice_13, 0, 0, 0);
    grid_sizer_13->Add(label_49, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_24, 0, 0, 0);
    grid_sizer_13->Add(label_38, 0, 0, 0);
    grid_sizer_13->Add(choice_14, 0, 0, 0);
    grid_sizer_13->Add(label_26, 0, 0, 0);
    grid_sizer_8->Add(text_ctrl_33, 0, 0, 0);
    grid_sizer_8->Add(label_27, 0, 0, 0);
    grid_sizer_8->Add(text_ctrl_35, 0, 0, 0);
    grid_sizer_13->Add(grid_sizer_8, 1, wxEXPAND, 0);
    grid_sizer_13->Add(label_39, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_26, 0, 0, 0);
    grid_sizer_13->Add(label_55, 0, 0, 0);
    grid_sizer_9->Add(text_ctrl_34, 0, 0, 0);
    grid_sizer_9->Add(label_28, 0, 0, 0);
    grid_sizer_9->Add(text_ctrl_36, 0, 0, 0);
    grid_sizer_13->Add(grid_sizer_9, 1, wxEXPAND, 0);
    grid_sizer_13->Add(label_40, 0, 0, 0);
    //grid_sizer_13->Add(choice_19, 0, 0, 0);
	grid_sizer_13->Add(text_ctrl_firstObject, 0, 0, 0);
    grid_sizer_13->Add(label_54, 0, 0, 0);
    grid_sizer_13->Add(choice_15, 0, 0, 0);
    grid_sizer_13->Add(label_41, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_28, 0, 0, 0);
    grid_sizer_13->Add(label_53, 0, 0, 0);
    grid_sizer_13->Add(choice_16, 0, 0, 0);
    grid_sizer_13->Add(label_42, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_29, 0, 0, 0);
    grid_sizer_13->Add(label_52, 0, 0, 0);
    grid_sizer_13->Add(choice_20, 0, 0, 0);
    grid_sizer_13->Add(label_43, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_30, 0, 0, 0);
    grid_sizer_13->Add(label_51, 0, 0, 0);
    grid_sizer_13->Add(choice_17, 0, 0, 0);
    grid_sizer_13->Add(label_44, 0, 0, 0);
    grid_sizer_13->Add(text_ctrl_31, 0, 0, 0);
    grid_sizer_13->Add(label_50, 0, 0, 0);
    grid_sizer_13->Add(choice_18, 0, 0, 0);

    grid_sizer_13->Add(new wxStaticText(this, wxID_ANY, wxT("Floor Height")), 0, 0, 0);
    grid_sizer_13->Add(textFloorHeight, 0, 0, 0);
    grid_sizer_13->Add(new wxPanel(this, wxID_ANY), 1, wxEXPAND, 0);
    grid_sizer_13->Add(new wxPanel(this, wxID_ANY), 1, wxEXPAND, 0);
    grid_sizer_13->Add(new wxStaticText(this, wxID_ANY, wxT("Ceiling Height")), 0, 0, 0);
    grid_sizer_13->Add(textCeilingHeight, 0, 0, 0);
    grid_sizer_13->Add(new wxPanel(this, wxID_ANY), 1, wxEXPAND, 0);
    grid_sizer_13->Add(new wxPanel(this, wxID_ANY), 1, wxEXPAND, 0);

	grid_sizer_13->Add(button_21, 0, 0, 0);
    //grid_sizer_13->Add(panel_10, 1, wxEXPAND, 0);
	grid_sizer_13->Add(button_createPlatform, 0,0,0);
    grid_sizer_13->Add(button_OK, 0, wxEXPAND, 0);
    grid_sizer_13->Add(button_Cancel, 0, wxEXPAND, 0);
    SetSizer(grid_sizer_13);
    grid_sizer_13->Fit(this);
    Layout();
    this->setPolyIndex(polygonIndex, wxGetApp().getStockManager());

    //Typeに追加
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        choice_12->Insert(wxConvertMB2WX(wxGetApp().polygonTypeInfo[i].jname.c_str()), i);
    }

    //TODO snd src
    //choice_20->Clear();
/*    for(int i = 0; i < (int).size(); i ++){
        choice_20->Insert(getString("%d", i), i);
    }
    choice_20->Insert(_T("NONE"), .size());*/
    //choice_17->Clear();
    for(int i = 0; i < (int)AmbientSoundImageList.size(); i ++){
        choice_17->Insert(getString("%d", i), i);
    }
    choice_17->Insert(_T("NONE"), (int)AmbientSoundImageList.size());
    //random sound
    //choice_18->Clear();
/*    for(int i = 0; i < (int).size(); i ++){
        choice_18->Insert(getString("%d", i), i);
    }
    choice_18->Insert(_T("NONE"), .size());*/

	//combo
	updateCombo();
	setupDialog(wxGetApp().getStockManager());
    return result;
}

void PolygonPropDialog::setPolyIndex(int index,
									 hpl::aleph::HPLStockManager* smgr)
{
    this->polyIndex = index;
//    setupDialog(smgr);
    //タイトル変更
    SetTitle(getString("Polygon prop [index:%d]", this->getPolyIndex()));
}
int PolygonPropDialog::getPolyIndex()
{
    return polyIndex;
}

/**
	コンボボックスの再構成
	時間がかかるので変化が起きた場合にのみ呼び出す
*/
void PolygonPropDialog::updateCombo()
{
    //CHOICEをセットアップしなおす
    //light floor/ceiling/media-light
    choice_13->Clear();
    choice_14->Clear();
    choice_16->Clear();
    for(int i = 0; i < (int)LightList.size(); i ++){
        choice_13->Insert(getString("%d", i), i);
        choice_14->Insert(getString("%d", i), i);
        choice_16->Insert(getString("%d", i), i);
    }
    choice_13->Insert(_T("NONE"), (int)LightList.size());
    choice_14->Insert(_T("NONE"), (int)LightList.size());
    choice_16->Insert(_T("NONE"), (int)LightList.size());

	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

    //first object
	/*
    choice_19->Clear();
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
		if(smgr->delObjects[i]){
		}else{
	        choice_19->Insert(getString("%d", i), i);
		}
    }
    choice_19->Insert(_T("NONE"), (int)LightList.size());
	*/

    //Media
    choice_15->Clear();
    for(int i = 0; i < (int)MediaList.size(); i ++){
        choice_15->Insert(getString("%d", i), i);
    }
    choice_15->Insert(_T("NONE"), (int)MediaList.size());
    
}

void PolygonPropDialog::setupDialog(hpl::aleph::HPLStockManager* smgr)
{


    //ポリゴン情報をダイアログに設定
    polygon_data* poly = get_polygon_data(this->getPolyIndex());
#ifdef __WXDEBUG__
	wxASSERT(poly);
#endif
    text_ctrl_20->SetValue(getString("%d", this->getPolyIndex()));
    choice_12->SetSelection(poly->type);
	//プラットフォームならボタンを有効にする
	setupPlatformButton(smgr);
    text_ctrl_25->SetValue(getString("%d", poly->permutation));
    choice_13->SetSelection(poly->floor_lightsource_index);
    choice_14->SetSelection(poly->ceiling_lightsource_index);
    text_ctrl_26->SetValue(getString("%d", poly->permutation));
    int index = poly->first_object;
/*    if(!hpl::aleph::map::isValidIndex(index, SavedObjectList.size())){
        index = (int)SavedObjectList.size();
    }*/
    
	//choice_19->SetSelection(index);
	text_ctrl_firstObject->SetValue(getString("%d", poly->first_object));
    text_ctrl_28->SetValue(getString("%d", poly->first_exclusion_zone_index));
    text_ctrl_29->SetValue(getString("%d", poly->line_exclusion_zone_count));
    text_ctrl_30->SetValue(getString("%d", poly->floor_transfer_mode));
    text_ctrl_31->SetValue(getString("%d", poly->ceiling_transfer_mode));

    text_ctrl_21->SetValue(getString("%d", poly->first_neighbor_index));
    text_ctrl_22->SetValue(getString("%d", poly->neighbor_count));
    text_ctrl_23->SetValue(getString("%d", poly->center.x));
    text_ctrl_24->SetValue(getString("%d", poly->center.y));
    text_ctrl_33->SetValue(getString("%d", poly->floor_origin.x));
    text_ctrl_35->SetValue(getString("%d", poly->floor_origin.y));
    text_ctrl_34->SetValue(getString("%d", poly->ceiling_origin.x));
    text_ctrl_36->SetValue(getString("%d", poly->ceiling_origin.y));
    index = poly->media_index;
    if(!hpl::aleph::map::isValidIndex(index, MediaList.size())){
        index = (int)MediaList.size();
    }
    choice_15->SetSelection(index);
    index = poly->media_lightsource_index;
    if(!hpl::aleph::map::isValidIndex(index, MediaList.size())){
        index = (int)LightList.size();
    }
    choice_16->SetSelection(index);
    /* TODO snd src
    index = poly->;
    if(index == NONE){
        index = .size();
    }
    choice_20->SetSelection(index);*/
    index = poly->ambient_sound_image_index;
    if(!hpl::aleph::map::isValidIndex(index, AmbientSoundImageList.size())){
        index = (int)AmbientSoundImageList.size();
    }
    choice_17->SetSelection(index);
/*
    TODO rnd snd
    index = poly->;
    if(index == NONE){
        index = .size();
    }
    choice_18->SetSelection(index);
    */
    textFloorHeight->SetValue(getString("%d", poly->floor_height));
    textCeilingHeight->SetValue(getString("%d", poly->ceiling_height));

	
}

void PolygonPropDialog::OnTypeChoice(wxCommandEvent &event)
{
	polygon_data* poly = get_polygon_data(this->getPolyIndex());
    if(poly == NULL)	return ;
	int sel = event.GetSelection();
	if(sel >= 0){
		poly->type = sel;
		if(sel == _polygon_is_platform){
			setupPlatformButton(wxGetApp().getStockManager());
		}else{
			disablePlatformButton();
		}
	}
}
void PolygonPropDialog::disablePlatformButton()
{
	//プラットフォームボタン
	button_21->Disable();
	//プラットフォーム作成ボタン
	button_createPlatform->SetLabel(wxConvertMB2WX(CREATE_BUTTON_LABEL));
	button_createPlatform->Disable();
}

void PolygonPropDialog::setupPlatformButton(hpl::aleph::HPLStockManager* smgr)
{
	polygon_data* poly = get_polygon_data(getPolyIndex());
	if(!poly){
		return;
	}
	if(poly->type == _polygon_is_platform){
		int platformIndex = hpl::aleph::map::getPlatformIndexFromPolygonIndex(
			this->getPolyIndex(), smgr);
		//プラットフォーム
		if(hpl::aleph::map::isValidIndex(platformIndex, PlatformList.size())){
			//かつプラットフォームが存在する
			this->readyForDeleting();
		}else{
			this->readyForCreating();
		}
	}else{
		//ポリゴンはプラットフォームではない
		button_21->Disable();
		button_createPlatform->SetLabel(wxConvertMB2WX(CREATE_BUTTON_LABEL));
		button_createPlatform->Disable();
	}
}

void PolygonPropDialog::OnPlatformBtn(wxCommandEvent &event)
{
    if(!hpl::aleph::map::isValidIndex(polyIndex, PolygonList.size())){
        return ;
    }
    PlatformDialog dlg;
    dlg.Create(this, wxID_ANY, polyIndex);
    if(dlg.ShowModal() == wxID_OK){
        //設定変更
		platform_data data = dlg.getPlatform();
		polygon_data* poly = get_polygon_data(polyIndex);
		hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
		int platformIndex = hpl::aleph::map::getPlatformIndexFromPolygonIndex(
			polyIndex, smgr);
		platform_data* org = &PlatformList[platformIndex];
		*org = data;
		//memcpy(org, &data, sizeof(platform_data));
    }
}
void PolygonPropDialog::OnCreatePlatformBtn(wxCommandEvent &event)
{
    if(!hpl::aleph::map::isValidIndex(this->getPolyIndex(), PolygonList.size())){
        return ;
    }
	polygon_data* poly = get_polygon_data(getPolyIndex());
#ifdef _WXDEBUG_
	wxASSERT(poly);
#endif
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
	if(isCreatePlatform){
		//TODO プラットフォームの作成
		//this->readyForDeleting();
	}else{
		//TODO プラットフォームの削除
		int platformIndex = hpl::aleph::map::getPlatformIndexFromPolygonIndex(
			getPolyIndex(), smgr);
		smgr->deletePlatform(platformIndex);
		this->readyForCreating();
	}
}
void PolygonPropDialog::readyForCreating()
{
	button_21->Disable();
	button_createPlatform->SetLabel(wxConvertMB2WX(CREATE_BUTTON_LABEL));
	button_createPlatform->Enable();
	isCreatePlatform = true;
}
void PolygonPropDialog::readyForDeleting()
{
	button_21->Enable();
	button_createPlatform->SetLabel(wxConvertMB2WX(DELETE_BUTTON_LABEL));
	button_createPlatform->Enable();
	isCreatePlatform = false;
}
/*
void PolygonPropDialog::OnFloorHeightEdit(wxCommandEvent &event)
{
	//TODO
}
void PolygonPropDialog::OnceilingHeightEdit(wxCommandEvent &event)
{
	//TODO
}
*/

/**
	Choiceの値を取得します。
	最大値を超えるものを選択した場合、
	それをNONEとして変換します
*/
static int getIndexWithNONE(wxChoice* choice,
							size_t max)
{
	int index = choice->GetSelection();
	if(index >= (int)max){
		index = NONE;
	}
	return index;
}

polygon_data PolygonPropDialog::getPolygon()
{
	polygon_data data;
	polygon_data* org = get_polygon_data(polyIndex);
	//memcpy(&data, org, sizeof(polygon_data));
	data = *org;

	//TODO 値をセット
	//編集できる項目のみ変更する
	data.type = choice_12->GetSelection();
	//id
	//permutation
	data.floor_lightsource_index = getIndexWithNONE(choice_13,
		LightList.size());
	data.ceiling_lightsource_index = getIndexWithNONE(choice_14,
		LightList.size());
	//area
	//first object
	//first ex zone
	//line ex zone
	//TODO floor trans
	//TODO ceiling trans
	data.floor_height = atoi(wxConvertWX2MB(textFloorHeight->GetValue()));
	data.ceiling_height = atoi(wxConvertWX2MB(textCeilingHeight->GetValue()));
	
	//first neighbour
	//near count
	//center x
	//center y
	//origins
	//media
	data.media_index = getIndexWithNONE(choice_15,
		MediaList.size());
	/*
	//TODO
	data.media_lightsource_index = getIndexWithNONE(choice_16,
		LightList.size());
	data.sound_source_indexes = getIndexWithNONE(choice_20,
		SoundList.size());
	data.ambient_sound_image_index = getIndexWithNONE(choice_17,
		SoundList.size());
	data.random_sound_image_index = getIndexWithNONE(choice_18,
		SoundList.size());
		*/

	return data;
}

void PolygonPropDialog::OnOk(wxCommandEvent &ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void PolygonPropDialog::OnCancel(wxCommandEvent &ev)
{
	SetReturnCode(wxID_CANCEL);
    Destroy();
}
