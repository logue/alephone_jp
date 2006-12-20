// BitmapCLUTDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapCLUTDialog.h"

const int NUMBER_OF_ROW_PALETTE_ELEMENTS = 32;
const int LENGTH_OF_PALETTE_ROW_SKIP = 20;
const int LENGTH_OF_ELEMENT_COLUMN_SKIP = 1;
const int LENGTH_OF_ELEMENT_ROW_SKIP = 1;
const int ELEMENT_WIDTH = 10;
const int ELEMENT_HEIGHT = 10;

// CBitmapCLUTDialog �_�C�A���O

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
    DDX_Control(pDX, IDC_SLIDER1, scrollSlider);
}


BEGIN_MESSAGE_MAP(CBitmapCLUTDialog, CDialog)
    ON_WM_PAINT()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBitmapCLUTDialog::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CBitmapCLUTDialog ���b�Z�[�W �n���h��

BOOL CBitmapCLUTDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CBitmapCLUTDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

//paint field
void CBitmapCLUTDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B

    CRect frameRect;
    this->GetWindowRect(&frameRect);

    frameRect.left = frameRect.top = 0;
    dc.SelectObject(GetStockObject(LTGRAY_BRUSH));
    dc.Rectangle(&frameRect);
    if(theApp.isShapesLoaded){
        int collectionIndex = theApp.collection;
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
                top -= offset;
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
    scrollSlider.SetRangeMin(0);
    
    if(theApp.isShapesLoaded){
        int collectionIndex = theApp.collection;
        struct collection_header* header = get_collection_header(collectionIndex);
        int clutNum = header->collection->clut_count;
        //max
        int max = 0;
        for(int i = 0; i < clutNum; i ++){
            int numColors = 0;
            struct rgb_color_value* palette = get_collection_colors(collectionIndex, i, numColors);
            max += LENGTH_OF_PALETTE_ROW_SKIP +
                        (numColors / NUMBER_OF_ROW_PALETTE_ELEMENTS + 1) *
                        (ELEMENT_HEIGHT + LENGTH_OF_ELEMENT_ROW_SKIP);
        }
        scrollSlider.SetRangeMax(max);
        scrollSlider.SetPos(0);
    }
    Invalidate(FALSE);
}

void CBitmapCLUTDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
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