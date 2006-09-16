#include "HPLLibMFC.h"

/**
    CString��char*�ɕϊ����܂�
*/
void strToChar(CString& src, char* dest){
    LPWSTR buf = new WCHAR[src.GetLength()];
    LPBOOL ok = new BOOL[1];
	lstrcpy(buf, src);
    wcharToChar(buf, dest);
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

/**
    ������𕪊����܂�
*/
void splitString(CString& src, const char* sep, CStringArray &array){
    int pos;
    
    while(1){
        pos = src.Find(CString(sep));
        if(pos == -1){
            array.Add(src);
            break;
        }else if(pos == 0){
            //continue;
        }else{
            array.Add(src.Left(pos));
        }
        src = src.Mid(pos + (int)strlen(sep));
    }
}


void setIntegerNum(int num, CEdit* edit)
{
    char cstr[256];
    sprintf(cstr, "%d", num);
    edit->SetWindowText(CString(cstr));
}
int getIntegerNum(CEdit* edit)
{
    char cstr[256];
    CString str;
    edit->GetWindowText(str);
    strToChar(str, cstr);
    int num = atoi(cstr);
    return num;
}
void setComboAndIntegerNum(int num, int max,
                           CEdit* edit, CComboBox* cmb)
{
    if(num == -1){
        num = max;
    }
    cmb->SetCurSel(num);
    setIntegerNum(num, edit);
}

void worldToWindow(int worldX, int worldY, POINT* point)
{
    exit(0);
}
