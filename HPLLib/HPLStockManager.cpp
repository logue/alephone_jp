#include "HPLStockManager.h"
#include "HPLMapTool.h"

#include "map.h"

hpl::aleph::HPLStockManager::HPLStockManager()
{
}
hpl::aleph::HPLStockManager::~HPLStockManager()
{
}

//�|���S�������������ǂ������������܂�(������)
bool hpl::aleph::HPLStockManager::isPolygonValidityStored(int polyIndex)
{
	if(polyIndex < 0){
		return false;
	}else if(polyIndex >= (int)this->polygonValidity.size()){
		//���݂��Ȃ�����
		//�X�V
		updatePolygonValidityStored();
		if(polyIndex >= (int)this->polygonValidity.size()){
			//����ł�����ς�Ȃ�������
			return false;
		}
	}

	return this->polygonValidity[polyIndex];
}

//�|���S�������������X�V���܂�
void hpl::aleph::HPLStockManager::updatePolygonValidityStored()
{
	this->polygonValidity.clear();
	for(int i = 0; i < (int)PolygonList.size(); i ++){
        bool isValid = hpl::aleph::map::isValidPolygon(i);
		this->polygonValidity.push_back(isValid);
	}

    //���łɍ��������\�[�g����
    //this->polygonDrawOrderByHeight.clear();
}

