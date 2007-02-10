#include "PageMonster.h"
#include "PESGlobalData.h"

hpl::pes::PaneMonster01::PaneMonster01():gcn::Container()
{
}
hpl::pes::PaneMonster01::~PaneMonster01()
{
}

gcn::Rectangle SCR_LIST_BOX_MONSTER_TYPES_RECT(10,10,100,PAGE_HEIGHT - 20);
gcn::Rectangle LIST_BOX_MONSTER_TYPES_RECT=SCR_LIST_BOX_MONSTER_TYPES_RECT;
gcn::Rectangle PANE_RECT(SCR_LIST_BOX_MONSTER_TYPES_RECT.x + SCR_LIST_BOX_MONSTER_TYPES_RECT.width + 10,
                         50, PAGE_WIDTH - (SCR_LIST_BOX_MONSTER_TYPES_RECT.x + SCR_LIST_BOX_MONSTER_TYPES_RECT.width + 20), PAGE_HEIGHT - 70);

hpl::pes::PageMonster::PageMonster():gcn::Container()
{
    LIST_BOX_MONSTER_TYPES_RECT.width = 300;

    //list box
    listBoxMonsterTypes = new gcn::ListBox(globalData->listMonsterTypes);
    listBoxMonsterTypes->setDimension(LIST_BOX_MONSTER_TYPES_RECT);
    listBoxMonsterTypes->setBorderSize(1);
    // scroll area
    scrListBoxMonsterTypes = new gcn::ScrollArea(listBoxMonsterTypes);
    scrListBoxMonsterTypes->setDimension(SCR_LIST_BOX_MONSTER_TYPES_RECT);
    scrListBoxMonsterTypes->setBorderSize(1);
    this->add(scrListBoxMonsterTypes);

    pane01 = new hpl::pes::PaneMonster01();
    pane01->setDimension(PANE_RECT);
    pane01->setBaseColor(gcn::Color(0,10,0));
    this->add(pane01);
}
hpl::pes::PageMonster::~PageMonster()
{
    delete pane01;
    delete scrListBoxMonsterTypes;
    delete listBoxMonsterTypes;
}
