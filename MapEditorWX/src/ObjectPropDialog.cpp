#include "ObjectPropDialog.h"
#include "MapEditorWX.h"
static char* DIR_CIRCLE_IMG_PATH = "./data/Toolbar/ObjectProperties/direction circle.BMP";
static char* DIR_MARKER_IMG_PATH = "./data/Toolbar/ObjectProperties/direction marker.BMP";
//facingデータの一周
const double FACING_ROUND = 512;
const double DEGREE_ROUND = 360;
//半径
const double DIRECTION_MARKER_RADIUS = 20;

enum{
    ID_TYPE,
    ID_INDEX,
    ID_HIDDEN,
    ID_CEILING,
    ID_SEE,
    ID_HEAR,
    ID_AERIAL,
    ID_NET,
    ID_LAUNCH,
    ID_X,
    ID_Y,
    ID_Z,
};

BEGIN_EVENT_TABLE(ObjectPropDialog, wxDialog)
    EVT_CHOICE(ID_TYPE, ObjectPropDialog::OnTypeChoice)
    EVT_CHOICE(ID_INDEX, ObjectPropDialog::OnIndexChoice)
    EVT_CHECKBOX(ID_HIDDEN, ObjectPropDialog::OnHiddenCheck)
    EVT_CHECKBOX(ID_CEILING, ObjectPropDialog::OnCeilingCheck)
    EVT_CHECKBOX(ID_SEE, ObjectPropDialog::OnSeeCheck)
    EVT_CHECKBOX(ID_HEAR, ObjectPropDialog::OnHearCheck)
    EVT_CHECKBOX(ID_AERIAL, ObjectPropDialog::OnAerialCheck)
    EVT_CHECKBOX(ID_NET, ObjectPropDialog::OnNetCheck)
    EVT_CHOICE(ID_LAUNCH, ObjectPropDialog::OnLaunchChoice)
    EVT_TEXT(ID_X, ObjectPropDialog::OnXEdit)
    EVT_TEXT(ID_Y, ObjectPropDialog::OnYEdit)
    EVT_TEXT(ID_Z, ObjectPropDialog::OnZEdit)
    EVT_PAINT(ObjectPropDialog::OnPaint)
