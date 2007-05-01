// MapEditorOneDoc.cpp : CMapEditorOneDoc クラスの実装
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


// CMapEditorOneDoc コンストラクション/デストラクション

CMapEditorOneDoc::CMapEditorOneDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CMapEditorOneDoc::~CMapEditorOneDoc()
{
}

BOOL CMapEditorOneDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CMapEditorOneDoc シリアル化

void CMapEditorOneDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 格納するコードをここに追加してください。
	}
	else
	{
		// TODO: 読み込むコードをここに追加してください。
	}
}


// CMapEditorOneDoc 診断

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


// CMapEditorOneDoc コマンド
