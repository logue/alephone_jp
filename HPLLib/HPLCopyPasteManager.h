#ifndef _HPL_COPY_PASTE_MANAGER_
#define _HPL_COPY_PASTE_MANAGER_

#include "HPLRealMapData.h"

/**
	�R�s�[���y�[�X�g�̊Ǘ��Ə������s���܂�
*/
//�R�s�y�̎��̂��炵�Ԋu
const int COPY_AND_PASTE_DELTA_X = 10;
const int COPY_AND_PASTE_DELTA_Y = COPY_AND_PASTE_DELTA_X;

namespace hpl{
namespace aleph{
	class HPLCopyPasteManager{
		//�R�s�y�ŕێ�����f�[�^
		hpl::aleph::map::HPLRealMapData storedMapData;
		//���炷�ʒu
		int storedDataDiffPointDelta[2];
	public:
		HPLCopyPasteManager();
		~HPLCopyPasteManager();

		/**
			�ێ����Ă���f�[�^�����������܂�
		*/
		void clear();

		/**
			�R�s�[���܂�
			���l�̑Ή��͈�U�����C���f�b�N�X�ɕϊ����܂�
			���݂��Ȃ����̂�NONE�ɂȂ�܂����A
			���݂̂̃R�s�[�̏ꍇ�A�V���ɓ_����t�������܂�
			@param sel �R�s�[���̑I���f�[�^
		*/
		void copy(hpl::aleph::map::HPLSelectData& sel);

		/**
			�ێ����Ă�����e���y�[�X�g���܂�
			@return �y�[�X�g�Ɏ��s�����ꍇ�i�����ێ����Ă��Ȃ��Ƃ��j�ɋU
		*/
		bool paste(int div);
	};
};
};
#endif
