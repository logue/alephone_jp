#include "HPLError.h"
#include "stdarg.h"

const int BUF_MAX = 1024;

#ifdef WX
#include <wx/wx.h>
#elif define(WIN32)
#include <windows.h>
#endif

/**
    メッセージを表示します
*/
void hpl::error::caution(const char* format, ...)
{
    char message[BUF_MAX];
    va_list maker;
    va_start(maker, format);
    vsprintf(message, format, maker);
//    int len = strlen(message);

#ifdef WX
#ifdef UNICODE/*
    wchar_t wmsg[BUF_MAX];
    size_t wlen = wxMBConv::MB2WC(wmsg, message, BUF_MAX);*/
    wxMessageBox(wxConvCurrent->cMB2WX(message));
#else
    wxMessageBox(message);
#endif
#elif define(WIN32)
//    MessageBox(NULL, 
#endif
    fprintf(stderr, message);
}

/**
    メッセージを表示しして異常終了します
*/
void hpl::error::halt(const char* format, ...)
{
    char message[BUF_MAX];
    va_list maker;
    va_start(maker, format);
    vsprintf(message, format, maker);
    caution(message);
    exit(-1);
}
