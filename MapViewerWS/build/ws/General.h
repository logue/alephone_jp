#ifndef _GENERAL_
#define _GENERAL_

#include <vector>
#include <string>

extern std::vector<std::string> mapNameList;
extern int selectLevel;
extern int zoomDivision, offsetx, offsety;
extern int nowMousePointX, nowMousePointY, oldMousePointX, oldMousePointY;

const int NUMBER_OF_POLYGON_TYPE = 24;
const int ZOOM_DIVISION_STEP = 5;
const int ZOOM_DIVISION_MAX = 200;
const int ZOOM_DIVISION_MIN = 1;
const int ZOOM_DIVISION_DEFAULT = 100;
const int OFFSET_X_WORLD = 32768;
const int OFFSET_Y_WORLD = 32768;
const int NUMBER_OF_GLID = 5;

const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;

const int NUMBER_OF_LANDSPACES = 4;
//�_�ƃN���b�N�n�_�̋���������ȉ��ł���ΑI������B
//���X�g���ɒT������
const int POINT_DISTANCE_EPSILON = 5;
const int OBJECT_DISTANCE_EPSILON = 8;
const int LINE_DISTANCE_EPSILON = 5;

#endif
