#include <windows.h>
//#include <commctrl.h>
#include <shlobj.h>
#include <string>
#include <vector>
#include "HPLLib/HPLAlephLib.h"
#include "platforms.h"
#include "game_wad.h"
#include "FileHandler.h"
#include "map.h"
////////////////////////////////
static WCHAR TITLE[] = TEXT("MapDamagerOne");
wchar_t currentDir[MAX_PATH];

////////////////////////////////

/////////////////////////////////
// prototypes

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

////////////////////////////////
// codes
static bool loadMapFromFile(const char* filename){
    FileSpecifier mapFile = FileSpecifier(filename);
    //set map file
    set_map_file(mapFile);
    return true;
}

/**
    WCHAR*をchar*に変換します。
*/
void wcharToChar(WCHAR* src, char* dest){
    DWORD len = WideCharToMultiByte(CP_ACP, 0,
        src, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0,
        src, -1, dest, len, NULL, NULL);
}

/**
    char*をWCHAR*に変換します
*/
void charToWChar(char* src, WCHAR* dest){
    DWORD len = MultiByteToWideChar(CP_ACP, 0,
        src, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP,0,
        src, -1, dest, len);
}

//ファイル選択ダイアログ
std::string getFileName(HWND hwnd)
{
    WCHAR strCustom[256] = TEXT("before files\0*.*\0\0");
    std::string fname;
    wchar_t buf[MAX_PATH] =TEXT("="), fileTitle[256];
    char cbuf[MAX_PATH];

    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.lpstrTitle = TEXT("Select Source Map File");
    ofn.lpstrFilter = TEXT("Any format {*.*}\0*.*\0\0");
//    ofn.lpstrCustomFilter = strCustom;
//    ofn.nMaxCustFilter = 256;
//    ofn.nFilterIndex = 0;
    ofn.lpstrFile = buf;
    ofn.nMaxFile = MAX_PATH;
//    ofn.lpstrFileTitle = fileTitle;
//    ofn.nMaxFileTitle = 256;
    ofn.Flags = OFN_FILEMUSTEXIST;
//    ofn.lpstrDefExt = TEXT("*");

    if(!GetOpenFileName(&ofn)){
        return std::string("");
    }

    //wchar->char
    wcharToChar(buf, cbuf);
    fname = std::string(cbuf);
    return fname;
}

int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData)
{
    switch (uMsg)
    {
        case BFFM_INITIALIZED:
            // wParam が TRUE  ならパス名
            //          FALSE ならpidl
            SendMessage(hwnd, BFFM_SETSELECTION, TRUE,
                (LPARAM)currentDir);
            break;
        default:
            break;
    }
    return 0;
}

//出力フォルダ選択
std::string getDestDirName(HWND hwnd)
{
    std::string dir;

    GetCurrentDirectory(MAX_PATH, currentDir);

    BROWSEINFO bi;
    wchar_t szDir[MAX_PATH]=TEXT(" ");
    LPITEMIDLIST pidl;
    LPMALLOC pMalloc;

    if(SUCCEEDED(SHGetMalloc(&pMalloc))){
        ZeroMemory(&bi, sizeof(bi));
        bi.hwndOwner = hwnd;
        bi.pidlRoot = 0;
        bi.pszDisplayName = 0;
        bi.lpszTitle = TEXT("Select Destination Directory");
        bi.ulFlags = BIF_RETURNONLYFSDIRS;
        bi.lpfn = BrowseCallbackProc;

        pidl = SHBrowseForFolder(&bi);

        if(pidl){
            if(SHGetPathFromIDList(pidl, szDir)){
                //wchar->char
                char cbuf[MAX_PATH];
                wcharToChar(szDir, cbuf);
                dir = std::string(cbuf);
            }
        }
        pMalloc->Free(pidl);
    }
    pMalloc->Release();

    return dir;
}

/*
    ファイルを開いて全レベルの名称を取得
    @return 取得した名称の列
*/
std::vector<std::string> getLevelList()
{
    //
    initialize_map_for_new_level();
    std::vector<std::string> names;
    char cstr[MAX_PATH];
    {
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
    }
    return names;
}

