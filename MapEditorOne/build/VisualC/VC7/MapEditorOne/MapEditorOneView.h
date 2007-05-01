// MapEditorOneView.h : CMapEditorOneView クラスのインターフェイス
//


#pragma once


class CMapEditorOneView : public CView
{
protected: // シリアル化からのみ作成します。
	CMapEditorOneView();
	DECLARE_DYNCREATE(CMapEditorOneView)

// 属性
public:
	CMapEditorOneDoc* GetDocument() const;

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

// 実装
public:
	virtual ~CMapEditorOneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MapEditorOneView.cpp のデバッグ バージョン
inline CMapEditorOneDoc* CMapEditorOneView::GetDocument() const
   { return reinterpret_cast<CMapEditorOneDoc*>(m_pDocument); }
#endif

