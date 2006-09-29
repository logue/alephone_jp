// ObjectPlacementDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ObjectPlacementDialog.h"
#include ".\objectplacementdialog.h"


// CObjectPlacementDialog ダイアログ

IMPLEMENT_DYNAMIC(CObjectPlacementDialog, CDialog)


static char cstr[256];
static WCHAR wstr[256];

void CObjectPlacementDialog::setListControlItem( CListCtrl *ctrl, object_frequency_definition *place,
                                                LVITEM *item)
{
    //minimum
    item->iSubItem = idColumn[1];
    sprintf(cstr, "%d", place->minimum_count);
    charToWChar(cstr, wstr);
    item->pszText = wstr;
    ctrl->SetItem(item);

    //maximum
    item->iSubItem = idColumn[2];
    sprintf(cstr, "%d", place->maximum_count);
    charToWChar(cstr, wstr);
    item->pszText = wstr;
    ctrl->SetItem(item);
    
    //init
    item->iSubItem = idColumn[3];
    sprintf(cstr, "%d", place->initial_count);
    charToWChar(cstr, wstr);
    item->pszText = wstr;
    ctrl->SetItem(item);

    //rnd count
    item->iSubItem = idColumn[4];
    sprintf(cstr, "%d", place->random_count);
    charToWChar(cstr, wstr);
    item->pszText = wstr;
    ctrl->SetItem(item);

    //rnd chance
    item->iSubItem = idColumn[5];
    sprintf(cstr, "%d", place->random_chance);
    charToWChar(cstr, wstr);
    item->pszText = wstr;
    ctrl->SetItem(item);

    //flags
    item->iSubItem = idColumn[6];
    sprintf(cstr, "%d", place->flags);
    charToWChar(cstr, wstr);
    item->pszText = wstr;
    ctrl->SetItem(item);
}

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
    DDX_Control(pDX, IDC_EDIT4, randomChanceNum);
    DDX_Control(pDX, IDC_CHECK1, placementFlags);
    DDX_Control(pDX, IDC_EDIT5, initialNum);
}


BEGIN_MESSAGE_MAP(CObjectPlacementDialog, CDialog)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CObjectPlacementDialog::OnNMClickList1)
    ON_BN_CLICKED(IDC_CHECK1, &CObjectPlacementDialog::OnBnClickedCheck1)
    ON_EN_CHANGE(IDC_EDIT1, &CObjectPlacementDialog::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT2, &CObjectPlacementDialog::OnEnChangeEdit2)
    ON_EN_CHANGE(IDC_EDIT3, &CObjectPlacementDialog::OnEnChangeEdit3)
    ON_EN_CHANGE(IDC_EDIT4, &CObjectPlacementDialog::OnEnChangeEdit4)
    ON_EN_CHANGE(IDC_EDIT5, &CObjectPlacementDialog::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CObjectPlacementDialog メッセージ ハンドラ

BOOL CObjectPlacementDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //1 line select
    ListView_SetExtendedListViewStyle(
        (HWND)objectPlacementListCtrl.m_hWnd,
        LVS_EX_FULLROWSELECT);
    //リストコントロールに流し込む
    //カラム追加
    LVCOLUMN column;
    char columnNames[][100] ={
        "type", "min", "max", 
        "initial", "rnd count", "rnd chance", "flags"
    };
    WCHAR wwstr[256];
    for(int i = 0; i < 7; i ++){
        charToWChar(columnNames[i], wwstr);
        column.pszText = wwstr;
        column.mask = LVCF_TEXT | LVCF_WIDTH;
        column.fmt = LVCFMT_LEFT;

        int width = 70;
        if(i == 0){
            width = 100;
        }
        column.cx = width;
        idColumn[i] = objectPlacementListCtrl.InsertColumn(i, &column);
        //objectPlacementListCtrl.SetColumnWidth(idColumn[i], width);
    }
    
    LVITEM item;
    //object_frequency_definition def_place;
    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MONSTER_TYPES; i ++){

        object_frequency_definition *place = getIndexOfPlacement(i);
        CString jname;
        if(place == NULL){
            break;
        }
        if(i < NUMBER_OF_DEFINED_ITEMS){
            jname = theApp.itemTypeInformations[i].jname;
        }else{
            int de = i - NUMBER_OF_DEFINED_ITEMS;
            jname = theApp.monsterTypeInformations[de].jname;
        }
        //name
        item.mask = LVIF_TEXT | LVCF_WIDTH ;
        item.iSubItem = idColumn[0];
        strToChar(jname, cstr);
        charToWChar(cstr, wstr);
        item.pszText = wstr;
        item.iItem = i;
        int idItem = objectPlacementListCtrl.InsertItem(&item);

        setListControlItem(&objectPlacementListCtrl, place,
            &item);
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

//setup list control
void CObjectPlacementDialog::setupDialog()
{
    LVITEM item;
    //object_frequency_definition def_place;
    for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS + NUMBER_OF_MONSTER_TYPES; i ++){
        item.mask = LVIF_TEXT | LVCF_WIDTH ;
        item.iItem = i;
        object_frequency_definition *place = getIndexOfPlacement(i);
        setListControlItem(&objectPlacementListCtrl, place, &item);
    }
    UpdateData();
}

