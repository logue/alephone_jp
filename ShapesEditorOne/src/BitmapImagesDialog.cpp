// BitmapImagesDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapImagesDialog.h"

const int LENGTH_OF_TOP_MERGE = 40;
const int LENGTH_OF_RIGHT_DELTA = 50;
const int PANEL_WIDTH = 100;
const int PANEL_HEIGHT = 100;
const int PANEL_COLUMN_SKIP = 1;
const int PANEL_ROW_SKIP = 1;
const int PANEL_SIZE_STEP = 5;
int NUMBER_OF_MAX_ROWS = 50;

bool isAlloced = false;
bool isReady = false;

// CBitmapImagesDialog ダイアログ

IMPLEMENT_DYNAMIC(CBitmapImagesDialog, CDialog)
CBitmapImagesDialog::CBitmapImagesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapImagesDialog::IDD, pParent)
    , clutNum(0)
    , idNum(_T(""))
{
    isFirstOfSetup = true;

}

CBitmapImagesDialog::~CBitmapImagesDialog()
{
    freeBitmaps();
    freeBuffer();
}

void CBitmapImagesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, clutNum);
    DDX_Control(pDX, IDC_COMBO1, clutCmb);
    DDX_Control(pDX, IDC_SLIDER1, scrollSlider);
    DDX_Text(pDX, IDC_EDIT2, idNum);
}


BEGIN_MESSAGE_MAP(CBitmapImagesDialog, CDialog)
    ON_WM_PAINT()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBitmapImagesDialog::OnNMCustomdrawSlider1)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CBitmapImagesDialog::OnCbnSelchangeCombo1)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CBitmapImagesDialog メッセージ ハンドラ

BOOL CBitmapImagesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

CBitmap* oldbitmap;


BOOL CBitmapImagesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
//    zoom = 0;
    offset = 0;
    selectBitmapIndex = NONE;
    isReady = true;
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CBitmapImagesDialog::allocBuffer(){
    bufferDC.CreateCompatibleDC(this->GetDC());
    CRect imageRect;
    getImageRect(&imageRect);

    CRect destRect;
    getDestRect(&destRect, 0, imageRect);

    int maxHeight = destRect.Height() * NUMBER_OF_MAX_ROWS;
    scrollSlider.SetRange(0, maxHeight);
    bufferBitmap.CreateCompatibleBitmap(this->GetDC(), 
        imageRect.Width(), imageRect.Height());
    oldbitmap = bufferDC.SelectObject(&bufferBitmap);

    isAlloced = true;

}

void CBitmapImagesDialog::freeBuffer(){
    if(isAlloced){
        bufferDC.SelectObject(oldbitmap);
        bufferBitmap.DeleteObject();
        bufferDC.DeleteDC();
    }

    isAlloced = false;
}

void CBitmapImagesDialog::freeBitmaps()
{
    for(int i = 0; i < (int)stockBitmapList.size(); i ++){
        stockBitmapList[i]->DeleteObject();
        delete stockBitmapList[i];
    }
    stockBitmapList.clear();
}

void CBitmapImagesDialog::setupDialog()
{
    int collectionIndex = theApp.collection;
    selectBitmapIndex = NONE;
    if(theApp.isShapesLoaded){
        if(isFirstOfSetup){
            scrollSlider.SetPos(0);

            //store clut
            struct collection_header* header = get_collection_header(collectionIndex);
            int clutNum = header->collection->clut_count;
            clutCmb.ResetContent();
            char cstr[10];
            for(int i = 0; i < clutNum; i ++){
                sprintf(cstr, "%d", i);
                clutCmb.InsertString(i, CString(cstr));
            }
            clutCmb.SetCurSel(0);

            //id
            sprintf(cstr, "%d", selectBitmapIndex);
            idNum.SetString(CString(cstr));

            //draw images
            draw(&bufferDC);
            isFirstOfSetup = false;
        }else{
        }
    }
    UpdateData();
    Invalidate(FALSE);
}

void CBitmapImagesDialog::getImageRect(CRect* rect)
{
    CRect panelRect;
    this->GetClientRect(&panelRect);

    *rect = panelRect;
    rect->left = 0;
    rect->top = LENGTH_OF_TOP_MERGE;
    rect->right = rect->left + rect->Width() - LENGTH_OF_RIGHT_DELTA;
    rect->bottom = rect->top + rect->Height() - LENGTH_OF_TOP_MERGE;
}

