// MapEditorOneDoc.cpp : CMapEditorOneDoc �N���X�̎���
//

#include "stdafx.h"
#include "MapEditorOne.h"

#include "MapEditorOneDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorOneDoc

IMPLEMENT_DYNCREATE(CMapEditorOneDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditorOneDoc, CDocument)
END_MESSAGE_MAP()


// CMapEditorOneDoc �R���X�g���N�V����/�f�X�g���N�V����

CMapEditorOneDoc::CMapEditorOneDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CMapEditorOneDoc::~CMapEditorOneDoc()
{
}

BOOL CMapEditorOneDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}




// CMapEditorOneDoc �V���A����

void CMapEditorOneDoc::Serialize(CArchive& ar)
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


// CMapEditorOneDoc �f�f

#ifdef _DEBUG
void CMapEditorOneDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditorOneDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMapEditorOneDoc �R�}���h
