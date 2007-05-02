#ifndef _HPL_MATH_
#define _HPL_MATH_

namespace hpl{
namespace math{
    //exchange between a and b
    template<class T>
    void exchange(T *a, T *b)
    {
        T temp = *a;
        *a = *b;
        *b = temp;
    }

    /**
        get sign of num
    */
    template<class T>
    int sgn(T n)
    {
        if( n > 0){
            return 1;
        }else if( n < 0){
            return -1;
        }else{
            return 0;
        }
    }


    /**
        ラジアンと度の変換
    */
    double getDegreeFromRadian(double rad);
    double getRadianFromDegree(double deg);

    //////////////////////////////////////////////////////////////////////
    ///////////////  Is Point In  ////////////////////////////////////////
    /**
        点が矩形内か調べる
        <en>check point be in a rect
    */
    template<class T>
    bool isPointInRect(T px, T py, T rx0, T ry0, T rx1, T ry1)
    {
        T left = (rx0<rx1?rx0:rx1);
        T right = (rx0<rx1?rx1:rx0);
        T top = (ry0<ry1?ry0:ry1);
        T bottom = (ry0<ry1?ry1:ry0);

        if( left <= px && px <= right &&
        top <= py && py <= bottom){
            return true;
        }
        return false;
    }
    /**
        線が矩形内かチェック
    */
    bool isLineInRect(int lx0, int ly0, int lx1, int ly1,
                        int rx0, int ry0, int rx1, int ry1);

    /**
        ポリゴンが矩形内かチェック
    */
    bool isPolygonInRect(int **points, int point_num,
                        int rx0, int ry0, int rx1, int ry1);

    /**
        ベクトルから角度を求めます(右方向がX正方向。下方向がY正方向)
        calcurate degree from vector
        down to 90 degree. right to 0 degree.(right and bottom are plus)
    */
    double getDegreeFromVector(double dx, double dy);

    //////////////////////////////////////////////////////////////////////
    ///////////////  Length  /////////////////////////////////////////////
    /**
        <jp>点と線分の距離が閾値以下か調べる
        <en>check distance between point and line is under threshold
    */
    bool isNearbyPointToLine(double px, double py, 
                     double lx0, double ly0, double lx1, double ly1,
                     double distance);

    /**
        点と点の距離が所定以内か判定
        <en>check distance between points be under threshold
    */
    bool isNearbyPoints(double px0, double py0, 
                     double px1, double py1, double distance);

    //////////////////////////////////////////////////////////////////////
    ///////////////  Angle   /////////////////////////////////////////////
    /**
        二つの線が織り成す角度を求めます。スクリーン座標系より、
        時計回りが正方向となる
        @param pax,y,pbx,y 線分ABの座標
        @param pcx,y,pdx,y 線分CDの座標
    */
    double getTwoLinesRadian(double pax, double pay, double pbx, double pby,
        double pcx, double pcy, double pdx, double pdy);
    double getTwoLinesDegree(double pax, double pay, double pbx, double pby,
        double pcx, double pcy, double pdx, double pdy);
    /**
        ベクトルの角度を求めます(0 deg = (1,0))
    */
    double getDegreeFromVector(double x, double y);
    double getRadianFromVector(double x, double y);

    /**
        角度を[0,360)に直します
    */
    double optimizeDegree(double deg);
    double optimizeRadian(double rad);
};
};
#endif
