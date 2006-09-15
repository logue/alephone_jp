// PhysicsEditorDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "PhysicsEditorDlg.h"
#include "extensions.h"
#include "FileHandler.h"
#include "effect_definitions.h"
#include "item_definitions.h"
#include "monster_definitions.h"
//#include "monsters.h"

#include "projectile_definitions.h"
#include "weapon_definitions.h"

#include "SaveCheckDialog.h"

/** prototype ****/
static void importPhysicsFile(char *filename);

/** local global ****/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPhysicsEditorDlg �_�C�A���O

/**
    ��������̐ݒ�f�[�^��W���̂��̂ɒ����܂�
*/
static void setDefinitionsToDefault(){
    //�����X�^�[���
    memcpy(monster_definitions, theApp.monster_default_definitions, sizeof(struct monster_definition) * NUMBER_OF_MONSTER_TYPES);
    memcpy(effect_definitions, theApp.effect_default_definitions, sizeof(struct effect_definition) * NUMBER_OF_EFFECT_TYPES);
    memcpy(projectile_definitions, theApp.projectile_default_definitions, sizeof(struct projectile_definition) * NUMBER_OF_PROJECTILE_TYPES);
    memcpy(physics_models, theApp.physics_default_models, sizeof(struct physics_constants) * NUMBER_OF_PHYSICS_MODELS);
    memcpy(weapon_definitions, theApp.weapon_default_definitions, sizeof(struct weapon_definition) * MAXIMUM_NUMBER_OF_WEAPONS);
}


CPhysicsEditorDlg::CPhysicsEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhysicsEditorDlg::IDD, pParent)
	, physicsFileNameField(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhysicsEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, physicsFileNameField);
	DDX_Control(pDX, IDC_EDIT1, physicsFileName);
	DDX_Control(pDX, IDC_TAB1, phyTabPane);
}

