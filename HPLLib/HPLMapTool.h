#ifndef _HPL_MAP_TOOL_
#define _HPL_MAP_TOOL_

#include <math.h>
#include <vector>
#include <map>

#include "map.h"
#include "wad.h"

//#include "HPLMath.h"
#include "HPLSelectData.h"

namespace hpl{
namespace aleph{
namespace map{

    ///////////////////////////////////////////////////////////////////////
    ///////////  Points  //////////////////////////////////////////////////
    /**
        <jp>�w�肵���_���N���b�N�ł��Ă��邩�̔�����s���܂��B
        <en>is view-point near world-point?
        @param viewPX   point(mouse/view)       �r���[���W�i�X�N���[�����W�j
        @param worldPX  point(world)            �ΏۂƂ���_�i�����W�j
        @param offsetViewX offset of view       �r���[���W�̃Y��
        @param offsetWorldX offset of world     �����W�̃Y��
        @param distance check distance          臒l
    */
    bool isSelectPoint(int viewPX, int viewPY, 
                       int worldPX, int worldPY,
                       int offsetViewX, int offsetViewY,
                       int offsetWorldX, int offsetWorldY,
                       int div,
                       int distance);
    bool isSelectPoint(world_point2d &point0, world_point2d &point1,
                       int distance);

    ///////////////////////  Lines  ////////////////////////////////////////////
    /**
        �w�肵���_��p�����Ƃ��ɐ���I���ł��Ă��邩�𔻒�
        is view-point near world-line?
        @param viewPX   point(mouse/view)
        @param worldPX0 line's point(world)
        @param offsetViewX offset of view
        @param offsetWorldX offset of world
        @param distance check distance
    */
    bool isSelectLine(int viewPX, int viewPY,
                       int worldPX0, int worldPY0,
                       int worldPX1, int worldPY1,
                       int offsetViewX, int offsetViewY,
                       int offsetWorldX, int offsetWorldY,
                       int div,
                       int distance);

    bool isSelectLine(world_point2d &point,
                      world_point2d &linePoint0, world_point2d &linePoint1,
                      int distance);

    /**
        ���̒������擾
        @param index ���f�[�^�̃C���f�b�N�X
    */
    double getLineLength(int index);
    /*
        ���̒����𓾂�
    */
    double getLength(world_point2d& pointA, world_point2d& pointB);

    ///////////////////////////////////////////////////////////////////////
    ///////////  Groups  //////////////////////////////////////////////////
    /**
        �}�E�X�����ɑI������Ă���A�C�e�����N���b�N���Ă��邩�m���߂܂�
        <en>is point in select groups?
        @param px point locatin(view)               �}�E�X�ʒu�i�r���[���W�j
        @param offsetViewX offset(view)             �r���[���W�Y��
        @param offsetWorldX offset(world)           �����W
        @param pointDistance distance as nearby     �_�p臒l
        @param lineDistance distance as nearby      ���p臒l
        @param selectInfo select group for check    �O���[�v�N���X
    */
    bool isPointInSelection(int px, int py,
                            int offsetViewX, int offsetViewY,
                            int offsetWorldX, int offsetWorldY,
                            int pointDistance,
                            int lineDistance,
                            int objectDistance,
                            hpl::aleph::map::HPLSelectData* selectInfo,
                            int heightMax, int heightMin, int div);

};
};
};
#endif
