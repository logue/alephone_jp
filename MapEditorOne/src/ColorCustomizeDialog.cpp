// ColorCustomizeDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ColorCustomizeDialog.h"


// CColorCustomizeDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CColorCustomizeDialog, CDialog)

CColorCustomizeDialog::CColorCustomizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CColorCustomizeDialog::IDD, pParent)
{
    memset(&colorSetting, 0, sizeof(ColorSettings));
}

CColorCustomizeDialog::~CColorCustomizeDialog()
{
}

void CColorCustomizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CColorCustomizeDialog, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CColorCustomizeDialog ���b�Z�[�W �n���h��

void CColorCustomizeDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B

    //draw color samples
    int items[] = {
        IDC_PICT_BACKGROUND,
        IDC_PICT_GRID_LINE,
        IDC_PICT_LINES,
        IDC_PICT_POLYGONS,
        IDC_PICT_STRINGS,
        IDC_PICT_POINTS
    };
    COLORREF colors[] ={
        colorSetting.background,
        colorSetting.gridLine,
        colorSetting.lines,
        colorSetting.polygons,
        colorSetting.strings,
        colorSetting.points
    };

    for(int i = 0; i < 6; i ++){
        CBrush brush;
        brush.CreateSolidBrush(colors[i]);

        CWnd *frame = GetDlgItem(IDC_PICT_BACKGROUND);
        CRect rect;
        frame->GetClientRect(&rect);
        CDC *dc = frame->GetDC();
        
        dc->SelectObject(brush);
        dc->Rectangle(&rect);

        brush.DeleteObject();
    }
}
