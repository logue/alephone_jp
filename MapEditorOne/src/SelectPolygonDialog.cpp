// SelectPolygonDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "SelectPolygonDialog.h"


// CSelectPolygonDialog �_�C�A���O

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


// CSelectPolygonDialog ���b�Z�[�W �n���h��

void CSelectPolygonDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B
}

BOOL CSelectPolygonDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
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
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CSelectPolygonDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    
    CDialog::OnLButtonDown(nFlags, point);
}

void CSelectPolygonDialog::OnBnClickedButton1()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    pointsOfPolygon = 3;
    DestroyWindow();
}

void CSelectPolygonDialog::OnBnClickedButton2()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    pointsOfPolygon = 4;
    DestroyWindow();
}
void CSelectPolygonDialog::OnBnClickedButton3()
{
    // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
