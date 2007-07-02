#include "General.h"

GlobalData globalData;

const double A_POLYGON_RADIUS = 100;
void init();
void loop(SDL_Surface* screen);
void doEvent();
void step();
void drawCommon(SDL_Surface* screen);

double getRandomDouble(double min, double max)
{
    double r = (rand() % (int)((max + min) * BIAS) - min * BIAS) / BIAS;
    return r;
}

std::vector<int> hogeVec;
std::list<int> hogeList;
std::map<int, int> hogeMap;


static void printLists(){
    printf("#Vector\n");
    for(int i = 0; i < hogeVec.size(); i ++){
        printf("%d:%d\n", i, &hogeVec[i]);
    }
    printf("#List\n");
    int counter = 0;
    for(std::list<int>::iterator it = hogeList.begin(); it != hogeList.end(); it ++){
        int* add = &(*it);
        printf("%d:%d\n", counter, add);
        counter ++;
    }
    printf("#Map\n");
    counter = 0;
    for(std::map<int,int>::iterator it = hogeMap.begin(); it != hogeMap.end(); it ++){
        int* add = &(*it).second;
        printf("%d:%d\n", counter, add);
        counter ++;
    }
}

static void printPairs(hpl::math::qsort::Pair<double> pairs[], int max){
    for(int i = 0; i < max; i ++){
        printf("[%d]=%lf\n", pairs[i].index, pairs[i].data);
    }
}

int main(int argc, char** argv){
    const int NUM = 3;

    //quickSortの検証
    hpl::math::qsort::Pair<double> pairs[NUM];
    int max = NUM;
    for(int i = 0; i < max; i ++){
        pairs[i].index = i;
        pairs[i].data = rand()%100;
    }
    //表示してみる
    printPairs(pairs, max);
    //ソート
    hpl::math::qsort::quickSort(pairs, max);
    printf("sorted\n");
    //表示してみる
    printPairs(pairs, max);
    getchar();
    return 0;
    /*
    for(int i = 0; i < NUM; i ++){
        hogeVec.push_back(i);
        hogeList.push_back(i);
        hogeMap[i] = i;
    }

    //アドレスを表示してみる
    printLists();

    //先頭を削除してみる
    std::vector<int>::iterator it = hogeVec.begin();
    it += 1;
    hogeVec.erase(it);
    hogeList.pop_front();
    hogeMap.erase(hogeMap.begin());
    
    //また表示してみる
    printLists();

    return 0;
    */

    //SDL初期化するよ
    SDL_Init(SDL_INIT_VIDEO);

    //Video初期化するよ
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP, SDL_SWSURFACE);
    
    init();
    //ループ
    loop(screen);

    //終了するよ
    SDL_Quit();
    return 0;
}

BounceBall* getRandomNewBounceBall()
{
    double x = rand() % WINDOW_WIDTH;
    double y = rand() % WINDOW_HEIGHT;
    double deg = getRandomDouble(0,360);
    double rad = hpl::math::getRadianFromDegree(deg);
    double dx = cos(rad) * BALL_SPEED;
    double dy = sin(rad) * BALL_SPEED;
    double size = BALL_SIZE;
    BounceBall* ball = new BounceBall(x, y, dx, dy, size);
    return ball;
}


void init()
{
    //初期化設定だよ
    globalData.isRunning = true;

    //ball setup
    for(int i = 0; i < BALL_NUM; i ++){
        globalData.balls[i] = getRandomNewBounceBall();
    }
    globalData.catchedBall = -1;
    globalData.nPolygon = 3;

    //正8角形でスタート
    double points[MAX_POLYGON][2];
    double radius = A_POLYGON_RADIUS;
    hpl::math::getCirculatePolygonPoints(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
        radius, MAX_POLYGON, points);
    for(int i = 0; i < A_POLY_BALL_NUM; i ++){
        globalData.polygonBalls[i] = getRandomNewBounceBall();
        if(i < MAX_POLYGON){
            globalData.polygonBalls[i]->x = points[i][0];
            globalData.polygonBalls[i]->y = points[i][1];
        }
    }

    //チェックタイプ
    globalData.checkType = CheckType::IsPointInPolygon;
}

void loop(SDL_Surface* screen)
{
    while(globalData.isRunning){
        //イベント処理するよ
        doEvent();

        step();

        drawCommon(screen);
        draw(screen);

        SDL_Flip(screen);

        SDL_Delay(16);
    }
}

