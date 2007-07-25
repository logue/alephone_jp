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

//編集モード
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
        マウスイベントなど各種動作を管理
    */
    class HPLEventManager{
    private:
        //Ctrlボタンを押しているかどうか
        //bool isPressButtonWithCtrl_;

        //選択範囲始点
        int selGroupStartPoint[2];

        //範囲選択中
        bool isSelGrp;

        //選択中のツールタイプ
        int toolType;

        //編集モード
        int editModeType;

		//最後に選択した座標
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
			最後に選択したときのマウス座標を取得します
		*/
		void setLastMouseSelectPoint(int px, int py);
		void getLastMouseSelectPoint(int point[2]);
    };
};
};
#endif
