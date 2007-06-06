#ifndef _HPL_ERROR_
#define _HPL_ERROR_

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