BEGIN_MESSAGE_MAP(CPhysicsEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_OPEN32772, &CPhysicsEditorDlg::OnFileOpenPhysics)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPhysicsEditorDlg::OnTcnSelchangeTab1)
	ON_COMMAND(ID_FILE_EXIT32774, &CPhysicsEditorDlg::OnFileExit32774)
	ON_COMMAND(ID_FILE_NEW32771, &CPhysicsEditorDlg::OnFileNew32771)
	ON_COMMAND(ID_FILE_SAVE, &CPhysicsEditorDlg::OnFileSave)
    ON_WM_DESTROY()
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPhysicsEditorDlg ���b�Z�[�W �n���h��

BOOL CPhysicsEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
/*
    this->accel = LoadAccelerators(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDR_ACCELERATOR1));
*/

    //���ݑI�𒆂̃����X�^�[
    theApp.editMonsterTypeId = 0;
    theApp.editEffectTypeId = 0;
    theApp.editPhysicsTypeId = 0;
    theApp.editProjectileTypeId = 0;
    theApp.editWeaponTypeId = 0;

	CRect r, org;
	this->phyTabPane.GetClientRect(r);
	org = r;
	r.OffsetRect(18,70);
	r.right = r.left + org.Width() - 20;
	r.bottom = r.top + org.Height() - 40;
	this->monsterPage.Create(CMonsterPage::IDD, this);
	this->monsterPage.MoveWindow(&r, TRUE);
	this->monsterPage.ShowWindow(SW_SHOW);
	this->monsterPage2.Create(CMonsterPage2::IDD, this);
	this->monsterPage2.MoveWindow(&r, TRUE);
	this->monsterPage2.ShowWindow(SW_HIDE);
	this->monsterPage3.Create(CMonsterPage3::IDD, this);
	this->monsterPage3.MoveWindow(&r, TRUE);
	this->monsterPage3.ShowWindow(SW_HIDE);
	this->monsterPage4.Create(CMonsterPage4::IDD, this);
	this->monsterPage4.MoveWindow(&r, TRUE);
	this->monsterPage4.ShowWindow(SW_HIDE);
	this->effectPage.Create(CEffectPage::IDD, this);
	this->effectPage.MoveWindow(&r, TRUE);
	this->effectPage.ShowWindow(SW_HIDE);
    this->projectilePage.Create(CProjectilePage::IDD, this);
	this->projectilePage.MoveWindow(&r, TRUE);
	this->projectilePage.ShowWindow(SW_HIDE);
    this->physicsPage.Create(CPhysicsPage::IDD, this);
	this->physicsPage.MoveWindow(&r, TRUE);
	this->physicsPage.ShowWindow(SW_HIDE);
    this->weaponPage.Create(CWeaponPage::IDD, this);
	this->weaponPage.MoveWindow(&r, TRUE);
	this->weaponPage.ShowWindow(SW_HIDE);
    this->weaponPage2.Create(CWeaponPage2::IDD, this);
	this->weaponPage2.MoveWindow(&r, TRUE);
	this->weaponPage2.ShowWindow(SW_HIDE);
	
	TC_ITEMW monsterPane;
	monsterPane.mask = TCIF_TEXT;
	monsterPane.pszText = L"Monsters1(Physics)";
	phyTabPane.InsertItem( 0, &monsterPane);
	TC_ITEMW monsterPane2;
	monsterPane2.mask = TCIF_TEXT;
	monsterPane2.pszText = L"Monsters2(Flags)";
	phyTabPane.InsertItem( 1, &monsterPane2);
	TC_ITEMW monsterPane3;
	monsterPane3.mask = TCIF_TEXT;
	monsterPane3.pszText = L"Monsters3(Sequences)";
	phyTabPane.InsertItem( 2, &monsterPane3);
	TC_ITEMW monsterPane4;
	monsterPane4.mask = TCIF_TEXT;
	monsterPane4.pszText = L"Monsters4(Attack)";
	phyTabPane.InsertItem( 3, &monsterPane4);
	TC_ITEMW effectPane;
	effectPane.mask = TCIF_TEXT;
	effectPane.pszText = L"Effects";
	phyTabPane.InsertItem( 4, &effectPane);
	TC_ITEMW projectilePane;
	projectilePane.mask = TCIF_TEXT;
	projectilePane.pszText = L"Projectiles";
	phyTabPane.InsertItem( 5, &projectilePane);
	TC_ITEMW physicsPane;
	physicsPane.mask = TCIF_TEXT;
	physicsPane.pszText = L"Physics";
	phyTabPane.InsertItem( 6, &physicsPane);
	TC_ITEMW weaponPane;
	weaponPane.mask = TCIF_TEXT;
	weaponPane.pszText = L"Weapons1(Appearance)";
	phyTabPane.InsertItem( 7, &weaponPane);
	TC_ITEMW weaponPane2;
	weaponPane2.mask = TCIF_TEXT;
	weaponPane2.pszText = L"Weapons2(Triggers)";
	phyTabPane.InsertItem( 8, &weaponPane2);

	//��{�t�@�C����ǂݍ���
	importPhysicsFile(DEFAULT_PHYSICS_FILE_NAME);
    setDefinitionsToDefault();
    
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CPhysicsEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CPhysicsEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CPhysicsEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**
    CString��char*�ɕϊ����܂�
*/
void strToChar(CString src, char* dest){
    LPWSTR buf = new WCHAR[src.GetLength()];
    LPBOOL ok = new BOOL[1];
	lstrcpy(buf, src);
    wcharToChar(buf, dest);
}

/**
    WCHAR*��char*�ɕϊ����܂��B
*/
void wcharToChar(WCHAR* src, char* dest){
    DWORD len = WideCharToMultiByte(CP_ACP, 0,
        src, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0,
        src, -1, dest, len, NULL, NULL);
}

/**
    char*��WCHAR*�ɕϊ����܂�
*/
void charToWChar(char* src, WCHAR* dest){
    DWORD len = MultiByteToWideChar(CP_ACP, 0,
        src, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP,0,
        src, -1, dest, len);
}

void CPhysicsEditorDlg::OnFileOpenPhysics()
{
	//�t�@�C���I�[�v���_�C�A���O�\��
	CFileDialog dlg(TRUE, L"*.*", L"hoge", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PhysicsFile (*.*)|*.*||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

        //�ǂݍ���
        char str[256];
        strToChar(filename, str);
        importPhysicsFile(str);

        //�_�C�A���O�X�V
        setupDialogs();
	}
}

/**
    �����t�@�C����ǂݍ��݂܂�
*/
void CPhysicsEditorDlg::importPhysicsFile(const char *filename){
	//�����t�@�C�����ݒ�
	FileSpecifier phy = FileSpecifier(filename);
	set_physics_file(phy);
    //�ǂݍ���
	import_definition_structures();


    WCHAR wstr[256];
    charToWChar((char*)filename, wstr);
    //�t�@�C�����ݒ�
	this->physicsFileName.SetWindowTextW(wstr);
    
    //�X�V�𔽉f
    this->UpdateData();

    //���g�Ƀ^�u�ω����b�Z�[�W�𑗂�f�[�^���X�V����
    PostMessage(TCN_SELCHANGE);
}

void CPhysicsEditorDlg::setupDialogs(){
    this->monsterPage.setupDialog(theApp.editMonsterTypeId);
    this->monsterPage2.setupDialog();
    this->monsterPage3.setupDialog();
    this->monsterPage4.setupDialog();

    this->effectPage.setupDialog();
    this->projectilePage.setupDialog();
    this->physicsPage.setupDialog();

    weaponPage.setupDialog();
    weaponPage2.setupDialog();
}

void CPhysicsEditorDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	int sel = this->phyTabPane.GetCurSel();
	//MessageBox(L"CHANGED TAB");

	this->monsterPage.ShowWindow(sel == 0 ? SW_SHOW: SW_HIDE);
	this->monsterPage2.ShowWindow(sel == 1 ? SW_SHOW: SW_HIDE);
	this->monsterPage3.ShowWindow(sel == 2 ? SW_SHOW: SW_HIDE);
	this->monsterPage4.ShowWindow(sel == 3 ? SW_SHOW: SW_HIDE);
	this->effectPage.ShowWindow(sel == 4 ? SW_SHOW: SW_HIDE);
	this->projectilePage.ShowWindow(sel == 5 ? SW_SHOW: SW_HIDE);
	this->physicsPage.ShowWindow(sel == 6 ? SW_SHOW: SW_HIDE);
	this->weaponPage.ShowWindow(sel == 7 ? SW_SHOW: SW_HIDE);
	this->weaponPage2.ShowWindow(sel == 8 ? SW_SHOW: SW_HIDE);

	*pResult = 0;
}
void CPhysicsEditorDlg::OnFileExit32774()
{
	// TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	CSaveCheckDialog dlg;
	if( dlg.DoModal() == IDOK){
		//�I�����܂�
        this->DestroyWindow();
		
	}else{
		//�������܂���
	}
}

