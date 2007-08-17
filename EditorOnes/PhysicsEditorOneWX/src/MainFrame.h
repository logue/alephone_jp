#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_

#include "Common.h"
#include "panel/MonsterPanel.h"
#include "panel/EffectPanel.h"
#include "panel/ProjectilePanel.h"
#include "panel/PhysicsPanel.h"
#include "panel/WeaponPanel.h"

class MainFrame: public wxFrame{
public:
private:
	/**タブ*/
	wxNotebook* notebook;

	/**各パネル*/
	MonsterPanel* monsterPanel;
	EffectPanel* effectPanel;
	ProjectilePanel* projectilePanel;
	PhysicsPanel* physicsPanel;
	WeaponPanel* weaponPanel;

public:
	void Create(wxWindow* parent, wxWindowID id);
protected:
	void OnNew(wxCommandEvent& ev);
	void OnOpen(wxCommandEvent& ev);
	void OnSave(wxCommandEvent& ev);
	void OnSaveAs(wxCommandEvent& ev);
	void OnQuit(wxCommandEvent& ev);

    DECLARE_EVENT_TABLE()
private:
	/**
		もし編集中であれば内容を破棄するか、その前に保存するか、キャンセルするか
		どうか問いただします。
		@return 
			wxYES:	破棄する前に保存する
			wxNO:	保存せずに破棄する
			wxCANCEL:キャンセルして処理を行わない
	*/
	int askDestroy();


public:
};

#endif
