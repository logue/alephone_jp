#include "MapEditorMainFrame.h"

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// file menus

void MapEditorMainFrame::OnPrint(wxCommandEvent& ev)
{
    //マップの全体像を紙サイズに合わせて印刷
}
void MapEditorMainFrame::OnPrintPreview(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPrintSetup(wxCommandEvent& ev)
{
}

void MapEditorMainFrame::initLevel()
{
    //初期化
    wxGetApp().editLevelIndex = 0;
    build_trig_tables();
    //allocate
    if(dynamic_world == NULL){
        allocate_map_memory();
    }
    //ズーム・オフセットを初期化
    wxCommandEvent dummy;
    this->OnZoomDefault(dummy);
    this->OnMoveToCenter(dummy);


    wxGetApp().getStockManager()->resetDeletes();
    wxGetApp().isChanged = false;
    //レベル一覧削除
    wxGetApp().levelNameList.clear();
    initialize_map_for_new_level();
    //データの初期化
    wxGetApp().getStockManager()->resetDeletes();
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MAX);
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MIN);
}
void MapEditorMainFrame::OnNew(wxCommandEvent& ev)
{
    if(wxGetApp().isChanged){
        wxMessageDialog dlg(this, _T("Map has been modified. Are you sure that delete this and create new one?"));
        if(dlg.ShowModal() == wxID_CANCEL){
            //拒否
            return;
        }
    }
    initLevel();


    //ついでにレベル設定
    //TODO
    //レベル設定ダイアログ表示
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
    //内容をマップデータに反映
    //TODO

    Refresh();
}
void MapEditorMainFrame::OnNewLevel(wxCommandEvent& ev)
{
    //新規レベル作成
    //TODO 不要？
    //マージされているマップは保存できない


}

