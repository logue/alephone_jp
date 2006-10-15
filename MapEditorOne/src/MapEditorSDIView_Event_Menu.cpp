#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"
#include ".\mapeditorsdiview.h"
#include "SelectLevelDialog.h"

static bool loadMapFromFile(const char* filename){
    FileSpecifier mapFile = FileSpecifier(filename);
    //set map file
    set_map_file(mapFile);
    return true;
}
//open file
void CMapEditorSDIView::OnFileOpen()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。

    if(theApp.isChanged){
        //warn to save
        if(MessageBox(L"map changed, but no save is found.", L"warn to save",
            MB_OKCANCEL | MB_ICONEXCLAMATION) != IDOK)
        {
            return ;
        }
    }
    	//ファイルオープンダイアログ表示
	CFileDialog dlg(TRUE, L"*.*", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

        //読み込み
        char cstr[256];
        strToChar(filename, cstr);

        //タイトルに設定
        CMapEditorSDIDoc* doc = GetDocument();
        doc->SetTitle(filename);

        
        //マップファイルロード
        loadMapFromFile(cstr);

        //レベル1を読み込んでみる
        {
            theApp.selectGroupInformation.clear();
            initialize_map_for_new_level();
            theApp.editLevelIndex = 0;
            bool check = load_level_from_map(theApp.editLevelIndex);
            if(!check){
                MessageBox(L"failed");
            }
        }

        /*int s[10];
        for(int i = 0; i < SavedObjectList.size(); i ++){
            int t = SavedObjectList[i].location.x;
            sprintf(cstr, "%d", t);
            //TRACE(CString(cstr)+L"\n");
        }*/
//        char cstr[256];
        //monster_placement_info[0].

        theApp.LevelNameList.RemoveAll();
        
        //int index = 0;
        {
            short index = 0;
            struct entry_point ep;
            int type = 3;
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d,", ep.level_number);
                theApp.LevelNameList.Add(//CString(cstr) + 
                    CString(ep.level_name));
            }
            /*sprintf(cstr, "%d", theApp.LevelNameList.GetSize());
            MessageBox(CString(cstr));*/
        }
        //ステータスバーに表示
        setStatusBar(0, theApp.LevelNameList.GetAt(0));

        //default zoom
        theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
        
        //default position(center)
        OnItemCentering();

        //
        theApp.isChanged = false;
        this->Invalidate(FALSE);
    }
}
//save file
void CMapEditorSDIView::OnFileSave()
{
    CFileDialog dlg(FALSE, L"*.sceA", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"MarathonMapFile (*.sceA)|*.sceA|Any format (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();
        char cstr[256];
        strToChar(filename, cstr);

        //保存
        if(!save_level(cstr)){
            MessageBox(L"failure");
        }else{
            theApp.isChanged = false;
        }
    }
}

/**
    Jump Level!
*/
void CMapEditorSDIView::On32776()
{
    // TODO : ここにコマンド ハンドラ コードを追加します。
    //レベル選択ダイアログ
    CSelectLevelDialog dlg;
    if(dlg.DoModal() == IDOK){
        load_level_from_map(theApp.editLevelIndex);

        //中心へ移動
        OnItemCentering();

        //Zoom
        OnItemZoomDefault();

        //選択無し
        theApp.selectGroupInformation.clear();

        this->Invalidate(FALSE);

        //ステータスバーに表示
        setStatusBar(0, theApp.LevelNameList.GetAt(theApp.editLevelIndex));
    }
}

