#ifndef _HPL_MATH_
#define _HPL_MATH_

namespace hpl{
namespace math{
    /**
        ���̎��
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

    namespace RotationType{
        //���̉��������v��肩�A�����v��肩
        enum {
            Clockwise,
            Counterclockwise,

            MAX_POLYGON_ROTATION_TYPES
        };
    };
    /**
        ���W�A���Ɠx�̕ϊ�
    */
    double getDegreeFromRadian(double rad);
    double getRadianFromDegree(double deg);

    //////////////////////////////////////////////////////////////////////
    ///////////////  Is Point In  ////////////////////////////////////////
    /**
        �_����`�������ׂ�
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
        ������`�����`�F�b�N
    */
    bool isLineInRect(int lx0, int ly0, int lx1, int ly1,
                        int rx0, int ry0, int rx1, int ry1);

    /**
        �|���S������`�����`�F�b�N
    */
    bool isPolygonInRect(int **points, int point_num,
                        int rx0, int ry0, int rx1, int ry1);

    /**
        �x�N�g������p�x�����߂܂�(�E������X�������B��������Y������)
        calcurate degree from vector
        down to 90 degree. right to 0 degree.(right and bottom are plus)
    */
    double getDegreeFromVector(double dx, double dy);

    //////////////////////////////////////////////////////////////////////
    ///////////////  Length  /////////////////////////////////////////////
    /**
        <jp>�_�Ɛ����̋�����臒l�ȉ������ׂ�
        <en>check distance between point and line is under threshold
    */
    bool isNearbyPointToLine(double px, double py, 
                     double lx0, double ly0, double lx1, double ly1,
                     double distance);

    /**
        �_�Ɠ_�̋���������ȓ�������
        @param distance �r���[���W�ł̋���臒l
        <en>check distance between points be under threshold
    */
    bool isNearbyPoints(double px0, double py0, 
                     double px1, double py1, double distance);

    //////////////////////////////////////////////////////////////////////
    ///////////////  Angle   /////////////////////////////////////////////
    /**
        ��̐����D�萬���p�x�����߂܂��B�X�N���[�����W�n���A
        ���v��肪�������ƂȂ�
        @param pax,y,pbx,y ����AB�̍��W
        @param pcx,y,pdx,y ����CD�̍��W
    */
    double getTwoLinesRadian(double pax, double pay, double pbx, double pby,
        double pcx, double pcy, double pdx, double pdy);
    double getTwoLinesDegree(double pax, double pay, double pbx, double pby,
        double pcx, double pcy, double pdx, double pdy);
    /**
        �x�N�g���̊p�x�����߂܂�(0 deg = (1,0))
    */
    double getDegreeFromVector(double x, double y);
    double getRadianFromVector(double x, double y);

    /**
        �p�x��[0,360)�ɒ����܂�
    */
    double optimizeDegree(double deg);
    double optimizeRadian(double rad);

    /////////////////////////////////////////////////////
    /////////////  cross  ///////////////////////////////
    /**
        2�̐��������������_���擾���܂��B
        @param line0 ��0
        @param line1 ��1
        @return 2�̐������������Ă��Ȃ��ꍇ�U
    */
    bool getCrossPointOfTwoLines(double line0[2][2],
        double line1[2][2], double dest[2]);

    /**
        �����̒[�_�f�[�^����A���̐��̌X���ƐؕЂ����߂܂�
        �������������Ȑ��̏ꍇ�͌X�����t���ɂȂ��Ă�̂Œ���
        @param line line datas ([0][0],[0][1])-([1][0],[1][1])
        @param 
    */
    int getLineAngleAndSlice(double line[2][2], double *degree, double *slice);
    
    /**
        ���̌X�����p�x���瓾�܂�
    */
    double getAngleFromDegree(double degree);

    ///////////////////
    /**
        �_��������ւ̋����i�����̒����j�����߂܂�
        <en>get 
    */
    double getPointDistanceFromLine(double px, double py, 
                             double lx0, double ly0, double lx1, double ly1);

    /**
        <jp>�O�����̒藝�Œ��������߂�
        <en>get length of (0,0)-(x,y)
    */
    double getLength(double x, double y);

    /**
        <jp>���ς����߂܂�
    */
    double getInnerProduct(double x0, double y0, double x1, double y1);

    /**
        �_����~�낵���������u�����v�ƌ������邩���f�i�����┼�����ł͂Ȃ��j
    */
    bool isCrossPointLine(double px, double py, 
                             double lx0, double ly0, double lx1, double ly1);

    /////////////////////////////////////////////////////////
    //////  polygons  ///////////////////////////////////////
    /**
        �w�肵���͈͂Ɏ��܂�n�p�`�𐶐����܂��B
        ������
        @param (x0,y0)-(x1,y1) range of rectangle. the polygon you want will be create fitting with this.
        @param n
        @param points destraction of this function. you can add points and lines and polygon
        @return true when succeeded
    */
    bool getRectangleScaledPreparedPolygon(double x0, double y0, double x1, double y1, int n,
                                                            double points[8][2]);
    /**
        ��`�̒��S�ʒu�𓾂܂�
    */
    void getCenterOfRectangle(double x0, double y0, double x1, double y1, double center[2]);

    /**
        �~���ɉ�������n�p�`�̓_�𓾂܂�
    */
    void getCirculatePolygonPoints(double centerx, double centery, double radius,
        int n, double dest[][2]);

    /**
        �_���|���S���̂Ȃ��ɑ��݂��邩���`�F�b�N���܂�
    */
    bool isPointInPolygon(double px, double py, double polygonPoints[][2], int n);

    /**
        �_�����̉E�������ɂ��邩�A���������ɂ��邩���f���܂�
    */
    int getPointRotationTypeFromLine(double px, double py, double line0x, double line0y,
        double line1x, double line1y);

    /**
        �|���S���ɓ������s�p�����݂��Ȃ����ǂ����m�F���܂�
    */
    bool isValidPolygon(double points[][2], int maxVertex);

	/**
		�|���S����Area�i�ʐρj�����߂܂�
		<en> calculate polygon's area
		referenced from
		http://local.wasp.uwa.edu.au/~pbourke/geometry/polyarea/
	*/
	double getPolygonArea(double points[][2], int maxVertex);

	/**
		�|���S���̃Z���g���C�h�����߂܂�
		<en> calculate polygon's center(centre,centroid)
	*/
	void getPolygonCentroid(double points[][2], int maxVertex, double center[2]);
};
};
#endif
