#include "PolygonTypeDialog.h"
#include "MapEditorWX.h"
enum{
    ID_SEL
};
BEGIN_EVENT_TABLE(PolygonTypeDialog, wxDialog)
    EVT_LIST_ITEM_SELECTED(ID_SEL, PolygonTypeDialog::OnSel)
END_EVENT_TABLE()
PolygonTypeDialog::PolygonTypeDialog()
{
}
PolygonTypeDialog::~PolygonTypeDialog()
{
}
bool PolygonTypeDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Polygon Type"));

    list_ctrl_2 = new wxListCtrl(this, ID_SEL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxSUNKEN_BORDER);
    list_ctrl_2->SetMinSize(wxSize(120,120));

    wxBoxSizer* sizer_53 = new wxBoxSizer(wxHORIZONTAL);
    sizer_53->Add(list_ctrl_2, 1, wxEXPAND, 0);
    SetSizer(sizer_53);
    sizer_53->Fit(this);
    Layout();
	//setup columns
	char *columnNames[100] = {"Index", "Color"};
	const int COLUMN_NUM = 2;
    for(int i = 0; i < COLUMN_NUM; i ++){
        list_ctrl_2->InsertColumn(i, wxConvertMB2WX(columnNames[i]));
    }
	wxString strings[NUMBER_OF_POLYGON_TYPE];
	wxColor colors[NUMBER_OF_POLYGON_TYPE];
	for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
		strings[i] = wxConvertMB2WX(wxGetApp().polygonTypeInfo[i].jname.c_str());
		colors[i] = wxColor(
			wxGetApp().polygonTypeColors[i][0],
			wxGetApp().polygonTypeColors[i][1],
			wxGetApp().polygonTypeColors[i][2]);
	}
	wxGetApp().setupPaletteListControl(NUMBER_OF_POLYGON_TYPE, list_ctrl_2,
		strings, colors);

	setType(0);
    return result;
}
void PolygonTypeDialog::OnSel(wxListEvent &event)
{
	polyType = event.GetIndex();
}
void PolygonTypeDialog::setupDialog()
{
}
void PolygonTypeDialog::setType(int type)
{
	this->polyType = type;
	//ëIëê›íË
	for(int i = 0; i < list_ctrl_2->GetItemCount(); i ++){
		list_ctrl_2->SetItemState(i, 0, 0);
	}
	list_ctrl_2->SetItemState(polyType, wxLIST_STATE_SELECTED, 0);
}
int PolygonTypeDialog::getType()
{
	return this->polyType;
}
