// MapEditorSDIView.h : CMapEditorSDIView クラスのインターフェイス
//


#pragma once


class CMapEditorSDIView : public CView
{
protected: // シリアル化からのみ作成します。
	CMapEditorSDIView();
	DECLARE_DYNCREATE(CMapEditorSDIView)

// 属性
public:
	CMapEditorSDIDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    void addZoom(int step);
    void createDoubleBuffer();

// 実装
public:
	virtual ~CMapEditorSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:

// 生成された、メッセージ割り当て関数
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

#ifndef _DEBUG  // MapEditorSDIView.cpp のデバッグ バージョン
inline CMapEditorSDIDoc* CMapEditorSDIView::GetDocument() const
   { return reinterpret_cast<CMapEditorSDIDoc*>(m_pDocument); }
#endif

