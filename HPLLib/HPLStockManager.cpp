#include "HPLStockManager.h"

#include "map.h"

hpl::aleph::HPLStockManagerHPLStockManager()
{
}
hpl::aleph::HPLStockManager~HPLStockManager()
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
    �E�_�폜��
        �[�_�ɂȂ��Ă����������
        �i�|���S�������������̕����ōs���j
        �iSide�AObject�͖��֌W�j

        �ˑ����ڂ͂Ȃ�

    �E���폜��
        Side���폜
        �|���S��������
        �i�_�͂���ȏ�����Ȃ��B�I�u�W�F�N�g�͖��֌W�j

        �ˑ����ڂȂ�

    �ESide�폜��
        ���݂Ƃ��Ă͑��ƓƗ����Ă���̂ŁA���ɏ������̂͂Ȃ�

        ����Side��NONE��
        �|���S����side_indexes�̊Y��������NONE��
        
    �E�|���S���폜��
        ��ԂɂȂ�̂ŁASide���폜�iline_data::clockwise_polygon_owner�ȂǂŒ��ׂ�j
        ����Ă���I�u�W�F�N�g���폜
        
        �_�A���ASide�̃|���S���ԍ���NONE��

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

    //�_�֘A�̍폜�Ώې���
    for(int i = 0; i < (int)delPoints.size(); i ++){
        if(delPoints[i]){
            //�폜�Ώ�
            //���L���Ă�������폜����
            std::vector<int> lineIndexes = hpl::aleph::map::getLineIndexesIncludePoint(i);
            for(int j = 0; j < (int)lineIndexes.size(); j ++){
                delLines[lineIndexes[i]] = true;
            }
        }else{
            //�c��
            endpoint_data* ep = get_endpoint_data(i);
            if(ep->supporting_polygon_index != NONE && 
                get_polygon_data(ep->supporting_polygon_index) != NULL &&
                delPolygon[ep->supporting_polygon_index])
            {
                //�֘A�|���S�����������Ȃ�ΑΉ���؂��Ă���
                ep->supporting_polygon_index = NONE;
            }
        }
    }
    for(int i = 0; i < (int)delLines.size(); i ++){
        line_data* line = get_line_data(i);
        if(delLine[i]){
            //�֘A����|���S�����폜����
            if(line->clockwise_polygon_owner != NONE){
                delPolygons[line->clockwise_polygon_owner] = true;
            }
            if(line->counterclockwise_polygon_owner != NONE){
                delPolygons[line->counterclockwise_polygon_owner] = true;
            }
        }else{
            //�c��
            //�_�������Ă�����c���Ă���킯���Ȃ��̂ōl�����Ȃ��Ă悢
            //Side�������Ă�����֘A��؂�
            if(delSides.at(line->clockwise_polygon_side_index)){
                line->clockwise_polygon_side_index = NONE;
            }
            if(delSides[line->counterclockwise_polygon_side_index]){
                line->counterclockwise_polygon_side_index = NONE;
            }
        }
    }

    //Side
    for(int i = 0; i < (int)delSides.size(); i ++){
        side_data* side = get_side_data(i);
        if(delSides[i]){
            //����
            //�����烊���N���O������
            //�c�̂͂��łɏI����Ă���
        }else{
            //�c��
            //�֘A����C���f�b�N�X��NONE�ɂ���
            if(delLines[side->line_index]){
                side->line_index = NONE;
            }
            if(delPolygon[side->polygon_index]){
                //���g���폜����
                side->polygon_index = NONE;
            }
        }
    }
    //�|���S��
    for(int i = 0; i < (int)delPolygons.size(); i ++){
        polygon_data* poly = get_polygon_data(i);
        if(delPolygons[i]){
            //�폜�Ώ�
            //�I�u�W�F�N�g������
            
        }else{
            //�c��
        }
    }
}

/**
    �폜����������
    ���ۂɂ�clear�������daupteDeletes()���Ă�ł邾��
*/
void hpl::aleph::HPLStockManager::resetDeletes()
{
}

bool hpl::aleph::HPLStockManager::deletePoint(int index)
{
    if(get_endpoint_data(index) == NULL){
        return false;
    }
    this->delPoints[index] = true;
}
bool hpl::aleph::HPLStockManager::deleteLine(int index)
{
}
bool hpl::aleph::HPLStockManager::deletePolygon(int index)
{
}
bool hpl::aleph::HPLStockManager::deleteSide(int index)
{
}
bool hpl::aleph::HPLStockManager::deleteObject(int index)
{
}
