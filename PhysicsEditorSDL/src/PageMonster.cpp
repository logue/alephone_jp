#include "PageMonster.h"
#include "PESGlobalData.h"

const gcn::Rectangle LIST_BOX_MONSTER_TYPES_RECT(10,10,200,PAGE_HEIGHT - 20);

hpl::pes::PageMonster::PageMonster():gcn::Container()
{
    //list box
    listBoxMonsterTypes = new gcn::ListBox(globalData->listMonsterTypes);
    listBoxMonsterTypes->setDimension(LIST_BOX_MONSTER_TYPES_RECT);
    listBoxMonsterTypes->setBorderSize(1);
    // scroll area
    scrListBoxMonsterTypes = new gcn::ScrollArea(listBoxMonsterTypes);
    scrListBoxMonsterTypes->setDimension(LIST_BOX_MONSTER_TYPES_RECT);
    scrListBoxMonsterTypes->setBorderSize(1);
    this->add(scrListBoxMonsterTypes);
}
hpl::pes::PageMonster::~PageMonster()
{
    delete scrListBoxMonsterTypes;
    delete listBoxMonsterTypes;
}
