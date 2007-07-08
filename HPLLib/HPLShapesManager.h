/**
    Shapesファイルを用いる関数と管理マネージャー
    Shapes<->SDL_Surface間の操作のみ行い、
    SDL_Surface<->SDL_Surface, SDL_Surface<->wxImage等の操作は別で行うこと
*/
#ifndef _HPL_SHAPES_MANAGER_
#define _HPL_SHAPES_MANAGER_

#include "header.h"
#include "extensions.h"
#include "FileHandler.h"
#include "map.h"
#include "game_wad.h"
#include "weapons.h"
#include "items.h"
#include "monsters.h"
#include "scenery_definitions.h"
#include "mysound.h"
#include "computer_interface.h"
#include "editor.h"
#include "lightsource.h"
#include "media.h"

namespace hpl{
namespace shapes{
    /**
        指定したShapesデータを取得します。
        @return 失敗時にNULL
    */
    SDL_Surface* getSurface(int collection, int clut, int index, double illumination);
    /**
        Shapesファイルを読み込みます
        <en> load Shapes file
        @param path Shapesファイルパス <en> Shapes file's path
    */
    void loadShapesFile(const char* path);

    void initScreen();

	/**
		読み込み管理
	*/
    class HPLShapesManager{
        //Shapesファイルを読み込めていたら真 <en> true when Shapes file loaded
        bool isLoadedShapesFile_;

    public:
        HPLShapesManager();
        ~HPLShapesManager();

    public:
        bool isLoadedShapesFile();
		void setLoadedShapesFile(bool loaded);
    };
};
};
#endif
