// ObjectPlacementDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ObjectPlacementDialog.h"


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
}


BEGIN_MESSAGE_MAP(CObjectPlacementDialog, CDialog)
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
    column.pszText = L"min";
    idColumn[1] = objectPlacementListCtrl.InsertColumn(1, &column);
    column.pszText = L"max";
    idColumn[2] = objectPlacementListCtrl.InsertColumn(2, &column);

    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MONSTER_TYPES; i ++){

        object_frequency_definition *place;
        if(i < NUMBER_OF_DEFINED_ITEMS){
            place = &item_placement_info[i];
        }else{
            place = &monster_placement_info[i];
        }
        CString jname = theApp.monsterTypeInformations[i].jname;

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

        //name
        item.iSubItem = idColumn[1];
        sprintf(cstr, "%d", place->minimum_count);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);

        //name
        item.iSubItem = idColumn[2];
        sprintf(cstr, "%d", place->maximum_count);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        objectPlacementListCtrl.SetItem(&item);
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
