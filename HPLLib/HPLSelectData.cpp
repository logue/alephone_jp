#include "HPLSelectData.h"

hpl::aleph::map::HPLSelectData::HPLSelectData()
{
    
}
hpl::aleph::map::HPLSelectData::~HPLSelectData()
{
    this->clear();
}
////////////////////////////////////////////


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
struct hpl::aleph::map::SelSide* hpl::aleph::map::HPLSelectData::getSelSide()
{
    return &this->side;
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
bool hpl::aleph::map::HPLSelectData::isSelectSide(int index)
{
    if(this->side.index == index){
        return true;
    }else{
        return false;
    }
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
    this->side.index = NONE;

    // unselected
    this->setSelected(false);
}

bool hpl::aleph::map::HPLSelectData::isSelectOnePoint()
{
    if(this->isSelected() && 
        static_cast<int>(selpoints.size()) == 1 &&
        static_cast<int>(sellines.size()) == 0 &&
        static_cast<int>(selpolygons.size()) == 0 &&
        static_cast<int>(selobjects.size()) == 0)
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
        static_cast<int>(selobjects.size()) == 0)
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
        static_cast<int>(selobjects.size()) == 0)
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
        static_cast<int>(selobjects.size()) == 1)
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
        this->side.index != NONE)
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

    //‘I‘ðó‘Ô‚É‚·‚é
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
    this->side.index = index;
    this->setSelected(true);
}
