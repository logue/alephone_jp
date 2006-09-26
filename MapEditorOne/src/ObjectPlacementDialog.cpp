// ObjectPlacementDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ObjectPlacementDialog.h"
#include ".\objectplacementdialog.h"


// CObjectPlacementDialog ダイアログ

IMPLEMENT_DYNAMIC(CObjectPlacementDialog, CDialog)

CObjectPlacementDialog::CObjectPlacementDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectPlacementDialog::IDD, pParent)
{
    int a = 0;
}

CObjectPlacementDialog::~CObjectPlacementDialog()
{
}

void CObjectPlacementDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, objectPlacementListCtrl);
    DDX_Control(pDX, IDC_EDIT1, minimumNum);
    DDX_Control(pDX, IDC_EDIT2, maximum);
    DDX_Control(pDX, IDC_EDIT3, randomCountNum);
}


BEGIN_MESSAGE_MAP(CObjectPlacementDialog, CDialog)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CObjectPlacementDialog メッセージ ハンドラ

BOOL CObjectPlacementDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //リストコントロールに流し込む
    //カラム追加
    LV_COLUMN column;
    char columnNames[][100] ={
        "type", "min", "max", 
        "initial", "rnd count", "rnd chance", "flags"
    };
    WCHAR wwstr[256];
    for(int i = 0; i < 7; i ++){
        charToWChar(columnNames[i], wwstr);
        column.pszText = wwstr;
        idColumn[i] = objectPlacementListCtrl.InsertColumn(i, &column);
        int width = 70;
        if(i == 0){
            width = 100;
        }
        objectPlacementListCtrl.SetColumnWidth(idColumn[i], width);
    }
    
    //object_frequency_definition def_place;
    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MONSTER_TYPES; i ++){

        object_frequency_definition *place;
        CString jname;
        if(i < NUMBER_OF_DEFINED_ITEMS){
            place = &item_placement_info[i];
            jname = theApp.itemTypeInformations[i].jname;
        }else{
            int index = i - NUMBER_OF_DEFINED_ITEMS;
            place = &monster_placement_info[index];
            jname = theApp.monsterTypeInformations[index].jname;
        }
        if(place == NULL){
            break;
        }
        char cstr[256];
        WCHAR wstr[256];
        LV_ITEM item;
        int idItem;

        //name
        item.iSubItem = idColumn[0];
        strToChar(jname, cstr);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        idItem = objectPlacementListCtrl.InsertItem(&item);
        item.iItem = idItem;

        //minimum
        item.iSubItem = idColumn[1];
        sprintf(cstr, "%d", place->minimum_count);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);

        //maximum
        item.iSubItem = idColumn[2];
        sprintf(cstr, "%d", place->maximum_count);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);
        
        //init
        item.iSubItem = idColumn[3];
        sprintf(cstr, "%d", place->initial_count);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);

        //rnd count
        item.iSubItem = idColumn[4];
        sprintf(cstr, "%d", place->random_count);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);

        //rnd chance
        item.iSubItem = idColumn[5];
        sprintf(cstr, "%d", place->random_chance);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);

        //flags
        item.iSubItem = idColumn[6];
        sprintf(cstr, "%d", place->flags);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

//
void CObjectPlacementDialog::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    int sel = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if( sel >= 0){
        object_frequency_definition *place;
        if( sel < NUMBER_OF_DEFINED_ITEMS){
            place = &item_placement_info[sel];
        }else{
            int index = sel - NUMBER_OF_DEFINED_ITEMS;
            place = &monster_placement_info[index];
        }
        setIntegerNum(place->minimum_count, &minimumNum);
        setIntegerNum(place->maximum_count, &maximum);
        setIntegerNum(place->random_count, &randomCountNum);
    }

    *pResult = 0;
}
