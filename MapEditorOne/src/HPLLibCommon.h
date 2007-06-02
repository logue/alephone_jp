#pragma once

#include <math.h>
#include <vector>
#include <map>

#include "map.h"
#include "wad.h"

#include "HPLLib/HPLAlephLib.h"

using namespace std;

/**
    calculate degree between two connected lines
*/
double getDegreeBetweenTwoLines(int lineIndex0, int lineIndex1);

/**
    check is polygon valid
*/
bool isPolygonValid(int polygonIndex);

//SDL
/**
    get pixel data 
    !!! must lock screen before using !!!
*
Uint32 getpixel(SDL_Surface *surface, int x, int y);
Uint32 getpixel(Uint8* pixels, int pitch, int bpp,  int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
*/
void addAnnotationText(world_point2d& point, string text);

//get polygon index which include the point
//return NONE when not found
inline int getPolygonIdPointIn(world_point2d& point)
{
    for(int i = 0; i < (int)PolygonList.size(); i ++){

		if(hpl::aleph::map::isPointInPolygon(point, i))
		{///point_in_polygon(i, &point)){
            return i;
        }
    }
    return NONE;
}

/**
    search polygon include point stated.
    @return points included in a new or existing valid polygon
        if no points returned, no valid polygon can create or found
*/
vector<int> getValidPoligon(world_point2d& point, short maxHeight, short minHeight);

/**
    get point nearest the one
*/
int getNearestPoint(world_point2d& pointFrom);


// get nearest point in the height range
int getNearestPoint(world_point2d& pointFrom, short maxHeight, short minHeight);

// is point in range
bool isPointInHeight(endpoint_data* point, short maxHeight, short minHeight);

//data���\�[�g����
//void sortMap(int *indexes, int max, int* datas);

/**
    get point list ordered by length from a point
*/
void getPointListLengthOrder(world_point2d& pointFrom, int* indexes);

/**
    �w�肵���_�Ɛ��Ōq�����Ă���_��T��
*/
vector<int> getLineSharedPoints(int fromPointIndex);

/**
    <jp>�w�肵���_���܂ސ����擾
    <en>get lines include the point
*/
vector<int> getLineIncludePoint(int pointIndex);

/**
    3�̘A������_���������̊p�x���E����180�x�ȓ���
    [0]�n�_
    [1]�o�R�_
    [2]�I�_
*/
bool isThreeClockwisePointsInValidDegree(int pointIndexes[3]);

/** 
    <jp>��̓_�����������擾���܂��B���s���͕���
    <en>
    @return -1 when failed
*/
int getLineFromPoints(int point0, int point1);
