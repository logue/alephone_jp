// MapEditorOneView.cpp : CMapEditorOneView �N���X�̎���
//

#include "stdafx.h"
#include "MapEditorOne.h"

#include "MapEditorOneDoc.h"
#include "MapEditorOneView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorOneView

IMPLEMENT_DYNCREATE(CMapEditorOneView, CView)

BEGIN_MESSAGE_MAP(CMapEditorOneView, CView)
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMapEditorOneView �R���X�g���N�V����/�f�X�g���N�V����

CMapEditorOneView::CMapEditorOneView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CMapEditorOneView::~CMapEditorOneView()
{
}

BOOL CMapEditorOneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CMapEditorOneView �`��

void CMapEditorOneView::OnDraw(CDC* /*pDC*/)
{
	CMapEditorOneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}


// CMapEditorOneView ���

BOOL CMapEditorOneView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CMapEditorOneView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CMapEditorOneView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}


// CMapEditorOneView �f�f

#ifdef _DEBUG
void CMapEditorOneView::AssertValid() const
{
	CView::AssertValid();
}

void CMapEditorOneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditorOneDoc* CMapEditorOneView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorOneDoc)));
	return (CMapEditorOneDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditorOneView ���b�Z�[�W �n���h��
