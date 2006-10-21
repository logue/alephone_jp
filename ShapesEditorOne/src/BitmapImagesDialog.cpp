// BitmapImagesDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapImagesDialog.h"

const int LENGTH_OF_TOP_MERGE = 40;
const int LENGTH_OF_RIGHT_DELTA = 100;
const int PANEL_WIDTH = 100;
const int PANEL_HEIGHT = 100;
const int PANEL_COLUMN_SKIP = 1;
const int PANEL_ROW_SKIP = 1;
const int PANEL_SIZE_STEP = 5;

// CBitmapImagesDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CBitmapImagesDialog, CDialog)
CBitmapImagesDialog::CBitmapImagesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapImagesDialog::IDD, pParent)
    , clutNum(0)
{
}

CBitmapImagesDialog::~CBitmapImagesDialog()
{
}

void CBitmapImagesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, clutNum);
    DDX_Control(pDX, IDC_COMBO1, clutCmb);
    DDX_Control(pDX, IDC_SLIDER1, scrollSlider);
}


BEGIN_MESSAGE_MAP(CBitmapImagesDialog, CDialog)
    ON_WM_PAINT()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBitmapImagesDialog::OnNMCustomdrawSlider1)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CBitmapImagesDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CBitmapImagesDialog ���b�Z�[�W �n���h��

BOOL CBitmapImagesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CBitmapImagesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    zoom = 0;
    offset = 0;
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CBitmapImagesDialog::setupDialog()
{
    int collectionIndex = ((CBitmapsDialog*)parent)->collection;

    if(theApp.isShapesLoaded){
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
    }
    UpdateData();
    Invalidate(FALSE);
}


void CBitmapImagesDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B

    CRect panelRect;
    this->GetWindowRect(&panelRect);

    CRect imageRect = panelRect;
    dc.SelectObject(GetStockObject(LTGRAY_BRUSH));
    imageRect.left = 0;
    imageRect.top = LENGTH_OF_TOP_MERGE;
    imageRect.right = imageRect.left + imageRect.Width() - LENGTH_OF_RIGHT_DELTA;
    imageRect.bottom = imageRect.top + imageRect.Height() - LENGTH_OF_TOP_MERGE;
    dc.Rectangle(&imageRect);

    SDLToWindows *sdlToWin = new SDLToWindows(this->m_hWnd, imageRect);
    screenSurface = sdlToWin->getSurface();
    if(theApp.isShapesLoaded){
        int collectionIndex = ((CBitmapsDialog*)parent)->collection;

        int clut = clutCmb.GetCurSel();

        struct collection_header* header = get_collection_header(collectionIndex);

        //get number of bitmaps
        int bitmapNum = header->collection->bitmap_count;

        int width = PANEL_WIDTH + PANEL_SIZE_STEP * zoom;
        int holizontalPanelNum = panelRect.Width() / 
            (width + PANEL_COLUMN_SKIP);
        int height = PANEL_HEIGHT + PANEL_SIZE_STEP * zoom;

        SDL_Color palette[256];

        for(int i = 0; i < bitmapNum; i ++){
            int left = (i % holizontalPanelNum) *
                (width + PANEL_COLUMN_SKIP);
            int top = LENGTH_OF_TOP_MERGE +
                (i / holizontalPanelNum) * 
                (height + PANEL_ROW_SKIP);
            CRect destRect(left, top, left + width, top + height);

            //get shape surface
            int collection = BUILD_COLLECTION(collectionIndex, clut);
            int shapes = BUILD_DESCRIPTOR(collection, i);
            int excol = NONE;
            float illumination = 1.0f;
            byte **outp = (byte**)malloc(sizeof(byte*));
            
            SDL_Surface *surface = get_shape_surface(shapes, excol, outp,
                illumination, false, palette);

            drawSurfaceByPalette(&dc, surface, palette, destRect);

            free(outp);
            SDL_FreeSurface(surface);
        }
    }
    delete sdlToWin;
}

void CBitmapImagesDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    int sel = clutCmb.GetCurSel();
    clutNum = sel;
    Invalidate(FALSE);
    UpdateData();
}
