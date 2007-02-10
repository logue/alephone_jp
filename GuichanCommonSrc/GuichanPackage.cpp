#include "GuichanPackage.h"

const int WINDOW_SIZE_W = 640;
const int WINDOW_SIZE_H = 480;
const int SCREEN_BPP = 32;
static char *IMAGE_FONT_PATH = "fixedfont.bmp";

hpl::pes::GuichanPackage::GuichanPackage()
{
}
hpl::pes::GuichanPackage::~GuichanPackage()
{
}

void hpl::pes::GuichanPackage::init()
{
    this->running = true;

    SDL_Init(SDL_INIT_VIDEO);

    int w = WINDOW_SIZE_W;
    int h = WINDOW_SIZE_H;
    int bpp = SCREEN_BPP;
    int flags = SDL_HWSURFACE;
    this->screen = SDL_SetVideoMode(w, h, bpp, flags);

    SDL_EnableUNICODE(SDL_TRUE);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    //image
    this->imageLoader = new gcn::SDLImageLoader();
    gcn::Image::setImageLoader(this->imageLoader);
    
    this->graphics = new gcn::SDLGraphics();
    this->graphics->setTarget(this->screen);
    this->input = new gcn::SDLInput();

    //container
    this->top = new gcn::Container();
    this->top->setDimension(gcn::Rectangle(0,0,w,h));
    this->gui = new gcn::Gui();
    this->gui->setGraphics(this->graphics);
    this->gui->setInput(this->input);
    this->gui->setTop(this->top);
    this->font = new gcn::ImageFont(
        IMAGE_FONT_PATH, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    gcn::Widget::setGlobalFont(this->font);

    
    initLocal();
}

void hpl::pes::GuichanPackage::halt()
{

    delete this->font;
    delete this->gui;

    delete this->top;

    delete this->input;
    delete this->graphics;
    delete this->imageLoader;

    haltLocal();

    SDL_Quit();
}

void hpl::pes::GuichanPackage::checkEvent()
{
    while(SDL_PollEvent(&this->ev)){
        if(this->ev.type == SDL_KEYDOWN){
            //Alt+F4
            if((this->ev.key.keysym.mod & SDLK_LALT || 
                this->ev.key.keysym.mod & SDLK_RALT)&&
                this->ev.key.keysym.sym == SDLK_F4){
                this->running = false;
            }
        }else if(this->ev.type == SDL_QUIT){
            this->running = false;
        }
        
        checkEventLocal(this->ev);

        this->input->pushInput(this->ev);
    }
}

void hpl::pes::GuichanPackage::run()
{
    while(this->running){
        this->gui->logic();
        this->gui->draw();
        runLocal();
        this->checkEvent();
        SDL_Flip(this->screen);
    }
}
