// ToolDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ToolDialog.h"
#include ".\tooldialog.h"


const int NUMBER_OF_TOOL_BAR_ICON_FILES = 8;

// CToolDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CToolDialog, CDialog)
CToolDialog::CToolDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CToolDialog::IDD, pParent)
{
    //imageList.Create(TOOL_WIDTH, TOOL_HEIGHT, ILC_COLOR32, NUMBER_OF_TOOLS * 2, 2);

    char *TOOL_BAR_ICONS_DIR_NAMR = "Toolbar/";
    char *SELECTED_ICONS_DIR_NAME = "Selected/";
    char *TOOL_BAR_ICONS_IMAGE_LIST_FILE_NAME = "ToolBarImageList.txt";

    //�C���[�W�����X�g�ǂݍ���
    Information imageNameInformations[NUMBER_OF_TOOL_BAR_ICON_FILES];
    CString listPath = CString(DATA_DIR_NAME) +
        CString(TOOL_BAR_ICONS_IMAGE_LIST_FILE_NAME);
    char cstr[256];
    strToChar(listPath, cstr);
    loadInformations(cstr, NUMBER_OF_TOOL_BAR_ICON_FILES,
        imageNameInformations);
    /*
    //�A�C�R���ǂݍ���
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
    for(int i = 0; i < NUMBER_OF_TOOLS * 2; i ++){
        //loadBitmap(assignment[i], &imageList, RGB(255,0,0));
        CString path = CString(DATA_DIR_NAME) + CString(TOOL_BAR_ICONS_DIR_NAMR);
        if(i >= NUMBER_OF_TOOLS){
            path += CString(SELECTED_ICONS_DIR_NAME);
        }
        path += imageNameInformations[i % NUMBER_OF_TOOLS].jname;
        strToChar(path, cstr);
        CBitmap *bmp = loadBitmapFromFile(cstr);
        
        //CBitmap* bmp = new CBitmap();
        //bmp->LoadBitmap(assignment[i]);
        bitmaps.push_back(bmp);
    }
}

CToolDialog::~CToolDialog()
{
    //imageList.DeleteImageList();
    vector<CBitmap*>::iterator it;
    for(it = bitmaps.begin(); it != bitmaps.end(); it ++){
        (*it)->DeleteObject();
        delete (*it);
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


// CToolDialog ���b�Z�[�W �n���h��

BOOL CToolDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CToolDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CToolDialog::PostNcDestroy()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CToolDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CToolDialog::DestroyWindow()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    theApp.isToolDialogShow = FALSE;
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

BOOL CToolDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CToolDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
    // �`�惁�b�Z�[�W�� CDialog::OnPaint() ���Ăяo���Ȃ��ł��������B
    //draw tools
    CDC memDC;
    memDC.CreateCompatibleDC(&dc);
    CBitmap* old = memDC.SelectObject(bitmaps[0]);
    for(int i = 0; i < NUMBER_OF_TOOLS; i ++){
        POINT pt;

        pt.x = (i % 2) * TOOL_WIDTH;
        pt.y = (i / 2) * TOOL_HEIGHT;

        //imageList.Draw(&dc, i, pt, SRCCOPY);
        int index = i;
        if(theApp.selectingToolType == i){
            index += NUMBER_OF_TOOLS;
        }
        CBitmap* bmp = bitmaps[index];
        BITMAP bmpInfo;
        bmp->GetBitmap(&bmpInfo);
        memDC.SelectObject(bmp);
        dc.BitBlt(pt.x, pt.y, TOOL_WIDTH, TOOL_HEIGHT, &memDC,
            0, 0, SRCCOPY);

    }
    memDC.SelectObject(old);
    memDC.DeleteDC();
}

//click dialog to select tool
void CToolDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    for(int i = 0; i < NUMBER_OF_TOOLS; i ++){
        CRect rect;
        rect.left = (i % 2) * TOOL_WIDTH;
        rect.top = (i / 2) * TOOL_HEIGHT;
        rect.right = rect.left + TOOL_WIDTH;
        rect.bottom = rect.top + TOOL_HEIGHT;
        if(isPointInRect<int>(point.x, point.y,
            rect.left, rect.top, rect.right, rect.bottom))
        {
            //�c�[���ω�
            theApp.selectingToolType = i;
            if(i == TI_SKULL && !theApp.isObjectPropertyDialogShow){
                //show object property's dialog
                theApp.isObjectPropertyDialogShow = TRUE;
                theApp.objectPropertyDialog->ShowWindow(TRUE);
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

    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
}