END_EVENT_TABLE()
ObjectPropDialog::ObjectPropDialog()
{
}
ObjectPropDialog::~ObjectPropDialog()
{
}
bool ObjectPropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Edit Object"));
    label_45 = new wxStaticText(this, wxID_ANY, wxT("Group"));
    text_ctrl_27 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    choice_21 = new wxChoice(this, wxID_ANY);
    label_56 = new wxStaticText(this, wxID_ANY, wxT("Type"));
    text_ctrl_32 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    choice_22 = new wxChoice(this, wxID_ANY);
    checkbox_46 = new wxCheckBox(this, wxID_ANY, wxT("Teleports In"));
    checkbox_47 = new wxCheckBox(this, wxID_ANY, wxT("From Ceiling"));
    checkbox_48 = new wxCheckBox(this, wxID_ANY, wxT("Is Blind"));
    checkbox_49 = new wxCheckBox(this, wxID_ANY, wxT("Is Deaf"));
    checkbox_50 = new wxCheckBox(this, wxID_ANY, wxT("Teleports Out"));
    checkbox_51 = new wxCheckBox(this, wxID_ANY, wxT("Network Only"));
    label_59 = new wxStaticText(this, wxID_ANY, wxT("Polygon ID"));
    text_ctrl_37 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_58 = new wxStaticText(this, wxID_ANY, wxT("Facing"));
    text_ctrl_38 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    panel_16 = new wxPanel(this, wxID_ANY);
    label_60 = new wxStaticText(this, wxID_ANY, wxT("Launch by"));
    choice_23 = new wxChoice(this, wxID_ANY);
    panel_17 = new wxPanel(this, wxID_ANY);
    label_61 = new wxStaticText(this, wxID_ANY, wxT("Location x"));
    text_ctrl_39 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_63 = new wxStaticText(this, wxID_ANY, wxT("y"));
    text_ctrl_41 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_62 = new wxStaticText(this, wxID_ANY, wxT("            z"));
    text_ctrl_40 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    panel_18 = new wxPanel(this, wxID_ANY);

    text_ctrl_27->SetMinSize(wxSize(25, -1));
    text_ctrl_32->SetMinSize(wxSize(25, -1));
    panel_16->SetMinSize(wxSize(120, 120));
    choice_21->SetMinSize(wxSize(130, 22));
    choice_22->SetMinSize(wxSize(130, 22));
    choice_23->SetMinSize(wxSize(90, 22));
    text_ctrl_39->SetMinSize(wxSize(50, -1));
    text_ctrl_41->SetMinSize(wxSize(50, -1));
    text_ctrl_40->SetMinSize(wxSize(50, -1));

    wxFlexGridSizer* grid_sizer_15 = new wxFlexGridSizer(4, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_20 = new wxFlexGridSizer(3, 3, 0, 0);
    wxFlexGridSizer* grid_sizer_24 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_18 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_19 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_21 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_23 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_22 = new wxFlexGridSizer(6, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_16 = new wxFlexGridSizer(2, 3, 0, 0);
    grid_sizer_16->Add(label_45, 0, 0, 0);
    grid_sizer_16->Add(text_ctrl_27, 0, 0, 0);
    grid_sizer_16->Add(choice_21, 0, 0, 0);
    grid_sizer_16->Add(label_56, 0, 0, 0);
    grid_sizer_16->Add(text_ctrl_32, 0, 0, 0);
    grid_sizer_16->Add(choice_22, 0, 0, 0);
    grid_sizer_15->Add(grid_sizer_16, 1, wxEXPAND, 0);
    grid_sizer_22->Add(checkbox_46, 0, 0, 0);
    grid_sizer_22->Add(checkbox_47, 0, 0, 0);
    grid_sizer_22->Add(checkbox_48, 0, 0, 0);
    grid_sizer_22->Add(checkbox_49, 0, 0, 0);
    grid_sizer_22->Add(checkbox_50, 0, 0, 0);
    grid_sizer_22->Add(checkbox_51, 0, 0, 0);
    grid_sizer_21->Add(grid_sizer_22, 1, wxEXPAND, 0);
    grid_sizer_23->Add(label_59, 0, 0, 0);
    grid_sizer_23->Add(text_ctrl_37, 0, 0, 0);
    grid_sizer_21->Add(grid_sizer_23, 1, wxEXPAND, 0);
    grid_sizer_15->Add(grid_sizer_21, 1, wxEXPAND, 0);
    grid_sizer_19->Add(label_58, 0, 0, 0);
    grid_sizer_19->Add(text_ctrl_38, 0, 0, 0);
    grid_sizer_18->Add(grid_sizer_19, 1, wxEXPAND, 0);
    grid_sizer_18->Add(panel_16, 1, wxEXPAND, 0);
    grid_sizer_15->Add(grid_sizer_18, 1, wxEXPAND, 0);
    grid_sizer_20->Add(label_60, 0, 0, 0);
    grid_sizer_20->Add(choice_23, 0, 0, 0);
    grid_sizer_20->Add(panel_17, 1, wxEXPAND, 0);
    grid_sizer_20->Add(label_61, 0, 0, 0);
    grid_sizer_20->Add(text_ctrl_39, 0, 0, 0);
    grid_sizer_24->Add(label_63, 0, 0, 0);
    grid_sizer_24->Add(text_ctrl_41, 0, 0, 0);
    grid_sizer_20->Add(grid_sizer_24, 1, wxEXPAND, 0);
    grid_sizer_20->Add(label_62, 0, 0, 0);
    grid_sizer_20->Add(text_ctrl_40, 0, 0, 0);
    grid_sizer_20->Add(panel_18, 1, wxEXPAND, 0);
    grid_sizer_15->Add(grid_sizer_20, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_15);
    grid_sizer_15->Fit(this);
    Layout();

    //type
    for(int i = 0; i < NUMBER_OF_MAP_OBJECT_TYPES; i ++){
        this->choice_21->Insert(wxConvertMB2WX(
            wxGetApp().objectTypeInfo[i].jname.c_str()),
            i);
    }

    this->objIndex = NONE;

    //イメージファイル読み込み
    wxGetApp().loadImage(DIR_CIRCLE_IMG_PATH, &this->directionCircle, 255,255,255);
    wxGetApp().loadImage(DIR_MARKER_IMG_PATH, &this->directionMarker, 255,255,255);
    
    return result;
}
void ObjectPropDialog::setObjIndex(int index)
{
    this->objIndex = index;
    setupDialog();
}
int ObjectPropDialog::getObjIndex()
{
    return this->objIndex;
}
void ObjectPropDialog::setObject(map_object obj){
    int oldSel = choice_21->GetSelection();
    this->text_ctrl_27->SetValue(getString("%d", obj.type));
    this->choice_21->SetSelection(obj.type);

    this->text_ctrl_32->SetValue(getString("%d", obj.index));
    if(oldSel != obj.type){
        this->choice_22->Clear();
        switch(obj.type){
        case _saved_monster:
            for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
                this->choice_22->Insert(wxConvertMB2WX(
                    wxGetApp().monsterTypeInfo[i].jname.c_str()),
                    i);
            }
            break;
        case _saved_player:
            this->choice_22->Insert(_T("Uh-huh?"), 0);
            break;
        case _saved_item:
            for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
                this->choice_22->Insert(wxConvertMB2WX(
                    wxGetApp().itemTypeInfo[i].jname.c_str()),
                    i);
            }
            break;
        case _saved_goal:
            this->choice_22->Insert(_T("Anything go here"),0 );
            break;
        case _saved_object:
            for(int i = 0; i < NUMBER_OF_SCENERY_DEFINITIONS; i ++){
                this->choice_22->Insert(wxConvertMB2WX(
                    wxGetApp().sceneryTypeInfo[i].jname.c_str()),
                    i);
            }
            break;
        case _saved_sound_source:
            for(int i = 0; i < NUMBER_OF_AMBIENT_SOUND_DEFINITIONS; i ++){
                this->choice_22->Insert(wxConvertMB2WX(
                    wxGetApp().soundSourceTypeInfo[i].jname.c_str()),
                    i);
            }
            break;
        }
    }
    this->choice_22->SetSelection(obj.index);

    //flags
    this->checkbox_46->SetValue((obj.flags & _map_object_is_invisible) != 0);
    this->checkbox_47->SetValue((obj.flags & _map_object_hanging_from_ceiling) != 0);
    this->checkbox_48->SetValue((obj.flags & _map_object_is_blind) != 0);
    this->checkbox_49->SetValue((obj.flags & _map_object_is_deaf) != 0);
    this->checkbox_50->SetValue((obj.flags & _map_object_floats) != 0);
    this->checkbox_51->SetValue((obj.flags & _map_object_is_network_only) != 0);

    this->text_ctrl_37->SetValue(getString("%d", obj.polygon_index));

    this->text_ctrl_38->SetValue(getString("%d", obj.facing));

    this->text_ctrl_39->SetValue(getString("%d", obj.location.x));
    this->text_ctrl_41->SetValue(getString("%d", obj.location.y));
    this->text_ctrl_40->SetValue(getString("%d", obj.location.z));
 
    Refresh();
}
void ObjectPropDialog::setupDialog()
{
    if(this->objIndex == NONE){
        map_object obj;
        memset(&obj, 0, sizeof(map_object));
        this->setObject(obj);
    }else{
#ifdef __WXDEBUG__
        wxASSERT(this->objIndex >= 0 && this->objIndex < (int)SavedObjectList.size());
#endif
        map_object* obj = &SavedObjectList[this->objIndex];
        this->setObject(*obj);
    }
}
static bool isValidIndex(int *index)
{
    if(*index == NONE){
        return false;
    }
    if(*index < 0 || *index >= (int)SavedObjectList.size()){
        hpl::error::caution("target object not found.");
        *index = NONE;
        return false;
    }
    return true;
}

