#include "HPLLibMFC.h"

/**
    CString‚ðchar*‚É•ÏŠ·‚µ‚Ü‚·
*/
void strToChar(CString& src, char* dest){
    //LPWSTR buf = new WCHAR[src.GetLength()];
	strcpy(dest, CT2A(src));
//    delete temp;
    //delete buf;
}

/**
    WCHAR*‚ðchar*‚É•ÏŠ·‚µ‚Ü‚·B
*/
void wcharToChar(WCHAR* src, char* dest){
    DWORD len = WideCharToMultiByte(CP_ACP, 0,
        src, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0,
        src, -1, dest, len, NULL, NULL);
}

/**
    char*‚ðWCHAR*‚É•ÏŠ·‚µ‚Ü‚·
*/
void charToWChar(char* src, WCHAR* dest){
    DWORD len = MultiByteToWideChar(CP_ACP, 0,
        src, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP,0,
        src, -1, dest, len);
}

/**
    •¶Žš—ñ‚ð•ªŠ„‚µ‚Ü‚·
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

void setStatusBar(int index, CString str)
{
    CFrameWnd* wnd = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CStatusBar* status = (CStatusBar*)wnd->GetMessageBar();
    status->SetPaneText(index, str);
}


//load informations
void loadInformations(const char* filename, int max, 
                             Information *informations)
{
    ifstream is;
    is.open(filename);
    if(!is.is_open()){
        CString errMsg = CString("Couldn't open:");
        errMsg += L"[" + CString(filename) + L"]";
        MessageBox(NULL, errMsg, L"Error", MB_OK);
        exit(-1);
    }
    char cstr[256];
    int count = 0;
    while(is.getline(cstr, sizeof(cstr)) && count < max){
        if(strcmp(cstr, "") == 0){
            continue;
        }
        informations[count].jname = CString(cstr);
        count ++;
    }
    is.close();
}

//draw surface to DC.
//surface have "Marathon" palette indexes.
void drawSurfaceByPalette(CDC* cdc, SDL_Surface* surface, SDL_Color* palette,
                          CRect& destRect)
{
    CDC memDC;
    memDC.CreateCompatibleDC(cdc);
    
    if(surface){
        CBitmap bitmap;
        SDL_LockSurface(surface);
        
        double perspective = (double)surface->w / surface->h;
        if(surface->w > surface->h){
            destRect.bottom = (LONG)(destRect.top + destRect.Height() / perspective);
        }else{
            destRect.right = (LONG)(destRect.left + destRect.Width() * perspective);
        }

        bitmap.CreateCompatibleBitmap(cdc, surface->w, surface->h);
        memDC.SelectObject(bitmap);

        for(int x = 0; x < surface->w; x ++){
            for(int y = 0; y < surface->h; y ++){
                Uint32 pixel = getpixel(surface, x, y);
                memDC.SetPixel(x, y, RGB(palette[pixel].b, palette[pixel].g, palette[pixel].r));
            }
        }
        SDL_UnlockSurface(surface);

        /*    cdc->BitBlt(destRect.left, destRect.top,
            destRect.Width(), destRect.Height(),
            &memDC, 0, 0, SRCCOPY);*/
        cdc->StretchBlt(destRect.left, destRect.top,
            destRect.Width(), destRect.Height(),
            &memDC, 0, 0, surface->w, surface->h, SRCCOPY);
        /*::StretchBlt(cdc->m_hDC, destRect.left, destRect.top,
            destRect.Width(), destRect.Height(),
            memDC.m_hDC, 0, 0, surface->w, surface->h, SRCCOPY);
        */
        bitmap.DeleteObject();
    }
        memDC.DeleteDC();
}

void copySurfaceToBitmap(CDC* cdc, CBitmap* dest, SDL_Surface* surface, SDL_Color* palette)
{
    CDC memDC;
    memDC.CreateCompatibleDC(cdc);
    CBitmap* old = memDC.SelectObject(dest);
    if(surface){
        SDL_LockSurface(surface);
        
        for(int x = 0; x < surface->w; x ++){
            for(int y = 0; y < surface->h; y ++){
                Uint32 pixel = getpixel(surface, x, y);
                memDC.SetPixel(x, y, RGB(palette[pixel].b, palette[pixel].g, palette[pixel].r));
            }
        }
        SDL_UnlockSurface(surface);
    }
    memDC.SelectObject(old);
    memDC.DeleteDC();
}
