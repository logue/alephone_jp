#include "General.h"

#ifdef SEARCH_POLY
void onMouseButtonDown(SDL_Event ev){
    globalData.catchedBall = -1;
    //�I���ł��Ă��邩�T��
    double mx = (double)ev.button.x;
    double my = (double)ev.button.y;
    for(int i = 0; i < A_POLY_BALL_NUM; i ++){
        double dx = mx - globalData.polygonBalls[i]->x;
        double dy = my - globalData.polygonBalls[i]->y;
        double distance = hpl::math::getLength(dx, dy);
        if(distance <= SELECT_BALL_THRESHOLD){
            globalData.catchedBall = i;
            break;
        }
    }
}
void onMouseMotion(SDL_Event ev){
    int mx = ev.motion.x;
    int my = ev.motion.y;
    if(globalData.catchedBall >= 0 && globalData.catchedBall < A_POLY_BALL_NUM &&
        ev.motion.state == SDL_PRESSED)
    {
        //�I�����Ă���E�{�^���������Ă���ꍇ
        //�ʒu�ړ�
        globalData.polygonBalls[globalData.catchedBall]->x = (double)mx;
        globalData.polygonBalls[globalData.catchedBall]->y = (double)my;
    }
}

static int checkTypeColor[][4] ={
    {200,0,0,255},
    {0,200,0,255},
    {0,0,200,255}
};
static char CHECK_TYPE_STRING[][100] = {
    "Is Point In Polygon",
        "Can Fill Polygon From The Point",
        "Is Valid This Polygon",
};

void drawStrings(SDL_Surface* screen, int startY)
{
    int y = startY;
    drawString(screen, 0, y, 255, 255, 255, 255, "Search polygon");
    //�_�̐��\��
    drawString(screen, 0, y + FONT_SIZE, 255, 255, 255, 255, "Points num:%d", globalData.nPolygon);
    //�`�F�b�N�^�C�v�\��
    int c = globalData.checkTypeTable[globalData.checkType];
    drawString(screen, 0, y + 2 * FONT_SIZE, checkTypeColor[c][0], checkTypeColor[c][1], 
        checkTypeColor[c][2], checkTypeColor[c][3], 
        CHECK_TYPE_STRING[c]);
}

void draw(SDL_Surface* screen)
{
    //����
    SDL_FillRect(screen, NULL, 0);

    //�_���|���S���̒��ɂ��邩�`�F�b�N
    bool enable = false;
    CheckType::CheckType ch = globalData.checkType;
    int c = globalData.checkTypeTable[ch];
    if(ch == CheckType::IsPointInPolygon){
        //�_���|���S�����ɂ���ΐ^
        //if(isPointInPolygon(
    }else if(ch == CheckType::IsCanFillPolygonFromPoint){
    }else if(ch == CheckType::IsValidPolygon){
    }else{
    }

    if(enable){
        //�|���S���\��
        int vx[MAX_POLYGON], vy[MAX_POLYGON];
        int n = globalData.nPolygon;
        for(int i = 0; i < n; i ++){
            vx[n] = globalData.polygonBalls[i]->x;
            vy[n] = globalData.polygonBalls[i]->y;
        }
        polygonRGBA(screen, (const Sint16*)vx, (const Sint16*)vy, n, checkTypeColor[c][0], checkTypeColor[c][1], 
        checkTypeColor[c][2], checkTypeColor[c][3]);
    }

    //�_�\��
    for(int i = 0; i < A_POLY_BALL_NUM - 1; i ++){
        double x = globalData.polygonBalls[i]->x;
        double y = globalData.polygonBalls[i]->y;
        double size = BALL_SIZE;
        drawBall(screen, x, y, size, 255, 255, 0, 255);
    }

    //��_�\��
    {
        int i = A_POLY_BALL_NUM - 1;
        double x = globalData.polygonBalls[i]->x;
        double y = globalData.polygonBalls[i]->y;
        double size = BALL_SIZE;
        drawBall(screen, x, y, size, 255, 0, 0, 255);
    }

    //���\��
    int n = globalData.nPolygon;
    for(int i = 0; i < n; i ++){
        int index = i;
        int nextIndex = i + 1;
        if(i == n - 1){
            nextIndex = 0;
        }
        double x0 = globalData.polygonBalls[index]->x;
        double y0 = globalData.polygonBalls[index]->y;
        double x1 = globalData.polygonBalls[nextIndex]->x;
        double y1 = globalData.polygonBalls[nextIndex]->y;
        drawArrow(screen, x0, y0, x1, y1, 255, 100, 0, 255, ARROW_LENGTH);
    }

    //���[�h�\��
    drawStrings(screen, 0);
}

#endif