void MapEditorMainFrame::OnOpen(wxCommandEvent& WXUNUSED(ev))
{
    //TODO 未セーブチェック
    wxFileDialog fileDialog(this, _T("Choose a file"),
        _T("."), _T(""), _T("*.*"));

    if(fileDialog.ShowModal() == wxID_OK){
        wxString path = fileDialog.GetPath();

        //タイトル
        SetTitle(path);
        
        FileSpecifier mapFile = FileSpecifier(path.mb_str());

        //set map file
        set_map_file(mapFile);

        wxGetApp().filePath = path;
        //初期化
        initLevel();

        //Level1を読み込み
        bool check = load_level_from_map(wxGetApp().editLevelIndex);
        if(!check){
            wxMessageBox(_T("failed"));
        }

        //インデックス
        wxGetApp().levelNameList.clear();
        {
            short index = 0;
            struct entry_point ep;
            int type = 3;
            char cstr[256];
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d", ep.level_number);
                wxGetApp().levelNameList.push_back(string(cstr) + string(ep.level_name));
            }
            if(wxGetApp().levelNameList.size() == 0){
                wxGetApp().levelNameList.push_back("unnamed");
            }
        }
        //セットアップ
        wxGetApp().getStockManager()->updateDeletes();
        //再描画
        Refresh();
    }
}void MapEditorMainFrame::OnSave(wxCommandEvent& ev)
{
    //TODO save correctly
    if(wxGetApp().isChanged){
        OnSaveAs(ev);
    }else{
        //現在のファイル名で保存
        if(save_level(wxGetApp().filePath.mb_str())){
            wxGetApp().isChanged = false;
//            wxGetApp().filePath = fname;
        }else{
            hpl::error::caution("save failure");
        }
    }
}
void MapEditorMainFrame::OnSaveAs(wxCommandEvent& ev)
{
    int style = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
    wxString wildcard(_T("AlephOne map (*.sceA)|*.sceA|Any file|*.*"));
    wxFileDialog dlg(this, wxString(_T("Save at...")), 
        wxString(_T("")), wxString(_T("")), wildcard,
        style);
    if(dlg.ShowModal() == wxID_OK){
        //
        wxString fname = dlg.GetPath();
        SetTitle(fname);

        if(save_level(fname.mb_str())){
            wxGetApp().isChanged = false;
            wxGetApp().filePath = fname;
        }else{
            hpl::error::caution("save failure");
        }
    }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// edit menus
void MapEditorMainFrame::OnUndo(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnCut(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnCopy(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPaste(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPreference(wxCommandEvent& ev)
{
    //Call up editor preferences dialog
    EditorPreferencesDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //ファイルに保存
        if(!wxGetApp().setting.saveSetting()){
            hpl::error::caution("Fail to save setting as [%s]", wxGetApp().setting.getFilePath().c_str());
        }
        //ペンの作り直し
        setupPenAndBrush(wxGetApp().setting.getColorSetting());
        Refresh();
    }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// show/hide menus
void MapEditorMainFrame::OnToolDialog(wxCommandEvent& ev)
{
    this->toolDialog.Show(!this->toolDialog.IsShown());
}
void MapEditorMainFrame::OnZoomIn(wxCommandEvent& ev)
{
    wxSize size = this->GetSize();
    wxGetApp().getViewGridManager()->zoomIn(size.GetWidth(), size.GetHeight());
}
void MapEditorMainFrame::OnZoomOut(wxCommandEvent& ev)
{
    wxSize size = this->GetSize();
    wxGetApp().getViewGridManager()->zoomOut(size.GetWidth(), size.GetHeight());
}
void MapEditorMainFrame::OnZoomDefault(wxCommandEvent& ev)
{
    wxGetApp().getViewGridManager()->zoomReset();
}
void MapEditorMainFrame::OnMoveToCenter(wxCommandEvent& ev)
{
    //中心がワールド座標の真ん中に来るようにする
    wxGetApp().getViewGridManager()->setOffset(0,0);
}
void MapEditorMainFrame::OnHeightDialog(wxCommandEvent& ev)
{
    bool shown = this->heightDialog.IsShown();
    this->heightDialog.Show(!shown);
    if(shown){
        //TODO メニューにチェックを入れる
        //this->GetMenuBar()->GetMenu(0)->Get
    }else{
    }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// mode menus
/*
    モードレスダイアログがいっぱいになるので、メニュー選択時に切り替える
    それぞれのモードで開いている可能性のあるモードレスダイアログは以下のとおり
    ・Draw(Polygon)Mode
        点情報ダイアログ        PointProp
        線情報ダイアログ        LineProp
        ポリゴン情報ダイアログ  PolygonProp
        Side情報ダイアログ      SideProp
        オブジェクト情報ダイアログ  ObjectProp
    ・PolygonType
        PolygonType
    ・Floor/Ceiling HeightMode
        HeightPalette (setFloor(bool))
    ・Floor/CeilingTexture
        Texture
    ・Media
        MediaPalette
    ・Light
        LightPalette
*/

void MapEditorMainFrame::OnDrawPolygonMode(wxCommandEvent& ev)
{
    //現在の状態を取得
    bool checked = ev.IsChecked();
    
    //前の段階
    int editMode = wxGetApp().getEventManager()->getEditModeType();

    //一旦全てチェックをはずします
    this->uncheckModesOnMenu();

    //ドローモードにします
    wxGetApp().getEventManager()->setEditModeType(EditModeType::EM_DRAW);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();
}
void MapEditorMainFrame::closeAllModelessDialogs()
{
    this->objPropDialog.Show(false);
    this->pointPropDialog.Show(false);
    this->polyPropDialog.Show(false);
    this->linePropDialog.Show(false);
    this->sidePropDialog.Show(false);
    this->polyTypeDialog.Show(false);
    this->mediaPaletteDialog.Show(false);
    this->heightPaletteDialog.Show(false);
    this->lightPaletteDialog.Show(false);
    this->textureDialog.Show(false);
}

void MapEditorMainFrame::OnVisualMode(wxCommandEvent& ev)
{
    //モーダル表示
    VisualDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
    }

}
void MapEditorMainFrame::OnPolygonTypeMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_POLYGON_TYPE);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    //ポリゴンタイプダイアログ表示
    this->polyTypeDialog.Show(true);
}
void MapEditorMainFrame::OnFloorHeightMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_FLOOR_HEIGHT);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    //床の高さ
    this->heightPaletteDialog.setFloor(true);
    //高さパレットダイアログ表示
    this->heightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingHeightMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_CEILING_HEIGHT);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    //天井の高さ
    this->heightPaletteDialog.setFloor(false);
    //高さパレットダイアログ表示
    this->heightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnFloorLightMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_FLOOR_LIGHT);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    this->lightPaletteDialog.setFloor(true);
    //ライトパレットダイアログ表示
    this->lightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingLightMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_CEILING_LIGHT);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    this->lightPaletteDialog.setFloor(false);
    //ライトパレットダイアログ表示
    this->lightPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnMediaMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_MEDIA);
 
    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    //メディアパレットダイアログ表示
    this->mediaPaletteDialog.Show(true);
}
void MapEditorMainFrame::OnFloorTextureMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_FLOOR_TEXTURE);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    //テクスチャダイアログ表示
    this->textureDialog.setFloor(true);
    this->textureDialog.Show(true);
}
void MapEditorMainFrame::OnCeilingTextureMode(wxCommandEvent& ev)
{
    //モード変更
    this->changeEditMode(EditModeType::EM_CEILING_TEXTURE);

    //全部のダイアログを閉じます
    this->closeAllModelessDialogs();

    this->textureDialog.setFloor(false);
    //テクスチャダイアログ表示
    this->textureDialog.Show(true);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// special menus
void MapEditorMainFrame::OnJumpLevel(wxCommandEvent& ev)
{
    //TODO
    SelectLevelDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
    }
}
void MapEditorMainFrame::OnLevelInfo(wxCommandEvent& ev)
{
    //保存確認
    if(wxGetApp().isChanged){
        if(wxMessageBox(_T("This level has been edited. Destruct it?"), _T("Message"), 
            wxOK | wxCANCEL) == wxCANCEL)
        {
            return;
        }
    }
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() != wxCANCEL){
        //初期化
        this->initLevel();
        
        int index = wxGetApp().editLevelIndex;
        //読み込み
        bool check = load_level_from_map(index);
        if(!check){
            hpl::error::caution("Loading level[%d] failure", index);
        }
        wxGetApp().getStockManager()->updateDeletes();
    }
}
void MapEditorMainFrame::OnObjectPlacement(wxCommandEvent& ev)
{
    //オブジェクト配置ダイアログ
    PlacementDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
}
void MapEditorMainFrame::OnTerminalViewer(wxCommandEvent& ev)
{
    //ターミナル
    TerminalDialog dlg;
    dlg.Create(this, wxID_ANY);
    dlg.ShowModal();
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

void MapEditorMainFrame::OnLineProp(wxCommandEvent& ev)
{
    this->linePropDialog.setLineIndex(wxGetApp().popupLineIndex);
    this->linePropDialog.Show(true);
}
void MapEditorMainFrame::OnClockwiseSide(wxCommandEvent& ev)
{
    //TODO
    this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->clockwise_polygon_side_index);
    this->sidePropDialog.Show(true);
}
void MapEditorMainFrame::OnCounterclockwiseSide(wxCommandEvent& ev)
{
    //TODO
    this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->counterclockwise_polygon_side_index);
    this->sidePropDialog.Show(true);
}
void MapEditorMainFrame::OnPointProp(wxCommandEvent& ev)
{
    this->pointPropDialog.setIndex(wxGetApp().popupEndpointIndex);
    this->pointPropDialog.Show(true);
}
