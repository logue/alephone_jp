// AnnotationDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "AnnotationDialog.h"


// CAnnotationDialog �_�C�A���O

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


// CAnnotationDialog ���b�Z�[�W �n���h��

void CAnnotationDialog::OnEnChangeEdit1()
{
    // TODO:  ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A
    // �܂��ACDialog::OnInitDialog() �֐����I�[�o�[���C�h���āAOR ��Ԃ� ENM_CHANGE
    // �t���O���}�X�N�ɓ���āACRichEditCtrl().SetEventMask() ���Ăяo���Ȃ�����A
    // �R���g���[���́A���̒ʒm�𑗐M���܂���B

    // TODO:  �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����Ă��������B
    if(annotationText.GetLength() > MAXIMUM_ANNOTATION_TEXT_LENGTH){
        AfxMessageBox(L"text's length must be under 64");
        annotationText = annotationText.Mid(0,MAXIMUM_ANNOTATION_TEXT_LENGTH);
    }
}
