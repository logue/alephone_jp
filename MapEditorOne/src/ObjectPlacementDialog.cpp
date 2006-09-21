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
    column.pszText = L"type";
    idColumn[0] = objectPlacementListCtrl.InsertColumn(0, &column);
    objectPlacementListCtrl.SetColumnWidth(idColumn[0], 100);
    column.pszText = L"min";
    idColumn[1] = objectPlacementListCtrl.InsertColumn(1, &column);
    objectPlacementListCtrl.SetColumnWidth(idColumn[1], 100);
    column.pszText = L"max";
    idColumn[2] = objectPlacementListCtrl.InsertColumn(2, &column);
    objectPlacementListCtrl.SetColumnWidth(idColumn[2], 100);
    column.pszText = L"initial";
    idColumn[3] = objectPlacementListCtrl.InsertColumn(2, &column);
    objectPlacementListCtrl.SetColumnWidth(idColumn[3], 100);
    column.pszText = L"rnd count";
    idColumn[4] = objectPlacementListCtrl.InsertColumn(2, &column);
    objectPlacementListCtrl.SetColumnWidth(idColumn[4], 100);
    column.pszText = L"rnd chance";
    idColumn[5] = objectPlacementListCtrl.InsertColumn(2, &column);
    objectPlacementListCtrl.SetColumnWidth(idColumn[5], 100);
    column.pszText = L"flags";
    idColumn[6] = objectPlacementListCtrl.InsertColumn(2, &column);
    objectPlacementListCtrl.SetColumnWidth(idColumn[6], 100);
    
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

        place->minimum_count;
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