void upNPolygon()
{
    globalData.nPolygon ++;
    if(globalData.nPolygon > MAX_POLYGON){
        globalData.nPolygon = MIN_POLYGON;
    }
}
void downNPolygon()
{
    globalData.nPolygon --;
    if(globalData.nPolygon < MIN_POLYGON){
        globalData.nPolygon = MAX_POLYGON;
    }
}
void upPolyCheckType()
{
    globalData.checkType ++;
    if(globalData.checkType >= CheckType::MAX_CHECK_TYPES){
        globalData.checkType = 0;
    }
}
void downPolyCheckType()
{
    globalData.checkType --;
    if(globalData.checkType < 0){
        globalData.checkType = CheckType::MAX_CHECK_TYPES - 1;
    }
}

void doEvent()
{
    //イベント取得するよ
    SDL_Event ev;
    while(SDL_PollEvent(&ev)){
        switch(ev.type){
        case SDL_QUIT:
            globalData.isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(ev);
            break;
        case SDL_MOUSEMOTION:
            onMouseMotion(ev);
            break;
        case SDL_MOUSEBUTTONUP:
            globalData.catchedBall = -1;
            break;
        case SDL_KEYDOWN:
            int key = ev.key.keysym.sym;
            if(key == SDLK_UP){
                upNPolygon();
            }else if(key == SDLK_DOWN){
                downNPolygon();
            }else if(key == SDLK_a){
                upPolyCheckType();
            }else if(key == SDLK_z){
                downPolyCheckType();
            }
            break;
        }
    }
}

void step()
{
    //ボール移動
/*    for(int i = 0; i < BALL_NUM; i ++){
        globalData.balls[i]->step(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }*/

}

/**
    @param x1,y1 終点
    @param length 鏃の長さ
*/
void drawArrow(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a, double length)
{
    double dx = x1 - x0;
    double dy = y1 - y0;
    //0->1の角度を得ます
    double deg = hpl::math::getDegreeFromVector(dx, dy);
    //135度ずらす
    for(int i = -1; i < 2; i += 2){
        double newDeg = deg + (double)i * 160;
        double rad = hpl::math::getRadianFromDegree(newDeg);
        //
        double newX = x1 + cos(rad) * length;
        double newY = y1 + sin(rad) * length;
        //線を引きます
        drawLine(screen, x1, y1, newX, newY, r, g, b, a);
    }
    drawLine(screen, x0, y0, x1, y1, r, g, b, a);
}

void drawAngleAndSlice(SDL_Surface* screen, double line[2][2], int x, int y,
                       int r, int g, int b, int a)
{
    double degree, slice;
    hpl::math::getLineAngleAndSlice(line, &degree, &slice);
    char buf[BUF_MAX];
    double angle = hpl::math::getAngleFromDegree(degree);
    sprintf(buf, "0:(%d,%d)-(%d,%d), \nangle:%f, degree:%f, slice:%f",
        (int)line[0][0], (int)line[0][1], (int)line[1][0], (int)line[1][1],
        angle, degree, slice);
    stringRGBA(screen, x,y,buf, r,g,b,a);
}
void drawBall(SDL_Surface* screen, double x, double y, double size,
              double r, double g, double b, double a)
{
    SDL_Rect rect = {(Sint16)(x - size / 2), (Sint16)(y - size / 2), (Uint16)size, (Uint16)size};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, (Uint8)r, (Uint8)g, (Uint8)b));
}

/**
    線を引く（簡易版）。これを使うことでライブラリの変動に柔軟に（ｒｙ
*/
void drawLine(SDL_Surface* screen, double x0, double y0, double x1, double y1, int r, int g, int b, int a)
{
    lineRGBA(screen, (Sint16)x0, (Sint16)y0,
        (Sint16)x1, (Sint16)y1,
        r,g,b,a);
}

/**
    文字列を出力します
*/
void drawString(SDL_Surface* screen, double x, double y, int r, int g, int b, int a, const char* format, ...)
{
    char messages[BUF_MAX];
    va_list maker;
    va_start(maker, format);
    vsprintf(messages, format, maker);
    
    //改行を分断する
    std::vector<std::string> lines = hpl::string::Split(std::string(messages), "\n");

    //一行ずつ表示
    for(int i = 0; i < (int)lines.size(); i ++){
        int tempY = (int)(y + FONT_SIZE * i);
        stringRGBA(screen, (Sint16)x, (Sint16)tempY, lines[i].c_str(), r, g, b, a);
    }
}

/**
    操作説明を記します
*/
void drawCommon(SDL_Surface* screen)
{
    //消去
    SDL_FillRect(screen, NULL, 0);
    double x = WINDOW_WIDTH - 200;
    double y = 0;
    drawString(screen, x, y, 255,255,255,255, "up/down : change num of polygon's edges");
    y += FONT_SIZE;
    drawString(screen, x, y, 255,255,255,255, "a/z     : change polygon check type");
}
