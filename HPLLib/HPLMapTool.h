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
		<jp>�w�肵���_���N���b�N�ł��Ă��邩�̔�����s���܂��B
		<en>is view-point near world-point?
		@param viewPX	point(mouse/view)		�r���[���W�i�X�N���[�����W�j
		@param worldPX	point(world)			�ΏۂƂ���_�i�����W�j
		@param offsetViewX offset of view		�r���[���W�̃Y��
		@param offsetWorldX offset of world		�����W�̃Y��
		@param distance check distance			臒l
	*/
	bool isSelectPoint(int viewPX, int viewPY, 
					   int worldPX, int worldPY,
					   int offsetViewX, int offsetViewY,
					   int offsetWorldX, int offsetWorldY,
					   int div,
					   int distance);
	bool isSelectPoint(world_point2d &point0, world_point2d &point1,
					   int distance);
	
	/**
		<jp>�w�肵���_���O���b�h�ɍ��킹�A���̍��W�𓾂܂�
		<en>snap point to grid
		@param srcPoint
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
	double getPointsDistance(world_point2d& pointA, world_point2d& pointB);

	/**
		<jp>�������X�V����
		<en>Fix line_data up
		@param isDeleteOldSide descide which deletes or not �g���Ă��Ȃ��Ǐ����폜���邩
	*/
	void fixLine(int index, bool isDeleteOldSide);

	////////////////////////////////////////////////////////////////////////
	///////////	 Sides	////////////////////////////////////////////////////

	void fixSide(int leftPolyIndex, int rightPolyIndex, int sideIndex,
		int lineIndex, bool isDeleteOldSide);

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
