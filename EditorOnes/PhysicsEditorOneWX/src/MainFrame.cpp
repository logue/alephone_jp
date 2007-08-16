#include "MainFrame.h"

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;


/**
	メニューの識別ID(特殊なものに限る)
*/
namespace MainFrameMenuId{
	enum{
		
	};
};

/**イベント関連づけ*/
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

	//メニューの作成
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

	//配置
	
}
/**
	もし編集中であれば内容を破棄するか、その前に保存するか、キャンセルするか
	どうか問いただします。
	@return 
		wxYES:	破棄する前に保存する
		wxNO:	保存せずに破棄する
		wxCANCEL:キャンセルして処理を行わない
*/
int MainFrame::askDestroy()
{
	if(wxGetApp().isChanged()){
		//変更あり
        wxMessageDialog dlg(this,
			_T("Physics data has been modified. Do you save this before destruction? Click No to skip save."),
			_T("Destroy!"), wxYES_NO | wxCANCEL);
		return dlg.ShowModal();
	}else{
		//変更はない
		return wxNO;
	}
}

void MainFrame::OnNew(wxCommandEvent& ev)
{
	int result = askDestroy();
	wxCommandEvent dummy;
	if(result == wxYES){
		//保存
		OnSave(dummy);
	}else if(result == wxNO){
		//そのまま初期化
	}else{
		//キャンセル
		return;
	}
	wxGetApp().loadDefaultPhysicsFile();

	//ステータスバーに表示
	SetStatusText(_T("Create new physics file."));
}
void MainFrame::OnOpen(wxCommandEvent& ev)
{
	int result = askDestroy();
	wxCommandEvent dummy;
	if(result == wxYES){
		//保存
		OnSave(dummy);
	}else if(result == wxNO){
		//そのままオープン
	}else{
		//キャンセル
		return;
	}
    wxFileDialog fileDialog(this, _T("Choose a file"),
        _T("."), _T(""), _T("*.*"));

    if(fileDialog.ShowModal() == wxID_OK){
        wxString path = fileDialog.GetPath();
		wxGetApp().loadPhysicsFile(path.mb_str());

		//ステータスバーに表示
		SetStatusText(_T("Load physics file complete."));
	}
}
void MainFrame::OnSave(wxCommandEvent& ev)
{
	wxCommandEvent dummy;

	if(wxGetApp().isNew()){
		//新規状態
		OnSaveAs(dummy);
	}else{
		//今持っているファイル名で保存します
		std::string saveFilePath = wxGetApp().getSaveFilePath();
		wxGetApp().savePhysicsFile(saveFilePath.c_str());
		//ステータスバーに表示
		SetStatusText(_T("Save physics file complete."));
	}
}
void MainFrame::OnSaveAs(wxCommandEvent& ev)
{
	//新規保存先を選択します
    int style = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;
    wxString wildcard(_T("AlephOne physics file (*.phyA)|*.phyA|Any file|*.*"));
    wxFileDialog dlg(this, wxString(_T("Save at...")), 
        wxString(_T("")), wxString(_T("unknown.phyA")), wildcard,
        style);
    if(dlg.ShowModal() == wxID_OK){
		wxString str = dlg.GetPath();
		//保存
		wxGetApp().savePhysicsFile(str.mb_str());
		//ステータスバーに表示
		SetStatusText(_T("Save physics file complete."));
	}
}
void MainFrame::OnQuit(wxCommandEvent& ev)
{
	int result = this->askDestroy();
	wxCommandEvent dummy;
	if(result == wxYES){
		//保存
		OnSave(dummy);
	}else if(result == wxNO){
		//そのままオープン
	}else{
		//キャンセル
		return;
	}
}
