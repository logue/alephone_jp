#include "HPLStockManager.h"
#include "HPLMapTool.h"

#include "map.h"
#include "platforms.h"

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
    �T�C�Y�����ۂ̂��̂ɍ��킹�܂�
*/
void hpl::aleph::HPLStockManager::resizeDeletes()
{
    //points
    for(int i = (int)delPoints.size(); i < dynamic_world->endpoint_count; i ++){
        delPoints.push_back(false);
    }
    for(int i = (int)delLines.size(); i < dynamic_world->line_count; i ++){
        delLines.push_back(false);
    }
    for(int i = (int)delSides.size(); i < dynamic_world->side_count; i ++){
        delSides.push_back(false);
    }
    for(int i = (int)delPolygons.size(); i < dynamic_world->polygon_count; i ++){
        delPolygons.push_back(false);
    }
    for(int i = (int)delObjects.size(); i < (int)SavedObjectList.size(); i ++){
        delObjects.push_back(false);
    }
    for(int i = (int)delPlatforms.size(); i < (int)PlatformList.size(); i ++){
        delPlatforms.push_back(false);
    }
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
    this->resizeDeletes();

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
            if(poly->first_object != NONE){
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

	//platform
	for(int i = 0; i < (int)delPlatforms.size(); i ++){
		platform_data* platform = &PlatformList[i];
		int polyIndex = platform->polygon_index;
		if(polyIndex == NONE || delPolygons[polyIndex]){
			delPlatforms[i] = true;
		}else{
			if(delPlatforms[i]){
				//���̃v���b�g�t�H�[���͑��݂��Ȃ�
			}else{
				//�������Ȃ�
			}
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
#ifdef _WXDEBUG_
    wxASSERT(get_endpoint_data(index));
#endif
    this->delPoints[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deleteLine(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(get_line_data(index));
#endif
    this->delLines[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deletePolygon(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(get_polygon_data(index));
#endif
    this->delPolygons[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deleteSide(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(get_side_data(index));
#endif
    this->delSides[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deleteObject(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(index >= 0 && index < (int)SavedObjectList.size());
#endif
    this->delObjects[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deletePlatform(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(index >= 0 && index < (int)PlatformList.size());
#endif
    this->delPlatforms[index] = true;
    //updateDeletes();
    return true;
}

/**
	�I�������X�V
*/
void hpl::aleph::HPLStockManager::updateSelects(hpl::aleph::map::HPLSelectData& sel)
{
	//������
	this->selPoints.clear();
	this->selPoints.resize(EndpointList.size());
	this->selLines.clear();
	this->selLines.resize(LineList.size());
	this->selPolygons.clear();
	this->selPolygons.resize(PolygonList.size());
	this->selObjects.clear();
	this->selObjects.resize(SavedObjectList.size());
	this->selSides.clear();
	this->selSides.resize(SideList.size());

	//points
	for(int i = 0; i < (int)EndpointList.size(); i ++){
		this->selPoints[i] = sel.containsPoint(i);
	}

	//lines
	for(int i = 0; i < (int)LineList.size(); i ++){
		this->selLines[i] = sel.containsLine(i);
	}

	//polygons
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		this->selPolygons[i] = sel.containsPolygon(i);
	}

	//objects
	for(int i = 0; i < (int)SavedObjectList.size(); i ++){
		this->selObjects[i] = sel.containsObject(i);
	}

	//sides
	for(int i = 0; i < (int)SideList.size(); i ++){
		this->selSides[i] = sel.containsSide(i);
	}
}
/**
	�I�����̎擾
*/
bool hpl::aleph::HPLStockManager::isSelectPoint(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPoints.size());
#endif
	return this->selPoints[index];
}
bool hpl::aleph::HPLStockManager::isSelectLine(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selLines.size());
#endif
	return this->selLines[index];
}
bool hpl::aleph::HPLStockManager::isSelectPolygon(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPolygons.size());
#endif
	return this->selPolygons[index];
}
bool hpl::aleph::HPLStockManager::isSelectSide(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selSides.size());
#endif
	return this->selSides[index];
}
bool hpl::aleph::HPLStockManager::isSelectObject(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selObjects.size());
#endif
	return this->selObjects[index];
}
//�ݒ�
void hpl::aleph::HPLStockManager::setSelectPoint(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPoints.size());
#endif
	this->selPoints[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectLine(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selLines.size());
#endif
	this->selLines[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectPolygon(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPolygons.size());
#endif
	this->selPolygons[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectSide(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selSides.size());
#endif
	this->selSides[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectObject(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selObjects.size());
#endif
	this->selObjects[index] = sel;
}

////////////////
bool hpl::aleph::HPLStockManager::isDeletePoint(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delPoints.size());
#endif
	return this->delPoints[index];
}
bool hpl::aleph::HPLStockManager::isDeleteLine(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delLines.size());
#endif
	return this->delLines[index];
}
bool hpl::aleph::HPLStockManager::isDeletePolygon(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delPolygons.size());
#endif
	return this->delPolygons[index];
}
bool hpl::aleph::HPLStockManager::isDeleteSide(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delSides.size());
#endif
	return this->delSides[index];
}
bool hpl::aleph::HPLStockManager::isDeleteObject(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index <(int) this->delObjects.size());
#endif
	return this->delObjects[index];
}
bool hpl::aleph::HPLStockManager::isDeletePlatform(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delPlatforms.size());
#endif
	return this->delPlatforms[index];
}
