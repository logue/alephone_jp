#include "General.h"

#ifdef PREPARED

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


void draw(SDL_Surface* screen)
{

    for(int i = 0; i < BALL_NUM; i ++){
        int x = (int)globalData.balls[i]->x;
        int y = (int)globalData.balls[i]->y;
        int size = (int)globalData.balls[i]->size;
        drawBall(screen, x, y, size, 255,0,0,255);
    }
    //矩形を表示します
    rectangleRGBA(screen, (Sint16)globalData.balls[0]->x, (Sint16)globalData.balls[0]->y,
        (Sint16)globalData.balls[1]->x, (Sint16)globalData.balls[1]->y,
        200,50,50,255);
    //中心
    {
        char buf[BUF_MAX];
        //n角形
        sprintf(buf, "polygon:%d", globalData.nPolygon);
        stringRGBA(screen, 16,100,buf, 255, 255, 0, 255);
        double x0 = globalData.balls[0]->x, y0 = globalData.balls[0]->y;
        double x1 = globalData.balls[1]->x, y1 = globalData.balls[1]->y;
        int size = (int)BALL_SIZE;
        double center[2];
        //中心取得
        hpl::math::getCenterOfRectangle(x0,y0,x1,y1,center);
        //中心表示
        drawBall(screen, center[0], center[1], size, 255,255,200,255);
        //円表示
        //半径
        double r = hpl::math::getLength(center[0] - x0, center[1] - y0);
        circleRGBA(screen, (Sint16)center[0], (Sint16)center[1], (Sint16)r, 255,255,200,255);
        //円周上の点
        double cirPoints[MAX_POLYGON][2];
        hpl::math::getCirculatePolygonPoints(center[0], center[1], (Sint16)r, globalData.nPolygon,
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
            stringRGBA(screen, (Sint16)cirPoints[i][0], (Sint16)cirPoints[i][1],buf, 255, 255, 0, 255);
            lineRGBA(screen, (Sint16)center[0], (Sint16)center[1], (Sint16)cirPoints[i][0], (Sint16)cirPoints[i][1],
                0,255,255,255);
            vx[i] = (Sint16)cirPoints[i][0];
            vy[i] = (Sint16)cirPoints[i][1];
            scaledVX[i] = (Sint16)scaledPolygonPoints[i][0];
            scaledVY[i] = (Sint16)scaledPolygonPoints[i][1];
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
    lineRGBA(screen, (Sint16)globalData.balls[0]->x, (Sint16)globalData.balls[0]->y,
        (Sint16)globalData.balls[1]->x, (Sint16)globalData.balls[1]->y,
        255, 0, 0, 255);
    lineRGBA(screen, (Sint16)globalData.balls[2]->x, (Sint16)globalData.balls[2]->y,
        (Sint16)globalData.balls[3]->x, (Sint16)globalData.balls[3]->y,
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
        int x = (int)crossPoint[0];
        int y = (int)crossPoint[1];
        int size = (int)BALL_SIZE;
        drawBall(screen, x, y, size, 255,255,0,255);

        //座標を表示します
        char buf[BUF_MAX];
        sprintf(buf, "cross:(%d,%d)", x, y);
        stringRGBA(screen, 16,50,buf, 255, 255, 0, 255);
    }else{
        int x = (int)crossPoint[0];
        int y = (int)crossPoint[1];
        char buf[BUF_MAX];
        sprintf(buf, "cannot get cross point:(%d,%d)", x, y);
        stringRGBA(screen, 16,50,buf, 255, 255, 0, 255);
    }
}

#endif
