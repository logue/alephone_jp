#include "MapEditorMainFrame.h"

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// file menus

void MapEditorMainFrame::OnPrint(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPrintPreview(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPrintSetup(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnNew(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnNewLevel(wxCommandEvent& ev)
{
}

void MapEditorMainFrame::OnOpen(wxCommandEvent& WXUNUSED(ev))
{
    //TODO 未セーブチェック

    //file dialog open
    wxFileDialog fileDialog(this, _T("Choose a file"),
        _T("."), _T(""), _T("*.*"));

    if(fileDialog.ShowModal() == wxID_OK){
        wxString path = fileDialog.GetPath();

        //タイトル
        SetTitle(path);
        
        FileSpecifier mapFile = FileSpecifier(path.mb_str());

        //set map file
        set_map_file(mapFile);

        wxGetApp().editLevelIndex = 0;
        build_trig_tables();
        //allocate
        if(dynamic_world == NULL){
            allocate_map_memory();
        }
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
        //ズーム・オフセットを初期化
        wxCommandEvent dummy;
        this->OnZoomDefault(dummy);
        this->OnMoveToCenter(dummy);
        //再描画
        Refresh();
    }
}void MapEditorMainFrame::OnSave(wxCommandEvent& ev)
{
    //TODO save correctly

}
void MapEditorMainFrame::OnSaveAs(wxCommandEvent& ev)
{
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
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// show menus
void MapEditorMainFrame::OnToolDialog(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnZoomIn(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnZoomOut(wxCommandEvent& ev)
{
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
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// mode menus
void MapEditorMainFrame::OnDrawPolygonMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnVisualMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnPolygonTypeMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnFloorHeightMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnCeilingHeightMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnFloorLightMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnCeilingLightMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnMediaMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnFloorTextureMode(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnCeilingTextureMode(wxCommandEvent& ev)
{
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// special menus
void MapEditorMainFrame::OnJumpLevel(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnLevelInfo(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnObjectPlacement(wxCommandEvent& ev)
{
}
void MapEditorMainFrame::OnTerminalViewer(wxCommandEvent& ev)
{
}

