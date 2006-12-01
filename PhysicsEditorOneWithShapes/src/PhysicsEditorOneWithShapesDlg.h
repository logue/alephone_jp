// PhysicsEditorOneWithShapesDlg.h : ヘッダー ファイル
//

#pragma once


// CPhysicsEditorOneWithShapesDlg ダイアログ
class CPhysicsEditorOneWithShapesDlg : public CDialog
{
// コンストラクション
public:
	CPhysicsEditorOneWithShapesDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_PHYSICSEDITORONEWITHSHAPES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
