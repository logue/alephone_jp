/**
    <jp>�g��k����A�ҏW�ʒuOffset�̏C���A���W�ϊ��A�X�N���[���\���Ȃ�
        ���܂Ƃ߂ĊǗ�����}�l�[�W���[�ł�
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
        /**���̊g��k���Ő�����ω���*/
        int zoomDivisionStep;

        /**�g�嗦��������臒l*/
        int zoomDivStepThreshold;

        /**�g�嗦����������̑������x*/
        int zoomDivisionStepDetail;

        /**�ő�l*/
        int zoomDivisionMax;

        /**�ŏ��l*/
        int zoomDivisionMin;

        /**�����l�E�K��l*/
        int zoomDivisionDefault;

        //�O���b�h
        int gridIntervals[NUMBER_OF_GLID];

    };
    /**
        �g��k���A�X�N���[���Ȃǂ̊Ǘ�
    */
    class HPLViewGridManager{
    private:
        /**�g��֌W�̒萔*/
        ZoomProperties zoomProperties;

        /**���݂̊g�劄��*/
        int zoomDivision;

        /**View���W�̃I�t�Z�b�g*/
        int viewOffset[2];

        //�}�E�X���W�i���j
        int oldMousePoint[2];
        int newMousePoint[2];

        //�O���b�h
        int gridIndex;

        //�\���E�ҏW�ł��鍂��
        int viewHeightMax;
        int viewHeightMin;
        //�����͈͊O�̃|���S������\�����邩�H
        bool isRevealHiddenLines_;
    public:
        HPLViewGridManager();
        void setProp(ZoomProperties *zoomProp);
        ~HPLViewGridManager();

    public:
        /**
            �g�嗦�擾
            <en>get zoom division
        */
        int getZoomDivision();
        /**
            zoom in
            @param viewW, viewH View�͈͂̃T�C�Y
        */
        void zoomIn(int viewW, int viewH);

        /**
            zoom out
        */
        void zoomOut(int viewW, int viewH);

        /**
            �g�嗦������
        */
        void zoomReset();

        //void setOldMousePoint(int x, int y);
        /**
            �}�E�X���W���Z�b�g���܂�
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
			�O���b�h�Ԋu
		*/
        int getGridInterval();
        void setGridIntervalIndex(int index);

        //�����`�F�b�N
        bool isValidHeight(int zMin, int zMax);
    private:
        /**
            �Y�[������
            @param step �ω���
        */
        void addZoom(int step, int viewW, int viewH);
    };
};
};
};
#endif

