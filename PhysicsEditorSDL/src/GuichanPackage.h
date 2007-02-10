#ifndef _PES_GUICHAN_PACKAGE_
#define _PES_GUICHAN_PACKAGE_

//#include "General.h"
#include "ListModelFromArray.h"



namespace hpl{
namespace pes{
    class GuichanPackage{
    public:
        GuichanPackage();
        ~GuichanPackage();

        bool running;

        SDL_Surface* screen;
        SDL_Event ev;

        gcn::SDLInput* input;
        gcn::SDLGraphics* graphics;
        gcn::SDLImageLoader* imageLoader;

        gcn::Gui* gui;
        gcn::ImageFont* font;

        gcn::Container* top;


        void init();
        void halt();
        void run();
        void checkEvent();
    };
};
};


void initLocal();
void haltLocal();
void runLocal();
void checkEventLocal(SDL_Event& ev);
#endif
