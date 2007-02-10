#include "PESGlobalData.h"

hpl::pes::PESGlobalData::PESGlobalData()
{
    //setup list
    std::vector<std::string> lines;
    lines = hpl::string::loadFromFile(LIST_MONSTER_TYPES_PATH);
    listMonsterTypes = new hpl::pes::ListModelFromArray(lines);
    lines = hpl::string::loadFromFile(LIST_COLLECTIONS_PATH);
    listCollections = new hpl::pes::ListModelFromArray(lines);
    lines = hpl::string::loadFromFile(LIST_EFFECT_TYPES_PATH);
    listEffectTypes = new hpl::pes::ListModelFromArray(lines);
    lines = hpl::string::loadFromFile(LIST_PROJECTILE_TYPES_PATH);
    listProjectileTypes = new hpl::pes::ListModelFromArray(lines);
    lines = hpl::string::loadFromFile(LIST_WEAPON_TYPES_PATH);
    listWeaponTypes = new hpl::pes::ListModelFromArray(lines);

}

hpl::pes::PESGlobalData::~PESGlobalData()
{
    delete listCollections;
    delete listEffectTypes;
    delete listProjectileTypes;
    delete listWeaponTypes;
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
