// VisualDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "VisualDialog.h"


// CVisualDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CVisualDialog, CDialog)

CVisualDialog::CVisualDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CVisualDialog::IDD, pParent)
{
    m_SDLToWindows = NULL;
    testImage = NULL;
}

CVisualDialog::~CVisualDialog()
{
    if(m_SDLToWindows)delete m_SDLToWindows;
    SDL_FreeSurface(testImage);
}

void CVisualDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisualDialog, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CVisualDialog ���b�Z�[�W �n���h��

void CVisualDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B

    if(m_SDLToWindows){
        SDL_Surface* screen = m_SDLToWindows->getSurface();
        //drawing!
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));

        SDL_BlitSurface(testImage, NULL, screen, NULL);
        m_SDLToWindows->paint();
    }
    /*CWnd *pictBox = GetDlgItem(IDC_PICTURE);
    
    CRect pictRect;
    pictBox->GetClientRect(&pictRect);
    CDC *pictDC = pictBox->GetDC();

    CBrush blackBrush;
    blackBrush.CreateSolidBrush(RGB(0,0,0));
    CBrush *oldBrush = pictDC->SelectObject(&blackBrush);
    pictDC->Rectangle(&pictRect);
    blackBrush.DeleteObject();
    */
}

BOOL CVisualDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    CRect cl_rect;
    CWnd *pictBox = GetDlgItem(IDC_PICTURE);
    
    pictBox->GetClientRect(&cl_rect);
    m_SDLToWindows=new SDLToWindows(pictBox->m_hWnd, cl_rect);

    
    int collection = BUILD_COLLECTION(12, 0);
    int shape = BUILD_DESCRIPTOR(collection, 0);
    unsigned char** outPointerToPixelData = (unsigned char**)malloc(sizeof(unsigned char*) * 1);
    testImage = get_shape_surface(0,collection, outPointerToPixelData, 20);
    free(outPointerToPixelData);
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
