// MapEditorOneView.cpp : CMapEditorOneView クラスの実装
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
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMapEditorOneView コンストラクション/デストラクション

CMapEditorOneView::CMapEditorOneView()
{
	// TODO: 構築コードをここに追加します。

}

CMapEditorOneView::~CMapEditorOneView()
{
}

BOOL CMapEditorOneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CMapEditorOneView 描画

void CMapEditorOneView::OnDraw(CDC* /*pDC*/)
{
	CMapEditorOneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CMapEditorOneView 印刷

BOOL CMapEditorOneView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// デフォルトの印刷準備
	return DoPreparePrinting(pInfo);
}

void CMapEditorOneView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMapEditorOneView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}


// CMapEditorOneView 診断

#ifdef _DEBUG
void CMapEditorOneView::AssertValid() const
{
	CView::AssertValid();
}

void CMapEditorOneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditorOneDoc* CMapEditorOneView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditorOneDoc)));
	return (CMapEditorOneDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditorOneView メッセージ ハンドラ
