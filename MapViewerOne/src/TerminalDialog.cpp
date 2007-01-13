// TerminalDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "TerminalDialog.h"


// CTerminalDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CTerminalDialog, CDialog)

CTerminalDialog::CTerminalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTerminalDialog::IDD, pParent)
{
}

CTerminalDialog::~CTerminalDialog()
{
}

void CTerminalDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_TERMINALS, terminalList);
    DDX_Control(pDX, IDC_LIST_GROUPS, terminalGroupList);
    //    DDX_Control(pDX, IDC_RICHEDIT21, terminalEdit);
    DDX_Control(pDX, IDC_EDIT1, terminalEdit);
    DDX_Control(pDX, IDC_LIST_INFORMATION, informationList);
}


BEGIN_MESSAGE_MAP(CTerminalDialog, CDialog)
    ON_LBN_SELCHANGE(IDC_LIST_TERMINALS, &CTerminalDialog::OnLbnSelchangeListTerminals)
    ON_LBN_SELCHANGE(IDC_LIST_GROUPS, &CTerminalDialog::OnLbnSelchangeListGroups)
END_MESSAGE_MAP()


// CTerminalDialog ���b�Z�[�W �n���h��

static void storeGroups(terminal_text_t *terminal, CListBox *listbox)
{
    listbox->ResetContent();
    for(int i = 0; i < (int)terminal->groupings.size(); i ++){
        terminal_groupings *group = &terminal->groupings[i];
        //add type name
        listbox->InsertString(i,
            CString(theApp.terminalGroupTypeInformations[group->type].jname));
    }
}

BOOL CTerminalDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    //terminal index -> list box
    for(int i = 0; i < (int)map_terminal_text.size(); i ++){
        //terminal_text_t* terminal = &map_terminal_text[i];
        char cstr[256];
        sprintf(cstr, "terminal%3d", i);
        terminalList.InsertString(i, CString(cstr));
    }
    editTerminalIndex = 0;
    if(map_terminal_text.size() > 0){
        editTerminalGroupIndex = 0;
        //�I����Ԃɂ���
        terminalList.SetCurSel(editTerminalIndex);

        //��������
        storeGroups(get_indexed_terminal_data(editTerminalIndex), &terminalGroupList);
        terminalGroupList.SetCurSel(editTerminalGroupIndex);

    }else{
        editTerminalIndex = -1;
        editTerminalGroupIndex = -1;
    }

    setupDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CTerminalDialog::setupDialog()
{
    
    int tsel = terminalList.GetCurSel();
    if(tsel == LB_ERR){
        //�I������Ă��Ȃ�
        //�O���[�v����ɁB
        terminalGroupList.ResetContent();
        //�e�L�X�g�����
        terminalEdit.Clear();
    }else{
        terminal_text_t* terminal = get_indexed_terminal_data(editTerminalIndex);
        //show selected group
        if(tsel != editTerminalIndex){
            editTerminalIndex = tsel;
            terminal = get_indexed_terminal_data(editTerminalIndex);
            //clear list & store group list
            storeGroups(terminal, &terminalGroupList);
        }
        terminalEdit.Clear();
        int gsel = terminalGroupList.GetCurSel();
        if(gsel == LB_ERR){
        }else{
            //�^�[�~�i���e�L�X�g�𗬂�����
            //CString msg = CString((char*)get_indexed_terminal_data(editTerminalIndex)->text);
            char *cstr = new char[terminal->text_length + 1];
            for(int i = 0; i < terminal->groupings[gsel].length; i ++){
                cstr[i] = (char)terminal->text[i + terminal->groupings[gsel].start_index];
            }
            cstr[terminal->groupings[gsel].length] = '\0';
            CString msg = CString(cstr);
            //MessageBox(msg);
            //�e�L�X�g�𗬂�����
            terminalEdit.SetWindowText(msg);
            
            //���𗬂�
            informationList.ResetContent();
            sprintf(cstr, "group_flags:%d", terminal->groupings[gsel].flags);
            informationList.InsertString(0, CString(cstr));
            sprintf(cstr, "group_permutation:%d", terminal->groupings[gsel].permutation);
            informationList.InsertString(0, CString(cstr));
            sprintf(cstr, "terminal_flags:%d", terminal->flags);
            informationList.InsertString(0, CString(cstr));

            delete cstr;
        }

    }
    
    UpdateData();
}

//�^�[�~�i���I��
void CTerminalDialog::OnLbnSelchangeListTerminals()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    setupDialog();
}

void CTerminalDialog::OnLbnSelchangeListGroups()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    setupDialog();
}
