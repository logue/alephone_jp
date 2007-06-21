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

//�|���S���`�F�b�N�p�ɗp�ӂ���|���S���p�_�ƁA�|���S��������邩���`�F�b�N�����_�p�_
const int A_POLY_BALL_NUM = 8 + 1;

//�����̏c��
const int FONT_SIZE = 12;

//�V�̒���
const double ARROW_LENGTH = 10;

//�|���S���`�F�b�N�^�C�v
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
    //���s����
    bool isRunning;

    //n�p�`
    int nPolygon;

    int catchedBall;

    ///////////////////
    //�{�[��x4
    BounceBall *balls[BALL_NUM];

    /////////////////////
    //�{�[�� n + 1
    BounceBall *polygonBalls[A_POLY_BALL_NUM];

    //�������
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

//���ʂŎg����֐�
void drawBall(SDL_Surface* screen, double x, double y, double size,
              double r, double g, double b, double a);
void drawAngleAndSlice(SDL_Surface* screen, double line[2][2], int x, int y,
                       int r, int g, int b, int a);
void drawArrow(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a, double length);
double getRandomDouble(double min, double max);

//���ꂼ�ꂪ�ݒ肷��֐�
void draw(SDL_Surface* screen);
void onMouseButtonDown(SDL_Event ev);
void onMouseMotion(SDL_Event ev);

/**
    ���������i�ȈՔŁj�B������g�����ƂŃ��C�u�����̕ϓ��ɏ_��Ɂi����
*/
void drawLine(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a);

/**
    ��������o�͂��܂�
*/
void drawString(SDL_Surface* screen, double x, double y, int r, int g, int b, int a, const char* format, ...);
#endif
