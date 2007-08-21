#include "MainFrame.h"
#include "PhysicsEditorOneWX.h"

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;


/**
	�C�x���g�����p�̎���ID(����Ȃ��̂Ɍ���)
*/
namespace MainFrameEventId{
	enum{
		//�y�[�W�ύX��
		ID_NOTE,
		//�����X�^�[�y�[�W�����p
		ID_MONSTER_PAGE,
		ID_EFFECT_PAGE,
		ID_PROJECTILE_PAGE,
		ID_PHYSICS_PAGE,
		ID_WEAPON_PAGE,
	};
};

/**�C�x���g�֘A�Â�*/
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_NEW, MainFrame::OnNew)
	EVT_MENU(wxID_OPEN, MainFrame::OnOpen)
	EVT_MENU(wxID_SAVE, MainFrame::OnSave)
	EVT_MENU(wxID_SAVEAS, MainFrame::OnSaveAs)
	EVT_MENU(wxID_EXIT, MainFrame::OnQuit)
END_EVENT_TABLE()

void MainFrame::Create(wxWindow* parent, wxWindowID id)
{
	wxString title = wxConvertMB2WX(TITLE);
	if(!wxFrame::Create(parent, id, title, wxDefaultPosition,
		wxSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT)))
	{
		hpl::error::halt("Unknown error occured when launch app.");
	}

	//status bar
	CreateStatusBar();
	SetStatusText( _T("get ready..."));

	//���j���[�̍쐬
	//File
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_NEW, _T("&New"));
	menuFile->Append(wxID_OPEN, _T("&Open"));
	menuFile->Append(wxID_SAVE, _T("&Save"));
	menuFile->Append(wxID_SAVEAS, _T("Save as..."));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, _T("E&xit"));

    wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, _T("&File"));

    SetMenuBar(menuBar);

	//�z�u
	this->notebook = new wxNotebook(this, MainFrameEventId::ID_NOTE, wxDefaultPosition, wxDefaultSize,
		wxNB_LEFT);
	bool select = true;
	wxNotebookPage* monsterPage = new wxNotebookPage(notebook, MainFrameEventId::ID_MONSTER_PAGE);
	this->notebook->AddPage(monsterPage, _T("Monsters"), select);
	wxNotebookPage* effectPage = new wxNotebookPage(notebook, MainFrameEventId::ID_EFFECT_PAGE);
	this->notebook->AddPage(effectPage, _T("Effects"));
	wxNotebookPage* projectilePage = new wxNotebookPage(notebook, MainFrameEventId::ID_PROJECTILE_PAGE);
	this->notebook->AddPage(projectilePage, _T("Projectiles"));
	wxNotebookPage* physicsPage = new wxNotebookPage(notebook, MainFrameEventId::ID_PHYSICS_PAGE);
	this->notebook->AddPage(physicsPage, _T("Physics"));
	wxNotebookPage* weaponPage = new wxNotebookPage(notebook, MainFrameEventId::ID_WEAPON_PAGE);
	this->notebook->AddPage(weaponPage, _T("Weapons"));

	//�����X�^�[�p�l��
	this->monsterPanel = new MonsterPanel(this, wxID_ANY);
	//�p�l���z�u�pSizer
	wxGridSizer* sizerMonster = new wxGridSizer(1);
	//�p�l����z�u
	sizerMonster->Add(monsterPanel, 0, wxEXPAND, 0);
	//�����X�^�[�y�[�W��Sizer��ݒ�
	monsterPage->SetSizer(sizerMonster);
	//sizerMonster->Fit(monsterPage);

	this->effectPanel = new EffectPanel(this, wxID_ANY);
	this->projectilePanel = new ProjectilePanel(this, wxID_ANY);
	this->physicsPanel = new PhysicsPanel(this, wxID_ANY);
	this->weaponPanel = new WeaponPanel(this, wxID_ANY);

	this->notebook->SetMinSize(wxSize(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT));

    wxGridSizer* sizer_base = new wxGridSizer(1);
	sizer_base->Add(this->notebook, 0,wxEXPAND,0);
	wxGridSizer* monsterSizer = new wxGridSizer(1);
	monsterSizer->Add(monsterPanel, 0, wxEXPAND, 0);
	notebook->SetSizer(monsterSizer);

    SetSizer(sizer_base);
    sizer_base->Fit(this);
    Layout();
}
/**
	�����ҏW���ł���Γ��e��j�����邩�A���̑O�ɕۑ����邩�A�L�����Z�����邩
	�ǂ����₢�������܂��B
	@return 
		wxYES:	�j������O�ɕۑ�����
		wxNO:	�ۑ������ɔj������
		wxCANCEL:�L�����Z�����ď������s��Ȃ�
*/
int MainFrame::askDestroy()
{
	if(wxGetApp().isChanged()){
		//�ύX����
        wxMessageDialog dlg(this,
			_T("Physics data has been modified. Do you save this before destruction? Click No to skip save."),
			_T("Destroy!"), wxYES_NO | wxCANCEL);
		return dlg.ShowModal();
	}else{
		//�ύX�͂Ȃ�
		return wxNO;
	}
}