void CPhysicsEditorDlg::OnFileNew32771()
{
	// TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    //���݂̕ҏW�͍폜����܂��c
    if(MessageBox(L"If you do, all Editing parameters will disappear!", L"Caution�I",
        MB_OKCANCEL | MB_ICONEXCLAMATION) == IDCANCEL){
        //�������Ȃ�
        return;
    }
    //�f�t�H���g�����t�@�C����ǂݍ���
	//importPhysicsFile(DEFAULT_PHYSICS_FILE_NAME);
    setDefinitionsToDefault();

    setupDialogs();
}

void CPhysicsEditorDlg::OnFileSave()
{
	// TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	//�ۑ��_�C�A���O
    CString fnameStr;
    this->physicsFileName.GetWindowTextW(fnameStr);
    /*if(fnameStr == CString(DEFAULT_PHYSICS_FILE_NAME)){
        fnameStr = CString("hoge.phy");
    }*/
	CFileDialog dlg(FALSE, L"*.*", fnameStr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PhysicsFile (*.phy)|*.phy||", this);
	if( dlg.DoModal() == IDOK){
		CString filename = dlg.GetPathName();

		char str[256];
        strToChar(filename, str);

		export_definition_structures(str);

		this->physicsFileName.SetWindowTextW(filename);
		this->UpdateData();
	}
}



void CPhysicsEditorDlg::OnDestroy()
{
    
    CDialog::OnDestroy();
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
}

void CPhysicsEditorDlg::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    //����m�F
    //�I���m�F�_�C�A���O�\��
	CSaveCheckDialog dlg;
	if( dlg.DoModal() == IDOK){
		//�I�����܂�
        CDialog::OnClose();
		
	}else{
		//�������܂���
	}
}

/*BOOL CPhysicsEditorDlg::PreTranslateMessage(MSG* pMsg) 
{
    CDialog::PreTranslateMessage(pMsg);
    int x;  
    x = ::TranslateAccelerator(pMsg->hwnd, accel, pMsg);
    TRACE("%d\n", x);
    if(IsDialogMessage(pMsg)) {
        TRACE("��\n");
        return TRUE;
    } else {
        TRACE("��\n");
        TranslateMessage(pMsg);
        return CDialog::PreTranslateMessage(pMsg);
    }

}

*/