#ifndef _HPL_MATH_
#define _HPL_MATH_

namespace hpl{
namespace aleph{
namespace math{
    /**
        get sign of num
    */
    template<class T>
    int sgn(T n)
    {
        if( n > 0){
            return 1;
        }else if( n < 0){
            return -1;
        }else{
            return 0;
        }
    }
    template<class T>
    bool isPointInRect(T px, T py, 
                              T rx0, T ry0,
                              T rx1, T ry1)
    {
        T left = (rx0<rx1?rx0:rx1);
        T right = (rx0<rx1?rx1:rx0);
        T top = (ry0<ry1?ry0:ry1);
        T bottom = (ry0<ry1?ry1:ry0);

        if( left <= px && px <= right &&
        top <= py && py <= bottom){
            return true;
        }
        return false;
    }

};
};
};
#endif
