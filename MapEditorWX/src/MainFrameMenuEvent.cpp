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
    //TODO
}
void MapEditorMainFrame::OnPrintSetup(wxCommandEvent& ev)
{
    //TODO
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

	//プロパティコンボボックスを設定
	this->polyPropDialog.updateCombo();
}

/**
    ダイアログを出して編集中のマップを破壊してよいかを聞き出します。
    @param ユーザからOKが出れば真。出なければ偽。
        また、編集されてなければ真が返る
*/
bool MapEditorMainFrame::askDestructMap()
{
    if(wxGetApp().isChanged){
        wxMessageDialog dlg(this, _T("Map has been modified. Are you sure that delete this and create new one?"));
        if(dlg.ShowModal() == wxID_OK){
            return true;
        }else{
            //拒否
            return false;
        }
    }
    return true;
}

void MapEditorMainFrame::OnNew(wxCommandEvent& ev)
{
    if(!this->askDestructMap()){
        return ;
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

static void loadLevel(int i){
    bool check = load_level_from_map(wxGetApp().editLevelIndex);
    if(!check){
        wxMessageBox(_T("failed"));
    }
    //セットアップ
    wxGetApp().getStockManager()->updateDeletes();

	//履歴初期化
	wxGetApp().getDoneHistoryManager()->init();

	//プレイヤーポジションを設定
	//プレイヤーを捜す
	for(int i = 0 ; i < (int)SavedObjectList.size(); i ++){
		map_object* obj = &SavedObjectList[i];
		if(obj->type == _saved_player){
			//位置取得
			wxGetApp().getVisualModeManager()->setPlayerPosition(obj->location);
			break;
		}
	}
}
void MapEditorMainFrame::OnOpen(wxCommandEvent& WXUNUSED(ev))
{
    //未セーブチェック
    if(!this->askDestructMap()){
        return ;
    }

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
        loadLevel(0);

        //インデックス
        wxGetApp().levelNameList.clear();
        {
            short index = 0;
            struct entry_point ep;
			//全てのマップを読み込み
            int type = 0xff;
            char cstr[256];
            while(get_indexed_entry_point(&ep, &index, type)){
                sprintf(cstr, "%d", ep.level_number);
                wxGetApp().levelNameList.push_back(string(cstr) + string(ep.level_name));
            }
            if(wxGetApp().levelNameList.size() == 0){
                wxGetApp().levelNameList.push_back("unnamed");
            }
        }

		//プロパティコンボボックスを設定
		this->polyPropDialog.updateCombo();

        //再描画
        Refresh();
    }
}void MapEditorMainFrame::OnSave(wxCommandEvent& ev)
{
    //TODO save correctly
    if(wxGetApp().isChanged || wxGetApp().levelNameList.size() > 1){
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

void MapEditorMainFrame::OnMerge(wxCommandEvent& ev)
{
    //ディレクトリを指定し、フォーマットに従ってレベルをマージする
    //TODO
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// edit menus
void MapEditorMainFrame::OnUndo(wxCommandEvent& ev)
{
    //TODO
    /*
        処理すべきは
        ・マップアイテムの追加
        ・              の削除
        ・              の設定変更(移動含む)
        くらいかな？（それ以外の処理については無視。要望があれば応える感じ）
    */
    //bool result = 
}
void MapEditorMainFrame::OnRedo(wxCommandEvent& ev)
{
    //TODO REDO
}
void MapEditorMainFrame::OnCut(wxCommandEvent& ev)
{
    //TODO
}
void MapEditorMainFrame::OnCopy(wxCommandEvent& ev)
{
    //TODO デバッグ
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	if(sel->isSelected()){
		//選択中の物がある
		//→記憶する
		wxGetApp().getCopyPasteManager()->copy(*sel);
	}
}
void MapEditorMainFrame::OnPaste(wxCommandEvent& ev)
{
    //TODO デバッグ
	int div = wxGetApp().getViewGridManager()->getZoomDivision();
	if(!wxGetApp().getCopyPasteManager()->paste(div)){
		//失敗
	}
}
void MapEditorMainFrame::OnPreference(wxCommandEvent& ev)
{
    //Call up editor preferences dialog
    EditorPreferencesDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //ファイルに保存 <en> save preference setting to file
        if(!wxGetApp().setting.saveSetting()){
            hpl::error::caution("Fail to save setting as [%s]", wxGetApp().setting.getFilePath().c_str());
        }
        //ペンの作り直し <en> recreate pens and brushes
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
    
    //モード変更
	this->changeEditMode(EditModeType::EM_DRAW);

    //一旦全てチェックをはずします
    this->uncheckModesOnMenu();

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
    //this->closeAllModelessDialogs();

    //ポリゴンタイプダイアログ表示
	this->polyTypeDialog.setupDialog();
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
	this->mediaPaletteDialog.setupDialog();
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
    //保存確認
    //未セーブチェック
    if(!this->askDestructMap()){
        return ;
    }
    SelectLevelDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        int sel = dlg.getSelectLevel();
        wxGetApp().editLevelIndex = sel;
        //ステージ読み込み
//        initLevel();
        loadLevel(sel);
        Refresh();
    }
}
void MapEditorMainFrame::OnLevelInfo(wxCommandEvent& ev)
{
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //設定反映
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
void MapEditorMainFrame::OnPolygonProp(wxCommandEvent& ev)
{
    this->polyPropDialog.setPolyIndex(wxGetApp().popupPolygonIndex);
    this->polyPropDialog.Show(true);
}
void MapEditorMainFrame::OnSetVisualModePlayerPosition(wxCommandEvent& ev)
{
	//wxASSERT(wxGetApp().popupPolygonIndex != NONE);
	//ポリゴンの床の高さを取得
	polygon_data* poly = get_polygon_data(wxGetApp().popupPolygonIndex);
#ifdef __WXDEBUG__
	hpl::error::halt("polygon index was invalid", wxGetApp().popupPolygonIndex);
#endif
	int height = poly->floor_height;
	int mpoint[2];
	wxGetApp().getViewGridManager()->getNewMousePoint(mpoint);
	//ワールド座標に変換
	world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mpoint[0], mpoint[1]);
	wxGetApp().getVisualModeManager()->setPlayerPosition(wpoint.x, wpoint.y, height);
}
