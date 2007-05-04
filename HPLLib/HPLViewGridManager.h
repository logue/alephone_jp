/**
    <jp>�g��k����A�ҏW�ʒuOffset�̏C���A���W�ϊ��A�X�N���[���\���Ȃ�
        ���܂Ƃ߂ĊǗ�����}�l�[�W���[�ł�
    <en>the manager that manage zooming in or out, offsets for editing, exchanging
        different coordinates, scrolling, and so on
*/
#ifndef _HPL_VIEW_GRID_MANAGER_
#define _HPL_VIEW_GRID_MANAGER_

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
        int viewOffset;
    public:
        HPLViewGridManager(ZoomProperties *zoomProp);
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

