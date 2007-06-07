#ifndef _HPL_MAP_TOOL_
#define _HPL_MAP_TOOL_

#include <math.h>
#include <vector>
#include <map>
#include <string>

#include "map.h"
#include "wad.h"

//#include "HPLMath.h"
#include "HPLSelectData.h"

const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

const int NUMBER_OF_LANDSPACES = 4;
//�_�ƃN���b�N�n�_�̋���������ȉ��ł���ΑI������B
//���X�g���ɒT������
const int POINT_DISTANCE_EPSILON = 5;
const int OBJECT_DISTANCE_EPSILON = 8;
const int LINE_DISTANCE_EPSILON = 5;




//���ނł��Ȃ�����
namespace hpl{
namespace aleph{
    //����
    typedef struct Information_tag{
        std::string jname;
    }Information;

    //�l������
    typedef struct InformationBinded_tag{
        std::string jname;
        int bind;
    }InformationBinded;

    /**
        �^�O�f�[�^��������擾���܂�
        load data strings from file
        @param filePath �t�@�C���p�X file path
        @param maxLines �ő�s��
        @param infos �o��
    */
    void loadInformation(const char* filePath, int maxLines, std::vector<std::string>* infos);

    /**
		vector�̑�index�Ԗڂ̗v�f���폜���܂�
		�����ӁIindex+1�Ԗڈȍ~���S�Ă����I
	*/
	template<class T>
	void removeIndexInVector(std::vector<T>* items, int index)
	{
		if(index < 0 || index >= (int)items->size()){
			return;
		}
		std::vector<T>::iterator it = items->begin();
		it += index;
		items->erase(it);
	}
};
};

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
        1:calc length
        2:set side
		@param isDeleteOldSide descide which deletes or not �g���Ă��Ȃ��Ǐ����폜���邩
	*/
	void fixLine(int index, bool isDeleteOldSide);

    /**
        ����������\������_�ɂ���Ď擾���܂�
        get line index with two point indexes
        @return �������݂��Ȃ��ꍇNONE
    */
    int getLineIndexFromTwoLPoints(int pindex0, int pindex1);

	/**
		�_�����L������C���f�b�N�X�̃��X�g���擾���܂�
	*/
	std::vector<int> getLineIndexesIncludePoint(int endpointIndex);

	/**
		�������L����|���S���̃��X�g���擾���܂�
		line_data�ɂ͉E���|���S���ƍ����|���S���̃C���f�b�N�X�������Ă�̂ł�������p���Ă�����
		** ����g���Ηǂ������c
	*
	std::vector<int> getPolygonIndexesIncludeLine(int lineIndex);
	*/
	/**
		�_�����L����|���S���̃��X�g���擾���܂�
	*/
	std::vector<int> getPolygonIndexesIncludePoint(int endpointIndex);
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
        ���W�����͂ރ|���S���̂����A�|���S���Ƃ��Đ������Ă�����̂��������܂�
        ���łɃ|���S�������݂��Ă���ꍇ�͖������܂�
        @param wpoint �T����_�B�������͂ރ|���S����T��
        @return �|���S���̎��f�[�^���B��������ɐ�������Ɨǂ��B�f�[�^��createPolygon�Ő������ׂ�
    */
    std::vector<polygon_data> searchValidPolygon(world_point2d wpoint);

    /**
        ��̐����D�萬���p�x�����߂܂�
        @param pIndexA1,2 ����A1-A2�̓_�C���f�b�N�X
        @param pIndexB1,2 ����B1-B2�̓_�C���f�b�N�X
    */
    double getTwoLinesDegree(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);
    double getTwoLinesRadian(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);

    /**
        �|���S���f�[�^�����܂�
        TODO
    */
    polygon_data createPolygon(int epindexes[8]);

    /**
        ���E���W����|���S���f�[�^�����܂�
        TODO ������
        @param points ���E���W
        @param ep �������ꂽ�_�f�[�^
        @param ld �������ꂽ���f�[�^
        @param n n�p�`
    */
    polygon_data createPolygon(world_point2d points[], endpoint_data epd[], line_data ld[],
        int n);

//    void addNewPoint(endpoint_data point);


    /**
        �|���S�����Z�b�g�A�b�v���܂�
        ��̓I�ɂ́A
        �E�_�̏��ԁA���̏��Ԃ����v���ɐ����܂�
        �ESide�f�[�^����ݒ肵�܂�
        �E
    */
    //void setupPolygon(int index);

    /**
        �w�肵���_���|���S���̒��ɑ��݂��邩�ǂ������m���߂܂�
        @
    */
    bool isPointInPolygon(int viewPX, int viewPY, int polygonIndex,
        int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety);
    bool isPointInPolygon(world_point2d& wpoint, int polygonIndex);

    ///////////////////////////////////////////////////////////////////////////////
    ////////// add delete modify it /////////////////////////////////////////////////
	/**
		�_����ǉ����܂�
		@param ep �ǉ�����_�f�[�^�i�l�n���Ȃ̂ŃR�s�[����܂��j
		@return �ǉ����ꂽ�_�̃C���f�b�N�X�l
	*/
	int addEndpoint(endpoint_data ep);
	int addLine(line_data line);
	int addSide(side_data side);
	int addPolygon(polygon_data polygon);
	int addMapSavedObject(map_object object);
	int addAnnotation(map_annotation annotation);

	/**
		�_�����폜���܂�
		@param index �폜�Ώۂ̃C���f�b�N�X
		@return �폜���s���ɋU�B�C���f�b�N�X���������Ȃ��ꍇ�Ȃ�
	*/
	bool deleteEndpoint(int index);
	bool deleteLine(int index);
	bool deleteSide(int index);
	bool deletePolygon(int index);
	bool deleteMapSavedObject(int index);

    /**
        �|���S�������C�����܂�
        TODO
    */
    void fixPolygon(int pindex);

    /**
        �Ɨ������|���S���f�[�^��ǉ����܂�
		�|���S���f�[�^��|�C���g�f�[�^�Ȃǂ�����ۂɒǉ����܂�
    */
    void addNewPolygon(polygon_data& pdata, endpoint_data epd[], line_data ld[], int n);
    void addNewPolygon(world_distance points[][2], int n);
    void addNewPolygon(world_point2d points[], int n);

	////////////////////////////////////////////////
	////// objects ////////////////////////////////
	/**
		�����z�u���̐ݒ�
		@param objectType �I�u�W�F�N�g�^�C�v
			_saved_item
			_saved_monster
		@param index �ǂ̃I�u�W�F�N�g�̏����͈ʒu�������邩
		@param num ����������l
		@return �����̌��ʂ̐��B�z�u��񂪓����Ȃ��ꍇNONE(����)
	*/
	int addInitialPlacementNum(int objectType, int index, int num);
	/**
		�z�u�����擾
		@param objectType �I�u�W�F�N�g�^�C�v
			_saved_item
			_saved_monster
		@param index �ǂ̃I�u�W�F�N�g�̏����͈ʒu�������邩
		@return �z�u���B�z�u���⃉���_���}�b�N�X�Ȃ�
			�擾�ł��Ȃ��ꍇ��NULL���Ԃ���܂�
	*/
	struct object_frequency_definition* getPlacementData(int objectType, int index);

};
};
};
#endif
