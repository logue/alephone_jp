#include "PhysicsPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_TYPE = 100,
};


BEGIN_EVENT_TABLE(PhysicsPanel, wxPanel)
	EVT_CHOICE(ID_TYPE, PhysicsPanel::OnType)
	EVT_TEXT( 0, PhysicsPanel::OnData00)
	EVT_TEXT( 1, PhysicsPanel::OnData01)
	EVT_TEXT( 2, PhysicsPanel::OnData02)
	EVT_TEXT( 3, PhysicsPanel::OnData03)
	EVT_TEXT( 4, PhysicsPanel::OnData04)

	EVT_TEXT( 5, PhysicsPanel::OnData05)
	EVT_TEXT( 6, PhysicsPanel::OnData06)
	EVT_TEXT( 7, PhysicsPanel::OnData07)
	EVT_TEXT( 8, PhysicsPanel::OnData08)
	EVT_TEXT( 9, PhysicsPanel::OnData09)

	EVT_TEXT(10, PhysicsPanel::OnData10)
	EVT_TEXT(11, PhysicsPanel::OnData11)
	EVT_TEXT(12, PhysicsPanel::OnData12)
	EVT_TEXT(13, PhysicsPanel::OnData13)
	EVT_TEXT(14, PhysicsPanel::OnData14)

	EVT_TEXT(15, PhysicsPanel::OnData15)
	EVT_TEXT(16, PhysicsPanel::OnData16)
	EVT_TEXT(17, PhysicsPanel::OnData17)
	EVT_TEXT(18, PhysicsPanel::OnData18)
	EVT_TEXT(19, PhysicsPanel::OnData19)

	EVT_TEXT(20, PhysicsPanel::OnData20)
	EVT_TEXT(21, PhysicsPanel::OnData21)
	EVT_TEXT(22, PhysicsPanel::OnData22)
	EVT_TEXT(23, PhysicsPanel::OnData23)
	EVT_TEXT(24, PhysicsPanel::OnData24)
	EVT_TEXT(25, PhysicsPanel::OnData25)
END_EVENT_TABLE()

PhysicsPanel::PhysicsPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//create
	this->typeChoice = new wxChoice(this, ID_TYPE);
	for(int i = 0; i < NUMBER_OF_PHYSICS_ITEMS; i ++){
		this->datas[i] = new wxTextCtrl(this, i);
	}

	//set
	for(int i = 0; i < NUMBER_OF_PHYSICS_MODELS; i ++){
		this->typeChoice->Insert(wxConvertMB2WX(
			wxGetApp().physicsInfo[i].jname.c_str()), i);
	}

	//layout
	wxFlexGridSizer* leftSizer = new wxFlexGridSizer(21,2,0,0);
	leftSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Type")));
	leftSizer->Add(this->typeChoice);
	char labels[][100] = {
		"Max Forward Velocity",
		"Max Backward Velocity",
		"Max Perpendicular Velocity",
		"Acceleration",
		"Deceleration",

		"Airborne Deceleration",
		"Gravity Accel",
		"Climb Accel",
		"Terminal Accel",
		"External Deceleration",

		"Angular Accel",
		"Angular Deceleration",
		"Max Angular Velocity",
		"Angular Recentering Velocity",
		"Fast Angular Velocity",

		"Fast Angular Maximum",
		"Max Elevation",
		"External Angular Deceleration",
		"Step Delta",
		"Step Amplitude",

		"Radius",
		"Height",
		"Dead Height",
		"Camera Height",
		"Splash Height",
		"Half Camera Separation",
	};
	for(int i = 0; i < 20; i ++){
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			wxConvertMB2WX(labels[i])));
		leftSizer->Add(this->datas[i]);
	}

	wxFlexGridSizer* rightSizer = new wxFlexGridSizer(6,2,0,0);
	for(int i = 20; i < NUMBER_OF_PHYSICS_ITEMS; i ++){
		rightSizer->Add(new wxStaticText(this, wxID_ANY,
			wxConvertMB2WX(labels[i])));
		rightSizer->Add(this->datas[i]);
	}

	wxFlexGridSizer* allSizer = new wxFlexGridSizer(1,2,0,0);
	allSizer->Add(leftSizer);
	allSizer->Add(rightSizer);
	this->SetSizer(allSizer);

	allSizer->Fit(this);
	Layout();
}

PhysicsPanel::~PhysicsPanel()
{
}

void PhysicsPanel::OnType(wxCommandEvent& ev)
{
	int index = ev.GetSelection();
	if(index >= 0 && index < NUMBER_OF_PHYSICS_MODELS){
		wxGetApp().setEditingPhysicsIndex(index);
		setup();
	}
	common();
}