//zoom in / out
void CMapEditorSDIView::addZoom(int step)
{
    int oldZoomDiv = theApp.zoomDivision;
    if( theApp.zoomDivision < 50){
        step = sgn<int>(step);
    }
    theApp.zoomDivision += step;
    if(theApp.zoomDivision < ZOOM_DIVISION_MIN){
        theApp.zoomDivision = ZOOM_DIVISION_MIN;
    }else if(theApp.zoomDivision > ZOOM_DIVISION_MAX){
        theApp.zoomDivision = ZOOM_DIVISION_MAX;
    }
    CRect rect;
    GetClientRect(&rect);

    POINT oldOffset = theApp.offset;
    POINT center;
    center.x = rect.Width() / 2;
    center.y = rect.Height() / 2;
    int newZoomDiv = theApp.zoomDivision;

    int ax = center.x - oldOffset.x;
    theApp.offset.x = center.x - (ax * oldZoomDiv / newZoomDiv);
    int ay = center.y - oldOffset.y;
    theApp.offset.y = center.y - (ay * oldZoomDiv / newZoomDiv);
    /*
    int delta = OFFSET_X_WORLD / theApp.zoomDivision -
        //(rect.Width() / 2) +
        OFFSET_X_WORLD / oldZoomDiv;
    theApp.offset.x -= delta;
    delta = OFFSET_Y_WORLD / theApp.zoomDivision -
        //(rect.Height() / 2) +
        OFFSET_Y_WORLD / oldZoomDiv;
    theApp.offset.y -= delta;
    */
}

//拡大
void CMapEditorSDIView::OnZoomIn()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    addZoom(-ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//縮小
void CMapEditorSDIView::OnZoomOut()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    addZoom(ZOOM_DIVISION_STEP);
    this->Invalidate(FALSE);
}

//中心へ移動
void CMapEditorSDIView::OnItemCentering()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.offset.x = 0;
    theApp.offset.y = 0;
    Invalidate(FALSE);
}
//拡大標準
void CMapEditorSDIView::OnItemZoomDefault()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.zoomDivision = ZOOM_DIVISION_DEFAULT;
    Invalidate(FALSE);
}
//object info dialog on/off
void CMapEditorSDIView::On32784()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.objectPropertyDialog->ShowWindow(!theApp.objectPropertyDialog->IsWindowVisible());
    int flags = MF_BYCOMMAND;
    if(theApp.objectPropertyDialog->IsWindowVisible()){
        flags |= MF_CHECKED;
    }else{
        flags |= MF_UNCHECKED;
    }
    GetMenu()->CheckMenuItem(ID_32784, flags);
}
//level information(same to new)
void CMapEditorSDIView::On32787()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    CLevelParameterDialog dlg(this, false);
    if(dlg.DoModal() == IDOK){
        //値設定
    }
}
//show/hide height dialog
void CMapEditorSDIView::On32789()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.heightDialog->ShowWindow(theApp.heightDialog->IsWindowVisible());
}
//show/hide polygon type dialog
void CMapEditorSDIView::On32786()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    theApp.polygonTypeDialog->ShowWindow(theApp.polygonTypeDialog->IsWindowVisible());
}
//edit terminals
void CMapEditorSDIView::On32790()
{
    // TODO: ここにコマンド ハンドラ コードを追加します。
    CTerminalDialog dlg(this);
    if(dlg.DoModal() == IDOK){
        //変更を保存

    }
}

void CMapEditorSDIView::changeMode(int mode)
{
    int oldMode = theApp.getEditMode();
    int nextMode = mode;
    theApp.setEditMode(nextMode);
    //チェックを変更
    int flags = 0;
    flags = MF_BYCOMMAND | MF_UNCHECKED;
    //GetMenu()->CheckMenuItem(theApp.menuIDMap[oldMode], flags);
    flags = MF_BYCOMMAND | MF_CHECKED;
    //GetMenu()->CheckMenuItem(theApp.menuIDMap[nextMode], flags);
    Invalidate(FALSE);

}
//draw polygon mode
void CMapEditorSDIView::On32795()
{
    changeMode(EM_DRAW);
}
//height -> floor
void CMapEditorSDIView::OnHeightFloor()
{
    changeMode(EM_FLOOR_HEIGHT);
}

void CMapEditorSDIView::OnModePolygontype()
{
    changeMode(EM_POLYGON_TYPE);

    //show polygon type dialog
    theApp.polygonTypeDialog->ShowWindow(TRUE);

    //hide other dialog
    theApp.objectPropertyDialog->ShowWindow(FALSE);
    theApp.polygonPropertyDialog->ShowWindow(FALSE);
    
}
