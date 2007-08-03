#ifndef _HPL_MAP_TOOL_
#define _HPL_MAP_TOOL_

#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <set>

#include "map.h"
#include "wad.h"

//#include "HPLMath.h"
#include "HPLSelectData.h"
//#include "HPLStockManager.h"
#include "HPLError.h"


#ifdef __WXDEBUG__
#include <wx/defs.h>
#include <wx/debug.h>
#endif

namespace hpl{namespace aleph{
class HPLStockManager;
}};

/*
const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_ZOOM_DIVISION = 3;
const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;
*/


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
    void loadInformation(const char* filePath, int maxLines, hpl::aleph::Information infos[]);

	/**
		�w�肵���l�ɑ�������C���f�b�N�X�l���擾���܂�
		���݂��Ȃ��Ȃǂ̗��R�ɂ�莸�s�����ꍇ�́A�������Ԃ���܂�
	*/
	int getIndexFromInformationBinded(int value, hpl::aleph::InformationBinded infos[], int max);
	/**
		�o�C���h�^�̕����񂾂����t�@�C������ǂݍ��݂܂��B
		���蓖�Ĕԍ��͐ݒ肳��܂���
	*/
	void loadInformation(const char* filePath, int maxLines, hpl::aleph::InformationBinded infos[]);

    /**
        �J���[�f�[�^���t�@�C������ǂݍ��݂܂�
        @return ���s���ɋU
    */
    bool loadColorSetting(const char* filePath, int colors[][3], int max);

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

    /**
        �w�肵���ꏊ�ɓ_�����邩�ǂ����𓾂܂�
        @param wpoint ���[���h���W�̓_
        @param threshold �_�Ƃ̋���������ȉ��Ȃ�΋߂��ƌ��Ȃ��BView���W�n�̋������w�肷��
        @param zMin, zMax �����`�F�b�N�p
        @return ���̏ꏊ�ɓ_������΂��̃C���f�b�N�X��������܂��B
            �Ȃ����NONE
    */
    int getSelectPointIndex(world_point2d& wpoint, int threshold,
        int zMin, int zMax, int div,
                                        hpl::aleph::HPLStockManager* smgr);
    int getSelectPointIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
                                        hpl::aleph::HPLStockManager* smgr);

    /**
        ���鍂�����K��͈͓��ɂ��邩���m���߂܂�
        @return ���鍂�x�͈̔͂��K��͈͂Ƌ��L���镔���������Ȃ��ꍇ��
    */
    bool isValidHeight(int checkMin, int checkMax, int validMin, int validMax);

    /**
        �w�肵���_�����𓥂�ł���ꍇ�A���̐��ԍ���Ԃ��܂�
    */
    int getSelectLineIndex(world_point2d& wpoint, int threshold, int zMin, int zMax, int div,
                                        hpl::aleph::HPLStockManager* smgr);
    int getSelectLineIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
                                        hpl::aleph::HPLStockManager* smgr);

	/**
		�w�肵���_���|���S���𓥂�ł���ꍇ�A���̃|���S����Ԃ��܂�
	*/
	int getSelectPolygonIndex(int viewX, int viewY, int zMin, int zMax,
		int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
		hpl::aleph::HPLStockManager* smgr);

	/**
		�I���ł����A�m�e�[�V�����̃C���f�b�N�X���擾���܂�
	*/
	int getSelectAnnotationIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
                                        hpl::aleph::HPLStockManager* smgr);
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
					  int distance, int div);

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
	void fixLine(int index,// bool isDeleteOldSide,
		hpl::aleph::HPLStockManager* smgr);
	/**
        �|���S�������C�����܂�
    */
    void fixPolygon(int pindex,
		hpl::aleph::HPLStockManager* smgr);

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

    /**
        �|���S���ɏ���Ă���I�u�W�F�N�g�̃C���f�b�N�X���擾���܂�
    */
    std::vector<int> getObjectIndexesOnPolygon(int polygonIndex);

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
    std::vector<polygon_data> searchValidPolygon(world_point2d wpoint,
                                              hpl::aleph::HPLStockManager* smgr,
                                              int zMin, int zMax);

    /**
        ��̐����D�萬���p�x�����߂܂�
        @param pIndexA1,2 ����A1-A2�̓_�C���f�b�N�X
        @param pIndexB1,2 ����B1-B2�̓_�C���f�b�N�X
    */
    double getTwoLinesDegree(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);
    double getTwoLinesRadian(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);

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
	int addSide(side_data side, bool isClockwise);
	int addPolygon(polygon_data polygon);
	int addMapSavedObject(map_object object);
	int addAnnotation(map_annotation annotation);

    //TODO
    //int getEndpointIndexFromAddress(endpoint_data* ep);

    /**
        �ȗ��o�[�W����
    */
    void createPoint(world_point2d& wpoint, endpoint_data* ep);
    /**
        @param polyIndex �ڂ���|���S���̃C���f�b�N�X
    */
    void createObject(world_point2d& wpoint, int polyIndex, map_object* obj,
                                   int flags, int type, int index);

    /**
        �����̓_��p���Đ���|���S�����쐬���܂�
        <en> create new line and polygon with points already exist
    */
    void createLine(int beginPointIndex, int endPointIndex, line_data* line);
    void createPolygon(int pointIndexes[], int n, polygon_data* poly);

	/**
		�_�����폜���܂�
		@param index �폜�Ώۂ̃C���f�b�N�X
		@return �폜���s���ɋU�B�C���f�b�N�X���������Ȃ��ꍇ�Ȃ�
	*/
    /*
	bool deleteEndpoint(int index);
	bool deleteLine(int index);
	bool deleteSide(int index);
	bool deletePolygon(int index);
	bool deleteMapSavedObject(int index);
    */
    /**
        �}�b�v�A�C�e���i�_�E���ESide�E�|���S���E�I�u�W�F�N�g�j
        ���폜���܂�
        ��@�Ƃ��ẮA
        �P�F���̒[�_�ȂǁA�Q�ƌ����폜�ΏۂƂȂ��Ă���ꍇ�A
            �E�Q�Ƃ�NONE�ɂ���
            �E�������g���폜�ΏۂƂ���
        �Q�F�폜�Ώۂ��폜���Ă���
            �E�폜�ԍ��̗�����
            �E��둤��������Ă���

        @param 
    */
    bool deleteMapItems(std::vector<bool>& delPoints, std::vector<bool>& delLines,
        std::vector<bool>& delPolygons, std::vector<bool>& delSides,
		std::vector<bool>& delObjects);

	/**
		�}�b�v�A�C�e���̃C���f�b�N�X���w�肵���e�[�u���ɏ]���ĕύX���܂��B
		�O���[�o���f�[�^�ł���EndpointList�Ȃǂ����̂܂܎g���_�ɒ��ӁB
		<en> change map items' indexes with prepared index map
		@param *List ���̃}�b�v�C���f�b�N�X�ō\�����ꂽ�I�u�W�F�N�g�f�[�^
		@param *IndexMap <originalIndex, newIndex>
	*/
	void changeIndexMapping(
		std::vector<endpoint_data>& endpointList, std::vector<line_data>& lineList, 
		std::vector<polygon_data>& polygonList, std::vector<side_data>& sideList,
		std::vector<map_object>& objectList,
		int endpointIndexStart, int endpointIndexEnd,
		int lineIndexStart, int lineIndexEnd,
		int polygonIndexStart, int polygonIndexEnd,
		int sideIndexStart, int sideIndexEnd,
		int objectIndexStart, int objectIndexEnd,
		std::map<int, int>& endpointIndexMap, std::map<int, int>& lineIndexMap, 
		std::map<int, int>& polygonIndexMap, std::map<int, int>& sideIndexMap, 
		std::map<int, int>& objectIndexMap);

	/*
		�Ώۂ�EndpointList�ȂǁA���ڂ�����^�C�v
		@param *IndexStart *IndexEnd���Q��
		@param *IndexEnd [*IndexStart, *IndexEnd)�͈̔͂̃f�[�^�ɑ΂��Ē������s���܂�
	*
	void changeIndexMappingRaw(
		int endpointIndexStart, int endpointIndexEnd,
		int lineIndexStart, int lineIndexEnd,
		int polygonIndexStart, int polygonIndexEnd,
		int sideIndexStart, int sideIndexEnd,
		int objectIndexStart, int objectIndexEnd,
		std::map<int, int>& endpointIndexMap, std::map<int, int>& lineIndexMap, 
		std::map<int, int>& polygonIndexMap, std::map<int, int>& sideIndexMap, 
		std::map<int, int>& sideIndexMap);
		*/

    /**
        �Ɨ������|���S���f�[�^��ǉ����܂�
		�|���S���f�[�^��|�C���g�f�[�^�Ȃǂ�����ۂɒǉ����܂�
    */
    void addNewPolygon(polygon_data& pdata, endpoint_data epd[], line_data ld[], int n);
    void addNewPolygon(world_distance points[][2], int n);
    void addNewPolygon(world_point2d points[], int n);

    /**
        �I���f�[�^�ɃI�t�Z�b�g��ݒ肵�܂��B
        @param mx, my �}�E�X���W
        @param sel �I���f�[�^
    */
    void setupSelectDataGroupOffsets(int mx, int my, 
        hpl::aleph::map::HPLSelectData* sel, 
        int voffsetX, int voffsetY, int woffsetX, int woffsetY, int div);

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
//	int addInitialPlacementNum(int objectType, int index, int num);
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

	/**
		�w�肵��Type/Index�̐������߂܂�
	*/
	int getObjectCount(int type, int index);

	/**
		�����Type/Index�̐��𒲂ׁAinitial�l�����ݐ���菭�Ȃ��ꍇ�͍��킹��
		���ݐ���initial����菭�Ȃ��Ă��ʂɍ���Ȃ�
		@return �����ω����������ꍇ�^
	*/
	bool updateObjectInitialPlacement(int type, int index);

	///////////////////////////////////
	//	Platform
	int getPlatformIndexFromPolygonIndex(int polyIndex,
		hpl::aleph::HPLStockManager* smgr);

	/**
		Check map items' validity
		valid:		[0,n)
		invalid:	-1], [n
		-1�Ȃ��NONE�Ȃ̂�Invalid�B
		-2],[n�̏ꍇ��������Index�̐ݒ肪���������̂ŃA�T�[�V�������Ƃ΂�
		�폜�m�F�͍s��Ȃ��̂Œ���
		@return -1�Ȃ�U�B�������l�Ȃ�^�B
	*/
	template<class T>
	bool isValidIndex(int index, T numMax);
};
};
};

int getKeyByValue(std::map<int, int>& indexMap, int targetValue);
#endif
