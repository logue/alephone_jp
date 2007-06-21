#ifndef _GENERAL_
#define _GENERAL_

#include <HPLLib/HPLAlephLib.h>
#include <SDL.h>
#include <cmath>
#include <cstdlib>
//#include <cstdio>
#include <stdarg.h>
#include <string>
#include <vector>
#include <map>
#include <list>

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

//ポリゴンチェック用に用意するポリゴン用点と、ポリゴンが張れるかをチェックする基点用点
const int A_POLY_BALL_NUM = 8 + 1;

//文字の縦幅
const int FONT_SIZE = 12;

//鏃の長さ
const double ARROW_LENGTH = 10;

//ポリゴンチェックタイプ
namespace CheckType{
enum {
    IsPointInPolygon,
    IsCanFillPolygonFromPoint,
    IsValidPolygon,
    MAX_CHECK_TYPES
};
};

/////////////////////////////////////
//#define PREPARED
#define SEARCH_POLY

class GlobalData{
public:
    //実行中か
    bool isRunning;

    //n角形
    int nPolygon;

    int catchedBall;

    ///////////////////
    //ボールx4
    BounceBall *balls[BALL_NUM];

    /////////////////////
    //ボール n + 1
    BounceBall *polygonBalls[A_POLY_BALL_NUM];

    //調査種類
    int checkType;
public:
    GlobalData(){}
    ~GlobalData(){
        for(int i = 0; i < BALL_NUM; i ++){
            delete balls[i];
        }
        for(int i = 0; i < A_POLY_BALL_NUM; i ++){
            delete polygonBalls[i];
        }
    }

};

extern GlobalData globalData;

const double BIAS = 100.0;

//共通で使える関数
void drawBall(SDL_Surface* screen, double x, double y, double size,
              double r, double g, double b, double a);
void drawAngleAndSlice(SDL_Surface* screen, double line[2][2], int x, int y,
                       int r, int g, int b, int a);
void drawArrow(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a, double length);
double getRandomDouble(double min, double max);

//それぞれが設定する関数
void draw(SDL_Surface* screen);
void onMouseButtonDown(SDL_Event ev);
void onMouseMotion(SDL_Event ev);

/**
    線を引く（簡易版）。これを使うことでライブラリの変動に柔軟に（ｒｙ
*/
void drawLine(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a);

/**
    文字列を出力します
*/
void drawString(SDL_Surface* screen, double x, double y, int r, int g, int b, int a, const char* format, ...);
#endif
