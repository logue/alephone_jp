#ifndef _HPL_ERROR_
#define _HPL_ERROR_
#ifdef WX
#include <wx/wx.h>
#endif

#ifdef __WXDEBUG__

#include <wx/defs.h>
#include <wx/debug.h>

#endif
#ifdef WIN32

#include <windows.h>

#endif


namespace hpl{
namespace error{
    /**
        メッセージを表示します
    */
    void caution(const char* format, ...);

    /**
        メッセージを表示しして異常終了します
    */
    void halt(const char* format, ...);
};
};

#endif
