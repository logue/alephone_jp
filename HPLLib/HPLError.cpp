#include "HPLError.h"
#include "stdarg.h"
#include <cstdio>
#include <cstdlib>

const int BUF_MAX = 1024;

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

#ifdef __WXDEBUG__
    wxMessageBox(wxConvCurrent->cMB2WX(message));
#endif
#ifdef WIN32
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
#ifdef __WXDEBUG__
    wxASSERT(false);
#else
    exit(-1);
#endif
}
