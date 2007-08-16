#include "MainFrame.h"

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;


/**
	���j���[�̎���ID(����Ȃ��̂Ɍ���)
*/
namespace MainFrameMenuId{
	enum{
		
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
	::CreateStatusBar();
	::SetStatusText( _T("get ready..."));

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
}
