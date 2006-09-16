// MapEditorSDIView.h : CMapEditorSDIView �N���X�̃C���^�[�t�F�C�X
//


#pragma once


class CMapEditorSDIView : public CView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CMapEditorSDIView();
	DECLARE_DYNCREATE(CMapEditorSDIView)

// ����
public:
	CMapEditorSDIDoc* GetDocument() const;

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
    void addZoom(int step);
    void createDoubleBuffer();

// ����
public:
	virtual ~CMapEditorSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnFileOpen();
    afx_msg void OnFileSave();
    afx_msg void On32776();
public:
    afx_msg void OnZoomIn();
public:
    afx_msg void OnZoomOut();
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
    afx_msg void OnItemCentering();
public:
    afx_msg void OnItemZoomDefault();
public:
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
    afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
    virtual void OnInitialUpdate();
public:
    afx_msg void On32784();
public:
    afx_msg void On32787();
public:
    afx_msg void On32789();
public:
    afx_msg void On32786();
public:
    afx_msg void On32790();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
    afx_msg void OnFileNew();
};

#ifndef _DEBUG  // MapEditorSDIView.cpp �̃f�o�b�O �o�[�W����
inline CMapEditorSDIDoc* CMapEditorSDIView::GetDocument() const
   { return reinterpret_cast<CMapEditorSDIDoc*>(m_pDocument); }
#endif

