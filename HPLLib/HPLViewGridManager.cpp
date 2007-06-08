#include "HPLViewGridManager.h"
#include <memory.h>
#include "HPLMath.h"
#include <limits.h>

/**
    �r���[�̎���
    the dimension of view window
*/
const int VIEW_DIMENSION = 2;

hpl::aleph::view::HPLViewGridManager::HPLViewGridManager()
{
    //�I�t�Z�b�g������
    this->viewOffset[0] = viewOffset[1] = 0;
    //����Z��������
    this->zoomReset();
    //���������ő�l
    this->setViewHeightMax(SHRT_MAX);
    this->setViewHeightMin(SHRT_MIN);
}
void hpl::aleph::view::HPLViewGridManager::setProp(ZoomProperties *zoomProp)
{
    memcpy(&this->zoomProperties, zoomProp, sizeof(struct ZoomProperties));
    //����Z��������
    this->zoomReset();
}

hpl::aleph::view::HPLViewGridManager::~HPLViewGridManager()
{
}

/**
    �g�嗦�擾
    <en>get zoom division
*/
int hpl::aleph::view::HPLViewGridManager::getZoomDivision()
{
    return zoomDivision;
}
/**
    zoom in
*/
void hpl::aleph::view::HPLViewGridManager::zoomIn(int viewW, int viewH)
{
    this->addZoom(-this->zoomProperties.zoomDivisionStep, viewW, viewH);
}

/**
    zoom out
*/
void hpl::aleph::view::HPLViewGridManager::zoomOut(int viewW, int viewH)
{
    this->addZoom(this->zoomProperties.zoomDivisionStep, viewW, viewH);
}
/**
    �g�嗦������
*/
void hpl::aleph::view::HPLViewGridManager::zoomReset()
{
    this->zoomDivision = this->zoomProperties.zoomDivisionDefault;
}



/**
    �Y�[������
    @param step �ω���
*/
void hpl::aleph::view::HPLViewGridManager::addZoom(int step, int viewW, int viewH)
{
    int oldZoomDiv = this->zoomDivision;
    
    //�g�劄����臒l���z�����瑝�����xDown
    //<en>set zoom step small when division num is over threshold
    if(zoomDivision < this->zoomProperties.zoomDivStepThreshold){
        step = hpl::math::sgn<int>(step) * this->zoomProperties.zoomDivisionStepDetail;
    }
    this->zoomDivision += step;

    //adjustment
    if(this->zoomDivision < this->zoomProperties.zoomDivisionMin){
        this->zoomDivision = this->zoomProperties.zoomDivisionMin;
    }else if(this->zoomDivision > this->zoomProperties.zoomDivisionMax){
        this->zoomDivision = this->zoomProperties.zoomDivisionMax;
    }

    int oldOffset[2] = {this->viewOffset[0], this->viewOffset[1]};
    int center[2] = {viewW / 2, viewH / 2};

    int newZoomDiv = this->zoomDivision;
    //�ʒu�C��
    for(int i = 0; i < VIEW_DIMENSION; i ++){
        int a = center[i] - oldOffset[i];
        this->viewOffset[i] = center[i] - a * oldZoomDiv / newZoomDiv;
    }
}

//void setOldMousePoint(int x, int y);
/**
    �}�E�X���W���Z�b�g���܂�
    set mouse position info (view coordinate)
*/
void hpl::aleph::view::HPLViewGridManager::setNewMousePoint(int x, int y)
{
    for(int i = 0; i < VIEW_DIMENSION; i ++){
        this->oldMousePoint[i] = this->newMousePoint[i];
    }
    this->newMousePoint[0] = x;
    this->newMousePoint[1] = y;
}
void hpl::aleph::view::HPLViewGridManager::getNewMousePoint(int* point)
{
    for(int i = 0; i < VIEW_DIMENSION; i ++){
        point[i] = this->newMousePoint[i];
    }
}
void hpl::aleph::view::HPLViewGridManager::getOldMousePoint(int* point)
{
    for(int i = 0; i < VIEW_DIMENSION; i ++){
        point[i] = this->oldMousePoint[i];
    }
}

void hpl::aleph::view::HPLViewGridManager::setOffset(int x, int y)
{
    this->viewOffset[0] = x;
    this->viewOffset[1] = y;
}
void hpl::aleph::view::HPLViewGridManager::getOffset(int* point)
{
    for(int i = 0; i < VIEW_DIMENSION; i ++){
        point[i] = this->viewOffset[i];
    }
}

void hpl::aleph::view::HPLViewGridManager::setViewHeightMax(int max)
{
    this->viewHeightMax = max;
}
void hpl::aleph::view::HPLViewGridManager::setViewHeightMin(int min)
{
    this->viewHeightMin = min;
}
int hpl::aleph::view::HPLViewGridManager::getViewHeightMax()
{
    return this->viewHeightMax;
}
int hpl::aleph::view::HPLViewGridManager::getViewHeightMin()
{
    return this->viewHeightMin;
}
void hpl::aleph::view::HPLViewGridManager::setRevealHiddenLines(bool show)
{
    this->isRevealHiddenLines_ = show;
}
bool hpl::aleph::view::HPLViewGridManager::isRevealHiddenLines()
{
    return this->isRevealHiddenLines_;
}
