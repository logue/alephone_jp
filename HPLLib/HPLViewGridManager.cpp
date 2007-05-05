#include "HPLViewGridManager.h"
#include <memory.h>
#include "HPLMath.h"

hpl::aleph::view::HPLViewGridManager::HPLViewGridManager(ZoomProperties *zoomProp)
{
    memcpy(&this->zoomProperties, zoomProp, sizeof(struct ZoomProperties));

}

hpl::aleph::view::HPLViewGridManager::~HPLViewGridManager()
{
}

/**
    Šg‘å—¦æ“¾
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
    ƒY[ƒ€’²®
    @param step •Ï‰»—Ê
*/
void hpl::aleph::view::HPLViewGridManager::addZoom(int step, int viewW, int viewH)
{
    int oldZoomDiv = this->zoomDivision;

    //Šg‘åŠ„—¦‚ªè‡’l‚ğ‰z‚¦‚½‚ç‘Œ¸‘¬“xDown
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
    //ˆÊ’uC³
    int ax = center[0] - oldOffset[1];
    this->viewOffset[0] = center[0] - ax * oldZoomDiv / newZoomDiv;
    int ay = center[1] - oldOffset[1];
    this->viewOffset[1] = center[1] - ay * oldZoomDiv / newZoomDiv;
}
