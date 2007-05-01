// MapEditorOneView.h : CMapEditorOneView �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CMapEditorOneView : public CView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CMapEditorOneView();
	DECLARE_DYNCREATE(CMapEditorOneView)

// ����
public:
	CMapEditorOneDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����
public:
	virtual ~CMapEditorOneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MapEditorOneView.cpp �̃f�o�b�O �o�[�W����
inline CMapEditorOneDoc* CMapEditorOneView::GetDocument() const
   { return reinterpret_cast<CMapEditorOneDoc*>(m_pDocument); }
#endif

