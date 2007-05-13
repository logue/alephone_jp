#include "PresetPolygon.h"
#include "HPLLib/HPLAlephLib.h"

/**
    ���_�̐����w�肵�Đ���
    @param n the number of edges
*/
mapeditorone::PresetPolygon::PresetPolygon(int n)
{
    //�R�p�`�ȉ��̓_���Ȃ̂łR�p�`�ɂ���
    if(n < 3){
        n = 3;
    }

    //�W�p�`����ł̓G���[���N����
    if(n > 8){
        n = 8;
    }
    this->num = n;
}
mapeditorone::PresetPolygon::~PresetPolygon()
{
}

const int ROUND_DEGREE = 360;

/**
    �͈͎w�肩��|���S�����W�𓾂܂�
*/
void mapeditorone::PresetPolygon::getPoints(int x0, int y0, int x1, int y1, int *dest)
{
    //p0������Ap1���E���ɂȂ�悤�ɃZ�b�g
    if(x0 > x1){
        hpl::math::exchange<int>(&x0, &x1);
    }
    if(y0 > y1){
        hpl::math::exchange<int>(&y0, &y1);
    }
    //���S���W�����_�܂ł̋����𔼌a�Ƃ���~��z�肷��
    int centerX = x0 + (x1 - x0) / 2;
    int centerY = y0 + (y1 - y0) / 2;
    int r = sqrt(pow(centerX - x0, 2) + pow(centerY - y0, 2));
    
    //�~�����ɐ�n�p�`���擾����
    //���߂�~����̓_
    int points[8][2];
    //��n�p�`�̊e�ӂɑ΂��钆�S�p
    int degInterval = ROUND_DEGREE / this->num;
    for(int degStep = 0; degStep < this->num; degStep ++){
        int degree = degStep * degInerval;

        //�����E���O�x�A�^�����X�O�x�Ȃ̂ŁA-90����
        degree -= (ROUND_DEGREE / 4);

        double rad = hpl::math::getRadianFromDegree(degree);
        points[degStep][0] = cos(rad) * r;
        points[degStep][1] = sin(rad) * r;

        //�����`�Ƃ̌�_�����߂�

    }
}
