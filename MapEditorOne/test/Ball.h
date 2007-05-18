#ifndef _BALL_
#define _BALL_

/**
    ˆÚ“®‚·‚éƒ{[ƒ‹
*/
class Ball{
public:
    double x;
    double y;
    double dx;
    double dy;
    double size;
public:
    Ball(double x_, double y_, double dx_, double dy_, double size_);
    ~Ball();

    void step();
};


#endif
