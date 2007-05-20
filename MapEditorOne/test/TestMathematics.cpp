#include <HPLLib/HPLMath.h>
#include <SDL.h>
#include <cmath>
#include <cstdlib>
//#include <cstdio>

#include <SDL_gfxPrimitives.h>
#include "BounceBall.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int BPP = 32;

const double BALL_SIZE = 10;
const double BALL_SPEED = 10.0;
const int BALL_NUM = 4;

const double SELECT_BALL_THRESHOLD = 10;

const int BUF_MAX = 256;

const int MAX_POLYGON = 8;
const int MIN_POLYGON = 3;

class GlobalData{
public:
    //実行中か
    bool isRunning;

    //ボールx4
    BounceBall *balls[BALL_NUM];
    int catchedBall;

    //n角形
    int nPolygon;
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
    globalData.catchedBall = -1;
    globalData.nPolygon = 3;
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

void onMouseButtonDown(SDL_Event ev){
    globalData.catchedBall = -1;
    //選択できているか探す
    double mx = (double)ev.button.x;
    double my = (double)ev.button.y;
    for(int i = 0; i < BALL_NUM; i ++){
        double dx = mx - globalData.balls[i]->x;
        double dy = my - globalData.balls[i]->y;
        double distance = hpl::math::getLength(dx, dy);
        if(distance <= SELECT_BALL_THRESHOLD){
            globalData.catchedBall = i;
            break;
        }
    }
}
void onMouseMotion(SDL_Event ev){
    int mx = ev.motion.x;
    int my = ev.motion.y;
    if(globalData.catchedBall >= 0 && globalData.catchedBall < BALL_NUM &&
        ev.motion.state == SDL_PRESSED)
    {
        //選択している・ボタンを押している場合
        //位置移動
        globalData.balls[globalData.catchedBall]->x = (double)mx;
        globalData.balls[globalData.catchedBall]->y = (double)my;
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
        globalData.nPolygon = MAX_POLYGON - 1;
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
    //ボール移動
/*    for(int i = 0; i < BALL_NUM; i ++){
        globalData.balls[i]->step(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }*/

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
    SDL_Rect rect = {x - size / 2, y - size / 2, size, size};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, r,g,b));
}
void draw(SDL_Surface* screen)
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));

    for(int i = 0; i < BALL_NUM; i ++){
        int x = (int)globalData.balls[i]->x;
        int y = (int)globalData.balls[i]->y;
        int size = (int)globalData.balls[i]->size;
        drawBall(screen, x, y, size, 255,0,0,255);
    }
    //矩形を表示します
    rectangleRGBA(screen, globalData.balls[0]->x, globalData.balls[0]->y,
        globalData.balls[1]->x, globalData.balls[1]->y,
        200,50,50,255);
    //中心
    {
        char buf[BUF_MAX];
        //n角形
        sprintf(buf, "polygon:%d", globalData.nPolygon);
        stringRGBA(screen, 16,100,buf, 255, 255, 0, 255);
        double x0 = globalData.balls[0]->x, y0 = globalData.balls[0]->y;
        double x1 = globalData.balls[1]->x, y1 = globalData.balls[1]->y;
        int size = BALL_SIZE;
        double center[2];
        //中心取得
        hpl::math::getCenterOfRectangle(x0,y0,x1,y1,center);
        //中心表示
        drawBall(screen, center[0], center[1], size, 255,255,200,255);
        //円表示
        //半径
        double r = hpl::math::getLength(center[0] - x0, center[1] - y0);
        circleRGBA(screen, center[0], center[1], r, 255,255,200,255);
        //円周上の点
        double cirPoints[MAX_POLYGON][2];
        hpl::math::getCirculatePolygonPoints(center[0], center[1], r, globalData.nPolygon,
            cirPoints);

        //矩形にあわせた点
        double scaledPolygonPoints[MAX_POLYGON][2];
        hpl::math::getRectangleScaledPreparedPolygon(x0, y0, x1, y1,
            globalData.nPolygon, scaledPolygonPoints);

        //点表示
        //中心からの線表示
        Sint16 vx[MAX_POLYGON+1], vy[MAX_POLYGON+1];
        Sint16 scaledVX[MAX_POLYGON+1], scaledVY[MAX_POLYGON+1];

        for(int i = 0; i < globalData.nPolygon; i ++){
            drawBall(screen, cirPoints[i][0], cirPoints[i][1], size,
                255, 100, 0, 255);
            //番号
            sprintf(buf, "%d", i);
            stringRGBA(screen, cirPoints[i][0],cirPoints[i][1],buf, 255, 255, 0, 255);
            lineRGBA(screen, center[0], center[1], cirPoints[i][0], cirPoints[i][1],
                0,255,255,255);
            vx[i] = cirPoints[i][0];
            vy[i] = cirPoints[i][1];
            scaledVX[i] = scaledPolygonPoints[i][0];
            scaledVY[i] = scaledPolygonPoints[i][1];
            drawBall(screen, scaledPolygonPoints[i][0], scaledPolygonPoints[i][1], size,
                100,255,100,255);
        }
/*        vx[globalData.nPolygon] = cirPoints[0][0];
        vy[globalData.nPolygon] = cirPoints[0][1];
  */      
        //ポリゴン表示
        polygonRGBA(screen, (const Sint16*)vx, (const Sint16*)vy, globalData.nPolygon, 100,100,255, 255);
        polygonRGBA(screen, (const Sint16*)scaledVX, (const Sint16*)scaledVY, globalData.nPolygon, 255,100,255, 255);
        
    }
    //線を表示します
    //TODO
    lineRGBA(screen, globalData.balls[0]->x, globalData.balls[0]->y,
        globalData.balls[1]->x, globalData.balls[1]->y,
        255, 0, 0, 255);
    lineRGBA(screen, globalData.balls[2]->x, globalData.balls[2]->y,
        globalData.balls[3]->x, globalData.balls[3]->y,
        0, 0, 255, 255);
    double line[2][2][2] = 
    {
        {{globalData.balls[0]->x, globalData.balls[0]->y},
        {globalData.balls[1]->x, globalData.balls[1]->y}},
        {{globalData.balls[2]->x, globalData.balls[2]->y},
        {globalData.balls[3]->x, globalData.balls[3]->y}}
    };
    //angle & slice
    drawAngleAndSlice(screen, line[0], 16, 16, 255, 50, 50, 255);
    drawAngleAndSlice(screen, line[1], 16, 32, 50, 50, 255, 255);
    //交点を求めます
    double crossPoint[2];
    if(hpl::math::getCrossPointOfTwoLines(line[0], line[1], crossPoint))
    {
        //点を表示します
        int x = crossPoint[0];
        int y = crossPoint[1];
        int size = BALL_SIZE;
        drawBall(screen, x, y, size, 255,255,0,255);

        //座標を表示します
        char buf[BUF_MAX];
        sprintf(buf, "cross:(%d,%d)", x, y);
        stringRGBA(screen, 16,50,buf, 255, 255, 0, 255);
    }else{
        int x = crossPoint[0];
        int y = crossPoint[1];
        char buf[BUF_MAX];
        sprintf(buf, "cannot get cross point:(%d,%d)", x, y);
        stringRGBA(screen, 16,50,buf, 255, 255, 0, 255);
    }
}