void CObjectPlacementDialog::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO : ここにコントロール通知ハンドラ コードを追加します。
    int sel = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if( sel >= 0){
        object_frequency_definition *place =
            getIndexOfPlacement(sel);
        setIntegerNum(place->minimum_count, &minimumNum);
        setIntegerNum(place->maximum_count, &maximum);
        setIntegerNum(place->random_count, &randomCountNum);
        setIntegerNum(place->random_chance, &randomChanceNum);
        setIntegerNum(place->initial_count, &initialNum);
        int check = 0;
        if(place->flags){
            check = 1;
        }
        placementFlags.SetCheck(check);
    }
    UpdateData();

    *pResult = 0;
}
//select item

void CObjectPlacementDialog::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
/*    int sel = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if( sel >= 0){
        object_frequency_definition *place =
            getIndexOfPlacement(sel);
        setIntegerNum(place->minimum_count, &minimumNum);
        setIntegerNum(place->maximum_count, &maximum);
        setIntegerNum(place->random_count, &randomCountNum);
        setIntegerNum(place->random_chance, &randomChanceNum);
        int check = 0;
        if(place->flags){
            check = 1;
        }
        placementFlags.SetCheck(check);
    }
    UpdateData();*/
    *pResult = 0;
}
//change flag
void CObjectPlacementDialog::OnBnClickedCheck1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int index = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if(index >= 0){
        int flags = 0;
        if(placementFlags.GetCheck()){
            flags = 1;
        }
        object_frequency_definition *place =
            getIndexOfPlacement(index);
        place->flags = flags;
    }    
}

//min
void CObjectPlacementDialog::OnEnChangeEdit1()
{
    //enchange
    int index = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if(index >= 0){
        getIndexOfPlacement(index)->minimum_count = getIntegerNum(&this->minimumNum);
    }
    setupDialog();
}
//max
void CObjectPlacementDialog::OnEnChangeEdit2()
{
    int index = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if(index >= 0){
        getIndexOfPlacement(index)->maximum_count = getIntegerNum(&this->maximum);
    }
    setupDialog();
}
//random count
void CObjectPlacementDialog::OnEnChangeEdit3()
{
    int index = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if(index >= 0){
        getIndexOfPlacement(index)->random_count = getIntegerNum(&this->randomCountNum);
    }
    setupDialog();
}
//random chance
void CObjectPlacementDialog::OnEnChangeEdit4()
{
    int index = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if(index >= 0){
        getIndexOfPlacement(index)->random_chance = getIntegerNum(&this->randomChanceNum);
    }
    setupDialog();
}

void CObjectPlacementDialog::OnEnChangeEdit5()
{
    int index = objectPlacementListCtrl.GetNextItem(-1, LVIS_SELECTED);
    if(index >= 0){
        getIndexOfPlacement(index)->initial_count = getIntegerNum(&this->initialNum);
    }
    setupDialog();
}
