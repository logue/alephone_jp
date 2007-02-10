#ifndef _PES_PAGE_MONSTER_01_
#define _PES_PAGE_MONSTER_01_

#include "General.h"
#include "ListModelFromArray.h"

namespace hpl{
namespace pes{
    class PageMonster: public gcn::Container{
    public:
        //monster types
        gcn::ListBox* listBoxMonsterTypes;
        gcn::ScrollArea* scrListBoxMonsterTypes;

        PageMonster();
        virtual ~PageMonster();

    };
};
};
#endif
