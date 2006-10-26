// AnnotationDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "AnnotationDialog.h"


// CAnnotationDialog ダイアログ

IMPLEMENT_DYNAMIC(CAnnotationDialog, CDialog)

CAnnotationDialog::CAnnotationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAnnotationDialog::IDD, pParent)
    , annotationText(_T(""))
    , isOnlyDisplayWhenPolygonShown(FALSE)
{
    isOnlyDisplayWhenPolygonShown = false;
    
}

CAnnotationDialog::~CAnnotationDialog()
{
}

void CAnnotationDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, annotationText);
    DDX_Check(pDX, IDC_CHECK1, isOnlyDisplayWhenPolygonShown);
}


BEGIN_MESSAGE_MAP(CAnnotationDialog, CDialog)
    ON_EN_CHANGE(IDC_EDIT1, &CAnnotationDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CAnnotationDialog メッセージ ハンドラ

void CAnnotationDialog::OnEnChangeEdit1()
{
    // TODO:  これが RICHEDIT コントロールの場合、
    // まず、CDialog::OnInitDialog() 関数をオーバーライドして、OR 状態の ENM_CHANGE
    // フラグをマスクに入れて、CRichEditCtrl().SetEventMask() を呼び出さない限り、
    // コントロールは、この通知を送信しません。

    // TODO:  ここにコントロール通知ハンドラ コードを追加してください。
    if(annotationText.GetLength() > MAXIMUM_ANNOTATION_TEXT_LENGTH){
        AfxMessageBox(L"text's length must be under 64");
        annotationText = annotationText.Mid(0,MAXIMUM_ANNOTATION_TEXT_LENGTH);
    }
}
