#include "TerminalDialog.h"
#include "computer_interface.h"
#include "MapEditorWX.h"

const int BUF_MAX = 1024;

enum{
    ID_TERMINAL,
    ID_SCREEN,
    ID_INFO,
    ID_TEXT_EDIT
};

BEGIN_EVENT_TABLE(TerminalDialog, wxDialog)
    EVT_LISTBOX(ID_TERMINAL, TerminalDialog::OnSelTerminal)
    EVT_LISTBOX(ID_SCREEN, TerminalDialog::OnSelScreen)
    EVT_LISTBOX(ID_INFO, TerminalDialog::OnSelInfo)
    EVT_TEXT(ID_TEXT_EDIT, TerminalDialog::OnEdit)
    EVT_BUTTON(wxID_OK, TerminalDialog::OnOk)
END_EVENT_TABLE()

TerminalDialog::TerminalDialog():wxDialog()
{
}

TerminalDialog::~TerminalDialog()
{
}
bool TerminalDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Terminal"));
    if(!result){
        return result;
    }
    list_box_1 = new wxListBox(this, ID_TERMINAL);
    list_box_2 = new wxListBox(this, ID_SCREEN);
    list_box_3 = new wxListBox(this, ID_INFO);
    panel_7 = new wxPanel(this, wxID_ANY);
    text_ctrl_13 = new wxTextCtrl(this, ID_TEXT_EDIT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    button_20 = new wxButton(this, wxID_OK, wxEmptyString);

    list_box_1->SetMinSize(wxSize(180, 200));
    list_box_2->SetMinSize(wxSize(180, 100));
    panel_7->SetMinSize(wxSize(500, 200));
    text_ctrl_13->SetMinSize(wxSize(500, 200));

    wxFlexGridSizer* grid_sizer_5 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_7 = new wxFlexGridSizer(3, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_6 = new wxFlexGridSizer(3, 1, 0, 0);
    grid_sizer_6->Add(list_box_1, 0, 0, 0);
    grid_sizer_6->Add(list_box_2, 0, 0, 0);
    grid_sizer_6->Add(list_box_3, 0, 0, 0);
    grid_sizer_5->Add(grid_sizer_6, 1, wxEXPAND, 0);
    grid_sizer_7->Add(panel_7, 1, wxEXPAND, 0);
    grid_sizer_7->Add(text_ctrl_13, 0, 0, 0);
    grid_sizer_7->Add(button_20, 0, wxALIGN_RIGHT, 0);
    grid_sizer_5->Add(grid_sizer_7, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_5);
    grid_sizer_5->Fit(this);
    Layout();

    //terminal index -> listbox_1
    for(int i = 0; i < (int)map_terminal_text.size(); i ++){
        //terminal_text_t* terminal = &map_terminal_text[i];
        char cstr[256];
        sprintf(cstr, "terminal%3d", i);
        list_box_1->Insert(wxString(wxConvertMB2WX(cstr)), i);
    }
/*    if(map_terminal_text.size() > 0){
        //選択状態にする <en> select one
        list_box_1->SetSelection(0);

//        wxCommandEvent dummy;
//        OnSelTerminal(dummy);
    }
    */
    return result;
}
void TerminalDialog::OnOk(wxCommandEvent& ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void TerminalDialog::OnSelTerminal(wxCommandEvent &event)
{
    int sel = event.GetSelection();
    if(sel < 0 || sel >= (int)map_terminal_text.size()){
        //illegal selecting
    }else{
        //スクリーンリストを初期化
        this->list_box_2->Clear();
        terminal_text_t *terminal = &map_terminal_text[sel];
        for(int i = 0; i < (int)terminal->groupings.size(); i ++){
            terminal_groupings *group = &terminal->groupings[i];
            list_box_2->Insert(
                wxString(wxConvertMB2WX(wxGetApp().terminalTypeInfo[i].jname.c_str())),
                i);
        }
    }
}

static void encode_text(
    terminal_text_t *terminal_text)
{
	int length = terminal_text->text_length;
	uint8 *p = terminal_text->text;

	for (int i=0; i<length/4; i++) {
		p += 2;
		*p++ ^= 0xfe;
		*p++ ^= 0xed;
	}
	for (int i=0; i<length%4; i++)
		*p++ ^= 0xfe;

	terminal_text->flags |= _text_is_encoded_flag;
}
static void decode_text(
	terminal_text_t *terminal_text)
{
	if(terminal_text->flags & _text_is_encoded_flag)
	{
		encode_text(terminal_text);
		terminal_text->flags &= ~_text_is_encoded_flag;
	}
}

void TerminalDialog::OnSelScreen(wxCommandEvent &event)
{
    //Editに流し込みます
    int tsel = this->list_box_1->GetSelection();
    if(tsel < 0 || tsel >= (int)map_terminal_text.size()){
        return;
    }

    terminal_text_t *terminal = &map_terminal_text[tsel];
    int sel = event.GetSelection();
    if(sel < 0 || sel >= (int)terminal->groupings.size()){
        return;
    }

    //Edit初期化
    this->text_ctrl_13->Clear();
    decode_text(terminal);

    //文字列データへ変換
    int length = terminal->groupings[sel].length;
    char *cstr = new char[length + 1];
    for(int i = 0; i < length; i ++){
        uint8 u = terminal->text[i + terminal->groupings[sel].start_index];
        cstr[i] = static_cast<char>(u);
    }
    cstr[length] = '\0';
//    hpl::error::caution("%s", cstr);
    wxString str = wxString(wxConvertMB2WX(cstr));
    this->text_ctrl_13->SetValue(str);
//    this->text_ctrl_13->AppendText(str);
    delete cstr;

    //情報も入れる
    this->list_box_3->Clear();
    char buf[BUF_MAX];
    sprintf(buf, "group_flags:%d", terminal->groupings[sel].flags);
    this->list_box_3->Insert( wxConvertMB2WX(buf), 0);
    sprintf(buf, "group_permutation:%d", terminal->groupings[sel].permutation);
    this->list_box_3->Insert(wxConvertMB2WX(buf), 1);
    sprintf(buf, "terminal_flags:%d", terminal->flags);
    this->list_box_3->Insert(wxConvertMB2WX(buf), 2);
}


void TerminalDialog::OnSelInfo(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TerminalDialog::OnSelInfo) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void TerminalDialog::OnEdit(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (TerminalDialog::OnEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
