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
    //allocate
    if(dynamic_world == NULL){
		build_trig_tables();
        allocate_map_memory();
    }
    //ズーム・オフセットを初期化
    wxCommandEvent dummy;
    this->OnZoomDefault(dummy);
    this->OnMoveToCenter(dummy);

	
    wxGetApp().getStockManager()->resetDeletes();
	wxGetApp().selectData.clear();

    wxGetApp().isChanged = false;
	
    //レベル一覧削除
    wxGetApp().levelNameList.clear();
    initialize_map_for_new_level();
    //データの初期化
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MAX);
    wxGetApp().getViewGridManager()->setViewHeightMin(SHRT_MIN);

	///dynamic_world->map_index_count = 1;
}

/**
    ダイアログを出して編集中のマップを破壊してよいかを聞き出します。
    @param ユーザからOKが出れば真。出なければ偽。
        また、編集されてなければ真が返る
*/
int MapEditorMainFrame::askDestructMap()
{
    if(wxGetApp().isChanged){
        wxMessageDialog dlg(this,
			_T("Map has been modified. Are you sure that delete this and create new one?"),
			_T("are you sure? :o"), wxYES_NO | wxCANCEL);
        return dlg.ShowModal();
    }
    return wxID_NO;
}

void MapEditorMainFrame::OnNew(wxCommandEvent& ev)
{
#ifdef MAP_VIEWER
#else
	int result = this->askDestructMap();
	if(result == wxID_YES){
		//保存します
		wxCommandEvent dummy;
		OnSaveAs(dummy);
	}else if(result = wxID_NO){
	}else{
		//cancel
		return;
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

#endif
    Refresh();
}

void MapEditorMainFrame::loadLevel(int i){

    bool check = load_level_from_map(wxGetApp().editLevelIndex);
    if(!check){
        wxMessageBox(_T("failed"));
    }
    //セットアップ
    wxGetApp().getStockManager()->resetDeletes();

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

	//選択状態表を初期化
	this->updateMapItems();
}
void MapEditorMainFrame::OnOpen(wxCommandEvent& ev)
{
	int result = this->askDestructMap();
	if(result == wxID_YES){
		//保存します
		wxCommandEvent dummy;
		OnSaveAs(dummy);
	}else if(result = wxID_NO){
	}else{
		//cancel
		return;
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

        //再描画
        Refresh();

		wxGetApp().isChanged = false;

    }
}void MapEditorMainFrame::OnSave(wxCommandEvent& ev)
{
    //TODO save correctly
	if(PhysicsModelLoaded || wxGetApp().levelNameList.size() > 1){
		hpl::error::caution("This map seems to be merged. This editor cannot save as merged one. Please save as another file");
        OnSaveAs(ev);
    }else{
		hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
		hpl::aleph::map::deleteMapItems(
			*smgr->getDelPoints(),
			*smgr->getDelLines(),
			*smgr->getDelPolygons(),
			*smgr->getDelSides(),
			*smgr->getDelObjects());
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
		hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
		
		hpl::aleph::map::deleteMapItems(
			*smgr->getDelPoints(),
			*smgr->getDelLines(),
			*smgr->getDelPolygons(),
			*smgr->getDelSides(),
			*smgr->getDelObjects());
		
		//dynamic_world->map_index_count = 1;

		//インデックスが正しいかどうか検査
		for(int i = 0; i < (int)EndpointList.size(); i ++){
			endpoint_data* ep = get_endpoint_data(i);
			wxASSERT(ep->supporting_polygon_index >= 0);
		}
		for(int i = 0; i < (int)LineList.size(); i ++){
			line_data* line = get_line_data(i);
			wxASSERT(line->clockwise_polygon_owner >= NONE);
			wxASSERT(line->clockwise_polygon_side_index >= NONE);
			wxASSERT(line->counterclockwise_polygon_owner >= NONE);
			wxASSERT(line->counterclockwise_polygon_side_index >= NONE);
			for(int j = 0; j < 2; j ++){
				wxASSERT(line->endpoint_indexes[j] >= 0);
			}
		}
		for(int i = 0; i < (int)PolygonList.size(); i ++){
			polygon_data* poly = get_polygon_data(i);
			wxASSERT(poly->first_object >= NONE);
			for(int j = 0; j < poly->vertex_count; j ++){
				wxASSERT(poly->adjacent_polygon_indexes[j] >= NONE);
				wxASSERT(poly->endpoint_indexes[j] >= 0);
				wxASSERT(poly->line_indexes[j] >= 0);
				wxASSERT(poly->side_indexes[j] >= NONE);
			}
		}
		for(int i = 0; i < (int)SideList.size(); i ++){
			side_data* side = get_side_data(i);
			wxASSERT(side->line_index >= 0);
			wxASSERT(side->polygon_index >= 0);
		}

		for(int i = 0; i < (int)PlatformList.size(); i ++){
			platform_data* platform = &PlatformList[i];
			wxASSERT(platform->polygon_index >= 0);
		}
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
void MapEditorMainFrame::OnSavePhysicsFile(wxCommandEvent& ev)
{
	//TODO 抽出しているPhysicsFilesを保存
	if(!PhysicsModelLoaded){
		//読み込まれていない
		hpl::error::caution("No physics data included in this map");
	}else{
		//読み込まれている
		std::string str("P0%1d_%s.phyA");
		int levelIndex = wxGetApp().editLevelIndex;
		if(levelIndex >= 10){
			str = std::string("P%2d_%s.phyA");
		}
		wxString fname = getString(str.c_str(),
			levelIndex, wxGetApp().levelNameList[levelIndex].c_str());

		//ファイル出力先ダイアログ
		wxString wildcard(_T("AlephOne physics file data(*.phyA)|*.phyA|Any file|*.*"));
	    int style = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
		wxFileDialog dlg(this, wxString(_T("Save at...")), 
			wxString(_T("")), fname, wildcard,
			style);
		if(dlg.ShowModal() == wxID_OK){
			//
			fname = dlg.GetPath();
		
			export_definition_structures(fname.mb_str());
		}
			
	}
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
	hpl::aleph::map::HPLSelectData dummy1;
	hpl::aleph::map::HPLRealMapData dummy2;
	hpl::aleph::map::HPLActionItem act = hpl::aleph::map::HPLActionItem(0, dummy1, dummy2);
	hpl::aleph::map::HPLDoneHistory* dmgr = wxGetApp().getDoneHistoryManager();
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

	if(dmgr->getIndex() > 0){
		bool result = dmgr->back(&act);
		if(!result){
			dmgr->forward(&act);
		}else if(act.type == hpl::aleph::map::ActionType::Move){
			//もう一度取得を試みる
			result = dmgr->back(&act);
		}
		if(result){
			if(act.type == hpl::aleph::map::ActionType::None ||
				act.type == hpl::aleph::map::ActionType::Move)
			{
				//移動を元に戻す
				for(int i = 0; i < (int)act.selectData.getSelPoints()->size(); i ++){
					int index = act.selectData.getSelPoints()->at(i).index;
					endpoint_data* ep = get_endpoint_data(index);
					//TODO 削除・追加のUndo機能も実装しよう。
					//これだけだと削除されている場合エラーになる
					if(smgr->isDeletePoint(index) || ep == NULL){
						//TODO 応急処置！
						continue;
					}
					ep->vertex = act.pointVertexMap[index];
				}
				for(int i = 0; i < (int)act.selectData.getSelObjects()->size(); i ++){
					int index = act.selectData.getSelObjects()->at(i).index;
					if(smgr->isDeleteObject(index) || index >= (int)SavedObjectList.size()){
						continue;
					}
					map_object* obj = &SavedObjectList[index];
					obj->location = act.objectLocationMap[index];
				}
				//lines
				for(int i = 0; i < (int)act.selectData.getSelLines()->size(); i ++){
					int index = act.selectData.getSelLines()->at(i).index;
					line_data* line = get_line_data(index);
					for(int j = 0; j < 2; j ++){
						int epIndex = line->endpoint_indexes[j];
						get_endpoint_data(epIndex)->vertex = act.pointVertexMap[epIndex];
					}
				}

				//polygons
				for(int i = 0; i < (int)act.selectData.getSelPolygons()->size(); i ++){
					int index = act.selectData.getSelPolygons()->at(i).index;
					polygon_data* poly = get_polygon_data(index);
					for(int j = 0; j < poly->vertex_count; j ++){
						int epIndex = poly->endpoint_indexes[j];
						get_endpoint_data(epIndex)->vertex = act.pointVertexMap[epIndex];
					}
				}

			}else{
				hpl::error::halt("This function is disable");
			}

		}else{
	#ifdef __WXDEBUG__
			hpl::error::caution("Undo失敗。index=%d", dmgr->getIndex());
	#endif
		}

		//更新
		this->updateMapItems();
	}
}
void MapEditorMainFrame::OnRedo(wxCommandEvent& ev)
{
    //TODO REDO
}
void MapEditorMainFrame::OnCut(wxCommandEvent& ev)
{
    //TODO コピーして削除
	OnCopy(ev);
	OnDelete(ev);
}
void MapEditorMainFrame::OnDelete(wxCommandEvent& ev)
{
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();

	if(sel->isSelected()){
		//TODO 選択対象を記録してUndoに用いる
		//

#ifdef MAP_VIEWER
		//objects
		for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
			smgr->deleteObject(sel->getSelObjects()->at(i).index);
		}
#else
		//objects
		for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
			smgr->deleteObject(sel->getSelObjects()->at(i).index);
		}
		//選択対象を削除対象とする
		for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
			hpl::aleph::map::SelPoint* opt = &sel->getSelPoints()->at(i);
			smgr->deletePoint(opt->index);
		}
		//lines
		for(int i = 0; i < (int)sel->getSelLines()->size(); i ++){
			smgr->deleteLine(sel->getSelLines()->at(i).index);
		}
		/*
		//sides
		for(int i = 0; i < sel->getSelSides()->size(); i ++){
			smgr->deleteSide(sel->getSelSides()->at(i).index);
		}*/
		//polygons
		for(int i = 0; i < (int)sel->getSelPolygons()->size(); i ++){
			smgr->deletePolygon(sel->getSelPolygons()->at(i).index);
		}
#endif
		sel->clear();
		//削除が実行されたのでコンボ更新
		this->updateMapItems();
	}
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
	hpl::aleph::map::HPLSelectData* sel = &wxGetApp().selectData;
	int div = wxGetApp().getViewGridManager()->getZoomDivision();
	if(wxGetApp().getCopyPasteManager()->paste(div, sel)){
		//成功
		//追加されたのでコンボを更新
		this->updateMapItems();
	}else{
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
//    this->pointPropDialog.Show(false);
    //this->polyPropDialog.Show(false);
    //this->linePropDialog.Show(false);
//    this->sidePropDialog.Show(false);
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
	int result = this->askDestructMap();
	if(result == wxID_YES){
		//保存します
		wxCommandEvent dummy;
		OnSaveAs(dummy);
	}else if(result = wxID_NO){
	}else{
		//cancel
		return;
	}

	SelectLevelDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        int sel = dlg.getSelectLevel();
        wxGetApp().editLevelIndex = sel;
        //ステージ読み込み
//        initLevel();
        loadLevel(sel);
		this->updateMapItems();
        Refresh();
    }
}
void MapEditorMainFrame::OnLevelInfo(wxCommandEvent& ev)
{
	//編集設定
	wxGetApp().isChanged = true;
    LevelInfoDialog dlg;
    dlg.Create(this, wxID_ANY);
    if(dlg.ShowModal() == wxID_OK){
        //設定反映
    }
}
void MapEditorMainFrame::OnObjectPlacement(wxCommandEvent& ev)
{
	//編集設定
	wxGetApp().isChanged = true;
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
	//編集設定
	wxGetApp().isChanged = true;
    //this->linePropDialog.setLineIndex(wxGetApp().popupLineIndex);
    //this->linePropDialog.Show(true);
	int lineIndex = wxGetApp().popupLineIndex;
	line_data* org = get_line_data(lineIndex);
	wxASSERT(org);
	LinePropDialog dlg;
	dlg.Create(this, wxID_ANY, lineIndex);
	if(dlg.ShowModal() == wxID_OK){
#ifdef MAPVIEWER
#else
		*org = dlg.getLine();
#endif
		//memcpy(org, &data, sizeof(line_data));
	}
}
void MapEditorMainFrame::OnClockwiseSide(wxCommandEvent& ev)
{
	//編集設定
	wxGetApp().isChanged = true;
    //this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->clockwise_polygon_side_index);
    //this->sidePropDialog.Show(true);
	int index = get_line_data(wxGetApp().popupLineIndex)->clockwise_polygon_side_index;
	this->openSidePropDialog(index);
}
void MapEditorMainFrame::openSidePropDialog(int sideIndex)
{
	if(hpl::aleph::map::isValidIndex(sideIndex, SideList.size())){
		SidePropDialog dlg;
		dlg.Create(this, wxID_ANY, sideIndex);
		if(dlg.ShowModal() == wxID_OK){
#ifdef MAPVIEWER
#else
			side_data data = dlg.getSide();
			side_data* org = get_side_data(sideIndex);
			*org = data;
#endif
		}
	}else{
		hpl::error::caution("invalid side index[%d]", sideIndex);
	}
}

