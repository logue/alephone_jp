// BitmapCLUTDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapCLUTDialog.h"


// CBitmapCLUTDialog ダイアログ

IMPLEMENT_DYNAMIC(CBitmapCLUTDialog, CDialog)
CBitmapCLUTDialog::CBitmapCLUTDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapCLUTDialog::IDD, pParent)
{
}

CBitmapCLUTDialog::~CBitmapCLUTDialog()
{
}

void CBitmapCLUTDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBitmapCLUTDialog, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CBitmapCLUTDialog メッセージ ハンドラ

BOOL CBitmapCLUTDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CBitmapCLUTDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

//paint field
void CBitmapCLUTDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: ここにメッセージ ハンドラ コードを追加します。
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。

    CRect frameRect;
    this->GetWindowRect(&frameRect);

    const int NUMBER_OF_ROW_PALETTE_ELEMENTS = 32;
    const int LENGTH_OF_PALETTE_ROW_SKIP = 20;
    const int LENGTH_OF_ELEMENT_COLUMN_SKIP = 1;
    const int LENGTH_OF_ELEMENT_ROW_SKIP = 1;
    const int ELEMENT_WIDTH = 10;
    const int ELEMENT_HEIGHT = 10;

    frameRect.left = frameRect.top = 0;
    dc.SelectObject(GetStockObject(LTGRAY_BRUSH));
    dc.Rectangle(&frameRect);
    if(theApp.isShapesLoaded){
        int collectionIndex = ((CBitmapsDialog*)parent)->collection;
        struct collection_header* header = get_collection_header(collectionIndex);
        int clutNum = header->collection->clut_count;
        vector<int> colorCount;
        for(int i = 0; i < clutNum; i ++){
            int numColors = 0;
            struct rgb_color_value* palette = get_collection_colors(collectionIndex, i, numColors);
            colorCount.push_back(numColors);
        }
        for(int i = 0; i < clutNum; i ++){
            int numColors = 0;
            struct rgb_color_value* palette = get_collection_colors(collectionIndex, i, numColors);

            int merge = 0;
            for(int j = 0; j < i; j ++){
                merge += LENGTH_OF_PALETTE_ROW_SKIP +
                    (colorCount[j] / NUMBER_OF_ROW_PALETTE_ELEMENTS + 1) *
                    (ELEMENT_HEIGHT + LENGTH_OF_ELEMENT_ROW_SKIP);
            }
            for(int j = 0; j < numColors; j ++){
                int left = (j % NUMBER_OF_ROW_PALETTE_ELEMENTS) * 
                    (ELEMENT_WIDTH + LENGTH_OF_ELEMENT_COLUMN_SKIP);
                int top = merge +
                    (j / NUMBER_OF_ROW_PALETTE_ELEMENTS) * 
                    (ELEMENT_HEIGHT + LENGTH_OF_ELEMENT_ROW_SKIP);
                CRect rect;
                rect.SetRect(left, top, left + ELEMENT_WIDTH, top + ELEMENT_HEIGHT);

                //color
                CBrush brush;
                brush.CreateSolidBrush(RGB(palette[j].red, palette[j].green,
                    palette[j].blue));
                dc.SelectObject(&brush);
                dc.Rectangle(rect);
                brush.DeleteObject();
            }
        }
    }else{

    }

}

void CBitmapCLUTDialog::setupDialog()
{

    Invalidate(FALSE);
}