void ObjectPropDialog::OnTypeChoice(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
    obj->type = event.GetSelection();

}


void ObjectPropDialog::OnIndexChoice(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
    obj->index = event.GetSelection();
}


void ObjectPropDialog::OnHiddenCheck(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}


void ObjectPropDialog::OnCeilingCheck(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}


void ObjectPropDialog::OnSeeCheck(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}


void ObjectPropDialog::OnHearCheck(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}


void ObjectPropDialog::OnAerialCheck(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}


void ObjectPropDialog::OnNetCheck(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
    
}


void ObjectPropDialog::OnLaunchChoice(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
    //TODO launch?
}


void ObjectPropDialog::OnXEdit(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}


void ObjectPropDialog::OnYEdit(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}


void ObjectPropDialog::OnZEdit(wxCommandEvent &event)
{
    if(!isValidIndex(&this->objIndex))return;
    map_object* obj = &SavedObjectList[this->objIndex];
}
map_object ObjectPropDialog::getObject()
{
    map_object obj;
    memset(&obj, 0, sizeof(map_object));

    obj.type = choice_21->GetSelection();
    obj.index = choice_22->GetSelection();

    obj.flags = 0;
    if(checkbox_46->GetValue()) obj.flags |= _map_object_is_invisible;
    if(checkbox_47->GetValue()) obj.flags |= _map_object_hanging_from_ceiling;
    if(checkbox_48->GetValue()) obj.flags |= _map_object_is_blind;
    if(checkbox_49->GetValue()) obj.flags |= _map_object_is_deaf;
    if(checkbox_50->GetValue()) obj.flags |= _map_object_floats;
    if(checkbox_51->GetValue()) obj.flags |= _map_object_is_network_only;

    //obj.polygon_index = text_ctr

    obj.facing = atoi(wxConvertWX2MB(text_ctrl_38->GetValue()));
    obj.location.x = atoi(wxConvertWX2MB(text_ctrl_39->GetValue()));
    obj.location.x = atoi(wxConvertWX2MB(text_ctrl_40->GetValue()));
    obj.location.x = atoi(wxConvertWX2MB(text_ctrl_41->GetValue()));
    return obj;
}
void ObjectPropDialog::drawFacing(wxWindow* panel, int facing, wxDC* dc)
{
    //degreeに変換
    double degree = DEGREE_ROUND * (double)facing / FACING_ROUND;
    //radianに変換
    double rad = hpl::math::getRadianFromDegree(degree);
    //中心位置
    int centerX = this->directionCircle.GetWidth() / 2;
    int centerY = this->directionCircle.GetHeight() / 2;
    int x = centerX + DIRECTION_MARKER_RADIUS * cos(rad);
    int y = centerY + DIRECTION_MARKER_RADIUS * sin(rad);
    int markerW = this->directionMarker.GetWidth();
    int markerH = this->directionMarker.GetHeight();
    
    //wxWindowDC dc(panel);
    //circle
    wxBitmap circleBmp(this->directionCircle);
    dc->DrawBitmap(circleBmp, 0,0);

    //marker
    wxBitmap markerBmp(this->directionMarker);
    dc->DrawBitmap(markerBmp, x - markerW / 2, y - markerH / 2);
}

void ObjectPropDialog::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);
    wxPaintDC dcw(panel_16);
    //wxDialog::OnPaint();
    if(this->getObjIndex() != NONE){
        map_object* obj = &SavedObjectList[this->objIndex];
        drawFacing(panel_16, obj->facing, &dcw);
    }else{
        drawFacing(panel_16, 0, &dcw);
    }
}