void MainFrame::OnNew(wxCommandEvent& ev)
{
	int result = askDestroy();
	wxCommandEvent dummy;
	if(result == wxYES){
		//�ۑ�
		OnSave(dummy);
	}else if(result == wxNO){
		//���̂܂܏�����
	}else{
		//�L�����Z��
		return;
	}
	wxGetApp().loadDefaultPhysicsFile();

	//�X�e�[�^�X�o�[�ɕ\��
	SetStatusText(_T("Create new physics file."));
}
void MainFrame::OnOpen(wxCommandEvent& ev)
{
	int result = askDestroy();
	wxCommandEvent dummy;
	if(result == wxYES){
		//�ۑ�
		OnSave(dummy);
	}else if(result == wxNO){
		//���̂܂܃I�[�v��
	}else{
		//�L�����Z��
		return;
	}
    wxFileDialog fileDialog(this, _T("Choose a file"),
        _T("."), _T(""), _T("*.*"));

    if(fileDialog.ShowModal() == wxID_OK){
        wxString path = fileDialog.GetPath();
		wxGetApp().loadPhysicsFile(path.mb_str());

		//�X�e�[�^�X�o�[�ɕ\��
		SetStatusText(_T("Load physics file complete."));
	}
}
void MainFrame::OnSave(wxCommandEvent& ev)
{
	wxCommandEvent dummy;

	if(wxGetApp().isNew()){
		//�V�K���
		OnSaveAs(dummy);
	}else{
		//�������Ă���t�@�C�����ŕۑ����܂�
		std::string saveFilePath = wxGetApp().getSaveFilePath();
		wxGetApp().savePhysicsFile(saveFilePath.c_str());
		//�X�e�[�^�X�o�[�ɕ\��
		SetStatusText(_T("Save physics file complete."));
	}
}
void MainFrame::OnSaveAs(wxCommandEvent& ev)
{
	//�V�K�ۑ����I�����܂�
    int style = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
    wxString wildcard(_T("AlephOne physics file (*.phyA)|*.phyA|Any file|*.*"));
    wxFileDialog dlg(this, wxString(_T("Save at...")), 
        wxString(_T("")), wxString(_T("unknown.phyA")), wildcard,
        style);
    if(dlg.ShowModal() == wxID_OK){
		wxString str = dlg.GetPath();
		//�ۑ�
		wxGetApp().savePhysicsFile(str.mb_str());
		//�X�e�[�^�X�o�[�ɕ\��
		SetStatusText(_T("Save physics file complete."));
	}
}
void MainFrame::OnQuit(wxCommandEvent& ev)
{
	int result = this->askDestroy();
	wxCommandEvent dummy;
	if(result == wxYES){
		//�ۑ�
		OnSave(dummy);
	}else if(result == wxNO){
		//���̂܂܃I�[�v��
	}else{
		//�L�����Z��
		return;
	}
	Destroy();
}