//初期化してウインドウ作るよ
//@return 失敗時負数
HWND createInitWindow(HINSTANCE hInstance)
{
    WNDCLASS winc;

    winc.style = CS_HREDRAW| CS_VREDRAW;
    winc.lpfnWndProc = WndProc;
    winc.cbClsExtra = winc.cbWndExtra = 0;
    winc.hInstance = hInstance;
    winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winc.hCursor = LoadCursor(NULL, IDC_ARROW);
    winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    winc.lpszMenuName = NULL;
    winc.lpszClassName = TITLE;

    if(!RegisterClass(&winc))
        return 0;
    HWND hwnd = CreateWindow(TITLE, TITLE,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);
    return hwnd;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if(msg == WM_DESTROY){
        PostQuitMessage(0);
    }else if(msg == WM_CREATE){
        return 0;
    }else if(msg == WM_RBUTTONDOWN){
        wchar_t wbuf[MAX_PATH];
        //マップファイル指定
        {
            std::string name = getFileName(hwnd);
            charToWChar((char*)name.c_str(), wbuf);
            MessageBox(hwnd, wbuf, TEXT("map"), MB_OK);
        }

        //マップ読み込み
        //インデックス取得

        //出力先指定
        {
            std::string dir = getDestDirName(hwnd);
            charToWChar((char*)dir.c_str(), wbuf);
            MessageBox(hwnd, wbuf, TEXT("dir"), MB_OK);
        }
    }else{
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance ,
            HINSTANCE hPrevInstance ,
		    PSTR lpCmdLine ,
		    int nCmdShow ) 
{
    MSG msg;

    //ウインドウ作成
    /*
    HWND hwnd = createInitWindow(hInstance);
    if(hwnd == 0){
        return -1;
    }
    */
//    allocate_player_memory();

    HWND hwnd = NULL;
    wchar_t wbuf[MAX_PATH + 100];
    //マップファイル指定
    std::string fname = getFileName(hwnd);
    if(fname == ""){
        MessageBox(hwnd, TEXT("Task was canceled"), TEXT("canceled"), MB_OK);
    }
//    charToWChar((char*)name.c_str(), wbuf);
//    MessageBox(hwnd, wbuf, TEXT("map"), MB_OK);
//    createDoubleBuffer();
    build_trig_tables();

    allocate_map_memory();
    //マップ読み込み
    if(!loadMapFromFile(fname.c_str())){
        char buf[MAX_PATH+100];
        sprintf(buf, "open error with [%s]", fname.c_str());
        charToWChar(buf, wbuf);
        MessageBox(hwnd, wbuf, TEXT("open error"), MB_OK);
        return -1;
    }

    initialize_map_for_new_level();
    load_level_from_map(0);

    //出力先指定
    std::string dir;
    {
        dir = getDestDirName(hwnd);
        if(dir == std::string("")){
            MessageBox(hwnd, TEXT("Task was canceled"),
                TEXT("open error"), MB_OK);
            return -1;
        }
        if(dir[dir.length()-1] != '\\'){
            dir += "\\";
        }
//        charToWChar((char*)dir.c_str(), wbuf);
//        MessageBox(hwnd, wbuf, TEXT("dir"), MB_OK);
    }

    //インデックス取得
    std::vector<std::string> names = getLevelList();
    //レベルを順に保存していく
    //ファイル名は
    //L[index]_name.sceA
    //のフォーマットに従う
//    dynamic_world->map_index_count = 0;
    for(int i = 0; i < (int)names.size(); i ++){
        char buf[MAX_PATH];
        //読み込み
        bool check = load_level_from_map(i);
        if(!check){
            MessageBox(hwnd, TEXT("failed"), TEXT("load error"), MB_OK);
            return -1;
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
        sprintf(buf, "%sL%s%s.sceA", dir.c_str(),
            numstr.c_str(), names[i].c_str());
        //保存
        MapIndexList.clear();
        MapIndexList.push_back(0);
        dynamic_world->map_index_count = 1;
//        dynamic_world->platform_count = PlatformList.size();
        if(!save_level(buf)){
            char cbuf[MAX_PATH+100];
            sprintf(cbuf, "save error with [%s]", buf);
            charToWChar(cbuf, wbuf);
            MessageBox(hwnd, wbuf, TEXT("save error"), MB_OK);
        }
    }

    MessageBox(hwnd, TEXT("saving completed"), TEXT("complete"), MB_OK);
/*    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	return msg.wParam;
    */
    return 0;
}