// MapEditorOneDoc.h : CMapEditorOneDoc クラスのインターフェイス
//


#pragma once

class CMapEditorOneDoc : public CDocument
{
protected: // シリアル化からのみ作成します。
	CMapEditorOneDoc();
	DECLARE_DYNCREATE(CMapEditorOneDoc)

// 属性
public:

// 操作
public:

// オーバーライド
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 実装
public:
	virtual ~CMapEditorOneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
};


