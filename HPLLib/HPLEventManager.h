#ifndef _HPL_EVENT_MANAGER_
#define _HPL_EVENT_MANAGER_

//tools
namespace ToolType{
    enum
    {
        TI_ARROW = 0,
        TI_FILL,
        TI_HAND,
        TI_LINE,
        TI_MAGNIFY,
        TI_SKULL,
        TI_TEXT,
        TI_POLYGON,
        NUMBER_OF_TOOLS //7
    };
};

//�ҏW���[�h
namespace EditModeType{
    enum
    {
        EM_DRAW,
        EM_VISUAL,
        EM_FLOOR_HEIGHT,
        EM_CEILING_HEIGHT,
        EM_FLOOR_TEXTURE,
        EM_CEILING_TEXTURE,
        EM_FLOOR_LIGHT,
        EM_CEILING_LIGHT,
        EM_MEDIA,
        EM_SOUND,
        EM_POLYGON_TYPE,
    };
};

namespace hpl{
namespace aleph{
    /**
        �}�E�X�C�x���g�ȂǊe�퓮����Ǘ�
    */
    class HPLEventManager{
    private:
        //Ctrl�{�^���������Ă��邩�ǂ���
        //bool isPressButtonWithCtrl_;

        //�I��͈͎n�_
        int selGroupStartPoint[2];

        //�͈͑I��
        bool isSelGrp;

        //�I�𒆂̃c�[���^�C�v
        int toolType;

        //�ҏW���[�h
        int editModeType;

		//�Ō�ɑI���������W
		int lastMouseSelectPoint[2];
    public:
        HPLEventManager();
        ~HPLEventManager();
	private:
        void setSelectingGroup(bool flag);
    public:
        void getSelectGroupStartPoint(int point[2]);
        void setSelectGroupStartPoint(int px, int py);
        bool isSelectingGroup();
		void exitSelectingGroup();
        void setToolType(int type);
        int getToolType();
        void setEditModeType(int type);
        int getEditModeType();

		/**
			�Ō�ɑI�������Ƃ��̃}�E�X���W���擾���܂�
		*/
		void setLastMouseSelectPoint(int px, int py);
		void getLastMouseSelectPoint(int point[2]);
    };
};
};
#endif
