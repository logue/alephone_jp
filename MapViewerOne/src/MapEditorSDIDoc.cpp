// MapEditorSDIDoc.cpp : CMapEditorSDIDoc �N���X�̎���
//

#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorSDIDoc

IMPLEMENT_DYNCREATE(CMapEditorSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditorSDIDoc, CDocument)
END_MESSAGE_MAP()


// CMapEditorSDIDoc �R���X�g���N�V����/�f�X�g���N�V����

CMapEditorSDIDoc::CMapEditorSDIDoc()
{
	// TODO: ���̈ʒu�� 1 �x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CMapEditorSDIDoc::~CMapEditorSDIDoc()
{
}

BOOL CMapEditorSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CMapEditorSDIDoc �V���A����

void CMapEditorSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �i�[����R�[�h�������ɒǉ����Ă��������B
	}
	else
	{
		// TODO: �ǂݍ��ރR�[�h�������ɒǉ����Ă��������B
	}
}


// CMapEditorSDIDoc �f�f

#ifdef _DEBUG
void CMapEditorSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditorSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMapEditorSDIDoc �R�}���h
