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
        //collections
        hpl::pes::ListModelFromArray* listCollections;
        hpl::pes::ListModelFromArray* listEffectTypes;
        hpl::pes::ListModelFromArray* listProjectileTypes;
        hpl::pes::ListModelFromArray* listWeaponTypes;

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
