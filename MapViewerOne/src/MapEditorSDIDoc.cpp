// MapEditorSDIDoc.cpp : CMapEditorSDIDoc クラスの実装
//

#include "stdafx.h"
#include "MapEditorSDI.h"

#include "MapEditorSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorSDIDoc

IMPLEMENT_DYNCREATE(CMapEditorSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditorSDIDoc, CDocument)
END_MESSAGE_MAP()


// CMapEditorSDIDoc コンストラクション/デストラクション

CMapEditorSDIDoc::CMapEditorSDIDoc()
{
	// TODO: この位置に 1 度だけ呼ばれる構築用のコードを追加してください。

}

CMapEditorSDIDoc::~CMapEditorSDIDoc()
{
}

BOOL CMapEditorSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}




// CMapEditorSDIDoc シリアル化

void CMapEditorSDIDoc::Serialize(CArchive& ar)
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


// CMapEditorSDIDoc 診断

#ifdef _DEBUG
void CMapEditorSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditorSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMapEditorSDIDoc コマンド
