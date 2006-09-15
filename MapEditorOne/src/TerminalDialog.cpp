// TerminalDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "TerminalDialog.h"


// CTerminalDialog ダイアログ

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


// CTerminalDialog メッセージ ハンドラ

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

    // TODO:  ここに初期化を追加してください
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
        //選択状態にする
        terminalList.SetCurSel(editTerminalIndex);

        //流し込む
        storeGroups(get_indexed_terminal_data(editTerminalIndex), &terminalGroupList);
        terminalGroupList.SetCurSel(editTerminalGroupIndex);

    }else{
        editTerminalIndex = -1;
        editTerminalGroupIndex = -1;
    }

    setupDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CTerminalDialog::setupDialog()
{
    
    int tsel = terminalList.GetCurSel();
    if(tsel == LB_ERR){
        //選択されていない
        //グループを空に。
        terminalGroupList.ResetContent();
        //テキストを空に
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
            //ターミナルテキストを流し込む
            //CString msg = CString((char*)get_indexed_terminal_data(editTerminalIndex)->text);
            char *cstr = new char[terminal->text_length + 1];
            for(int i = 0; i < terminal->groupings[gsel].length; i ++){
                cstr[i] = (char)terminal->text[i + terminal->groupings[gsel].start_index];
            }
            cstr[terminal->groupings[gsel].length] = '\0';
            CString msg = CString(cstr);
            //MessageBox(msg);
            //テキストを流し込む
            terminalEdit.SetWindowText(msg);
            
            //情報を流す
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

//ターミナル選択
void CTerminalDialog::OnLbnSelchangeListTerminals()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    setupDialog();
}

void CTerminalDialog::OnLbnSelchangeListGroups()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    setupDialog();
}
