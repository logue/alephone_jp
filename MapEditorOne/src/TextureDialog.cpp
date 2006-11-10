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

// CTextureDialog �_�C�A���O

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


// CTextureDialog ���b�Z�[�W �n���h��

BOOL CTextureDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO :  �����ɏ�������ǉ����Ă�������
    child = new CTextureChildDialog(this);

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
            //�k���\��
            
            type ++;
        }
    }
}

//�R���N�V������ݒ肵�čX�V
void CTextureDialog::setupDialog(int col)
{
}

