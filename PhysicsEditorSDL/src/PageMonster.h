#ifndef _PES_PAGE_MONSTER_01_
#define _PES_PAGE_MONSTER_01_

#include "General.h"
#include "ListModelFromArray.h"

namespace hpl{
namespace pes{
    class PaneMonster01: public gcn::Container{
    public:
        PaneMonster01();
        virtual ~PaneMonster01();
    };
    class PageMonster: public gcn::Container{
    public:
        //monster types
        gcn::ListBox* listBoxMonsterTypes;
        gcn::ScrollArea* scrListBoxMonsterTypes;

        //01
        PaneMonster01* pane01;

        PageMonster();
        virtual ~PageMonster();

    };
};
};
#endif
