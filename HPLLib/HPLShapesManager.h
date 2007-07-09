/**
    Shapes�t�@�C����p����֐��ƊǗ��}�l�[�W���[
    Shapes<->SDL_Surface�Ԃ̑���̂ݍs���A
    SDL_Surface<->SDL_Surface, SDL_Surface<->wxImage���̑���͕ʂōs������
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
		�ǂݍ��݊Ǘ�
	*/
    class HPLShapesManager{
        //Shapes�t�@�C����ǂݍ��߂Ă�����^ <en> true when Shapes file loaded
        bool isLoadedShapesFile_;

		bool isInitialized;
    public:
        HPLShapesManager();
        ~HPLShapesManager();

	private:
		void setLoadedShapesFile(bool loaded);

    public:
        bool isLoadedShapesFile();
        /**
            �ǂݍ��񂾃f�[�^�����̂܂܎擾���܂��B
            �p���b�g�̐F�ԍ����������Ȃ����߁A�p���b�g���K�v
            @param palette �J���[�p���b�g�B�O���ŗp�ӂ���
            @param outp ���f�[�^�B�O���ŗp�ӂ���
        */
        SDL_Surface* getRawSurface(int collection, int clut, int index, double illumination,
            SDL_Color palette[256], byte **outp);
		/**
			�w�肵��Shapes�f�[�^���擾���܂��B
			@return ���s����NULL
		*/
		SDL_Surface* getSurface(int collection, int clut, int index, double illumination);

		/**
			Shapes�t�@�C����ǂݍ��݂܂�
			<en> load Shapes file
			@param path Shapes�t�@�C���p�X <en> Shapes file's path
		*/
		bool loadShapesFile(const char* path);

		void initScreen();

    };
};
};
#endif
