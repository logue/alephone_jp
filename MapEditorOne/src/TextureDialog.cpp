// TextureDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "TextureDialog.h"
#include ".\texturedialog.h"


const int LEFT_MERGIN = 10;
const int TOP_MERGIN = 10;
const int INTERVAL_X = 10;
const int INTERVAL_Y = 10;
const int TILE_W = 30;
const int TILE_H = 30;

// CTextureDialog ダイアログ

IMPLEMENT_DYNAMIC(CTextureDialog, CDialog)
CTextureDialog::CTextureDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureDialog::IDD, pParent)
{
}

CTextureDialog::~CTextureDialog()
{
    delete child;
}

void CTextureDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, typeCmb);
}


BEGIN_MESSAGE_MAP(CTextureDialog, CDialog)
    ON_WM_CLOSE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CTextureDialog メッセージ ハンドラ

BOOL CTextureDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO :  ここに初期化を追加してください
    child = new CTextureChildDialog(this);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CTextureDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CTextureDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CTextureDialog::PostNcDestroy()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CTextureDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CTextureDialog::DestroyWindow()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

void CTextureDialog::OnPain()
{
    CPaintDC dc(this); // device context for painting

    //get picture box's rect
    CRect pictboxRect;
    CWnd *pictBox = GetDlgItem(IDC_PICTURE);
    pictBox->GetClientRect(&pictboxRect);

    CDC *pictDC = pictBox->GetDC();    //clear rect
    pictDC->SelectObject(GetStockObject(NULL_PEN));
    pictDC->SelectObject(GetStockObject(BLACK_PEN));
    pictDC->Rectangle(pictboxRect);

    int tileNumX = (pictboxRect.Width() - LEFT_MERGIN * 2) / (TILE_W + INTERVAL_X);
    int tileNumY = (pictboxRect.Height() - TOP_MERGIN * 2) / (TILE_H + INTERVAL_Y);
    int type = 0;

    int clut = clutCmb.GetCurSel()
    struct collection_header* header = get_collection_header(collectionIndex);
    //get number of bitmaps
    int bitmapNum = header->collection->bitmap_count;

    for(int x = 0 ; x < tileNumX && type < bitmapNum; x ++){
        for(int y = 0; y < tileNumY && type < bitmapNum; y ++){
            int tileX = LEFT_MERGIN + tileX * (TILE_W + INTERVALX);
            int tileY = TOP_MERGING + tileY * (TILE_H + INTERVAL_Y);
            CRect destRect = CRect(tileX, tileY, tileX + TILE_X, tileY + TILE_H);
            //縮小表示
            
            type ++;
        }
    }
}

//コレクションを設定して更新
void CTextureDialog::setupDialog(int col)
{
}

