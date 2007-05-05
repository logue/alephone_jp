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
	///////////	 Points	 //////////////////////////////////////////////////
	/**
		<jp>�w�肵���_���N���b�N�������ǂ����̔�����s���܂�
		<en>is view-point near world-point?
		@param viewPX	point(mouse/view)		    �r���[���W�i�X�N���[�����W�j
		@param worldPX	point(world)			    �����ΏۂƂ���_�i�����W�j
		@param offsetViewX offset of view		    �r���[���W�̃Y��
		@param offsetWorldX offset of world		    �����W�̃Y��
		@param distance check distance threshold    臒l
	*/
	bool isSelectPoint(int viewPX, int viewPY, 
					   int worldPX, int worldPY,
					   int offsetViewX, int offsetViewY,
					   int offsetWorldX, int offsetWorldY,
					   int div,
					   int distance);
    /**
        <jp>�w�肵���_(point1)���}�E�X�̍��W(point0)���N���b�N�������ǂ����𔻒肵�܂�
        <en>check which two world-points are near or not
        @param point0 world-point0  �_
        @param point1 world-point1  �_
        @param distance threshold   臒l
    */
	bool isSelectPoint(world_point2d &point0, world_point2d &point1,
					   int distance);
	
	/**
		<jp>�w�肵���_���O���b�h�ɍ��킹�A���̍��W�𓾂܂�
		<en>snap point to grid
		@param srcPoint                         ���̍��W
		@param destPoint snapped point			�O���b�h�ɍ��킳�ꂽ�_���W
		@param gridInterval interval of grids	�O���b�h�Ԋu
	*/
	void getSnapedPointToGrid(world_point2d &srcPoint, world_point2d* destPoint,
		int gridInterval);

	/**
		<jp>�w�肵���_�A����ѓ_�����L������ƃ|���S�������������ǂ�������?
	*/
//	  bool isValidPoint(int index);

	//convert view <-> world point
	world_point2d getWorldPoint2DFromViewPoint(int viewPX, int viewPY,
	    int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety);
	void getViewPointFromWorldPoint2D(world_point2d& point, int *dest,
	    int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety);

	///////////////////////	 Lines	////////////////////////////////////////////
	/**
		�w�肵���_��p�����Ƃ��ɐ���I���ł��Ă��邩�𔻒�
		is view-point near world-line?
		@param viewPX	point(mouse/view)
		@param worldPX0 line's point(world)                     
		@param offsetViewX offset of view                       view���W�̃Y��
		@param offsetWorldX offset of world                     world���W�̃Y���i���S�ʒu�j
		@param distance distance threshold which grab or not    �߂����ǂ�����臒l
        @return true when mouse can grab line                   ����I���ł��Ă����true
	*/
	bool isSelectLine(int viewPX, int viewPY,
					   int worldPX0, int worldPY0,
					   int worldPX1, int worldPY1,
					   int offsetViewX, int offsetViewY,
					   int offsetWorldX, int offsetWorldY,
					   int div,
					   int distance);

    /**
        <jp>����I���ł��Ă��邩���f
        <en>check which mouse grob line
        @param point mouse location in view
        @param linePoint0
        @param linePoint1 line's location in world
        @param distance distance threshold which grab or not
        @return true when mouse can grab line
    */
	bool isSelectLine(world_point2d &point,
					  world_point2d &linePoint0, world_point2d &linePoint1,
					  int distance);

	/**
		���̒������擾
        get line's length (calc length, not get from its structure::length)
		@param index ���f�[�^�̃C���f�b�N�X
        @return line(index)'s length
	*/
	double getLineLength(int index);

	/*
		���̒����𓾂�
        get line's length from two world points
        
	*/
	double getPointsDistance(world_point2d& pointA, world_point2d& pointB);

	/**
		<jp>�������X�V����
		<en>Fix line_data up
		@param isDeleteOldSide descide which deletes or not �g���Ă��Ȃ��Ǐ����폜���邩
	*/
	void fixLine(int index, bool isDeleteOldSide);

	////////////////////////////////////////////////////////////////////////
	///////////	 Sides	////////////////////////////////////////////////////

    /**
        <jp>�Ǐ����Z�b�g�A�b�v���܂�
        <en>
    */
	void fixSide(int sideIndex);

	///////////////////////////////////////////////////////////////////////
	///////////	 Groups	 //////////////////////////////////////////////////
	/**
		�}�E�X�����ɑI������Ă���A�C�e�����N���b�N���Ă��邩�m���߂܂�
		<en>is point in select groups?
		@param px point locatin(view)				�}�E�X�ʒu�i�r���[���W�j
		@param offsetViewX offset(view)				�r���[���W�Y��
		@param offsetWorldX offset(world)			�����W
		@param pointDistance distance as nearby		�_�p臒l
		@param lineDistance distance as nearby		���p臒l
		@param selectInfo select group for check	�O���[�v�N���X
	*/
	bool isPointInSelection(int px, int py,
							int offsetViewX, int offsetViewY,
							int offsetWorldX, int offsetWorldY,
							int pointDistance,
							int lineDistance,
							int objectDistance,
							hpl::aleph::map::HPLSelectData* selectInfo,
							int heightMax, int heightMin, int div);

    ///////////////////////////////////////////////////////////////////////////////
    ////// Polygon ////////////////////////////////////////////////////////////////

    /**
        �|���S�������݂Ƃ��Đ��������ǂ����𔻒肵�܂�
        @param index index of polygon which is checked �����Ώۂ̃|���S���C���f�b�N�X
    */
    bool isValidPolygon(int index);

    /**
        ��̐����D�萬���p�x�����߂܂�
        @param pIndexA1,2 ����A1-A2�̓_�C���f�b�N�X
        @param pIndexB1,2 ����B1-B2�̓_�C���f�b�N�X
    */
    double getTwoLinesDegree(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);
    double getTwoLinesRadian(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);

    /**
        �|���S�����Z�b�g�A�b�v���܂�
        ��̓I�ɂ́A
        �E�_�̏��ԁA���̏��Ԃ����v���ɐ����܂�
        �ESide�f�[�^����ݒ肵�܂�
        �E
    */
    //void setupPolygon(int index);
};
};
};
#endif