/**
    �폜�����X�V���܂��B
    ��̓I�ɂ�dynamic_world�̒l�ɍ��킹�ėv�f���𑝉������܂�
    �������͍폜�Ώۂł͂Ȃ��̂ł��ׂ�false�ł��B
    ���ɁA���ۂ̃f�[�^�𒲂ׂĊ֘A����������̂�����ɍ폜���܂��B
    -endpoint_data
        [delete point]
        lines depend this       -> delete line
        polygon depends this    -> delete polygon (but no need to do, because deleted line will delete polygon)
                                    <jp>�ˑ����Ă�����������Ƃ��Ƀ|���S���������Ă����̂Ŗ������܂�
        [no delete]
        polygon_index           -> set NONE when polygon is to be deleted

    -line_data
        [delete line]
        endpoints depend this   -> none necessity to do
                                    <jp>�_�͎c��܂��B
        polygon depends this    -> delete
        sides depend this       -> delete

        [no delete]
        *_polygon_owner         -> set NONE when polygon is to be deleted
        *_polygon_side_owner    -> set NONE when side is to be deleted

    -polygon_data
        [delete polygon]
        points depend this      -> nope
                                    <jp>�_�͎c����
        lines depend this       -> nope
        sides depend this       -> delete side
        objects depend this     -> delete them

        [no delete]
        endpoint_indexes, line_indexes  -> no to do
        side_indexes            -> set NONE when sides are to be deleted
        first_object_index      -> set NONE when no objects are on this

        TODO line��S��solid�ɂ���

    -side_data
        [delete side]
        nope

        [no delete]
        line_index              -> nope
                                    <jp>���������Ă����Side���������̂ŉ������Ȃ��Ă悢
        polygon_index           -> nope

    -map_object
        [delete object]
        nope

        [no delete]
        polygon_index           -> nope

*/
void hpl::aleph::HPLStockManager::updateDeletes()
{
    //points
    for(int i = delPoints.size(); i < dynamic_world->endpoint_count; i ++){
        delPoints.push_back(false);
    }
    for(int i = delLines.size(); i < dynamic_world->line_count; i ++){
        delLines.push_back(false);
    }
    for(int i = delSides.size(); i < dynamic_world->side_count; i ++){
        delSides.push_back(false);
    }
    for(int i = delPolygons.size(); i < dynamic_world->polygon_count; i ++){
        delPolygons.push_back(false);
    }
    for(int i = delObjects.size(); i < SavedObjectList.size(); i ++){
        delObjects.push_back(false);
    }

    //�_�֘A�̍폜�Ώې��� <en> endpoints
    for(int i = 0; i < (int)delPoints.size(); i ++){
        if(delPoints[i]){
            //�폜�Ώ�
            //���L���Ă�������폜���� (���Ƌ��ˑ��֌W strong depenence -> lines )
            std::vector<int> lineIndexes = hpl::aleph::map::getLineIndexesIncludePoint(i);
            for(int j = 0; j < (int)lineIndexes.size(); j ++){
                delLines[lineIndexes[i]] = true;
            }
            //�|���S�������ˑ��֌W�����A����������Ă����̂ŕ��u
        }else{
            //�c��
            endpoint_data* ep = get_endpoint_data(i);
            if(ep->supporting_polygon_index != NONE){
                assert(get_polygon_data(ep->supporting_polygon_index));
                if(delPolygons[ep->supporting_polygon_index]){
                    //�֘A�|���S�����������Ȃ�ΑΉ���؂��Ă���
                    ep->supporting_polygon_index = NONE;
                }
            }
        }
    }

    //�� <en> lines
    for(int i = 0; i < (int)delLines.size(); i ++){
        line_data* line = get_line_data(i);
        assert(line);
        if(delLines[i]){
            //�֘A����|���S�����폜����
            if(line->clockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->clockwise_polygon_owner));
                delPolygons[line->clockwise_polygon_owner] = true;
            }
            if(line->counterclockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->counterclockwise_polygon_owner));
                delPolygons[line->counterclockwise_polygon_owner] = true;
            }
            //����Side������
            if(line->clockwise_polygon_side_index != NONE){
                assert(get_side_data(line->clockwise_polygon_side_index));
                delSides[line->clockwise_polygon_side_index] = true;
            }
            if(line->counterclockwise_polygon_side_index != NONE){
                assert(get_side_data(line->counterclockwise_polygon_side_index));
                delSides[line->counterclockwise_polygon_side_index] = true;
            }
        }else{
            //�c��
            //�_�������Ă�����c���Ă���킯���Ȃ��̂ōl�����Ȃ��Ă悢

            //�|���S���������Ă�����֘A��؂�
            if(line->clockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->clockwise_polygon_owner));
                if(delPolygons.at(line->clockwise_polygon_owner)){
                    line->clockwise_polygon_owner = NONE;
                }
            }
            if(line->counterclockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->counterclockwise_polygon_owner));
                if(delPolygons[line->counterclockwise_polygon_owner]){
                    line->counterclockwise_polygon_owner = NONE;
                }
            }

            //Side�������Ă�����֘A��؂�
            if(line->clockwise_polygon_side_index != NONE){
                assert(get_side_data(line->clockwise_polygon_side_index));
                if(delSides.at(line->clockwise_polygon_side_index)){
                    line->clockwise_polygon_side_index = NONE;
                }
            }
            if(line->counterclockwise_polygon_side_index != NONE){
                assert(get_side_data(line->counterclockwise_polygon_side_index));
                if(delSides[line->counterclockwise_polygon_side_index]){
                    line->counterclockwise_polygon_side_index = NONE;
                }
            }
        }
    }

    //�|���S��
    for(int i = 0; i < (int)delPolygons.size(); i ++){
        polygon_data* poly = get_polygon_data(i);
        int n = poly->vertex_count;
        if(delPolygons[i]){
            //�폜�Ώ�
            //�֘A����side������
            for(int j = 0; j < n; j ++){
                if(poly->side_indexes[j] != NONE){
                    assert(get_side_data(poly->side_indexes[j]));
                    delSides[poly->side_indexes[j]] = true;
                }
            }

            //�I�u�W�F�N�g������
            for(int j = 0; j < (int)SavedObjectList.size(); j ++){
                map_object* obj = &SavedObjectList[j];
                assert(obj);
                if(obj->polygon_index == i){
                    delObjects[j] = true;
                }
            }
        }else{
            //�c��
            for(int j = 0; j < n; j ++){
                if(poly->side_indexes[j] != NONE){
                    assert(get_side_data(poly->side_indexes[j]));
                    if(delSides[poly->side_indexes[j]]){
                        poly->side_indexes[j] = NONE;
                    }
                }
            }

            //����Ă���I�u�W�F�N�g������Ȃ��ꍇ��first_object��NONE�ɂ���
            if(delObjects[poly->first_object]){
                int firstObjIndex = NONE;
                for(int j = 0; j < (int)SavedObjectList.size(); j ++){
                    if(!delObjects[j]){
                        map_object* obj = &SavedObjectList[j];
                        assert(obj);
                        if(obj->polygon_index == i){
                            firstObjIndex = j;
                            break;
                        }
                    }
                }
                poly->first_object = firstObjIndex;
            }
        }
    }

    //Side
    for(int i = 0; i < (int)delSides.size(); i ++){
        side_data* side = get_side_data(i);
        if(delSides[i]){
            //����
        }else{
            //�����Ȃ�
        }
    }

    //objects
    for(int i = 0; i < (int)delObjects.size(); i ++){
        if(delObjects[i]){
            //�����Ȃ�
        }else{
            //�����Ȃ�
        }
    }
}

/**
    �폜����������
    ���ۂɂ�clear�������updateDeletes()���Ă�ł邾��
*/
void hpl::aleph::HPLStockManager::resetDeletes()
{
    delPoints.clear();
    delLines.clear();
    delSides.clear();
    delPolygons.clear();
    delObjects.clear();

    this->updateDeletes();
}

bool hpl::aleph::HPLStockManager::deletePoint(int index)
{
    assert(get_endpoint_data(index));
    this->delPoints[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deleteLine(int index)
{
    assert(get_line_data(index));
    this->delLines[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deletePolygon(int index)
{
    assert(get_polygon_data(index));
    this->delPolygons[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deleteSide(int index)
{
    assert(get_side_data(index));
    this->delSides[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deleteObject(int index)
{
    assert(index >= 0 && index < SavedObjectList.size());
    this->delObjects[index] = true;
    return true;
}
