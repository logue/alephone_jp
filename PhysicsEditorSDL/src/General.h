#ifndef _PES_GENERAL_
#define _PES_GENERAL_

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include "SDL.h"
#include "HPLLib/HPLStringModifier.h"

const int WINDOW_SIZE_W = 640;
const int WINDOW_SIZE_H = 480;
const int SCREEN_BPP = 32;
static char *IMAGE_FONT_PATH = "fixedfont.bmp";
static char* LIST_MONSTER_TYPES_PATH ="data/MonsterTypes.txt";
const int PAGE_X = 100, PAGE_Y = 10;
const int PAGE_WIDTH = WINDOW_SIZE_W - PAGE_X - 20;
const int PAGE_HEIGHT = WINDOW_SIZE_H - PAGE_Y - 20;
const int PANE_X = 10, PANE_Y = 10;
const int PANE_WIDTH = PAGE_WIDTH - 20;
const int PANE_HEIGHT = PANE_HEIGHT - 20;

#endif
