#include "MainFrame.h"
#include "PhysicsEditorOneWX.h"

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;


/**
	イベント処理用の識別ID(特殊なものに限る)
*/
namespace MainFrameEventId{
	enum{
		//ページ変更時
		ID_NOTE,
		//モンスターページ処理用
		ID_MONSTER_PAGE,
		ID_EFFECT_PAGE,
		ID_PROJECTILE_PAGE,
		ID_PHYSICS_PAGE,
		ID_WEAPON_PAGE,
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
	CreateStatusBar();
	SetStatusText( _T("get ready..."));

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

	//モンスターパネル
	this->monsterPanel = new MonsterPanel(this, wxID_ANY);
	//パネル配置用Sizer
	wxGridSizer* sizerMonster = new wxGridSizer(1);
	//パネルを配置
	sizerMonster->Add(monsterPanel, 0, wxEXPAND, 0);
	//モンスターページのSizerを設定
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
	Destroy();
}
