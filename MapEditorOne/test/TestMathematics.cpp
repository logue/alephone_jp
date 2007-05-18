#include <HPLLib/HPLMath.h>
#include <SDL.h>
#include <cmath>
#include <cstdlib>
//#include <cstdio>

//#include <SDL/SDL_gfx>
#include "BounceBall.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int BPP = 32;

const double BALL_SIZE = 10;
const double BALL_SPEED = 10.0;
const int BALL_NUM = 4;

class GlobalData{
public:
    //実行中か
    bool isRunning;

    //ボールx4
    BounceBall *balls[BALL_NUM];
public:
    GlobalData(){}
    ~GlobalData(){
        for(int i = 0; i < BALL_NUM; i ++){
            delete balls[i];
        }
    }

};

GlobalData globalData;

const double BIAS = 100.0;

double getRandomDouble(double min, double max)
{
    double r = (rand() % (int)((max + min) * BIAS) - min * BIAS) / BIAS;
    return r;
}


void init();
void loop(SDL_Surface* screen);
void doEvent();
void step();
void draw(SDL_Surface* screen);

int main(int argc, char** argv){
    //SDL初期化するよ
    SDL_Init(SDL_INIT_VIDEO);

    //Video初期化するよ
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP, SDL_SWSURFACE);
    
    init();
    //ループ
    loop(screen);

    //終了するよ
    SDL_Quit();
    return 0;
}

void init()
{
    //初期化設定だよ
    globalData.isRunning = true;

    //ball setup
    for(int i = 0; i < BALL_NUM; i ++){
        double x = rand() % WINDOW_WIDTH;
        double y = rand() % WINDOW_HEIGHT;
        double deg = getRandomDouble(0,360);
        double rad = hpl::math::getRadianFromDegree(deg);
        double dx = cos(rad) * BALL_SPEED;
        double dy = sin(rad) * BALL_SPEED;
        double size = BALL_SIZE;
        globalData.balls[i] = new BounceBall(x, y, dx, dy, size);
    }
}

void loop(SDL_Surface* screen)
{
    while(globalData.isRunning){
        //イベント処理するよ
        doEvent();

        step();

        draw(screen);

        SDL_Flip(screen);

        SDL_Delay(16);
    }
}

void doEvent()
{
    //イベント取得するよ
    SDL_Event ev;
    while(SDL_PollEvent(&ev)){
        switch(ev.type){
        case SDL_QUIT:
            globalData.isRunning = false;
            break;
        }
    }
}

void step()
{
    //ボール移動
    for(int i = 0; i < BALL_NUM; i ++){
        globalData.balls[i]->step(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
}

void draw(SDL_Surface* screen)
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));

    for(int i = 0; i < BALL_NUM; i ++){
        int x = (int)globalData.balls[i]->x;
        int y = (int)globalData.balls[i]->y;
        int size = (int)globalData.balls[i]->size;
        SDL_Rect rect = {x - size / 2, y - size / 2, size, size};
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 0));
    }
}

