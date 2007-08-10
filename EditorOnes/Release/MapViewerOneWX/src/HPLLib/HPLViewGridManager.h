/**
    <jp>拡大縮小や、編集位置Offsetの修正、座標変換、スクロール表示など
        をまとめて管理するマネージャーです
    <en>the manager that manage zooming in or out, offsets for editing, exchanging
        different coordinates, scrolling, and so on
*/
#ifndef _HPL_VIEW_GRID_MANAGER_
#define _HPL_VIEW_GRID_MANAGER_

const int NUMBER_OF_GLID = 5;
const int ZOOM_DIVISION_STEP = 5;
const int ZOOM_DIVISION_MAX = 200;
const int ZOOM_DIVISION_MIN = 1;
const int ZOOM_DIVISION_DEFAULT = 100;
const int OFFSET_X_WORLD = 32768;
const int OFFSET_Y_WORLD = 32768;


namespace hpl{
namespace aleph{
namespace view{
    struct ZoomProperties{
        /**一回の拡大縮小で生じる変化量*/
        int zoomDivisionStep;

        /**拡大率を下げる閾値*/
        int zoomDivStepThreshold;

        /**拡大率を下げた後の増減速度*/
        int zoomDivisionStepDetail;

        /**最大値*/
        int zoomDivisionMax;

        /**最小値*/
        int zoomDivisionMin;

        /**初期値・規定値*/
        int zoomDivisionDefault;

        //グリッド
        int gridIntervals[NUMBER_OF_GLID];

    };
    /**
        拡大縮小、スクロールなどの管理
    */
    class HPLViewGridManager{
    private:
        /**拡大関係の定数*/
        ZoomProperties zoomProperties;

        /**現在の拡大割合*/
        int zoomDivision;

        /**View座標のオフセット*/
        int viewOffset[2];

        //マウス座標（旧）
        int oldMousePoint[2];
        int newMousePoint[2];

        //グリッド
        int gridIndex;

        //表示・編集できる高さ
        int viewHeightMax;
        int viewHeightMin;
        //高さ範囲外のポリゴン線を表示するか？
        bool isRevealHiddenLines_;
    public:
        HPLViewGridManager();
        void setProp(ZoomProperties *zoomProp);
        ~HPLViewGridManager();

    public:
        /**
            拡大率取得
            <en>get zoom division
        */
        int getZoomDivision();
        /**
            zoom in
            @param viewW, viewH View範囲のサイズ
        */
        void zoomIn(int viewW, int viewH);

        /**
            zoom out
        */
        void zoomOut(int viewW, int viewH);

        /**
            拡大率初期化
        */
        void zoomReset();

        //void setOldMousePoint(int x, int y);
        /**
            マウス座標をセットします
            set mouse position info (view coordinate)
        */
        void setNewMousePoint(int x, int y);
        void getNewMousePoint(int* point);
        void getOldMousePoint(int* point);

        void setOffset(int x, int y);
        void getOffset(int* point);
        void setViewHeightMax(int max);
        void setViewHeightMin(int min);
        int getViewHeightMax();
        int getViewHeightMin();
        void setRevealHiddenLines(bool show);
        bool isRevealHiddenLines();

		/**
			グリッド間隔
		*/
        int getGridInterval();
        void setGridIntervalIndex(int index);

        //高さチェック
        bool isValidHeight(int zMin, int zMax);
    private:
        /**
            ズーム調整
            @param step 変化量
        */
        void addZoom(int step, int viewW, int viewH);
    };
};
};
};
#endif

