#include "ObjectPropDialog.h"
#include "MapEditorWX.h"
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
END_EVENT_TABLE()
ObjectPropDialog::ObjectPropDialog()
{
}
ObjectPropDialog::~ObjectPropDialog()
{
}
bool ObjectPropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Object Properties"));
    label_45 = new wxStaticText(this, wxID_ANY, wxT("Object type"));
    text_ctrl_27 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    choice_21 = new wxChoice(this, wxID_ANY);
    label_56 = new wxStaticText(this, wxID_ANY, wxT("Object index"));
    text_ctrl_32 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    choice_22 = new wxChoice(this, wxID_ANY);
    checkbox_46 = new wxCheckBox(this, wxID_ANY, wxT("Hidden"));
    checkbox_47 = new wxCheckBox(this, wxID_ANY, wxT("Hung on ceiling"));
    checkbox_48 = new wxCheckBox(this, wxID_ANY, wxT("Can't seeing"));
    checkbox_49 = new wxCheckBox(this, wxID_ANY, wxT("Can't hearing"));
    checkbox_50 = new wxCheckBox(this, wxID_ANY, wxT("From aerial"));
    checkbox_51 = new wxCheckBox(this, wxID_ANY, wxT("Only network game"));
    label_59 = new wxStaticText(this, wxID_ANY, wxT("Polygon ID"));
    text_ctrl_37 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_58 = new wxStaticText(this, wxID_ANY, wxT("Facing/Direction"));
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

    text_ctrl_27->SetMinSize(wxSize(20, -1));
    text_ctrl_32->SetMinSize(wxSize(20, -1));
    panel_16->SetMinSize(wxSize(120, 120));
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
    grid_sizer_18->Add(panel_16, 1, 0, 0);
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

    this->objIndex = NONE;
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
void ObjectPropDialog::setupDialog()
{
}
void ObjectPropDialog::OnTypeChoice(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnTypeChoice) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnIndexChoice(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnIndexChoice) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnHiddenCheck(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnHiddenCheck) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnCeilingCheck(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnCeilingCheck) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnSeeCheck(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnSeeCheck) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnHearCheck(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnHearCheck) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnAerialCheck(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnAerialCheck) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnNetCheck(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnNetCheck) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnLaunchChoice(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnLaunchChoice) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnXEdit(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnXEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnYEdit(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnYEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void ObjectPropDialog::OnZEdit(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (ObjectPropDialog::OnZEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
