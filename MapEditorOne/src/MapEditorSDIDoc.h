// MapEditorSDIDoc.h : CMapEditorSDIDoc �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CMapEditorSDIDoc : public CDocument
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CMapEditorSDIDoc();
	DECLARE_DYNCREATE(CMapEditorSDIDoc)

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CMapEditorSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
};


