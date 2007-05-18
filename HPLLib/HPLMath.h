#ifndef _HPL_MATH_
#define _HPL_MATH_

namespace hpl{
namespace math{
    /**
        線の種類
    */
    namespace LineType{
        enum{
            Normal,
            Horizontal,
            Vertical,
        };
    };

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

    /////////////////////////////////////////////////////
    /////////////  cross  ///////////////////////////////
    /**
        2つの線分が交差した点を取得します。
        @param line0 線0
        @param line1 線1
        @return 2つの線分が交差していない場合偽
    */
    bool getCrossPointOfTwoLines(double line0[2][2],
        double line1[2][2], double dest[2]);

    /**
        線分の端点データから、その線の傾きと切片を求めます
        水平線か垂直な線の場合は傾きが逆軸になってるので注意
        @param line line datas ([0][0],[0][1])-([1][0],[1][1])
        @param 
    */
    int getLineAngleAndSlice(double line[2][2], double *degree, double *slice);
    
    /**
        線の傾きを角度から得ます
    */
    double getAngleFromDegree(double degree);

    ///////////////////
    /**
        点から線分への距離（垂線の長さ）を求めます
        <en>get 
    */
    double getPointDistanceFromLine(double px, double py, 
                             double lx0, double ly0, double lx1, double ly1);

    /**
        <jp>三平方の定理で長さを求める
        <en>get length of (0,0)-(x,y)
    */
    double getLength(double x, double y);

    /**
        <jp>内積を求めます
    */
    double getInnerProduct(double x0, double y0, double x1, double y1);

    /**
        点から降ろした垂線が「線分」と交差するか判断（直線や半直線ではない）
    */
    bool isCrossPointLine(double px, double py, 
                             double lx0, double ly0, double lx1, double ly1);

    /////////////////////////////////////////////////////////
    //////  polygons  ///////////////////////////////////////
    /**
        指定した範囲に収まるn角形を生成します。
        作り方は
        @param (x0,y0)-(x1,y1) range of rectangle. the polygon you want will be create fitting with this.
        @param n
        @param points destraction of this function. you can add points and lines and polygon
        @return true when succeeded
    */
    bool getRectangleScaledPreparedPolygon(double x0, double y0, double x1, double y1, int n,
                                                            double points[8][2]);
};
};
#endif
