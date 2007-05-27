#include "General.h"

GlobalData globalData;

void init();
void loop(SDL_Surface* screen);
void doEvent();
void step();

double getRandomDouble(double min, double max)
{
    double r = (rand() % (int)((max + min) * BIAS) - min * BIAS) / BIAS;
    return r;
}

int main(int argc, char** argv){
    //SDL�����������
    SDL_Init(SDL_INIT_VIDEO);

    //Video�����������
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP, SDL_SWSURFACE);
    
    init();
    //���[�v
    loop(screen);

    //�I�������
    SDL_Quit();
    return 0;
}

BounceBall* getRandomNewBounceBall()
{
    double x = rand() % WINDOW_WIDTH;
    double y = rand() % WINDOW_HEIGHT;
    double deg = getRandomDouble(0,360);
    double rad = hpl::math::getRadianFromDegree(deg);
    double dx = cos(rad) * BALL_SPEED;
    double dy = sin(rad) * BALL_SPEED;
    double size = BALL_SIZE;
    BounceBall* ball = new BounceBall(x, y, dx, dy, size);
    return ball;
}


void init()
{
    //�������ݒ肾��
    globalData.isRunning = true;

    //ball setup
    for(int i = 0; i < BALL_NUM; i ++){
        globalData.balls[i] = getRandomNewBounceBall();
    }
    globalData.catchedBall = -1;
    globalData.nPolygon = 3;

    for(int i = 0; i < A_POLY_BALL_NUM; i ++){
        globalData.polygonBalls[i] = getRandomNewBounceBall();
    }

}

void loop(SDL_Surface* screen)
{
    while(globalData.isRunning){
        //�C�x���g���������
        doEvent();

        step();


        draw(screen);

        SDL_Flip(screen);

        SDL_Delay(16);
    }
}

void upNPolygon()
{
    globalData.nPolygon ++;
    if(globalData.nPolygon > MAX_POLYGON){
        globalData.nPolygon = MIN_POLYGON;
    }
}
void downNPolygon()
{
    globalData.nPolygon --;
    if(globalData.nPolygon < MIN_POLYGON){
        globalData.nPolygon = MAX_POLYGON;
    }
}

void doEvent()
{
    //�C�x���g�擾�����
    SDL_Event ev;
    while(SDL_PollEvent(&ev)){
        switch(ev.type){
        case SDL_QUIT:
            globalData.isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(ev);
            break;
        case SDL_MOUSEMOTION:
            onMouseMotion(ev);
            break;
        case SDL_MOUSEBUTTONUP:
            globalData.catchedBall = -1;
            break;
        case SDL_KEYDOWN:
            int key = ev.key.keysym.sym;
            if(key == SDLK_UP){
                upNPolygon();
            }else if(key == SDLK_DOWN){
                downNPolygon();
            }
            break;
        }
    }
}

void step()
{
    //�{�[���ړ�
/*    for(int i = 0; i < BALL_NUM; i ++){
        globalData.balls[i]->step(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }*/

}

/**
    @param x1,y1 �I�_
    @param length �V�̒���
*/
void drawArrow(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a, double length)
{
    double dx = x1 - x0;
    double dy = y1 - y0;
    //0->1�̊p�x�𓾂܂�
    double deg = hpl::math::getDegreeFromVector(dx, dy);
    //135�x���炷
    for(int i = -1; i < 2; i += 2){
        double newDeg = deg + (double)i * 45.0;
        double rad = hpl::math::getRadianFromDegree(newDeg);
        //
        double newX = x1 + cos(rad) * length;
        double newY = y1 + sin(rad) * length;
        //���������܂�
        drawLine(screen, x1, y1, newX, newY, r, g, b, a);
    }
    drawLine(screen, x0, y0, x1, y1, r, g, b, a);
}

void drawAngleAndSlice(SDL_Surface* screen, double line[2][2], int x, int y,
                       int r, int g, int b, int a)
{
    double degree, slice;
    hpl::math::getLineAngleAndSlice(line, &degree, &slice);
    char buf[BUF_MAX];
    double angle = hpl::math::getAngleFromDegree(degree);
    sprintf(buf, "0:(%d,%d)-(%d,%d), \nangle:%f, degree:%f, slice:%f",
        (int)line[0][0], (int)line[0][1], (int)line[1][0], (int)line[1][1],
        angle, degree, slice);
    stringRGBA(screen, x,y,buf, r,g,b,a);
}
void drawBall(SDL_Surface* screen, double x, double y, double size,
              double r, double g, double b, double a)
{
    SDL_Rect rect = {(Sint16)(x - size / 2), (Sint16)(y - size / 2), (Uint16)size, (Uint16)size};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, (Uint8)r, (Uint8)g, (Uint8)b));
}

/**
    ���������i�ȈՔŁj�B������g�����ƂŃ��C�u�����̕ϓ��ɏ_��Ɂi����
*/
void drawLine(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a)
{
    lineRGBA(screen, (Sint16)x0, (Sint16)y0,
        (Sint16)x1, (Sint16)y1,
        r,g,b,a);
}

/**
    ��������o�͂��܂�
*/
void drawString(SDL_Surface* screen, double x, double y, int r, int g, int b, int a, const char* format, ...)
{
    char messages[BUF_MAX];
    va_list maker;
    va_start(maker, format);
    vsprintf(messages, format, maker);
    
    //���s�𕪒f����
    std::vector<std::string> lines = hpl::string::Split(std::string(messages), "\n");

    //��s���\��
    for(int i = 0; i < (int)lines.size(); i ++){
        int tempY = y + FONT_SIZE * i;
        stringRGBA(screen, (Sint16)x, (Sint16)tempY, lines[i].c_str(), r, g, b, a);
    }
}