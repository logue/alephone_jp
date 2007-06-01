#include "General.h"

#ifdef SEARCH_POLY
void onMouseButtonDown(SDL_Event ev){
    globalData.catchedBall = -1;
    //選択できているか探す
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
        //選択している・ボタンを押している場合
        //位置移動
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
    //点の数表示
    drawString(screen, 0, y + FONT_SIZE, 255, 255, 255, 255, "Points num:%d", globalData.nPolygon);
    //チェックタイプ表示
    int c = globalData.checkType;
    drawString(screen, 0, y + 2 * FONT_SIZE, checkTypeColor[c][0], checkTypeColor[c][1], 
        checkTypeColor[c][2], checkTypeColor[c][3], 
        CHECK_TYPE_STRING[c]);

	//点の番号
	for(int i = 0; i < MAX_POLYGON; i ++){
		int x = globalData.polygonBalls[i]->x;
		y = globalData.polygonBalls[i]->y;
		drawString(screen, x, y, 255,255,255,255, "%d", i);
	}
}

bool isEnablePolygonDraw()
{
    int ch = globalData.checkType;
    bool enable = false;
    int px = (int)globalData.polygonBalls[A_POLY_BALL_NUM - 1]->x;
    int py = (int)globalData.polygonBalls[A_POLY_BALL_NUM - 1]->y;
    //ポリゴン位置情報
    double polyPoints[MAX_POLYGON][2];
    for(int i = 0; i < MAX_POLYGON; i ++){
        polyPoints[i][0] = globalData.polygonBalls[i]->x;
        polyPoints[i][1] = globalData.polygonBalls[i]->y;
    }
    //n角形の頂点の数
    int n = globalData.nPolygon;
    if(ch == CheckType::IsPointInPolygon){
        //点がポリゴン内にあれば真
        //if(isPointInPolygon(
        //AlephOneのポリゴンチェッカーには任せておけない！
        if(hpl::math::isPointInPolygon(px, py, polyPoints, n)){
            enable = true;
        }
    }else if(ch == CheckType::IsCanFillPolygonFromPoint){
        //この点から塗りつぶせるポリゴンを探します
        //この点で塗りつぶせるポリゴンを見つけたら真

    }else if(ch == CheckType::IsValidPolygon){
        //ポリゴンが正しいか判断します
        //・指定以上の点を持たないこと
        //・内向き鋭角を持たないこと
		if(hpl::math::isValidPolygon(polyPoints, n)){
			enable = true;
		}
    }else{
    }
    return enable;
}

void draw(SDL_Surface* screen)
{

    //点がポリゴンの中にあるかチェック
    bool enable = false;
    int ch = globalData.checkType;
    int c = ch;
    enable = isEnablePolygonDraw();

    if(enable){
        //ポリゴン表示
        Sint16 vx[MAX_POLYGON], vy[MAX_POLYGON];
        int n = globalData.nPolygon;
        for(int i = 0; i < n; i ++){
            vx[i] = (Sint16)globalData.polygonBalls[i]->x;
            vy[i] = (Sint16)globalData.polygonBalls[i]->y;
        }
        filledPolygonRGBA(screen, (const Sint16*)vx, (const Sint16*)vy, n, checkTypeColor[c][0], checkTypeColor[c][1], 
        checkTypeColor[c][2], checkTypeColor[c][3]);
    }

    //点表示
    for(int i = 0; i < A_POLY_BALL_NUM - 1; i ++){
        double x = globalData.polygonBalls[i]->x;
        double y = globalData.polygonBalls[i]->y;
        double size = BALL_SIZE;
        drawBall(screen, x, y, size, 255, 255, 0, 255);
    }

    //基点表示
    {
        int i = A_POLY_BALL_NUM - 1;
        double x = globalData.polygonBalls[i]->x;
        double y = globalData.polygonBalls[i]->y;
        double size = BALL_SIZE;
        drawBall(screen, x, y, size, 255, 0, 0, 255);
    }

    //線表示
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

    //モード表示
    drawStrings(screen, 0);
}

#endif
