#include "PESGlobalData.h"

hpl::pes::PESGlobalData::PESGlobalData()
{
    //setup list
    std::vector<std::string> lines;
    lines = hpl::string::loadFromFile(LIST_MONSTER_TYPES_PATH);
    listMonsterTypes = new hpl::pes::ListModelFromArray(lines);

}

hpl::pes::PESGlobalData::~PESGlobalData()
{
    delete listMonsterTypes;
    delete pageMonster;
}

void hpl::pes::PESGlobalData::setupPageWidgets()
{
    //////////////////////
    //monster pane
    pageMonster = new hpl::pes::PageMonster();
    pageMonster->setDimension(gcn::Rectangle(PAGE_X, PAGE_Y, PAGE_WIDTH, PAGE_HEIGHT));
    pageMonster->setBackgroundColor(gcn::Color(10, 0, 0));
    pageMonster->setBaseColor(gcn::Color(10,0,0));
}
