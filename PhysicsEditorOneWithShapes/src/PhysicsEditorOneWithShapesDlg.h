// PhysicsEditorOneWithShapesDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// CPhysicsEditorOneWithShapesDlg �_�C�A���O
class CPhysicsEditorOneWithShapesDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CPhysicsEditorOneWithShapesDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PHYSICSEDITORONEWITHSHAPES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
