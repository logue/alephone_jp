// MapEditorOneDoc.h : CMapEditorOneDoc �N���X�̃C���^�[�t�F�C�X
//


#pragma once

class CMapEditorOneDoc : public CDocument
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CMapEditorOneDoc();
	DECLARE_DYNCREATE(CMapEditorOneDoc)

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
	virtual ~CMapEditorOneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
};


