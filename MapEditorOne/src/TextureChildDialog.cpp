// TextureChildDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "TextureChildDialog.h"

const int LEFT_MERGIN = 10;
const int TOP_MERGIN = 10;
const int INTERVAL_X = 10;
const int INTERVAL_Y = 10;
const int TILE_W = 30;
const int TILE_H = 30;

// CTextureChildDialog ダイアログ

IMPLEMENT_DYNAMIC(CTextureChildDialog, CDialog)

CTextureChildDialog::CTextureChildDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureChildDialog::IDD, pParent)
{
    parent = pParent;
}

CTextureChildDialog::~CTextureChildDialog()
{
}

void CTextureChildDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTextureChildDialog, CDialog)
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CTextureChildDialog メッセージ ハンドラ

BOOL CTextureChildDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CTextureChildDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: ここにメッセージ ハンドラ コードを追加します。
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。

    CRect clRect;
    GetClientRect(&clRect);

    dc.SelectObject(GetStockObject(NULL_PEN));
    dc.SelectObject(GetStockObject(BLACK_PEN));
    dc.Rectangle(clRect);

    int tileNumX = (clRect.Width() - LEFT_MERGIN * 2) / (TILE_W + INTERVAL_X);
    int tileNumY = (clRect.Height() - TOP_MERGIN * 2) / (TILE_H + INTERVAL_Y);
    int type = 0;

    int clut = 0;
    int collection = ((CTextureDialog*)parent)->collection;

    struct collection_header* header = get_collection_header(collection);
    //get number of bitmaps
    int bitmapNum = header->collection->bitmap_count;
    CDC memDC;
    memDC.CreateCompatibleDC(&dc);

    for(int x = 0 ; x < tileNumX && type < bitmapNum; x ++){
        for(int y = 0; y < tileNumY && type < bitmapNum; y ++){
            int tileX = LEFT_MERGIN + x * (TILE_W + INTERVAL_X);
            int tileY = TOP_MERGIN + y * (TILE_H + INTERVAL_Y);
            CRect destRect = CRect(tileX, tileY, tileX + TILE_W, tileY + TILE_H);
            CBitmap* bmp = theApp.textureBitmaps[collection][type];
            BITMAP bmpInfo;
            bmp->GetBitmap(&bmpInfo);

            memDC.SelectObject(bmp);
            //縮小表示
            dc.StretchBlt(destRect.left, destRect.top,
                destRect.Width(), destRect.Height(),
                &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
            type ++;
        }
    }

    memDC.DeleteDC();
}

void CTextureChildDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: ここにメッセージ ハンドラ コードを追加します。
}
