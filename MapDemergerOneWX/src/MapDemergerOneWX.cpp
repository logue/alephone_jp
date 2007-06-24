#include "MapDemergerOneWX.h"
#include "HPLLib/HPLAlephLib.h"
#include "platforms.h"
#include "game_wad.h"
#include "FileHandler.h"
#include "map.h"
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <string>
#include <vector>

IMPLEMENT_APP(MapDemergerOneWX)

//const int MAX_PATH = 260;

static std::vector<std::string> getLevelList()
{
    //
    initialize_map_for_new_level();
    std::vector<std::string> names;
    char cstr[MAX_PATH];
    short index = 0;
    struct entry_point ep;
    int type = 3;
    int num = 0;
    while(get_indexed_entry_point(&ep, &index, type)){
        sprintf(cstr, "%d,", ep.level_number);
        std::string str = std::string(ep.level_name);
        names.push_back(str);
        num ++;
    }
    if(num == 0){
        //theApp.LevelNameList.Add(CString("unmerged"));
        names.push_back(std::string("unmerged"));
    }
    return names;
}

bool MapDemergerOneWX::OnInit()
{
    //ファイル選択ダイアログ
    wxString path = ::wxFileSelector();
    if(path.empty()){
        wxMessageBox(_T("Operation canceld by user. exit"));
        return false;
    }
    FileSpecifier mapFile = FileSpecifier(path.mb_str());
    //set map file
    set_map_file(mapFile);

    build_trig_tables();

    allocate_map_memory();
    initialize_map_for_new_level();
    load_level_from_map(0);

    wxString dirPath = wxDirSelector();
    if(dirPath.empty()){
        wxMessageBox(_T("Operation canceled by user. exit"));
        return false;
    }
    wxString last = dirPath.Right(1);
    if(last != _T("\\") && last != _T("/")){
        dirPath.Append(_T("/"));
    }
#ifdef MAC
    //TODO separator in MacOSX may not be "/" nor "\".
#endif

    //インデックス取得
    std::vector<std::string> names = getLevelList();
    for(int i = 0; i < (int)names.size(); i ++){
        char buf[MAX_PATH];
        //読み込み
        if(!load_level_from_map(i)){
            wxString str = wxConvertMB2WX("Fail to load map");
            str.Append(wxString(wxConvertMB2WX(names[i].c_str())));
            wxMessageBox(str);
            continue;
        }
        sprintf(buf, "%d", i);
        std::string numstr = hpl::string::appendFrontString(
            std::string(buf), 2, std::string("0"));
        for(int n = 0; n < (int)names.size(); n ++){
            //表示不可の文字を置き換える
            if(names[i][n] == '?' || names[i][n] == ';' || names[i][n] == ':'){
                names[i][n] = '-';
            }
        }
        sprintf(buf, "%sL%s%s.sceA", dirPath.mb_str(),
            numstr.c_str(), names[i].c_str());
        if(!save_level(buf)){
            wxString str = wxConvertMB2WX("Fail to save map:[");
            str.Append(wxString(wxConvertMB2WX(buf)));
            str.Append(_T("] If you want, push cancel button to interrupt operation. If not, push ok button to continue."));
            if(wxMessageBox(_T("Fail to save map:"), _T("Message"), wxOK | wxCANCEL ) == wxID_OK){
                continue;
            }else{
                return false;
            }
        }
    }

    wxMessageBox(_T("All convertion completed"));
    return false;
}