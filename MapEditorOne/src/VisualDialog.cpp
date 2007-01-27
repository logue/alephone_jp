// VisualDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "VisualDialog.h"
static unsigned char** outPointerToPixelData;
SDL_Color pallet[256];
HPALETTE hPalette;

// CVisualDialog ダイアログ

IMPLEMENT_DYNAMIC(CVisualDialog, CDialog)

CVisualDialog::CVisualDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CVisualDialog::IDD, pParent)
{
    m_SDLToWindows = NULL;
    testImage = NULL;
    outPointerToPixelData = (unsigned char**)malloc(sizeof(unsigned char*) * 1);
}

CVisualDialog::~CVisualDialog()
{
    DeleteObject(hPalette);
    free(outPointerToPixelData);
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


// CVisualDialog メッセージ ハンドラ

void CVisualDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: ここにメッセージ ハンドラ コードを追加します。
    // 描画メッセージで CDialog::OnPaint() を呼び出さないでください。

    /*
    if(testImage){
        /*
        dc.SelectPalette( CPalette::FromHandle(hPalette), TRUE);
        dc.RealizePalette();
        SDL_LockSurface(testImage);
        int bpp = testImage->format->BytesPerPixel;
        for(int y = 0; y < testImage->h; y ++){
            for(int x = 0; x < testImage->w; x ++){
                Uint32 pix = getpixel(testImage, x, y);
                dc.SetPixel(x,y, RGB(pallet[pix].r, pallet[pix].g, pallet[pix].b));
            }//logger.printf("\n");
        }
        SDL_UnlockSurface(testImage);
        //AfxMessageBox(L"stop");
        //exit(1);
        *
        
        SDL_Surface* screen = m_SDLToWindows->getSurface();
        //drawing!
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));

        SDL_LockSurface(testImage);
        SDL_LockSurface(screen);
        //SDL_Rect r = {0,0,testImage->w, testImage->h};
        //SDL_BlitSurface(testImage, &r, screen, &r);
        for(int y = 0; y < testImage->h; y ++){
            for(int x = 0; x < testImage->w; x ++){
                Uint32 pix = hpl::surface::getpixel(testImage, x, y);
                hpl::surface::putpixel(screen, x, y, SDL_MapRGB(screen->format,
                    pallet[pix].r, pallet[pix].g, pallet[pix].b));
                //dc.SetPixel(x,y, RGB(pallet[pix].r, pallet[pix].g, pallet[pix].b));
            }//logger.printf("\n");
        }
       SDL_UnlockSurface(screen);
        SDL_UnlockSurface(testImage);

        m_SDLToWindows->paint();
        
        //Invalidate(FALSE);
    }*/

    //copy surface to GDI
    CWnd *pictBox = GetDlgItem(IDC_PICTURE);
    
    CRect pictRect;
    pictBox->GetClientRect(&pictRect);
    CDC *pictDC = pictBox->GetDC();
    
    render_screen(0);

    m_SDLToWindows->paint();
    Invalidate(FALSE);
    /*
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

    // TODO:  ここに初期化を追加してください
    CRect cl_rect;
    CWnd *pictBox = GetDlgItem(IDC_PICTURE);
    
    pictBox->GetWindowRect(&cl_rect);
    m_SDLToWindows=new SDLToWindows(pictBox->m_hWnd, cl_rect);
    screenSurface = m_SDLToWindows->getSurface();
    main_surface = m_SDLToWindows->getSurface();


    //screenSurface = SDL_SetVideoMode(640,480, 8, SDL_SWSURFACE);
    
    /*
    int clut = 0;
    int collection = BUILD_COLLECTION(11, clut);
    shape_descriptor shape = BUILD_DESCRIPTOR(collection, 1);
    SDL_Surface *s = get_shape_surface(shape, NONE, outPointerToPixelData,
        0.9f, false, pallet);

    if(s){
        testImage = s;//SDL_DisplayFormat(s);
        //SDL_FreeSurface(s);
    }else{
        testImage = NULL;
        AfxMessageBox(L"couldn't load surface");
        return FALSE;
    }

    int entries = 256;
	LOGPALETTE *lpPalette = (LOGPALETTE *)malloc(sizeof (LOGPALETTE) + (entries-1) * sizeof (PALETTEENTRY));
	lpPalette->palVersion = 0x0300;
	lpPalette->palNumEntries = entries;

	for (int count = 0 ; count < entries ; count++) {
		lpPalette->palPalEntry[count].peRed = pallet[count].r;
		lpPalette->palPalEntry[count].peGreen = pallet[count].g;
		lpPalette->palPalEntry[count].peBlue = pallet[count].b;
		lpPalette->palPalEntry[count].peFlags = NULL;
	}
	hPalette = CreatePalette(lpPalette);
	free(lpPalette);
    */
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
