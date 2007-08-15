#include "HPLSelectData.h"

hpl::aleph::map::HPLSelectData::HPLSelectData()
{
    
}
hpl::aleph::map::HPLSelectData::~HPLSelectData()
{
    this->clear();
}
////////////////////////////////////////////

//�}�E�X���W
void hpl::aleph::map::HPLSelectData::setMousePosition(int x, int y)
{
	this->mx = x;
	this->my = y;
}
void hpl::aleph::map::HPLSelectData::getMousePosition(int point[2])
{
	point[0] = mx;
	point[1] = my;
}

std::vector<struct hpl::aleph::map::SelPoint>* hpl::aleph::map::HPLSelectData::getSelPoints()
{
    return &this->selpoints;
}
std::vector<struct hpl::aleph::map::SelLine>* hpl::aleph::map::HPLSelectData::getSelLines()
{
    return &this->sellines;
}
std::vector<struct hpl::aleph::map::SelPolygon>* hpl::aleph::map::HPLSelectData::getSelPolygons()
{
    return &this->selpolygons;
}
std::vector<struct hpl::aleph::map::SelObject>* hpl::aleph::map::HPLSelectData::getSelObjects()
{
    return &this->selobjects;
}
std::vector<struct hpl::aleph::map::SelSide>* hpl::aleph::map::HPLSelectData::getSelSides()
{
    return &this->selsides;
}
struct hpl::aleph::map::SelSide* hpl::aleph::map::HPLSelectData::getSelSide()
{
    return &this->side;
}
std::vector<struct hpl::aleph::map::SelAnnotation>* hpl::aleph::map::HPLSelectData::getSelAnnotations()
{
    return &this->selannotations;
}

bool hpl::aleph::map::HPLSelectData::containsPoint(int index)
{
    for(int i = 0; i < static_cast<int>(this->selpoints.size()); i ++){
        if(this->selpoints[i].index == index){
            return true;
        }
    }
    return false;
}
bool hpl::aleph::map::HPLSelectData::containsLine(int index)
{
    for(int i = 0; i < static_cast<int>(this->sellines.size()); i ++){
        if(this->sellines[i].index == index){
            return true;
        }
    }
    return false;
}
bool hpl::aleph::map::HPLSelectData::containsPolygon(int index)
{
    for(int i = 0; i < static_cast<int>(this->selpolygons.size()); i ++){
        if(this->selpolygons[i].index == index){
            return true;
        }
    }
    return false;
}
bool hpl::aleph::map::HPLSelectData::containsObject(int index)
{
    for(int i = 0; i < static_cast<int>(this->selobjects.size()); i ++){
        if(this->selobjects[i].index == index){
            return true;
        }
    }
    return false;
}
bool hpl::aleph::map::HPLSelectData::containsSide(int index)
{
    for(int i = 0; i < static_cast<int>(this->selsides.size()); i ++){
        if(this->selsides[i].index == index){
            return true;
        }
    }
    return false;
}
bool hpl::aleph::map::HPLSelectData::isSelectSide(int index)
{
    if(this->side.index == index){
        return true;
    }else{
        return false;
    }
}
bool hpl::aleph::map::HPLSelectData::containsAnnotation(int index)
{
    for(int i = 0; i < static_cast<int>(this->selannotations.size()); i ++){
        if(this->selannotations[i].index == index){
            return true;
        }
    }
    return false;
}

bool hpl::aleph::map::HPLSelectData::isSelected()
{
    return this->_isSelected;
}
void hpl::aleph::map::HPLSelectData::setSelected(bool sel)
{
    this->_isSelected = sel;
}

//clear all selecting informatins
void hpl::aleph::map::HPLSelectData::clear()
{
    this->selpoints.clear();
    this->sellines.clear();
    this->selpolygons.clear();
    this->selobjects.clear();
    this->selsides.clear();
    this->side.index = NONE;
    this->selannotations.clear();

    // unselected
    this->setSelected(false);
}