void MapEditorMainFrame::OnCounterclockwiseSide(wxCommandEvent& ev)
{
	//編集設定
	wxGetApp().isChanged = true;
    //TODO
//    this->sidePropDialog.setIndex(get_line_data(wxGetApp().popupLineIndex)->counterclockwise_polygon_side_index);
//    this->sidePropDialog.Show(true);
	int index = get_line_data(wxGetApp().popupLineIndex)->counterclockwise_polygon_side_index;
	this->openSidePropDialog(index);
}
void MapEditorMainFrame::OnPointProp(wxCommandEvent& ev)
{
	//編集設定
	wxGetApp().isChanged = true;
	PointPropDialog dlg;
	int endpointIndex = wxGetApp().popupEndpointIndex;
	dlg.Create(this, wxID_ANY, endpointIndex);
	if(dlg.ShowModal() == wxID_OK){
#ifdef MAPVIEWER
#else
		endpoint_data data = dlg.getEndpoint();
		endpoint_data* org = get_endpoint_data(endpointIndex);
		obj_copy(*org, data);
#endif
	}
}

/**
	ポリゴンプロパティメニュー
*/
void MapEditorMainFrame::OnPolygonProp(wxCommandEvent& ev)
{
	//編集設定
	wxGetApp().isChanged = true;
	int polyIndex = wxGetApp().popupPolygonIndex;
	polygon_data* org = get_polygon_data(polyIndex);
	wxASSERT(org);
	PolygonPropDialog dlg;
	dlg.Create(this, wxID_ANY, polyIndex);
	if(dlg.ShowModal() == wxID_OK){
		polygon_data data = dlg.getPolygon();
		//コピー
		//memcpy(org, &data, sizeof(polygon_data));
#ifdef MAPVIEWER
#else
		*org = data;
#endif
	}
}
void MapEditorMainFrame::OnSetVisualModePlayerPosition(wxCommandEvent& ev)
{
	if(!hpl::aleph::map::isValidIndex(wxGetApp().popupPolygonIndex, PolygonList.size())){
		return;
	}
	//ポリゴンの床の高さを取得
	polygon_data* poly = get_polygon_data(wxGetApp().popupPolygonIndex);

	int height = poly->floor_height;
	int mpoint[2];
	wxGetApp().getViewGridManager()->getNewMousePoint(mpoint);
	//ワールド座標に変換
	world_point2d wpoint = wxGetApp().getWorldPointFromViewPoint(mpoint[0], mpoint[1]);
	wxGetApp().getVisualModeManager()->setPlayerPosition(wpoint.x, wpoint.y, height);
}

