#include "General.h"
#include "GuichanPackage.h"

//#include "PageMonster.h"
#include "PESGlobalData.h"



hpl::pes::GuichanPackage* package;

//select button
gcn::Button* btnMonster;
gcn::Button* btnEffect;
gcn::Button* btnProjectile;
gcn::Button* btnPhysics;
gcn::Button* btnWeapon;


//list-box
gcn::ListBox* listBoxCollections;
gcn::ListBox* listBoxEffectTypes;
gcn::ListBox* listBoxProjectileTypes;
gcn::ListBox* listBoxWeaponTypes;

//global data
hpl::pes::PESGlobalData* globalData;


void initLocal()
{
    //global data
    globalData = new hpl::pes::PESGlobalData();
    globalData->setupPageWidgets();

    /////////////////
    //add widgets
    btnMonster = new gcn::Button("Monster");
    btnEffect = new gcn::Button("Effect");
    btnProjectile = new gcn::Button("Projectile");
    btnPhysics = new gcn::Button("Physics");
    btnWeapon = new gcn::Button("Weapon");
    //on the top
    const int BUTTON_HEIGHT_INTERVAL = 50;
    int x = 10, y = 10;
    package->top->add(btnMonster, x, y);
    y += BUTTON_HEIGHT_INTERVAL;
    package->top->add(btnEffect, x, y);
    y += BUTTON_HEIGHT_INTERVAL;
    package->top->add(btnProjectile, x, y);
    y += BUTTON_HEIGHT_INTERVAL;
    package->top->add(btnPhysics, x, y);
    y += BUTTON_HEIGHT_INTERVAL;
    package->top->add(btnWeapon, x, y);

    //add on top
    package->top->add(globalData->pageMonster);
}

void haltLocal()
{
    delete globalData;

    delete btnMonster;
    delete btnEffect;
    delete btnProjectile;
    delete btnPhysics;
    delete btnWeapon;

}

void runLocal()
{
}

void checkEventLocal(SDL_Event& ev)
{
    
}


int main(int argc, char**argv)
{
    package = new hpl::pes::GuichanPackage();

    try{
        package->init();
        package->run();
        package->halt();
    }catch(gcn::Exception e){
        fprintf(stderr,"%s\n", e.getMessage());
        return -1;
    }catch(std::exception e){
        fprintf(stderr,"Std exception: %s\n", e.what());
        return -1;
    }catch(...){
        fprintf(stderr, "Unknown exception\n");
        return -1;
    }

    delete package;

    return 0;
}
