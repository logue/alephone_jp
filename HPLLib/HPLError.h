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
        ���b�Z�[�W��\�����܂�
    */
    void caution(const char* format, ...);

    /**
        ���b�Z�[�W��\�������Ĉُ�I�����܂�
    */
    void halt(const char* format, ...);
};
};

#endif
