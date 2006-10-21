// ShowImageDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "ShowImageDialog.h"

const int LENGTH_OF_BOTTOM_MERGE = 30;

// CShowImageDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CShowImageDialog, CDialog)

CShowImageDialog::CShowImageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CShowImageDialog::IDD, pParent)
{

}

CShowImageDialog::~CShowImageDialog()
{
}

void CShowImageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowImageDialog, CDialog)
    ON_WM_SIZE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CShowImageDialog ���b�Z�[�W �n���h��

void CShowImageDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    Invalidate(FALSE);
}

BOOL CShowImageDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CShowImageDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B
    
    CRect winRect;
    this->GetClientRect(&winRect);

    CRect imageRect = winRect;
    imageRect.bottom = imageRect.top + winRect.Height() -
        LENGTH_OF_BOTTOM_MERGE;


    //clear back
    dc.SelectObject(GetStockObject(BLACK_BRUSH));
    dc.Rectangle(&imageRect);
    
    //draw surface
    int collection = BUILD_COLLECTION(collectionIndex, clutNum);
    int shape = BUILD_DESCRIPTOR(collection, bitmapIndex);
    byte** outp = (byte**)malloc(sizeof(byte*));
    SDL_Color palette[256];
    SDL_Surface* surface = get_shape_surface(shape, NONE,
        outp, 1.0, false, palette);
    
    drawSurfaceByPalette(&dc, surface, palette, imageRect);

    free(outp);
    SDL_FreeSurface(surface);
}

void CShowImageDialog::setupDialog(int col, int bitmap, int clut)
{
    collectionIndex = col;
    bitmapIndex = bitmap;
    clutNum = clut;
}
