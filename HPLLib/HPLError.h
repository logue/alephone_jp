#ifndef _HPL_ERROR_
#define _HPL_ERROR_

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
