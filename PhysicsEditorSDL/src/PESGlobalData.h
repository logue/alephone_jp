#ifndef _PES_GLOBAL_DATA_
#define _PES_GLOBAL_DATA_

#include "General.h"
#include "PageMonster.h"

namespace hpl{
namespace pes{
    class PESGlobalData{
    public:
        //monster types
        hpl::pes::ListModelFromArray* listMonsterTypes;
        //page
        PageMonster* pageMonster;
    public:
        PESGlobalData();
        ~PESGlobalData();

        void setupPageWidgets();
    };
};
};

extern hpl::pes::PESGlobalData* globalData;

#endif
