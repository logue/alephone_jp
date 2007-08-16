#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_

#include "Common.h"

class MainFrame: public wxFrame{
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