bool hpl::aleph::map::HPLSelectData::isSelectOnePoint()
{
    if(this->isSelected() && 
        static_cast<int>(selpoints.size()) == 1 &&
        static_cast<int>(sellines.size()) == 0 &&
        static_cast<int>(selpolygons.size()) == 0 &&
        static_cast<int>(selobjects.size()) == 0 &&
        (int)(selsides.size()) == 0 &&
        (int)(selannotations.size()) == 0)
    {
        return true;
    }else{
        return false;
    }
}
bool hpl::aleph::map::HPLSelectData::isSelectOneLine()
{
    if(this->isSelected() && 
        static_cast<int>(selpoints.size()) == 0 &&
        static_cast<int>(sellines.size()) == 1 &&
        static_cast<int>(selpolygons.size()) == 0 &&
        static_cast<int>(selobjects.size()) == 0 &&
        (int)(selsides.size()) == 0 &&
        (int)(selannotations.size()) == 0)
    {
        return true;
    }else{
        return false;
    }
}
bool hpl::aleph::map::HPLSelectData::isSelectOnePolygon()
{
    if(this->isSelected() && 
        static_cast<int>(selpoints.size()) == 0 &&
        static_cast<int>(sellines.size()) == 0 &&
        static_cast<int>(selpolygons.size()) == 1 &&
        static_cast<int>(selobjects.size()) == 0 &&
        (int)(selsides.size()) == 0 &&
        (int)(selannotations.size()) == 0)
    {
        return true;
    }else{
        return false;
    }
}
bool hpl::aleph::map::HPLSelectData::isSelectOneObject()
{
    if(this->isSelected() && 
        static_cast<int>(selpoints.size()) == 0 &&
        static_cast<int>(sellines.size()) == 0 &&
        static_cast<int>(selpolygons.size()) == 0 &&
        static_cast<int>(selobjects.size()) == 1 &&
        (int)(selsides.size()) == 0 &&
        (int)(selannotations.size()) == 0)
    {
        return true;
    }else{
        return false;
    }
}
bool hpl::aleph::map::HPLSelectData::isSelectOneSide()
{
    if(this->isSelected() && 
        static_cast<int>(selpoints.size()) == 0 &&
        static_cast<int>(sellines.size()) == 0 &&
        static_cast<int>(selpolygons.size()) == 0 &&
        static_cast<int>(selobjects.size()) == 0 &&
        (int)(selsides.size()) == 1 &&
        (int)(selannotations.size()) == 0)
    {
        return true;
    }else{
        return false;
    }
}
bool hpl::aleph::map::HPLSelectData::isSelectOneAnnotation()
{
    if(this->isSelected() && 
        static_cast<int>(selpoints.size()) == 0 &&
        static_cast<int>(sellines.size()) == 0 &&
        static_cast<int>(selpolygons.size()) == 0 &&
        static_cast<int>(selobjects.size()) == 0 &&
        (int)(selsides.size()) == 0 &&
        (int)(selannotations.size()) == 1)
    {
        return true;
    }else{
        return false;
    }
}

void hpl::aleph::map::HPLSelectData::addSelPoint(int index, int offset[2])
{
    struct hpl::aleph::map::SelPoint sp;
    sp.index = index;
    sp.offset[0] = offset[0];
    sp.offset[1] = offset[1];
    this->selpoints.push_back(sp);

    //�I����Ԃɂ���
    //set as selecting mode
    this->setSelected(true);
}
void hpl::aleph::map::HPLSelectData::addSelLine(int index, int offset[2][2])
{
    struct hpl::aleph::map::SelLine sp;
    sp.index = index;
    for(int i = 0; i < 2; i ++){
        for(int j = 0; j < 2; j ++){
            sp.offset[i][j] = offset[i][j];
        }
    }
    this->sellines.push_back(sp);
    this->setSelected(true);
}
void hpl::aleph::map::HPLSelectData::addSelPolygon(int index, int offset[8][2], int num)
{
    struct hpl::aleph::map::SelPolygon sp;
    sp.index = index;
    sp.num = num;
    for(int i = 0; i < num; i ++){
        for(int j = 0; j < 2; j ++){
            sp.offset[i][j] = offset[i][j];
        }
    }
    this->selpolygons.push_back(sp);
    this->setSelected(true);
}
void hpl::aleph::map::HPLSelectData::addSelObject(int index, int offset[2])
{
    struct hpl::aleph::map::SelObject sp;
    sp.index = index;
    for(int i = 0; i < 2; i ++){
        sp.offset[i] = offset[i];
    }
    this->selobjects.push_back(sp);
    this->setSelected(true);
}
void hpl::aleph::map::HPLSelectData::addSelSide(int index)
{
/*    struct hpl::aleph::map::SelSide sp;
    sp.index = index;
    selsides.push_back(sp);*/
    this->side.index = index;
    this->setSelected(true);
}
void hpl::aleph::map::HPLSelectData::addSelAnnotation(int index, int offset[2])
{
    struct hpl::aleph::map::SelAnnotation sp;
    sp.index = index;
    for(int i = 0; i < 2; i ++){
        sp.offset[i] = offset[i];
    }
    this->selannotations.push_back(sp);
    this->setSelected(true);
}