// ToolDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ToolDialog.h"
#include ".\tooldialog.h"



// CToolDialog ダイアログ

IMPLEMENT_DYNAMIC(CToolDialog, CDialog)
CToolDialog::CToolDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CToolDialog::IDD, pParent)
{
    //imageList.Create(TOOL_WIDTH, TOOL_HEIGHT, ILC_COLOR32, NUMBER_OF_TOOLS * 2, 2);


    //イメージ名リスト読み込み
    Information imageNameInformations[NUMBER_OF_TOOL_BAR_ICON_FILES];
    char cstr[260];
    sprintf(cstr, "%s%s", DATA_DIR_NAME, TOOL_BAR_ICONS_IMAGE_LIST_FILE_NAME);
    loadInformations(cstr, NUMBER_OF_TOOL_BAR_ICON_FILES,
        imageNameInformations);
    /*
    //アイコン読み込み
    int assignment[]={
        //unselected
        IDB_BITMAP5,
        IDB_BITMAP7,
        IDB_BITMAP8,
        IDB_BITMAP12,
        IDB_BITMAP13,
        IDB_BITMAP15,
        IDB_BITMAP16,
        IDB_BITMAP3,

        //selected
        IDB_BITMAP4,
        IDB_BITMAP6,
        IDB_BITMAP9,
        IDB_BITMAP11,
        IDB_BITMAP13,
        IDB_BITMAP14,
        IDB_BITMAP17,
        IDB_BITMAP19,
    };
    */
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS * 2; i ++){
        CString path = CString(DATA_DIR_NAME) + CString(TOOL_BAR_ICONS_DIR_NAMR);
        if(i >= ToolType::NUMBER_OF_TOOLS){
            path += CString(SELECTED_ICONS_DIR_NAME);
        }
        path += imageNameInformations[i % ToolType::NUMBER_OF_TOOLS].jname;
        strToChar(path, cstr);
        HBITMAP bmp = loadBitmapFromFile(cstr);
        
        bitmaps.push_back(bmp);
    }
}

CToolDialog::~CToolDialog()
{
    for(int i = 0; i < (int)bitmaps.size(); i ++){
        DeleteObject(bitmaps[i]);
    }
    bitmaps.clear();
}

void CToolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolDialog, CDialog)
    ON_WM_CLOSE()
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CToolDialog メッセージ ハンドラ

BOOL CToolDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CToolDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(TEXT("Failed"));
    }
    return ret;
}

void CToolDialog::PostNcDestroy()
{
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CToolDialog::OnClose()
{
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CToolDialog::DestroyWindow()
{
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

BOOL CToolDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CToolDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。
    //draw tools
    CDC memDC;
    memDC.CreateCompatibleDC(&dc);
//    CBitmap* old = memDC.SelectObject(bitmaps[0]);
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
        POINT pt;
#ifdef MAP_VIEWER
        if(i % 2 == 1 || i >= 6){
            continue;
        }
#endif
        pt.x = (i % 2) * TOOL_WIDTH;
        pt.y = (i / 2) * TOOL_HEIGHT;

        //imageList.Draw(&dc, i, pt, SRCCOPY);
        int index = i;
        if(theApp.getEventManager()->getToolType() == i){
            index += ToolType::NUMBER_OF_TOOLS;
        }
        CBitmap* bmp = CBitmap::FromHandle(bitmaps[index]);
        BITMAP bmpInfo;
        bmp->GetBitmap(&bmpInfo);
        memDC.SelectObject(bmp);
        dc.BitBlt(pt.x, pt.y, TOOL_WIDTH, TOOL_HEIGHT, &memDC,
            0, 0, SRCCOPY);

    }
//    memDC.SelectObject(old);
    memDC.DeleteDC();
}

//click dialog to select tool
void CToolDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
        CRect rect;
        rect.left = (i % 2) * TOOL_WIDTH;
        rect.top = (i / 2) * TOOL_HEIGHT;
        rect.right = rect.left + TOOL_WIDTH;
        rect.bottom = rect.top + TOOL_HEIGHT;
        if(hpl::math::isPointInRect<int>(point.x, point.y,
            rect.left, rect.top, rect.right, rect.bottom))
        {
            //ツール変化
            theApp.getEventManager()->setToolType(i);
            if(i == ToolType::TI_SKULL){
                //show object property's dialog
                theApp.objectPropertyDialog->ShowWindow(TRUE);
            }else if(i == ToolType::TI_POLYGON){
                //show polygon dialog
                CSelectPolygonDialog dlg(this);
                dlg.DoModal();
                theApp.numberOfPolygonPoints = dlg.pointsOfPolygon;
            }
            Invalidate(FALSE);
            setCursor();
        }
    }
    CDialog::OnLButtonDown(nFlags, point);
}



void CToolDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
    CDialog::OnActivate(nState, pWndOther, bMinimized);

    // TODO: ここにメッセージ ハンドラ コードを追加します。
}
