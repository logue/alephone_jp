#include "BounceBall.h"
#include <cmath>

BounceBall::BounceBall(double x_, double y_, double dx_, double dy_, double size_)
:Ball(x_,y_,dx_,dy_,size_)
{
}

void BounceBall::step(double scrLeft, double scrTop, double scrRight, double scrBottom)
{
    Ball::step();
    if(x >= scrRight){
        x = scrRight - 1;
        dx = -1 * fabs(dx);
    }
    if(x < scrLeft){
        x = scrLeft;
        dx = fabs(dx);
    }
    if(y >= scrBottom){
        y = scrBottom - 1;
        dy = -1 * fabs(dy);
    }
    if(y < scrTop){
        y = scrTop;
        dy = fabs(dy);
    }
}