void PhysicsPanel::OnData00(wxCommandEvent& ev)
{
	int type = common();
	*nums[0] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData01(wxCommandEvent& ev)
{
	int type = common();
	*nums[1] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData02(wxCommandEvent& ev)
{
	int type = common();
	*nums[2] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData03(wxCommandEvent& ev)
{
	int type = common();
	*nums[3] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData04(wxCommandEvent& ev)
{
	int type = common();
	*nums[4] = getNumberFromTextCtrl(&ev);
}

void PhysicsPanel::OnData05(wxCommandEvent& ev)
{
	int type = common();
	*nums[5] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData06(wxCommandEvent& ev)
{
	int type = common();
	*nums[6] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData07(wxCommandEvent& ev)
{
	int type = common();
	*nums[7] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData08(wxCommandEvent& ev)
{
	int type = common();
	*nums[8] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData09(wxCommandEvent& ev)
{
	int type = common();
	*nums[9] = getNumberFromTextCtrl(&ev);
}

void PhysicsPanel::OnData10(wxCommandEvent& ev)
{
	int type = common();
	*nums[10] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData11(wxCommandEvent& ev)
{
	int type = common();
	*nums[11] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData12(wxCommandEvent& ev)
{
	int type = common();
	*nums[12] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData13(wxCommandEvent& ev)
{
	int type = common();
	*nums[13] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData14(wxCommandEvent& ev)
{
	int type = common();
	*nums[14] = getNumberFromTextCtrl(&ev);
}

void PhysicsPanel::OnData15(wxCommandEvent& ev)
{
	int type = common();
	*nums[15] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData16(wxCommandEvent& ev)
{
	int type = common();
	*nums[16] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData17(wxCommandEvent& ev)
{
	int type = common();
	*nums[17] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData18(wxCommandEvent& ev)
{
	int type = common();
	*nums[18] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData19(wxCommandEvent& ev)
{
	int type = common();
	*nums[19] = getNumberFromTextCtrl(&ev);
}

void PhysicsPanel::OnData20(wxCommandEvent& ev)
{
	int type = common();
	*nums[20] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData21(wxCommandEvent& ev)
{
	int type = common();
	*nums[21] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData22(wxCommandEvent& ev)
{
	int type = common();
	*nums[22] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData23(wxCommandEvent& ev)
{
	int type = common();
	*nums[23] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData24(wxCommandEvent& ev)
{
	int type = common();
	*nums[24] = getNumberFromTextCtrl(&ev);
}
void PhysicsPanel::OnData25(wxCommandEvent& ev)
{
	int type = common();
	*nums[25] = getNumberFromTextCtrl(&ev);
}

void PhysicsPanel::setup()
{
	int type = wxGetApp().getEditingPhysicsIndex();

	nums[0] = &physics_models[type].maximum_forward_velocity;
	nums[1] = &physics_models[type].maximum_backward_velocity;
	nums[2] = &physics_models[type].maximum_perpendicular_velocity;
	nums[3] = &physics_models[type].acceleration;
	nums[4] = &physics_models[type].deceleration;

	nums[5] = &physics_models[type].airborne_deceleration;
	nums[6] = &physics_models[type].gravitational_acceleration;
	nums[7] = &physics_models[type].climbing_acceleration;
	nums[8] = &physics_models[type].terminal_velocity;
	nums[9] = &physics_models[type].external_deceleration;

	nums[10] = &physics_models[type].angular_acceleration;
	nums[11] = &physics_models[type].angular_deceleration;
	nums[12] = &physics_models[type].maximum_angular_velocity;
	nums[13] = &physics_models[type].angular_recentering_velocity;
	nums[14] = &physics_models[type].fast_angular_velocity;

	nums[15] = &physics_models[type].fast_angular_maximum;
	nums[16] = &physics_models[type].maximum_elevation;
	nums[17] = &physics_models[type].external_angular_deceleration;
	nums[18] = &physics_models[type].step_delta;
	nums[19] = &physics_models[type].step_amplitude;

	nums[20] = &physics_models[type].radius;
	nums[21] = &physics_models[type].height;
	nums[22] = &physics_models[type].dead_height;
	nums[23] = &physics_models[type].camera_height;
	nums[24] = &physics_models[type].splash_height;
	nums[25] = &physics_models[type].half_camera_separation;

	for(int i = 0; i < NUMBER_OF_PHYSICS_ITEMS; i ++){
		this->datas[i]->SetValue(wx::string::getString("%d",
			*nums[i]));
	}

}
int PhysicsPanel::common()
{
	int type = wxGetApp().getEditingPhysicsIndex();
	wxGetApp().setChanged(true);
	return type;
}
