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
    WCHAR*��char*�ɕϊ����܂��B
*/
void wcharToChar(WCHAR* src, char* dest){
    DWORD len = WideCharToMultiByte(CP_ACP, 0,
        src, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0,
        src, -1, dest, len, NULL, NULL);
}

/**
    char*��WCHAR*�ɕϊ����܂�
*/
void charToWChar(char* src, WCHAR* dest){
    DWORD len = MultiByteToWideChar(CP_ACP, 0,
        src, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP,0,
        src, -1, dest, len);
}

//�t�@�C���I���_�C�A���O
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
            // wParam �� TRUE  �Ȃ�p�X��
            //          FALSE �Ȃ�pidl
            SendMessage(hwnd, BFFM_SETSELECTION, TRUE,
                (LPARAM)currentDir);
            break;
        default:
            break;
    }
    return 0;
}

//�o�̓t�H���_�I��
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
    �t�@�C�����J���đS���x���̖��̂��擾
    @return �擾�������̗̂�
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

//���������ăE�C���h�E����
//@return ���s������
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
        //�}�b�v�t�@�C���w��
        {
            std::string name = getFileName(hwnd);
            charToWChar((char*)name.c_str(), wbuf);
            MessageBox(hwnd, wbuf, TEXT("map"), MB_OK);
        }

        //�}�b�v�ǂݍ���
        //�C���f�b�N�X�擾

        //�o�͐�w��
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

    //�E�C���h�E�쐬
    /*
    HWND hwnd = createInitWindow(hInstance);
    if(hwnd == 0){
        return -1;
    }
    */
//    allocate_player_memory();

    HWND hwnd = NULL;
    wchar_t wbuf[MAX_PATH + 100];
    //�}�b�v�t�@�C���w��
    std::string fname = getFileName(hwnd);
    if(fname == ""){
        MessageBox(hwnd, TEXT("Task was canceled"), TEXT("canceled"), MB_OK);
    }
//    charToWChar((char*)name.c_str(), wbuf);
//    MessageBox(hwnd, wbuf, TEXT("map"), MB_OK);
//    createDoubleBuffer();
    build_trig_tables();

    allocate_map_memory();
    //�}�b�v�ǂݍ���
    if(!loadMapFromFile(fname.c_str())){
        char buf[MAX_PATH+100];
        sprintf(buf, "open error with [%s]", fname.c_str());
        charToWChar(buf, wbuf);
        MessageBox(hwnd, wbuf, TEXT("open error"), MB_OK);
        return -1;
    }

    initialize_map_for_new_level();
    load_level_from_map(0);

    //�o�͐�w��
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

    //�C���f�b�N�X�擾
    std::vector<std::string> names = getLevelList();
    //���x�������ɕۑ����Ă���
    //�t�@�C������
    //L[index]_name.sceA
    //�̃t�H�[�}�b�g�ɏ]��
//    dynamic_world->map_index_count = 0;
    for(int i = 0; i < (int)names.size(); i ++){
        char buf[MAX_PATH];
        //�ǂݍ���
        bool check = load_level_from_map(i);
        if(!check){
            MessageBox(hwnd, TEXT("failed"), TEXT("load error"), MB_OK);
            return -1;
        }
        sprintf(buf, "%d", i);
        std::string numstr = hpl::string::appendFrontString(
            std::string(buf), 2, std::string("0"));
        for(int n = 0; n < (int)names.size(); n ++){
            //�\���s�̕�����u��������
            if(names[i][n] == '?' || names[i][n] == ';' || names[i][n] == ':'){
                names[i][n] = '-';
            }
        }
        sprintf(buf, "%sL%s%s.sceA", dir.c_str(),
            numstr.c_str(), names[i].c_str());
        //�ۑ�
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