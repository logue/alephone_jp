#include "HPLViewGridManager.h"
#include <memory.h>
#include "HPLMath.h"

/**
    ビューの次元
    the dimension of view window
*/
const int VIEW_DIMENSION = 2;

hpl::aleph::view::HPLViewGridManager::HPLViewGridManager(ZoomProperties *zoomProp)
{
    memcpy(&this->zoomProperties, zoomProp, sizeof(struct ZoomProperties));
    //オフセット初期化
    this->viewOffset[0] = viewOffset[1] = 0;
    //割り算率初期化
    this->zoomReset();
}

hpl::aleph::view::HPLViewGridManager::~HPLViewGridManager()
{
}

/**
    拡大率取得
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
    this->addZoom(this->zoomProperties.zoomDivisionStep, viewW, viewH);
}

/**
    zoom out
*/
void hpl::aleph::view::HPLViewGridManager::zoomOut(int viewW, int viewH)
{
    this->addZoom(this->zoomProperties.zoomDivisionStep, viewW, viewH);
}
/**
    拡大率初期化
*/
void hpl::aleph::view::HPLViewGridManager::zoomReset()
{
    this->zoomDivision = this->zoomProperties.zoomDivisionDefault;
}



/**
    ズーム調整
    @param step 変化量
*/
void hpl::aleph::view::HPLViewGridManager::addZoom(int step, int viewW, int viewH)
{
    int oldZoomDiv = this->zoomDivision;

    //拡大割率が閾値を越えたら増減速度Down
    //<en>set zoom step small when division num is over threshold
    if(zoomDivision < this->zoomProperties.zoomDivStepThreshold){
        step = hpl::math::sgn<int>(step) * this->zoomProperties.zoomDivisionStepDetail;
    }

    //adjustment
    if(this->zoomDivision < this->zoomProperties.zoomDivisionMin){
        this->zoomDivision = this->zoomProperties.zoomDivisionMin;
    }else if(this->zoomDivision > this->zoomProperties.zoomDivisionMax){
        this->zoomDivision = this->zoomProperties.zoomDivisionMax;
    }

    int oldOffset[2] = {this->viewOffset[0], this->viewOffset[1]};
    int center[2] = {viewW / 2, viewH / 2};

    int newZoomDiv = this->zoomDivision;
    //位置修正
    int ax = center[0] - oldOffset[1];
    this->viewOffset[0] = center[0] - ax * oldZoomDiv / newZoomDiv;
    int ay = center[1] - oldOffset[1];
    this->viewOffset[1] = center[1] - ay * oldZoomDiv / newZoomDiv;
}

//void setOldMousePoint(int x, int y);
/**
    マウス座標をセットします
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
