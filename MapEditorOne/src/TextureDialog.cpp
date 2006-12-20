// TextureDialog.cpp : �����t�@�C��
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

const int CHILD_LEFT = 10;
const int CHILD_TOP = 30;
const int CHILD_W_DELTA = 10;
const int CHILD_H_DELTA = 10;

// CTextureDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CTextureDialog, CDialog)
CTextureDialog::CTextureDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureDialog::IDD, pParent)
{
    child = NULL;
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
    ON_WM_SHOWWINDOW()
    ON_WM_SIZE()
END_MESSAGE_MAP()

void CTextureDialog::resizeChild()
{
    CRect parentRect;
    GetClientRect(&parentRect);
    child->MoveWindow(CHILD_LEFT, CHILD_TOP, 
        parentRect.Width() - CHILD_LEFT - CHILD_W_DELTA,
        parentRect.Height() - CHILD_TOP - CHILD_H_DELTA);
}

// CTextureDialog ���b�Z�[�W �n���h��

BOOL CTextureDialog::OnInitDialog()
{
    CDialog::OnInitDialog();


    // TODO :  �����ɏ�������ǉ����Ă�������
    child = new CTextureChildDialog(this);
    child->Create(CTextureChildDialog::IDD, this);
    resizeChild();
    //child->ShowWindow(TRUE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
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
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CTextureDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CTextureDialog::DestroyWindow()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

void CTextureDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CDialog::OnPaint();
    //get picture box's rect
/*    CRect pictboxRect;
    CWnd *pictBox = GetDlgItem(IDC_PICTURE);
    pictBox->GetClientRect(&pictboxRect);

    CDC *pictDC = pictBox->GetDC();    //clear rect
    pictDC->SelectObject(GetStockObject(NULL_PEN));
    pictDC->SelectObject(GetStockObject(BLACK_PEN));
    pictDC->Rectangle(pictboxRect);

    int tileNumX = (pictboxRect.Width() - LEFT_MERGIN * 2) / (TILE_W + INTERVAL_X);
    int tileNumY = (pictboxRect.Height() - TOP_MERGIN * 2) / (TILE_H + INTERVAL_Y);
    int type = 0;

    int clut = 0;
    struct collection_header* header = get_collection_header(collection);
    //get number of bitmaps
    int bitmapNum = header->collection->bitmap_count;
    CDC memDC;
    memDC.CreateCompatibleDC(pictDC);

    for(int x = 0 ; x < tileNumX && type < bitmapNum; x ++){
        for(int y = 0; y < tileNumY && type < bitmapNum; y ++){
            int tileX = LEFT_MERGIN + tileX * (TILE_W + INTERVALX);
            int tileY = TOP_MERGING + tileY * (TILE_H + INTERVAL_Y);
            CRect destRect = CRect(tileX, tileY, tileX + TILE_X, tileY + TILE_H);
            CBitmap* bmp = theApp.textureBitmaps[collection][type];
            BITMAP bmpInfo;
            bmp->GetBitmap(&bmpInfo);

            memDC.SelectObject(bmp);
            //�k���\��
            bufferDC.StretchBlt(destRect.left, destRect.top,
                destRect.Width(), destRect.Height(),
                &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
            type ++;
        }
    }

    memDC.DeleteDC();*/
}

//�R���N�V������ݒ肵�čX�V
void CTextureDialog::setupDialog(int col)
{
    collection = col;
    Invalidate(FALSE);
}


void CTextureDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);
    
    child->ShowWindow(bShow);
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
}

void CTextureDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    //resize child dialog
    if(child){
        resizeChild();
    }
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
}