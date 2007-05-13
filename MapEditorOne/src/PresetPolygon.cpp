#include "PresetPolygon.h"
#include "HPLLib/HPLAlephLib.h"

/**
    頂点の数を指定して生成
    @param n the number of edges
*/
mapeditorone::PresetPolygon::PresetPolygon(int n)
{
    //３角形以下はダメなので３角形にする
    if(n < 3){
        n = 3;
    }

    //８角形より上ではエラーを起こす
    if(n > 8){
        n = 8;
    }
    this->num = n;
}
mapeditorone::PresetPolygon::~PresetPolygon()
{
}

const int ROUND_DEGREE = 360;

/**
    範囲指定からポリゴン座標を得ます
*/
void mapeditorone::PresetPolygon::getPoints(int x0, int y0, int x1, int y1, int *dest)
{
    //p0が左上、p1が右下になるようにセット
    if(x0 > x1){
        hpl::math::exchange<int>(&x0, &x1);
    }
    if(y0 > y1){
        hpl::math::exchange<int>(&y0, &y1);
    }
    //中心座標→頂点までの距離を半径とする円を想定する
    int centerX = x0 + (x1 - x0) / 2;
    int centerY = y0 + (y1 - y0) / 2;
    int r = sqrt(pow(centerX - x0, 2) + pow(centerY - y0, 2));
    
    //円を元に正n角形を取得する
    //求める円周上の点
    int points[8][2];
    //正n角形の各辺に対する中心角
    int degInterval = ROUND_DEGREE / this->num;
    for(int degStep = 0; degStep < this->num; degStep ++){
        int degree = degStep * degInerval;

        //水平右が０度、真下が９０度なので、-90する
        degree -= (ROUND_DEGREE / 4);

        double rad = hpl::math::getRadianFromDegree(degree);
        points[degStep][0] = cos(rad) * r;
        points[degStep][1] = sin(rad) * r;

        //長方形との交点を求める

    }
}
