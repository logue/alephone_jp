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
*/
void hpl::aleph::HPLStockManager::updateDeletes()
{
    //points
    for(int i = delPoints.size(); i < dynamic_world->endpoint_count; i ++){

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
