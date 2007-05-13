/**
    �W���ŏ������ꂽ�|���S�����
    a polygon information which is preset
*/
#ifndef _PRESET_POLYGON_
#define _PRESET_POLYGON_

namespace mapeditorone{
    class PresetPolygon{
    private:

        /**
            ���_�̐�
            the number of edges
        */
        int num;

    public:
        /**
            ���_�̐����w�肵�Đ���
            @param n the number of edges
        */
        PresetPolygon(int n);
        ~PresetPolygon();

        /**
            �͈͎w�肩��|���S�����W�𓾂܂�
        */
        void getPoints(int x0, int y0, int x1, int y1, int *dest);
    };
};
#endif
