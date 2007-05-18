#include "Ball.h"

Ball::Ball(double x_, double y_, double dx_, double dy_, double size_)
{
    x = x_; y = y_; dx = dx_; dy = dy_; size = size_;
}

Ball::~Ball(){}

void Ball::step()
{
    x += dx;
    y += dy;
}
