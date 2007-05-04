/**
    <jp>拡大縮小や、編集位置Offsetの修正、座標変換、スクロール表示など
        をまとめて管理するマネージャーです
    <en>the manager that manage zooming in or out, offsets for editing, exchanging
        different coordinates, scrolling, and so on
*/
#ifndef _HPL_VIEW_GRID_MANAGER_
#define _HPL_VIEW_GRID_MANAGER_

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
        int viewOffset;
    public:
        HPLViewGridManager(ZoomProperties *zoomProp);
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

