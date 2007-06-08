#ifndef _EVENT_MANAGER_
#define _EVENT_MANAGER_
/*
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
*/
namespace mapeditorone{
    /**
        �}�E�X�C�x���g�Ȃǂ̃C�x���g���̋L���Ȃǂ�ێ��E�Ǘ�����
    */
    class EventManager{
    private:
    //�{�^�������Ă�H
    bool isPressLButtonWithCtrl_;

    //�I��͈͎n�_
    int selectGroupStartPoint[2];

    //�͈͑I��
    bool isSelectingGroup_;

    //select tool type
    //�I���c�[���^�C�v
    int toolType;

    //�ҏW���[�h
    int editModeType;

    public:
        EventManager();
        ~EventManager();

    public:
//        bool isPressLButtonWithCtrl
        void getSelectGroupStartPoint(int point[2]);
        void setSelectGroupStartPoint(int px, int py);
        bool isSelectingGroup();
        void setSelectingGroup(bool flag);
        void setToolType(int type);
        int getToolType();
        void setEditModeType(int type);
        int getEditModeType();

    };
};

#endif
