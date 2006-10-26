// SelectPolygonDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "SelectPolygonDialog.h"


// CSelectPolygonDialog ダイアログ

IMPLEMENT_DYNAMIC(CSelectPolygonDialog, CDialog)

CSelectPolygonDialog::CSelectPolygonDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectPolygonDialog::IDD, pParent)
{
    pointsOfPolygon = 3;
}

CSelectPolygonDialog::~CSelectPolygonDialog()
{
}

void CSelectPolygonDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON1, polygon3);
    DDX_Control(pDX, IDC_BUTTON2, polygon4);
    DDX_Control(pDX, IDC_BUTTON3, polygon5);
    DDX_Control(pDX, IDC_BUTTON4, polygon6);
    DDX_Control(pDX, IDC_BUTTON5, polygon7);
    DDX_Control(pDX, IDC_BUTTON6, polygon8);
}


BEGIN_MESSAGE_MAP(CSelectPolygonDialog, CDialog)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_BN_CLICKED(IDC_BUTTON1, &CSelectPolygonDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CSelectPolygonDialog::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CSelectPolygonDialog::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CSelectPolygonDialog::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CSelectPolygonDialog::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CSelectPolygonDialog::OnBnClickedButton6)
END_MESSAGE_MAP()


// CSelectPolygonDialog メッセージ ハンドラ

void CSelectPolygonDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: ここにメッセージ ハンドラ コードを追加します。
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。
}

BOOL CSelectPolygonDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //set button's images
    polygon3.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP_POLYGON3)));
    polygon4.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP_POLYGON4)));
    polygon5.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP_POLYGON5)));
    polygon6.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP_POLYGON6)));
    polygon7.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP_POLYGON7)));
    polygon8.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP_POLYGON8)));
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSelectPolygonDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    
    CDialog::OnLButtonDown(nFlags, point);
}

void CSelectPolygonDialog::OnBnClickedButton1()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    pointsOfPolygon = 3;
    DestroyWindow();
}

void CSelectPolygonDialog::OnBnClickedButton2()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    pointsOfPolygon = 4;
    DestroyWindow();
}
void CSelectPolygonDialog::OnBnClickedButton3()
{
    // TODO: ここにコントロール通知ハンドラ コードを追加します。
    pointsOfPolygon = 5;
    DestroyWindow();
}
void CSelectPolygonDialog::OnBnClickedButton4()
{
    pointsOfPolygon = 6;
    DestroyWindow();
}
void CSelectPolygonDialog::OnBnClickedButton5()
{
    pointsOfPolygon = 7;
    DestroyWindow();
}
void CSelectPolygonDialog::OnBnClickedButton6()
{
    pointsOfPolygon = 8;
    DestroyWindow();
}
