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
    void drawBackground(CDC *cdc);
    void drawGrid(CDC *cdc);
    void drawPolygons(CDC *cdc);
    void drawLines(CDC *cdc);
    void drawPoints(CDC *cdc);
    void drawObjects(CDC *cdc);
    void drawStrings(CDC *cdc);

	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    void addZoom(int step);
    void createDoubleBuffer();
    void moveMapOffset(int newPx, int newPy);
    void setStartPointForSelectGroup(int px, int py);
// 実装
public:
	virtual ~CMapEditorSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


public:
    void changeMode(int mode);
    void doLButtonDownDrawMode(UINT nFlags, CPoint &point);
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
public:
    afx_msg void On32796();
    afx_msg void On32788();
public:
    afx_msg void OnMenu32797();
public:
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
public:
    afx_msg void On32795();
public:
    afx_msg void OnHeightFloor();
public:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
    afx_msg void OnModePolygontype();
public:
    afx_msg void On32808();
};

#ifndef _DEBUG  // MapEditorSDIView.cpp のデバッグ バージョン
inline CMapEditorSDIDoc* CMapEditorSDIView::GetDocument() const
   { return reinterpret_cast<CMapEditorSDIDoc*>(m_pDocument); }
#endif

