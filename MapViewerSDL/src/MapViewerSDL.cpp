#include "General.h"
#include "GuichanPackage.h"

hpl::pes::GuichanPackage* package;

void initLocal()
{
}
void haltLocal()
{
}
void runLocal()
{
    gcn::Graphics* g = package->gui->getGraphics();
    g->_beginDraw();
    g->setColor(gcn::Color(255,0,0));
    g->drawLine(0,0,100,100);
    g->_endDraw();
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
