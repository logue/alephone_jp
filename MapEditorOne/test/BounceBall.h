#ifndef _BOUNCE_BALL_
#define _BOUNCE_BALL_

#include "Ball.h"

/**
    ��`�̒��Ŕ��˂���{�[��
*/
class BounceBall: public Ball{
public:
    double speed;
public:

    BounceBall(double x_, double y_, double dx_, double dy_, double size_);
    virtual ~BounceBall(){}

    void step(double scrLeft, double scrTop, double scrRight, double scrBottom);
};

#endif