void CBitmapImagesDialog::getDestRect(CRect* rect, int index, CRect& imageRect)
{
    int width = PANEL_WIDTH + PANEL_SIZE_STEP;// * zoom;
    int holizontalPanelNum = imageRect.Width() / 
        (width + PANEL_COLUMN_SKIP) ;
    int height = PANEL_HEIGHT + PANEL_SIZE_STEP;// * zoom;

    int left = //imageRect.left + 
        (index % holizontalPanelNum) *
        (width + PANEL_COLUMN_SKIP);
    int top = //LENGTH_OF_TOP_MERGE +
        //imageRect.top + 
        (index / holizontalPanelNum) * 
        (height + PANEL_ROW_SKIP);
    top -= this->offset;
    rect->SetRect(left, top, left + width, top + height);
    
}

void CBitmapImagesDialog::draw(CDC *cdc)
{
    CRect imageRect;
    getImageRect(&imageRect);

    cdc->SelectObject(GetStockObject(LTGRAY_BRUSH));
    cdc->Rectangle(&imageRect);
    
    //CRect rect(0, 0, imageRect.Width(), imageRect.Height());
    //bufferDC.SelectObject(GetStockObject(LTGRAY_BRUSH));
    //bufferDC.Rectangle(rect);

    SDLToWindows *sdlToWin = new SDLToWindows(this->m_hWnd, imageRect);
    screenSurface = sdlToWin->getSurface();

    freeBitmaps();
    if(theApp.isShapesLoaded){
        int collectionIndex = theApp.collection;

        int clut = clutCmb.GetCurSel();

        struct collection_header* header = get_collection_header(collectionIndex);

        //get number of bitmaps
        int bitmapNum = header->collection->bitmap_count;

        /*
        int width = PANEL_WIDTH + PANEL_SIZE_STEP;// * zoom;
        int holizontalPanelNum = imageRect.Width() / 
            (width + PANEL_COLUMN_SKIP) ;
        int height = PANEL_HEIGHT + PANEL_SIZE_STEP;// * zoom;
*/
        SDL_Color palette[256];

        for(int i = 0; i < bitmapNum; i ++){

            /*
            int left = (i % holizontalPanelNum) *
                (width + PANEL_COLUMN_SKIP);
            int top = //LENGTH_OF_TOP_MERGE +
                (i / holizontalPanelNum) * 
                (height + PANEL_ROW_SKIP);
            top -= offset;
            CRect destRect(left, top, left + width, top + height);
            */
            CRect destRect;
            getDestRect(&destRect, i, imageRect);

            //get shape surface
            int collection = BUILD_COLLECTION(collectionIndex, clut);
            int shapes = BUILD_DESCRIPTOR(collection, i);
            int excol = NONE;
            float illumination = 1.0f;
            byte **outp = (byte**)malloc(sizeof(byte*));
            
            SDL_Surface *surface = get_shape_surface(shapes, excol, outp,
                illumination, false, palette);

            CBitmap *bitmap = new CBitmap();
            bitmap->CreateCompatibleBitmap(cdc, surface->w, surface->h);
            
            //copy to bitmap
            copySurfaceToBitmap(cdc, bitmap, surface, palette);

            free(outp);
            SDL_FreeSurface(surface);

            //add to list
            stockBitmapList.push_back(bitmap);
        }
    }
    delete sdlToWin;
}

void CBitmapImagesDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: ここにメッセージ ハンドラ コードを追加します。
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。

    CRect imageRect;
    getImageRect(&imageRect);

    CRect clRect;
    GetClientRect(&clRect);

    bufferDC.SelectObject(GetStockObject(NULL_PEN));
    bufferDC.SelectObject(GetStockObject(LTGRAY_BRUSH));
    bufferDC.Rectangle(clRect);

    //draw panels
    if(theApp.isShapesLoaded){
        int collectionIndex = theApp.collection;

        int clut = clutCmb.GetCurSel();

        struct collection_header* header = get_collection_header(collectionIndex);

        //get number of bitmaps
        int bitmapNum = header->collection->bitmap_count;

        CDC memDC;
        memDC.CreateCompatibleDC(&dc);

        for(int i = 0; i < bitmapNum; i ++){
            CRect destRect;
            getDestRect(&destRect, i, imageRect);
            /*if(isPointInRect<int>(destRect.left, destRect.top,
                imageRect.left, imageRect.top, imageRect.right, imageRect.bottom) ||
                isPointInRect<int>(destRect.right, destRect.bottom,
                imageRect.left, imageRect.top, imageRect.right, imageRect.bottom))
            {*/
                CBitmap* bitmap = stockBitmapList[i];

                memDC.SelectObject(bitmap);
                //drawSurfaceByPalette(&memDC, surface, palette, destRect);
                
                //元サイズ
                BITMAP bmpInfo;
                bitmap->GetBitmap(&bmpInfo);

                double perspective = (double)bmpInfo.bmWidth / bmpInfo.bmHeight;
                if(bmpInfo.bmWidth > bmpInfo.bmHeight){
                    destRect.bottom = (LONG)(destRect.top + destRect.Height() / perspective);
                }else{
                    destRect.right = (LONG)(destRect.left + destRect.Width() * perspective);
                }

                bufferDC.StretchBlt(destRect.left, destRect.top,
                    destRect.Width(), destRect.Height(),
                    &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

            //}

        }
        memDC.DeleteDC();
    }
    dc.BitBlt(0,LENGTH_OF_TOP_MERGE ,imageRect.Width(), imageRect.Height(),
        &bufferDC, 0, 0, SRCCOPY);

    if(selectBitmapIndex != NONE){
        CRect imageRect, destRect;
        getImageRect(&imageRect);
        getDestRect(&destRect, selectBitmapIndex, imageRect);
        destRect.top += LENGTH_OF_TOP_MERGE;
        destRect.bottom += LENGTH_OF_TOP_MERGE;
        //blit select rect
        CPen pen;
        pen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
        dc.SelectObject(&pen);
        dc.SelectObject(GetStockObject(NULL_BRUSH));
        dc.Rectangle(destRect);
        pen.DeleteObject();
    }
    dc.SelectObject(GetStockObject(NULL_PEN));
    dc.SelectObject(GetStockObject(LTGRAY_BRUSH));
    CRect bgRect = clRect;
    bgRect.bottom = bgRect.top + LENGTH_OF_TOP_MERGE;
    dc.Rectangle(bgRect);
}

//change slider
void CBitmapImagesDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int oldPos = offset;
    offset = scrollSlider.GetPos();
    if(offset != oldPos){
        Invalidate(FALSE);
    }
    *pResult = 0;
}
//clut cmb
void CBitmapImagesDialog::OnCbnSelchangeCombo1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    int sel = clutCmb.GetCurSel();
    clutNum = sel;
    draw(&bufferDC);
    Invalidate(FALSE);
    UpdateData();
}

int CBitmapImagesDialog::getIndexPointIn(int px, int py)
{
    CRect imageRect;
    getImageRect(&imageRect);

    int collectionIndex = theApp.collection;

    int clut = clutCmb.GetCurSel();

    struct collection_header* header = get_collection_header(collectionIndex);

    //get number of bitmaps
    int bitmapNum = header->collection->bitmap_count;

    for(int i = 0; i < bitmapNum; i ++){
        CRect destRect;
        getDestRect(&destRect, i, imageRect);
        destRect.OffsetRect(0, destRect.Height() / 2);

        if(isPointInRect<int>(px, py , destRect.left, destRect.top,
            destRect.right, destRect.bottom))
        {
            return i;
        }
    }
    return NONE;
}

void CBitmapImagesDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    CRect imageRect;
    getImageRect(&imageRect);
    if(theApp.isShapesLoaded && isPointInRect(point.x, point.y, imageRect.left, imageRect.top,
        imageRect.right, imageRect.bottom))
    {
        selectBitmapIndex = getIndexPointIn(point.x, point.y);
    }
    Invalidate();
    UpdateData();
    CDialog::OnLButtonDown(nFlags, point);
}

//double click 
void CBitmapImagesDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    CRect imageRect;
    getImageRect(&imageRect);
    if(theApp.isShapesLoaded && isPointInRect(point.x, point.y, imageRect.left, imageRect.top,
        imageRect.right, imageRect.bottom))
    {
        selectBitmapIndex = getIndexPointIn(point.x, point.y);
        if(selectBitmapIndex != NONE){
            int collectionIndex = theApp.collection;

            int clut = clutCmb.GetCurSel();

            struct collection_header* header = get_collection_header(collectionIndex);

            //show image viewer
            CShowImageDialog dlg(this);
            dlg.setupDialog(collectionIndex, selectBitmapIndex, clut);
            dlg.DoModal();
        }
    }
    Invalidate(FALSE);
    UpdateData();
    CDialog::OnLButtonDblClk(nFlags, point);
}

void CBitmapImagesDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: ここにメッセージ ハンドラ コードを追加します。

    if(isReady){
        freeBuffer();

        allocBuffer();
    }
}
